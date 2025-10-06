#include <vector>
#include <stdexcept>
#include <unordered_map>

#include "list.h"

List::List() {
    this->head = nullptr;
    this->tail = nullptr;    
    this->_size = 0;
}

List::List(const List& other){
    this->head = nullptr;
    this->tail = nullptr;    
    this->_size = 0;

    Node* cur = other.head;

    while (cur != nullptr) {
        this->push_back(cur->value);
        cur = cur->next;
    }
}

List::List(std::vector<int> array){
    this->head = nullptr;
    this->tail = nullptr;    
    this->_size = 0;

    for (size_t i = 0; i < array.size(); i++) {
        this->push_back(array[i]);
    }
}

// Uncommenting this causes double free panic on list with cycle xd
List::~List(){
    // Node* cur = this->head;
    // while (cur != nullptr) {
    //     Node* next = cur->next;
    //     free(cur);
        
    //     cur = next;
    // }
    return; 
}

int List::front() {
    if (this->head == nullptr) {
        return 0;
    }

    return this->head->value;
}

int List::back() {
    if (this->tail == nullptr) {
        return 0;
    }

    return this->tail->value;
}

void List::push_back(int value) {
    Node* next = new Node(this->tail, nullptr, value);
    if (this->tail != nullptr) {
        this->tail->next = next;
    }
    if (this->head == nullptr) { 
        this->head = next;
    }
    this->tail = next;
    
    this->_size++;
}

void List::push_front(int value) {
    Node* prev = new Node(nullptr, this->head, value);
    if (this->head != nullptr) {
        this->head->prev = prev;
    }
    if (this->tail == nullptr) {
        this->tail = prev;
    }
    this->head = prev;

    this->_size++;
}

void List::insert(Node* pos, int value) {
    Node* cur = this->head;
    while (cur != nullptr) {
        if (cur != pos) {
            cur = cur->next;
            continue;
        }

        Node* next = cur->next;
        Node* node = new Node(cur, next, value);
        cur->next = node;
        if (next == nullptr) {
            this->tail = cur->next;
        } else {
            next->prev = cur->next;
        }

        this->_size++;

        return;
    }

    throw std::runtime_error("Incorrect position!");
}

void List::pop_front() {
    if (this->head == nullptr) {
        throw std::runtime_error("Deleting in empty list");
    }

    Node* head = this->head;
    Node* tail = this->tail;
    if (head == tail) {
        this->tail = nullptr;
        this->head = nullptr; 
    } else {
        this->head = head->next;
        if (head->next != nullptr) {
            head->next->prev = nullptr;
        }
    }
    free(head);

    this->_size--;
}

void List::pop_back() {
    if (this->tail == nullptr) {
        throw std::runtime_error("Deleting in empty list");
    }

    Node* head = this->head;
    Node* tail = this->tail;
    if (head == tail) {
        this->tail = nullptr;
        this->head = nullptr; 
    } else {
        this->tail = tail->prev;
        if (tail->prev != nullptr) {
            tail->prev->next = nullptr;
        }
    }
    free(tail);

    this->_size--;
}


void List::erase(Node* pos) {
    Node* cur = this->head;
    while (cur != nullptr) {
        if (cur != pos) {
            cur = cur->next;
            continue;
        }

        Node* next = cur->next;
        Node* prev = cur->prev;

        free(cur);

        if (next == nullptr) {
            this->tail = prev;
        } else {
            next->prev = prev;
        }
        if (prev == nullptr) {
           this->head = next;
        } else {
            prev->next = next;
        }

        this->_size--;

        return;
    }

    throw std::runtime_error("Incorrect position!");
}

void List::clear() {
    Node* cur = this->head;
    while (cur != nullptr) {
        Node* next = cur->next;
        free(cur);
        cur = next;
    }

    this->head = nullptr;
    this->tail = nullptr;
    this->_size = 0;
}

void List::reverse() {
    Node* cur = this->head;
    while (cur != nullptr) {
        Node* next = cur->next;
        std::swap(cur->prev, cur->next);
        cur = next;
    }

    std::swap(this->head, this->tail);
}

void List::remove_duplicates() {
    std::unordered_map<int, int> seen;

    Node* cur = this->head;
    while (cur != nullptr) {
        int value = cur->value;
        Node* next = cur->next;
        Node* prev = cur->prev;

        if (seen[value]) {
            free(cur);

            if (next == nullptr) {
                this->tail = prev;
            } else {
                next->prev = prev;
            }
            if (prev == nullptr) {
            this->head = next;
            } else {
                prev->next = next;
            }

            this->_size--;
        }
        
        cur = next;
        seen[value] = true;
    }
}

void List::replace(int old_value, int new_value) {
    Node* cur = this->head;
    while (cur != nullptr) {
        if (cur->value == old_value) {
            cur->value = new_value;
        }

        cur = cur->next;
    }
}

void List::merge(const List& other) {
    Node* cur = other.head;

    while (cur != nullptr) {
        this->push_back(cur->value);
        cur = cur->next;
    }
}

bool List::check_cycle() const {
    if (this->head == nullptr) {
        return false;
    }

    Node* fast = this->head;
    Node* slow = this->head;

    while (1){
        slow = slow->next;
        fast = fast->next;

        if (fast == nullptr) {
            return false;
        }

        fast = fast->next;

        if (fast == nullptr) {
            return false;
        }

        if (fast == slow) {
            return true;
        }
    }

    return false;
}

size_t List::size() const {
    return this->_size;
}

bool List::empty() const{
    return (this->_size == 0);
}

void List::copy(const List& other) {
    this->clear();

    Node* cur = other.head;

    while (cur != nullptr) {
        this->push_back(cur->value);
        cur = cur->next;
    }
}
