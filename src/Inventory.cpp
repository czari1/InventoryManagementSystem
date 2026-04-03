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

            if (existing->getItemId() == item->getItemId())
                throw DuplicateItemException(item->getItemId());
        }
        m_items.push_back(std::move(item));
    }

    void Inventory::removeItem(const std::string& itemId) {
        const auto it = std::remove_if(m_items.begin(), m_items.end(),
            [&itemId](const auto& item) {
                return item->getItemId() == itemId;
            });
        
        if (it == m_items.end()) 
            throw ItemNotFoundException(itemId);

        m_items.erase(it, m_items.end());
    }

    void Inventory::updateQuantity(const std::string& itemId, int quantity) {

        for (auto& item : m_items) {

            if (item->getItemId() == itemId) {
                item->setQuantity(quantity);
                return;
            }
        }

        throw ItemNotFoundException(itemId);
    }

    void Inventory::displayInventory() const {

        if(m_items.empty()) {
            std::cout << "Inventory is empty\n";
            return;
        }

        for (const auto& item : m_items) {
            item->display();
        }
    }

    void Inventory::readFromFile(const std::string& filename) {
        std::ifstream file(filename);

        if (!file.is_open()) {
            throw InventoryException("Cannot open file for reading: '" + filename + "'");
        }

        std::vector<std::shared_ptr<Item>> loaded;
        std::string line;
        int lineNumber = 0;

        try {

            while (std::getline(file, line)) {
                ++lineNumber;

                if (line.empty()) continue;

                std::istringstream ss(line);
                std::string itemId, category, name, quantityStr, priceStr, extra;

                if (!std::getline(ss, itemId, ',') ||
                    !std::getline(ss, category, ',') ||
                    !std::getline(ss, name, ',') ||
                    !std::getline(ss, quantityStr,',') ||
                    !std::getline(ss, priceStr, ',') ||
                    !std::getline(ss, extra, ','))
                {
                    throw InventoryException(
                        "Malformed CSV at line " + std::to_string(lineNumber) +
                        ": '" + line + "'");
                }

                if (!extra.empty() && extra.back() == '\r')
                    extra.pop_back();

                const int quantity = std::stoi(quantityStr);
                const double price = std::stod(priceStr);

                if (category == "Electronics") {
                    loaded.push_back(makeElectronics(itemId, name, quantity, price, std::stoi(extra)));
                } else if (category == "Grocery") {
                    loaded.push_back(makeGrocery(itemId, name, quantity, price, extra));
                } else {
                    throw InventoryException(
                        "Unknown category '" + category + "' at line " +
                        std::to_string(lineNumber));
                }
            }
        } catch (const std::invalid_argument& e) {
            throw InventoryException(
                "Invalid numeric value at line " + std::to_string(lineNumber) +
                ": " + e.what());
        } catch (const std::out_of_range& e) {
            throw InventoryException(
                "Numeric value out of range at line " + std::to_string(lineNumber) +
                ": " + e.what());
        }

        m_items = std::move(loaded);
    }

    void Inventory::writeToFile(const std::string& filename) const {
        std::ofstream file(filename);

        if (!file.is_open()){
            throw InventoryException("Cannot open file for writing: '" + filename + "'");
        }

        // Format: itemID,category,name,quantity,price,extra
        for (const auto& item : m_items) {
            file << item->getItemId() << ","
                << item->category() << ","
                << item->getName() << ","
                << item->getQuantity() << ","
                << item->getPrice() << ",";

            // Retrieve the category-specific extra field via findAttribute
            if (item->category() == "Electronics") {
                const auto warranty = item->findAttribute("warranty");
                file << warranty.value_or("0");
            } else {
                const auto expDate = item->findAttribute("expirationDate");
                file << expDate.value_or("");
            }

            file << "\n";
        }
    }
}