#include "TestHelpers.hpp"

// ============================================================
// Task 3 — Smart Pointers & Move semantics
// ============================================================

TEST(InventoryMoveTest, MoveConstructorTransfersItems) {
    Inventory src;
    src.addItem(makePhone());
    src.addItem(makeApple());

    Inventory dst = std::move(src);
    EXPECT_EQ(dst.getItems().size(), 2u);
    EXPECT_TRUE(src.getItems().empty());
}

TEST(InventoryMoveTest, MoveAssignmentTransfersItems) {
    Inventory src;
    src.addItem(makePhone());

    Inventory dst;
    dst = std::move(src);
    EXPECT_EQ(dst.getItems().size(), 1u);
    EXPECT_TRUE(src.getItems().empty());
}

TEST(InventoryMoveTest, CopyConstructorDeleted) {
    EXPECT_FALSE(std::is_copy_constructible<Inventory>::value);
}

TEST(InventoryMoveTest, CopyAssignmentDeleted) {
    EXPECT_FALSE(std::is_copy_assignable<Inventory>::value);
}

TEST(FactoryTest, MakeElectronicsReturnsNonNull) {
    EXPECT_NE(makePhone(), nullptr);
}

TEST(FactoryTest, MakeGroceryReturnsNonNull) {
    EXPECT_NE(makeApple(), nullptr);
}

TEST(FactoryTest, SharedPtrRefCountIsOne) {
    auto e = makePhone();
    EXPECT_EQ(e.use_count(), 1);
}