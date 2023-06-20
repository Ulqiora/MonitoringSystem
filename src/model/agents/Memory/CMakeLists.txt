cmake_minimum_required(VERSION 3.22.1)
project(MemoryAgent VERSION 1.0 LANGUAGES CXX)

if(UNIX AND NOT APPLE)
set(SOURCE_LIB_MEMORY MemoryAgentLinux.cc)
else()
set(SOURCE_LIB_MEMORY MemoryAgentMacOS.cc)
endif()
add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB_MEMORY})
target_include_directories(${PROJECT_NAME}
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )
target_link_libraries(${PROJECT_NAME} tutorial_compiler_flags)