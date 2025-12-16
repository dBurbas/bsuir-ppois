/**
 * @file document.h
 * @brief Базовый класс для документов
 * @author Dmitry Burbas
 * @date 16/11/2025
 */
#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <string>

#include "../../exceptions/dean_office_exceptions.h"
#include "../../people/person/person.h"
#include "../../value_structures/date/date.h"

/*! @class Document
 *  @brief Абстрактный базовый класс для всех документов.
 *  @details Описывает общий интерфейс для документов: имя, дата выдачи
 *  и состояния подписания. Предназначен для наследования конкретными типами
 *  документов
 */
class Document {
 public:
  /*!
   *  @brief Конструктор документа
   *  @param name Уникальное имя документа
   *  @param issue_date Дата выдачи(создания) документа
   */
  Document(std::string name, const Date& issue_date)
      : name_(std::move(name)), issue_date_(issue_date) {}
  /*!
   *  @brief Виртуальный деструктор
   *  @details Гарантировать правильное разрушение всех наследников при удалении
   * через указатель на базовый класс документа
   */
  virtual ~Document() = default;

  /*!
   *  @brief Возвращает название документа
   *  @return Строка содержащая уникальное имя документа
   */
  [[nodiscard]] const std::string& GetName() const { return name_; }

  /*!
   *  @brief Возвращает дату выдачи(создания документа)
   *  @return Date объект представляющий дату выдачи документа
   */
  [[nodiscard]] const Date& GetIssueDate() const { return issue_date_; }

  /*!
   *  @brief Проверяет подписан ли уже документ
   *  @return True, если документ подписан, в ином случае false
   */
  [[nodiscard]] bool IsSigned() const { return is_signed_; }

  /*!
   *  @brief Подписание документа
   *  @details Подписывает документ, если он уже не подписан и если подписант
   *  обладает правами доступа
   *  @param signer Ссылка на объект Person, выступающего в роли подписанта
   */
  void Sign(const Person& signer) {
    if (is_signed_)
      throw DocumentException("Document " + name_ + " already signed");
    if (!CheckSignerAccess(signer))
      throw DocumentException(
          "Signer is not authorised for this document type");
    OnSigning(signer);
    is_signed_ = true;
  }

 protected:
  /*!
   *  @brief Проверка доступа к подписанию человека
   *  @details Чисто виртуальный метод который нужно реализовать всем
   * наследникам
   *  @param signer Ссылка на объект Person, выступающего в роли подписанта
   *  @return True, если человек имеет нужные права доступа, в ином случае false
   */
  [[nodiscard]] virtual bool CheckSignerAccess(const Person& signer) const = 0;

  /*!
   *  @brief Действие, выполняющееся при подписании
   *  @details Виртуальный метод, который могут реализовать наследники
   *  @param signer Ссылка на объект Person, выступающего в роли подписанта
   */
  virtual void OnSigning(const Person& signer) { (void)signer; };

 private:
  std::string name_;        ///< Уникальное имя документа
  Date issue_date_;         ///< Дата выдачи документа
  bool is_signed_ = false;  ///< Флаг, указывающий на то, что документ подписан
};

#endif  // DOCUMENT_H
