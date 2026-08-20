#include "Task.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>

Task::Task() : id(0), priority(Priority::LOW), status(Status::PENDING) {}

Task::Task(int id, const std::string& title, const std::string& description,
           Priority priority, const std::string& dueDate, Status status)
    : id(id), title(title), description(description), priority(priority),
      status(status), dueDate(dueDate) {}

int Task::getId() const { return id; }
std::string Task::getTitle() const { return title; }
std::string Task::getDescription() const { return description; }
Priority Task::getPriority() const { return priority; }
Status Task::getStatus() const { return status; }
std::string Task::getDueDate() const { return dueDate; }

void Task::setTitle(const std::string& t) { title = t; }
void Task::setDescription(const std::string& d) { description = d; }
void Task::setPriority(Priority p) { priority = p; }
void Task::setStatus(Status s) { status = s; }
void Task::setDueDate(const std::string& d) { dueDate = d; }

std::string Task::priorityToString(Priority p) {
    switch (p) {
        case Priority::HIGH: return "HIGH";
        case Priority::MEDIUM: return "MEDIUM";
        default: return "LOW";
    }
}

Priority Task::stringToPriority(const std::string& s) {
    if (s == "HIGH") return Priority::HIGH;
    if (s == "MEDIUM") return Priority::MEDIUM;
    return Priority::LOW;
}

std::string Task::statusToString(Status s) {
    switch (s) {
        case Status::COMPLETED: return "COMPLETED";
        case Status::IN_PROGRESS: return "IN_PROGRESS";
        default: return "PENDING";
    }
}

Status Task::stringToStatus(const std::string& s) {
    if (s == "COMPLETED") return Status::COMPLETED;
    if (s == "IN_PROGRESS") return Status::IN_PROGRESS;
    return Status::PENDING;
}

// Fields joined with '|' delimiter. Any '|' in text fields is escaped as "~PIPE~"
static std::string escapePipes(const std::string& in) {
    std::string out;
    for (char c : in) {
        if (c == '|') out += "~PIPE~";
        else out += c;
    }
    return out;
}

static std::string unescapePipes(const std::string& in) {
    std::string out = in;
    size_t pos;
    while ((pos = out.find("~PIPE~")) != std::string::npos) {
        out.replace(pos, 6, "|");
    }
    return out;
}

std::string Task::serialize() const {
    std::ostringstream oss;
    oss << id << "|" << escapePipes(title) << "|" << escapePipes(description) << "|"
        << priorityToString(priority) << "|" << statusToString(status) << "|" << dueDate;
    return oss.str();
}

Task Task::deserialize(const std::string& line) {
    std::vector<std::string> fields;
    std::string field;
    std::istringstream iss(line);
    while (std::getline(iss, field, '|')) {
        fields.push_back(field);
    }
    // Guard against malformed lines
    while (fields.size() < 6) fields.push_back("");

    Task t;
    try {
        t.id = std::stoi(fields[0]);
    } catch (...) {
        t.id = 0;
    }
    t.title = unescapePipes(fields[1]);
    t.description = unescapePipes(fields[2]);
    t.priority = stringToPriority(fields[3]);
    t.status = stringToStatus(fields[4]);
    t.dueDate = fields[5];
    return t;
}

void Task::display() const {
    std::cout << std::left
              << std::setw(4) << id
              << std::setw(20) << title
              << std::setw(10) << priorityToString(priority)
              << std::setw(13) << statusToString(status)
              << std::setw(12) << dueDate
              << " " << description << "\n";
}
