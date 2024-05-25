#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "content/line/csv_line_collection.h"
typedef struct CSV_CONTENT {
	CSV_LINE_COLLECTION lines;
} CSV_CONTENT;

extern void CsvContent_Init(CSV_CONTENT *this);
extern void CsvContent_MoveBackLine(CSV_CONTENT *this, CSV_LINE *line);
extern void CsvContent_Destroy(CSV_CONTENT *this);
extern void CsvContent_Print(CSV_CONTENT *this);
extern bool CsvContent_Equals(CSV_CONTENT *this, CSV_CONTENT *content);


