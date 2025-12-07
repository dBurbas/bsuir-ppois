/*! @file dean_office_exceptions.h
 *  @brief Заголовочный файл с описанием иерархии классов исключений
 *  @details Содержит объявление базового класса DeanOfficeException и
 * специализированных классов исключений для различных ошибок в системе
 * деканата.
 */
#ifndef DEAN_OFFICE_EXCEPTIONS_H
#define DEAN_OFFICE_EXCEPTIONS_H

#include "base_exception.h"
/**
 * @class DeanOfficeException
 * @brief Базовый класс для всех исключений в предметной области деканата
 * @details Наследуется от std::exception и предоставляет базовую
 * функциональность для хранения и вывода сообщений об ошибках. Все
 * пользовательские исключения в предметной области деканата должны
 * наследоваться от этого класса.
 */
class DeanOfficeException : public BaseException {
 public:
  using BaseException::BaseException;  ///< Наследование конструкторов
};

/**
 * @class PersonException
 * @brief Класс исключений для некорректных операций с Person
 * @details Выбрасывается когда добавляется некорректная персональная или
 * контактная информация для человека.
 */
class PersonException : public DeanOfficeException {
 public:
  using DeanOfficeException::DeanOfficeException;  ///< Наследование
                                                   ///< конструкторов
};

/**
 * @class EmployeeException
 * @brief Класс исключений для некорректных операций с Employee
 * @details Выбрасывается при некорректной установке опыта, зарплаты или
 * ставки заработной платы.
 */
class EmployeeException : public DeanOfficeException {
 public:
  using DeanOfficeException::DeanOfficeException;  ///< Наследование
                                                   ///< конструкторов
};

/**
 * @class DocumentException
 * @brief Класс исключений для некорректных операций с Document
 * @details Выбрасывается при некорректном подписании документа (недостаточные
 * права подписанта, документ уже подписан).
 */
class DocumentException : public DeanOfficeException {
 public:
  using DeanOfficeException::DeanOfficeException;  ///< Наследование
                                                   ///< конструкторов
};

#endif  // DEAN_OFFICE_EXCEPTIONS_H
