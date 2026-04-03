#include "TestHelpers.hpp"
#include <fstream>
#include <filesystem>

// ============================================================
// Task 6 — File I/O
// ============================================================

class FileIOTest : public ::testing::Test {
protected:
    std::string testFile = "/tmp/inv_test.csv";

    void TearDown() override {
        std::filesystem::remove(testFile);
    }
};

TEST_F(FileIOTest, WriteAndReadRoundtrip) {
    Inventory src;
    src.addItem(makePhone());
    src.addItem(makeApple());
    src.writeToFile(testFile);

    Inventory dst;
    dst.readFromFile(testFile);

    ASSERT_EQ(dst.getItems().size(), 2u);

    const auto& e = dst.getItems()[0];
    EXPECT_EQ(e->getItemId(),       "E1");
    EXPECT_EQ(e->getName(),         "Phone");
    EXPECT_EQ(e->getQuantity(),     10);
    EXPECT_DOUBLE_EQ(e->getPrice(), 699.99);
    EXPECT_EQ(e->category(),        "Electronics");

    const auto& g = dst.getItems()[1];
    EXPECT_EQ(g->getItemId(),  "G1");
    EXPECT_EQ(g->getName(),    "Apple");
    EXPECT_EQ(g->category(),   "Grocery");
    auto expDate = g->findAttribute("expirationDate");
    ASSERT_TRUE(expDate.has_value());
    EXPECT_EQ(expDate.value(), "2026-06-01");
}

TEST_F(FileIOTest, ReadFromMissingFileThrows) {
    Inventory inv;
    EXPECT_THROW(inv.readFromFile("/tmp/does_not_exist_xyz.csv"),
                 InventoryException);
}

TEST_F(FileIOTest, WriteToInvalidPathThrows) {
    Inventory inv;
    inv.addItem(makePhone());
    EXPECT_THROW(inv.writeToFile("/no_such_dir/output.csv"),
                 InventoryException);
}

TEST_F(FileIOTest, ReadMalformedLineThrows) {
    std::ofstream f(testFile);
    f << "E1,Electronics,Phone,10\n"; // missing price and extra
    f.close();

    Inventory inv;
    EXPECT_THROW(inv.readFromFile(testFile), InventoryException);
}

TEST_F(FileIOTest, ReadUnknownCategoryThrows) {
    std::ofstream f(testFile);
    f << "X1,Robot,Terminator,1,999.99,0\n";
    f.close();

    Inventory inv;
    EXPECT_THROW(inv.readFromFile(testFile), InventoryException);
}

TEST_F(FileIOTest, ReadEmptyFileResultsInEmptyInventory) {
    std::ofstream f(testFile);
    f.close();

    Inventory inv;
    inv.addItem(makePhone());
    inv.readFromFile(testFile);
    EXPECT_TRUE(inv.getItems().empty());
}

TEST_F(FileIOTest, ReadWindowsCRLFFile) {
    std::ofstream f(testFile, std::ios::binary);
    f << "E1,Electronics,Phone,10,699.99,24\r\n";
    f << "G1,Grocery,Apple,100,0.99,2026-06-01\r\n";
    f.close();

    Inventory inv;
    EXPECT_NO_THROW(inv.readFromFile(testFile));
    ASSERT_EQ(inv.getItems().size(), 2u);

    auto expDate = inv.getItems()[1]->findAttribute("expirationDate");
    ASSERT_TRUE(expDate.has_value());
    EXPECT_EQ(expDate.value(), "2026-06-01"); // must NOT contain \r
}

TEST_F(FileIOTest, StrongSafetyOnBadRead) {
    Inventory inv;
    inv.addItem(makePhone());
    inv.addItem(makeLaptop());

    std::ofstream f(testFile);
    f << "E3,Electronics,Tablet,3,399.99,6\n";
    f << "BAD_LINE\n";
    f.close();

    EXPECT_THROW(inv.readFromFile(testFile), InventoryException);
    EXPECT_EQ(inv.getItems().size(), 2u);       // original items intact
    EXPECT_EQ(inv.getItems()[0]->getItemId(), "E1");
}

TEST_F(FileIOTest, WriteAllFourSampleItems) {
    Inventory src;
    src.addItem(makePhone());
    src.addItem(makeLaptop());
    src.addItem(makeApple());
    src.addItem(makeMilk());
    src.writeToFile(testFile);

    Inventory dst;
    dst.readFromFile(testFile);
    EXPECT_EQ(dst.getItems().size(), 4u);
}

TEST_F(FileIOTest, WarrantyRoundtrip) {
    Inventory src;
    src.addItem(makeElectronics("E5", "TV", 3, 499.99, 36));
    src.writeToFile(testFile);

    Inventory dst;
    dst.readFromFile(testFile);
    auto w = dst.getItems()[0]->findAttribute("warranty");
    ASSERT_TRUE(w.has_value());
    EXPECT_EQ(w.value(), "36");
}