/**
 * @file salary.h
 * @brief Класс зарплаты
 * @author Dmitry Burbas
 * @date 14/12/2025
 */
#ifndef SALARY_H
#define SALARY_H
#include "../exceptions/dean_office_exceptions.h"

/*! @class Salary
 *  @brief Класс для всех зарплат.
 *  @details Описывает минимальную реализацию зарплаты для сотрудника.
 */
class Salary {
 public:
  /*!
   *  @brief Конструктор зарплаты
   *  @param base Базовый оклад
   *  @param rate Ставка
   */
  explicit Salary(const double base, const double rate) {
    SetBase(base);
    SetRate(rate);
  }

  /*!
   *  @brief Устанавливает значение оклада
   *  @param base Новое значение оклада
   */
  void SetBase(const double base) {
    if (base < 0.0) throw SalaryException("Salary base cannot be negative");
    base_value_ = base;
  }

  /*!
   *  @brief Устанавливает значение ставки
   *  @param rate Новое значение ставки
   */
  void SetRate(const double rate) {
    if (rate <= 0.0) throw SalaryException("Salary rate must be > 0");
    rate_ = rate;
  }

  /*!
   *  @brief Возвращает значение зарплаты
   *  @return Дробное значение зарплаты
   */
  [[nodiscard]] double GetSalary() const { return (base_value_ * rate_); }

  /*!
   *  @brief Возвращает оклад зарплаты
   *  @return Дробное значение оклада
   */
  [[nodiscard]] double GetBase() const { return base_value_; }

  /*!
   *  @brief Возвращает ставку зарплаты
   *  @return Дробное значение ставки
   */
  [[nodiscard]] double GetRate() const { return rate_; }

 private:
  double base_value_ = 0.0;  ///< Оклад зарплаты(0 по умолчанию)
  double rate_ = 1.0;        ///< Ставка зарплаты(1.0 по умолчанию)
};

#endif  // SALARY_H
