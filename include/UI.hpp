#pragma once

#include "Inventory.hpp"

namespace inventory {

    class UI {
    public:
        explicit UI(Inventory& inventory);

        void run();
    
    private:
        Inventory& m_inventory;
        std::string m_dataDir;

        [[nodiscard]] std::string resolvePath(const std::string& filename) const;

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