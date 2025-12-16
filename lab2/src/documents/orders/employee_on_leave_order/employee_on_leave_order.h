/**
 * @file employee_on_leave_order.h
 * @brief Класс приказа о предоставлении отпуска сотруднику
 * @author Dmitry Burbas
 * @date 13/12/2025
 */

#ifndef EMPLOYEE_ON_LEAVE_ORDER_H
#define EMPLOYEE_ON_LEAVE_ORDER_H

#include <memory>
#include <string>
#include <utility>

#include "../../document/document.h"
#include "../order/order.h"

/**
 * @class EmployeeOnLeaveOrder
 * @brief Приказ об отпуске сотрудника
 * @details Наследуется от Order. Используется для изменения статуса сотрудника
 * на "OnLeave". Требует реализации проверки прав подписи.
 */
class EmployeeOnLeaveOrder : public Order {
 public:
  /**
   * @brief Конструктор приказа об отпуске
   * @param name Номер приказа
   * @param issue_date Дата издания
   * @param foundation Основание (заявление сотрудника)
   * @param effective_date Дата начала отпуска
   */
  EmployeeOnLeaveOrder(std::string name, const Date& issue_date,
                       std::shared_ptr<const Document> foundation,
                       const Date& effective_date)
      : Order(std::move(name), issue_date, std::move(foundation),
              effective_date) {}

 protected:
  /**
   * @brief Проверка прав подписи
   * @param signer Подписант
   * @return true (Временная заглушка)
   * @details Метод необходим, так как базовый метод в Order чисто виртуальный.
   * Без этой реализации класс остался бы абстрактным.
   */
  [[nodiscard]] bool CheckSignerAccess(const Person& signer) const override {
    (void)signer;
    return true;  // Разрешаем всем для тестирования
  }
};

#endif  // EMPLOYEE_ON_LEAVE_ORDER_H
