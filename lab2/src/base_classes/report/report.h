//
// Created by Dmitry Burbas on 13/12/2025.
//

#ifndef REPORT_H
#define REPORT_H
#include "../document/document.h"

// TODO: документация

class Report : public Document {
 public:
  Report(std::string name, const Date& issue_date, const Date& period_from,
         const Date& period_to)
      : Document(std::move(name), issue_date),
        period_from_(period_from),
        period_to_(period_to) {}

  [[nodiscard]] const Date& GetDateFrom() const { return period_from_; }
  [[nodiscard]] const Date& GetDateTo() const { return period_to_; }

 protected:
  [[nodiscard]] bool CheckSignerAccess(const Person& signer) const override = 0;

 private:
  Date period_from_;
  Date period_to_;
};

#endif  // REPORT_H
