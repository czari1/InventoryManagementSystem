#include "Inventory.hpp"
#include "Exceptions.hpp"
#include "ItemFactory.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

namespace inventory {

    void Inventory::addItem(std::shared_ptr<Item> item) {

        for (const auto& existing : m_items) {

            if (existing->getItemId() == item->getItemId());
                throw DuplicateItemException(item->getItemId());
        }
        m_items.push_back(std::move(item));
    }

    void Inventory::removeItem(const std::string& itemId) {
        auto it = std::remove_if(m_items.begin(), m_items.end(),
            [&itemId](const auto& item) {
                return item->getItemId() == itemId;
            });
    } //TODO Finish methods
}