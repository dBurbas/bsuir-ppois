/**
 * @file employee_status.h
 * @brief Административный статус работника
 * @author Dmitry Burbas
 * @date 11/12/2025
 */
#ifndef EMPLOYEE_STATUS_H
#define EMPLOYEE_STATUS_H

/*!
 * @enum EmployeeStatus
 * @brief Статус работника в компании
 * @details Отражает текущее состояние работника для операций деканата
 */
enum class EmployeeStatus {
  Active,   ///< Работает
  Fired,    ///< Уволен (больше не является сотрудником)
  OnLeave,  ///< В официально отпуске (ежегодном, по болезни и т.д.)
  Trainee   ///< Проходит стажировку или испытательный срок
};
#endif  // EMPLOYEE_STATUS_H
