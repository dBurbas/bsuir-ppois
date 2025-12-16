/**
 * @file group.h
 * @brief Класс студенческой группы
 * @author Dmitry Burbas
 * @date 16/11/2025
 */

#ifndef GROUP_H
#define GROUP_H

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "../exceptions/dean_office_exceptions.h"
#include "../people/teacher/teacher.h"

// Forward declaration
class Student;
class Teacher;

/**
 * @class Group
 * @brief Представляет учебную группу студентов
 * @details Агрегирует студентов, предоставляя методы для управления составом
 * (добавление, удаление, поиск). Хранит студентов в векторе.
 */
class Group {
 public:
  /**
   * @brief Конструктор группы
   * @param id Уникальный идентификатор группы (шифр)
   * @throws GroupException, если ID пуст
   */
  explicit Group(std::string id) : id_(std::move(id)) { ValidateGroupId(id_); }

  /**
   * @brief Получение списка всех студентов
   * @return Константная ссылка на вектор студентов
   */
  [[nodiscard]] const std::vector<std::shared_ptr<Student>>& GetStudents()
      const {
    return students_;
  }

  /**
   * @brief Получение ID группы
   */
  [[nodiscard]] const std::string& GetId() const { return id_; }

  /**
   * @brief Добавляет студента в группу
   * @param student Умный указатель на студента
   * @throws GroupException, если указатель null или студент с таким ID уже есть
   */
  void AddStudent(std::shared_ptr<Student> student);

  /**
   * @brief Получает студента по его порядковому номеру в списке
   * @param teacher Преподаватель, запрашивающий студента
   * @param student_numb Порядковый номер (начиная с 1)
   * @return Умный указатель на студента
   * @throws GroupException, если номер некорректен, преподаватель не активен
   * или студент null
   * @warning Логика требует наличия активного преподавателя для доступа, что
   * спорно.
   */
  [[nodiscard]] std::shared_ptr<Student> GetStudentByNumber(
      const std::shared_ptr<Teacher>& teacher, int student_numb);

  /**
   * @brief Ищет студента по ID (номеру студенческого)
   * @param student_id ID студента
   * @return Умный указатель на студента или nullptr, если не найден
   */
  [[nodiscard]] std::shared_ptr<Student> FindStudent(
      const std::string& student_id) const;

  /**
   * @brief Удаляет студента из группы по ID
   * @param student_id ID удаляемого студента
   * @details Использует erase-remove идиому. Меняет порядок/индексы оставшихся
   * студентов.
   */
  void RemoveStudent(const std::string& student_id);

  /**
   * @brief Получение количества студентов
   */
  [[nodiscard]] size_t GetSize() const { return students_.size(); }

  /**
   * @brief Проверка на пустоту
   */
  [[nodiscard]] bool IsEmpty() const { return students_.empty(); }

 private:
  /**
   * @brief Валидация ID группы
   * @throws GroupException, если строка пуста
   */
  static void ValidateGroupId(const std::string& group_id) {
    if (group_id.empty()) throw GroupException("Group ID cannot be empty");
  }

  std::vector<std::shared_ptr<Student>> students_;  ///< Список студентов
  std::string id_;                                  ///< Шифр группы
};

#endif  // GROUP_H
