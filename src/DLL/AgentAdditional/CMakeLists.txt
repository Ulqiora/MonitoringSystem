cmake_minimum_required(VERSION 3.22)
project("AgentAdditional")
find_package(PkgConfig REQUIRED )
find_package(Boost REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
message("Boost library place : ${Boost_INCLUDE_DIR}")
# pkg_check_modules(BOOST_DLL REQUIRED IMPORTED_TARGET boost_atomic)

add_library(AgentAdditional SHARED src/AgentAdditional.cpp)

target_include_directories( AgentAdditional
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
