#pragma once
#include "Item.hpp"

namespace inventory {
    class Electronics final : public Item {
    public: 
        Electronics(std::string electronicsId, std::string name, int quantity,
                    double price, int warrantyMonths);
        
        void display() const override;
        
        [[nodiscard]] std::string category() const override;

        [[nodiscard]] std::optional<std::string>
        findAttribute(const std::string& key) const noexcept override ;

        [[nodiscard]] int getWarrantyMonths() const noexcept { return m_warrantyMonths; }
        
        void setWarrantyMonths(int months);
    private:
        int m_warrantyMonths;
    };
}