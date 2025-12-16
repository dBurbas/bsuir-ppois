/**
 * @file lesson.h
 * @brief Абстрактный базовый класс учебного занятия
 * @author Dmitry Burbas
 * @date 15/12/2025
 */

#ifndef LESSON_H
#define LESSON_H

#include <memory>
#include <string>
#include <utility>

#include "../../../group/group.h"
#include "../../../people/student/student.h"
#include "../../../people/teacher/teacher.h"
#include "../../event/event.h"

/**
 * @class Lesson
 * @brief Базовый класс для всех типов уроков (лекции, семинары)
 * @details Наследуется от Event. Связывает событие с конкретной группой,
 * преподавателем и предметом. Содержит общую логику отметки студентов.
 */
class Lesson : public Event {
 public:
  /**
   * @brief Конструктор занятия
   * @param title Название/тема занятия
   * @param date Дата проведения
   * @param address Адрес (аудитория)
   * @param teacher Преподаватель (слабая ссылка)
   * @param group Группа (слабая ссылка)
   * @param subject_id ID предмета
   */
  Lesson(std::string title, const Date& date, Address address,
         std::weak_ptr<Teacher> teacher, std::weak_ptr<Group> group,
         std::string subject_id)
      : Event(std::move(title), date, std::move(address)),
        teacher_(std::move(teacher)),
        group_(std::move(group)),
        subject_id_(std::move(subject_id)) {}

  /**
   * @brief Чисто виртуальный метод проведения занятия
   * @details Должен быть реализован в Seminar, Lecture и т.д.
   */
  void Hold() override = 0;

  /**
   * @brief Процедура переклички студентов
   * @details Итерируется по всем студентам группы и вызывает метод MarkStudent
   * у преподавателя.
   */
  void MarkStudents() {
    auto teacher_ptr = teacher_.lock();
    auto group_ptr = group_.lock();

    if (!teacher_ptr || !group_ptr)
      throw LessonException("Lesson::MarkStudents: no data");

    for (int i = 1; i <= static_cast<int>(group_ptr->GetSize()); ++i) {
      auto cur_student = group_ptr->GetStudentByNumber(teacher_ptr, i);
      if (teacher_ptr->MarkStudent(*cur_student))
        cur_student->MarkSkip(*teacher_ptr);
    }
  }

 private:
  std::weak_ptr<Teacher> teacher_;  ///< Преподаватель, ведущий занятие
  std::weak_ptr<Group> group_;      ///< Обучаемая группа
  std::string subject_id_;          ///< ID предмета
};

#endif  // LESSON_H
