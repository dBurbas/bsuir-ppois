/*! @file base_exception.h
 *  @brief Заголовочный файл для базового класса исключения
 *  @details Содержит объявление базового класса исключения от которого
 * наследуются все остальные классы исключений в системе
 */
#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H

#include <exception>
#include <string>

/**
 * @class BaseException
 * @brief Базовый класс для всех исключений в этой системе
 * @details Наследуется от std::exception и предоставляет базовую
 * функциональность для хранения и вывода сообщений об ошибках.
 */
class BaseException : public std::exception {
 public:
  /**
   * @brief Конструктор с сообщением об ошибке
   * @param message Сообщение об ошибке (в виде std::string)
   */
  explicit BaseException(std::string message) : message_(std::move(message)) {}

  /**
   * @brief Получить сообщение об ошибке
   * @return Указатель на C-строку с сообщением об ошибке
   */
  [[nodiscard]] const char* what() const noexcept override {
    return message_.c_str();
  }

 private:
  std::string message_;  ///< Сообщение об ошибке
};
#endif  // BASE_EXCEPTION_H
