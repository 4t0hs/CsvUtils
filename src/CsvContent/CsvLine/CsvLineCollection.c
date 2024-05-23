#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "CsvContent/CsvLine/CsvLineCollection.h"
#include "CsvLineCollection.h"

#define INITIALIZE_CAPACITY	(4)
#define CLEAR(this)			(memset(this, 0, sizeof(CsvLineCollection_t)))

static inline bool NeedResize(CsvLineCollection_t *this) {
	return this->length >= this->capacity;
}
void CsvLineCollection_Init(CsvLineCollection_t *this) {
	this->capacity = INITIALIZE_CAPACITY;
	this->_list = calloc(this->capacity, sizeof(CsvLine_t));
	this->length = 0;
}

void CsvLineCollection_Resize(CsvLineCollection_t *this, size_t newCapacity) {
	this->_list = realloc(this->_list, newCapacity * sizeof(CsvLine_t));
	this->capacity = newCapacity;
}

void CsvLineCollection_MoveAndAdd(CsvLineCollection_t *this, CsvLine_t *moveLine) {
	if (NeedResize(this)) {
		CsvLineCollection_Resize(this, this->capacity * 2);
	}
	CsvLine_MoveOwner(moveLine, &this->_list[this->length++]);
}

void CsvLineCollection_Destroy(CsvLineCollection_t *this) {
	for (size_t i = 0; i < this->length; i++) {
		CsvLine_t *line = &this->_list[i];
		CsvLine_Destroy(line);
	}
	free(this->_list);
}

void CsvLineCollection_Print(CsvLineCollection_t *this) {
	for (size_t i = 0; i < this->length; i++) {
		CsvLine_t *line = &this->_list[i];
		CsvLine_Print(line);
		printf("\n");
	}
}

bool CsvLineCollection_Equals(CsvLineCollection_t *this, CsvLineCollection_t *lines) {
	if (this->length != lines->length) {
		return false;
	}
	for (size_t i = 0; i < this->length; i++) {
		CsvLine_t *line1 = &this->_list[i];
		CsvLine_t *line2 = &lines->_list[i];
		if (!CsvLine_Equals(line1, line2)) {
			return false;
		}
	}
	return true;
}

