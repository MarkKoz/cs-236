cmake_minimum_required(VERSION 3.10)
project(cs_236_06)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME}
    src/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC
    include)

list(APPEND FLAGS_WARN
    -Wall
    -Wcast-align
    -Wconversion
    -Wextra
    -Wfloat-equal
    -Wlogical-op
    -Wmissing-declarations
    -Woverloaded-virtual
    -Wpedantic
    -Wredundant-decls
    -Wshadow
    -Wundef)
list(APPEND FLAGS_DEBUG
    ${FLAGS_WARN}
    -g3
    -ggdb)
list(APPEND FLAGS_RELEASE
    ${FLAGS_WARN}
    -DNDEBUG
    -o2)

target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:DEBUG>:${FLAGS_DEBUG}>")
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:RELEASE>:${FLAGS_RELEASE}>")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME output)
