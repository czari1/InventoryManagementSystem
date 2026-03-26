#pragma once

#include "Inventory.hpp"

namespace inventory {

    class UI {
    public:
        explicit UI(Inventory& inventory);

        void run();
    
    private:
        Inventory& m_inventory;

        void printMenu();

        void handleAddElectronics();
        void handleAddGrocery();
        void handleRemoveItem();
        void handleUpdateQuantity();
        void handleDisplayInventory()  const;
        void handleReadFromFile();
        void handleWriteToFile()       const;
        void handleFindMostExpensive() const;
        void handleFilterByQuantity()  const;
        void handleSortByPrice();
    };
}