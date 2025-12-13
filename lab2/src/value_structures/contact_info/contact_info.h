/**
 * @file contact_info.h
 * @brief Контактная информация с валидацией и нормализацией
 * @author Dmitry Burbas
 * @date 11/11/2025
 */
#ifndef CONTACT_INFO_H
#define CONTACT_INFO_H

#include <optional>
#include <string>

#include "../../utility_functions/utility_functions.h"
#include "../address/address.h"

/**
 * @class ContactInfo
 * @brief Хранит и валидирует базовую контактную информацию
 * @details Содержит нормализованный номер телефона, опциональные адрес
 * электронной почты и экземпляр адреса (Address). Все телефоны и email-адреса
 * проходят валидацию и нормализацию при создании и изменении.
 */
class ContactInfo {
 public:
  /**
   * @brief Конструктор ContactInfo с телефоном, email и опциональным
   * адресом
   * @param phone_number Номер телефона для нормализации и валидации
   * (белорусский формат +375*********)
   * @param email Адрес электронной почты для нормализации и валидации
   * (опциональный, по умолчанию: пустая строка)
   * @param address Опциональный объект Address (по умолчанию: std::nullopt)
   * @throws ContactInfoException, если формат телефона или email некорректен
   * @details Нормализует телефон, удаляя пробелы, дефисы, скобки, и преобразует
   * префикс "80" в "+375". У email удаляются пробелы в начале и конце строки.
   */
  explicit ContactInfo(const std::string& phone_number,
                       const std::string& email = "",
                       std::optional<Address> address = std::nullopt);
  /**
   * @brief Конструктор ContactInfo с телефоном, email и адресом в виде
   * строки
   * @param phone_number Номер телефона для нормализации и валидации
   * @param email Адрес электронной почты для нормализации и
   * валидации(опциональный, по умолчанию пустая строка)
   * @param address_str Адрес в виде строки (по умолчанию: пустая строка)
   * @throws ContactInfoException, если формат телефона или email некорректен
   * @details Делегирует создание основному конструктору. Если address_str пуст
   * или состоит только из пробелов, адрес устанавливается в std::nullopt.
   */
  explicit ContactInfo(const std::string& phone_number,
                       const std::string& email = "",
                       const std::string& address_str = "")
      : ContactInfo(phone_number, email,
                    Utility::Trim(address_str).empty()
                        ? std::nullopt
                        : std::optional<Address>(address_str)) {}

  /**
   * @brief Деструктор по умолчанию
   */
  ~ContactInfo() = default;

  /**
   * @brief Установка нового email с валидацией и нормализацией
   * @param email Новый адрес электронной почты
   * @throws ContactInfoException, если формат email некорректен
   * @details Удаляет пробелы по краям и проверяет соответствие регулярному
   * выражению.
   */
  void SetEmail(const std::string& email) {
    const std::string normalized = NormalizeEmail(email);
    ValidateEmail(normalized);
    email_ = normalized;
  }

  /**
   * @brief Устанавливает новый номер телефона с валидацией и нормализацией
   * @param phone_number Новый номер телефона
   * @throws ContactInfoException, если формат телефона некорректен или пуст.
   * @details Удаляет символы форматирования и приводит к формату +375*********
   */
  void SetPhoneNumber(const std::string& phone_number) {
    const std::string normalized = NormalizePhone(phone_number);
    ValidatePhone(normalized);
    phone_number_ = normalized;
  }

  /**
   * @brief Устанавливает новый адрес из строки
   * @param address Строка с адресом для создания объекта Address
   * @details Создает новый объект Address из переданной строки
   */
  void SetAddress(const std::string& address) { address_ = Address(address); }

  /**
   * @brief Устанавливает новый адрес из объекта Address
   * @param address Объект Address для установки
   * @details Копирует переданный объект адреса в текущую контактную информацию
   */
  void SetAddress(const Address& address) { address_ = address; }

  /**
   * @brief Возвращает текущий email
   * @return Адрес электронной почты в виде строки
   */
  [[nodiscard]] std::string GetEmail() const { return email_; }

  /**
   * @brief Возвращает текущий номер телефона
   * @return Номер телефона в виде строки в нормализованном формате
   * (+375*********)
   */
  [[nodiscard]] std::string GetPhoneNumber() const { return phone_number_; }

  /**
   * @brief Возвращает адрес в виде отформатированной строки
   * @return Строковое представление адреса
   * @throws ContactInfoException, если адрес не установлен (std::nullopt)
   * @details Вызывает метод ToString() у объекта Address.
   */
  [[nodiscard]] std::string GetAddressString() const;

  /**
   * @brief Возвращает объект Address
   * @return Объект Address
   * @throws ContactInfoException, если адрес не установлен (std::nullopt)
   */
  [[nodiscard]] Address GetAddress() const;

 private:
  std::string email_;         ///< Нормализованный адрес электронной почты
  std::string phone_number_;  ///< Нормализованный номер телефона в формате
                              ///< +375*********
  std::optional<Address> address_;  ///< Опциональный почтовый адрес

  /**
   * @brief Валидирует формат email с помощью регулярного выражения
   * @param email Строка email для проверки
   * @throws ContactInfoException, если email не соответствует паттерну
   * @details Использует regex-паттерн: (\w+)(\.|-|_)?(\w*)@(\w+)(\.\w+)+
   */
  static void ValidateEmail(const std::string& email);

  /**
   * @brief Нормализует email, удаляя пробельные символы
   * @param email Строка email для нормализации
   * @return Email без пробелов по краям
   */
  static std::string NormalizeEmail(std::string email);

  /**
   * @brief Валидирует формат телефона с помощью регулярного выражения
   * @param phone Строка телефона для проверки
   * @throws ContactInfoException, если телефон пуст или не соответствует
   * формату +375*********.
   * @details Проверяет по regex-паттерну: ^\+375\d{9}$ (валидирует только
   * белорусские номера, так как проект регионально ориентирован).
   */
  static void ValidatePhone(const std::string& phone);

  /**
   * @brief Нормализует телефон, удаляя форматирование и преобразуя префикс.
   * @param phone Строка телефона для нормализации.
   * @return Нормализованный телефон в формате +375*********.
   * @details Удаляет пробелы, тире и скобки. Преобразует префикс "80" в "+375".
   */
  static std::string NormalizePhone(std::string phone);
};

#endif  // CONTACT_INFO_H
