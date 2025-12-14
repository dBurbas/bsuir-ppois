/*! @file dean_office_exceptions.h
 *  @brief Заголовочный файл с описанием иерархии классов исключений
 *  @details Содержит объявление базового класса DeanOfficeException и
 * специализированных классов исключений для различных ошибок в системе
 * деканата.
 */
#ifndef DEAN_OFFICE_EXCEPTIONS_H
#define DEAN_OFFICE_EXCEPTIONS_H
// TODO: поменять названия исключений и добавить конкретные например "Нет даты
// рождения человека"

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
 * @class PersonComponentException
 * @brief Класс исключений для некорректных операций с Person
 * @details Выбрасывается когда добавляется некорректная персональная или
 * контактная информация для человека.
 */
class PersonComponentException : public DeanOfficeException {
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
 * @class StudentException
 * @brief Класс исключений для некорректных операций с Student
 * @details Выбрасывается при
 */
class StudentException : public DeanOfficeException {
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

/**
 * @class OrderArgumentsException
 * @brief Класс исключений при отсутствии основания для приказа
 * @details Выбрасывается при создании приказа без основания
 */
class OrderArgumentsException : public DeanOfficeException {
 public:
  using DeanOfficeException::DeanOfficeException;  ///< Наследование
                                                   ///< конструкторов
};

/**
 * @class ReportPeriodException
 * @brief Класс исключений для некорректного ввода периода отчета
 * @details Выбрасывается при некорректном вводе периода отчета
 */
class ReportPeriodException : public DeanOfficeException {
 public:
  using DeanOfficeException::DeanOfficeException;  ///< Наследование
                                                   ///< конструкторов
};

/**
 * @class SalaryException
 * @brief Класс исключений для некорректных операций с зарплатой
 * @details Выбрасывается при создании зарплаты с негативным значением оклада
 * или не положительным значением ставки.
 */
class SalaryException : public DeanOfficeException {
 public:
  using DeanOfficeException::DeanOfficeException;  ///< Наследование
                                                   ///< конструкторов
};

/**
 * @class ScholarshipException
 * @brief Класс исключений для некорректных операций со стипендией
 * @details Выбрасывается при создании стипендии с негативным значением базового
 * значения или не положительным значением коэффициентом надбавки.
 */
class ScholarshipException : public DeanOfficeException {
 public:
  using DeanOfficeException::DeanOfficeException;  ///< Наследование
                                                   ///< конструкторов
};

/**
 * @class SubjectException
 * @brief Класс исключений для некорректных операций с предметами
 * @details Выбрасывается при пустых id и имени предмета и других операциях с
 * Subject
 */
class SubjectException : public DeanOfficeException {
 public:
  using DeanOfficeException::DeanOfficeException;  ///< Наследование
                                                   ///< конструкторов
};

/**
 * @class EventException
 * @brief Класс исключений для некорректных операций с событиями
 * @details Выбрасывается при некорректных операциях с Event, например дата
 * начала позже даты конца и т.п.
 */
class EventException : public DeanOfficeException {
 public:
  using DeanOfficeException::DeanOfficeException;  ///< Наследование
  ///< конструкторов
};
#endif  // DEAN_OFFICE_EXCEPTIONS_H
