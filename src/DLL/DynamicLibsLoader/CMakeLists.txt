cmake_minimum_required(VERSION 3.22)
project(DynamicLibraryLoader)

file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DynamicLibraryLoader.cpp
)
file(GLOB HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)
set (CMAKE_CXX_STANDARD 20)
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(${PROJECT_NAME} PRIVATE
        ${Boost_LIBRARIES}
)