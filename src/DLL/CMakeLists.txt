
add_subdirectory(DynamicLibsLoader)
add_subdirectory(AgentCPU)
target_include_directories(
        DynamicLibraryLoader
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)