#ifndef QUEUE
#define QUEUE

#include <vector>
#include <utility>


namespace queue {

class Stack {
private:
    std::vector<std::pair<int, int>> internal;
public:
    bool IsEmpty();
    int Size();
    void Push(int);
    int Pop();
    int Min();
    int& First();
    int& Last();

    Stack();
    ~Stack() = default;
};

class Queue {
private:
    Stack pushStack;
    Stack popStack;
public:
    bool IsEmpty();
    int Size();
    void Push(int);
    int Pop();
    int Min();
    int& First();
    int& Last();
    
    Queue();
    ~Queue() = default;
};

}

#endif