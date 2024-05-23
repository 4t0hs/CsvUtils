#pragma once

#include <stdlib.h>
#include "CsvProperties/CsvProperties.h"
#include "CsvContent/CsvContent.h"

struct CsvParser;
typedef struct CsvParser CsvParser_t;

typedef enum CsvParserStatus {
	CSV_PARSER_SUCCESS = 0,
	CSV_PARSER_INVALID_PARAMETER,
} CsvParserStatus;

extern CsvParser_t *CsvParser_Init(const CsvProperties_t *props);
extern CsvParserStatus CsvParser_LoadFromFile(CsvParser_t *this, const char *filePath);
extern CsvParserStatus CsvParser_LoadFromData(CsvParser_t *this, const char *data, size_t dataSize);
extern const CsvContent_t *CsvParser_GetContent(CsvParser_t *this);
extern void CsvParser_Destroy(CsvParser_t *this);
