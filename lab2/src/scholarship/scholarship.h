/**
 * @file scholarship.h
 * @brief Класс для расчета стипендии
 * @author Dmitry Burbas
 * @date 13/12/2025
 */

#ifndef SCHOLARSHIP_H
#define SCHOLARSHIP_H

#include <cmath>
#include <string>

#include "../exceptions/dean_office_exceptions.h"

/**
 * @class Scholarship
 * @brief Управляет расчетом размера стипендии на основе базовой ставки и
 * коэффициента.
 * @details Класс обеспечивает валидацию входных данных, предотвращая установку
 * некорректных значений базы или коэффициента. Итоговая сумма рассчитывается
 * путем округления произведения базы на коэффициент.
 */
class Scholarship {
 public:
  /**
   * @brief Конструктор стипендии с параметрами по умолчанию
   * @param base Базовая сумма стипендии (по умолчанию 100)
   * @param rate Коэффициент стипендии (по умолчанию 1.0)
   * @throws ScholarshipException, если переданные параметры выходят за
   * допустимые границы
   * @details Вызывает методы SetBase и SetRate для инициализации, обеспечивая
   * единую точку валидации данных.
   */
  explicit Scholarship(const int base = kMinBase,
                       const double rate = kMinRate) {
    SetBase(base);
    SetRate(rate);
  }

  /**
   * @brief Устанавливает базовый размер стипендии
   * @param base Новая базовая сумма (должна быть >= kMinBase)
   * @throws ScholarshipException, если base меньше минимально допустимого
   * значения
   */
  void SetBase(const int base) {
    if (base < kMinBase)
      throw ScholarshipException("Scholarship base cannot be <" +
                                 std::to_string(kMinBase));
    base_ = base;
  }

  /**
   * @brief Устанавливает коэффициент стипендии
   * @param rate Новый коэффициент (должен быть > 0 и <= kMaxRate)
   * @throws ScholarshipException, если rate выходит за пределы (0, kMaxRate]
   * @details Коэффициент определяет надбавку или тип стипендии (обычная,
   * повышенная).
   */
  void SetRate(const double rate) {
    if (rate <= 0 || rate > kMaxRate)
      throw ScholarshipException("Scholarship rate must be > 0 and <= " +
                                 std::to_string(kMaxRate));
    rate_ = rate;
  }

  /**
   * @brief Вычисляет итоговый размер стипендии
   * @return Округленное до ближайшего целого значение (base * rate)
   * @details Использует std::lround для корректного математического округления.
   * Результат приводится к типу int.
   */
  [[nodiscard]] int GetValue() const {
    return static_cast<int>(std::lround(base_ * rate_));
  }

  /**
   * @brief Получение текущего коэффициента
   * @return Значение коэффициента типа double
   */
  [[nodiscard]] double GetRate() const { return rate_; }

  /**
   * @brief Получение текущей базовой ставки
   * @return Значение базы типа int
   */
  [[nodiscard]] int GetBase() const { return base_; }

 private:
  static constexpr int kMinBase =
      100;  ///< Минимальная база (защита от "нулевых" начислений)
  static constexpr double kMinRate =
      1.0;  ///< Стандартный коэффициент по умолчанию
  static constexpr double kMaxRate =
      10.0;  ///< Максимальный коэффициент (защита от ошибок ввода)

  int base_ = kMinBase;     ///< Базовая часть стипендии
  double rate_ = kMinRate;  ///< Множитель стипендии
};

#endif  // SCHOLARSHIP_H
