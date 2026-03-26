#include "ItemFactory.hpp"
#include "Electronics.hpp"
#include "Grocery.hpp"

namespace inventory {

    std::shared_ptr<Item> makeElectronics(const std::string& electronicsId, const std::string& name,
                                          int qty, double price, int warrantyMonths) {
        return std::make_shared<Electronics>(electronicsId, name, qty, price, warrantyMonths);
    }

    std::shared_ptr<Item> makeGrocery(const std::string& groceryId, const std::string& name,
                                      int qty, double price, const std::string& expDate) {
        return std::make_shared<Grocery>(groceryId, name, qty, price, expDate);
    }
}