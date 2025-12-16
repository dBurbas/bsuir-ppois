/**
 * @file subject.h
 * @brief Класс учебной дисциплины (предмета)
 * @author Dmitry Burbas
 * @date 14/12/2025
 */
#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>

#include "../exceptions/dean_office_exceptions.h"

/**
 * @class Subject
 * @brief Представляет учебную дисциплину с названием, часами и привязкой к
 * кафедре.
 * @details Класс хранит основную информацию о предмете и выполняет валидацию
 * входных данных, таких как количество часов и наличие идентификаторов.
 */
class Subject {
 public:
  /**
   * @brief Конструктор дисциплины.
   * @param id Уникальный идентификатор дисциплины.
   * @param name Название дисциплины.
   * @param department_id Идентификатор кафедры, к которой относится дисциплина.
   * @param hours Количество академических часов, выделенных на дисциплину.
   * @throws SubjectException, если один из идентификаторов или имя пусты, или
   * если количество часов некорректно (<= 0).
   */
  Subject(std::string id, std::string name, std::string department_id,
          const int hours)
      : id_(std::move(id)),
        name_(std::move(name)),
        department_id_(std::move(department_id)),
        hours_(hours) {
    if (id_.empty()) throw SubjectException("Subject id is empty");
    if (name_.empty()) throw SubjectException("Subject name is empty");
    if (department_id_.empty())
      throw SubjectException("Subject department id is empty");
    ValidateHours(hours_);
  }

  /**
   * @brief Устанавливает новое количество часов для дисциплины.
   * @param hours Новое количество часов.
   * @throws SubjectException, если количество часов некорректно (<= 0).
   */
  void SetHours(const int hours) {
    ValidateHours(hours);
    hours_ = hours;
  }

  /**
   * @brief Получение идентификатора дисциплины.
   * @return Константная ссылка на строку с ID.
   */
  [[nodiscard]] const std::string& GetId() const { return id_; }

  /**
   * @brief Получение названия дисциплины.
   * @return Константная ссылка на строку с названием.
   */
  [[nodiscard]] const std::string& GetName() const { return name_; }

  /**
   * @brief Получение идентификатора кафедры.
   * @return Константная ссылка на строку с ID кафедры.
   */
  [[nodiscard]] const std::string& GetDepartmentId() const {
    return department_id_;
  }

  /**
   * @brief Получение количества часов.
   * @return Количество часов.
   */
  [[nodiscard]] int GetHours() const { return hours_; }

 private:
  /**
   * @brief Проверяет корректность количества часов.
   * @param hours Количество часов для проверки.
   * @throws SubjectException, если количество часов меньше или равно нулю.
   */
  static void ValidateHours(const int hours) {
    if (hours <= 0) throw SubjectException("Subject hours is invalid");
  }

  std::string id_;             ///< Уникальный идентификатор дисциплины
  std::string name_;           ///< Название дисциплины
  std::string department_id_;  ///< ID кафедры, к которой приписана дисциплина
  int hours_;                  ///< Количество академических часов
};

#endif  // SUBJECT_H
