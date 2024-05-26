#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "property/csv_property.h"
#include "utilities/file/file.h"
#include "content/csv_content.h"
#include "parser/csv_parser.h"

typedef struct FILE_BUFFER {
	char *data;
	size_t size;
} FILE_BUFFER;
struct CSV_PARSER {
	CSV_PROPERTIES properties;
	CSV_CONTENT content;
	FILE_BUFFER file;
};

static const char *eol_chars[] = {
	"\n", "\r\n",
};

#define EOF				((uint8_t)0xFF)
#define EOF_LENGTH		(sizeof(EOF))
#define COMMA			(',')
#define CARRIGE_RETURN	('\r')
#define LINE_FEED		('\n')
static inline bool is_eof(char c) {
	return (uint8_t)c == EOF;
}
static inline bool is_comma(char c) {
	return c == COMMA;
}
static inline bool is_cr(char c) {
	return c == LINE_FEED;
}
static inline bool is_lf(char c) {
	return c == CARRIGE_RETURN;
}
static inline bool is_crlf(char c, char next_char) {
	return is_lf(c) && is_cr(next_char);
}

#define TERMINATE(c)	((c) = '\0')

static inline bool is_extra_chars(char c) {
	return c == '\0' || is_cr(c) || is_lf(c);
}

static inline bool is_ascii(char c) {
	return c > 0x7F;
}

static bool is_not_supported_char_code(const char *data, size_t size) {
	for (size_t i = 0; i < size; i++) {
		if (!is_ascii(data[i])) {
			return false;
		}
	}
	return true;
}

static void fill_eof(char *data, size_t size) {
	// 最後の値は必ずEofにする
	data[size - 1] = EOF;
	for (size_t i = size - 2; i != 0; i--) {
		if (!is_extra_chars(data[i])) {
			return;
		}
		data[i] = EOF;
	}
}

static CSV_PARSER_STATUS parse(CSV_PARSER *this) {
	CSV_LINE line;
	CSV_ITEM item;
	csv_line_init(&line);
	csv_item_init(&item);
	csv_item_set(&item, this->file.data);

	for (char *str = this->file.data; true; str++) {
		char *c = str;
		char *next_char = str + 1;
		if (is_comma(*c)) {
			TERMINATE(*c);	// 終端
			csv_line_move_back_item(&line, &item);
			csv_item_set(&item, next_char);
		} else if (is_eof(*c)) {
			TERMINATE(*c);
			csv_line_move_back_item(&line, &item);
			csv_content_move_back_line(&this->content, &line);
			break;
		} else if (is_crlf(*c, *next_char)) {
			TERMINATE(*c);
			TERMINATE(*next_char);
			csv_line_move_back_item(&line, &item);
			csv_content_move_back_line(&this->content, &line);
			csv_line_init(&line);
			csv_item_set(&item, next_char + 1);
		} else if (is_cr(*c)) {
			TERMINATE(*c);
			csv_line_move_back_item(&line, &item);
			csv_content_move_back_line(&this->content, &line);
			csv_line_init(&line);
			csv_item_set(&item, next_char);
		} else {
			// do nothing
		}
	}
	return CSV_PARSER_SUCCESS;
}

static int load_file(CSV_PARSER *this, const char *file_path) {
	ssize_t file_size = file_get_size(file_path);
	if (file_size < 0) {
		return (int)file_size;
	}
	size_t allocate_size = file_size + EOF_LENGTH;
	this->file.data = malloc(allocate_size);
	int ret = file_read(file_path, this->file.data, file_size);
	if (ret < 0) {
		free(this->file.data);
		this->file.data = NULL;
		return ret;
	}
	this->file.size = allocate_size;
	fill_eof(this->file.data, this->file.size);
	return 0;
}

CSV_PARSER *csv_parser_init(const CSV_PROPERTIES *props) {
	CSV_PARSER *this = (CSV_PARSER *)calloc(1, sizeof(*this));

	this->properties = *props;
	csv_content_init(&this->content);
	return this;
}

CSV_PARSER_STATUS csv_parser_load_from_file(CSV_PARSER *this, const char *file_path) {
	if (!this) return CSV_PARSER_INVALID_PARAMETER;
	if (load_file(this, file_path) != 0) {
		return CSV_PARSER_INVALID_PARAMETER;
	}
	return parse(this);
}

CSV_PARSER_STATUS csv_parser_load_from_data(CSV_PARSER *this, const char *data, size_t data_size) {
	if (!this) return CSV_PARSER_INVALID_PARAMETER;
	if (!data || data_size == 0) {
		return CSV_PARSER_INVALID_PARAMETER;
	}
	size_t allocate_size = data_size + EOF_LENGTH;
	this->file.data = malloc(allocate_size);
	this->file.size = allocate_size;
	memcpy(this->file.data, data, data_size);
	fill_eof(this->file.data, allocate_size);
	return parse(this);
}

const CSV_CONTENT *csv_parser_get_content(CSV_PARSER *this) {
	return &this->content;
}

void csv_parser_destroy(CSV_PARSER *this) {
	if (!this) return;

	csv_content_destroy(&this->content);
	if (this->file.data) free(this->file.data);
	free(this);
	this = NULL;
}


