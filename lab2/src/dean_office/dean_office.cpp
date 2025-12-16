//
// Created by Dmitry Burbas on 16/11/2025.
//

#include "dean_office.h"
/**
 * @file dean_office.cpp
 * @brief Реализация методов Деканата
 * @author Dmitry Burbas
 * @date 16/11/2025
 */

#include <algorithm>
#include <stdexcept>

#include "dean_office.h"

// ПОДКЛЮЧАЕМ ВСЕ ЗАГОЛОВОЧНЫЕ ФАЙЛЫ, которые мы убрали из .h
// Это нужно, чтобы компилятор видел полные определения классов здесь.
#include "../department/department.h"
#include "../documents/certificate/certificate.h"
#include "../documents/orders/enrollment_order/enrollment_order.h"
#include "../documents/orders/expulsion_order/expulsion_order.h"
#include "../people/dean/dean.h"
#include "../people/dean_deputy/dean_deputy.h"
#include "../people/office_worker/office_worker.h"
#include "../people/student/student.h"
#include "../speciality/speciality.h"

DeanOffice::DeanOffice(std::unique_ptr<Dean> dean,
                       const ContactInfo& contact_info)
    : dean_(std::move(dean)), contact_info_(contact_info) {
  if (!dean_) {
    throw std::invalid_argument("Dean cannot be null at DeanOffice creation");
  }
}

DeanOffice::~DeanOffice() = default;

DeanOffice::DeanOffice(DeanOffice&& other) noexcept = default;

DeanOffice& DeanOffice::operator=(DeanOffice&& other) noexcept = default;

void DeanOffice::SetDean(std::unique_ptr<Dean> dean) {
  if (!dean) {
    throw DeanOfficeException("Cannot set null Dean");
  }
  dean_ = std::move(dean);
}

const Dean& DeanOffice::GetDean() const { return *dean_; }

void DeanOffice::AddDeputy(std::unique_ptr<DeanDeputy> deputy) {
  if (deputy) {
    deputies_.push_back(std::move(deputy));
  }
}

void DeanOffice::RemoveDeputyByPersonalInfo(const PersonalInfo& deputy_info) {
  auto it =
      std::remove_if(deputies_.begin(), deputies_.end(),
                     [&deputy_info](const std::unique_ptr<DeanDeputy>& deputy) {
                       return deputy->GetPersonalInfo() == deputy_info;
                     });

  if (it != deputies_.end()) {
    deputies_.erase(it, deputies_.end());
  }
}

std::vector<const DeanDeputy*> DeanOffice::GetDeputies() const {
  std::vector<const DeanDeputy*> result;
  result.reserve(deputies_.size());
  for (const auto& dep : deputies_) {
    result.push_back(dep.get());
  }
  return result;
}

void DeanOffice::AddDepartment(std::shared_ptr<Department> department) {
  if (department) {
    departments_.push_back(std::move(department));
  }
}

void DeanOffice::RemoveDepartment(const std::string& department_name) {
  auto it = std::remove_if(
      departments_.begin(), departments_.end(),
      [&department_name](const std::shared_ptr<Department>& dept) {
        return dept->GetName() == department_name;
      });

  if (it != departments_.end()) {
    departments_.erase(it, departments_.end());
  }
}

const std::vector<std::shared_ptr<Department>>& DeanOffice::GetDepartments()
    const {
  return departments_;
}

std::shared_ptr<Department> DeanOffice::FindDepartment(
    const std::string& name) const {
  for (const auto& dept : departments_) {
    if (dept->GetName() == name) {
      return dept;
    }
  }
  return nullptr;
}

void DeanOffice::EnrollStudent(const EnrollmentOrder& order) {
  // TODO: Реализовать логику зачисления
  // 1. Извлечь данные из order
  // 2. Создать объект Student
  // 3. Добавить в нужную группу
}

std::unique_ptr<Certificate> DeanOffice::IssueStudyCertificate(
    const Student& student) const {
  // TODO: Реализовать генерацию справки
  return nullptr;
}

std::unique_ptr<ExpulsionOrder> DeanOffice::CreateExpulsionOrder(
    const std::vector<std::shared_ptr<Student>>& students) {
  // TODO: Реализовать создание приказа об отчислении
  return nullptr;
}

void DeanOffice::SetAddress(const Address& address) {
  contact_info_.SetAddress(address);
}

Address DeanOffice::GetAddress() const {
  try {
    return contact_info_.GetAddress();
  } catch (const ContactInfoException& e) {
    throw DeanOfficeException("DeanOffice error (GetAddress): " +
                              std::string(e.what()));
  }
}

void DeanOffice::SetEmail(const std::string& email) {
  try {
    contact_info_.SetEmail(email);
  } catch (const ContactInfoException& e) {
    throw DeanOfficeException("DeanOffice error (SetEmail): " +
                              std::string(e.what()));
  }
}

std::string DeanOffice::GetEmail() const {
  try {
    return contact_info_.GetEmail();
  } catch (const ContactInfoException& e) {
    throw DeanOfficeException("DeanOffice error (GetEmail): " +
                              std::string(e.what()));
  }
}

void DeanOffice::SetPhoneNumber(const std::string& phone) {
  try {
    contact_info_.SetPhoneNumber(phone);
  } catch (const ContactInfoException& e) {
    throw DeanOfficeException("DeanOffice error (SetPhoneNumber): " +
                              std::string(e.what()));
  }
}

std::string DeanOffice::GetPhoneNumber() const {
  try {
    return contact_info_.GetPhoneNumber();
  } catch (const ContactInfoException& e) {
    throw DeanOfficeException("DeanOffice error (GetPhoneNumber): " +
                              std::string(e.what()));
  }
}
