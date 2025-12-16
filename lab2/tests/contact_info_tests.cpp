//
// Created by Dmitry Burbas on 16/11/2025.
//
#include "../src/exceptions/components_exceptions.h"
#include "../src/value_structures/address/address.h"
#include "../src/value_structures/contact_info/contact_info.h"
#include "gtest/gtest.h"

// Тесты Конструктора (покомпонентного)

TEST(ContactInfoTest, Constructor_ValidData_NoAddress) {
  ContactInfo info("+375291234567", "test@example.com", "");
  EXPECT_EQ(info.GetPhoneNumber(), "+375291234567");
  EXPECT_EQ(info.GetEmail(), "test@example.com");
  EXPECT_THROW(info.GetAddress(), ContactInfoException);
}

TEST(ContactInfoTest, Constructor_ValidData_WithAddressObject) {
  // Создаем валидный Address через конструктор (Country, Oblast, City, Street,
  // House, Apt, Zip)
  Address addr("Belarus", "Minsk obl", "Minsk", "Lenina", 1, 15, "220030");
  ContactInfo info("+375291234567", "test@example.com", addr);

  EXPECT_NO_THROW((void)info.GetAddress());
  // Проверка через ToString() может зависеть от формата, но базово:
  EXPECT_EQ(info.GetAddress().GetCity(), "Minsk");
}

TEST(ContactInfoTest, Constructor_ValidData_WithAddressString_ParsedCorrectly) {
  // ВАЖНО: Формат строки должен соответствовать Address::ParseFromString (через
  // точку с запятой) Country;Oblast;City;Street;House;Apartment;PostalCode
  std::string valid_addr_str =
      "Belarus;Minsk Region;Minsk;Pobediteley;10;5;220004";

  ContactInfo info("+375291234567", "test@example.com", valid_addr_str);

  ASSERT_NO_THROW((void)info.GetAddress());
  EXPECT_EQ(info.GetAddress().GetStreet(), "Pobediteley");
  EXPECT_EQ(info.GetAddress().GetHouseNumber(), 10);
}

TEST(ContactInfoTest, Constructor_InvalidAddressString_ThrowsException) {
  // Неверный формат строки (нет разделителей или мало частей)
  std::string bad_addr_str = "Minsk, Lenina, 1";
  // Address кидает AddressException, ContactInfo его не ловит (по идее),
  // поэтому ожидаем AddressException. Если ContactInfo оборачивает - поменяй на
  // ContactInfoException.
  EXPECT_THROW(ContactInfo("+375291234567", "test@example.com", bad_addr_str),
               AddressException);
}

TEST(ContactInfoTest, Constructor_EmptyAddressString_CreatesNullopt) {
  ContactInfo info("+375291234567", "test@example.com", "   ");
  EXPECT_THROW(info.GetAddress(), ContactInfoException);
}

// Тесты Валидации Телефона

TEST(ContactInfoTest, Phone_Normalization_BelarusPrefix) {
  ContactInfo info("80291234567", "test@example.com", "");
  EXPECT_EQ(info.GetPhoneNumber(), "+375291234567");
}

TEST(ContactInfoTest, Phone_Normalization_ComplexFormat) {
  ContactInfo info("80 (29) 123-45-67", "test@example.com", "");
  EXPECT_EQ(info.GetPhoneNumber(), "+375291234567");
}

TEST(ContactInfoTest, Phone_InvalidFormat_ThrowsException) {
  EXPECT_THROW(ContactInfo("123", "a@b.c", ""), ContactInfoException);
  EXPECT_THROW(ContactInfo("+11234567890", "a@b.c", ""), ContactInfoException);
  EXPECT_THROW(ContactInfo("", "a@b.c", ""), ContactInfoException);
}

TEST(ContactInfoTest, SetPhoneNumber_Validates) {
  ContactInfo info("+375291111111", "test@example.com", "");
  info.SetPhoneNumber("8044 777-88-99");
  EXPECT_EQ(info.GetPhoneNumber(), "+375447778899");
}

TEST(ContactInfoTest, SetPhoneNumber_Invalid_ThrowsException) {
  ContactInfo info("+375291111111", "test@example.com", "");
  EXPECT_THROW(info.SetPhoneNumber("invalid"), ContactInfoException);
  EXPECT_EQ(info.GetPhoneNumber(), "+375291111111");
}

// Тесты Валидации Email

TEST(ContactInfoTest, Email_ValidFormats) {
  EXPECT_NO_THROW(ContactInfo("+375291111111", "user@domain.com", ""));
  EXPECT_NO_THROW(ContactInfo("+375291111111", "u.name@sub.domain.org", ""));
}

TEST(ContactInfoTest, Email_Normalization_Trims) {
  ContactInfo info("+375291111111", "  test@example.com  ", "");
  EXPECT_EQ(info.GetEmail(), "test@example.com");
}

TEST(ContactInfoTest, Email_InvalidFormats) {
  EXPECT_THROW(ContactInfo("+375291111111", "plain", ""), ContactInfoException);
  EXPECT_THROW(ContactInfo("+375291111111", "@domain.com", ""),
               ContactInfoException);
}

// Тесты Адреса (Интеграция с Address)

TEST(ContactInfoTest, SetAddress_FromString_Valid) {
  ContactInfo info("+375291111111", "test@example.com", "");
  // Используем правильный разделитель ;
  info.SetAddress("Belarus;Minsk Reg;Minsk;Main St;1;2;220000");
  EXPECT_NO_THROW(info.GetAddress());
  EXPECT_EQ(info.GetAddress().GetStreet(), "Main St");
}

TEST(ContactInfoTest, SetAddress_FromObject_Valid) {
  ContactInfo info("+375291111111", "test@example.com", "");
  Address new_addr("Belarus", "Grodno Obl", "Grodno", "Mira", 5);
  info.SetAddress(new_addr);
  EXPECT_EQ(info.GetAddress().GetCity(), "Grodno");
}

TEST(ContactInfoTest, GetAddressString_Empty_ThrowsException) {
  ContactInfo info("+375291111111", "test@example.com", "");
  EXPECT_THROW(info.GetAddressString(), ContactInfoException);
}
