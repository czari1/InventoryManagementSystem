#pragma once

#include "Inventory.hpp"
#include <algorithm>
#include <vector>
#include <memory>

namespace inventory {
    
    template<typename Predicate>
    [[nodiscard]] std::vector<std::shared_ptr<Item>>
    filterItems(const Inventory& inv, Predicate pred) {
        std::vector<std::shared_ptr<Item>> result;
        std::copy_if(
            inv.getItems().cbegin(),
            inv.getItems().cend(),
            std::back_inserter(result),
            pred
        );
        
        return result;
    }

    template<typename Key>
    void sortItems(Inventory& inv, Key keyFn) {
        std::sort(
            inv.getItems().begin(),
            inv.getItems().end(),
            [&keyFn](const std::shared_ptr<Item>& a,
                    const std::shared_ptr<Item>& b) {
                
                        return keyFn(a) < keyFn(b);
            }
        );
    }
}