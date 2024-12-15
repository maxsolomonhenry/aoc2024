add_executable(day01 day01.cpp)
target_include_directories(day01 PUBLIC ../common)
target_link_libraries(day01 util)