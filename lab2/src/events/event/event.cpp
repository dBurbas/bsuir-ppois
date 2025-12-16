//
// Created by Dmitry Burbas on 16/11/2025.
//

#include "event.h"
void Event::CleanupExpired() {
  participants_.erase(std::remove_if(participants_.begin(), participants_.end(),
                                     [](const std::weak_ptr<Person>& wp) {
                                       return wp.expired();
                                     }),
                      participants_.end());
}

void Event::AddParticipant(const std::shared_ptr<Person>& p) {
  if (!p) throw EventException("Null participant");
  CleanupExpired();
  for (const auto& wp : participants_) {
    if (!wp.owner_before(p) && !p.owner_before(wp)) {
      throw EventException("Already existed participant");
    }
  }
  participants_.push_back(p);
}