/**
 * @file employee.h
 * @brief Базовый класс для всех сотрудников организации
 * @author Dmitry Burbas
 * @date 06/12/2025
 */

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "../../documents/orders/dismissal_order/dismissal_order.h"
#include "../../documents/orders/employee_on_leave_order/employee_on_leave_order.h"
#include "../../enum_classes/employee_status.h"
#include "../../salary/salary.h"
#include "../person/person.h"

/**
 * @class Employee
 * @brief Абстрактный класс сотрудника
 * @details Объединяет общие атрибуты всех работников: зарплату, дату найма,
 * текущий статус (работает/в отпуске/уволен) и методы управления ими.
 * Наследуется от Person.
 */
class Employee : public Person {
 public:
  /**
   * @brief Конструктор сотрудника
   * @param personal_info Персональные данные
   * @param contact_info Контактная информация
   * @param salary_base Базовая ставка зарплаты
   * @param salary_rate Ставка (0.5, 1.0 и т.д.)
   * @param hire_date Дата приема на работу
   * @details Статус по умолчанию устанавливается в Active.
   */
  Employee(const PersonalInfo& personal_info, const ContactInfo& contact_info,
           const double salary_base, const double salary_rate,
           const Date& hire_date)
      : Person(personal_info, contact_info),
        salary_(salary_base, salary_rate),
        hire_date_(hire_date) {}

  /**
   * @brief Виртуальный деструктор
   */
  ~Employee() override = default;

  /**
   * @brief Чисто виртуальный метод выполнения работы
   * @details Должен быть реализован в конкретных классах (Teacher,
   * OfficeWorker).
   */
  virtual void Work() = 0;

  /**
   * @brief Возвращает сотрудника в активное состояние (например, из отпуска)
   * @throws EmployeeException, если сотрудник уволен или не находится в отпуске
   */
  void BecomeActive();

  /**
   * @brief Отправляет сотрудника в отпуск или командировку
   * @param order Приказ об отпуске
   * @param cur_date Текущая дата
   * @throws EmployeeException, если приказ не валиден или сотрудник уже в
   * отпуске/уволен
   */
  void SendOnLeave(const EmployeeOnLeaveOrder& order, const Date& cur_date);

  /**
   * @brief Увольняет сотрудника
   * @param order Приказ об увольнении
   * @param cur_date Текущая дата
   * @throws EmployeeException, если приказ не валиден или сотрудник уже уволен
   */
  void Fire(const DismissalOrder& order, const Date& cur_date);

  /**
   * @brief Изменяет базовую ставку зарплаты
   */
  void SetSalaryBase(const double new_salary_base) {
    salary_.SetBase(new_salary_base);
  }

  /**
   * @brief Изменяет коэффициент ставки
   */
  void SetSalaryRate(const double new_salary_rate) {
    salary_.SetRate(new_salary_rate);
  }

  /**
   * @brief Получение текущего статуса сотрудника
   */
  [[nodiscard]] EmployeeStatus GetEmployeeStatus() const {
    return employee_status_;
  }

  /**
   * @brief Расчет стажа работы в полных годах
   * @param cur_date Текущая дата для расчета
   * @return Количество полных лет стажа
   */
  [[nodiscard]] int GetExperienceYears(const Date& cur_date) const {
    return FullYearsBetween(hire_date_, cur_date);
  }

  /**
   * @brief Получение полной зарплаты (база * ставка)
   */
  [[nodiscard]] double GetSalary() const { return salary_.GetSalary(); }

  /**
   * @brief Получение базовой части зарплаты
   */
  [[nodiscard]] double GetSalaryBase() const { return salary_.GetBase(); }

  /**
   * @brief Получение коэффициента ставки
   */
  [[nodiscard]] double GetSalaryRate() const { return salary_.GetRate(); }

 private:
  /**
   * @brief Вспомогательный метод расчета разницы лет между датами
   * @param from Дата начала
   * @param to Дата окончания
   * @return Разница в годах
   * @throws EmployeeException, если дата окончания раньше даты начала
   */
  static int FullYearsBetween(const Date& from, const Date& to);

  Salary salary_;   ///< Объект зарплаты
  Date hire_date_;  ///< Дата найма
  EmployeeStatus employee_status_ = EmployeeStatus::Active;  ///< Текущий статус
};

#endif  // EMPLOYEE_H
