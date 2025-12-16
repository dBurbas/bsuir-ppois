/**
 * @file numeric_grade.h
 * @brief Класс числовой оценки (экзамен, диф. зачет)
 * @author Dmitry Burbas
 * @date 15/12/2025
 */

#ifndef NUMERIC_GRADE_H
#define NUMERIC_GRADE_H

#include <string>
#include <utility>

#include "../../exceptions/dean_office_exceptions.h"
#include "../grade/grade.h"

/**
 * @class NumericGrade
 * @brief Представляет оценку в числовом формате (баллы)
 * @details Наследуется от Grade. Используется для экзаменов и
 * дифференцированных зачетов. Подразумевает 10-балльную шкалу (где 4 —
 * минимальный проходной балл), но жесткой верхней границы в валидации нет.
 */
class NumericGrade : public Grade {
 public:
  /**
   * @brief Конструктор числовой оценки
   * @param subject_id Идентификатор предмета
   * @param mark Оценка (по умолчанию 1)
   */
  explicit NumericGrade(std::string subject_id, const int mark = 1)
      : Grade(std::move(subject_id)), mark_(mark) {
    ValidateMark(mark_);
  }

  /**
   * @brief Устанавливает новое значение оценки
   * @param mark Новая оценка
   * @throws NumericGradeException, если оценка <= 0
   */
  void SetValue(const int mark) override {
    ValidateMark(mark);
    mark_ = mark;
  }

  /**
   * @brief Проверяет, является ли оценка положительной (сдал)
   * @return true, если оценка >= kPassMark
   * @details Порог прохождения зашит в коде.
   */
  [[nodiscard]] bool IsPassed() const override { return mark_ >= kPassMark_; }

  /**
   * @brief Строковое представление
   * @return Число в виде строки (например, "8")
   */
  [[nodiscard]] std::string ToString() const override {
    return std::to_string(mark_);
  }

  /**
   * @brief Получение числового значения
   * @return Оценка (int)
   */
  [[nodiscard]] int GetValue() const override { return mark_; }

 private:
  /**
   * @brief Проверка корректности оценки
   * @param mark Значение для проверки
   * @throws NumericGradeException, если оценка меньше или равна нулю
   */
  static void ValidateMark(const int mark) {
    if (mark <= 0 || mark > 10) {
    }
    throw NumericGradeException("NumericGrade: Mark must be [1-10]");
  }
  static constexpr int kPassMark_ = 4;  ///< Минимальная оценка для сдачи
  int mark_;                            ///< Значение оценки
};

#endif  // NUMERIC_GRADE_H
