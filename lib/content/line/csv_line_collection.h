#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "content/line/csv_line.h"

typedef struct CSV_LINE_COLLECTION {
	CSV_LINE *list;
	size_t length;
	size_t capacity;
} CSV_LINE_COLLECTION;

extern void csv_line_collection_init(CSV_LINE_COLLECTION *this);
extern void csv_line_collection_resize(CSV_LINE_COLLECTION *this, size_t newCapacity);
extern void csv_line_collection_move_and_add(CSV_LINE_COLLECTION *this, CSV_LINE *moveLine);
extern void csv_line_collection_destroy(CSV_LINE_COLLECTION *this);
extern void csv_line_collection_print(CSV_LINE_COLLECTION *this);
extern bool csv_line_collection_equals(CSV_LINE_COLLECTION *this, CSV_LINE_COLLECTION *lines);
