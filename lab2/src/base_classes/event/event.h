//
// Created by Dmitry Burbas on 16/11/2025.
//

#ifndef EVENT_H
#define EVENT_H
#include <vector>

#include "../person/person.h"
// TODO:написать логику методов
class Event {
 public:
 protected:
  std::vector<Person*> participants_;
  std::string title_;
  Date start_date_;
  Date end_date_;
  int hour_duration;
  Address address_;
};

#endif  // EVENT_H
