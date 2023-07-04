cmake_minimum_required(VERSION 3.22.1)
project(SystemAgent VERSION 1.0 LANGUAGES CXX)

if(UNIX AND NOT APPLE)
set(SOURCE_LIB_SYSTEM SystemAgentLinux.cc)
else()
set(SOURCE_LIB_SYSTEM SystemAgentMacOS.cc)
endif()
add_library(${PROJECT_NAME} MODULE ${SOURCE_LIB_SYSTEM})
target_include_directories(${PROJECT_NAME}
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )
target_link_libraries(${PROJECT_NAME} tutorial_compiler_flags)