aux_source_directory(. SRC)
aux_source_directory(./Vector SRC)
aux_source_directory(./Queue SRC)
aux_source_directory(./List SRC)
aux_source_directory(./Dict SRC)
aux_source_directory(./fs SRC)
aux_source_directory(./codec SRC)

add_library(cutils ${SRC})
