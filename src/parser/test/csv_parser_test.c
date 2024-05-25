#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "parser/csv_parser.h"
#include "content/csv_content.h"
#include "csv_parser_test.h"

void csv_parser_test_scenario1(void) {
	const char data[] =
		"title1,title2,title3\n"
		"abc,def,ghi";
	CSV_PROPERTIES props = { .hasHeader = false };
	CSV_PARSER *parser = csv_parser_init(&props);

	CSV_PARSER_STATUS st = csv_parser_load_from_data(parser, data, strlen(data));
	assert(st == CSV_PARSER_SUCCESS);
	const CSV_CONTENT *content = csv_parser_get_content(parser);
	const CSV_LINE_COLLECTION *lines = &content->lines;
	assert(lines->length == 2);
	assert(lines->_list[0].items.length == 3);
	assert(lines->_list[1].items.length == 3);
	CsvContent_Print((CSV_CONTENT *)content);
	csv_parser_destroy(parser);
}

void csv_parser_test_scenario2(void) {
	const char data[] =
		"title1,title2\r\n"
		"data1,data2";
	CSV_PROPERTIES props = { .hasHeader = false };
	CSV_PARSER *parser = csv_parser_init(&props);

	CSV_PARSER_STATUS st = csv_parser_load_from_data(parser, data, strlen(data));
	assert(st == CSV_PARSER_SUCCESS);
	const CSV_CONTENT *content = csv_parser_get_content(parser);
	const CSV_LINE_COLLECTION *lines = &content->lines;
	assert(lines->length == 2);
	assert(lines->_list[0].items.length == 2);
	assert(lines->_list[1].items.length == 2);
	CsvContent_Print((CSV_CONTENT *)content);
	csv_parser_destroy(parser);
}

void csv_parser_test_scenario3(void) {
	const char data[] =
		"title1,title2,title3\n"
		"data1,data2,data3\n"
		"data4";
	CSV_PROPERTIES props = { .hasHeader = false };
	CSV_PARSER *parser = csv_parser_init(&props);

	CSV_PARSER_STATUS st = csv_parser_load_from_data(parser, data, strlen(data));
	assert(st == CSV_PARSER_SUCCESS);
	const CSV_CONTENT *content = csv_parser_get_content(parser);
	const CSV_LINE_COLLECTION *lines = &content->lines;
	assert(lines->length == 3);
	assert(lines->_list[0].items.length == 3);
	assert(lines->_list[1].items.length == 3);
	assert(lines->_list[2].items.length == 1);
	printf("\n");
	csv_parser_destroy(parser);
}

void csv_parser_test_scenario4(void) {
	const char data[] = "";
	CSV_PROPERTIES props = { .hasHeader = false };
	CSV_PARSER *parser = csv_parser_init(&props);

	CSV_PARSER_STATUS st = csv_parser_load_from_data(parser, data, sizeof(data));
	assert(st == CSV_PARSER_SUCCESS);
	const CSV_CONTENT *content = csv_parser_get_content(parser);
	const CSV_LINE_COLLECTION *lines = &content->lines;
	assert(lines->length == 1);
	CsvContent_Print((CSV_CONTENT *)content);
	csv_parser_destroy(parser);
}

void csv_parser_test_scenario5(void) {
	CSV_PROPERTIES props = { .hasHeader = false };
	CSV_PARSER *parser = csv_parser_init(&props);
	CSV_PARSER_STATUS st = csv_parser_load_from_file(parser, "~/c_lang/CsvUtils/src/parser/test/input.csv");
	assert(st == CSV_PARSER_SUCCESS);
	const CSV_CONTENT *content = csv_parser_get_content(parser);
	const CSV_LINE_COLLECTION *lines = &content->lines;
	assert(lines->length == 3);
	assert(lines->_list[0].items.length == 1);
	assert(lines->_list[1].items.length == 2);
	assert(lines->_list[2].items.length == 2);
	CsvContent_Print((CSV_CONTENT *)content);
	csv_parser_destroy(parser);
}

