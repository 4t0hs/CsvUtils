#pragma once

#include <stdbool.h>

typedef struct CsvItem {
	char *text;
} CsvItem_t;

extern void CsvItem_Init(CsvItem_t *this);
extern void CsvItem_Set(CsvItem_t *this, char *value);
extern void CsvItem_MoveOwner(CsvItem_t *this, CsvItem_t *newOwner);
extern void CsvItem_Destroy(CsvItem_t *this);
extern void CsvItem_Print(CsvItem_t *this);
extern bool CsvItem_Equals(CsvItem_t *this, CsvItem_t *item);
