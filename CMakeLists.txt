cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)
project(vagabond2 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11 CACHE STRING "C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
set(glm_path "/home/qms64511/myDevelopments/glm")
set(gemmi_path "/home/qms64511/myDevelopments/gemmi")

add_subdirectory(utils)
add_subdirectory(core)


# The main vagabond executable.
add_executable(vagabond2 ${PROJECT_SOURCE_DIR}/hello.cpp)
target_link_libraries(vagabond2 PRIVATE  libbond libpca libreader)        

#Compilation settings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(vagabond2 PUBLIC -Wall -Wextra -pedantic)
endif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")

if (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    target_compile_options(vagabond2 PUBLIC -Wall -Wextra -pedantic)
    target_compile_options(vagabond2 PUBLIC -xHost)
endif (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
