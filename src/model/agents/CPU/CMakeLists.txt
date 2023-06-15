cmake_minimum_required(VERSION 3.22.1)
project(AgentCPU VERSION 1.0 LANGUAGES CXX)

set(SOURCE_LIB CpuAgentMacOS.cc)
add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB})
target_include_directories(${PROJECT_NAME}
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )
target_link_libraries(${PROJECT_NAME} tutorial_compiler_flags)