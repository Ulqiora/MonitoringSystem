cmake_minimum_required(VERSION 3.22)
project("EmailPrinter")
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
message("Boost library place : ${Boost_INCLUDE_DIR}")
# pkg_check_modules(BOOST_DLL REQUIRED IMPORTED_TARGET boost_atomic)
find_package(CURL REQUIRED)

file(GLOB SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
file(GLOB HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

add_library(EmailPrinter STATIC ${HEADERS} ${SOURCES})
target_link_libraries(EmailPrinter
        PUBLIC
        Net
        NetSSL
        ${CURL_LIBRARIES}
#        Poco
)
target_include_directories( EmailPrinter
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
