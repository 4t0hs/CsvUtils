#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "../item/csv_item_collection.h"
typedef struct CSV_LINE {
	CSV_ITEM_COLLECTION	items;
} CSV_LINE;

extern void csv_line_init(CSV_LINE *this);
extern void csv_line_move_owner(CSV_LINE *this, CSV_LINE *newOwner);
extern void csv_line_move_back_item(CSV_LINE *this, CSV_ITEM *item);
extern void csv_line_destroy(CSV_LINE *this);
extern void csv_line_print(CSV_LINE *this);
extern bool csv_line_equals(CSV_LINE *this, CSV_LINE *line);
