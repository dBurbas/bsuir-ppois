/**
 * @file person.h
 * @brief Базовый класс для людей
 * @author Dmitry Burbas
 * @date 11/11/2025
 */
#ifndef PERSON_H
#define PERSON_H

#include "../../exceptions/components_exceptions.h"
#include "../../exceptions/dean_office_exceptions.h"
#include "../../value_structures/contact_info/contact_info.h"
#include "../../value_structures/personal_info/personal_info.h"

/*! @class Person
 *  @brief Абстрактный базовый класс для всех людей.
 *  @details Описывает общий интерфейс для людей: личная информация(ФИО, день
 *  рождения), контактная информация(номер телефона, адрес электронной почты,
 *  адрес). Предназначен для наследования
 *  конкретными людьми (студентами, работниками и т.д.)
 */
class Person {
 public:
  /*!
   *  @brief Конструктор человека
   *  @param personal_info Личная информация человека
   *  @param contact_info Контактная информация человека
   *  @throw PersonComponentException, если нет дня рождения человека
   */
  Person(const PersonalInfo& personal_info, const ContactInfo& contact_info)
      : personal_info_(personal_info), contact_info_(contact_info) {
    try {
      (void)personal_info_.GetBirthDate();
    } catch (const PersonalInfoException& e) {
      throw PersonComponentException("No birth date for person:" +
                                     std::string(e.what()));
    }
  }
  /*!
   *  @brief Виртуальный деструктор
   *  @details Гарантировать правильное разрушение всех наследников при удалении
   * через указатель на базовый класс человека
   */
  virtual ~Person() = default;

  /*!
   *  @brief Установка адреса электронной почты человека
   *  @param email Строка представляющая собой адрес электронной почты
   *  @details Делегирует реализацию полю контактной информации
   *  @throw PersonComponentException, пробрасывает исключение контактной
   * информации
   */
  void SetEmail(const std::string& email) {
    try {
      contact_info_.SetEmail(email);
    } catch (const ContactInfoException& e) {
      throw PersonComponentException("Person error:" + std::string(e.what()));
    }
  }

  /*!
   *  @brief Установка номера телефона человека
   *  @param phone_number Строка представляющая собой номер телефона
   *  @details Делегирует реализацию полю контактной информации
   *  @throw PersonComponentException, пробрасывает исключение контактной
   * информации
   */
  void SetPhoneNumber(const std::string& phone_number) {
    try {
      contact_info_.SetPhoneNumber(phone_number);
    } catch (const ContactInfoException& e) {
      throw PersonComponentException("Person error:" + std::string(e.what()));
    }
  }

  /*!
   *  @brief Возвращает полную личную информацию человека
   *  @return Объект PersonalInfo со всей личной информацией
   */
  [[nodiscard]] const PersonalInfo& GetPersonalInfo() const {
    return personal_info_;
  }
  /*!
   *  @brief Возвращает полную контактную информацию человека
   *  @return Объект ContactInfo со всей контактной информацией
   */
  [[nodiscard]] const ContactInfo& GetContactInfo() const {
    return contact_info_;
  }

  /*!
   *  @brief Возвращает только ФИО человека
   *  @return Строка представляющая собой ФИО
   */
  [[nodiscard]] std::string GetFullName() const {
    return personal_info_.GetFullName();
  }

  /*!
   *  @brief Возвращает только дату рождения человека
   *  @return Объект Date представляющий собой дату рождения
   */
  [[nodiscard]] const Date& GetBirthDate() const {
    return personal_info_.GetBirthDate();
  }

  /*!
   *  @brief Возвращает только адрес электронной почты человека
   *  @return Строка представляющая собой адрес электронной почты
   */
  [[nodiscard]] std::string GetEmail() const {
    return contact_info_.GetEmail();
  }

  /*!
   *  @brief Возвращает только телефонный номер человека
   *  @return Строка представляющая собой телефонный номер
   */
  [[nodiscard]] std::string GetPhoneNumber() const {
    return contact_info_.GetPhoneNumber();
  }

 protected:
  PersonalInfo personal_info_;  ///< Личная информация человека
  ContactInfo contact_info_;    ///< Контактная информация человека
};

#endif  // PERSON_H
