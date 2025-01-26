cmake_minimum_required(VERSION 3.31)
project(Alloy VERSION 0.0.3)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILER gcc)
configure_file(
	info.h.in
	info.h
)

add_executable(alloy
	src/main.c
	src/error/messages.c
	src/codeParsing/execTree.c
	src/codeParsing/parser.c
	src/codeParsing/lexer.c
)

target_compile_options(alloy PUBLIC -static)
target_compile_options(alloy PUBLIC -Wall)
target_compile_options(alloy PUBLIC -Werror)
# target_compile_options(alloy PUBLIC -fsanitize=address)

target_include_directories(
	alloy
	PUBLIC
	${CMAKE_BINARY_DIR}
)


