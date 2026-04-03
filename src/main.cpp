#include "Inventory.hpp"
#include "ItemFactory.hpp"
#include "Algorithms.hpp"
#include "UI.hpp"
#include "Exceptions.hpp"
#include <iostream>

static inventory::Inventory buildDemoInventory() {
    inventory::Inventory inv;

    inv.addItem(inventory::makeElectronics("E1", "Phone",  10,  699.99, 24));
    inv.addItem(inventory::makeElectronics("E2", "Laptop",  5, 1099.99, 12));
    inv.addItem(inventory::makeGrocery   ("G1", "Apple", 100,    0.99, "2026-06-01"));
    inv.addItem(inventory::makeGrocery   ("G2", "Milk",   30,    1.49, "2026-04-10"));

    return inv;
}

int main() {

    std::cout << "Demo\n";

    inventory::Inventory demo = buildDemoInventory();

    std::cout << "Inevntory\n";
    demo.displayInventory();

    inventory::Inventory movedInv = std::move(demo);

    std::cout << "\nAfter std::move(demo)\n";
    demo.displayInventory();
    
    std::cout << "\nmovedInv holds all items\n";
    movedInv.displayInventory();

    std::cout << "\nfilterItems — qty < 20\n";
    const auto filtered = inventory::filterItems(movedInv,
        [](const auto& item) { return item->getQuantity() < 20; });

    for (const auto& item : filtered)
        item->display();

    std::cout << "\nsortItems by price \n";
    inventory::sortItems(movedInv,
        [](const auto& item) { return item->getPrice(); });
    movedInv.displayInventory();

    std::cout << "\nStarting CLI menu\n\n";

    inventory::Inventory appInventory;
    inventory::UI ui(appInventory);
    ui.run();

    return 0;
}