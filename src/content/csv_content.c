#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "content/csv_content.h"
#include "content/line/csv_line_collection.h"

#define CLEAR(this) (memset(this, 0, sizeof(CSV_CONTENT)));

void CsvContent_Init(CSV_CONTENT *this) {
	CLEAR(this);
	csv_line_collection_init(&this->lines);
}

void CsvContent_MoveBackLine(CSV_CONTENT *this, CSV_LINE *line) {
	csv_line_collection_move_and_add(&this->lines, line);
}

void CsvContent_Destroy(CSV_CONTENT *this) {
	csv_line_collection_destroy(&this->lines);
	CLEAR(this);
}

void CsvContent_Print(CSV_CONTENT *this) {
	printf("Csv contents\n");
	csv_line_collection_print(&this->lines);
}

bool CsvContent_Equals(CSV_CONTENT *this, CSV_CONTENT *content) {
	return csv_line_collection_equals(&this->lines, &content->lines);
}
