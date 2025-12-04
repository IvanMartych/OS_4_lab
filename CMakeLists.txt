cmake_minimum_required(VERSION 3.10)
project(OS_Lab4 C)

set(CMAKE_C_STANDARD 11)

# Включаем директорию с заголовочными файлами
include_directories(${CMAKE_SOURCE_DIR}/include)

# Создание динамической библиотеки 1 (наивные алгоритмы)
add_library(math1 SHARED lib1/lib1.c)
set_target_properties(math1 PROPERTIES 
    OUTPUT_NAME "math1"
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Создание динамической библиотеки 2 (оптимизированные алгоритмы)
add_library(math2 SHARED lib2/lib2.c)
set_target_properties(math2 PROPERTIES 
    OUTPUT_NAME "math2"
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Программа 1: Статическая линковка с библиотекой 1
add_executable(program1 program1/main.c)
target_link_libraries(program1 math1)
set_target_properties(program1 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Программа 2: Динамическая загрузка библиотек
add_executable(program2 program2/main.c)
target_link_libraries(program2 ${CMAKE_DL_LIBS})
set_target_properties(program2 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Устанавливаем RPATH для корректного поиска библиотек
set_target_properties(program1 PROPERTIES
    BUILD_RPATH "${CMAKE_BINARY_DIR}"
    INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib"
)

set_target_properties(program2 PROPERTIES
    BUILD_RPATH "${CMAKE_BINARY_DIR}"
    INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib"
)
