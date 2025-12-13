//
// Created by Dmitry Burbas on 11/11/2025.
//

#ifndef PERSON_H
#define PERSON_H

#include "../../exceptions/components_exceptions.h"
#include "../../exceptions/dean_office_exceptions.h"
#include "../../value_structures/contact_info/contact_info.h"
#include "../../value_structures/personal_info/personal_info.h"

// TODO: make docs and some tuning
class Person {
 public:
  Person(const PersonalInfo& personal_info, const ContactInfo& contact_info)
      : personal_info_(personal_info), contact_info_(contact_info) {
    try {
      personal_info_.GetBirthDate();
    } catch (const PersonalInfoException& e) {
      throw PersonException("No birth date for person:" +
                            std::string(e.what()));
    }
  }
  virtual ~Person() = default;
  void SetEmail(const std::string& email) {
    // TODO: убрать этот try-catch(нет смысла) или перевести на nested_exception
    try {
      contact_info_.SetEmail(email);
    } catch (const ContactInfoException& e) {
      throw PersonException("Person error:" + std::string(e.what()));
    }
  }
  void SetPhoneNumber(const std::string& phone_number) {
    try {
      contact_info_.SetPhoneNumber(phone_number);
    } catch (const ContactInfoException& e) {
      throw PersonException("Person error:" + std::string(e.what()));
    }
  }
  [[nodiscard]] const PersonalInfo& GetPersonalInfo() const {
    return personal_info_;
  }
  [[nodiscard]] const ContactInfo& GetContactInfo() const {
    return contact_info_;
  }
  [[nodiscard]] std::string GetFullName() const {
    return personal_info_.GetFullName();
  }

  [[nodiscard]] std::string GetBirthDateString() const {
    return personal_info_.GetBirthDate().ToString();
  }

  [[nodiscard]] std::string GetEmail() const {
    return contact_info_.GetEmail();
  }

  [[nodiscard]] std::string GetPhoneNumber() const {
    return contact_info_.GetPhoneNumber();
  }

 protected:
  PersonalInfo personal_info_;
  ContactInfo contact_info_;
};

#endif  // PERSON_H
