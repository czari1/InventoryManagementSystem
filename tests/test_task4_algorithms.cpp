#include "TestHelpers.hpp"

// ============================================================
// Task 4 — Templates & Generic Programming
// ============================================================

TEST(AlgorithmsTest, FilterItemsBelowQuantity) {
    Inventory inv;
    inv.addItem(makePhone());   // qty=10
    inv.addItem(makeLaptop());  // qty=5
    inv.addItem(makeApple());   // qty=100

    auto result = filterItems(inv,
        [](const auto& item) { return item->getQuantity() < 20; });

    EXPECT_EQ(result.size(), 2u);
}

TEST(AlgorithmsTest, FilterItemsNoMatch) {
    Inventory inv;
    inv.addItem(makePhone());

    auto result = filterItems(inv,
        [](const auto& item) { return item->getQuantity() > 9999; });

    EXPECT_TRUE(result.empty());
}

TEST(AlgorithmsTest, FilterItemsAllMatch) {
    Inventory inv;
    inv.addItem(makePhone());
    inv.addItem(makeLaptop());

    auto result = filterItems(inv,
        [](const auto&) { return true; });

    EXPECT_EQ(result.size(), 2u);
}

TEST(AlgorithmsTest, SortItemsByPriceAscending) {
    Inventory inv;
    inv.addItem(makeLaptop());  // 1099.99
    inv.addItem(makePhone());   //  699.99
    inv.addItem(makeApple());   //    0.99

    sortItems(inv, [](const auto& item) { return item->getPrice(); });

    const auto& items = inv.getItems();
    EXPECT_DOUBLE_EQ(items[0]->getPrice(),    0.99);
    EXPECT_DOUBLE_EQ(items[1]->getPrice(),  699.99);
    EXPECT_DOUBLE_EQ(items[2]->getPrice(), 1099.99);
}

TEST(AlgorithmsTest, SortItemsByName) {
    Inventory inv;
    inv.addItem(makePhone());   // "Phone"
    inv.addItem(makeApple());   // "Apple"
    inv.addItem(makeLaptop());  // "Laptop"

    sortItems(inv, [](const auto& item) { return item->getName(); });

    const auto& items = inv.getItems();
    EXPECT_EQ(items[0]->getName(), "Apple");
    EXPECT_EQ(items[1]->getName(), "Laptop");
    EXPECT_EQ(items[2]->getName(), "Phone");
}