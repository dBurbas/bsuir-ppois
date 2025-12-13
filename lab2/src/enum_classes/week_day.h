/**
 * @file week_day.h
 * @brief Описание дней недели
 * @author Dmitry Burbas
 * @date 16/11/2025
 */

#ifndef WEEKDAY_H
#define WEEKDAY_H

/**
 * @enum WeekDay
 * @brief Дни недели
 * @details Перечисление следует классическому варианту, где неделя начинается с
 * понедельника. Используется для планирования событий.
 */
enum class WeekDay {
  Monday,     ///< Понедельник (начало рабочей недели)
  Tuesday,    ///< Вторник
  Wednesday,  ///< Среда
  Thursday,   ///< Четверг
  Friday,     ///< Пятница
  Saturday,   ///< Суббота(выходной)
  Sunday      ///< Воскресенье(выходной)
};

#endif  // WEEKDAY_H
