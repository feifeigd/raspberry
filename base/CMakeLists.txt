aux_source_directory( . SRC)
add_library(base ${SRC})
target_link_libraries(base PUBLIC wiringPi)
target_include_directories(base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
