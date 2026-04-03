cmake_minimum_required(VERSION 3.16)

find_package(GTest REQUIRED)

add_executable(inventory_tests
    main_test.cpp
    test_task1_items.cpp
    test_task2_inventory.cpp
    test_task3_smartptrs.cpp
    test_task4_algorithms.cpp
    test_task5_exceptions.cpp
    test_task6_fileio.cpp
)

target_include_directories(inventory_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(inventory_tests PRIVATE inventory_lib GTest::GTest)
target_compile_definitions(inventory_tests PRIVATE
    PROJECT_DATA_DIR="${PROJECT_SOURCE_DIR}"
)

enable_testing()
add_test(NAME InventoryTests COMMAND inventory_tests)