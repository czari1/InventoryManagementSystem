#pragma once

#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <iostream>

#include "Item.hpp"
#include "Electronics.hpp"
#include "Grocery.hpp"
#include "Inventory.hpp"
#include "ItemFactory.hpp"
#include "Algorithms.hpp"
#include "Exceptions.hpp"

using namespace inventory;

// ---- Factory helpers ----

inline std::shared_ptr<Item> makePhone() {
    return makeElectronics("E1", "Phone", 10, 699.99, 24);
}
inline std::shared_ptr<Item> makeLaptop() {
    return makeElectronics("E2", "Laptop", 5, 1099.99, 12);
}
inline std::shared_ptr<Item> makeApple() {
    return makeGrocery("G1", "Apple", 100, 0.99, "2026-06-01");
}
inline std::shared_ptr<Item> makeMilk() {
    return makeGrocery("G2", "Milk", 30, 1.49, "2026-04-10");
}

// ---- stdout capture helpers ----

inline std::string captureDisplay(const std::shared_ptr<Item>& item) {
    std::ostringstream buf;
    std::streambuf* old = std::cout.rdbuf(buf.rdbuf());
    item->display();
    std::cout.rdbuf(old);
    return buf.str();
}

inline std::string captureInventoryDisplay(const Inventory& inv) {
    std::ostringstream buf;
    std::streambuf* old = std::cout.rdbuf(buf.rdbuf());
    inv.displayInventory();
    std::cout.rdbuf(old);
    return buf.str();
}