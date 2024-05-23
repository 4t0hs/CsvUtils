#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "CsvParser/CsvParser.h"
#include "CsvContent/CsvContent.h"
#include "TestScenario.h"

static void PrintScenarioTitle(const char *no, const char *input) {
	printf("--------------------------------------------------\n");
	printf("CsvParser Test scenario%s\n", no);
	printf("input:\n%s\n", input);
	printf("--------------------------------------------------\n");
}

void CsvParserTest_Scenario1(void) {
	const char data[] =
		"title1,title2,title3\n"
		"abc,def,ghi";
	PrintScenarioTitle("1", data);
	CsvProperties_t props = { .hasHeader = false };
	CsvParser_t *parser = CsvParser_Init(&props);

	CsvParserStatus st = CsvParser_LoadFromData(parser, data, strlen(data));
	assert(st == CSV_PARSER_SUCCESS);
	const CsvContent_t *content = CsvParser_GetContent(parser);
	const CsvLineCollection_t *lines = &content->lines;
	assert(lines->length == 2);
	assert(lines->_list[0].items.length == 3);
	assert(lines->_list[1].items.length == 3);
	CsvContent_Print((CsvContent_t *)content);
	printf("\n");
	CsvParser_Destroy(parser);
}

void CsvParserTest_Scenario2(void) {
	const char data[] =
		"title1,title2\r\n"
		"data1,data2";
	PrintScenarioTitle("2", data);
	CsvProperties_t props = { .hasHeader = false };
	CsvParser_t *parser = CsvParser_Init(&props);

	CsvParserStatus st = CsvParser_LoadFromData(parser, data, strlen(data));
	assert(st == CSV_PARSER_SUCCESS);
	const CsvContent_t *content = CsvParser_GetContent(parser);
	const CsvLineCollection_t *lines = &content->lines;
	assert(lines->length == 2);
	assert(lines->_list[0].items.length == 2);
	assert(lines->_list[1].items.length == 2);
	CsvContent_Print((CsvContent_t *)content);
	printf("\n");
	CsvParser_Destroy(parser);
}

void CsvParserTest_Scenario3(void) {
	const char data[] =
		"title1,title2,title3\n"
		"data1,data2,data3\n"
		"data4";
	PrintScenarioTitle("3", data);
	CsvProperties_t props = { .hasHeader = false };
	CsvParser_t *parser = CsvParser_Init(&props);

	CsvParserStatus st = CsvParser_LoadFromData(parser, data, strlen(data));
	assert(st == CSV_PARSER_SUCCESS);
	const CsvContent_t *content = CsvParser_GetContent(parser);
	const CsvLineCollection_t *lines = &content->lines;
	assert(lines->length == 3);
	assert(lines->_list[0].items.length == 3);
	assert(lines->_list[1].items.length == 3);
	assert(lines->_list[2].items.length == 1);
	CsvContent_Print((CsvContent_t *)content);
	printf("\n");
	CsvParser_Destroy(parser);
}
// todo: データが空の時lines->lengthが1になってしまうのを修正
void CsvParserTest_Scenario4(void) {
	const char data[] = "";
	PrintScenarioTitle("4", data);
	CsvProperties_t props = { .hasHeader = false };
	CsvParser_t *parser = CsvParser_Init(&props);

	CsvParserStatus st = CsvParser_LoadFromData(parser, data, sizeof(data));
	assert(st == CSV_PARSER_SUCCESS);
	const CsvContent_t *content = CsvParser_GetContent(parser);
	const CsvLineCollection_t *lines = &content->lines;
	assert(lines->length == 0);
	CsvContent_Print((CsvContent_t *)content);
	printf("\n");
	CsvParser_Destroy(parser);
}

