//
// Created by Dmitry Burbas on 15/11/2025.
//
#include <gtest/gtest.h>

#include <string>

#include "exceptions/components_exceptions.h"
#include "value_structures/date/date.h"
// TODO: поменять названия тестов
TEST(DateTest, FromIntsValidStoresFields) {
  Date d(1, 1, 1800);
  EXPECT_EQ(d.GetDay(), 1);
  EXPECT_EQ(d.GetMonth(), 1);
  EXPECT_EQ(d.GetYear(), 1800);
}

TEST(DateTest, ToStringFormatsLeadingZeros) {
  Date d(3, 4, 2020);
  EXPECT_EQ(d.ToString(), "03.04.2020");
}

TEST(DateTest, FromStringParsesAndNormalizesViaToString) {
  Date d(std::string("03.04.2020"));
  EXPECT_EQ(d.GetDay(), 3);
  EXPECT_EQ(d.GetMonth(), 4);
  EXPECT_EQ(d.GetYear(), 2020);
  EXPECT_EQ(d.ToString(), "03.04.2020");
}

TEST(DateTest, FromStringAllowsSingleDigitDayMonth) {
  Date d(std::string("3.4.2020"));
  EXPECT_EQ(d.ToString(), "03.04.2020");
}

// Validate()

TEST(DateTest, FromIntsYearTooSmallThrows) {
  EXPECT_THROW((void)Date(1, 1, 1799), DateException);
}

TEST(DateTest, FromIntsYearTooLargeThrows) {
  EXPECT_THROW((void)Date(1, 1, 2101), DateException);
}

TEST(DateTest, FromIntsYearBoundsInclusiveDoNotThrow) {
  EXPECT_NO_THROW((void)Date(31, 12, 2100));
  EXPECT_NO_THROW((void)Date(1, 1, 1800));
}

// Validate()

TEST(DateTest, FromIntsMonthTooSmallThrows) {
  EXPECT_THROW((void)Date(1, 0, 2020), DateException);
}

TEST(DateTest, FromIntsMonthTooLargeThrows) {
  EXPECT_THROW((void)Date(1, 13, 2020), DateException);
}

// Validate()

TEST(DateTest, FromIntsDayLessThan1Throws) {
  EXPECT_THROW((void)Date(0, 1, 2020), DateException);
}

TEST(DateTest, FromIntsDayTooLargeForMonthThrows) {
  EXPECT_THROW((void)Date(31, 4, 2020), DateException);

  EXPECT_THROW((void)Date(32, 1, 2020), DateException);
}

// Validate()

TEST(DateTest, FromIntsFeb29LeapYearAllowed) {
  EXPECT_NO_THROW((void)Date(29, 2, 2000));
  EXPECT_NO_THROW((void)Date(29, 2, 2004));
}

TEST(DateTest, FromIntsFeb29NonLeapYearThrows) {
  EXPECT_THROW((void)Date(29, 2, 1900), DateException);
  EXPECT_THROW((void)Date(29, 2, 2001), DateException);
}

TEST(DateTest, FromIntsFeb30AlwaysThrows) {
  EXPECT_THROW((void)Date(30, 2, 2000), DateException);
  EXPECT_THROW((void)Date(30, 2, 2001), DateException);
}

// SetFullDate()

TEST(DateTest, SetFullDateValidUpdatesState) {
  Date d(1, 1, 2020);
  d.SetFullDate(31, 12, 2021);
  EXPECT_EQ(d.ToString(), "31.12.2021");
}

TEST(DateTest, SetFullDateInvalidDoesNotChangeState) {
  Date d(10, 10, 2020);
  const std::string before = d.ToString();

  try {
    d.SetFullDate(31, 4, 2020);
    FAIL() << "Expected DateException";
  } catch (const DateException&) {
  }

  EXPECT_EQ(d.ToString(), before);
}

// ParseFromString()

TEST(DateTest, FromStringInvalidDelimiterThrows) {
  EXPECT_THROW((void)Date(std::string("01-01-2020")), DateException);
}

TEST(DateTest, FromStringIncompleteThrows) {
  EXPECT_THROW((void)Date(std::string("01.01")), DateException);
}

TEST(DateTest, FromStringExtraCharactersAfterDateThrows) {
  EXPECT_THROW((void)Date(std::string("01.01.2020abc")), DateException);
}

// ==, !=, <, <=, >, >=

TEST(DateTest, EqualityAndInequalityWork) {
  Date a(1, 1, 2020);
  Date b(1, 1, 2020);
  Date c(2, 1, 2020);

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);

  EXPECT_FALSE(a == c);
  EXPECT_TRUE(a != c);
}

TEST(DateTest, LessThanOrdersByYearThenMonthThenDay) {
  Date d1(10, 5, 2020);
  Date d2(10, 5, 2021);
  EXPECT_TRUE(d1 < d2);
  EXPECT_FALSE(d2 < d1);

  Date m1(10, 5, 2020);
  Date m2(10, 6, 2020);
  EXPECT_TRUE(m1 < m2);
  EXPECT_FALSE(m2 < m1);

  Date a(10, 5, 2020);
  Date b(11, 5, 2020);
  EXPECT_TRUE(a < b);
  EXPECT_FALSE(b < a);
}

TEST(DateTest, LessThanReturnsFalseForEqualDates) {
  Date a(1, 1, 2020);
  Date b(1, 1, 2020);
  EXPECT_FALSE(a < b);
  EXPECT_FALSE(b < a);
}

TEST(DateTest, LessEqualWorksForEqualAndLess) {
  Date a(1, 1, 2020);
  Date b(1, 1, 2020);
  Date c(2, 1, 2020);

  EXPECT_TRUE(a <= b);
  EXPECT_TRUE(a <= c);
  EXPECT_FALSE(c <= a);
}

TEST(DateTest, GreaterWorksViaLessEqual) {
  Date a(1, 1, 2020);
  Date b(2, 1, 2020);

  EXPECT_TRUE(b > a);
  EXPECT_FALSE(a > b);
  EXPECT_FALSE(a > a);
}

TEST(DateTest, GreaterEqualWorksViaLess) {
  Date a(1, 1, 2020);
  Date b(1, 1, 2020);
  Date c(2, 1, 2020);

  EXPECT_TRUE(a >= b);
  EXPECT_FALSE(a >= c);
  EXPECT_TRUE(c >= a);
}

TEST(DateTest, ComparisonsAreConsistentTotalOrderingSanity) {
  Date a(31, 12, 2019);
  Date b(1, 1, 2020);
  Date c(2, 1, 2020);

  EXPECT_TRUE(a < b);
  EXPECT_TRUE(b < c);
  EXPECT_TRUE(a < c);

  EXPECT_TRUE(c > b);
  EXPECT_TRUE(c >= b);
  EXPECT_TRUE(b <= c);

  EXPECT_FALSE(b < a);
  EXPECT_FALSE(b > c);
}

TEST(DateTest, ComparisonsWorkAcrossDifferentFields) {
  Date jan(15, 1, 2020);
  Date feb(1, 2, 2020);
  EXPECT_TRUE(jan < feb);

  Date y1(1, 3, 2010);
  Date y2(1, 3, 2011);
  EXPECT_TRUE(y1 < y2);
  EXPECT_TRUE(y2 > y1);
}
