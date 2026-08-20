#ifndef TASK_H
#define TASK_H

#include <string>

enum class Priority { LOW = 1, MEDIUM = 2, HIGH = 3 };
enum class Status { PENDING, IN_PROGRESS, COMPLETED };

class Task {
private:
    int id;
    std::string title;
    std::string description;
    Priority priority;
    Status status;
    std::string dueDate; // stored as YYYY-MM-DD string

public:
    Task();
    Task(int id, const std::string& title, const std::string& description,
         Priority priority, const std::string& dueDate, Status status = Status::PENDING);

    // Getters
    int getId() const;
    std::string getTitle() const;
    std::string getDescription() const;
    Priority getPriority() const;
    Status getStatus() const;
    std::string getDueDate() const;

    // Setters
    void setTitle(const std::string& t);
    void setDescription(const std::string& d);
    void setPriority(Priority p);
    void setStatus(Status s);
    void setDueDate(const std::string& d);

    // Serialization helpers
    std::string serialize() const;
    static Task deserialize(const std::string& line);

    static std::string priorityToString(Priority p);
    static Priority stringToPriority(const std::string& s);
    static std::string statusToString(Status s);
    static Status stringToStatus(const std::string& s);

    void display() const;
};

#endif
