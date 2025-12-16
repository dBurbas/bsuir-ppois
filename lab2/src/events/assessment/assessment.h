/**
 * @file assessment.h
 * @brief Класс проведения контроля знаний (экзамен, зачет)
 * @author Dmitry Burbas
 * @date 14/12/2025
 */

#ifndef ASSESSMENT_H
#define ASSESSMENT_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../enum_classes/assessment_type.h"
#include "../../exceptions/dean_office_exceptions.h"
#include "../../group/group.h"
#include "../../people/student/student.h"
#include "../../people/teacher/teacher.h"
#include "../../subject/subject.h"
#include "../event/event.h"

/**
 * @class Assessment
 * @brief Событие экзаменационной сессии
 * @details Наследуется от Event. Организует процесс сдачи:
 * создает ведомость, вызывает студентов, генерирует оценки нужного типа (Grade)
 * и передает их преподавателю для фиксации.
 */
class Assessment : public Event {
 public:
  /**
   * @brief Конструктор экзамена/зачета
   * @param title Название мероприятия
   * @param date Дата проведения
   * @param address Аудитория
   * @param examiner Экзаменатор (слабая ссылка)
   * @param subject Предмет (слабая ссылка)
   * @param group Сдаваемая группа (слабая ссылка)
   * @param assessment_type Тип контроля (экзамен/зачет)
   * @throws AssessmentException, если любой из ключевых участников
   * (экзаменатор, предмет, группа) отсутствует
   */
  Assessment(std::string title, const Date& date, Address address,
             std::weak_ptr<Teacher> examiner,
             const std::weak_ptr<Subject>& subject, std::weak_ptr<Group> group,
             const AssessmentType assessment_type)
      : Event(std::move(title), date, std::move(address)),
        examiner_(std::move(examiner)),
        subject_(subject),
        group_(std::move(group)),
        assessment_type_(assessment_type) {
    ValidateSubject(subject_);
    ValidateExaminer(examiner_);
    ValidateGroup(group_);
  }

  /**
   * @brief Проведение экзамена
   * @details Итерируется по студентам, проверяет их присутствие.
   * Если студент присутствует, создается объект оценки (PassFailGrade или
   * NumericGrade), вычисляется балл (TakeAssessment) и результат передается
   * преподавателю.
   */
  void Hold() override;

  /**
   * @brief Смена экзаменатора
   * @throws AssessmentException если передан пустой указатель
   */
  void SetExaminer(std::weak_ptr<Teacher> examiner) {
    ValidateExaminer(examiner);
    examiner_ = std::move(examiner);
  }

  /**
   * @brief Получение текущего экзаменатора
   * @throws AssessmentException если экзаменатор удален из системы
   */
  [[nodiscard]] std::shared_ptr<Teacher> GetExaminer() const {
    auto ptr = examiner_.lock();
    if (!ptr) {
      throw AssessmentException("Examiner is not set");
    }
    return ptr;
  }

  /**
   * @brief Получение предмета
   */
  [[nodiscard]] std::shared_ptr<Subject> GetSubject() const {
    auto ptr = subject_.lock();
    if (!ptr) {
      throw AssessmentException("Subject deleted while assessment exists");
    }
    return ptr;
  }

  /**
   * @brief Получение типа контроля
   */
  [[nodiscard]] AssessmentType GetType() const { return assessment_type_; }

  /**
   * @brief Получение списка сдающих студентов
   * @throws AssessmentException если группа удалена
   */
  [[nodiscard]] std::vector<std::shared_ptr<Student>> GetExaminees() const {
    if (auto grp = group_.lock()) {
      return grp->GetStudents();
    }
    throw AssessmentException("Examinees not set");
  }

 private:
  static void ValidateSubject(const std::weak_ptr<Subject>& subj) {
    if (subj.expired()) {
      throw AssessmentException("Cannot create assessment: subject is null");
    }
  }
  static void ValidateExaminer(const std::weak_ptr<Teacher>& examiner) {
    if (examiner.expired()) {
      throw AssessmentException("Cannot assign a null examiner");
    }
  }
  static void ValidateGroup(const std::weak_ptr<Group>& group) {
    if (group.expired()) throw AssessmentException("Exam must have a Group");
  }

  std::weak_ptr<Teacher> examiner_;  ///< Экзаменатор
  std::weak_ptr<Subject> subject_;   ///< Предмет
  std::weak_ptr<Group> group_;       ///< Группа
  AssessmentType assessment_type_;   ///< Тип (экзамен/зачет)
};

#endif  // ASSESSMENT_H
