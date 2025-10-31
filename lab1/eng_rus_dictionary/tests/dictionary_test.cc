//
//  dictionary_tests.cc
//  eng_rus_dictionary
//
//  Created by Dmitry Burbas on 17/10/2025.
//

#include "../src/dictionary/dictionary.h"
#include <fstream>
#include <gtest/gtest.h>
#define DICTIONARY_INPUT_FILE_PATH "input/input_dictionary.txt"
#define DICTIONARY_INPUT_EMPTY_FILE_PATH "input/input_dictionary_empty.txt"
#define DICTIONARY_OUTPUT_FILE_PATH "output/output_dictionary.txt"

class DictionaryFixture : public ::testing::Test {
protected:
  void SetUp() override {
    test_dict += "test:тест";
    test_dict += "food:еда";
    test_dict += "apple:яблоко";
    test_dict += "mushroom:гриб";
    test_dict += "programmer:программист";
    test_dict +=
        "Object-Oriented-Programming:Объектно-Ориентированное-Программирование";
    test_dict += "mine:добывать";
    test_dict += "craft:ремесло";
  }
  void TearDown() override { test_dict.Clear(); }

  Dictionary test_dict;
};

TEST(DictionaryNonFixture, IsEmptyEmptyDictionary) {
  Dictionary dict;
  ASSERT_TRUE(dict.IsEmpty());
}
TEST(DictionaryNonFixture, GetSizeEmptyDictionary) {
  Dictionary dict;
  ASSERT_EQ(dict.GetSize(), 0);
}
TEST_F(DictionaryFixture, IsEmptyDictionary) {
  ASSERT_FALSE(test_dict.IsEmpty());
}
TEST_F(DictionaryFixture, GetSizeDictionary) {
  ASSERT_EQ(test_dict.GetSize(), 8);
}
TEST_F(DictionaryFixture, ClearWorks) {
  test_dict.Clear();
  ASSERT_TRUE(test_dict.IsEmpty());
}
TEST_F(DictionaryFixture, FindOperatorExisting) {
  ASSERT_EQ(test_dict["test"], "тест");
  ASSERT_EQ(test_dict["mine"], "добывать");
  ASSERT_EQ(test_dict["craft"], "ремесло");
}
TEST_F(DictionaryFixture, FindOperatorNonExisting) {
  ASSERT_EQ(test_dict["macbook"], "");
  ASSERT_EQ(test_dict["monday"], "");
  ASSERT_EQ(test_dict["frost"], "");
}
TEST_F(DictionaryFixture, ConstFindOperatorNonExisting) {
  const Dictionary const_dict(test_dict);
  ASSERT_THROW(const_dict["macbook"], std::out_of_range);
  ASSERT_THROW(const_dict["monday"], std::out_of_range);
  ASSERT_THROW(const_dict["frost"], std::out_of_range);
}
TEST_F(DictionaryFixture, ChangeValueOperatorExisting) {
  test_dict["test"] = "тестировать";
  ASSERT_EQ(test_dict["test"], "тестировать");
  test_dict["mine"] = "выкапывать";
  ASSERT_EQ(test_dict["mine"], "выкапывать");
  test_dict["craft"] = "судно";
  ASSERT_EQ(test_dict["craft"], "судно");
}
TEST_F(DictionaryFixture, ChangeValueOperatorNonExisting) {
  test_dict["macbook"] = "макбук";
  ASSERT_EQ(test_dict["macbook"], "макбук");
  test_dict["monday"] = "понедельник";
  ASSERT_NE(test_dict["monday"], "день-бездельник");
  ASSERT_EQ(test_dict["monday"], "понедельник");
  test_dict["frost"] = "мороз";
  ASSERT_EQ(test_dict["frost"], "мороз");
}
TEST_F(DictionaryFixture, AddOperatorSTLPair) {
  test_dict += std::make_pair("lucky", "удача");
  ASSERT_EQ(test_dict["lucky"], "удача");
  test_dict += std::make_pair("encapsulation", "инкапсуляция");
  ASSERT_EQ(test_dict["encapsulation"], "инкапсуляция");
  test_dict += std::make_pair("inheritance", "наследование");
  ASSERT_EQ(test_dict["inheritance"], "наследование");
}
TEST_F(DictionaryFixture, AddOperatorSTLString) {
  ASSERT_EQ(test_dict.GetSize(), 8);
  test_dict += std::string("lucky:удача");
  ASSERT_EQ(test_dict["lucky"], "удача");
  test_dict += std::string("encapsulation:инкапсуляция");
  ASSERT_EQ(test_dict["encapsulation"], "инкапсуляция");
  test_dict += std::string("inheritance:наследование");
  ASSERT_EQ(test_dict["inheritance"], "наследование");
  ASSERT_EQ(test_dict.GetSize(), 11);
}
TEST_F(DictionaryFixture, AddOperatorCString) {
  ASSERT_EQ(test_dict.GetSize(), 8);
  test_dict += "lucky:удача";
  ASSERT_EQ(test_dict["lucky"], "удача");
  test_dict += "encapsulation:инкапсуляция";
  ASSERT_EQ(test_dict["encapsulation"], "инкапсуляция");
  test_dict += "inheritance:наследование";
  ASSERT_EQ(test_dict["inheritance"], "наследование");
  ASSERT_EQ(test_dict.GetSize(), 11);
}
TEST_F(DictionaryFixture, AddOperatorExtraWord) {
  ASSERT_EQ(test_dict.GetSize(), 8);
  test_dict += "lucky:удача:лаки";
  ASSERT_EQ(test_dict["lucky"], "удача");
  test_dict += "inheritance:наследование:наследство";
  ASSERT_EQ(test_dict["inheritance"], "наследование");
  ASSERT_EQ(test_dict.GetSize(), 10);
}
TEST_F(DictionaryFixture, EraseOperatorSTLString) {
  ASSERT_EQ(test_dict.GetSize(), 8);
  test_dict -= std::string("test");
  ASSERT_EQ(test_dict.GetSize(), 7);
  test_dict -= std::string("food");
  ASSERT_EQ(test_dict.GetSize(), 6);
  test_dict -= std::string("apple");
  ASSERT_EQ(test_dict.GetSize(), 5);
}
TEST_F(DictionaryFixture, EraseOperatorCString) {
  ASSERT_EQ(test_dict.GetSize(), 8);
  test_dict -= "test";
  ASSERT_EQ(test_dict.GetSize(), 7);
  test_dict -= "food";
  ASSERT_EQ(test_dict.GetSize(), 6);
  test_dict -= "apple";
  ASSERT_EQ(test_dict.GetSize(), 5);
}
TEST_F(DictionaryFixture, EqualityOperatorEqualDictionaries) {
  Dictionary dict_to_compare;
  dict_to_compare += "test:тест";
  dict_to_compare += "food:еда";
  dict_to_compare += "apple:яблоко";
  dict_to_compare += "mushroom:гриб";
  dict_to_compare += "programmer:программист";
  dict_to_compare +=
      "Object-Oriented-Programming:Объектно-Ориентированное-Программирование";
  dict_to_compare += "mine:добывать";
  dict_to_compare += "craft:ремесло";
  EXPECT_TRUE(test_dict == dict_to_compare);
  dict_to_compare.Clear();
}
TEST_F(DictionaryFixture, EqualityOperatorNonEqualDictionaries) {
  Dictionary dict_to_compare;
  EXPECT_FALSE(test_dict == dict_to_compare);
  dict_to_compare += "test:тест";
  dict_to_compare += "food:еда";
  dict_to_compare += "apple:яблоко";
  dict_to_compare += "mushroom:гриб";
  EXPECT_FALSE(test_dict == dict_to_compare);
  dict_to_compare += "programmer:программист";
  dict_to_compare +=
      "Object-Oriented-Programming:Объектно-Ориентированное-Программирование";
  dict_to_compare += "mine:добывать";
  EXPECT_FALSE(test_dict == dict_to_compare);
  dict_to_compare.Clear();
}
TEST_F(DictionaryFixture, UnequalityOperatorEqualDictionaries) {
  Dictionary dict_to_compare;
  dict_to_compare += "test:тест";
  dict_to_compare += "food:еда";
  dict_to_compare += "apple:яблоко";
  dict_to_compare += "mushroom:гриб";
  dict_to_compare += "programmer:программист";
  dict_to_compare +=
      "Object-Oriented-Programming:Объектно-Ориентированное-Программирование";
  dict_to_compare += "mine:добывать";
  dict_to_compare += "craft:ремесло";
  EXPECT_FALSE(test_dict != dict_to_compare);
  dict_to_compare.Clear();
}
TEST_F(DictionaryFixture, UnequalityOperatorNonEqualDictionaries) {
  Dictionary dict_to_compare;
  EXPECT_TRUE(test_dict != dict_to_compare);
  dict_to_compare += "test:тест";
  dict_to_compare += "food:еда";
  dict_to_compare += "apple:яблоко";
  EXPECT_TRUE(test_dict != dict_to_compare);
  dict_to_compare += "mushroom:гриб";
  dict_to_compare += "programmer:программист";
  dict_to_compare += "Object-Oriented-Programming:"
                     "Объектно-Ориентированное-Программирование";
  dict_to_compare += "mine:добывать";
  EXPECT_TRUE(test_dict != dict_to_compare);
  dict_to_compare.Clear();
}
TEST_F(DictionaryFixture, CopyConstructor) {
  Dictionary dict(test_dict);
  ASSERT_TRUE(dict == test_dict);
  dict.Clear();
}
TEST_F(DictionaryFixture, CopyAssignmentOperatorNonEmpty) {
  Dictionary dict;
  dict = test_dict;
  ASSERT_TRUE(dict == test_dict);
  dict.Clear();
}
TEST_F(DictionaryFixture, CopyAssignmentOperatorEmpty) {
  Dictionary dict;
  test_dict = dict;
  ASSERT_TRUE(dict == test_dict);
  ASSERT_TRUE(test_dict.IsEmpty());
}
TEST_F(DictionaryFixture, InputOperator) {
  Dictionary dict;
  std::ifstream text_file(DICTIONARY_INPUT_FILE_PATH);
  if (!text_file) {
    throw std::runtime_error("Error: cannot open file");
  }
  text_file >> dict;
  text_file.close();
  ASSERT_TRUE(dict == test_dict);
}
TEST_F(DictionaryFixture, OutputOperatorInFile) {
  std::ofstream text_file(DICTIONARY_OUTPUT_FILE_PATH);
  if (!text_file) {
    throw std::runtime_error("Error: cannot open file");
  }
  text_file << test_dict;
  text_file.close();
}
TEST_F(DictionaryFixture, LoadFromFileNonEmptyFile) {
  Dictionary dict;
  ASSERT_TRUE(dict.LoadFromFile(DICTIONARY_INPUT_FILE_PATH));
  ASSERT_TRUE(dict == test_dict);
}

TEST(DictionaryNonFixture, LoadFromFileEmptyFile) {
  Dictionary dict;
  ASSERT_TRUE(dict.LoadFromFile(DICTIONARY_INPUT_EMPTY_FILE_PATH));
  ASSERT_TRUE(dict.IsEmpty());
  std::ifstream empty_file(DICTIONARY_INPUT_EMPTY_FILE_PATH);
  if (!empty_file) {
    throw std::runtime_error("Error: cannot open file");
  }
  empty_file >> dict;
  empty_file.close();
  ASSERT_TRUE(dict.IsEmpty());
}
