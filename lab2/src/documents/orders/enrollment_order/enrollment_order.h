/**
 * @file enrollment_order.h
 * @brief Класс приказа о зачислении студента
 * @author Dmitry Burbas
 * @date 15/12/2025
 */

#ifndef ENROLLMENT_ORDER_H
#define ENROLLMENT_ORDER_H

#include <memory>
#include <string>
#include <utility>

#include "../../document/document.h"
#include "../order/order.h"
// Необходимо добавить include для структур PersonalInfo и ContactInfo
// #include "../../people/person/person.h"

/**
 * @class EnrollmentOrder
 * @brief Приказ о зачислении абитуриента в число студентов
 * @details Содержит данные будущего студента (ФИО, контакты) и информацию
 * о направлении (специальность, группа), куда он зачисляется.
 */
class EnrollmentOrder : public Order {
 public:
  /**
   * @brief Конструктор приказа о зачислении
   * @param name Номер приказа
   * @param issue_date Дата создания
   * @param foundation Основание (например, заявление абитуриента)
   * @param effective_date Дата зачисления
   * @param student_info Персональные данные студента
   * @param contact_info Контактная информация
   * @param speciality_code Код специальности
   * @param group_id ID группы
   */
  EnrollmentOrder(std::string name, const Date& issue_date,
                  std::shared_ptr<const Document> foundation,
                  const Date& effective_date, PersonalInfo student_info,
                  ContactInfo contact_info, std::string speciality_code,
                  std::string group_id)
      : Order(std::move(name), issue_date, std::move(foundation),
              effective_date),
        student_personal_info_(std::move(student_info)),
        student_contact_info_(std::move(contact_info)),
        speciality_code_(std::move(speciality_code)),
        group_id_(std::move(group_id)) {}

  /**
   * @brief Получение персональных данных зачисляемого
   */
  [[nodiscard]] const PersonalInfo& GetStudentPersonalInfo() const {
    return student_personal_info_;
  }

  /**
   * @brief Получение контактов
   */
  [[nodiscard]] const ContactInfo& GetStudentContactInfo() const {
    return student_contact_info_;
  }

  /**
   * @brief Получение кода специальности
   */
  [[nodiscard]] const std::string& GetSpecialityCode() const {
    return speciality_code_;
  }

  /**
   * @brief Получение ID целевой группы
   */
  [[nodiscard]] const std::string& GetGroupId() const { return group_id_; }

 protected:
  /**
   * @brief Проверка прав подписи
   * @param signer Подписант
   * @return true (Всегда разрешено для тестов)
   * @warning Метод не реализован. Возвращает true, блокируя подписание любых
   * приказов. Ожидается реализация проверки на роль Ректора.
   */
  [[nodiscard]] bool CheckSignerAccess(const Person& signer) const override {
    (void)signer;  // Подавление warning о неиспользуемом параметре
    return true;   // TODO: Реализовать проверку dynamic_cast<const Rector*>
  }

 private:
  PersonalInfo
      student_personal_info_;         ///< Данные для создания профиля студента
  ContactInfo student_contact_info_;  ///< Контакты
  std::string speciality_code_;       ///< Специальность
  std::string group_id_;              ///< Группа
};

#endif  // ENROLLMENT_ORDER_H
