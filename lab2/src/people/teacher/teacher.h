/**
 * @file teacher.h
 * @brief Базовый класс для преподавателей учебного заведения
 * @author Dmitry Burbas
 * @date 16/11/2025
 */

#ifndef TEACHER_H
#define TEACHER_H

#include <memory>
#include <vector>

#include "../../enum_classes/assessment_type.h"
#include "../../grades/grade/grade.h"
#include "../../group/group.h"
#include "../../subject/subject.h"
#include "../employee/employee.h"

// Предварительное объявление, чтобы избежать циклической зависимости
class Student;

/**
 * @class Teacher
 * @brief Представляет преподавателя как сотрудника, способного оценивать
 * студентов
 * @details Наследуется от Employee (виртуально) для возможности создания
 * гибридных ролей (например, преподающий администратор). Основная
 * ответственность — проведение экзаменов и выставление оценок.
 */
class Teacher : virtual public Employee {
 public:
  /**
   * @brief Конструктор преподавателя
   * @param personal_info Персональные данные (ФИО и т.д.)
   * @param contact_info Контактная информация
   * @param salary_base Базовая ставка зарплаты
   * @param salary_rate Коэффициент зарплаты
   * @param hire_date Дата найма
   * @details Инициализирует базовую часть Employee.
   */
  Teacher(const PersonalInfo& personal_info, const ContactInfo& contact_info,
          const double salary_base, const double salary_rate,
          const Date& hire_date)
      : Employee(personal_info, contact_info, salary_base, salary_rate,
                 hire_date) {}

  /**
   * @brief Выполнение рабочих обязанностей
   * @details Реализация абстрактного метода базового класса.
   * В текущей версии метод пуст (преподаватель "присутствует").
   * @warning TODO: Реализовать логику проведения занятий или отчета о работе.
   */
  void Work() override {};

  /**
   * @brief Проверяет ответ студента и выставляет предварительную оценку
   * @param stud Слабая ссылка на студента (для проверки существования)
   * @param subject Предмет, по которому идет экзамен/зачет
   * @param provisional_grade Уникальный указатель на объект оценки (передача
   * владения)
   * @details Метод принимает владение объектом оценки.
   */
  void ExamineStudentAnswer(const std::weak_ptr<Student>& stud,
                            const Subject& subject,
                            std::unique_ptr<Grade> provisional_grade) const;

  /**
   * @brief Отмечает студента (например, посещаемость или простой статус)
   * @param student Ссылка на объект студента
   * @return true, если операция прошла успешно (студент отсутствует и отмечен)
   * @details Название метода неоднозначно (MarkStudent).
   */
  [[nodiscard]] bool MarkStudent(const Student& student) const;
};

#endif  // TEACHER_H
