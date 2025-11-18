#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>

// Элемент хеш-таблицы - список объектов с одним хешем
template <class KeyType, class ValueType>
struct Node {
    KeyType key;
    ValueType value;
    Node *next;

    Node(KeyType k, ValueType v) : key(k), value(v), next(nullptr) {}
};

// Хеш-таблица
template <class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
private:
    std::vector<Node<KeyType, ValueType>> table;  // Вектор узлов
    Func hasher;
    size_t numElements;
    double maxLoadFactor;
    
    static const size_t DEFAULT_CAPACITY = 100;
    static const double DEFAULT_LOAD_FACTOR;
    
    size_t hash(const KeyType& key) const {
        return hasher(key) % table.size();
    }
    
    void rehash() {
        std::vector<Node<KeyType, ValueType>> oldTable = std::move(table);
        size_t newCapacity = oldTable.empty() ? DEFAULT_CAPACITY : oldTable.size() * 2;
        table.resize(newCapacity);
        numElements = 0;
        
        // Перебираем все ячейки старой таблицы
        for (size_t i = 0; i < oldTable.size(); ++i) {
            Node<KeyType, ValueType>* current = &oldTable[i];
            
            // Пропускаем пустые ячейки
            if (current->next == nullptr && !(current->key == KeyType())) {
                // Вставляем узел в новую таблицу
                size_t newIndex = hash(current->key);
                
                // Если ячейка пустая, копируем узел напрямую
                if (table[newIndex].next == nullptr && table[newIndex].key == KeyType()) {
                    table[newIndex].key = current->key;
                    table[newIndex].value = current->value;
                } else {
                    // Ищем конец цепочки
                    Node<KeyType, ValueType>* chainEnd = &table[newIndex];
                    while (chainEnd->next != nullptr) {
                        chainEnd = chainEnd->next;
                    }
                    
                    // Создаем новый узел для копии
                    Node<KeyType, ValueType>* newNode = new Node<KeyType, ValueType>(current->key, current->value);
                    chainEnd->next = newNode;
                }
                
                numElements++;
            }
            
            // Обрабатываем цепочку коллизий
            while (current->next != nullptr) {
                Node<KeyType, ValueType>* nextNode = current->next;
                
                // Вставляем узел в новую таблицу
                size_t newIndex = hash(nextNode->key);
                
                // Если ячейка пустая, копируем узел напрямую
                if (table[newIndex].next == nullptr && table[newIndex].key == KeyType()) {
                    table[newIndex].key = nextNode->key;
                    table[newIndex].value = nextNode->value;
                } else {
                    // Ищем конец цепочки
                    Node<KeyType, ValueType>* chainEnd = &table[newIndex];
                    while (chainEnd->next != nullptr) {
                        chainEnd = chainEnd->next;
                    }
                    
                    // Создаем новый узел для копии
                    Node<KeyType, ValueType>* newNode = new Node<KeyType, ValueType>(nextNode->key, nextNode->value);
                    chainEnd->next = newNode;
                }
                
                numElements++;
                delete nextNode;
                current->next = nullptr;
                current = &oldTable[i];
            }
        }
    }

public:
    HashTable() : HashTable(DEFAULT_CAPACITY, DEFAULT_LOAD_FACTOR) {}
    
    HashTable(Func func) : HashTable(DEFAULT_CAPACITY, DEFAULT_LOAD_FACTOR, func) {}
    
    HashTable(size_t capacity, double loadFactor, Func func = std::hash<KeyType>())
        : hasher(func), numElements(0) {
        if (loadFactor <= 0.0 || loadFactor > 1.0) {
            maxLoadFactor = DEFAULT_LOAD_FACTOR;
        } else {
            maxLoadFactor = loadFactor;
        }
        table.resize(capacity);
    }

    ~HashTable() {
        for (size_t i = 0; i < table.size(); ++i) {
            Node<KeyType, ValueType>* current = table[i].next;
            while (current != nullptr) {
                Node<KeyType, ValueType>* next = current->next;
                delete current;
                current = next;
            }
        }
    }

    void insert(KeyType key, ValueType value) {
        if (table.empty()) {
            table.resize(DEFAULT_CAPACITY);
        }
        
        if ((double)numElements / table.size() > maxLoadFactor) {
            rehash();
        }
        
        size_t index = hash(key);
        
        // Проверяем, пуста ли ячейка
        if (table[index].next == nullptr && table[index].key == KeyType()) {
            table[index].key = key;
            table[index].value = value;
            numElements++;
            return;
        }
        
        // Ищем существующий ключ
        Node<KeyType, ValueType>* current = &table[index];
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            if (current->next == nullptr) break;
            current = current->next;
        }
        
        // Вставляем новый элемент в конец цепочки
        Node<KeyType, ValueType>* newNode = new Node<KeyType, ValueType>(key, value);
        current->next = newNode;
        numElements++;
    }

    ValueType *find(KeyType key) {
        if (table.empty()) return nullptr;
        
        size_t index = hash(key);
        Node<KeyType, ValueType>* current = &table[index];
        
        while (current != nullptr) {
            if (current->key == key && !(current->key == KeyType() && current->next == nullptr)) {
                return &(current->value);
            }
            current = current->next;
        }
        
        return nullptr;
    }

    void erase(KeyType key) {
        if (table.empty()) return;
        
        size_t index = hash(key);
        
        // Специальный случай: удаляем первый узел в цепочке
        if (table[index].key == key) {
            if (table[index].next != nullptr) {
                // Если есть следующий узел, перемещаем его данные на место первого
                Node<KeyType, ValueType>* nextNode = table[index].next;
                table[index].key = nextNode->key;
                table[index].value = nextNode->value;
                table[index].next = nextNode->next;
                delete nextNode;
            } else {
                // Если это единственный узел, сбрасываем значения
                table[index].key = KeyType();
                table[index].value = ValueType();
            }
            numElements--;
            return;
        }
        
        // Ищем узел в цепочке (не первый)
        Node<KeyType, ValueType>* current = &table[index];
        while (current->next != nullptr) {
            if (current->next->key == key) {
                Node<KeyType, ValueType>* toDelete = current->next;
                current->next = toDelete->next;
                delete toDelete;
                numElements--;
                return;
            }
            current = current->next;
        }
    }

    Node<KeyType, ValueType> &operator[](uint64_t index) {
        if (index >= table.size()) {
            throw std::out_of_range("Index out of range");
        }
        if (table[index].next == nullptr && table[index].key == KeyType()) {
            throw std::runtime_error("Empty cell");
        }
        return table[index];
    }

    Node<KeyType, ValueType> at(uint64_t index) {
        if (index >= table.size()) {
            throw std::out_of_range("Index out of range");
        }
        if (table[index].next == nullptr && table[index].key == KeyType()) {
            throw std::runtime_error("Empty cell");
        }
        return table[index];
    }

    int size() const {
        return numElements;
    }

    int capacity() const {
        return table.size();
    }
};

template <class KeyType, class ValueType, class Func>
const double HashTable<KeyType, ValueType, Func>::DEFAULT_LOAD_FACTOR = 0.5;