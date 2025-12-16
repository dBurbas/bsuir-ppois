/**
 * @file academic_leave_order.h
 * @brief Класс приказа о предоставлении академического отпуска
 * @author Dmitry Burbas
 * @date 14/12/2025
 */

#ifndef ACADEMIC_LEAVE_ORDER_H
#define ACADEMIC_LEAVE_ORDER_H

#include <memory>
#include <string>
#include <utility>

#include "../../../people/dean/dean.h"
#include "../../../people/dean_deputy/dean_deputy.h"
#include "../order/order.h"

/**
 * @class AcademicLeaveOrder
 * @brief Приказ об академическом отпуске студента
 * @details Наследуется от Order. Разрешает подписание Декану или его
 * заместителю. Служит основанием для перевода студента в статус AcademicLeave.
 */
class AcademicLeaveOrder : public Order {
 public:
  /**
   * @brief Конструктор приказа об академическом отпуске
   * @param name Номер приказа
   * @param issue_date Дата издания
   * @param foundation Основание (медицинская справка и т.д.)
   * @param effective_date Дата начала отпуска
   */
  AcademicLeaveOrder(std::string name, const Date& issue_date,
                     std::shared_ptr<const Document> foundation,
                     const Date& effective_date)
      : Order(std::move(name), issue_date, std::move(foundation),
              effective_date) {}

 protected:
  /**
   * @brief Проверка прав подписи
   * @param signer Подписант
   * @return true, если подписант — Декан или Замдекана
   * @details Использует dynamic_cast для проверки полномочий.
   */
  [[nodiscard]] bool CheckSignerAccess(const Person& signer) const override {
    return dynamic_cast<const Dean*>(&signer) != nullptr ||
           dynamic_cast<const DeanDeputy*>(&signer) != nullptr;
  }
};

#endif  // ACADEMIC_LEAVE_ORDER_H
