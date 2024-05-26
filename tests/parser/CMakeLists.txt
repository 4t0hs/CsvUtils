enable_testing()
set(TEST_TARGET_NAME TestCsvParser)

file(GLOB_RECURSE TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
set(TEST_INCLUDE_PATH ${PROJECT_HOME}/include)

add_executable(${TEST_TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.c)
target_compile_features(${TEST_TARGET_NAME} PUBLIC c_std_17)

target_sources(${TEST_TARGET_NAME} PRIVATE
	${TEST_SOURCES}
)
target_include_directories(${TEST_TARGET_NAME} PRIVATE
	${CSVUTILS_INLCUDE}
	${TEST_INCLUDE_PATH}
	${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_directories(${TEST_TARGET_NAME} PRIVATE
	${PROJECT_HOME}/build/lib
)
target_link_libraries(${TEST_TARGET_NAME}
	CsvUtils
	gcov
	${LIBS}
	${DEBUG_LIBS}
)

target_compile_options(${TEST_TARGET_NAME} PRIVATE
	-fprofile-arcs
	-ftest-coverage
	${WARNING_OPT}
	$<$<CONFIG:Debug>:${DEBUG_OPT}>
	$<$<CONFIG:Release>:${NODEBUG_OPT}>
)
