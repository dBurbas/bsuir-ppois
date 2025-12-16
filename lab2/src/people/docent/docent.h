/**
 * @file docent.h
 * @brief Класс доцента кафедры
 * @author Dmitry Burbas
 * @date 06/12/2025
 */

#ifndef DOCENT_H
#define DOCENT_H

#include <vector>

#include "../../exceptions/dean_office_exceptions.h"
#include "../../publication/publication.h"
#include "../teacher/teacher.h"

/**
 * @class Docent
 * @brief Представляет доцента — преподавателя, занимающегося научной работой.
 * @details Расширяет функционал преподавателя возможностью учета публикаций.
 * Является конкретным классом (concrete class), реализующим метод Work.
 */
class Docent : public Teacher {
 public:
  /**
   * @brief Конструктор доцента
   * @param personal_info Персональные данные
   * @param contact_info Контактная информация
   * @param salary_base Базовая ставка
   * @param salary_rate Коэффициент ставки
   * @param hire_date Дата найма
   * @details Из-за виртуального наследования Teacher от Employee, класс Docent
   * обязан явно инициализировать конструктор Employee, несмотря на то, что
   * он вызывается и в Teacher.
   */
  Docent(const PersonalInfo& personal_info, const ContactInfo& contact_info,
         const double salary_base, const double salary_rate,
         const Date& hire_date)
      : Employee(personal_info, contact_info, salary_base, salary_rate,
                 hire_date),
        Teacher(personal_info, contact_info, salary_base, salary_rate,
                hire_date) {}

  /**
   * @brief Выполнение обязанностей доцента
   * @details Реализация чисто виртуального метода. В данной версии метод пуст.
   * @warning Заглушка. Доцент ничего не делает при вызове Work().
   */
  void Work() override {}

  /**
   * @brief Добавляет публикацию в список трудов доцента
   * @param pub Объект публикации (передается по значению и перемещается)
   * @throws DocentException, если название публикации пустое или год
   * некорректен
   * @details Метод берет на себя ответственность за валидацию данных
   * публикации, что является нарушением инкапсуляции (валидация должна быть
   * внутри Publication).
   */
  void AddPublication(Publication pub) {
    if (pub.title.empty()) throw DocentException("Publication title is empty");
    if (pub.year <= 0) throw DocentException("Invalid publication year");
    publications_.push_back(std::move(pub));
  }

  /**
   * @brief Получение общего количества публикаций
   * @return Количество публикаций
   */
  [[nodiscard]] int GetPublicationsCount() const {
    return static_cast<int>(publications_.size());
  }

  /**
   * @brief Подсчет публикаций, выпущенных начиная с указанного года
   * @param year Год начала отсчета (включительно)
   * @return Количество свежих публикаций
   */
  [[nodiscard]] int CountPublicationsSince(const int year) const {
    int count = 0;
    for (const auto& p : publications_)
      if (p.year >= year) ++count;
    return count;
  }

 private:
  std::vector<Publication> publications_;  ///< Список научных трудов
};

#endif  // DOCENT_H
