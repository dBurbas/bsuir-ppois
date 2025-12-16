/**
 * @file expulsion_order.h
 * @brief Класс приказа об отчислении обучающегося
 * @author Dmitry Burbas
 * @date 13/12/2025
 */

#ifndef EXPULSION_ORDER_H
#define EXPULSION_ORDER_H

#include <memory>
#include <string>
#include <utility>

#include "../../../people/dean/dean.h"
#include "../../orders/order/order.h"

/**
 * @class ExpulsionOrder
 * @brief Приказ об отчислении студента
 * @details Наследуется от базового класса Order.
 * Определяет специфическую логику проверки прав подписи:
 * отчислить студента может только Декан (Dean).
 */
class ExpulsionOrder : public Order {
 public:  // ДОБАВЛЕНО: Без этого конструктор был private
  /**
   * @brief Конструктор приказа об отчислении
   * @param name Название/номер приказа
   * @param issue_date Дата создания
   * @param foundation Основание для приказа (ссылка на документ, например,
   * "Протокол комиссии")
   * @param effective_date Дата вступления в силу
   */
  ExpulsionOrder(std::string name, const Date& issue_date,
                 std::shared_ptr<const Document> foundation,
                 const Date& effective_date)
      : Order(std::move(name), issue_date, std::move(foundation),
              effective_date) {}

  /**
   * @brief Проверка прав подписи
   * @param signer Человек, пытающийся подписать приказ
   * @return true, если подписывающий является Деканом
   * @details Использует dynamic_cast для проверки типа объекта во время
   * выполнения. Требует, чтобы класс Person имел хотя бы один
   * виртуальный метод.
   */
  [[nodiscard]] bool CheckSignerAccess(const Person& signer) const override {
    return dynamic_cast<const Dean*>(&signer) != nullptr;
  }
};

#endif  // EXPULSION_ORDER_H
