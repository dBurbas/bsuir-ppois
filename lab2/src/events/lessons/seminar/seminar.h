/**
 * @file seminar.h
 * @brief Класс семинарского занятия
 * @author Dmitry Burbas
 * @date 15/12/2025
 */

#ifndef SEMINAR_H
#define SEMINAR_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "../lesson/lesson.h"

/**
 * @class Seminar
 * @brief Представляет практическое занятие (семинар)
 * @details Наследуется от Lesson. Реализует конкретную логику проведения
 * занятия, включая выполнение практической работы и отметку присутствующих.
 */
class Seminar : public Lesson {
 public:  // ДОБАВЛЕНО МНОЮ: Без этого конструктор был бы приватным!
  /**
   * @brief Конструктор семинара
   * @param title Тема занятия
   * @param date Дата проведения
   * @param address Место проведения
   * @param teacher Преподаватель (слабая ссылка)
   * @param group Учебная группа (слабая ссылка)
   * @param subject_id ID предмета
   */
  Seminar(const std::string& title, const Date& date, Address address,
          std::weak_ptr<Teacher> teacher, std::weak_ptr<Group> group,
          std::string subject_id)
      : Lesson(title, date, std::move(address), std::move(teacher),
               std::move(group), std::move(subject_id)) {}

  /**
   * @brief Проведение занятия
   * @details Переопределяет метод базового класса.
   * Выполняет последовательно: саму работу семинара (DoTheSeminar)
   * и отметку студентов (MarkStudents, наследуется от Lesson).
   */
  void Hold() override {
    DoTheSeminar();
    MarkStudents();
  }

 private:
  /**
   * @brief Имитация работы на семинаре
   * @details Выводит сообщение в стандартный поток вывода.
   */
  void DoTheSeminar() {}
};

#endif  // SEMINAR_H
