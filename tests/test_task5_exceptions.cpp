#include "TestHelpers.hpp"

// ============================================================
// Task 5 — Error Handling
// ============================================================

TEST(ExceptionTest, AddDuplicateThrows) {
    Inventory inv;
    inv.addItem(makePhone());
    EXPECT_THROW(inv.addItem(makePhone()), DuplicateItemException);
}

TEST(ExceptionTest, RemoveNonExistentThrows) {
    Inventory inv;
    EXPECT_THROW(inv.removeItem("E99"), ItemNotFoundException);
}

TEST(ExceptionTest, UpdateQuantityNonExistentThrows) {
    Inventory inv;
    EXPECT_THROW(inv.updateQuantity("E99", 5), ItemNotFoundException);
}

TEST(ExceptionTest, UpdateQuantityNegativeThrows) {
    Inventory inv;
    inv.addItem(makePhone());
    EXPECT_THROW(inv.updateQuantity("E1", -1), InvalidValueException);
}

TEST(ExceptionTest, ItemNotFoundMessageContainsID) {
    Inventory inv;
    try {
        inv.removeItem("E99");
        FAIL() << "Expected ItemNotFoundException";
    } catch (const ItemNotFoundException& e) {
        EXPECT_NE(std::string(e.what()).find("E99"), std::string::npos);
    }
}

TEST(ExceptionTest, DuplicateMessageContainsID) {
    Inventory inv;
    inv.addItem(makePhone());
    try {
        inv.addItem(makePhone());
        FAIL() << "Expected DuplicateItemException";
    } catch (const DuplicateItemException& e) {
        EXPECT_NE(std::string(e.what()).find("E1"), std::string::npos);
    }
}

TEST(ExceptionTest, AllExceptionsCatchableAsInventoryException) {
    Inventory inv;
    EXPECT_THROW(
        { try { inv.removeItem("X"); }
          catch (const InventoryException&) { throw; } },
        InventoryException);
}

TEST(ExceptionTest, StrongSafetyOnAddDuplicate) {
    Inventory inv;
    inv.addItem(makePhone());
    const std::size_t before = inv.getItems().size();

    try { inv.addItem(makePhone()); } catch (...) {}

    EXPECT_EQ(inv.getItems().size(), before);
}