//
// Created by Dmitry Burbas on 11/11/2025.
//

#include "contact_info.h"

#include <algorithm>
#include <optional>
#include <regex>

#include "../address/address.h"
#include "../exceptions/exceptions.h"
#include "../utility_functions/utility_functions.h"

ContactInfo::ContactInfo(const std::string& phone_number,
                         const std::string& email,
                         std::optional<Address> address) {
  const std::string normalized_email = NormalizeEmail(email);
  const std::string normalized_phone = NormalizePhone(phone_number);
  ValidateEmail(normalized_email);
  ValidatePhone(normalized_phone);

  email_ = normalized_email;
  phone_number_ = normalized_phone;
  address_ = std::move(address);
}
std::string ContactInfo::GetAddressString() const {
  if (address_ == std::nullopt) {
    throw ContactInfoException("Contact info: Address is empty");
  }
  return address_->ToString();
}
Address ContactInfo::GetAddress() const {
  if (address_ == std::nullopt) {
    throw ContactInfoException("Contact info: Address is empty");
  }
  return *address_;
}
void ContactInfo::ValidateEmail(const std::string& email) {
  static const std::regex pattern(R"((\w+)(\.|-|_)?(\w*)@(\w+)(\.\w+)+)");
  if (!std::regex_match(email, pattern)) {
    throw ContactInfoException("Contact info error: Invalid email format");
  }
}
std::string ContactInfo::NormalizeEmail(std::string email) {
  email = Utility::Trim(email);
  return email;
}
void ContactInfo::ValidatePhone(const std::string& phone) {
  if (phone.empty())
    throw ContactInfoException("Contact info error: Phone is required");
  static const std::regex pattern(R"(^\+375\d{9}$)");
  if (!std::regex_match(phone, pattern)) {
    throw ContactInfoException(
        "Contact info error: Invalid phone number format");
  }
}

std::string ContactInfo::NormalizePhone(std::string phone) {
  phone.erase(
      std::remove_if(
          phone.begin(), phone.end(),
          [](char c) { return c == ' ' || c == '-' || c == '(' || c == ')'; }),
      phone.end());
  if (phone.substr(0, 2) == "80") {
    phone = "+375" + phone.substr(2);
  }
  return phone;
}