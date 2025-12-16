/**
 * @file grade.h
 * @brief Абстрактный базовый класс для всех видов оценок
 * @author Dmitry Burbas
 * @date 14/12/2025
 */

#ifndef GRADE_H
#define GRADE_H

#include <string>
#include <utility>

#include "../../exceptions/dean_office_exceptions.h"

/**
 * @class Grade
 * @brief Интерфейс оценки по предмету
 * @details Определяет общий контракт для работы с результатами обучения.
 * Конкретные реализации (NumericGrade, PassFailGrade) определяют способ
 * хранения и интерпретации значения оценки.
 */
class Grade {
 public:
  /**
   * @brief Конструктор оценки
   * @param subject_id Уникальный идентификатор предмета
   * @throws GradeException, если ID предмета пуст
   */
  explicit Grade(std::string subject_id) : subject_id_(std::move(subject_id)) {
    ValidateSubject(subject_id_);
  }

  /**
   * @brief Виртуальный деструктор по умолчанию
   */
  virtual ~Grade() = default;

  /**
   * @brief Проверяет, является ли оценка положительной
   * @return true, если предмет сдан успешно
   */
  [[nodiscard]] virtual bool IsPassed() const = 0;

  /**
   * @brief Строковое представление оценки
   * @return Человеко-читаемая строка (например, "8" или "Passed")
   */
  [[nodiscard]] virtual std::string ToString() const = 0;

  /**
   * @brief Устанавливает значение оценки из целого числа
   * @param mark Числовое представление оценки
   * @warning Семантика параметра mark зависит от конкретного подкласса.
   * Для зачетов может происходить неявное приведение к bool.
   */
  virtual void SetValue(int mark) = 0;

  /**
   * @brief Получает численное значение оценки
   * @return Оценка в виде числа (для расчетов среднего балла и т.п.)
   */
  [[nodiscard]] virtual int GetValue() const = 0;

  /**
   * @brief Получение идентификатора предмета
   */
  [[nodiscard]] const std::string& GetSubjectId() const { return subject_id_; }

 protected:
  /**
   * @brief Проверяет корректность привязки к предмету
   * @param subject_id ID предмета
   * @throws GradeException если ID пуст
   */
  static void ValidateSubject(const std::string& subject_id) {
    if (subject_id.empty()) {
      throw GradeException("Grade must belong to a subject");
    }
  }

  std::string
      subject_id_;  ///< Идентификатор предмета, по которому получена оценка
};

#endif  // GRADE_H
