cmake_minimum_required(VERSION 3.22.1)
project(NetworkAgent VERSION 1.0 LANGUAGES CXX)

if(UNIX AND NOT APPLE)
set(SOURCE_LIB_NETWORK NetworkAgentLinux.cc)
else()
set(SOURCE_LIB_NETWORK NetworkAgentMacOS.cc)
endif()
add_library(${PROJECT_NAME} MODULE ${SOURCE_LIB_NETWORK})
target_include_directories(${PROJECT_NAME}
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )
target_link_libraries(${PROJECT_NAME} tutorial_compiler_flags)