/**
 * @file report.h
 * @brief Базовый класс для отчетов
 * @author Dmitry Burbas
 * @date 13/12/2025
 */
#ifndef REPORT_H
#define REPORT_H
#include "../../exceptions/dean_office_exceptions.h"
#include "../document/document.h"
/*! @class Report
 *  @brief Абстрактный базовый класс для всех отчетов.
 *  @details Описывает общую реализацию для отчетов. Наследуется от
 * документа(получает всю его реализацию) и реализует начало и конец периода
 * отчета.
 */
class Report : public Document {
 public:
  /*!
   *  @brief Конструктор отчета
   *  @param name Уникальное имя отчета
   *  @param issue_date Дата выдачи(создания) приказа
   *  @param period_from Начало периода отчета
   *  @param period_to Конец периода отчета
   *  @throw ReportPeriodException, если конец периода раньше начала
   */
  Report(std::string name, const Date& issue_date, const Date& period_from,
         const Date& period_to)
      : Document(std::move(name), issue_date),
        period_from_(period_from),
        period_to_(period_to) {
    if (period_to_ < period_from_)
      throw ReportPeriodException(
          "Report period end cannot be earlier than start");
  }
  /*!
   *  @brief Возвращает дату начала периода ведения отчета
   *  @return Объект даты начала периода
   */
  [[nodiscard]] const Date& GetPeriodFrom() const { return period_from_; }

  /*!
   *  @brief Возвращает дату конца периода ведения отчета
   *  @return Объект даты конца периода
   */
  [[nodiscard]] const Date& GetPeriodTo() const { return period_to_; }

 protected:
  /*!
   *  @brief Проверка доступа к подписанию человека
   *  @details Чисто виртуальный метод который нужно реализовать всем
   * наследникам
   *  @param signer Ссылка на объект Person, выступающего в роли подписанта
   *  @return True, если человек имеет нужные права доступа, в ином случае false
   */
  [[nodiscard]] bool CheckSignerAccess(const Person& signer) const override = 0;

 private:
  Date period_from_;  ///< Дата начала периода отчета
  Date period_to_;    ///< Дата конца периода отчета
};

#endif  // REPORT_H
