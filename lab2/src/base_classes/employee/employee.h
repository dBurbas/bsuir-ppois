/**
 * @file employee.h
 * @brief Базовый класс для работников
 * @author Dmitry Burbas
 * @date 06/12/2025
 */
#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "../../documents/orders/dismissal_order/dismissal_order.h"
#include "../../documents/orders/employee_on_leave_order/employee_on_leave_order.h"
#include "../../enum_classes/employee_status.h"
#include "../../salary/salary.h"
#include "../order/order.h"
#include "../person/person.h"

// TODO: сделать документацию
class Employee : public Person {
 public:
  Employee(const PersonalInfo& personal_info, const ContactInfo& contact_info,
           const double salary_base, const double salary_rate,
           const Date& hire_date)
      : Person(personal_info, contact_info),
        salary_(salary_base, salary_rate),
        hire_date_(hire_date) {}

  ~Employee() override = default;
  virtual void Work() = 0;
  void BecomeActive();
  void SendOnLeave(const EmployeeOnLeaveOrder& order, const Date& cur_date);
  void Fire(const DismissalOrder& order, const Date& cur_date);
  void SetSalaryBase(const double new_salary_base) {
    salary_.SetBase(new_salary_base);
  }
  void SetSalaryRate(const double new_salary_rate) {
    salary_.SetRate(new_salary_rate);
  }

  [[nodiscard]] EmployeeStatus GetEmployeeStatus() const {
    return employee_status_;
  }
  [[nodiscard]] int GetExperienceYears(const Date& cur_date) const {
    return FullYearsBetween(hire_date_, cur_date);
  }
  [[nodiscard]] double GetSalary() const { return salary_.GetSalary(); }
  [[nodiscard]] double GetSalaryBase() const { return salary_.GetBase(); }
  [[nodiscard]] double GetSalaryRate() const { return salary_.GetRate(); }

 private:
  static int FullYearsBetween(const Date& from, const Date& to);
  Salary salary_;
  Date hire_date_;
  EmployeeStatus employee_status_ = EmployeeStatus::Active;
};

#endif  // EMPLOYEE_H
