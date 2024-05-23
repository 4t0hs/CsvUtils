#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "CsvContent/CsvItem/CsvItemCollection.h"
typedef struct CsvLine {
	CsvItemCollection_t	items;
} CsvLine_t;

extern void CsvLine_Init(CsvLine_t *this);
extern void CsvLine_MoveOwner(CsvLine_t *this, CsvLine_t *newOwner);
extern void CsvLine_MoveBackItem(CsvLine_t *this, CsvItem_t *item);
extern void CsvLine_Destroy(CsvLine_t *this);
extern void CsvLine_Print(CsvLine_t *this);
extern bool CsvLine_Equals(CsvLine_t *this, CsvLine_t *line);
