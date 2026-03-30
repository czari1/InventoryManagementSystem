#pragma once 

#include "Item.hpp"
#include <memory>
#include <string>
#include <vector>

namespace inventory {

    class Inventory {
    public:
        Inventory() = default;
        ~Inventory() = default;

        Inventory(Inventory&&) noexcept = default;
        Inventory& operator=(Inventory&&) noexcept = default;
        Inventory(const Inventory&) = delete;
        Inventory& operator=(const Inventory&) = delete;

        void addItem(std::shared_ptr<Item> item);
        void removeItem(const std::string& itemId);
        void updateQuantity(const std::string& itemId, int quantity);
        void displayInventory() const;

        void readFromFile(const std::string& filename);
        void writeToFile(const std::string& filename) const;

        [[nodiscard]] const std::vector<std::shared_ptr<Item>>& getItems() const noexcept {
            return m_items;
        }
        [[nodiscard]] std::vector<std::shared_ptr<Item>>& getItems() noexcept {
            return m_items;
        }
    private:
        std::vector<std::shared_ptr<Item>> m_items;
    };
}