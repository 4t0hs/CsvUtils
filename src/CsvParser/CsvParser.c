#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "CsvProperties/CsvProperties.h"
#include "Utilities/File/File.c"

typedef struct CsvItem {
	char *text;
} CsvItem_t;

void CsvItemSet(CsvItem_t *this, char *value) {
	this->text = value;
}


#define INITIALIZE_CAPACITY	(4)

typedef struct CsvLine {
	CsvItem_t *items;
	size_t		length;
	size_t		capacity;
} CsvLine_t;

void CsvLineInit(CsvLine_t *this) {
	memset(this, 0, sizeof(CsvLine_t));
	this->capacity = INITIALIZE_CAPACITY;
	this->items = calloc(this->capacity, sizeof(CsvItem_t));
	this->length = 0;
}

void CsvLineResize(CsvLine_t *this, size_t new_capacity) {

}

void CsvLineMoveOwner(CsvLine_t *this, CsvLine_t *newOwner) {
	*newOwner = *this;
	this->capacity = INITIALIZE_CAPACITY;
	this->length = 0;
}

void CsvLineAddItem(CsvLine_t *this, const CsvItem_t *item) {
	if (this->length >= this->capacity) {
		CsvLineResize(this, this->capacity * 2);
	}

	this->items[this->length++] = *item;
}


typedef struct CsvContent {
	CsvLine_t	header;
	CsvLine_t *lines;
	size_t		length;
	size_t		capacity;
} CsvContent_t;

void CsvContentInit(CsvContent_t *this) {
	memset(this, 0, sizeof(CsvContent_t));
	this->capacity = INITIALIZE_CAPACITY;
	this->lines = calloc(this->capacity, sizeof(CsvLine_t));
	this->length = 0;
}

void CsvContentResize(CsvContent_t *this, size_t new_capacity) {

}

void CsvContentAddLine(CsvContent_t *this, CsvLine_t *line) {

}

void CsvContentMoveBackLine(CsvContent_t *this, CsvLine_t *line) {
	if (this->length >= this->capacity) {
		CsvContentResize(this, this->capacity * 2);
	}
	CsvLineMoveOwner(line, &this->lines[this->length++]);
}

typedef struct CsvParser_t {
	CsvProperties_t	properties;
	CsvContent_t	content;
	FileBuffer_t	file;
} CsvParser_t;

typedef enum CsvParserStatus {
	CSV_PARSER_SUCCESS = 0,
	CSV_PARSER_INVALID_PARAMETER,
} CsvParserStatus;

static const char *eolCharacters[] = {
	"\n", "\r\n",
};

CsvParser_t *CsvParserInit(const CsvProperties_t *props) {
	CsvParser_t *this = (CsvParser_t *)calloc(1, sizeof(*this));

	this->properties = *props;
	CsvContentInit(&this->content);
	return this;
}

static const uint8_t Eof[] = { 0xFF };
#define EOF_LENGTH	(sizeof(Eof))
#define COMMA				(',')
#define CARRIGE_RETURN		('\r')
#define LINE_FEED			('\n')
static bool IsEof(const char *fileData) {
	return memcmp(fileData, Eof, EOF_LENGTH) ? false : true;
}
static inline bool IsComma(char c) {
	return c == COMMA;
}
static inline bool IsCr(char c) {
	return c == LINE_FEED;
}
static inline bool IsLf(char c) {
	return c == CARRIGE_RETURN;
}
static inline bool IsCrLf(char c) {
	return IsCr(c) && IsLf(c);
}

static CsvParserStatus parse(CsvParser_t *this) {
	CsvLine_t line;
	CsvLineInit(&line);

	char *savedText = this->file.data;
	for (char *str = this->file.data; true; str++) {
		char *c = str;
		char *nextChar = str + 1;
		if (IsComma(*c)) {
			CsvLineAddItem(&line, &(CsvItem_t) {
				.text = savedText,
			});
			*c = '\0';
		} else if (IsCrLf(*c)) {
			CsvContentMoveBackLine(&this->content, &line);
			*c = '\0';
			nextChar = '\0';
			savedText = nextChar + 1;
		} else if (IsCr(*c)) {
			CsvContentMoveBackLine(&this->content, &line);
			*c = '\0';
			savedText = nextChar;
		} else if (IsEof(c)) {

		} else {
			// do nothing
		}
	}
}

static int LoadFile(CsvParser_t *this, const char *filePath) {
	ssize_t fileSize = FileGetSize(filePath);
	if (fileSize < 0) {
		return fileSize;
	}
	size_t allocateSize = fileSize + EOF_LENGTH;
	this->file.data = malloc(allocateSize);
	int ret = FileRead(filePath, this->file.data, fileSize);
	if (ret < 0) {
		free(this->file.data);
		this->file.data = NULL;
		return ret;
	}
	this->file.size = allocateSize;
	// eofを入れる
	memcpy(&this->file.data[fileSize], Eof, EOF_LENGTH);
}

CsvParserStatus CsvParserLoadFromFile(CsvParser_t *this, const char *filePath) {
	if (!this) return CSV_PARSER_INVALID_PARAMETER;
	LoadFile(this, filePath);
	parse(this);
}



