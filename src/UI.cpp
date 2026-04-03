#include "UI.hpp"
#include "Algorithms.hpp"
#include "ItemFactory.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <limits>
#include <algorithm>
#include <filesystem>

namespace inventory {

    UI::UI(Inventory& inventory) 
    : m_inventory(inventory)
    , m_dataDir(PROJECT_DATA_DIR)
    {}

    std::string UI::resolvePath(const std::string& filename) const {

        if (std::filesystem::path(filename).is_absolute())
            return filename;
        return m_dataDir + "/" + filename;
    }

    void UI::run() {
        int choice = 0;

        do {
            printMenu();

            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter an int.\n";
                continue;
            }
            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            try {
                switch (choice) {
                    case 1: handleAddElectronics(); break;
                    case 2: handleAddGrocery(); break;
                    case 3: handleRemoveItem(); break;
                    case 4:  handleUpdateQuantity(); break;
                    case 5:  handleDisplayInventory(); break;
                    case 6:  handleReadFromFile(); break;
                    case 7:  handleWriteToFile(); break;
                    case 8:  handleFindMostExpensive(); break;
                    case 9:  handleFilterByQuantity(); break;
                    case 10: handleSortByPrice(); break;
                    case 11: std::cout << "Goodbye\n"; break;
                    default: std::cout << "Invalid option. Please choose number from 1 to 11. \n";
                }
            } catch (const InventoryException& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        } while (choice != 11);
    }

    void UI::printMenu() {
        std::cout << "Inventory Management System\n"
            << " 1. Add Electronics\n"
            << " 2. Add Grocery\n"
            << " 3. Remove Item\n"
            << " 4. Update Quantity\n"
            << " 5. Display Inventory\n"
            << " 6. Read from File\n"
            << " 7. Write to File\n"
            << " 8. Find Most Expensive Item\n"
            << " 9. Find Items Below Quantity Threshold\n"
            << "10. Sort by Price\n"
            << "11. Exit\n"
            << "Choice: ";
    }

    void UI::handleAddElectronics() {
        std::string id, name;
        int quantity, warranty;
        double price;

        std::cout << "ID: "; 
        std::getline(std::cin, id);
        
        std::cout << "Name: "; 
        std::getline(std::cin, name);
        
        std::cout << "Quantity: ";
        std::cin >> quantity;
        
        std::cout << "Price: ";
        std::cin >> price;

        std::cout << "Warranty (months): ";
        std::cin >> warranty;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        m_inventory.addItem(makeElectronics(id, name, quantity, price, warranty));
        std::cout << "Electronics item added.\n";
    }

    void UI::handleAddGrocery() {
        std::string id, name, expDate;
        int quantity;
        double price;

        std::cout << "ID: "; 
        std::getline(std::cin, id);
        
        std::cout << "Name: "; 
        std::getline(std::cin, name);

        std::cout << "Quantity: ";
        std::cin >> quantity;

        std::cout << "Price: ";
        std::cin >> price;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "Expiration date: "; 
        std::getline(std::cin, expDate);

        m_inventory.addItem(makeGrocery(id, name, quantity, price, expDate));
        std::cout << "Grocery item added.\n";
    }

    void UI::handleRemoveItem() {
        std::string id;
        
        std::cout << "Item ID to remove: ";
        std::getline(std::cin, id);
        
        m_inventory.removeItem(id);
        std::cout << "Item removed.\n";
    }

    void UI::handleUpdateQuantity() {
        std::string id;
        int quantity;
        std::cout << "Item ID: "; 
        std::getline(std::cin, id);

        std::cout << "New quantity: ";
        std::cin >> quantity;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        m_inventory.updateQuantity(id, quantity);
        std::cout << "Quantity updated.\n";
    }

    void UI::handleDisplayInventory() const {
        m_inventory.displayInventory();
    }

    void UI::handleReadFromFile() {
        std::string filename;

        std::cout << "Filename: ";
        std::getline(std::cin, filename);

        const std::string path = resolvePath(filename);
        m_inventory.readFromFile(path);
        std::cout << "Inventory loaded from file.\n";
    }

    void UI::handleWriteToFile() const {
        std::string filename;

        std::cout << "Filename: ";
        std::getline(std::cin, filename);

        const std::string path = resolvePath(filename);
        m_inventory.writeToFile(path);
        std::cout << "Inventory saved to file.\n";
    }

    void UI::handleFindMostExpensive() const {
        const auto& items = m_inventory.getItems();

        if (items.empty()) {
            std::cout << "Inventory is empty.\n";
            return;
        }

        const auto it = std::max_element(items.cbegin(), items.cend(),
            [](const auto& a, const auto& b) {
                return a->getPrice() < b->getPrice();
            });
        (*it)->display();
    }

    void UI::handleFilterByQuantity() const {
        int threshold;

        std::cout << "Show items below quantity: ";
        std::cin >> threshold;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        const auto result = filterItems(m_inventory,
            [threshold](const auto& item) {
                return item->getQuantity() < threshold;
            });

        if (result.empty()) {
            std::cout << "No items below threshold " << threshold << ".\n";
        } else {
            
            for (const auto& item : result) {
                item->display();
            }
        }
    }

    void UI::handleSortByPrice() {
        sortItems(m_inventory, [](const auto& item) {
            return item->getPrice();
        });
        std::cout << "Inventory sorted by price.\n";
    }
}