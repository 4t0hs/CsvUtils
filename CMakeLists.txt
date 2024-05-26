cmake_minimum_required(VERSION 3.2)
project(csv_utilities CXX C)

#
# Download GoogleTest
#
include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

#
# definition common variables
#
set(PROJECT_HOME ${PROJECT_SOURCE_DIR})
set(SOURCE_DIR ${PROJECT_HOME}/lib)
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.c)

message(STATUS "Project home: " ${PROJECT_HOME})
message(STATUS "Source directory: " ${SOURCE_DIR})
message(STATUS "C source files: " ${SOURCES})

# compile options
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

# libraries
set(LIBS
)
set(DEBUG_LIBS
	asan
)

#
# sub directories
#
add_subdirectory(lib)
add_subdirectory(tests)
