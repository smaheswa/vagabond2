
set(READER_SRC
	 ${PROJECT_SOURCE_DIR}/utils/reader/src/FileReader.cpp
)

add_library(libreader STATIC ${READER_SRC})
set_target_properties(libreader PROPERTIES OUTPUT_NAME reader)

include_directories(${PROJECT_SOURCE_DIR}/utils ${glm_path}/install/include/glm)

add_executable(comma_dangling_starts 
	${PROJECT_SOURCE_DIR}/utils/reader/tests/split_by_comma_starts_with_dangling_string.cpp)
add_executable(comma_dangling_leaves 
	${PROJECT_SOURCE_DIR}/utils/reader/tests/split_by_comma_leaves_dangling_strings.cpp)

add_test(comma_dangle_start comma_dangling_starts)
add_test(comma_dangle_leave comma_dangling_leaves)
