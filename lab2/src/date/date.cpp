//
// Created by Dmitry Burbas on 13/11/2025.
//

#include "date.h"

#include <sstream>

#include "../exceptions/exceptions.h"
void Date::SetFullDate(const int day, const int month, const int year) {
  Validate(day, month, year);
  day_ = day;
  month_ = month;
  year_ = year;
}
std::string Date::ToString() const {
  auto format = [](const int val) {
    return (val < 10 ? "0" : "") + std::to_string(val);
  };
  return format(day_) + kDateDelimiter + format(month_) + kDateDelimiter +
         std::to_string(year_);
}
void Date::Validate(const int day, const int month, const int year) {
  if (year < kMinYear || year > kMaxYear)
    throw DateException("Invalid date input. Year must be from " +
                        std::to_string(kMinYear) + " to " +
                        std::to_string(kMaxYear));
  if (month < 1 || month > 12)
    throw DateException("Invalid date input. Month must be from 1 to 12");
  if (day < 1)
    throw DateException("Invalid date input. Day cannot be less than 1");

  static const int kDaysInMonth[] = {31, 28, 31, 30, 31, 30,
                                     31, 31, 30, 31, 30, 31};
  int max_day = kDaysInMonth[month - 1];
  if (month == 2 && IsLeapYear(year)) {
    max_day = 29;
  }
  if (day > max_day) {
    throw DateException(
        "Invalid date input. Day of this month cannot be greater than " +
        std::to_string(max_day));
  }
}
Date Date::ParseFromString(const std::string& date) {
  std::istringstream ss(date);
  int day, month, year;
  char delimiter1, delimiter2;
  if (!(ss >> day >> delimiter1 >> month >> delimiter2 >> year) ||
      delimiter1 != kDateDelimiter || delimiter2 != kDateDelimiter) {
    throw DateException("Invalid date format. Expected: DD.MM.YYYY");
  }
  std::string after_date;
  if (ss >> after_date) {
    throw DateException(
        "Invalid date format. Unexpected characters after date");
  }
  return {day, month, year};
}
