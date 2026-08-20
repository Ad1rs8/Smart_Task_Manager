#include <iostream>
#include <limits>
#include <iomanip>
#include "TaskManager.h"

static void printHeader() {
    std::cout << std::left
              << std::setw(4) << "ID"
              << std::setw(20) << "Title"
              << std::setw(10) << "Priority"
              << std::setw(13) << "Status"
              << std::setw(12) << "Due Date"
              << " Description\n";
    std::cout << std::string(90, '-') << "\n";
}

static void listTasks(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "(no tasks found)\n";
        return;
    }
    printHeader();
    for (const auto& t : tasks) t.display();
}

static int readInt(const std::string& prompt) {
    int value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input, enter a number: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

static std::string readLine(const std::string& prompt) {
    std::string line;
    std::cout << prompt;
    std::getline(std::cin, line);
    return line;
}

static Priority readPriority() {
    std::cout << "Priority (1-LOW, 2-MEDIUM, 3-HIGH): ";
    int p;
    std::cin >> p;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (p == 3) return Priority::HIGH;
    if (p == 2) return Priority::MEDIUM;
    return Priority::LOW;
}

static Status readStatus() {
    std::cout << "Status (1-PENDING, 2-IN_PROGRESS, 3-COMPLETED): ";
    int s;
    std::cin >> s;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (s == 3) return Status::COMPLETED;
    if (s == 2) return Status::IN_PROGRESS;
    return Status::PENDING;
}

static void printMenu() {
    std::cout << "\n===== Smart Task Manager =====\n"
              << "1. Add Task\n"
              << "2. Update Task\n"
              << "3. Delete Task\n"
              << "4. Search Tasks by Title\n"
              << "5. View All Tasks (sorted by Priority)\n"
              << "6. View All Tasks (insertion order)\n"
              << "0. Exit\n"
              << "Choice: ";
}

int main() {
    TaskManager manager("tasks.txt");
    bool running = true;

    std::cout << "Loaded " << manager.taskCount() << " task(s) from tasks.txt\n";

    while (running) {
        printMenu();
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                std::string title = readLine("Title: ");
                std::string desc = readLine("Description: ");
                Priority p = readPriority();
                std::string due = readLine("Due Date (YYYY-MM-DD): ");
                manager.addTask(title, desc, p, due);
                std::cout << "Task added.\n";
                break;
            }
            case 2: {
                int id = readInt("Task ID to update: ");
                if (!manager.findById(id)) {
                    std::cout << "No task with that ID.\n";
                    break;
                }
                std::string title = readLine("New Title: ");
                std::string desc = readLine("New Description: ");
                Priority p = readPriority();
                std::string due = readLine("New Due Date (YYYY-MM-DD): ");
                Status s = readStatus();
                manager.updateTask(id, title, desc, p, due, s);
                std::cout << "Task updated.\n";
                break;
            }
            case 3: {
                int id = readInt("Task ID to delete: ");
                if (manager.deleteTask(id)) std::cout << "Task deleted.\n";
                else std::cout << "No task with that ID.\n";
                break;
            }
            case 4: {
                std::string keyword = readLine("Search keyword: ");
                listTasks(manager.searchByTitle(keyword));
                break;
            }
            case 5: {
                listTasks(manager.getAllTasksSortedByPriority());
                break;
            }
            case 6: {
                listTasks(manager.getAllTasks());
                break;
            }
            case 0: {
                running = false;
                std::cout << "Goodbye!\n";
                break;
            }
            default:
                std::cout << "Invalid choice, try again.\n";
        }
    }
    return 0;
}
