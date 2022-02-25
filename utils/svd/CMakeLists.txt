set(SVD_SRC
	 ${PROJECT_SOURCE_DIR}/utils/svd/src/matrix.cpp
	 ${PROJECT_SOURCE_DIR}/utils/svd/src/PCA.cpp
	 ${PROJECT_SOURCE_DIR}/utils/svd/src/svdcmp.cpp
)

add_library(libpca STATIC ${SVD_SRC})
set_target_properties(libpca PROPERTIES OUTPUT_NAME pca)
target_include_directories(libpca PUBLIC ${PROJECT_SOURCE_DIR}/utils/svd/include)

include_directories(${PROJECT_SOURCE_DIR}/utils ${glm_path}/install/include/glm)

add_executable(pca_colums_row 
	${PROJECT_SOURCE_DIR}/utils/svd/tests/pca_does_not_allow_fewer_rows_than_columns.cpp)
target_link_libraries(pca_colums_row PRIVATE libpca)

add_executable(pca_glm_same 
	${PROJECT_SOURCE_DIR}/utils/svd/tests/pca_matrix_returns_same_result_as_glm_matrix.cpp)
target_link_libraries(pca_glm_same PRIVATE libpca)

add_test(pca_colums_row_fewer pca_colums_row)
add_test(pca_glm_same_check pca_glm_same)

if (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    target_compile_options(libpca PUBLIC -Wall -Wextra -pedantic)
    target_compile_options(libpca PUBLIC -xHost)
    target_compile_definitions(libpca PRIVATE -DAVX2 -DSSE2)
endif (CMAKE_CXX_COMPILER_ID MATCHES "Intel")

