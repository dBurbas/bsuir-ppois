/**
 * @file contact_info.h
 * @brief Contact information model with validation and normalization.
 * @author Dmitry Burbas
 * @date 11/11/2025
 */
#ifndef CONTACT_INFO_H
#define CONTACT_INFO_H

#include <optional>
#include <string>

#include "../address/address.h"
#include "../utility_functions/utility_functions.h"
/**
 * @class ContactInfo
 * @brief Stores and validates basic contact information
 * @details Holds a normalized phone number, an email address and an optional
 * postal Address instance. All phone numbers and emails are validated and
 * normalized during construction and modification.
 */
class ContactInfo {
 public:
  /**
   * @brief Constructs a ContactInfo object with phone, email, and optional
   * address
   * @param phone_number Phone number to be normalized and validated (Belarusian
   * format +375*********)
   * @param email Email address to be normalized and validated (default: empty
   * string)
   * @param address Optional Address object (default: std::nullopt)
   * @throws ContactInfoException if phone number or email format is invalid
   * @details Normalizes phone by removing spaces, dashes, parentheses and
   * converts "80" prefix to "+375". Email is trimmed of leading/trailing
   * whitespace.
   */
  explicit ContactInfo(const std::string& phone_number,
                       const std::string& email = "",
                       std::optional<Address> address = std::nullopt);
  /**
   * @brief Constructs a ContactInfo object with phone, email, and address
   * string
   * @param phone_number Phone number to be normalized and validated
   * @param email Email address to be normalized and validated
   * @param address_str Address as string (default: empty string)
   * @throws ContactInfoException if phone number or email format is invalid
   * @details Delegates to the main constructor. If address_str is empty or
   * whitespace-only, address is set to std::nullopt.
   */
  explicit ContactInfo(const std::string& phone_number,
                       const std::string& email,
                       const std::string& address_str = "")
      : ContactInfo(phone_number, email,
                    Utility::Trim(address_str).empty()
                        ? std::nullopt
                        : std::optional<Address>(address_str)) {}

  /**
   * @brief Default destructor
   */
  ~ContactInfo() = default;

  /**
   * @brief Sets a new email address with validation and normalization
   * @param email New email address
   * @throws ContactInfoException if email format is invalid
   * @details Trims whitespace and validates against email regex pattern
   */
  void SetEmail(const std::string& email) {
    const std::string normalized = NormalizeEmail(email);
    ValidateEmail(normalized);
    email_ = normalized;
  }

  /**
   * @brief Sets a new phone number with validation and normalization
   * @param phone_number New phone number
   * @throws ContactInfoException if phone number format is invalid or empty
   * @details Removes formatting characters and converts to +375********* format
   */
  void SetPhoneNumber(const std::string& phone_number) {
    const std::string normalized = NormalizePhone(phone_number);
    ValidatePhone(normalized);
    phone_number_ = normalized;
  }

  /**
   * @brief Sets a new address from string
   * @param address Address string to create Address object
   * @details Creates a new Address object from the provided string
   */
  void SetAddress(const std::string& address) { address_ = Address(address); }

  /**
   * @brief Sets a new address from an Address object
   * @param address Address object to set
   * @details Copies an address object to this contact info
   */
  void SetAddress(const Address& address) { address_ = address; }

  /**
   * @brief Gets the current email address
   * @return Email address as string
   */
  [[nodiscard]] std::string GetEmail() const { return email_; }

  /**
   * @brief Gets the current phone number
   * @return Phone number as string in normalized format (+375*********)
   */
  [[nodiscard]] std::string GetPhoneNumber() const { return phone_number_; }

  /**
   * @brief Gets the address as a formatted string
   * @return Address string representation
   * @throws ContactInfoException if address is not set (std::nullopt)
   * @details Calls ToString() method on the Address object
   */
  [[nodiscard]] std::string GetAddressString() const;

  /**
   * @brief Gets the Address object
   * @return Address object
   * @throws ContactInfoException if address is not set (std::nullopt)
   */
  [[nodiscard]] Address GetAddress() const;

 private:
  std::string email_;  ///< Normalized email address
  std::string
      phone_number_;  ///< Normalized phone number in +375********* format
  std::optional<Address> address_;  ///< Optional postal address

  /**
   * @brief Validates email format using regex
   * @param email Email string to validate
   * @throws ContactInfoException if email doesn't match pattern
   * @details Uses regex pattern: (\w+)(\.|-|_)?(\w*)@(\w+)(\.\w+)+
   */
  static void ValidateEmail(const std::string& email);

  /**
   * @brief Normalizes email by trimming whitespace
   * @param email Email string to normalize
   * @return Trimmed email string
   */
  static std::string NormalizeEmail(std::string email);

  /**
   * @brief Validates phone number format using regex
   * @param phone Phone string to validate
   * @throws ContactInfoException if phone is empty or doesn't match
   * +375********* format
   * @details Validates against regex pattern: ^\+375\d{9}$ (validates only
   * belarusian numbers because project is regionally oriented)
   */
  static void ValidatePhone(const std::string& phone);

  /**
   * @brief Normalizes phone number by removing formatting and converting prefix
   * @param phone Phone string to normalize
   * @return Normalized phone string in +375********* format
   * @details Removes spaces, dashes, and parentheses. Converts "80" prefix to
   * "+375"
   */
  static std::string NormalizePhone(std::string phone);
};

#endif  // CONTACT_INFO_H
