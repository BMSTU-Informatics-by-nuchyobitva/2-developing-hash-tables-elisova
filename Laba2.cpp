#include <iostream>
#include <vector>
#include <list>
#include <string>

struct Car {
    int id;
    std::string brand;
};

// хеш табоица с разельным чейнингом
class HashTable {
private:
    std::vector<std::list<Car>> table;  
    size_t capacity;                    
    size_t count;                       

    // этим вдохновилась в интернетах каюсь
    size_t hashFunction(const Car& car) const {
        unsigned long h = 0;
        const unsigned long P = 31;
        // polynomial hash on string
        for (char c : car.brand) {
            h = h * P + static_cast<unsigned char>(c);
        }
        // mix in the integer field
        h ^= static_cast<unsigned long>(car.id) * 2654435761u;
        return h % capacity;
    }

public:
    HashTable(size_t cap = 16)
        : table(cap), capacity(cap), count(0) {}

    void insert(const Car& car) {
        size_t idx = hashFunction(car);
        for (auto& item : table[idx]) {
            if (item.id == car.id) {
                item = car;  // оверрайт
                return;
            }
        }
        table[idx].push_back(car);
        ++count;
    }

    bool remove(int id) {
        Car dummy{ id, "" };
        size_t idx = hashFunction(dummy);
        auto& bucket = table[idx];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->id == id) {
                bucket.erase(it);
                --count;
                return true;
            }
        }
        return false;
    }

    bool find(int id, Car& result) const {
        Car dummy{ id, "" };
        size_t idx = hashFunction(dummy);
        for (auto& item : table[idx]) {
            if (item.id == id) {
                result = item;
                return true;
            }
        }
        return false;
    }

    void print() const {
        std::cout << "HashTable contents (" << count << " items):\n";
        for (size_t i = 0; i < capacity; ++i) {
            std::cout << "[" << i << "]: ";
            for (auto& car : table[i]) {
                std::cout << "{id:" << car.id
                    << ", brand:\"" << car.brand << "\"} -> ";
            }
            std::cout << "|\n";
        }
    }

    size_t size() const { return count; }
    bool isEmpty() const { return count == 0; }
};

// тестовые данные
int main() {
    HashTable ht(8);

    ht.insert({ 101, "Toyota" });
    ht.insert({ 202, "Ford" });
    ht.insert({ 303, "BMW" });
    ht.insert({ 404, "Tesla" });

    ht.print();

    Car found;
    if (ht.find(202, found)) {
        std::cout << "Found id=202: brand=" << found.brand << "\n";
    }

    ht.remove(303);
    std::cout << "After removing id=303:\n";
    ht.print();

    return 0;
} 