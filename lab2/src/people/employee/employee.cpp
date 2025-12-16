//
// Created by Dmitry Burbas on 14/12/2025.
//
#include "employee.h"

#include "../../exceptions/dean_office_exceptions.h"

void Employee::BecomeActive() {
  if (employee_status_ == EmployeeStatus::Fired)
    throw EmployeeException("Employee error: employee is fired");
  if (employee_status_ != EmployeeStatus::OnLeave)
    throw EmployeeException("Employee is not on leave");
  employee_status_ = EmployeeStatus::Active;
}
void Employee::SendOnLeave(const EmployeeOnLeaveOrder& order,
                           const Date& cur_date) {
  if (employee_status_ == EmployeeStatus::Fired)
    throw EmployeeException("Employee error: employee is fired");
  if (employee_status_ == EmployeeStatus::OnLeave)
    throw EmployeeException("Employee error: already on leave");
  if (!order.IsSigned())
    throw EmployeeException("Employee error: order is not signed");
  if (order.GetEffectiveDate() > cur_date)
    throw EmployeeException("Employee error: order has not taken effect");
  employee_status_ = EmployeeStatus::OnLeave;
}
void Employee::Fire(const DismissalOrder& order, const Date& cur_date) {
  if (employee_status_ == EmployeeStatus::Fired)
    throw EmployeeException("Employee error: already fired");
  if (!order.IsSigned())
    throw EmployeeException("Employee error: order is not signed");
  if (order.GetEffectiveDate() > cur_date)
    throw EmployeeException("Employee error: order has not taken effect");
  employee_status_ = EmployeeStatus::Fired;
}
int Employee::FullYearsBetween(const Date& from, const Date& to) {
  if (to < from) throw EmployeeException("Invalid dates for experience");
  int years = to.GetYear() - from.GetYear();
  if (to.GetMonth() < from.GetMonth() ||
      (to.GetMonth() == from.GetMonth() && to.GetDay() < from.GetDay())) {
    --years;
  }
  return years;
}