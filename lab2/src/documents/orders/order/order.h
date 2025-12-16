/**
 * @file order.h
 * @brief Базовый класс для приказов
 * @author Dmitry Burbas
 * @date 13/12/2025
 */
#ifndef ORDER_H
#define ORDER_H
#include <memory>

#include "../../../exceptions/dean_office_exceptions.h"
#include "../../../people/person/person.h"
#include "../../../value_structures/date/date.h"
#include "../../document/document.h"
/*! @class Order
 *  @brief Абстрактный базовый класс для всех приказов.
 *  @details Описывает общую реализацию для приказов: основание приказа, дата
 * вступления в силу. Наследуется от документа
 */
class Order : public Document {
 public:
  /*!
   *  @brief Конструктор приказа
   *  @param name Уникальное имя приказа
   *  @param issue_date Дата выдачи(создания) приказа
   *  @param foundation Основание приказа(документ)
   *  @param effective_date Дата вступления приказа в силу
   *  @throw OrderFoundationException, если нет основания для приказа или дата
   * вступления в силу раньше чем дата выдачи приказа
   */
  Order(std::string name, const Date& issue_date,
        std::shared_ptr<const Document> foundation, const Date& effective_date)
      : Document(std::move(name), issue_date),
        foundation_document_(std::move(foundation)),
        effective_date_(effective_date) {
    if (!foundation_document_)
      throw OrderArgumentsException("No order foundation");
    if (effective_date_ < issue_date)
      throw OrderArgumentsException(
          "Effective date cannot be earlier than issue date");
  }

  /*!
   *  @brief Возвращает документ на котором основывается приказ
   *  @return Объект документа (основание приказа)
   */
  [[nodiscard]] const Document& GetFoundation() const {
    return *foundation_document_;
  }

  /*!
   *  @brief Возвращает дату вступления приказа в силу
   *  @return Объект даты вступления в силу
   */
  [[nodiscard]] const Date& GetEffectiveDate() const { return effective_date_; }

 protected:
  /*!
   *  @brief Проверка доступа к подписанию человека
   *  @details Чисто виртуальный метод который нужно реализовать всем
   * наследникам
   *  @param signer Ссылка на объект Person, выступающего в роли подписанта
   *  @return True, если человек имеет нужные права доступа, в ином случае false
   */
  [[nodiscard]] bool CheckSignerAccess(const Person& signer) const override = 0;

 private:
  std::shared_ptr<const Document>
      foundation_document_;  ///< Основание приказа(документ)
  Date effective_date_;      ///< Дата вступления приказа в силу
};

#endif  // ORDER_H
