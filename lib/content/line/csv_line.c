#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "content/line/csv_line.h"
#include "content/item/csv_item_collection.h"

#define CLEAR(this)	(memset(this, 0, sizeof(CSV_LINE)))

void csv_line_init(CSV_LINE *this) {
	CLEAR(this);
	csv_item_collection_init(&this->items);
}

void csv_line_move_owner(CSV_LINE *this, CSV_LINE *newOwner) {
	*newOwner = *this;
	CLEAR(this);
}

void csv_line_move_back_item(CSV_LINE *this, CSV_ITEM *moveItem) {
	csv_item_collection_move_and_add(&this->items, moveItem);
}

void csv_line_destroy(CSV_LINE *this) {
	csv_item_collection_destroy(&this->items);
	CLEAR(this);
}

void csv_line_print(CSV_LINE *this) {
	csv_item_collection_print(&this->items);
}

bool csv_line_equals(CSV_LINE *this, CSV_LINE *line) {
	return csv_item_collection_equals(&this->items, &line->items);
}

