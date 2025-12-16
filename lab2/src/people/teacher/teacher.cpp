//
// Created by Dmitry Burbas on 16/11/2025.
//

#include "teacher.h"

#include "../../enum_classes/student_status.h"
#include "../student/student.h"
void Teacher::ExamineStudentAnswer(
    const std::weak_ptr<Student>& stud, const Subject& subject,
    std::unique_ptr<Grade> provisional_grade) const {
  stud.lock()->AddGrade(std::move(provisional_grade), *this);
}
[[nodiscard]] bool Teacher::MarkStudent(const Student& student) const {
  if (student.GetStatus() == StudentStatus::UnjustifiedLeave) return true;
  return false;
}