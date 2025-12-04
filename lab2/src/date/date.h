/**
 * @file date.h
 * @brief Date representation class with validation and formatting
 * @author Dmitry Burbas
 * @date 16/11/2025
 */
#ifndef DATE_H
#define DATE_H
#include <string>

/**
 * @class Date
 * @brief Represents a calendar date with validation and comparison operations
 * @details Supports dates from 1800 to 2100 with DD.MM.YYYY format.
 * Validates day, month, year constraints including leap years.
 */
class Date {
 public:
  /**
   * @brief Constructs a Date object with day, month, and year
   * @param day Day of the month (1-31 depending on month)
   * @param month Month of the year (1-12)
   * @param year Year (1800-2100)
   * @throws DateException if any component is invalid or date doesn't exist
   * @details Validates date including leap year calculation for February
   */
  Date(const int day, const int month, const int year)
      : day_(day), month_(month), year_(year) {
    Validate(day, month, year);
  }
  /**
   * @brief Constructs a Date object from string representation
   * @param date Date string in DD.MM.YYYY format
   * @throws DateException if format is invalid or date components are out of
   * range
   * @details Delegates to ParseFromString() then main constructor
   */
  explicit Date(const std::string& date) : Date(ParseFromString(date)) {}
  /**
   * @brief Default copy constructor
   */
  Date(const Date&) = default;

  /**
   * @brief Default move constructor
   */
  Date(Date&&) = default;

  /**
   * @brief Default copy assignment operator
   * @return Reference to this Date object
   */
  Date& operator=(const Date&) = default;

  /**
   * @brief Default move assignment operator
   * @return Reference to this Date object
   */
  Date& operator=(Date&&) = default;

  /**
   * @brief Default destructor
   */
  ~Date() = default;

  /**
   * @brief Sets all date components at once with validation
   * @param day Day of the month (1-31 depending on month)
   * @param month Month of the year (1-12)
   * @param year Year (1800-2100)
   * @throws DateException if any component is invalid
   * @details Validates the entire date before updating internal state
   */
  void SetFullDate(int day, int month, int year);

  /**
   * @brief Gets the day component
   * @return Day of the month (1-31)
   */
  [[nodiscard]] int GetDay() const { return day_; }

  /**
   * @brief Gets the month component
   * @return Month of the year (1-12)
   */
  [[nodiscard]] int GetMonth() const { return month_; }

  /**
   * @brief Gets the year component
   * @return Year (1800-2100)
   */
  [[nodiscard]] int GetYear() const { return year_; }

  /**
   * @brief Converts date to string representation
   * @return Date string in DD.MM.YYYY format with zero-padding
   * @details Formats single-digit days and months with leading zeros
   */
  [[nodiscard]] std::string ToString() const;

  /**
   * @brief Equality comparison operator
   * @param other Date to compare with
   * @return true if all components (day, month, year) are equal
   */
  bool operator==(const Date& other) const {
    return day_ == other.day_ && month_ == other.month_ && year_ == other.year_;
  }

  /**
   * @brief Less-than comparison operator
   * @param other Date to compare with
   * @return true if this date is chronologically before other
   * @details Compares year first, then month, then day
   */
  bool operator<(const Date& other) const {
    if (year_ != other.year_) return year_ < other.year_;
    if (month_ != other.month_) return month_ < other.month_;
    return day_ < other.day_;
  }

  /**
   * @brief Inequality comparison operator
   * @param other Date to compare with
   * @return true if dates are not equal
   */
  bool operator!=(const Date& other) const { return !(*this == other); }

  /**
   * @brief Less-than-or-equal comparison operator
   * @param other Date to compare with
   * @return true if this date is before or equal to other
   */
  bool operator<=(const Date& other) const {
    return *this < other || *this == other;
  }

  /**
   * @brief Greater-than comparison operator
   * @param other Date to compare with
   * @return true if this date is chronologically after other
   */
  bool operator>(const Date& other) const { return !(*this <= other); }

  /**
   * @brief Greater-than-or-equal comparison operator
   * @param other Date to compare with
   * @return true if this date is after or equal to other
   */
  bool operator>=(const Date& other) const { return !(*this < other); }

 private:
  static constexpr int kMinYear = 1800;        ///< Minimum valid year
  static constexpr int kMaxYear = 2100;        ///< Maximum valid year
  static constexpr char kDateDelimiter = '.';  ///< Delimiter for date format
  int day_;                                    ///< Day of the month (1-31)
  int month_;                                  ///< Month of the year (1-12)
  int year_;                                   ///< Year (1800-2100)
  // TODO:Перевести на regex если действительно нужно
  /**
   * @brief Validates date components
   * @param day Day to validate (1-31 depending on month)
   * @param month Month to validate (1-12)
   * @param year Year to validate (1800-2100)
   * @throws DateException if year is out of range [1800, 2100]
   * @throws DateException if month is out of range [1, 12]
   * @throws DateException if day is less than 1 or exceeds days in month
   * @details Checks leap years for February (29 days in leap years, 28
   * otherwise)
   */
  // TODO:перевести на Validator интерфейс
  static void Validate(int day, int month, int year);

  /**
   * @brief Parses date from string in DD.MM.YYYY format
   * @param date String to parse
   * @return Parsed Date object
   * @throws DateException if format doesn't match DD.MM.YYYY
   * @throws DateException if unexpected characters found after date
   * @details Uses '.' as delimiter and validates format strictly
   */
  static Date ParseFromString(const std::string& date);

  /**
   * @brief Determines if a year is a leap year
   * @param year Year to check
   * @return true if year is a leap year
   * @details A year is leap if divisible by 4 but not by 100, or divisible by
   * 400
   */
  static bool IsLeapYear(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
  }
};

#endif  // DATE_H
