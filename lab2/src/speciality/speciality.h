/**
 * @file speciality.h
 * @brief Класс специальности
 * @author Dmitry Burbas
 * @date 14/12/2025
 */

#ifndef SPECIALITY_H
#define SPECIALITY_H

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "../exceptions/dean_office_exceptions.h"
#include "../group/group.h"

/**
 * @class Speciality
 * @brief Представляет специальность (направление подготовки)
 * @details Содержит информацию о коде и названии специальности, а также
 * агрегирует студенческие группы, относящиеся к ней.
 */
class Speciality {
 public:
  /**
   * @brief Конструктор специальности
   * @param code Шифр специальности (например, "09.03.04")
   * @param name Название специальности
   * @throws SpecialityException, если код или название пусты
   */
  Speciality(std::string code, std::string name)
      : code_(std::move(code)), name_(std::move(name)) {
    if (code_.empty()) throw SpecialityException("Speciality code empty");
    if (name_.empty()) throw SpecialityException("Speciality name empty");
  }

  /**
   * @brief Добавляет группу к специальности
   * @param group Умный указатель на добавляемую группу
   * @throws SpecialityException, если передан нулевой указатель
   * @details Просто добавляет группу в конец списка.
   * @warning В отличие от класса Department, здесь ОТСУТСТВУЕТ проверка на
   * дубликаты. Вы можете добавить одну и ту же группу дважды.
   */
  void AddGroup(std::shared_ptr<Group> group) {
    if (!group) throw SpecialityException("Cannot add null group");

    groups_.push_back(std::move(group));
  }

  /**
   * @brief Ищет группу по её строковому идентификатору
   * @param group_id Идентификатор группы для поиска
   * @return Умный указатель на найденную группу или nullptr, если группа не
   * найдена
   * @details Выполняет линейный поиск по списку групп.
   */
  [[nodiscard]] std::shared_ptr<Group> FindGroup(
      const std::string& group_id) const {
    auto it = std::find_if(groups_.begin(), groups_.end(),
                           [&](const std::shared_ptr<Group>& g) {
                             return g->GetId() == group_id;
                           });
    return (it != groups_.end()) ? *it : nullptr;
  }

  /**
   * @brief Получение шифра специальности
   * @return Константная ссылка на строку с кодом
   */
  [[nodiscard]] const std::string& GetCode() const { return code_; }

  /**
   * @brief Получение названия специальности
   * @return Константная ссылка на строку с названием
   */
  [[nodiscard]] const std::string& GetName() const { return name_; }

  /**
   * @brief Получение списка всех групп на специальности
   * @return Константная ссылка на вектор групп
   */
  [[nodiscard]] const std::vector<std::shared_ptr<Group>>& GetGroups() const {
    return groups_;
  }

  /**
   * @brief Формирует полное название специальности
   * @return Строка формата "Код - Название"
   */
  [[nodiscard]] std::string GetFullName() const {
    return code_ + " - " + name_;
  }

 private:
  std::string code_;                            ///< Шифр специальности
  std::string name_;                            ///< Название
  std::vector<std::shared_ptr<Group>> groups_;  ///< Список групп
};

#endif  // SPECIALITY_H
