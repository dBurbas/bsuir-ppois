/**
 * @file dean_deputy.h
 * @brief Класс Заместителя Декана
 * @author Dmitry Burbas
 * @date 06/12/2025
 */

#ifndef DEAN_DEPUTY_H
#define DEAN_DEPUTY_H

#include <memory>
#include <vector>

#include "../dean/dean.h"
#include "../employee/employee.h"
#include "../office_worker/office_worker.h"
#include "../teacher/teacher.h"

/**
 * @class DeanDeputy
 * @brief Класс, представляющий заместителя декана
 * @details Объединяет в себе функционал офисного сотрудника (OfficeWorker)
 * и преподавателя (Teacher). Использует множественное наследование для
 * реализации гибридной роли. Отвечает за подписание документов и выполнение
 * учебной нагрузки.
 */
class DeanDeputy : public OfficeWorker, public Teacher {
 public:
  /**
   * @brief Конструктор заместителя декана
   * @param pi Персональные данные
   * @param ci Контактная информация
   * @param salary_base Базовая ставка зарплаты
   * @param salary_rate Коэффициент ставки
   * @param hire_date Дата найма
   * @details Инициализирует базовые классы Employee, OfficeWorker и Teacher.
   */
  DeanDeputy(const PersonalInfo& pi, const ContactInfo& ci, double salary_base,
             double salary_rate, const Date& hire_date)
      : Employee(pi, ci, salary_base, salary_rate, hire_date),
        OfficeWorker(pi, ci, salary_base, salary_rate, hire_date),
        Teacher(pi, ci, salary_base, salary_rate, hire_date) {}

  /**
   * @brief Выполнение служебных обязанностей
   * @details Последовательно выполняет обязанности преподавателя
   * (Teacher::Work) и офисного сотрудника (OfficeWorker::Work).
   */
  void Work() override {
    Teacher::Work();
    OfficeWorker::Work();
  }

  /**
   * @brief Массовое подписание документов
   * @param documents Вектор документов для подписания
   * @return Список документов, которые не удалось подписать
   * @details Пытается подписать каждый документ из переданного списка.
   * Если у заместителя нет прав на подпись конкретного документа (выбрасывается
   * DeanOfficeException), документ добавляется в возвращаемый список для
   * дальнейшей передачи Декану.
   */
  std::vector<std::shared_ptr<Document>> SignDocuments(
      const std::vector<std::shared_ptr<Document>>& documents) const {
    std::vector<std::shared_ptr<Document>> unsigned_documents_to_dean;
    for (auto doc : documents) {
      try {
        doc->Sign(*this);
      } catch (const DeanOfficeException& e) {
        unsigned_documents_to_dean.push_back(doc);
      }
    }
    return unsigned_documents_to_dean;
  }

  /**
   * @brief Обработка одного документа
   * @param doc Ссылка на документ
   * @warning Метод в данный момент не реализован (заглушка).
   */
  void ProcessDocument(Document& doc) override {}
};

#endif  // DEAN_DEPUTY_H
