cmake_minimum_required(VERSION 3.22)
project("AgentCPU")
find_package(PkgConfig REQUIRED )
find_package(Boost REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
message("Boost library place : ${Boost_INCLUDE_DIR}")
# pkg_check_modules(BOOST_DLL REQUIRED IMPORTED_TARGET boost_atomic)

add_library(AgentCPU SHARED src/AgentCPU.cpp)

target_include_directories( AgentCPU
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_CURRENT_SOURCE_DIR}/..
            ${Boost_LIBRARIES}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

#target_link_libraries(AgentCPU PRIVATE
#    ${Boost_LIBRARIES} )
