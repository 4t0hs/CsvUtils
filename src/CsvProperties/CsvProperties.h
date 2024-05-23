#pragma once

#include <stdbool.h>

typedef enum CsvEolCode {
	CsvEolCr = 0,
	CsvEolCrLf,
} CsvEolCode;

typedef struct CsvPeroperties {
	bool		hasHeader;
} CsvProperties_t;
