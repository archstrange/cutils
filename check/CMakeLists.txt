aux_source_directory(. CHECK_SRC)
add_executable(check ${CHECK_SRC})
target_link_libraries(check cutils)
