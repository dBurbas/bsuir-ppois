/**
 * @file dean_office.h
 * @brief Класс Деканата
 */

#ifndef DEAN_OFFICE_H
#define DEAN_OFFICE_H

#include <memory>
#include <string>
#include <vector>

class Dean;
class DeanDeputy;
class OfficeWorker;
class Department;
class Speciality;
class Student;
class Certificate;
class EnrollmentOrder;
class ExpulsionOrder;

#include "../exceptions/dean_office_exceptions.h"
#include "../value_structures/address/address.h"
#include "../value_structures/contact_info/contact_info.h"
#include "../value_structures/personal_info/personal_info.h"

class DeanOffice {
 public:
  explicit DeanOffice(std::unique_ptr<Dean> dean,
                      const ContactInfo& contact_info);

  ~DeanOffice();

  DeanOffice(const DeanOffice&) = delete;
  DeanOffice& operator=(const DeanOffice&) = delete;

  DeanOffice(DeanOffice&& other) noexcept;
  DeanOffice& operator=(DeanOffice&& other) noexcept;

  void SetDean(std::unique_ptr<Dean> dean);
  [[nodiscard]] const Dean& GetDean() const;

  void AddDeputy(std::unique_ptr<DeanDeputy> deputy);
  void RemoveDeputyByPersonalInfo(const PersonalInfo& deputy_info);

  [[nodiscard]] std::vector<const DeanDeputy*> GetDeputies() const;

  void AddDepartment(std::shared_ptr<Department> department);
  void RemoveDepartment(const std::string& department_name);
  [[nodiscard]] const std::vector<std::shared_ptr<Department>>& GetDepartments()
      const;
  [[nodiscard]] std::shared_ptr<Department> FindDepartment(
      const std::string& name) const;

  void EnrollStudent(const EnrollmentOrder& order);

  [[nodiscard]] std::unique_ptr<Certificate> IssueStudyCertificate(
      const Student& student) const;

  std::unique_ptr<ExpulsionOrder> CreateExpulsionOrder(
      const std::vector<std::shared_ptr<Student>>& students);

  void SetAddress(const Address& address);
  [[nodiscard]] Address GetAddress() const;

  void SetEmail(const std::string& email);
  [[nodiscard]] std::string GetEmail() const;

  void SetPhoneNumber(const std::string& phone);
  [[nodiscard]] std::string GetPhoneNumber() const;

 private:
  // Pimpl-like структура, скрывающая детали реализации
  std::unique_ptr<Dean> dean_;
  std::vector<std::unique_ptr<DeanDeputy>> deputies_;
  std::vector<std::unique_ptr<OfficeWorker>> office_workers_;
  std::vector<std::shared_ptr<Department>> departments_;
  std::vector<std::shared_ptr<Speciality>> specialities_;

  ContactInfo contact_info_;
};

#endif  // DEAN_OFFICE_H
