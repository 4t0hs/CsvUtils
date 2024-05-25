#pragma once

#include <stdbool.h>

typedef enum CSV_EOL_CODE {
	CsvEolCr = 0,
	CsvEolCrLf,
} CSV_EOL_CODE;

typedef struct CSV_PROPERTIES {
	bool		hasHeader;
} CSV_PROPERTIES;
