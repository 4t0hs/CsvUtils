#pragma once

#include <stdbool.h>

typedef struct CSV_ITEM {
	char *text;
} CSV_ITEM;

extern void csv_item_init(CSV_ITEM *this);
extern void csv_item_set(CSV_ITEM *this, char *value);
extern void csv_item_move_owner(CSV_ITEM *this, CSV_ITEM *newOwner);
extern void csv_item_destroy(CSV_ITEM *this);
extern void csv_item_print(CSV_ITEM *this);
extern bool csv_item_equals(CSV_ITEM *this, CSV_ITEM *item);
