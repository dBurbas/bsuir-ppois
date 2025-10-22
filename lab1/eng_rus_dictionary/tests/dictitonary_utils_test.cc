#include <gtest/gtest.h>
#include "../src/dictionary_utils/dictionary_utils.h"

TEST(UtilsTest, CheckIsEnglishWork) {
    EXPECT_EQ(true,utils::IsEnglishWord("work"));
    EXPECT_EQ(false,utils::IsEnglishWord("работа"));
}
TEST(UtilsTest, IsEnglishWordEmptyString) {
    EXPECT_FALSE(utils::IsEnglishWord(""));
}
TEST(UtilsTest, IsEnglishWordWithHyphen) {
    EXPECT_TRUE(utils::IsEnglishWord("test-word"));
}
TEST(UtilsTest, IsEnglishWordWithNumbers) {
    EXPECT_FALSE(utils::IsEnglishWord("test123"));
}
TEST(UtilsTest, CheckIsRussianWork) {
    EXPECT_EQ(true,utils::IsRussianWord("слово"));
    EXPECT_EQ(false,utils::IsRussianWord("word"));
}
TEST(UtilsTest, IsRussianWordEmptyString) {
    EXPECT_FALSE(utils::IsRussianWord(""));
}
TEST(UtilsTest, IsRussianWordWithHyphen) {
    EXPECT_TRUE(utils::IsRussianWord("тест-слово"));
}
TEST(UtilsTest, IsRussianWordWithNumbers) {
    EXPECT_FALSE(utils::IsRussianWord("тест123"));
}
TEST(UtilsTest, CheckIsParsingWork) {
    std::string eng,rus;
    utils::ParseWordPair(eng, rus, "word:слово");
    EXPECT_EQ("word", eng);
    EXPECT_EQ("слово", rus);
}
TEST(UtilsTest, ParseWordPairMultipleDelimiters) {
    std::string eng, rus;
    utils::ParseWordPair(eng, rus, "test:слово:лишнее");
    EXPECT_EQ("test", eng);
    EXPECT_EQ("слово", rus);
}
TEST(UtilsTest, ParseWordPairEmptyString) {
    std::string eng, rus;
    EXPECT_THROW(utils::ParseWordPair(eng, rus, ""),std::invalid_argument);
}
TEST(UtilsTest, ParseWordPairOnlyDelimeter) {
    std::string eng, rus;
    EXPECT_THROW(utils::ParseWordPair(eng, rus, ":"),std::invalid_argument);
}
