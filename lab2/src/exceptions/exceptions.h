/*! @file exceptions.h
 *  @brief Заголовочный файл с описанием иерархии классов исключений
 *  @details Содержит объявление базового класса DeanOfficeException и
 * специализированных классов исключений для различных ошибок в системе
 * деканата.
 */
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
#include <string>
/**
 * @class DeanOfficeException
 * @brief Base class for all exceptions in the system
 * @details Inherits from std::exception and provides basic functionality
 * for storing and displaying error messages. All custom exceptions in the
 * deanery system should inherit from this class.
 */
class DeanOfficeException : public std::exception {
 public:
  /**
   * @brief Constructor with error message
   * @param message Error message (as C-string)
   */
  explicit DeanOfficeException(const char* message) : message_(message) {}

  /**
   * @brief Constructor with error message
   * @param message Error message (as std::string)
   */
  explicit DeanOfficeException(const std::string& message)
      : message_(message) {}

  /**
   * @brief Get the error message
   * @return Pointer to C-string with error message
   */
  const char* what() const noexcept override { return message_.c_str(); }

 private:
  std::string message_;  ///< Error message
};

/**
 * @class DateException
 * @brief Exception class for invalid date operations
 * @details Thrown when date validation fails, including invalid day/month/year
 * combinations, out-of-range values (year not in [1800, 2100], month not in [1,
 * 12]), invalid day for given month (for example February 30), or incorrect
 * date string format.
 */
class DateException : public DeanOfficeException {
 public:
  /**
   * @brief Constructor with error message
   * @param message Error message (as C-string)
   */
  explicit DateException(const char* message) : DeanOfficeException(message) {}

  /**
   * @brief Constructor with error message
   * @param message Error message (as std::string)
   */
  explicit DateException(const std::string& message)
      : DeanOfficeException(message) {}
};

/**
 * @class PersonalInfoException
 * @brief Exception class for invalid personal information
 * @details Thrown when validation of personal information fails, such as
 * invalid name format (empty names, invalid characters, names not starting
 * with uppercase letter), or any other constraint
 * violations related to personal data fields.
 */
class PersonalInfoException : public DeanOfficeException {
 public:
  /**
   * @brief Constructor with error message
   * @param message Error message (as C-string)
   */
  explicit PersonalInfoException(const char* message)
      : DeanOfficeException(message) {}
  /**
   * @brief Constructor with error message
   * @param message Error message (as std::string)
   */
  explicit PersonalInfoException(const std::string& message)
      : DeanOfficeException(message) {}
};

/**
 * @class ContactInfoException
 * @brief Exception class for invalid contact information
 * @details Thrown when validation of contact information fails, including
 * invalid phone number format (not matching +375********* pattern), invalid
 * email format (not matching email regex pattern), empty required fields,
 * or when attempting to access unset optional address field.
 */
class ContactInfoException : public DeanOfficeException {
 public:
  /**
   * @brief Constructor with error message
   * @param message Error message (as C-string)
   */
  explicit ContactInfoException(const char* message)
      : DeanOfficeException(message) {}

  /**
   * @brief Constructor with error message
   * @param message Error message (as std::string)
   */
  explicit ContactInfoException(const std::string& message)
      : DeanOfficeException(message) {}
};

/**
 * @class AddressException
 * @brief Exception class for invalid address information
 * @details Thrown when address validation or parsing fails, such as
 * invalid address string format, empty address components where required,
 * or any other constraint violations related to postal address fields
 * (street, city, postal code, etc.).
 */
class AddressException : public DeanOfficeException {
 public:
  /**
   * @brief Constructor with error message
   * @param message Error message (as C-string)
   */
  explicit AddressException(const char* message)
      : DeanOfficeException(message) {}

  /**
   * @brief Constructor with error message
   * @param message Error message (as std::string)
   */
  explicit AddressException(const std::string& message)
      : DeanOfficeException(message) {}
};

#endif  // EXCEPTIONS_H
