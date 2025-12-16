/**
 * @file student_status.h
 * @brief Административный статус студента в университете
 * @author Dmitry Burbas
 * @date 13/12/2025
 */
#ifndef STUDENT_STATUS_H
#define STUDENT_STATUS_H

/*!
 * @enum StudentStatus
 * @brief Статус обучения студента в университете
 * @details Отражает текущее состояние обучающегося для операций деканата
 */
enum class StudentStatus {
  Studying,       ///< Учится (активный)
  Expelled,       ///< Отчислен (по различным причинам)
  AcademicLeave,  ///< Академический отпуск (временно не обучается, но сохраняет
                  ///< статус студента)
  UnjustifiedLeave
};

#endif  // STUDENT_STATUS_H
