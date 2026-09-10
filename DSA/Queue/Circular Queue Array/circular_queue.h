#pragma once

#include <stdexcept>
#include <string>

class CircularQueue {
public:
    explicit CircularQueue(int capacity);
    ~CircularQueue();

    bool enqueue(int value);
    bool dequeue();

    bool is_empty() const;
    bool is_full() const;
    int size() const;

    int front() const;
    int rear() const;
    std::string to_string() const;
    void traverse() const;

private:
    int* data_ = nullptr;
    int capacity_ = 0;
    int front_ = 0;
    int rear_ = -1;
    int count_ = 0;
};
