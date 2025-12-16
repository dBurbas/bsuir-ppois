//
// Created by Dmitry Burbas on 06/12/2025.
//

#ifndef LAB2_SECRETARY_H
#define LAB2_SECRETARY_H
#include "../../dean_office/dean_office.h"
#include "../office_worker/office_worker.h"

class Secretary final : public OfficeWorker {
 public:
  Secretary(const PersonalInfo& personal_info, const ContactInfo& contact_info,
            const double salary_base, const double salary_rate,
            const Date& hire_date)
      : Employee(personal_info, contact_info, salary_base, salary_rate,
                 hire_date),
        OfficeWorker(personal_info, contact_info, salary_base, salary_rate,
                     hire_date) {}
  void Work() override {}
  void ProcessDocument(Document& doc) override {}

 private:
  std::weak_ptr<DeanOffice> dean_office_;
};

#endif  // LAB2_SECRETARY_H
