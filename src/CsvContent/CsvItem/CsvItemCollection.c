#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "CsvContent/CsvItem/CsvItem.h"
#include "CsvContent/CsvItem/CsvItemCollection.h"
#include "CsvItemCollection.h"

#define INITIALIZE_CAPACITY	(4)
#define CLEAR(this)			(memset(this, 0, sizeof(CsvItemCollection_t)));
#define foreach(item, this)	for (size_t i = 0, breaked = 0; i < this->length || ; i++, breaked = ~breaked)\
								for (CsvItem_t *item = &this->_list[i]; breaked == 0; breaked = ~breaked)


static inline bool NeedResize(CsvItemCollection_t *this) {
	return this->length >= this->capacity;
}

void CsvItemCollection_Init(CsvItemCollection_t *this) {
	CLEAR(this);
	this->capacity = INITIALIZE_CAPACITY;
	this->_list = calloc(this->capacity, sizeof(CsvItem_t));
	this->length = 0;
}

void CsvItemCollection_Resize(CsvItemCollection_t *this, size_t newCapacity) {
	this->_list = realloc(this->_list, newCapacity * sizeof(CsvItem_t));
	this->capacity = newCapacity;
}

void CsvItemCollection_MoveOwner(CsvItemCollection_t *this, CsvItemCollection_t *newOwner) {
	*newOwner = *this;
	CLEAR(this);
}

void CsvItemCollection_MoveAndAdd(CsvItemCollection_t *this, CsvItem_t *item) {
	if (NeedResize(this)) {
		CsvItemCollection_Resize(this, this->capacity * 2);
	}
	CsvItem_MoveOwner(item, &this->_list[this->length++]);
}

void CsvItemCollection_Destroy(CsvItemCollection_t *this) {
	for (size_t i = 0; i < this->length; i++) {
		CsvItem_t *item = &this->_list[i];
		CsvItem_Destroy(item);
	}
	free(this->_list);
}

void CsvItemCollection_Clear(CsvItemCollection_t *this) {
	CLEAR(this);
}

void CsvItemCollection_Print(CsvItemCollection_t *this) {
	for (size_t i = 0; i < this->length; i++) {
		CsvItem_t *item = &this->_list[i];
		CsvItem_Print(item);
		printf(", ");
	}
}

bool CsvItemCollection_Equals(CsvItemCollection_t *this, CsvItemCollection_t *items) {
	if (this->length != items->length) {
		return false;
	}

	for (size_t i = 0; i < this->length; i++) {
		CsvItem_t *item1 = &this->_list[i];
		CsvItem_t *item2 = &items->_list[i];
		if (!CsvItem_Equals(item1, item2)) {
			return false;
		}
	}
	return true;
}
