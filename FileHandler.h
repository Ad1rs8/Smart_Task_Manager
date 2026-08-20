#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <vector>
#include "Task.h"

class FileHandler {
private:
    std::string filename;

public:
    explicit FileHandler(const std::string& filename = "tasks.txt");

    std::vector<Task> loadTasks() const;
    bool saveTasks(const std::vector<Task>& tasks) const;
};

#endif
