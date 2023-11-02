find_package(Boost REQUIRED COMPONENTS filesystem)
set(SOURCE_EXE main.cc)
add_subdirectory(DLL)
#add_subdirectory(MonitoringBot)
#add_subdirectory(EmailPrinter)

add_executable(myapp ${SOURCE_EXE})	# Создает исполняемый файл с именем main
set (CMAKE_CXX_STANDARD 20)
#target_include_directories(myapp
#        PRIVATE
#        ${Boost_INCLUDE_DIRS})
target_link_libraries(myapp PRIVATE
#    ${Boost_LIBRARIES}
        DynamicLibraryLoader
#        MonitoringBot
#        EmailPrinter
)
