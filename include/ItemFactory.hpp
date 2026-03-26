#pragma once

#include "Item.hpp"
#include <memory>
#include <string>

namespace inventory {

    [[nodiscard]] std::shared_ptr<Item> 
    makeElectronics(const std::string& id, const std::string& name,
                    int qty, double price, int warrantyMonths);
    [[nodiscard]] std::shared_ptr<Item> 
    makeGrocery(const std::string& id, const std::string& name,
                    int qty, double price, const std::string& expDate);
}