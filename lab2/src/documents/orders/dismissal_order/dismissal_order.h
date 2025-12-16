/**
 * @file dismissal_order.h
 * @brief Класс приказа об увольнении сотрудника
 * @author Dmitry Burbas
 * @date 13/12/2025
 */

#ifndef DISMISSAL_ORDER_H
#define DISMISSAL_ORDER_H

#include <memory>
#include <string>
#include <utility>

#include "../../document/document.h"
#include "../order/order.h"

/**
 * @class DismissalOrder
 * @brief Приказ об увольнении
 * @details Наследуется от Order. Служит основанием для перевода сотрудника
 * в статус Fired. Требует реализации проверки прав подписи.
 */
class DismissalOrder : public Order {
 public:
  /**
   * @brief Конструктор приказа об увольнении
   * @param name Номер приказа
   * @param issue_date Дата издания
   * @param foundation Основание (заявление по собственному / статья ТК)
   * @param effective_date Дата увольнения
   */
  DismissalOrder(std::string name, const Date& issue_date,
                 std::shared_ptr<const Document> foundation,
                 const Date& effective_date)
      : Order(std::move(name), issue_date, std::move(foundation),
              effective_date) {}

 protected:
  /**
   * @brief Проверка прав подписи
   * @param signer Подписант
   * @return true (Временная заглушка)
   * @details Метод необходим для инстанцирования класса.
   * TODO: Реализовать проверку (например, только Ректор может увольнять).
   */
  [[nodiscard]] bool CheckSignerAccess(const Person& signer) const override {
    (void)signer;
    // TODO: Добавить логику dynamic_cast<const Rector*>(&signer)
    return true;
  }
};

#endif  // DISMISSAL_ORDER_H
