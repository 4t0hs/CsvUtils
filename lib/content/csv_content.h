#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "content/line/csv_line_collection.h"
typedef struct CSV_CONTENT {
	CSV_LINE_COLLECTION lines;
} CSV_CONTENT;

extern void csv_content_init(CSV_CONTENT *this);
extern void csv_content_move_back_line(CSV_CONTENT *this, CSV_LINE *line);
extern void csv_content_destroy(CSV_CONTENT *this);
extern void csv_content_print(CSV_CONTENT *this);
extern bool csv_content_equals(CSV_CONTENT *this, CSV_CONTENT *content);


