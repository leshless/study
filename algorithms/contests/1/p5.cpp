#include <iostream>
#include <stdexcept>

struct Node {
public:
    Node* prev;
    Node* next;
    int value;

    Node() {
        next = prev = nullptr;
        value = 0;
    }
    Node(const int& value): value(value) { next = prev = nullptr; }
    Node(Node* prev, Node* next, const int& value) : prev(prev), next(next), value(value) {}

    ~Node() = default;
};

class List {
private:
    size_t _size;
    Node* head;
    Node* tail;
    Node* mid;

public:
    List() {
        this->head = nullptr;
        this->tail = nullptr;
        this->mid = nullptr;
        this->_size = 0;
    }

    int front() {
        if (this->tail == nullptr) {
            return 0;
        }

        return this->tail->value;
    }

    void push(int value) {
        Node* node = new Node(nullptr, this->head, value);
        if (this->head == nullptr) { 
            this->tail = node;
            this->mid = node;
        } else {
            this->head->prev = node;
            if (this->_size % 2 == 0) {
                this->mid = this->mid->prev;
            }
        }
        this->head = node;
        
        this->_size++;
    }

    void insert_mid(int value) {
        if (this->head == nullptr) {
            this->push(value);
            return;
        }

        Node* prev = this->mid->prev;
        Node* node = new Node(prev, this->mid, value);
        if (prev == nullptr) {
            this->head = node;
        } else {
            prev->next = node;
        }
        this->mid->prev = node;

        if (this->_size % 2 == 0) {
            this->mid = this->mid->prev;
        }

        this->_size++;
    }

    void print() {
        Node* cur = this->head;

        std::cout << "[" << this->_size << "] ";
        while (cur != nullptr) {
            if (cur == this->mid) {
                std::cout << "(" << cur->value << ")" << " ";
            }else {
                std::cout << cur->value << " ";
            }
            cur = cur->next;
        }
        std::cout << std::endl;
    }

    void pop() {
        if (this->head == nullptr) {
            throw std::runtime_error("Deleting in empty list");
        }

        Node* head = this->head;
        Node* tail = this->tail;
        if (head == tail) {
            this->tail = nullptr;
            this->head = nullptr;
            this->mid = nullptr;
        } else {
            this->tail = tail->prev;
            if (tail->prev != nullptr) {
                tail->prev->next = nullptr;
            }
            if (this->_size % 2 == 0) {
                this->mid = this->mid->prev;
            }
        }
        free(tail);

        this->_size--;
    }

    size_t size() const {
        return this->_size;
    };

    bool empty() const {
        return (this->_size == 0);
    };

    ~List() = default;
};


int main() {
    std::ios::sync_with_stdio(false);  
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    auto list = List();
    // list.print();

    while (q--) {
        char c; int x;
        std::cin >> c;

        switch (c) {
        case '+':
            std::cin >> x;

            list.push(x);

            break;
        case '*':
            std::cin >> x;

            list.insert_mid(x);
            
            break;
        case '-':
            std::cout << list.front() << std::endl;
            list.pop();

            break;
        }

        // list.print();
    }

    

    return 0;
}