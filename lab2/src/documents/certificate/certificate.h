/**
 * @file certificate.h
 * @brief Класс справки
 * @author Dmitry Burbas
 * @date 13/12/2025
 */

#ifndef CERTIFICATE_H
#define CERTIFICATE_H

#include <memory>
#include <string>
#include <utility>

#include "../../people/dean/dean.h"
#include "../../people/student/student.h"
#include "../document/document.h"

/**
 * @class Certificate
 * @brief Справка о статусе студента
 * @details Наследуется от Document. Выдается студенту для предоставления
 * по месту требования. Подписывается только Деканом.
 */
class Certificate : public Document {
 public:
  /**
   * @brief Конструктор справки
   * @param name Название документа (например, "Справка №123")
   * @param date Дата выдачи
   * @param student Студент, которому выдается справка (слабая ссылка)
   * @param purpose Цель выдачи (по умолчанию "по месту требования")
   */
  Certificate(std::string name, const Date& date,
              std::weak_ptr<Student> student,
              std::string purpose = "по месту требования")
      : Document(std::move(name), date),
        student_(std::move(student)),
        purpose_(std::move(purpose)) {}

 protected:
  /**
   * @brief Проверка прав подписи
   * @param signer Подписант
   * @return true, если подписант — Декан
   */
  [[nodiscard]] bool CheckSignerAccess(const Person& signer) const override {
    // Проверка: является ли подписант Деканом
    return dynamic_cast<const Dean*>(&signer) != nullptr;
  }

 private:
  std::weak_ptr<Student> student_;  ///< Ссылка на студента
  std::string purpose_;             ///< Место требования
};

#endif  // CERTIFICATE_H
