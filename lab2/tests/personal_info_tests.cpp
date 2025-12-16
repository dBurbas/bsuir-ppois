//
// Created by Dmitry Burbas on 15/11/2025.
//
#include <gtest/gtest.h>

#include "exceptions/components_exceptions.h"
#include "value_structures/personal_info/personal_info.h"
// TODO:Написать тесты
TEST(BirthDateTest, Construction) {
  EXPECT_THROW(PersonalInfo("Dmitry", "", "Yurievich", Date("23.08.2006")),
               PersonalInfoException);
}

// Тест конструктора и геттеров (Happy Path)
TEST(PersonalInfoTest, ConstructorAndGettersValidData) {
  std::optional<Date> birth_date = Date("15.05.2000");
  PersonalInfo info("Ivan", "Ivanov", "Ivanovich", birth_date);

  EXPECT_EQ(info.GetFirstName(), "Ivan");
  EXPECT_EQ(info.GetLastName(), "Ivanov");
  EXPECT_EQ(info.GetMiddleName(), "Ivanovich");
  EXPECT_EQ(info.GetBirthDate(), *birth_date);
  EXPECT_EQ(info.GetFullName(), "Ivanov Ivan Ivanovich");
}

// Тест конструктора без отчества и даты рождения
TEST(PersonalInfoTest, ConstructorOptionalFieldsMissing) {
  PersonalInfo info("Petr", "Petrov");

  EXPECT_EQ(info.GetFirstName(), "Petr");
  EXPECT_EQ(info.GetLastName(), "Petrov");
  EXPECT_TRUE(info.GetMiddleName().empty());
  EXPECT_EQ(info.GetFullName(), "Petrov Petr");

  // Проверка, что геттер даты кидает исключение, если даты нет
  EXPECT_THROW(info.GetBirthDate(), PersonalInfoException);
}

// Тест валидации в конструкторе (пустое имя)
TEST(PersonalInfoTest, ConstructorInvalidFirstNameThrowsException) {
  EXPECT_THROW(PersonalInfo("", "Ivanov"), PersonalInfoException);
  EXPECT_THROW(PersonalInfo("   ", "Ivanov"), PersonalInfoException);
}

// Тест валидации в конструкторе (пустая фамилия)
TEST(PersonalInfoTest, ConstructorInvalidLastNameThrowsException) {
  EXPECT_THROW(PersonalInfo("Ivan", ""), PersonalInfoException);
  EXPECT_THROW(PersonalInfo("Ivan", "   "), PersonalInfoException);
}

// Тест на автоматический тримминг пробелов
TEST(PersonalInfoTest, ConstructorTrimsWhitespaces) {
  PersonalInfo info("  Ivan  ", "  Ivanov  ", "  Ivanovich  ");

  EXPECT_EQ(info.GetFirstName(), "Ivan");
  EXPECT_EQ(info.GetLastName(), "Ivanov");
  EXPECT_EQ(info.GetMiddleName(), "Ivanovich");
}

// Тест SetFullName
TEST(PersonalInfoTest, SetFullNameValidData) {
  PersonalInfo info("Old", "Name");
  info.SetFullName("New", "Lastname", "Middle");

  EXPECT_EQ(info.GetFirstName(), "New");
  EXPECT_EQ(info.GetLastName(), "Lastname");
  EXPECT_EQ(info.GetMiddleName(), "Middle");
}

// Тест SetFullName с невалидными данными
TEST(PersonalInfoTest, SetFullNameInvalidDataThrowsException) {
  PersonalInfo info("Valid", "Name");
  EXPECT_THROW(info.SetFullName("", "Lastname"), PersonalInfoException);
  EXPECT_THROW(info.SetFullName("Firstname", ""), PersonalInfoException);
}

// Тест SetBirthDate (строковый ввод)
TEST(PersonalInfoTest, SetBirthDateValidString) {
  PersonalInfo info("Ivan", "Ivanov");
  info.SetBirthDate("01.01.1990");

  // Проверяем через сравнение с объектом Date
  EXPECT_EQ(info.GetBirthDate(), Date("01.01.1990"));
}

// Тест SetBirthDate (некорректная строка)
TEST(PersonalInfoTest, SetBirthDateInvalidStringThrowsException) {
  PersonalInfo info("Ivan", "Ivanov");
  // Предполагаем, что Date кидает DateException, а PersonalInfo оборачивает его
  EXPECT_THROW(info.SetBirthDate("invalid-date"), PersonalInfoException);
}

// Тест индивидуальных сеттеров
TEST(PersonalInfoTest, IndividualSetters) {
  PersonalInfo info("Initial", "Name");

  info.SetFirstName("  UpdatedFirst  ");
  EXPECT_EQ(info.GetFirstName(), "UpdatedFirst");

  info.SetLastName("  UpdatedLast  ");
  EXPECT_EQ(info.GetLastName(), "UpdatedLast");

  info.SetMiddleName("  UpdatedMiddle  ");
  EXPECT_EQ(info.GetMiddleName(), "UpdatedMiddle");
}

// Тест операторов сравнения (Equality)
TEST(PersonalInfoTest, OperatorsEquality) {
  std::optional<Date> date = Date("10.10.2000");
  PersonalInfo p1("A", "B", "C", date);
  PersonalInfo p2("A", "B", "C", date);
  PersonalInfo p3("X", "B", "C", date);
  PersonalInfo p4("A", "Y", "C", date);
  // Отличие в дате (один с датой, другой без)
  PersonalInfo p5("A", "B", "C");

  EXPECT_TRUE(p1 == p2);
  EXPECT_FALSE(p1 == p3);
  EXPECT_FALSE(p1 == p4);
  EXPECT_FALSE(p1 == p5);
}

// Тест операторов сравнения (Inequality)
TEST(PersonalInfoTest, OperatorsInequality) {
  PersonalInfo p1("A", "B");
  PersonalInfo p2("A", "B");
  PersonalInfo p3("A", "C");

  EXPECT_FALSE(p1 != p2);
  EXPECT_TRUE(p1 != p3);
}
