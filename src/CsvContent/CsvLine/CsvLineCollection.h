#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "CsvContent/CsvLine/CsvLine.h"

typedef struct CsvLineCollection {
	CsvLine_t *_list;
	size_t length;
	size_t capacity;
} CsvLineCollection_t;

extern void CsvLineCollection_Init(CsvLineCollection_t *this);
extern void CsvLineCollection_Resize(CsvLineCollection_t *this, size_t newCapacity);
extern void CsvLineCollection_MoveAndAdd(CsvLineCollection_t *this, CsvLine_t *moveLine);
extern void CsvLineCollection_Destroy(CsvLineCollection_t *this);
extern void CsvLineCollection_Print(CsvLineCollection_t *this);
extern bool CsvLineCollection_Equals(CsvLineCollection_t *this, CsvLineCollection_t *lines);
