#include "FileHandler.h"
#include <fstream>
#include <iostream>

FileHandler::FileHandler(const std::string& filename) : filename(filename) {}

std::vector<Task> FileHandler::loadTasks() const {
    std::vector<Task> tasks;
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        // No file yet is not an error on first run
        return tasks;
    }
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        tasks.push_back(Task::deserialize(line));
    }
    inFile.close();
    return tasks;
}

bool FileHandler::saveTasks(const std::vector<Task>& tasks) const {
    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Error: could not open " << filename << " for writing.\n";
        return false;
    }
    for (const auto& task : tasks) {
        outFile << task.serialize() << "\n";
    }
    outFile.close();
    return true;
}
