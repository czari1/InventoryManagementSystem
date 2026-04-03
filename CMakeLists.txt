cmake_minimum_required(VERSION 3.16)
project(InventoryManagementSystem LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

set(LIB_SOURCES
    src/Item.cpp
    src/Electronics.cpp
    src/Grocery.cpp
    src/Inventory.cpp
    src/ItemFactory.cpp
)

add_library(inventory_lib STATIC ${LIB_SOURCES})
target_include_directories(inventory_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(inventory_lib PUBLIC
    PROJECT_DATA_DIR="${PROJECT_SOURCE_DIR}"
)

add_executable(inventory_app src/main.cpp src/UI.cpp)
target_link_libraries(inventory_app PRIVATE inventory_lib)
target_compile_definitions(inventory_app PRIVATE
    PROJECT_DATA_DIR="${PROJECT_SOURCE_DIR}"
)

option(BUILD_TESTS "Build unit tests" OFF)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()