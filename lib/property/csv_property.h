#pragma once

#include <stdbool.h>

typedef enum CSV_EOL_CODE {
	CSV_EOL_CR = 0,
	CSV_EOL_CRLF,
} CSV_EOL_CODE;

typedef struct CSV_PROPERTIES {
	bool		has_header;
} CSV_PROPERTIES;
