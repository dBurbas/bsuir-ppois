/*! @file components_exceptions.h
 *  @brief Заголовочный файл с описанием иерархии вспомогательных классов
 * исключений
 *  @details Содержит объявление
 * специализированных классов исключений для различных ошибок в компонентах
 * используемых системой деканата.
 */

#ifndef COMPONENTS_EXCEPTIONS_H
#define COMPONENTS_EXCEPTIONS_H
#include <string>

#include "base_exception.h"

/**
 * @class BaseComponentException
 * @brief Базовый класс исключений для компонент
 * @details Наследуется от BaseException
 */
class BaseComponentException : public BaseException {
 public:
  using BaseException::BaseException;  ///< Наследование конструкторов
};

/**
 * @class DateException
 * @brief Класс исключения для некорректных операций с датой
 * @details Выбрасывается при сбое проверки даты, включая некорректные
 * комбинации день/месяц/год, значения за пределами допустимого(год не в
 * [1800,2100], месяц не 1-12), некорректный день для данного месяца (например
 * 30 Февраля) или некорректный формат строки даты.
 */
class DateException : public BaseComponentException {
 public:
  /**
   * @brief Конструктор с сообщением об ошибке
   * @param message Сообщение об ошибке (в виде std::string)
   */
  explicit DateException(std::string message)
      : BaseComponentException(std::move(message)) {}

  /**
   * @brief Конструктор с сообщением об ошибке и полями даты
   * @param message Сообщение об ошибке (в виде std::string)
   * @param day День даты, вызвавшей исключение
   * @param month Месяц даты, вызвавшей исключение
   * @param year Год даты, вызвавшей исключение
   */
  DateException(std::string message, const int day, const int month,
                const int year)
      : BaseComponentException(std::move(message)),
        day_(day),
        month_(month),
        year_(year) {}

  /**
   * @brief Геттер для дня даты, вызвавшей исключение
   * @return Число дня даты, вызвавшей исключение
   */
  [[nodiscard]] int day() const noexcept { return day_; }

  /**
   * @brief Геттер для месяца даты, вызвавшей исключение
   * @return Число месяца даты, вызвавшей исключение
   */
  [[nodiscard]] int month() const noexcept { return month_; }

  /**
   * @brief Геттер для года даты, вызвавшей исключение
   * @return Число года даты, вызвавшей исключение
   */
  [[nodiscard]] int year() const noexcept { return year_; }

 private:
  int day_ = 0;
  int month_ = 0;
  int year_ = 0;
};

/**
 * @class PersonalInfoException
 * @brief Класс исключений для некорректной личной информации
 * @details Выбрасывается при сбое проверки личной информации, например пустое
 * имя или другие подобные недопустимые ошибки.
 */
class PersonalInfoException : public BaseComponentException {
 public:
  using BaseComponentException::BaseComponentException;  ///< Наследование
                                                         ///< конструкторов
};

/**
 * @class ContactInfoException
 * @brief Класс исключения для некорректной контактной информации
 * @details Выбрасывается при сбое проверки контактной информации, включая
 * некорректный формат номера телефона (не соответствует шаблону +375*********),
 * некорректный формат электронной почты (не соответствует шаблону regex для
 * электронной почты), пустые необходимые поля или при попытке доступа к пустому
 * необязательному полю адреса.
 */
class ContactInfoException : public BaseComponentException {
 public:
  using BaseComponentException::BaseComponentException;  ///< Наследование
                                                         ///< конструкторов
};

/**
 * @class AddressException
 * @brief Класс исключений для некорректной информации адреса. Exception class
 * for invalid address information
 * @details Выбрасывается при сбоях проверки адреса или при сбоях парсинга,
 * например некорректного формата строки адреса, пустых необходимых компонент
 * адреса или других запрещенных операциях связанных с полями адреса(улица,
 * город и т.п.).
 */
class AddressException : public BaseComponentException {
 public:
  using BaseComponentException::BaseComponentException;  ///< Наследование
                                                         ///< конструкторов
};
#endif  // COMPONENTS_EXCEPTIONS_H
