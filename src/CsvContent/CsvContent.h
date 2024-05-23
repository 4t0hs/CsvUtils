#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "CsvContent/CsvLine/CsvLineCollection.h"
typedef struct CsvContent {
	CsvLineCollection_t lines;
} CsvContent_t;

extern void CsvContent_Init(CsvContent_t *this);
extern void CsvContent_MoveBackLine(CsvContent_t *this, CsvLine_t *line);
extern void CsvContent_Destroy(CsvContent_t *this);
extern void CsvContent_Print(CsvContent_t *this);
extern bool CsvContent_Equals(CsvContent_t *this, CsvContent_t *content);


