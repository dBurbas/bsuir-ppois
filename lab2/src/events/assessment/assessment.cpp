#include "assessment.h"

#include "../../grades/numeric_grade/numeric_grade.h"
#include "../../grades/pass_fail_grade/pass_fail_grade.h"
void Assessment::Hold() {
  auto examiner_ptr = examiner_.lock();
  auto group_ptr = group_.lock();
  auto subject_ptr = subject_.lock();

  if (!examiner_ptr || !group_ptr || !subject_ptr)
    throw AssessmentException("Critical resources expired during Hold()");

  for (int i = 1; i <= static_cast<int>(group_ptr->GetSize()); ++i) {
    auto cur_student = group_ptr->GetStudentByNumber(examiner_ptr, i);
    std::unique_ptr<Grade> provisional_grade;
    switch (assessment_type_) {
      case AssessmentType::CreditTest:
        provisional_grade =
            std::make_unique<PassFailGrade>(subject_ptr->GetId());
        break;
      case AssessmentType::Exam:
        provisional_grade =
            std::make_unique<NumericGrade>(subject_ptr->GetId());
        break;
      default:
        throw AssessmentException("Unsupported assessment type");
    }

    if (!examiner_ptr->MarkStudent(*cur_student)) {
      int score = cur_student->TakeAssessment(*subject_ptr, event_date_,
                                              assessment_type_);
      provisional_grade->SetValue(score);
    }
    examiner_ptr->ExamineStudentAnswer(cur_student, *subject_ptr,
                                       std::move(provisional_grade));
  }
}