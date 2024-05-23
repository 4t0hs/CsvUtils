#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "CsvContent/CsvItem/CsvItem.h"

typedef struct CsvItemCollection {
	CsvItem_t *_list;
	size_t		length;
	size_t		capacity;
} CsvItemCollection_t;

extern void CsvItemCollection_Init(CsvItemCollection_t *this);
extern void CsvItemCollection_Resize(CsvItemCollection_t *this, size_t newCapacity);
extern void CsvItemCollection_MoveOwner(CsvItemCollection_t *this, CsvItemCollection_t *newOwner);
extern void CsvItemCollection_MoveAndAdd(CsvItemCollection_t *this, CsvItem_t *item);
extern void CsvItemCollection_Destroy(CsvItemCollection_t *this);
extern void CsvItemCollection_Clear(CsvItemCollection_t *this);
extern void CsvItemCollection_Print(CsvItemCollection_t *this);
extern bool CsvItemCollection_Equals(CsvItemCollection_t *this, CsvItemCollection_t *items);
