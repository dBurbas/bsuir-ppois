//
// Created by Dmitry Burbas on 16/11/2025.
//

#include "group.h"

#include "../people/student/student.h"
void Group::AddStudent(std::shared_ptr<Student> student) {
  if (!student) throw GroupException("Cannot add null student");
  if (FindStudent(student->GetStudentId()))
    throw GroupException("Student already exists");
  students_.push_back(std::move(student));
}
[[nodiscard]] std::shared_ptr<Student> Group::GetStudentByNumber(
    const std::shared_ptr<Teacher>& teacher, const int student_numb) {
  if (student_numb <= 0 || static_cast<size_t>(student_numb) > students_.size())
    throw GroupException("Student number out of range");
  auto& cur_student = students_[student_numb - 1];
  if (teacher->GetEmployeeStatus() == EmployeeStatus::Active) {
    if (!cur_student) throw GroupException("Student pointer is null");
    return cur_student;
  }
  throw GroupException("Teacher is not active");
}
[[nodiscard]] std::shared_ptr<Student> Group::FindStudent(
    const std::string& student_id) const {
  auto it = std::find_if(students_.begin(), students_.end(),
                         [&student_id](const std::shared_ptr<Student>& s) {
                           return s->GetStudentId() == student_id;
                         });

  if (it != students_.end()) {
    return *it;
  }
  return nullptr;
}
void Group::RemoveStudent(const std::string& student_id) {
  students_.erase(
      std::remove_if(students_.begin(), students_.end(),
                     [&student_id](const std::shared_ptr<Student>& s) {
                       if (!s) return true;
                       return s->GetStudentId() == student_id;
                     }),
      students_.end());
}