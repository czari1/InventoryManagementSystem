#pragma once

#include <stdexcept>
#include <string>

namespace inventory {
    class InventoryException : public std::runtime_error {
    public:
        explicit InventoryException(const std::string& message)
        : std::runtime_error(message) {}
    };
    
    class ItemNotFoundException : public InventoryException {
    public:
        explicit ItemNotFoundException(const std::string& itemID)
        : InventoryException("Item with ID '" + itemID + "' not found.") {}
    };

    class DuplicateItemException : public InventoryException {
    public:
        explicit DuplicateItemException(const std::string& itemID)
        : InventoryException(
        "Item with ID '" + itemID + "' already exists in inventory.") {}
    };

    class InvalidValueException : public InventoryException {
    public:
        explicit InvalidValueException(const std::string& message)
            : InventoryException(message) {}
    };

}
