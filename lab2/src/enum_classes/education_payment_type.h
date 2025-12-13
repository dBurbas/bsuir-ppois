/**
 * @file education_payment_type.h
 * @brief Тип платы за обучение студента в университете
 * @author Dmitry Burbas
 * @date 16/11/2025
 */
#ifndef EDUCATION_PAYMENT_TYPE_H
#define EDUCATION_PAYMENT_TYPE_H

/*!
 * @enum EducationPaymentType
 * @brief Тип платы за обучение студента
 * @details Отражает состояние обучающегося для операций деканата(в основном
 * стипендии)
 */
enum class EducationPaymentType {
  Budget,   ///< Бюджетное (платит ВУЗ)
  Paid,     ///< Платное (платит студент)
  Targeted  ///< Целевое (платит компания заинтересованная в обучении себе
            ///< работника)
};

#endif  // EDUCATION_PAYMENT_TYPE_H
