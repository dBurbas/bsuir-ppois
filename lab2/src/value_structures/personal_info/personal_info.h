//
// Created by Dmitry Burbas on 11/11/2025.
//

#ifndef PERSONAL_INFO_H
#define PERSONAL_INFO_H

#include <string>

#include "../../exceptions/components_exceptions.h"
#include "../../utility_functions/utility_functions.h"
#include "../date/date.h"
// TODO: документация
class PersonalInfo {
 public:
  PersonalInfo(const std::string& first_name, const std::string& last_name,
               const std::string& middle_name = "",
               std::optional<Date> birth_date = std::nullopt);
  PersonalInfo(const PersonalInfo& other) = default;
  PersonalInfo(PersonalInfo&& other) = default;
  PersonalInfo& operator=(const PersonalInfo& other) = default;
  PersonalInfo& operator=(PersonalInfo&& other) = default;

  bool operator==(const PersonalInfo& other) const;
  bool operator!=(const PersonalInfo& other) const;
  ~PersonalInfo() = default;
  void SetFullName(const std::string& first_name, const std::string& last_name,
                   const std::string& middle_name = "") {
    UpdateFirstAndLastName(first_name, last_name);
    middle_name_ = Utility::Trim(middle_name);
  }
  void SetBirthDate(const std::string& birth_date);
  void SetFirstName(const std::string& first_name) {
    UpdateFirstName(first_name);
  }
  void SetLastName(const std::string& last_name) { UpdateLastName(last_name); }
  void SetMiddleName(const std::string& middle_name) {
    middle_name_ = Utility::Trim(middle_name);
  }
  [[nodiscard]] std::string GetFullName() const;
  [[nodiscard]] std::string GetLastName() const { return last_name_; }
  [[nodiscard]] std::string GetFirstName() const { return first_name_; }
  [[nodiscard]] std::string GetMiddleName() const { return middle_name_; }
  [[nodiscard]] const Date& GetBirthDate() const {
    if (birth_date_ == std::nullopt)
      throw PersonalInfoException("No date in this personal info");
    return *birth_date_;
  }

 private:
  std::string first_name_;
  std::string last_name_;
  std::string middle_name_;
  std::optional<Date> birth_date_;
  void UpdateFirstName(const std::string& first_name);
  void UpdateLastName(const std::string& last_name);
  void UpdateFirstAndLastName(const std::string& first_name,
                              const std::string& last_name);
  static void ValidateFirstName(const std::string& first_name);
  static void ValidateLastName(const std::string& last_name);
};

#endif  // PERSONAL_INFO_H
