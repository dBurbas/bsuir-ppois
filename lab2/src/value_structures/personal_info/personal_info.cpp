//
// Created by Dmitry Burbas on 15/11/2025.
//
#include "personal_info.h"

#include "../../exceptions/components_exceptions.h"
PersonalInfo::PersonalInfo(const std::string& first_name,
                           const std::string& last_name,
                           const std::string& middle_name,
                           const std::string& birth_date) {
  UpdateFirstAndLastName(first_name, last_name);
  middle_name_ = Utility::Trim(middle_name);
  if (!birth_date.empty()) {
    try {
      birth_date_ = Date(birth_date);
    } catch (const DateException& date_exception) {
      throw PersonalInfoException(std::string("Personal info error: ") +
                                  date_exception.what());
    }
  }
}

bool PersonalInfo::operator==(const PersonalInfo& other) {
  return last_name_ == other.last_name_ && first_name_ == other.first_name_ &&
         middle_name_ == other.middle_name_ && birth_date_ == other.birth_date_;
}
bool PersonalInfo::operator!=(const PersonalInfo& other) {
  return !(*this == other);
}
void PersonalInfo::SetBirthDate(const std::string& birth_date) {
  try {
    birth_date_ = Date(birth_date);
  } catch (const DateException& date_exception) {
    throw PersonalInfoException(std::string("Personal info error: ") +
                                date_exception.what());
  }
}
[[nodiscard]] std::string PersonalInfo::GetFullName() const {
  std::string result = last_name_ + " " + first_name_;
  if (!middle_name_.empty()) {
    result += " " + middle_name_;
  }
  return result;
}
void PersonalInfo::UpdateFirstName(const std::string& first_name) {
  const std::string trimmed_first = Utility::Trim(first_name);
  ValidateFirstName(trimmed_first);
  first_name_ = trimmed_first;
}
void PersonalInfo::UpdateLastName(const std::string& last_name) {
  const std::string trimmed_last = Utility::Trim(last_name);
  ValidateLastName(trimmed_last);
  last_name_ = trimmed_last;
}
void PersonalInfo::UpdateFirstAndLastName(const std::string& first_name,
                                          const std::string& last_name) {
  const std::string trimmed_first = Utility::Trim(first_name);
  const std::string trimmed_last = Utility::Trim(last_name);
  ValidateFirstName(trimmed_first);
  ValidateLastName(trimmed_last);
  first_name_ = trimmed_first;
  last_name_ = trimmed_last;
}
void PersonalInfo::ValidateFirstName(const std::string& first_name) {
  if (first_name.empty())
    throw PersonalInfoException(
        "Personal info error: first name cannot be empty");
}
void PersonalInfo::ValidateLastName(const std::string& last_name) {
  if (last_name.empty())
    throw PersonalInfoException(
        "Personal info error: last name cannot be empty");
}
