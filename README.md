# Smart Task Manager

Console-based task manager in C++ with OOP design and persistent file storage.

## Build

```bash
g++ -std=c++17 -Wall -o task_manager Task.cpp FileHandler.cpp TaskManager.cpp main.cpp
```

## Run

```bash
./task_manager
```

Tasks are saved to `tasks.txt` in the same directory after every add/update/delete,
so data survives across runs.

## Files

- `Task.h/.cpp` — Task entity: fields, getters/setters, serialize/deserialize
- `FileHandler.h/.cpp` — reads/writes `tasks.txt`
- `TaskManager.h/.cpp` — business logic: add/update/delete/search/sort
- `main.cpp` — console menu UI
