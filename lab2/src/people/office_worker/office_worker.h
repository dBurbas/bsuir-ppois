/**
 * @file office_worker.h
 * @brief Абстрактный базовый класс для административно-управленческого
 * персонала
 * @author Dmitry Burbas
 * @date 16/11/2025
 */

#ifndef OFFICE_WORKER_H
#define OFFICE_WORKER_H

#include "../employee/employee.h"

class Document;

/**
 * @class OfficeWorker
 * @brief Интерфейс для сотрудников, занимающихся бумажной работой
 * @details Является абстрактным классом. Наследуется от Employee (виртуально),
 * предполагая возможность множественного наследования для декана.
 * Определяет контракт для обработки документов.
 */
class OfficeWorker : virtual public Employee {
 public:
  /**
   * @brief Конструктор офисного работника
   * @param pi Персональные данные
   * @param ci Контактная информация
   * @param salary_base Базовая ставка
   * @param salary_rate Коэффициент ставки
   * @param hire_date Дата приема на работу
   * @details Просто пробрасывает параметры в конструктор базового класса
   * Employee.
   */
  OfficeWorker(const PersonalInfo& pi, const ContactInfo& ci,
               double salary_base, double salary_rate, const Date& hire_date)
      : Employee(pi, ci, salary_base, salary_rate, hire_date) {}

  /**
   * @brief Виртуальный деструктор по умолчанию
   */
  ~OfficeWorker() override = default;

  /**
   * @brief Чисто виртуальный метод обработки документа
   * @param doc Ссылка на обрабатываемый документ
   * @details Конкретные классы (секретарь, бухгалтер) должны реализовать
   * свою логику работы с документами (подпись, архивация, отклонение).
   */
  virtual void ProcessDocument(Document& doc) = 0;

  /**
   * @brief Чисто виртуальный метод выполнения общих обязанностей
   * @details Наследуется от Employee. Требует реализации в конкретных классах.
   */
  void Work() override = 0;
};

#endif  // OFFICE_WORKER_H
