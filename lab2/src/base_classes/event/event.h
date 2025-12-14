/**
 * @file event.h
 * @brief Базовый класс для событий
 * @author Dmitry Burbas
 * @date 16/11/2025
 */
#ifndef EVENT_H
#define EVENT_H
#include <algorithm>
#include <memory>
#include <vector>

#include "../../exceptions/dean_office_exceptions.h"
#include "../person/person.h"
// TODO: документация
class Event {
 public:
  Event(std::string title, const Date& date, const Date& end,
        const int hour_duration, Address address)
      : title_(std::move(title)),
        event_date_(date),
        hour_duration_(hour_duration),
        address_(std::move(address)) {
    if (title_.empty()) throw EventException("Event title is empty");
    if (hour_duration_ <= 0) throw EventException("Event duration must be > 0");
  }

  virtual ~Event() = default;

  void AddParticipant(const std::shared_ptr<Person>& p);
  void CleanupExpired();

  void RemoveAllParticipants() { participants_.clear(); }

  [[nodiscard]] const std::string& GetTitle() const { return title_; }
  [[nodiscard]] const Date& GetEventDate() const { return event_date_; }
  [[nodiscard]] int GetHourDuration() const { return hour_duration_; }
  [[nodiscard]] const Address& GetAddress() const { return address_; }

 protected:
  std::vector<std::weak_ptr<Person>> participants_;
  std::string title_;
  Date event_date_;
  int hour_duration_;
  Address address_;
};

#endif  // EVENT_H
