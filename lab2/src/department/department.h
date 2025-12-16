/**
 * @file department.h
 * @brief Класс кафедры (департамента) учебного заведения
 * @author Dmitry Burbas
 * @date 16/11/2025
 */

#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <memory>
#include <string>
#include <vector>

#include "../exceptions/dean_office_exceptions.h"
#include "../people/teacher/teacher.h"
#include "../subject/subject.h"

/**
 * @class Department
 * @brief Представляет кафедру с преподавателями, предметами и заведующим
 * @details Содержит списки сотрудников и дисциплин, а также управляет
 * назначением заведующего кафедрой. Обеспечивает валидацию данных при создании
 * и модификации.
 */
class Department {
 public:
  /**
   * @brief Конструктор кафедры с идентификатором и названием
   * @param id Уникальный идентификатор кафедры
   * @param name Название кафедры
   * @throws DepartmentException, если название кафедры пустое
   * @details Инициализирует кафедру, проверяя корректность переданного
   * названия. Идентификатор сохраняется без дополнительной валидации.
   */
  explicit Department(std::string id, std::string name)
      : name_(std::move(name)), id_(std::move(id)) {
    if (name_.empty())
      throw DepartmentException("Department name cannot be empty");
  }

  /**
   * @brief Добавляет преподавателя на кафедру
   * @param teacher Умный указатель на добавляемого преподавателя
   * @throws DepartmentException, если передан нулевой указатель
   * @details Проверяет, существует ли уже этот преподаватель в списке, чтобы
   * избежать дубликатов. Если преподаватель уже есть, действие игнорируется.
   */
  void AddTeacher(const std::shared_ptr<Teacher>& teacher) {
    if (!teacher) throw DepartmentException("Cannot add null teacher");

    for (const auto& t : teachers_) {
      if (t == teacher) return;
    }
    teachers_.push_back(teacher);
  }

  /**
   * @brief Назначает заведующего кафедрой
   * @param head Слабый указатель на преподавателя
   * @throws DepartmentException, если переданный указатель указывает на
   * удаленный объект
   * @details Сохраняет weak_ptr для предотвращения циклических ссылок.
   * Не проверяет, является ли назначаемый преподаватель сотрудником этой
   * кафедры.
   */
  void SetHeadOfDepartment(std::weak_ptr<Teacher> head) {
    if (head.expired())
      throw DepartmentException("Cannot set dead head of department");
    head_ = std::move(head);
  }

  /**
   * @brief Добавляет дисциплину (предмет) на кафедру
   * @param subject Умный указатель на предмет
   * @throws DepartmentException, если передан нулевой указатель
   * @details Просто добавляет предмет в конец списка без проверки на дубликаты.
   */
  void AddSubject(const std::shared_ptr<Subject>& subject) {
    if (!subject) throw DepartmentException("Cannot add null subject");
    subjects_.push_back(subject);
  }

  /**
   * @brief Получение названия кафедры
   * @return Константная ссылка на строку с названием
   */
  [[nodiscard]] const std::string& GetName() const { return name_; }

  /**
   * @brief Получение списка преподавателей
   * @return Константная ссылка на вектор указателей на преподавателей
   */
  [[nodiscard]] const std::vector<std::shared_ptr<Teacher>>& GetTeachers()
      const {
    return teachers_;
  }

  /**
   * @brief Получение списка предметов
   * @return Константная ссылка на вектор указателей на предметы
   */
  [[nodiscard]] const std::vector<std::shared_ptr<Subject>>& GetSubjects()
      const {
    return subjects_;
  }

  /**
   * @brief Получение текущего заведующего кафедрой
   * @return Умный указатель (shared_ptr) на заведующего
   * @throws DepartmentException, если заведующий не назначен или объект удален
   * @details Пытается заблокировать weak_ptr. Если объект уже не существует,
   * выбрасывает исключение.
   */
  [[nodiscard]] std::shared_ptr<Teacher> GetHeadOfDepartment() const {
    if (head_.expired())
      throw DepartmentException("Cannot get head of department");
    return head_.lock();
  }

 private:
  std::string name_;  ///< Название кафедры
  std::string id_;    ///< Уникальный идентификатор кафедры
  std::vector<std::shared_ptr<Teacher>> teachers_;  ///< Список преподавателей

  std::vector<std::shared_ptr<Subject>> subjects_;  ///< Список предметов

  std::weak_ptr<Teacher> head_;  ///< Слабая ссылка на заведующего
};

#endif  // DEPARTMENT_H
