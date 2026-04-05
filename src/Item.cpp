#include "Item.hpp"
#include "Exceptions.hpp"
#include <iomanip>
#include <iostream>

namespace inventory {

    Item::Item(std::string itemId, std::string name, int quantity, double price)
        : m_itemId(std::move(itemId)),
          m_name(std::move(name)),
          m_quantity(quantity),
          m_price(price)
    {
        if (quantity < MIN_QUANTITY) 
            throw InvalidValueException("Quantity cannot be negative.");

        if (price < MIN_PRICE)
            throw InvalidValueException("Price cannot be negative.");
    }

    void Item::setName(std::string name) {
        m_name = std::move(name);
    }

    void Item::setQuantity(int quantity) {
        if (quantity < MIN_QUANTITY)
            throw InvalidValueException("Quantity cannot be negative.");
        m_quantity = quantity;
    }

    void Item::setPrice(double price) {
        if (price < MIN_PRICE)
            throw InvalidValueException("Price cannot be negative.");
        m_price = price;
    }

    std::optional<std::string> Item::findAttribute(const std::string& /* key */) const noexcept {
        return std::nullopt;
    }

    void Item::displayBase() const {
        std::cout << std::fixed << std::setprecision(2)
                  << "[" << category() << "]"
                  << " ID: "    << m_itemId
                  << " | Name: " << m_name
                  << " | Qty: "  << m_quantity
                  << " | Price: "<< m_price;
    }
    
}
