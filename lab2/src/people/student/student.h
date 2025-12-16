/**
 * @file student.h
 * @brief Класс студента
 * @author Dmitry Burbas
 * @date 16/11/2025
 */

#ifndef STUDENT_H
#define STUDENT_H

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "../../documents/orders/academic_leave_order/academic_leave_order.h"
#include "../../documents/orders/expulsion_order/expulsion_order.h"
#include "../../enum_classes/education_payment_type.h"
#include "../../enum_classes/student_status.h"
#include "../../exceptions/dean_office_exceptions.h"
#include "../../grades/grade/grade.h"
#include "../../scholarship/scholarship.h"
#include "../../subject/subject.h"
#include "../person/person.h"

// Forward declarations
class AcademicLeaveOrder;
class Teacher;

/**
 * @class Student
 * @brief Представляет студента учебного заведения
 * @details Наследуется от Person, добавляя специфичные для студента атрибуты:
 * статус обучения, тип оплаты, зачетную книжку и стипендию.
 * Управляет жизненным циклом обучения (отчисление, академический отпуск).
 */
class Student : public Person {
 public:
  /**
   * @brief Конструктор студента
   * @param personal_info Персональные данные
   * @param contact_info Контактная информация
   * @param payment_type Тип оплаты обучения (бюджет/платное)
   * @param group ID группы
   * @param stud_id Номер студенческого билета (строка из 6 цифр)
   * @throws StudentException, если ID группы пуст или ID студента некорректен
   * @details, если обучение платное, стипендия не создается.
   * Статус по умолчанию устанавливается в Studying.
   */
  Student(const PersonalInfo& personal_info, const ContactInfo& contact_info,
          EducationPaymentType payment_type, std::string group,
          std::string stud_id)
      : Person(personal_info, contact_info),
        payment_type_(payment_type),
        group_id_(std::move(group)),
        student_id_(std::move(stud_id)) {
    ValidateStudentId(student_id_);
    if (group_id_.empty()) throw StudentException("Group id is empty");
    if (payment_type_ != EducationPaymentType::Paid)
      scholarship_ = Scholarship();
    status_ = StudentStatus::Studying;
  }

  /**
   * @brief Симулирует сдачу экзамена или зачета
   * @param subj Предмет
   * @param cur_date Дата сдачи
   * @param type Тип контроля
   * @return Оценка (число). Для зачета 1 (сдал) или 0 (не сдал).
   * @details Логика "заглушка": оценка зависит от четности дня и ID студента.
   * Для предмета "PPOIS" всегда возвращает 10.
   */
  [[nodiscard]] int TakeAssessment(const Subject& subj, const Date& cur_date,
                                   AssessmentType type) const;

  /**
   * @brief Фиксирует пропуск занятий без уважительной причины
   * @throws StudentException, если студент отчислен или в академический отпуске
   * @details Меняет статус на UnjustifiedLeave (прогул).
   */
  void SkipClasses();

  /**
   * @brief Оформляет уход в академический отпуск
   * @param order Приказ об академическом отпуске
   * @param cur_date Текущая дата
   * @throws StudentException, если приказ не подписан, дата не наступила или
   * статус некорректен
   */
  void OnLeave(const AcademicLeaveOrder& order, const Date& cur_date);

  /**
   * @brief Оформляет отчисление студента
   * @param order Приказ об отчислении
   * @param cur_date Текущая дата
   * @throws StudentException, если приказ не подписан или дата не наступила
   * @details Очищает группу, удаляет стипендию и меняет статус на Expelled.
   */
  void Expel(const ExpulsionOrder& order, const Date& cur_date);

  /**
   * @brief Получение типа оплаты обучения
   */
  [[nodiscard]] EducationPaymentType GetPaymentType() const {
    return payment_type_;
  }

  /**
   * @brief Получение текущего статуса студента
   */
  [[nodiscard]] StudentStatus GetStatus() const { return status_; }

  /**
   * @brief Получение ID группы
   */
  [[nodiscard]] const std::string& GetGroupId() const { return group_id_; }

  /**
   * @brief Получение номера студенческого билета
   */
  [[nodiscard]] const std::string& GetStudentId() const { return student_id_; }

  /**
   * @brief Проверяет наличие стипендии
   */
  [[nodiscard]] bool HasScholarship() const { return scholarship_.has_value(); }

  /**
   * @brief Назначает стипендию
   * @throws StudentException, если стипендия уже есть
   */
  void AddScholarship(const Scholarship& scholarship) {
    if (scholarship_.has_value())
      throw StudentException("Scholarship already exists");
    scholarship_ = scholarship;
  }

  /**
   * @brief Лишает стипендии
   */
  void RemoveScholarship() { scholarship_.reset(); }

  /**
   * @brief Возвращает размер текущей стипендии
   * @throws StudentException, если стипендии нет
   */
  [[nodiscard]] int GetScholarshipValue() const {
    if (!scholarship_.has_value()) throw StudentException("No scholarship");
    return scholarship_->GetValue();
  }

  /**
   * @brief Обновляет коэффициент стипендии (например, за успехи)
   * @param rate Новый коэффициент
   */
  void UpdateScholarshipRate(const double rate) { scholarship_->SetRate(rate); }

  /**
   * @brief Переводит студента в другую группу
   * @param group_id ID новой группы
   */
  void TransferToGroup(std::string group_id) {
    group_id_ = std::move(group_id);
  }

  /**
   * @brief Фиксирует пропуск, если преподаватель отметил отсутствие
   * @param teacher Преподаватель, проводящий занятие
   * @details Увеличивает счетчик пропусков (skips_hours) на 2 часа.
   */
  void MarkSkip(const Teacher& teacher) {
    if (teacher.MarkStudent(*this)) skips_hours += 2;
  }

  /**
   * @brief Добавляет оценку в зачетную книжку
   * @param grade Умный указатель на оценку (передача владения)
   * @param teacher Преподаватель, выставивший оценку
   * @throws StudentException, если статус преподавателя не Active
   */
  void AddGrade(std::unique_ptr<Grade> grade, const Teacher& teacher) {
    if (teacher.GetEmployeeStatus() != EmployeeStatus::Active)
      throw StudentException("Teacher must be active to add grade");
    grade_book_.push_back(std::move(grade));
  }

 private:
  /**
   * @brief Внутренний алгоритм расчета "случайной" оценки
   * @details Использует дату и номер студенческого для генерации числа.
   */
  [[nodiscard]] int DetermineAssessmentMark(const Date& cur_date) const;

  /**
   * @brief Проверяет формат студенческого билета
   * @param student_id Строка для проверки
   * @throws StudentException, если длина не 6 или содержатся недопустимые
   * символы
   * @warning В реализации cpp есть логическая ошибка проверки цифр (isnumber).
   */
  static void ValidateStudentId(const std::string& student_id);

  StudentStatus status_;  ///< Текущий статус (учится, отчислен и т.д.)
  EducationPaymentType payment_type_;       ///< Бюджет, платное или целевое
  std::string group_id_;                    ///< Привязка к группе
  std::string student_id_;                  ///< Номер студенческого
  std::optional<Scholarship> scholarship_;  ///< Стипендия (может отсутствовать)
  std::vector<std::unique_ptr<Grade>> grade_book_;  ///< Зачетка (список оценок)
  int skips_hours = 0;  ///< Количество часов прогулов
};

#endif  // STUDENT_H
