/**
 * @file event.h
 * @brief Базовый класс для любых событий (учебных и не только)
 * @author Dmitry Burbas
 * @date 16/11/2025
 */

#ifndef EVENT_H
#define EVENT_H

#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../exceptions/dean_office_exceptions.h"
#include "../../people/person/person.h"

/**
 * @class Event
 * @brief Абстрактное событие с датой, местом и списком участников
 * @details Служит базой для уроков (Lesson) и других мероприятий.
 * Управляет списком участников через слабые ссылки (weak_ptr),
 * чтобы не удерживать их в памяти, если они уже удалены из системы.
 */
class Event {
 public:
  /**
   * @brief Конструктор события
   * @param title Название события
   * @param date Дата проведения
   * @param address Место проведения
   * @param participants Начальный список участников (по умолчанию пуст)
   * @throws EventException, если название события пустое
   */
  Event(std::string title, const Date& date, Address address,
        const std::vector<std::weak_ptr<Person>>& participants =
            std::vector<std::weak_ptr<Person>>())
      : participants_(participants),
        title_(std::move(title)),
        event_date_(date),
        address_(std::move(address)) {
    if (title_.empty()) throw EventException("Event title is empty");
  }

  /**
   * @brief Виртуальный деструктор
   */
  virtual ~Event() = default;

  /**
   * @brief Чисто виртуальный метод проведения события
   * @details Должен быть реализован в конкретных классах (Lesson, Meeting и
   * т.д.)
   */
  virtual void Hold() = 0;

  /**
   * @brief Добавляет участника к событию
   * @param p Умный указатель на человека (Person)
   * @throws EventException, если указатель null или участник уже добавлен
   * @details Перед добавлением автоматически очищает список от "мертвых"
   * ссылок.
   */
  void AddParticipant(const std::shared_ptr<Person>& p);

  /**
   * @brief Удаляет из списка участников тех, кто был удален из памяти
   */
  void CleanupExpired();

  /**
   * @brief Очищает список всех участников
   */
  void RemoveAllParticipants() { participants_.clear(); }

  /**
   * @brief Получение названия события
   */
  [[nodiscard]] const std::string& GetTitle() const { return title_; }

  /**
   * @brief Получение даты проведения
   */
  [[nodiscard]] const Date& GetEventDate() const { return event_date_; }

  /**
   * @brief Получение адреса проведения
   */
  [[nodiscard]] const Address& GetAddress() const { return address_; }

  /**
   * @brief Проверяет, завершилось ли событие относительно текущей даты
   * @param cur_date Текущая дата
   * @return true, если событие уже прошло
   */
  [[nodiscard]] bool IsFinished(const Date& cur_date) const {
    return cur_date > event_date_;
  }

 protected:
  std::vector<std::weak_ptr<Person>>
      participants_;   ///< Список участников (без владения)
  std::string title_;  ///< Название
  Date event_date_;    ///< Дата
  Address address_;    ///< Адрес
};

#endif  // EVENT_H
