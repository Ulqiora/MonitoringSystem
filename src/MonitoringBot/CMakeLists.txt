cmake_minimum_required(VERSION 3.22)
project("MonitoringBot")
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
message("Boost library place : ${Boost_INCLUDE_DIR}")
# pkg_check_modules(BOOST_DLL REQUIRED IMPORTED_TARGET boost_atomic)

file(GLOB SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
file(GLOB HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

add_library(MonitoringBot STATIC ${HEADERS} ${SOURCES})
target_link_libraries(MonitoringBot
        PUBLIC
        TgBot
)
target_include_directories( MonitoringBot
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
