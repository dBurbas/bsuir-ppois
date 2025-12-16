/**
 * @file pass_fail_grade.h
 * @brief Класс оценки для зачета (зачтено/не зачтено)
 * @author Dmitry Burbas
 * @date 15/12/2025
 */

#ifndef PASS_FAIL_GRADE_H
#define PASS_FAIL_GRADE_H

#include <string>
#include <utility>

#include "../grade/grade.h"

/**
 * @class PassFailGrade
 * @brief Представляет бинарную оценку (зачет)
 * @details Наследуется от абстрактного класса Grade. Хранит результат
 * в виде булева значения (true - зачтено, false - не зачтено).
 */
class PassFailGrade : public Grade {
 public:
  /**
   * @brief Конструктор зачета
   * @param subject_id Идентификатор предмета
   * @param mark Результат зачета (по умолчанию false - не зачтено)
   */
  explicit PassFailGrade(std::string subject_id, const bool mark = false)
      : Grade(std::move(subject_id)), mark_(mark) {}

  /**
   * @brief Устанавливает результат зачета из целого числа
   * @param mark Числовое представление (0 - не зачтено, любое другое - зачтено)
   * @details Переопределяет виртуальный метод базового класса.
   * Происходит неявное преобразование int -> bool.
   * @warning Любое ненулевое значение (включая отрицательные) считается
   * "зачтено".
   */
  void SetValue(const int mark) override { mark_ = (mark != 0); }

  /**
   * @brief Проверяет, сдан ли зачет
   * @return true, если зачтено
   */
  [[nodiscard]] bool IsPassed() const override { return mark_; }

  /**
   * @brief Строковое представление оценки
   * @return "Passed" или "Failed"
   */
  [[nodiscard]] std::string ToString() const override {
    if (!mark_) return "Failed";
    return "Passed";
  }

  /**
   * @brief Числовое представление оценки
   * @return 1, если зачтено, 0, если не зачтено
   */
  [[nodiscard]] int GetValue() const override { return mark_ ? 1 : 0; }

 private:
  bool mark_;  ///< Результат зачета
};

#endif  // PASS_FAIL_GRADE_H
