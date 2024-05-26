#pragma once

#include <stdlib.h>
#include "property/csv_property.h"
#include "../content/csv_content.h"

struct CSV_PARSER;
typedef struct CSV_PARSER CSV_PARSER;

typedef enum CSV_PARSER_STATUS {
	CSV_PARSER_SUCCESS = 0,
	CSV_PARSER_INVALID_PARAMETER,
} CSV_PARSER_STATUS;

extern CSV_PARSER *csv_parser_init(const CSV_PROPERTIES *props);
extern CSV_PARSER_STATUS csv_parser_load_from_file(CSV_PARSER *this, const char *filePath);
extern CSV_PARSER_STATUS csv_parser_load_from_data(CSV_PARSER *this, const char *data, size_t dataSize);
extern const CSV_CONTENT *csv_parser_get_content(CSV_PARSER *this);
extern void csv_parser_destroy(CSV_PARSER *this);
