/**
 * @file date.h
 * @brief Класс даты с валидацией и нормализацией
 * @author Dmitry Burbas
 * @date 16/11/2025
 */
#ifndef DATE_H
#define DATE_H
#include <string>

/**
 * @class Date
 * @brief Представляет собой календарную дату с проверками инвариантов и
 * операциями сравнения
 * @details Поддерживает даты от 1800 до 2100 года в формате ДД.ММ.ГГГГ.
 * Поддерживает инварианты дня, месяца и года, включая проверку с учетом
 * високосного года.
 */
class Date {
 public:
  /**
   * @brief Конструктор даты через день, месяц и год
   * @param day День месяца (1-31 в зависимости от месяца и года)
   * @param month Месяц года (1-12)
   * @param year Год (1800-2100)
   * @throws DateException, если любой из элементов даты некорректен или дата
   * пустая
   * @details Проверяет дату, включая проверку на високосный год для Февраля
   */
  Date(const int day, const int month, const int year)
      : day_(day), month_(month), year_(year) {
    Validate(day, month, year);
  }
  /**
   * @brief Конструктор даты из строки
   * @param date Строка даты в формате ДД.ММ.ГГГГ
   * @throws DateException, если формат или элементы даты некорректны
   * @details Делегирует стандартному конструктору через ParseFromString()
   */
  explicit Date(const std::string& date) : Date(ParseFromString(date)) {}
  /**
   * @brief Конструктор копирования по умолчанию
   * @param date Объект даты для копирования
   */
  Date(const Date& date) = default;

  /**
   * @brief Конструктор перемещения по умолчанию
   * @param date Объект даты для перемещения
   */
  Date(Date&& date) = default;

  /**
   * @brief Оператор присваивания-копирования по умолчанию
   * @param date Объект даты для копирования
   * @return Ссылка на этот объект даты
   */
  Date& operator=(const Date& date) = default;

  /**
   * @brief Оператор присваивания-перемещения по умолчанию
   * @param date Объект даты для перемещения
   * @return Ссылка на этот объект даты
   */
  Date& operator=(Date&& date) = default;

  /**
   * @brief Деструктор по умолчанию
   */
  ~Date() = default;

  /**
   * @brief Устанавливает все элементы даты сразу с валидацией
   * @param day День месяца (1-31 в зависимости от месяца)
   * @param month Месяц года (1-12)
   * @param year Год (1800-2100)
   * @throws DateException, если любой из элементов не корректен
   * @details Проверяет всю дату перед обновлением внутреннего состояния(полей)
   */
  void SetFullDate(int day, int month, int year);

  /**
   * @brief Получение дня даты
   * @return День месяца (1-31)
   */
  [[nodiscard]] int GetDay() const { return day_; }

  /**
   * @brief Получение месяца даты
   * @return Месяц года (1-12)
   */
  [[nodiscard]] int GetMonth() const { return month_; }

  /**
   * @brief Получение года даты
   * @return Год (1800-2100)
   */
  [[nodiscard]] int GetYear() const { return year_; }

  /**
   * @brief Преобразование даты в строковое представление
   * @return Строка даты в формате ДД.ММ.ГГГГ без пробелов
   * @details Форматирует единичные числа дней и месяцев с ведущими нулями
   */
  [[nodiscard]] std::string ToString() const;

  /**
   * @brief Оператор сравнения равенства
   * @param other Дата для сравнения
   * @return true, если все элементы дат одинаковы
   */
  bool operator==(const Date& other) const {
    return day_ == other.day_ && month_ == other.month_ && year_ == other.year_;
  }

  /**
   * @brief Оператор сравнения меньше-чем
   * @param other Дата для сравнения
   * @return true, если эта дата хронологически раньше чем other
   * @details Сравнивает сначала год, потом месяц, потом день
   */
  bool operator<(const Date& other) const {
    if (year_ != other.year_) return year_ < other.year_;
    if (month_ != other.month_) return month_ < other.month_;
    return day_ < other.day_;
  }

  /**
   * @brief Оператор сравнения неравенства
   * @param other Дата для сравнения
   * @return true, если даты не равны
   */
  bool operator!=(const Date& other) const { return !(*this == other); }

  /**
   * @brief Оператор сравнения меньше-либо-равно
   * @param other Дата для сравнения
   * @return true если эта дата хронологически раньше или равна other
   */
  bool operator<=(const Date& other) const {
    return *this < other || *this == other;
  }

  /**
   * @brief Оператор сравнения больше-чем
   * @param other Дата для сравнения
   * @return true, если эта дата хронологически позже чем other
   */
  bool operator>(const Date& other) const { return !(*this <= other); }

  /**
   * @brief Оператор сравнения больше-либо-равно
   * @param other Дата для сравнения
   * @return true если эта дата хронологически позже или равна other
   */
  bool operator>=(const Date& other) const { return !(*this < other); }

 private:
  static constexpr int kMinYear = 1800;        ///< Минимальный корректный год
  static constexpr int kMaxYear = 2100;        ///< Максимальный корректный год
  static constexpr char kDateDelimiter = '.';  ///< Разделитель для формата даты
  int day_;                                    ///< День месяца (1-31)
  int month_;                                  ///< Месяц года (1-12)
  int year_;                                   ///< Год (1800-2100)

  /**
   * @brief Проверка всех элементов даты
   * @param day День для проверки (1-31 в зависимости от месяца)
   * @param month Месяц для проверки (1-12)
   * @param year Год для проверки (1800-2100)
   * @throws DateException, если год вне отрезка значений [1800,
   * 2100]
   * @throws DateException, если месяц вне отрезка значений [1, 12]
   * @throws DateException, если день меньше 1 или превосходит максимальный день
   * в месяце
   * @details Проверяет високосные года для Февраля (29 дней в високосном году,
   * 28 в остальных)
   */
  static void Validate(int day, int month, int year);

  /**
   * @brief Выделяет дату из строки формата ДД.ММ.ГГГГ
   * @param date Строка для выделения
   * @return Выделенный объект даты
   * @throws DateException, если формат не соответствует ДД.ММ.ГГГГ
   * @throws DateException, если после даты находятся какие-либо еще символы
   * @details Использует '.' в качестве разделителя и строго проверяет формат
   */
  static Date ParseFromString(const std::string& date);

  /**
   * @brief Определяет, является ли год високосным
   * @param year Год для проверки
   * @return true, если год високосный
   * @details Високосный год делится на 4 без остатка, но не на 100 или делится
   * на 400 без остатка
   */
  static bool IsLeapYear(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
  }
};

#endif  // DATE_H
