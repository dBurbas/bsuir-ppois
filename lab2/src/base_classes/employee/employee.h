//
// Created by Dmitry Burbas on 06/12/2025.
//

#ifndef LAB2_EMPLOYEE_H
#define LAB2_EMPLOYEE_H
#include "../person/person.h"
// TODO: уточнить методы и поля
class Employee : public Person {
 public:
  explicit Employee(const Person& employee) : Person(employee) {}
  ~Employee() override = default;
  virtual void Work() = 0;
  void IncreaseExperienceValue(int experience_increase) {
    if (experience_increase < 0) };

 protected:
  int experience_years_ = 0;
};

#endif  // LAB2_EMPLOYEE_H
