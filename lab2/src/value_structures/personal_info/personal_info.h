/**
 * @file personal_info.h
 * @brief Класс, описывающий персональные данные человека (ФИО и дата рождения).
 * @author Dmitry Burbas
 * @date 11/11/2025.
 */
#ifndef PERSONAL_INFO_H
#define PERSONAL_INFO_H

#include <string>

#include "../../exceptions/components_exceptions.h"
#include "../../utility_functions/utility_functions.h"
#include "../date/date.h"

/**
 * @class PersonalInfo
 * @brief Хранит и проверяет персональные данные: фамилию, имя, отчество и дату
 * рождения
 *
 * @details
 * Класс предназначен для хранения ФИО(отчество опционально) человека и
 * (опционально) даты рождения. Значения ФИО нормализуются (например, через
 * Utility::Trim) и проверяются внутренними методами
 * ValidateFirstName/ValidateLastName
 * Дата рождения хранится как std::optional<Date>. Если дата отсутствует, вызов
 * GetBirthDate() приводит к исключению
 */
class PersonalInfo {
 public:
  /**
   * @brief Конструктор персональных данных
   * @param first_name Имя
   * @param last_name Фамилия
   * @param middle_name Отчество (по умолчанию пустая строка)
   * @param birth_date Дата рождения (по умолчанию не задана)
   * @throw PersonalInfoException Если имя/фамилия не проходят валидацию
   * (в зависимости от логики ValidateFirstName/ValidateLastName и методов
   * Update*)
   */
  PersonalInfo(const std::string& first_name, const std::string& last_name,
               const std::string& middle_name = "",
               std::optional<Date> birth_date = std::nullopt);

  /// @brief Конструктор копирования по умолчанию
  PersonalInfo(const PersonalInfo& other) = default;
  /// @brief Конструктор перемещения по умолчанию
  PersonalInfo(PersonalInfo&& other) = default;

  /// @brief Оператор копирующего присваивания по умолчанию
  PersonalInfo& operator=(const PersonalInfo& other) = default;

  /// @brief Оператор перемещающего присваивания по умолчанию
  PersonalInfo& operator=(PersonalInfo&& other) = default;

  /**
   * @brief Проверяет равенство персональных данных
   * @param other Объект для сравнения
   * @return true, если все поля (ФИО и дата рождения) эквивалентны, иначе false
   */
  bool operator==(const PersonalInfo& other) const;

  /**
   * @brief Проверяет неравенство персональных данных
   * @param other Объект для сравнения
   * @return true, если объекты отличаются, иначе false
   */
  bool operator!=(const PersonalInfo& other) const;

  /// @brief Деструктор по умолчанию.
  ~PersonalInfo() = default;

  /**
   * @brief Устанавливает ФИО целиком
   * @param first_name Имя
   * @param last_name Фамилия
   * @param middle_name Отчество (по умолчанию пустая строка)
   * @details
   * Имя и фамилия проверяются и обновляются через внутренние методы Update*,
   * отчество нормализуется (Utility::Trim)
   * @throw PersonalInfoException Если имя/фамилия не проходят валидацию
   */
  void SetFullName(const std::string& first_name, const std::string& last_name,
                   const std::string& middle_name = "") {
    UpdateFirstAndLastName(first_name, last_name);
    middle_name_ = Utility::Trim(middle_name);
  }

  /**
   * @brief Устанавливает дату рождения
   * @param birth_date Дата рождения в строковом формате, который ожидает
   * парсер
   * @details
   * Преобразует входную строку в Date и сохраняет её во внутреннее поле.
   * @throw PersonalInfoException Если строка не соответствует ожидаемому
   * формату или дата некорректна (в зависимости от реализации)
   */
  void SetBirthDate(const std::string& birth_date);

  /**
   * @brief Устанавливает имя
   * @param first_name Новое имя
   * @throw PersonalInfoException Если имя не проходит валидацию
   */
  void SetFirstName(const std::string& first_name) {
    UpdateFirstName(first_name);
  }

  /**
   * @brief Устанавливает фамилию
   * @param last_name Новая фамилия
   * @throw PersonalInfoException Если фамилия не проходит валидацию
   */
  void SetLastName(const std::string& last_name) { UpdateLastName(last_name); }

  /**
   * @brief Устанавливает отчество
   * @param middle_name Новое отчество
   * @details
   * Отчество нормализуется (Utility::Trim). Валидация отчества в данной
   * реализации не задана.
   */
  void SetMiddleName(const std::string& middle_name) {
    middle_name_ = Utility::Trim(middle_name);
  }

  /**
   * @brief Возвращает ФИО в виде одной строки
   * @return Строка, содержащая фамилию, имя и отчество в согласованном формате
   */
  [[nodiscard]] std::string GetFullName() const;

  /// @brief Возвращает фамилию
  /// @return Фамилия
  [[nodiscard]] std::string GetLastName() const { return last_name_; }

  /// @brief Возвращает имя
  /// @return Имя
  [[nodiscard]] std::string GetFirstName() const { return first_name_; }

  /// @brief Возвращает отчество
  /// @return Отчество
  [[nodiscard]] std::string GetMiddleName() const { return middle_name_; }

  /**
   * @brief Возвращает дату рождения
   * @return Ссылка на объект Date
   * @throw PersonalInfoException Если дата рождения не задана
   */
  [[nodiscard]] const Date& GetBirthDate() const {
    if (birth_date_ == std::nullopt)
      throw PersonalInfoException("No date in this personal info");
    return *birth_date_;
  }

 private:
  std::string first_name_;          ///< Имя
  std::string last_name_;           ///< Фамилия
  std::string middle_name_;         ///< Отчество (может быть пустым)
  std::optional<Date> birth_date_;  ///< Дата рождения (может отсутствовать)

  /**
   * @brief Обновляет имя с валидацией и нормализацией
   * @param first_name Новое имя
   * @throw PersonalInfoException Если имя не проходит ValidateFirstName
   */
  void UpdateFirstName(const std::string& first_name);

  /**
   * @brief Обновляет фамилию с валидацией и нормализацией
   * @param last_name Новая фамилия
   * @throw PersonalInfoException Если фамилия не проходит ValidateLastName
   */
  void UpdateLastName(const std::string& last_name);

  /**
   * @brief Обновляет имя и фамилию единым действием
   * @param first_name Новое имя
   * @param last_name Новая фамилия
   * @throw PersonalInfoException Если имя или фамилия не проходят валидацию
   */
  void UpdateFirstAndLastName(const std::string& first_name,
                              const std::string& last_name);

  /**
   * @brief Проверяет корректность имени
   * @param first_name Проверяемое имя
   * @throw PersonalInfoException Если имя некорректно
   */
  static void ValidateFirstName(const std::string& first_name);

  /**
   * @brief Проверяет корректность фамилии
   * @param last_name Проверяемая фамилия
   * @throw PersonalInfoException Если фамилия некорректна
   */
  static void ValidateLastName(const std::string& last_name);
};

#endif  // PERSONAL_INFO_H
