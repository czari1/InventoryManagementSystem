#include "Grocery.hpp"
#include "Exceptions.hpp"
#include <iostream>

namespace inventory {

    Grocery::Grocery(std::string groceryId, std::string name,
                    int quantity, double price, std::string expirationDate)
        : Item(std::move(groceryId), std::move(name), quantity, price)
        , m_expirationDate(std::move(expirationDate))
        {}
    
    void Grocery::display() const {
        displayBase();
        std::cout << " | Expires: " << m_expirationDate << "\n";
    }

    std::string Grocery::category() const {
        return "Grocery";
    }

    std::optional<std::string> Grocery::findAttribute(const std::string& key) const {
        
        if (key == "expirationDate") {
            return m_expirationDate;
        }
            
        return std::nullopt;
    }

    void Grocery::setExpirationDate(std::string date) {
        m_expirationDate = std::move(date);
    }
}