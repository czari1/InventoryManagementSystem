#pragma once 

#include "Item.hpp"

namespace inventory {

class Grocery final : public Item {
    public:
        Grocery(std::string groceryId, std::string name, int quantity, 
                double price, std::string expirationDate);
        
        void display() const override;

        [[nodiscard]] std::string category() const override;

        [[nodiscard]] std::optional<std::string>
        findAttribute(const std::string& key) const noexcept override;

        [[nodiscard]] const std::string& getExpirationDate() const noexcept {
            return m_expirationDate;
        }

        void setExpirationDate(std::string date);

    private:
            std::string m_expirationDate;
    };
}