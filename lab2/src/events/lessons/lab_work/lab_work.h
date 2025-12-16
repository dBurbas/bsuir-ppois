/**
 * @file lab_work.h
 * @brief Класс лабораторной работы
 * @author Dmitry Burbas
 * @date 15/12/2025
 */

#ifndef LAB_WORK_H
#define LAB_WORK_H

#include <memory>
#include <string>
#include <utility>

#include "../lesson/lesson.h"

/**
 * @class LabWork
 * @brief Представляет лабораторное занятие
 * @details Наследуется от Lesson. Структурно идентичен классу Seminar.
 * Реализует проведение лабораторной работы.
 */
class LabWork : public Lesson {
 public:
  /**
   * @brief Конструктор лабораторной работы
   * @param title Тема работы
   * @param date Дата проведения
   * @param address Аудитория
   * @param teacher Преподаватель (слабая ссылка)
   * @param group Группа (слабая ссылка)
   * @param subject_id ID предмета
   */
  LabWork(const std::string& title, const Date& date, Address address,
          std::weak_ptr<Teacher> teacher, std::weak_ptr<Group> group,
          std::string subject_id)
      : Lesson(title, date, std::move(address), std::move(teacher),
               std::move(group), std::move(subject_id)) {}

  /**
   * @brief Проведение лабораторной работы
   * @details Выполняет заглушку DoTheLab() и отмечает студентов (MarkStudents).
   */
  void Hold() override {
    DoTheLab();
    MarkStudents();
  }

  /**
   * @brief Имитация выполнения лабораторной работы
   * @details В данной реализации метод пуст. Никаких действий не производится.
   */
  void DoTheLab() {
    // TODO: Реализовать логику проведения лабораторной, например, сдачу лаб
  }
};

#endif  // LAB_WORK_H
