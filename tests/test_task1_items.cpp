#include "TestHelpers.hpp"

// ============================================================
// Task 1 — Item
// ============================================================

TEST(ItemTest, ConstructorStoresValues) {
    auto e = makeElectronics("E1", "Phone", 10, 699.99, 24);
    EXPECT_EQ(e->getItemId(),   "E1");
    EXPECT_EQ(e->getName(),     "Phone");
    EXPECT_EQ(e->getQuantity(), 10);
    EXPECT_DOUBLE_EQ(e->getPrice(), 699.99);
}

TEST(ItemTest, SetQuantityUpdatesValue) {
    auto e = makePhone();
    e->setQuantity(42);
    EXPECT_EQ(e->getQuantity(), 42);
}

TEST(ItemTest, SetPriceUpdatesValue) {
    auto e = makePhone();
    e->setPrice(999.00);
    EXPECT_DOUBLE_EQ(e->getPrice(), 999.00);
}

TEST(ItemTest, SetNameUpdatesValue) {
    auto e = makePhone();
    e->setName("Smartphone");
    EXPECT_EQ(e->getName(), "Smartphone");
}

TEST(ItemTest, NegativeQuantityThrows) {
    EXPECT_THROW(makeElectronics("E1", "Phone", -1, 100.0, 12),
                 InvalidValueException);
}

TEST(ItemTest, NegativePriceThrows) {
    EXPECT_THROW(makeElectronics("E1", "Phone", 1, -0.01, 12),
                 InvalidValueException);
}

TEST(ItemTest, ZeroQuantityAllowed) {
    EXPECT_NO_THROW(makeElectronics("E1", "Phone", 0, 100.0, 12));
}

TEST(ItemTest, ZeroPriceAllowed) {
    EXPECT_NO_THROW(makeElectronics("E1", "Phone", 1, 0.0, 12));
}

TEST(ItemTest, SetNegativeQuantityThrows) {
    auto e = makePhone();
    EXPECT_THROW(e->setQuantity(-1), InvalidValueException);
}

TEST(ItemTest, SetNegativePriceThrows) {
    auto e = makePhone();
    EXPECT_THROW(e->setPrice(-1.0), InvalidValueException);
}

// ============================================================
// Task 1 — Electronics
// ============================================================

TEST(ElectronicsTest, CategoryReturnsElectronics) {
    EXPECT_EQ(makePhone()->category(), "Electronics");
}

TEST(ElectronicsTest, WarrantyStoredCorrectly) {
    auto e = makeElectronics("E1", "Phone", 10, 699.99, 24);
    auto raw = std::dynamic_pointer_cast<Electronics>(e);
    ASSERT_NE(raw, nullptr);
    EXPECT_EQ(raw->getWarrantyMonths(), 24);
}

TEST(ElectronicsTest, NegativeWarrantyThrows) {
    EXPECT_THROW(makeElectronics("E1", "Phone", 10, 699.99, -1),
                 InvalidValueException);
}

TEST(ElectronicsTest, FindAttributeWarranty) {
    auto attr = makePhone()->findAttribute("warranty");
    ASSERT_TRUE(attr.has_value());
    EXPECT_EQ(attr.value(), "24");
}

TEST(ElectronicsTest, FindAttributeUnknownReturnsNullopt) {
    EXPECT_FALSE(makePhone()->findAttribute("expiry").has_value());
}

TEST(ElectronicsTest, DisplayContainsExpectedFields) {
    std::string out = captureDisplay(makePhone());
    EXPECT_NE(out.find("Electronics"), std::string::npos);
    EXPECT_NE(out.find("E1"),          std::string::npos);
    EXPECT_NE(out.find("Phone"),       std::string::npos);
    EXPECT_NE(out.find("24"),          std::string::npos);
    EXPECT_NE(out.find("Warranty"),    std::string::npos);
}

// ============================================================
// Task 1 — Grocery
// ============================================================

TEST(GroceryTest, CategoryReturnsGrocery) {
    EXPECT_EQ(makeApple()->category(), "Grocery");
}

TEST(GroceryTest, ExpirationDateStoredCorrectly) {
    auto g = std::dynamic_pointer_cast<Grocery>(makeApple());
    ASSERT_NE(g, nullptr);
    EXPECT_EQ(g->getExpirationDate(), "2026-06-01");
}

TEST(GroceryTest, FindAttributeExpirationDate) {
    auto attr = makeApple()->findAttribute("expirationDate");
    ASSERT_TRUE(attr.has_value());
    EXPECT_EQ(attr.value(), "2026-06-01");
}

TEST(GroceryTest, FindAttributeUnknownReturnsNullopt) {
    EXPECT_FALSE(makeApple()->findAttribute("warranty").has_value());
}

TEST(GroceryTest, DisplayContainsExpectedFields) {
    std::string out = captureDisplay(makeApple());
    EXPECT_NE(out.find("Grocery"),    std::string::npos);
    EXPECT_NE(out.find("G1"),         std::string::npos);
    EXPECT_NE(out.find("Apple"),      std::string::npos);
    EXPECT_NE(out.find("2026-06-01"), std::string::npos);
    EXPECT_NE(out.find("Expires"),    std::string::npos);
}