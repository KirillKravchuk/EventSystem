# Исходные файлы
set(SRC_FILES
    src/main.cpp
    src/CommandHandler.cpp
    src/DataBase.cpp
    src/EventGenerator.cpp
    src/EventQueue.cpp
    src/Logger.cpp
    src/LoggerLevel0.cpp
    src/LoggerLevel1.cpp
    src/LoggerLevel2.cpp
    src/LoggerThread.cpp
    src/utils.cpp
)

add_executable(EventSystem)
target_sources(EventSystem PRIVATE ${SRC_FILES})

add_library(sqlite3 STATIC "${CMAKE_CURRENT_SOURCE_DIR}/SQLite/sqlite3.c")
set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/SQLite/sqlite3.c" PROPERTIES LANGUAGE C)

target_include_directories(EventSystem PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
    ${CMAKE_CURRENT_SOURCE_DIR}/SQLite
)
target_include_directories(sqlite3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SQLite)

target_link_libraries(EventSystem PRIVATE sqlite3)

if(UNIX)
    target_link_libraries(EventSystem PRIVATE pthread)
endif()

if(WIN32)
    target_compile_definitions(EventSystem PRIVATE _CRT_SECURE_NO_WARNINGS NOMINMAX)
    target_compile_definitions(sqlite3 PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

if(MSVC)
    target_compile_options(EventSystem PRIVATE /W4 /permissive-)
    set_target_properties(EventSystem PROPERTIES
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    )
else()
    target_compile_options(EventSystem PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(EventSystem PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(sqlite3 PROPERTIES POSITION_INDEPENDENT_CODE ON)

set_target_properties(EventSystem PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(sqlite3 PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)