cmake_minimum_required(VERSION 3.22.1)	 # Проверка версии CMake.
										# Если версия установленой программы
										# старее указаной, произайдёт аварийный выход.


project(myapp VERSION 1.0 LANGUAGES CXX)				# Название проекта

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
set(SOURCE_EXE main.cc)			# Установка переменной со списком исходников
add_executable(main ${SOURCE_EXE})	# Создает исполняемый файл с именем main
set (CMAKE_CXX_STANDARD 17)
add_library(tutorial_compiler_flags INTERFACE)
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_17)
target_compile_options(tutorial_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:-Wall;-g;-Wextra;-Wshadow;-Wformat=2;-Wunused>"
  "$<${msvc_cxx}:-W3>"
)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs)
execute_process(
    COMMAND git clone "https://github.com/nlohmann/json" json
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs)
add_subdirectory(libs/json)
list(APPEND EXTRA_LIBS nlohmann_json)
target_link_libraries(main PRIVATE ${EXTRA_LIBS})

add_subdirectory(model/AgentReportF)
list(APPEND EXTRA_LIBS TreeStructure)
target_link_libraries(main PRIVATE ${EXTRA_LIBS} tutorial_compiler_flags)


add_subdirectory(model/Agents/CPU)
list(APPEND EXTRA_LIBS CpuAgent)
target_link_libraries(main PRIVATE ${EXTRA_LIBS} tutorial_compiler_flags)


add_subdirectory(model/Agents/Memory)
list(APPEND EXTRA_LIBS MemoryAgent)
target_link_libraries(main PRIVATE ${EXTRA_LIBS} tutorial_compiler_flags)