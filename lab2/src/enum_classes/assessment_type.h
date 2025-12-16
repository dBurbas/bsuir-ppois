/**
 * @file assessment_type.h
 * @brief Перечисление видов промежуточной аттестации
 * @author Dmitry Burbas
 * @date 14/12/2025
 */

#ifndef ASSESSMENT_TYPE_H
#define ASSESSMENT_TYPE_H

/**
 * @enum AssessmentType
 * @brief Тип контроля знаний (форма сдачи предмета)
 * @details Используется классом Assessment для определения логики создания
 * оценок (фабричный метод) и выбора шкалы оценивания.
 */
enum class AssessmentType {
  /**
   * @brief Зачет
   * @details Недифференцированная оценка.
   * Соответствует созданию объекта PassFailGrade (зачтено/не зачтено).
   */
  CreditTest,

  /**
   * @brief Экзамен
   * @details Дифференцированная оценка (с баллами).
   * Соответствует созданию объекта NumericGrade.
   */
  Exam
};

#endif  // ASSESSMENT_TYPE_H
