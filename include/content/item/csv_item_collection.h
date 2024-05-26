
#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "csv_item.h"

typedef struct CSV_ITEM_COLLECTION {
	CSV_ITEM *_list;
	size_t length;
	size_t capacity;
} CSV_ITEM_COLLECTION;

extern void csv_item_collection_init(CSV_ITEM_COLLECTION *this);
extern void csv_item_collection_resize(CSV_ITEM_COLLECTION *this, size_t newCapacity);
extern void csv_item_collection_move_owner(CSV_ITEM_COLLECTION *this, CSV_ITEM_COLLECTION *newOwner);
extern void csv_item_collection_move_and_add(CSV_ITEM_COLLECTION *this, CSV_ITEM *item);
extern void csv_item_collection_destroy(CSV_ITEM_COLLECTION *this);
extern void csv_item_collection_clear(CSV_ITEM_COLLECTION *this);
extern void csv_item_collection_print(CSV_ITEM_COLLECTION *this);
extern bool csv_item_collection_equals(CSV_ITEM_COLLECTION *this, CSV_ITEM_COLLECTION *items);
