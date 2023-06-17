cmake_minimum_required(VERSION 3.22.1)
project(AgentMemory VERSION 1.0 LANGUAGES CXX)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(SOURCE_LIB_MEMORY MemoryAgentMacOS.cc)
else()
    set(SOURCE_LIB_MEMORY MemoryAgentLinux.cc)
endif()
add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB_MEMORY})
target_include_directories(${PROJECT_NAME}
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )
target_link_libraries(${PROJECT_NAME} tutorial_compiler_flags)