#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "CsvProperties/CsvProperties.h"
#include "Utilities/File/File.h"
#include "CsvContent/CsvContent.h"
#include "CsvParser/CsvParser.h"
#include "CsvParser.h"

typedef struct FileBuffer {
	char *data;
	size_t	size;
} FileBuffer_t;
struct CsvParser {
	CsvProperties_t	properties;
	CsvContent_t	content;
	FileBuffer_t	file;
};

static const char *eolCharacters[] = {
	"\n", "\r\n",
};

#define EOF				((uint8_t)0xFF)
#define EOF_LENGTH		(sizeof(EOF))
#define COMMA			(',')
#define CARRIGE_RETURN	('\r')
#define LINE_FEED		('\n')
static bool IsEof(char c) {
	return (uint8_t)c == EOF;
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

#define TERMINATE(c)	((c) = '\0')

static inline bool IsExtraChars(char c) {
	return c == '\0' || IsCr(c) || IsLf(c);
}

static void FillEof(char *data, size_t size) {
	// 最後の値は必ずEofにする
	data[size - 1] = EOF;
	for (size_t i = size - 2; i != 0; i--) {
		if (!IsExtraChars(data[i])) {
			return;
		}
		data[i] = EOF;
	}
}

static CsvParserStatus parse(CsvParser_t *this) {
	CsvLine_t line;
	CsvItem_t item;
	CsvLine_Init(&line);
	CsvItem_Init(&item);
	CsvItem_Set(&item, this->file.data);

	for (char *str = this->file.data; true; str++) {
		char *c = str;
		char *nextChar = str + 1;
		if (IsComma(*c)) {
			TERMINATE(*c);	// 終端
			CsvLine_MoveBackItem(&line, &item);
			CsvItem_Set(&item, nextChar);
		} else if (IsCrLf(*c)) {
			TERMINATE(*c);
			TERMINATE(*nextChar);
			CsvLine_MoveBackItem(&line, &item);
			CsvContent_MoveBackLine(&this->content, &line);
			CsvLine_Init(&line);
			CsvItem_Set(&item, nextChar + 1);
		} else if (IsCr(*c)) {
			TERMINATE(*c);
			CsvLine_MoveBackItem(&line, &item);
			CsvContent_MoveBackLine(&this->content, &line);
			CsvLine_Init(&line);
			CsvItem_Set(&item, nextChar);
		} else if (IsEof(*c)) {
			TERMINATE(*c);
			CsvLine_MoveBackItem(&line, &item);
			CsvContent_MoveBackLine(&this->content, &line);
			break;
		} else {
			// do nothing
		}
	}
	return CSV_PARSER_SUCCESS;
}

static int LoadFile(CsvParser_t *this, const char *filePath) {
	ssize_t fileSize = FileGetSize(filePath);
	if (fileSize < 0) {
		return (int)fileSize;
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
	FillEof(this->file.data, this->file.size);
	return 0;
}

CsvParser_t *CsvParser_Init(const CsvProperties_t *props) {
	CsvParser_t *this = (CsvParser_t *)calloc(1, sizeof(*this));

	this->properties = *props;
	CsvContent_Init(&this->content);
	return this;
}

CsvParserStatus CsvParser_LoadFromFile(CsvParser_t *this, const char *filePath) {
	if (!this) return CSV_PARSER_INVALID_PARAMETER;
	if (LoadFile(this, filePath) != 0) {
		return CSV_PARSER_INVALID_PARAMETER;
	}
	return parse(this);
}

CsvParserStatus CsvParser_LoadFromData(CsvParser_t *this, const char *data, size_t dataSize) {
	if (!this) return CSV_PARSER_INVALID_PARAMETER;
	if (!data || dataSize == 0) {
		return CSV_PARSER_INVALID_PARAMETER;
	}
	size_t allocateSize = dataSize + EOF_LENGTH;
	this->file.data = malloc(allocateSize);
	this->file.size = allocateSize;
	memcpy(this->file.data, data, dataSize);
	FillEof(this->file.data, allocateSize);
	return parse(this);
}

const CsvContent_t *CsvParser_GetContent(CsvParser_t *this) {
	return &this->content;
}

void CsvParser_Destroy(CsvParser_t *this) {
	if (!this) return;

	CsvContent_Destroy(&this->content);
	if (this->file.data) free(this->file.data);
	free(this);
	this = NULL;
}


