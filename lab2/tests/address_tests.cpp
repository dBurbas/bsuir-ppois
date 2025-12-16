//
// Created by Dmitry Burbas on 15/12/2025.
//
#include <gtest/gtest.h>

#include "exceptions/components_exceptions.h"
#include "src/value_structures/address/address.h"
class AddressTest : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// --- Positive Tests ---

TEST_F(AddressTest, Constructor_FullData_Valid) {
  ASSERT_NO_THROW({
    Address addr("Belarus", "Minsk obl", "Minsk", "Lenina", 10, 55, "220050");
    EXPECT_EQ(addr.GetCountry(), "Belarus");
    EXPECT_EQ(addr.GetOblast(), "Minsk obl");
    EXPECT_EQ(addr.GetCity(), "Minsk");
    EXPECT_EQ(addr.GetStreet(), "Lenina");
    EXPECT_EQ(addr.GetHouseNumber(), 10);
    EXPECT_EQ(addr.GetApartmentNumber(), 55);
    EXPECT_EQ(addr.GetPostalCode(), "220050");
  });
}

TEST_F(AddressTest, Constructor_PartialData_NoApartment_NoIndex) {
  Address addr("Poland", "Masovian", "Warsaw", "Zlota", 44);
  EXPECT_EQ(addr.GetCountry(), "Poland");
  EXPECT_EQ(addr.GetHouseNumber(), 44);

  EXPECT_THROW(addr.GetApartmentNumber(), AddressException);
  EXPECT_THROW(addr.GetPostalCode(), AddressException);
}

TEST_F(AddressTest, ParseFromString_FullValidString) {
  std::string input = "Belarus;Minsk Region;Minsk;Pobedy;12;45;220030";
  Address addr(input);
  EXPECT_EQ(addr.GetStreet(), "Pobedy");
  EXPECT_EQ(addr.GetHouseNumber(), 12);
  EXPECT_EQ(addr.GetApartmentNumber(), 45);
  EXPECT_EQ(addr.GetPostalCode(), "220030");
}
TEST_F(AddressTest, Setters_UpdateValues_Valid) {
  Address addr("Country", "Region", "City", "Street", 1);

  addr.SetCountry("NewCountry");
  addr.SetCity("NewCity");
  addr.SetStreet("NewStreet");
  addr.SetHouse(100);

  EXPECT_EQ(addr.GetCountry(), "NewCountry");
  EXPECT_EQ(addr.GetCity(), "NewCity");
  EXPECT_EQ(addr.GetHouseNumber(), 100);
}

// --- Validation / Negative Tests ---

TEST_F(AddressTest, Validation_EmptyFields_Throws) {
  EXPECT_THROW(Address("", "O", "C", "S", 1), AddressException);
  EXPECT_THROW(Address("C", "O", "", "S", 1), AddressException);
  EXPECT_THROW(Address("C", "O", "C", "", 1), AddressException);
}

TEST_F(AddressTest, Validation_InvalidNumbers_Throws) {
  EXPECT_THROW(Address("C", "O", "C", "S", 0), AddressException);
  EXPECT_THROW(Address("C", "O", "C", "S", -5), AddressException);

  EXPECT_THROW(Address("C", "O", "C", "S", 1, -1), AddressException);
}

TEST_F(AddressTest, Validation_PostalCode_Belarus) {
  Address addr("Belarus", "O", "C", "S", 1);

  EXPECT_NO_THROW(addr.SetPostalCode("220000"));

  EXPECT_THROW(addr.SetPostalCode("12345"), AddressException);
  EXPECT_THROW(addr.SetPostalCode("22000A"), AddressException);
  EXPECT_THROW(addr.SetPostalCode("320000"), AddressException);
}

TEST_F(AddressTest, Validation_PostalCode_International) {
  Address addr("USA", "O", "C", "S", 1);
  EXPECT_NO_THROW(addr.SetPostalCode("10001"));
  EXPECT_NO_THROW(addr.SetPostalCode("SW1A 1AA"));

  EXPECT_THROW(addr.SetPostalCode("A"), AddressException);
  EXPECT_THROW(addr.SetPostalCode("ThisIsWayTooLongPostalCode"),
               AddressException);
}

TEST_F(AddressTest, ParseFromString_InvalidFormat) {
  EXPECT_THROW(Address("Belarus;Minsk"), AddressException);

  EXPECT_THROW(Address("C;O;C;S;NotANumber"), AddressException);
}

TEST_F(AddressTest, Normalization_Checks) {
  // Проверка, что пробелы обрезаются
  Address addr("  Belarus  ", " O ", " C ", " S ", 1);
  EXPECT_EQ(addr.GetCountry(), "Belarus");
  EXPECT_EQ(addr.GetOblast(), "O");
}
