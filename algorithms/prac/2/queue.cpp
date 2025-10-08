#include <vector>
#include <utility>
#include <cmath>
#include <stdexcept>

#include "queue.hpp"

namespace queue {

Stack::Stack() {
    this->internal = std::vector<std::pair<int,int>>();
}

bool Stack::IsEmpty() {
    return this->internal.empty();
}

int Stack::Size() {
    return this->internal.size();
}

void Stack::Push(int a) {
    if (this->internal.empty()) {
        this->internal.push_back({a, a});
        return;
    }

    auto top = this->internal.back();
    this->internal.push_back({a, std::min(a, top.second)});
}

int Stack::Pop() {
    if (this->internal.empty()){
        throw std::underflow_error("stack underflow");
    }

    auto top = this->internal.back();
    this->internal.pop_back();
    
    return top.first;
}

int Stack::Min() {
    if (this->internal.empty()){
        throw std::underflow_error("stack underflow");
    }

    auto top = this->internal.back();

    return top.second;
}

int& Stack::First() {
    if (this->internal.empty()){
        throw std::underflow_error("stack underflow");
    }

    return this->internal.back().first;
}

int& Stack::Last() {
    if (this->internal.empty()){
        throw std::underflow_error("stack underflow");
    }

    return this->internal.front().first;
}

Queue::Queue() {
    this->pushStack = Stack();
    this->popStack = Stack();
}

bool Queue::IsEmpty() {
    return this->pushStack.IsEmpty() && this->popStack.IsEmpty();
}

int Queue::Size() {
    return this->pushStack.Size() + this->popStack.Size();
}

void Queue::Push(int a) {
    this->pushStack.Push(a);
}

int Queue::Pop() {
    if (!this->popStack.IsEmpty()) {
        return this->popStack.Pop();
    }
    
    while (!this->pushStack.IsEmpty()) {
        this->popStack.Push(this->pushStack.Pop());
    }

    return this->popStack.Pop();
}

int Queue::Min() {
    if (this->popStack.IsEmpty()) {
        return this->pushStack.Min();
    }
    if (this->pushStack.IsEmpty()) {
        return this->popStack.Min();
    }

    return std::min(this->pushStack.Min(), this->popStack.Min());
}

int& Queue::First() {
    if (!this->popStack.IsEmpty()) {
        return this->popStack.First();
    }

    return this->pushStack.Last();
}

int& Queue::Last() {
    if (!this->pushStack.IsEmpty()) {
        return this->pushStack.First();
    }

    return this->popStack.Last();
}

}