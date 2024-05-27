#pragma once

#include <stdlib.h>
#include "property/csv_property.h"
#include "../content/csv_content.h"
#include "../csv.h"

struct CSV_PARSER;
typedef struct CSV_PARSER CSV_PARSER;

extern CSV_PARSER *csv_parser_init(const CSV_PROPERTIES *props);
extern CSV_RETURN_CODE csv_parser_load_from_file(CSV_PARSER *this, const char *filePath);
extern CSV_RETURN_CODE csv_parser_load_from_data(CSV_PARSER *this, const char *data, size_t dataSize);
extern const CSV_CONTENT *csv_parser_get_content(CSV_PARSER *this);
extern void csv_parser_destroy(CSV_PARSER *this);
