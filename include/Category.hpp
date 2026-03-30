#pragma once

#include <string_view>
#include <string>
#include "Exceptions.hpp"

namespace inventory {

    /*
    Class for easier development of the project but not used due to 
    requirements of using std::string as return type in Item, Electronics 
    and Grocery classes for category() method
     */
    
    enum class Category {
        Electronics,
        Grocery
    };

    [[nodiscard]] constexpr std::string_view categoryToString(Category category) {
        
        switch (category) {
            case Category::Electronics: return "Electronics";
            case Category::Grocery: return "Grocery";
        
        }
    }

    [[nodiscard]] inline Category categoryFromString(std::string_view string) {
        
        if (string == "Electronics") return Category::Electronics;
        if (string == "Grocery") return Category::Grocery;
        
        throw InventoryException("Unknown category: '" + std::string(string) + "'");
    }
}