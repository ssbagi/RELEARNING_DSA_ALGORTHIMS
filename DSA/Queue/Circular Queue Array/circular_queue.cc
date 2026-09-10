#include <iostream>
#include <stdexcept>
#include <string>
#include "logger.h"
#include "circular_queue.h"

namespace {

constexpr const char* LOG_FILE = "circular_queue.log";

}  // namespace

CircularQueue::CircularQueue(int capacity) {
    if (capacity <= 0) {
        throw std::invalid_argument("Queue capacity must be greater than zero.");
    }

    capacity_ = capacity;
    data_ = new int[capacity_];
    front_ = 0;
    rear_ = -1;
    count_ = 0;
}

CircularQueue::~CircularQueue() {
    delete[] data_;
    data_ = nullptr;
    capacity_ = 0;
    front_ = 0;
    rear_ = -1;
    count_ = 0;
}

bool CircularQueue::enqueue(int value) {
    if (is_full()) {
        return false;
    }

    rear_ = (rear_ + 1) % capacity_;
    data_[rear_] = value;
    ++count_;
    return true;
}

bool CircularQueue::dequeue() {
    if (is_empty()) {
        return false;
    }

    front_ = (front_ + 1) % capacity_;
    --count_;

    if (count_ == 0) {
        front_ = 0;
        rear_ = -1;
    }

    return true;
}

bool CircularQueue::is_empty() const {
    return count_ == 0;
}

bool CircularQueue::is_full() const {
    return count_ == capacity_;
}

int CircularQueue::size() const {
    return count_;
}

int CircularQueue::front() const {
    if (is_empty()) {
        throw std::out_of_range("CircularQueue is empty.");
    }

    return data_[front_];
}

int CircularQueue::rear() const {
    if (is_empty()) {
        throw std::out_of_range("CircularQueue is empty.");
    }

    return data_[rear_];
}

std::string CircularQueue::to_string() const {
    std::string output = "Circular Queue: ";

    if (is_empty()) {
        return output + "empty";
    }

    for (int index = 0; index < count_; ++index) {
        const int position = (front_ + index) % capacity_;
        output += std::to_string(data_[position]);

        if (index + 1 < count_) {
            output += " -> ";
        }
    }

    return output;
}

void CircularQueue::traverse() const {
    std::cout << to_string() << std::endl;
}

int main() {
    common::Logger logger(LOG_FILE);
    if (!logger.is_open()) {
        logger.fatal("Unable to open log file: " + std::string(LOG_FILE));
    }

    logger.info("Circular queue array program started");

    CircularQueue queue(5);

    std::cout << "Initial queue state:" << std::endl;
    queue.traverse();
    logger.info("Initial queue state");
    logger.info(queue.to_string());

    for (int value : {10, 20, 30, 40}) {
        const bool enqueued = queue.enqueue(value);
        std::cout << "Enqueue " << value << ": " << (enqueued ? "success" : "full") << std::endl;
        logger.info("Enqueue value=", value, " result=", enqueued ? "success" : "full");
    }

    std::cout << "After inserting 4 elements:" << std::endl;
    queue.traverse();
    logger.info("After inserting 4 elements");
    logger.info(queue.to_string());

    std::cout << "Front: " << queue.front() << ", Rear: " << queue.rear() << std::endl;
    logger.info("Front=", queue.front(), " Rear=", queue.rear());

    std::cout << "Dequeue: " << (queue.dequeue() ? "success" : "failed") << std::endl;
    logger.info("Dequeued first element");
    queue.traverse();

    std::cout << "Dequeue: " << (queue.dequeue() ? "success" : "failed") << std::endl;
    logger.info("Dequeued second element");
    queue.traverse();

    const bool enqueued_50 = queue.enqueue(50);
    const bool enqueued_60 = queue.enqueue(60);
    const bool enqueued_70 = queue.enqueue(70);

    std::cout << "Enqueue 50: " << (enqueued_50 ? "success" : "full") << std::endl;
    std::cout << "Enqueue 60: " << (enqueued_60 ? "success" : "full") << std::endl;
    std::cout << "Enqueue 70: " << (enqueued_70 ? "success" : "full") << std::endl;
    logger.info("Enqueue 50 result=", enqueued_50 ? "success" : "full");
    logger.info("Enqueue 60 result=", enqueued_60 ? "success" : "full");
    logger.info("Enqueue 70 result=", enqueued_70 ? "success" : "full");

    std::cout << "Final queue state:" << std::endl;
    queue.traverse();
    logger.info("Final queue state");
    logger.info(queue.to_string());

    return 0;
}
