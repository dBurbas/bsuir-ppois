/**
 * @file expulsion_application.h
 * @brief Заявление об отчислении по собственному желанию (или без желания)
 * @author Dmitry Burbas
 * @date 16/12/2025
 */

#ifndef EXPULSION_APPLICATION_H
#define EXPULSION_APPLICATION_H
#include "../../document/document.h"

/**
 * @class ExpulsionApplication
 * @brief Заявление студента на отчисление
 * @details Класс-маркер, символизирующий конец академической карьеры.
 * В данный момент не содержит данных, как и работа студента,
 * который это пишет в 3 часа ночи.
 *
 * @warning Использование данного класса обычно приводит к вызову деструктора
 * объекта Student и освобождению памяти в мире.
 *
 */
class ExpulsionApplication : public Document {
 public:
  /**
   * @brief Конструктор приказа об академическом отпуске
   * @param name Номер приказа
   * @param issue_date Дата издания
   */
  ExpulsionApplication(std::string name, const Date& issue_date)
      : Document(std::move(name), issue_date) {}
  // Пустота внутри, как и в душе после сессии.
};

#endif  // EXPULSION_APPLICATION_H
