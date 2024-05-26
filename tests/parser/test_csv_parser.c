#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "include/parser/csv_parser.h"
#include "include/content/csv_content.h"

static void assert_content(CSV_CONTENT *expected, CSV_CONTENT *actual) {
	assert(expected->lines.length == actual->lines.length);
	for (size_t i = 0; i < expected->lines.length; i++) {
		CSV_LINE *expected_line = &expected->lines._list[i];
		CSV_LINE *actual_line = &actual->lines._list[i];
		assert(expected_line->items.length == actual_line->items.length);
		for (size_t j = 0; j < expected_line->items.length; j++) {
			CSV_ITEM *expected_item = &expected_line->items._list[j];
			CSV_ITEM *actual_item = &actual_line->items._list[j];
			assert(strcmp(expected_item->text, actual_item->text) == 0);
		}
	}
}
#define num_of_table(table) (sizeof(table)/sizeof(table[0]))

int csv_parser_test_scenario1(void) {
	const char data[] =
		"title1,title2,title3\n"
		"abc,def,ghi";
	CSV_ITEM items0[] = { {"title1"}, {"title2"}, {"title3"}, };
	CSV_ITEM items1[] = { {"abc"}, {"def"}, {"ghi"}, };
	CSV_LINE lines[] = {
		[0] = {.items = {._list = items0, .length = num_of_table(items0)}},
		[1] = {.items = {._list = items1, .length = num_of_table(items1)}},
	};
	CSV_CONTENT content = { {._list = lines, .length = num_of_table(lines)} };

	CSV_PROPERTIES props = { .has_header = false };
	CSV_PARSER *parser = csv_parser_init(&props);
	assert(csv_parser_load_from_data(parser, data, strlen(data)) == CSV_PARSER_SUCCESS);
	assert_content(&content, (CSV_CONTENT *)csv_parser_get_content(parser));
	csv_parser_destroy(parser);
	return 0;
}

void csv_parser_test_scenario2(void) {
	const char data[] =
		"title1,title2\r\n"
		"data1,data2";
	CSV_ITEM items0[] = { {"title1"}, {"title2"} };
	CSV_ITEM items1[] = { {"data1"}, {"data2"} };
	CSV_LINE lines[] = {
		[0] = {.items = {._list = items0, .length = num_of_table(items0)}},
		[1] = {.items = {._list = items1, .length = num_of_table(items1)}},
	};
	CSV_CONTENT content = { {._list = lines, .length = num_of_table(lines)} };
	CSV_PROPERTIES props = { .has_header = false };
	CSV_PARSER *parser = csv_parser_init(&props);

	assert(csv_parser_load_from_data(parser, data, strlen(data)) == CSV_PARSER_SUCCESS);
	assert_content(&content, (CSV_CONTENT *)csv_parser_get_content(parser));
	csv_parser_destroy(parser);
}

void csv_parser_test_scenario3(void) {
	const char data[] =
		"title1,title2,title3\n"
		"data1";
	CSV_ITEM items0[] = { {"title1"}, {"title2"}, {"title3"} };
	CSV_ITEM items1[] = { {"data1"} };
	CSV_LINE lines[] = {
		[0] = {{._list = items0, .length = num_of_table(items0)}},
		[1] = {{._list = items1, .length = num_of_table(items1)}},
	};
	CSV_CONTENT content = { {._list = lines, .length = num_of_table(lines)} };

	CSV_PROPERTIES props = { .has_header = false };
	CSV_PARSER *parser = csv_parser_init(&props);

	assert(csv_parser_load_from_data(parser, data, strlen(data)) == CSV_PARSER_SUCCESS);
	assert_content(&content, (CSV_CONTENT *)csv_parser_get_content(parser));
	csv_parser_destroy(parser);
}

void csv_parser_test_scenario4(void) {
	const char data[] = "";
	CSV_ITEM items[] = { {""} };
	CSV_LINE lines[] = {
		[0] = {{._list = items, .length = num_of_table(items)}}
	};
	CSV_CONTENT content = { {._list = lines, .length = num_of_table(lines)} };

	CSV_PROPERTIES props = { .has_header = false };
	CSV_PARSER *parser = csv_parser_init(&props);

	assert(csv_parser_load_from_data(parser, data, sizeof(data)) == CSV_PARSER_SUCCESS);
	assert_content(&content, (CSV_CONTENT *)csv_parser_get_content(parser));
	csv_parser_destroy(parser);
}

void csv_parser_test_scenario5(void) {
	CSV_ITEM items0[] = { {"scenario5"} };
	CSV_ITEM items1[] = { {"title1"}, {"title2"} };
	CSV_ITEM items2[] = { {"data1"}, {"data2"} };
	CSV_LINE lines[] = {
		[0] = {{._list = items0, .length = num_of_table(items0)}},
		[1] = {{._list = items1, .length = num_of_table(items1)}},
		[2] = {{._list = items2, .length = num_of_table(items2)}},
	};
	CSV_CONTENT content = { {._list = lines, .length = num_of_table(lines)} };
	CSV_PROPERTIES props = { .has_header = false };
	CSV_PARSER *parser = csv_parser_init(&props);
	assert(csv_parser_load_from_file(parser, "/home/atohs/c_lang/CsvUtils/tests/parser/input.csv") == CSV_PARSER_SUCCESS);
	assert_content(&content, (CSV_CONTENT *)csv_parser_get_content(parser));
	csv_parser_destroy(parser);
}
