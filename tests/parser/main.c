#include <stdio.h>
#include "test_csv_parser.h"
int main(void) {
	printf("Start csv parser test\n");
	test_csv_parser_scenario1();
	printf("Successful scenario1\n");
	test_csv_parser_scenario2();
	printf("Successful scenario2\n");
	test_csv_parser_scenario3();
	printf("Successful scenario3\n");
	test_csv_parser_scenario4();
	printf("Successful scenario4\n");
	test_csv_parser_scenario5();
	printf("Successful scenario5\n");
	test_csv_parser_scenario6();
	printf("Successful scenario6\n");
	return 0;
}


