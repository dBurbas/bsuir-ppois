//
// Created by Dmitry Burbas on 16/11/2025.
//

#ifndef DEAN_OFFICE_H
#define DEAN_OFFICE_H
#include <string>
#include <vector>

#include "../base_classes/office_worker/office_worker.h"
#include "../base_classes/student/student.h"
#include "../certificate/certificate.h"
#include "../dean/dean.h"
#include "../dean_deputy/dean_deputy.h"
#include "../department/department.h"
#include "../documents/orders/expulsion_order/expulsion_order.h"
#include "../exceptions/dean_office_exceptions.h"
#include "../value_structures/address/address.h"
#include "../value_structures/contact_info/contact_info.h"
#include "../value_structures/personal_info/personal_info.h"
// TODO: уточнить логику и методы
class DeanOffice {
 public:
  explicit DeanOffice(std::unique_ptr<Dean> dean,
                      const ContactInfo& contact_info);
  DeanOffice(const DeanOffice& other);
  DeanOffice& operator=(const DeanOffice& other);
  DeanOffice(DeanOffice&& other) noexcept;
  DeanOffice& operator=(DeanOffice&& other) noexcept;
  ~DeanOffice() = default;

  void SetDean(std::unique_ptr<Dean> dean);
  const Dean& GetDean() const;

  void AddDeputy(const DeanDeputy& deputy);
  void RemoveDeputyByPersonalInfo(const PersonalInfo& deputy_info);

  const std::vector<DeanDeputy>& GetDeputies() const;
  void AddDepartment(std::shared_ptr<Department> department);
  void RemoveDepartment(const std::string& department_name);
  const std::vector<Department>& GetDepartments() const;
  [[nodiscard]] std::shared_ptr<Department> FindDepartment(
      const std::string& name) const;

  void EnrollStudent(std::shared_ptr<Student> student,
                     const std::string& group_number);

  std::unique_ptr<Certificate> IssueStudyCertificate(
      const Student& student) const;

  std::unique_ptr<ExpulsionOrder> CreateExpulsionOrder(
      const std::vector<std::shared_ptr<Student>>& students);
  void SetAddress(const Address& address) { contact_info_.SetAddress(address); }
  const Address& GetAddress() const {
    try {
      const Address& address = contact_info_.GetAddress();
      return address;
    } catch (ContactInfoException& e) {
      throw DeanOfficeException("DeanOffice error: " + std::string(e.what()));
    }
  }

  void SetEmail(const std::string& email) {
    try {
      contact_info_.SetEmail(email);
    } catch (ContactInfoException& e) {
      throw DeanOfficeException("DeanOffice error: " + std::string(e.what()));
    }
  }
  const std::string& GetEmail() const {
    try {
      const std::string& email = contact_info_.GetEmail();
      return email;
    } catch (ContactInfoException& e) {
      throw DeanOfficeException("DeanOffice error: " + std::string(e.what()));
    }
  }
  void SetPhoneNumber(const std::string& phone) {
    try {
      contact_info_.SetPhoneNumber(phone);
    } catch (ContactInfoException& e) {
      throw DeanOfficeException("DeanOffice error: " + std::string(e.what()));
    }
  }
  const std::string& GetPhoneNumber() const {
    try {
      const std::string& phone = contact_info_.GetPhoneNumber();
      return phone;
    } catch (ContactInfoException& e) {
      throw DeanOfficeException("DeanOffice error: " + std::string(e.what()));
    }
  }

 private:
  std::unique_ptr<Dean> dean_;
  std::vector<std::unique_ptr<DeanDeputy>> deputies_;
  std::vector<std::unique_ptr<OfficeWorker>> office_workers_;
  std::vector<std::shared_ptr<Department>> departments_;
  ContactInfo contact_info_;
};

#endif  // DEAN_OFFICE_H
