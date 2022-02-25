set(SVD_SRC
	 ${PROJECT_SOURCE_DIR}/utils/svd/src/matrix.cpp
	 ${PROJECT_SOURCE_DIR}/utils/svd/src/PCA.cpp
	 ${PROJECT_SOURCE_DIR}/utils/svd/src/svdcmp.cpp
)

add_library(libpca STATIC ${SVD_SRC})
set_target_properties(libpca PROPERTIES OUTPUT_NAME pca)
target_include_directories(libpca PUBLIC ${PROJECT_SOURCE_DIR}/utils/svd/include)

if (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    target_compile_options(libpca PUBLIC -Wall -Wextra -pedantic)
    target_compile_options(libpca PUBLIC -xHost)
    target_compile_definitions(libpca PRIVATE -DAVX2 -DSSE2)
endif (CMAKE_CXX_COMPILER_ID MATCHES "Intel")

