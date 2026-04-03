#include "TestHelpers.hpp"

// ============================================================
// Task 2 — Inventory (STL containers)
// ============================================================

TEST(InventoryTest, EmptyByDefault) {
    Inventory inv;
    EXPECT_TRUE(inv.getItems().empty());
}

TEST(InventoryTest, AddItemIncreasesSize) {
    Inventory inv;
    inv.addItem(makePhone());
    EXPECT_EQ(inv.getItems().size(), 1u);
}

TEST(InventoryTest, AddMultipleItems) {
    Inventory inv;
    inv.addItem(makePhone());
    inv.addItem(makeLaptop());
    inv.addItem(makeApple());
    EXPECT_EQ(inv.getItems().size(), 3u);
}

TEST(InventoryTest, RemoveItemDecreasesSize) {
    Inventory inv;
    inv.addItem(makePhone());
    inv.addItem(makeLaptop());
    inv.removeItem("E1");
    EXPECT_EQ(inv.getItems().size(), 1u);
}

TEST(InventoryTest, RemoveItemCorrectItemRemoved) {
    Inventory inv;
    inv.addItem(makePhone());
    inv.addItem(makeLaptop());
    inv.removeItem("E1");
    EXPECT_EQ(inv.getItems().front()->getItemId(), "E2");
}

TEST(InventoryTest, UpdateQuantityChangesValue) {
    Inventory inv;
    inv.addItem(makePhone());
    inv.updateQuantity("E1", 99);
    EXPECT_EQ(inv.getItems().front()->getQuantity(), 99);
}

TEST(InventoryTest, DisplayInventoryEmptyMessage) {
    Inventory inv;
    std::string out = captureInventoryDisplay(inv);
    EXPECT_NE(out.find("empty"), std::string::npos);
}

TEST(InventoryTest, DisplayInventoryShowsItems) {
    Inventory inv;
    inv.addItem(makePhone());
    std::string out = captureInventoryDisplay(inv);
    EXPECT_NE(out.find("Phone"), std::string::npos);
}