# Задание: Хэш-таблица (вар 28)

В этом репозитории:

- **CarHashTable.cpp** – реализация хэш-таблицы с использованием цепочек  
- Этот **README** с описанием сделанных выборов и инструкцией по запуску

---

## 1. Пользовательский класс данных (сделала с машинкой)

```cpp
struct Car {
    int id;
    std::string brand;
};
```

- `id` (int) — уникальный идентификатор для хеша
- `brand` (string) — дополнительное поле, учитываемое при вычислении хэша  

---

## 2. Операции таблицы

- **insert(Car)** — вставка элемента  
- **remove(int id)** — удаление по `id`  
- **find(int id, Car& out)** — поиск по `id`  
- **print()** — вывод содержимого таблицы (каждого бакета)
