cmake_minimum_required(VERSION 3.10)
# project
project(test C)
# home directory 
set(PROJECT_HOME ${PROJECT_SOURCE_DIR})
# target name 
set(TARGET_NAME CsvUtils.exe)
# source directory 
set(SOURCE_DIR ${PROJECT_HOME}/src)

message(STATUS "Project home: " ${PROJECT_HOME})
message(STATUS "Source directory: " ${SOURCE_DIR})

# Definition compile options
set(NODEBUG_OPT
	-O2
)
Set(DEBUG_OPT 
	-g3
	-ggdb
	-O0
	-fsanitize=address
)
set(WARNING_OPT
	-Wall
	-Wextra
	-Wno-unused-variable
	-Wno-unused-function
)
# Definition libraries
set(LIBS
)
set(DEBUG_LIBS
	asan
)

# build target
add_executable(${TARGET_NAME} ${SOURCE_DIR}/main.c) 
# set features
target_compile_features(${TARGET_NAME} PUBLIC c_std_17)
# set options
target_compile_options(${TARGET_NAME} PRIVATE
	${WARNING_OPT}
	$<$<CONFIG:Debug>:${DEBUG_OPT}>
	$<$<CONFIG:Release>:${NODEBUG_OPT}>
)

# find cpp files
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.c)
message(STATUS "C files: " ${SOURCES})
# add cpp files
target_sources(${TARGET_NAME} PRIVATE ${SOURCES})
# add header directories 
target_include_directories(${TARGET_NAME} PRIVATE
	${SOURCE_DIR}/
)
# link libraries
target_link_libraries(${TARGET_NAME} PRIVATE
	$<$<CONFIG:Debug>:${DEBUG_LIBS}>
)

# definition preprocessor
# target_compile_definitions(${TARGET_NAME} PRIVATE 
# 	_GLIBCXX_USE_CXX11_ABI=1
# )
