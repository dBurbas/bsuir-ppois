//
// Created by Dmitry Burbas on 06/12/2025.
//

#ifndef LAB2_EMPLOYEE_H
#define LAB2_EMPLOYEE_H
#include "../person/person.h"
// TODO: перепроверить и уточнить методы и поля
class Employee : public Person {
 public:
  explicit Employee(const Person& employee) : Person(employee) {}
  Employee(const Person& employee, double salary, double salary_rate)
      : Person(employee), salary_(salary), salary_rate_(salary_rate) {}
  ~Employee() override = default;
  virtual void Work() = 0;
  void IncreaseExperienceValue(int experience_increase) {
    if (experience_increase < 0) {
      throw EmployeeException("Employee experience increase must be > 0");
    }
    experience_years_ += experience_increase;
  }
  void SetSalaryValue(double new_salary) {
    if (new_salary < 0.0) {
      throw EmployeeException("Employee error: salary cannot be negative");
    }
    salary_ = new_salary;
  }
  void SetSalaryRate(double new_salary_rate) {
    if (new_salary_rate <= 0.0) {
      throw EmployeeException("Employee error: salary must be positive");
    }
    salary_rate_ = new_salary_rate;
  }
  [[nodiscard]] int GetExperienceValue() const { return experience_years_; }
  [[nodiscard]] double GetSalaryValue() const { return salary_; }
  [[nodiscard]] double GetSalaryRate() const { return salary_rate_; }

 protected:
  int experience_years_ = 0;
  double salary_ = 0.0;
  double salary_rate_ = 1.0;
};

#endif  // LAB2_EMPLOYEE_H
