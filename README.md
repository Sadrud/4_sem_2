# Алгоритм Левита: клиент-серверная реализация

Проект реализует алгоритм Левита для поиска кратчайших путей в графе с возможностью работы в клиент-серверной архитектуре.

## Структура проекта
```
├── CMakeLists.txt
├── Include/
│ └── httplib.h
├── Methods/
│ ├── mainMethod.cpp
│ └── mainMethod.h
├── Tests/
│ └── tests.cpp
├── Server/
│ └── server.cpp
└── Client/
└── client.cpp
```
## Требования

- Компилятор C++17 (g++ или clang)
- CMake 3.10+
- Библиотека nlohmann/json

## Сборка и запуск

```bash
# Сборка
mkdir build && cd build
cmake ..
make
```


# Запуск сервера (в отдельном терминале)
```
./Server
```
# Запуск клиента
```
./Client
```
