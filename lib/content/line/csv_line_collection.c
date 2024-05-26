#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "content/line/csv_line_collection.h"

#define INITIAL_CAPACITY	(32)
#define CLEAR(this)			(memset(this, 0, sizeof(CSV_LINE_COLLECTION)))

static inline bool need_resize(CSV_LINE_COLLECTION *this) {
	return this->length >= this->capacity;
}
void csv_line_collection_init(CSV_LINE_COLLECTION *this) {
	this->capacity = INITIAL_CAPACITY;
	this->_list = calloc(this->capacity, sizeof(CSV_LINE));
	this->length = 0;
}

void csv_line_collection_resize(CSV_LINE_COLLECTION *this, size_t new_capacity) {
	this->_list = realloc(this->_list, new_capacity * sizeof(CSV_LINE));
	this->capacity = new_capacity;
}

void csv_line_collection_move_and_add(CSV_LINE_COLLECTION *this, CSV_LINE *move_line) {
	if (need_resize(this)) {
		csv_line_collection_resize(this, this->capacity * 2);
	}
	csv_line_move_owner(move_line, &this->_list[this->length++]);
}

void csv_line_collection_destroy(CSV_LINE_COLLECTION *this) {
	for (size_t i = 0; i < this->length; i++) {
		CSV_LINE *line = &this->_list[i];
		csv_line_destroy(line);
	}
	free(this->_list);
}

void csv_line_collection_print(CSV_LINE_COLLECTION *this) {
	for (size_t i = 0; i < this->length; i++) {
		CSV_LINE *line = &this->_list[i];
		csv_line_print(line);
		printf("\n");
	}
}

bool csv_line_collection_equals(CSV_LINE_COLLECTION *this, CSV_LINE_COLLECTION *lines) {
	if (this->length != lines->length) {
		return false;
	}
	for (size_t i = 0; i < this->length; i++) {
		CSV_LINE *line1 = &this->_list[i];
		CSV_LINE *line2 = &lines->_list[i];
		if (!csv_line_equals(line1, line2)) {
			return false;
		}
	}
	return true;
}

