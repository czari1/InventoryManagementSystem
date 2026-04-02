#include "Electronics.hpp"
#include "Exceptions.hpp"
#include <iostream>

namespace inventory {
    
    Electronics::Electronics(std::string electronicsId, std::string name,
                            int quantity, double price, int warrantyMonths)
        : Item(std::move(electronicsId), std::move(name), quantity, price)
        , m_warrantyMonths(warrantyMonths)
        {
            if (warrantyMonths < 0)
                throw InvalidValueException("Warranty months cannot be negative.");
        }

        void Electronics::display() const {
            displayBase();
            std::cout << " | Warranty: " << m_warrantyMonths << " months\n";
        }

        std::string Electronics::category() const {
            return "Electronics";
        }

        std::optional<std::string> Electronics::findAttribute(const std::string& key) const {
            
            if (key == "warranty") {
                return std::to_string(m_warrantyMonths);
            }

            return std::nullopt;
        }

        void Electronics::setWarrantyMonths(int months) {
            
            if (months < 0) {
                throw InvalidValueException("Warranty months cannot be negative");
            }
            m_warrantyMonths = months;
            
        }
}