#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "content/item/csv_item.h"
#include "content/item/csv_item_collection.h"

#define INITIALIZE_CAPACITY	(32)
#define CLEAR(this)			(memset(this, 0, sizeof(CSV_ITEM_COLLECTION)));

static inline bool need_resize(CSV_ITEM_COLLECTION *this) {
	return this->length >= this->capacity;
}

void csv_item_collection_init(CSV_ITEM_COLLECTION *this) {
	CLEAR(this);
	this->capacity = INITIALIZE_CAPACITY;
	this->_list = calloc(this->capacity, sizeof(CSV_ITEM));
	this->length = 0;
}

void csv_item_collection_resize(CSV_ITEM_COLLECTION *this, size_t new_capacity) {
	this->_list = realloc(this->_list, new_capacity * sizeof(CSV_ITEM));
	this->capacity = new_capacity;
}

void csv_item_collection_move_owner(CSV_ITEM_COLLECTION *this, CSV_ITEM_COLLECTION *new_owner) {
	*new_owner = *this;
	CLEAR(this);
}

void csv_item_collection_move_and_add(CSV_ITEM_COLLECTION *this, CSV_ITEM *item) {
	if (need_resize(this)) {
		csv_item_collection_resize(this, this->capacity * 2);
	}
	csv_item_move_owner(item, &this->_list[this->length++]);
}

void csv_item_collection_destroy(CSV_ITEM_COLLECTION *this) {
	for (size_t i = 0; i < this->length; i++) {
		CSV_ITEM *item = &this->_list[i];
		csv_item_destroy(item);
	}
	free(this->_list);
}

void csv_item_collection_clear(CSV_ITEM_COLLECTION *this) {
	CLEAR(this);
}

void csv_item_collection_print(CSV_ITEM_COLLECTION *this) {
	for (size_t i = 0; i < this->length; i++) {
		CSV_ITEM *item = &this->_list[i];
		csv_item_print(item);
		printf(", ");
	}
}

bool csv_item_collection_equals(CSV_ITEM_COLLECTION *this, CSV_ITEM_COLLECTION *items) {
	if (this->length != items->length) {
		return false;
	}

	for (size_t i = 0; i < this->length; i++) {
		CSV_ITEM *item1 = &this->_list[i];
		CSV_ITEM *item2 = &items->_list[i];
		if (!csv_item_equals(item1, item2)) {
			return false;
		}
	}
	return true;
}
