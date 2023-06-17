cmake_minimum_required(VERSION 3.22.1)
project(AgentCPU VERSION 1.0 LANGUAGES CXX)

if(UNIX)
    set(SOURCE_LIB CpuAgentLinux.cc)
else()
    set(SOURCE_LIB CpuAgentMacOS.cc)
endif()
add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB})
target_include_directories(${PROJECT_NAME}
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )
target_link_libraries(${PROJECT_NAME} tutorial_compiler_flags)