cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)
project(vagabond2 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11 CACHE STRING "C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(core)


#include the GLM directory - i have built it from source and install
#directory has a CMakeConfig file which can also be used - try later
include_directories(/home/qms64511/myDevelopments/glm/install/include/glm)
# The main vagabond executable.
add_executable(vagabond2 ${PROJECT_SOURCE_DIR}/hello.cpp)


target_link_libraries(vagabond2 PRIVATE  libbond)        

#Compilation settings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(vagabond2 PUBLIC -Wall -Wextra -pedantic)
endif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")

if (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    target_compile_options(vagabond2 PUBLIC -Wall -Wextra -pedantic)
    target_compile_options(vagabond2 PUBLIC -xHost)
endif (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
