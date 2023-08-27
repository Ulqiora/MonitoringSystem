# cmake_minimum_required(VERSION 3.22)
# project("AgentCPU")
find_package(PkgConfig REQUIRED)
find_package(Boost REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
message("Boost library place : ${Boost_INCLUDE_DIR}")
# pkg_check_modules(BOOST_DLL REQUIRED IMPORTED_TARGET boost_atomic)

add_library(AgentCPU SHARED AgentCPU.cpp)
target_include_directories(AgentCPU PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(AgentCPU PRIVATE
    ${Boost_LIBRARIES} )
