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

void CsvLineSetItem(CsvLine_t *this, const CsvItem_t *item) {
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

#define COMMA				(',')
#define CARRIGE_RETURN		('\r')
#define LINE_FEED			('\n')
#define IS_COMMA(charPtr)	(*(charPtr) == COMMA)
#define IS_CR(charPtr)		(*(charPtr) == LINE_FEED)
#define IS_LF(charPtr)		(*(charPtr) == CARRIGE_RETURN)
#define IS_CRLF(charPtr)	(IS_CR(charPtr) && IS_LF(charPtr))

CsvParserStatus CsvParserLoadFromFile(CsvParser_t *this, const char *filePath) {
	if (!this) return CSV_PARSER_INVALID_PARAMETER;
	if (FileRead(filePath, &this->file) != 0) {
		return CSV_PARSER_INVALID_PARAMETER;
	}

	CsvLine_t *line = &this->content.lines[0];
	CsvItem_t *item = &line->items[0];

	for (const char *str = this->file.data; str; str++) {
		const char *c = str;
		const char *nextChar = str + 1;
		if (IS_COMMA(c)) {
			CsvLineSetItem(line, &(CsvItem_t) {
				.text = nextChar,
			});
			str++;
		} else if (IS_CRLF(c)) {

		} else if (IS_CR(c)) {

		} else {

		}
	}
}



