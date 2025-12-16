//
// Created by Dmitry Burbas on 16/11/2025.
//

#include "student.h"
[[nodiscard]] int Student::TakeAssessment(const Subject& subj,
                                          const Date& cur_date,
                                          AssessmentType type) const {
  if (type == AssessmentType::CreditTest) {
    if (cur_date.GetDay() % 2 == 0) return 1;
    return 0;
  }
  if (subj.GetName() == "PPOIS") return 10;  // :)
  return DetermineAssessmentMark(cur_date);
}
void Student::SkipClasses() {
  if (status_ == StudentStatus::Expelled)
    throw StudentException("Student error: expelled");
  if (status_ == StudentStatus::AcademicLeave)
    throw StudentException("Student error: already on leave");
  status_ = StudentStatus::UnjustifiedLeave;
}
void Student::OnLeave(const AcademicLeaveOrder& order, const Date& cur_date) {
  if (status_ == StudentStatus::Expelled)
    throw StudentException("Student error: expelled");
  if (!order.IsSigned())
    throw StudentException("Student error: order is not signed");
  if (order.GetEffectiveDate() > cur_date)
    throw StudentException("Student error: order has not taken effect");
  if (status_ == StudentStatus::AcademicLeave)
    throw StudentException("Student error: already on leave");
  status_ = StudentStatus::AcademicLeave;
}

void Student::Expel(const ExpulsionOrder& order, const Date& cur_date) {
  if (status_ == StudentStatus::Expelled)
    throw StudentException("Student error: already expelled");
  if (!order.IsSigned())
    throw StudentException("Student error: order is not signed");
  if (order.GetEffectiveDate() > cur_date)
    throw StudentException("Student error: order has not taken effect");
  status_ = StudentStatus::Expelled;
  group_id_.clear();
  scholarship_.reset();
}

[[nodiscard]] int Student::DetermineAssessmentMark(const Date& cur_date) const {
  const int day = cur_date.GetDay();
  const int base = (day % 2 == 0) ? 5 : 10;
  int last_digit = 0;
  if (!student_id_.empty()) {
    last_digit = student_id_.back() - '0';  // '6' -> 6
    if (last_digit < 0 || last_digit > 9) {
      last_digit = 0;
    }
  }
  const int denominator = (last_digit == 0) ? 1 : (last_digit + 1);
  int mark = (base * 10 + denominator / 2) / denominator;
  if (mark < 1) mark = 1;
  if (mark > 10) mark = 10;
  return mark;
}
void Student::ValidateStudentId(const std::string& student_id) {
  if (student_id.size() != 6)
    throw StudentException("Invalid student id: " + student_id +
                           " (expected something like 421711");
  for (int i = 0; i < 6; i++) {
    if (!isdigit(student_id[i]))
      throw StudentException("Invalid student id: " + student_id +
                             "(expected something like 421711)");
  }
}