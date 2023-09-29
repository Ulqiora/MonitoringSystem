
add_subdirectory(DynamicLibsLoader)
add_subdirectory(AgentCPU)
add_subdirectory(PrinterAgentInfo)
target_include_directories(
        DynamicLibraryLoader
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_include_directories(
        PrinterAgentInfo
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)