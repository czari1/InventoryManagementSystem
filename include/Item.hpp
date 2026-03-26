#pragma once

#include <optional>
#include <string>
#include "IDisplayable.hpp"

namespace inventory {
    inline constexpr int MIN_QUANTITY = 0;
    inline constexpr double MIN_PRICE = 0.0;

    class Item : public IDisplayable {
    public:
        Item(std::string itemId, std::string name, int quantity, double price);
        
        virtual ~Item() = default;
        Item(const Item&) = default;
        Item& operator=(const Item&) = default;
        Item(Item&&) = default;
        Item& operator=(Item&&) = default;

        virtual void display() const = 0;

        [[nodiscard]] virtual std::string category() const = 0;

        [[nodiscard]] virtual std::optional<std::string> findAttribute(const std::string& key) const;

        [[nodiscard]] const std::string& getItemId() const noexcept { return m_itemId; }
        [[nodiscard]] const std::string& getName() const noexcept { return m_name; }
        [[nodiscard]] int getQuantity() const noexcept { return m_quantity; }
        [[nodiscard]] double getPrice() const noexcept { return m_price; }

        void setName(std::string name);
        void setQuantity(int quantity);
        void setPrice(double price);

    protected:
        void displayBase() const;

    private:
        std::string m_itemId;
        std::string m_name;
        int m_quantity;
        double m_price;
    };
}