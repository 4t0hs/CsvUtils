set(SOURCES_MINUS_MAIN ${SOURCES})
list(REMOVE_ITEM SOURCES_MINUS_MAIN ${SOURCE_DIR}/main.c)

set(CSV_INLCUDE ${PROJECT_HOME}/)

add_subdirectory(parser)
