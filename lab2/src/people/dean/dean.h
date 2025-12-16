/**
 * @file dean.h
 * @brief Класс Декана факультета
 * @author Dmitry Burbas
 * @date 16/11/2025
 */

#ifndef DEAN_H
#define DEAN_H

#include <memory>
#include <vector>

#include "../docent/docent.h"
#include "../office_worker/office_worker.h"

/**
 * @class Dean
 * @brief Главный руководитель факультета (Декан)
 * @details Класс объединяет роли Доцента (Docent) и Офисного работника
 * (OfficeWorker), используя множественное наследование. Декан обладает
 * исключительными правами подписи большинства документов и управления
 * персоналом.
 */
class Dean : public Docent, public OfficeWorker {
 public:
  /**
   * @brief Конструктор Декана
   * @param personal_info Персональные данные
   * @param contact_info Контактная информация
   * @param salary_base Базовая ставка зарплаты
   * @param salary_rate Коэффициент ставки
   * @param hire_date Дата вступления в должность
   * @details Инициализирует базовые классы Employee (виртуально), Docent и
   * OfficeWorker.
   */
  Dean(const PersonalInfo& personal_info, const ContactInfo& contact_info,
       const double salary_base, const double salary_rate,
       const Date& hire_date)
      : Employee(personal_info, contact_info, salary_base, salary_rate,
                 hire_date),
        Docent(personal_info, contact_info, salary_base, salary_rate,
               hire_date),
        OfficeWorker(personal_info, contact_info, salary_base, salary_rate,
                     hire_date) {}

  /**
   * @brief Выполнение обязанностей Декана
   * @details Совмещает преподавательскую деятельность (Docent::Work)
   * и административную работу (OfficeWorker::Work).
   */
  void Work() override {
    Docent::Work();
    OfficeWorker::Work();
  }

  /**
   * @brief Подписание пачки документов
   * @param documents Вектор документов для подписи
   * @return Вектор неподписанных документов (при возникновении ошибок)
   * @details Проходит по списку документов и ставит подпись Декана.
   * Если документ не может быть подписан (например, уже подписан или неверный
   * тип), он возвращается в списке необработанных.
   */
  std::vector<std::shared_ptr<Document>> SignDocuments(
      const std::vector<std::shared_ptr<Document>>& documents) {
    std::vector<std::shared_ptr<Document>> unsigned_documents;
    for (auto doc : documents) {
      try {
        doc->Sign(*this);
      } catch (const DeanOfficeException& e) {
        unsigned_documents.push_back(doc);
      }
    }
    return unsigned_documents;
  }

  /**
   * @brief Реализация обработки документа (из OfficeWorker)
   * @warning Если этот метод не реализован здесь,
   * класс Dean будет абстрактным и непригодным к созданию.
   */
  void ProcessDocument(Document& doc) override {
    // TODO: Реализовать логику обработки
    // Пока заглушка для компиляции
  }
};

#endif  // DEAN_H
