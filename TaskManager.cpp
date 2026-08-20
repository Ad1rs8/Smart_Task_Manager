#include "TaskManager.h"
#include <algorithm>
#include <cctype>

TaskManager::TaskManager(const std::string& filename) : fileHandler(filename) {
    tasks = fileHandler.loadTasks();
    nextId = generateNextId();
}

int TaskManager::generateNextId() const {
    int maxId = 0;
    for (const auto& t : tasks) {
        if (t.getId() > maxId) maxId = t.getId();
    }
    return maxId + 1;
}

void TaskManager::addTask(const std::string& title, const std::string& description,
                           Priority priority, const std::string& dueDate) {
    Task newTask(nextId++, title, description, priority, dueDate, Status::PENDING);
    tasks.push_back(newTask);
    persist();
}

bool TaskManager::updateTask(int id, const std::string& title, const std::string& description,
                              Priority priority, const std::string& dueDate, Status status) {
    Task* t = findById(id);
    if (!t) return false;
    t->setTitle(title);
    t->setDescription(description);
    t->setPriority(priority);
    t->setDueDate(dueDate);
    t->setStatus(status);
    persist();
    return true;
}

bool TaskManager::deleteTask(int id) {
    auto it = std::remove_if(tasks.begin(), tasks.end(),
                              [id](const Task& t) { return t.getId() == id; });
    if (it == tasks.end()) return false;
    tasks.erase(it, tasks.end());
    persist();
    return true;
}

static std::string toLower(const std::string& s) {
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(),
                    [](unsigned char c) { return std::tolower(c); });
    return out;
}

std::vector<Task> TaskManager::searchByTitle(const std::string& keyword) const {
    std::vector<Task> results;
    std::string needle = toLower(keyword);
    for (const auto& t : tasks) {
        if (toLower(t.getTitle()).find(needle) != std::string::npos) {
            results.push_back(t);
        }
    }
    return results;
}

Task* TaskManager::findById(int id) {
    for (auto& t : tasks) {
        if (t.getId() == id) return &t;
    }
    return nullptr;
}

std::vector<Task> TaskManager::getAllTasksSortedByPriority() const {
    std::vector<Task> sorted = tasks;
    // HIGH first, then MEDIUM, then LOW; stable to preserve insertion order within a priority
    std::stable_sort(sorted.begin(), sorted.end(), [](const Task& a, const Task& b) {
        return static_cast<int>(a.getPriority()) > static_cast<int>(b.getPriority());
    });
    return sorted;
}

std::vector<Task> TaskManager::getAllTasks() const {
    return tasks;
}

void TaskManager::persist() {
    fileHandler.saveTasks(tasks);
}

size_t TaskManager::taskCount() const {
    return tasks.size();
}
