# Inventory Management System

A C++ application that models an inventory management system for a store, demonstrating modern C++ features including OOP, smart pointers, STL containers, templates, exception handling, and CSV file I/O.

---

## Features

- Abstract base class `Item` with derived `Electronics` and `Grocery` classes
- Smart pointer (`std::shared_ptr`) memory management — no raw `new`/`delete`
- STL-based `Inventory` container with move semantics (non-copyable)
- Generic `filterItems` and `sortItems` function templates
- Custom exception hierarchy with strong exception safety guarantees
- CSV file I/O with cross-platform CRLF support
- Interactive menu-driven CLI
- Full Google Test suite (59 tests across 7 task categories)

---

## Project Structure

```
InventoryManagementSystem/
├── include/
│   ├── Algorithms.hpp       # filterItems / sortItems templates
│   ├── Category.hpp         # Category enum (documented reference)
│   ├── Electronics.hpp
│   ├── Exceptions.hpp       # Custom exception hierarchy
│   ├── Grocery.hpp
│   ├── IDisplayable.hpp     # Abstract display interface
│   ├── Inventory.hpp
│   ├── Item.hpp             # Abstract base class
│   ├── ItemFactory.hpp      # makeElectronics / makeGrocery
│   └── UI.hpp
├── src/
│   ├── Electronics.cpp
│   ├── Grocery.cpp
│   ├── Inventory.cpp        # addItem, removeItem, updateQuantity, file I/O
│   ├── Item.cpp
│   ├── ItemFactory.cpp
│   ├── UI.cpp               # Menu-driven CLI
│   └── main.cpp             # Demo + CLI entry point
├── tests/
│   ├── CMakeLists.txt
│   ├── TestHelpers.hpp
│   ├── main_test.cpp
│   ├── test_task1_items.cpp
│   ├── test_task2_inventory.cpp
│   ├── test_task3_smartptrs.cpp
│   ├── test_task4_algorithms.cpp
│   ├── test_task5_exceptions.cpp
│   └── test_task6_fileio.cpp
├── CMakeLists.txt
└── README.md
```

---

## Requirements

- C++17 compliant compiler (GCC, Clang, MSVC)
- CMake ≥ 3.16
- Google Test (optional, for running tests)

---

## Build

### Application only

```bash
cmake -B build
cmake --build build
./build/inventory_app
```

### With tests

```bash
cmake -B build -DBUILD_TESTS=ON
cmake --build build
./build/tests/inventory_tests
```

### Run a specific test group

```bash
./build/tests/inventory_tests --gtest_filter="FileIOTest.*"
```

---

## CSV File Format

One item per line:

```
itemID,category,name,quantity,price,extra
```

Where `extra` is `warrantyMonths` for Electronics or `expirationDate` for Grocery.

**Example (`inventory.csv`):**

```
E1,Electronics,Phone,10,699.99,24
E2,Electronics,Laptop,5,1099.99,12
G1,Grocery,Apple,100,0.99,2026-06-01
G2,Grocery,Milk,30,1.49,2026-04-10
```

---

## Expected Output

```
[Electronics] ID: E1 | Name: Phone | Qty: 10 | Price: 699.99 | Warranty: 24 months
[Electronics] ID: E2 | Name: Laptop | Qty: 5 | Price: 1099.99 | Warranty: 12 months
[Grocery] ID: G1 | Name: Apple | Qty: 100 | Price: 0.99 | Expires: 2026-06-01
[Grocery] ID: G2 | Name: Milk | Qty: 30 | Price: 1.49 | Expires: 2026-04-10
```

---

## CLI Menu

```
 1. Add Electronics
 2. Add Grocery
 3. Remove Item
 4. Update Quantity
 5. Display Inventory
 6. Read from File
 7. Write to File
 8. Find Most Expensive Item
 9. Find Items Below Quantity Threshold
10. Sort by Price
11. Exit
```

All user actions are wrapped in `try/catch` — errors are printed clearly without crashing the application.

---

## Exception Hierarchy

```
std::runtime_error
└── InventoryException
    ├── ItemNotFoundException     — item ID not found
    ├── DuplicateItemException    — item ID already exists
    └── InvalidValueException     — negative price or quantity
```

---

## Design Notes

- `Inventory` is **movable but non-copyable** (`= delete` on copy constructor and copy assignment)
- All file reads use a **staging buffer** — the inventory is only replaced after a fully successful parse (strong exception safety)
- `PROJECT_DATA_DIR` is injected via CMake `target_compile_definitions` with a `#ifndef` fallback for cross-context builds
- CSV parser handles Windows `\r\n` line endings explicitly
- `constexpr` constants `MIN_QUANTITY` and `MIN_PRICE` are used for validation thresholds

---
