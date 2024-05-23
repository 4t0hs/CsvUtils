#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "CsvContent/CsvItem/CsvItem.h"
#include "CsvItem.h"

#define CLEAR(this)	(memset(this, 0, sizeof(CsvItem_t)))

void CsvItem_Init(CsvItem_t *this) {
	CLEAR(this);
}

void CsvItem_Set(CsvItem_t *this, char *value) {
	this->text = value;
}

void CsvItem_MoveOwner(CsvItem_t *this, CsvItem_t *newOwner) {
	*newOwner = *this;
	this->text = NULL;
}

void CsvItem_Destroy(CsvItem_t *this) {
	CLEAR(this);
}

void CsvItem_Print(CsvItem_t *this) {
	printf("%s", this->text);
}

bool CsvItem_Equals(CsvItem_t *this, CsvItem_t *item) {
	return strcmp(this->text, item->text) ? false : true;
}
