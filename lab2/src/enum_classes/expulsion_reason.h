/**
 * @file expulsion_reason.h
 * @brief Перечисление причин отчисления
 * @author Dmitry Burbas
 * @date 13/12/2025
 */
#ifndef EXPULSION_REASON_H
#define EXPULSION_REASON_H

/*!
 * @enum ExpulsionReason
 * @brief Причины отчисления студента из университета
 * @details Необходимо для операций деканата с приказами
 */
enum class ExpulsionReason {
  AcademicFailure,     ///< Академическая неуспеваемость/задолженности
  Discipline,          ///< Дисциплинарное
  OwnRequest,          ///< По собственному желанию
  TransferToOtherUni,  ///< Перевод в другой вуз
  NonPayment           ///< Неоплата (если у тебя платное и это учитывается)
};

#endif  // EXPULSION_REASON_H
