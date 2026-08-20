#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <vector>
#include <string>
#include "Task.h"
#include "FileHandler.h"

class TaskManager {
private:
    std::vector<Task> tasks;
    FileHandler fileHandler;
    int nextId;

    int generateNextId() const;

public:
    explicit TaskManager(const std::string& filename = "tasks.txt");

    void addTask(const std::string& title, const std::string& description,
                 Priority priority, const std::string& dueDate);
    bool updateTask(int id, const std::string& title, const std::string& description,
                     Priority priority, const std::string& dueDate, Status status);
    bool deleteTask(int id);

    std::vector<Task> searchByTitle(const std::string& keyword) const;
    Task* findById(int id);

    std::vector<Task> getAllTasksSortedByPriority() const;
    std::vector<Task> getAllTasks() const;

    void persist(); // writes current state to disk
    size_t taskCount() const;
};

#endif
