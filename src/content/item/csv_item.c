#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "content/item/csv_item.h"

#define CLEAR(this)	(memset(this, 0, sizeof(CSV_ITEM)))

void csv_item_init(CSV_ITEM *this) {
	CLEAR(this);
}

void csv_item_set(CSV_ITEM *this, char *value) {
	this->text = value;
}

void csv_item_move_owner(CSV_ITEM *this, CSV_ITEM *new_owner) {
	*new_owner = *this;
	this->text = NULL;
}

void csv_item_destroy(CSV_ITEM *this) {
	CLEAR(this);
}

void csv_item_print(CSV_ITEM *this) {
	printf("%s", this->text);
}

bool csv_item_equals(CSV_ITEM *this, CSV_ITEM *item) {
	return strcmp(this->text, item->text) ? false : true;
}
