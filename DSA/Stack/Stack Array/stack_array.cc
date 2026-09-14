#include <iostream>
#include <sstream>
#include <string>
#include "logger.h"
#include "stack_array.h"


namespace {

    constexpr const char* LOG_FILE = "stack_array.log";
    constexpr int STACK_CAPACITY = 8;

    std::string stack_to_string(const ArrayStack* stack) {
        std::ostringstream output;
        output << "Array Stack (bottom -> top): ";

        if (is_empty(stack)) {
            output << "empty";
            return output.str();
        }

        for (int index = 0; index <= stack->top; ++index) {
            output << stack->items[index];
            if (index != stack->top) {
                output << " -> ";
            }
        }

        output << " <- top [size=" << stack_size(stack)
               << ", capacity=" << stack->capacity << "]";
        return output.str();
    }

}  // namespace

/*
    Basic DSA Concept : Stack using a fixed-size array
        1. The capacity is fixed at creation, so memory is allocated only once
        2. push() writes at index top + 1 and fails when the stack is full
        3. pop() reads index top and fails when the stack is empty
        4. Every operation except search and traversal is O(1)
*/

// Allocate the stack object and its storage in one call.
// Time: O(1). Auxiliary space: O(capacity).
ArrayStack* create_stack(int capacity) {
    if (capacity <= 0) {
        return nullptr;
    }

    ArrayStack* stack = new ArrayStack();
    stack->items = new int[static_cast<unsigned int>(capacity)]();
    stack->capacity = capacity;
    stack->top = -1;
    return stack;
}

// push(): store data at the next free slot.
// Time: O(1). Auxiliary space: O(1).
bool push_element(ArrayStack* stack, int data) {
    // Overflow is a hard failure because the array never grows.
    if (stack == nullptr || is_full(stack)) {
        return false;
    }

    stack->items[++stack->top] = data;
    return true;
}

// pop(): remove the top element.
// Time: O(1). Auxiliary space: O(1).
bool pop_element(ArrayStack* stack, int* popped_data) {
    if (is_empty(stack)) {
        return false;
    }

    if (popped_data != nullptr) {
        *popped_data = stack->items[stack->top];
    }

    // The slot is left untouched; lowering top makes it unreachable.
    --stack->top;
    return true;
}

// top(): read the top element without removing it.
// Time: O(1). Auxiliary space: O(1).
bool peek_element(const ArrayStack* stack, int* top_data) {
    if (is_empty(stack)) {
        return false;
    }

    if (top_data != nullptr) {
        *top_data = stack->items[stack->top];
    }

    return true;
}

// A nullptr stack is treated as empty so callers need no extra guard.
// Time: O(1). Auxiliary space: O(1).
bool is_empty(const ArrayStack* stack) {
    return stack == nullptr || stack->top < 0;
}

// Time: O(1). Auxiliary space: O(1).
bool is_full(const ArrayStack* stack) {
    return stack != nullptr && stack->top == stack->capacity - 1;
}

// Time: O(1). Auxiliary space: O(1).
int stack_size(const ArrayStack* stack) {
    if (stack == nullptr) {
        return 0;
    }
    return stack->top + 1;
}

// Scan the used part of the array from bottom to top.
// Time: O(n) worst case, including the not-found case.
// Auxiliary space: O(1).
bool search_element(const ArrayStack* stack, int data) {
    if (is_empty(stack)) {
        return false;
    }

    for (int index = 0; index <= stack->top; ++index) {
        if (stack->items[index] == data) {
            return true;
        }
    }

    // Element not found
    return false;
}

// Print every stored element.
// Time: O(n). Auxiliary space: O(1), excluding output-stream storage.
void traverse_stack(const ArrayStack* stack) {
    std::cout << stack_to_string(stack) << std::endl;
}

// Release the storage and the stack object.
// Time: O(1). Auxiliary space: O(1).
void destroy_stack(ArrayStack* stack) {
    if (stack == nullptr) {
        return;
    }

    delete[] stack->items;
    delete stack;
}



int main() {
    common::Logger logger(LOG_FILE);
    if (!logger.is_open()) {
        logger.fatal("Unable to open log file: " + std::string(LOG_FILE));
    }

    logger.info("Array stack program started");

    ArrayStack* stack = create_stack(STACK_CAPACITY);
    if (stack == nullptr) {
        logger.fatal("Unable to allocate a stack of capacity ", STACK_CAPACITY);
    }

    traverse_stack(stack);
    logger.info("Initial stack state");
    logger.info(stack_to_string(stack));

    // push() until the fixed capacity is reached.
    for (int data = 100; data < 100 + STACK_CAPACITY; ++data) {
        const bool pushed = push_element(stack, data);
        logger.info("Pushed data=", data, " result=", pushed ? "ok" : "full");
    }

    std::cout << "After filling the stack:" << std::endl;
    traverse_stack(stack);
    logger.info("After filling the stack");
    logger.info(stack_to_string(stack));

    // Overflow: the array cannot grow, so the extra push is rejected.
    const bool overflow_push = push_element(stack, 999);
    std::cout << "Push on full stack: " << (overflow_push ? "ok" : "rejected") << std::endl;
    logger.info("Push on full stack result=", overflow_push ? "ok" : "rejected");

    int top_data = 0;
    if (peek_element(stack, &top_data)) {
        std::cout << "Top: " << top_data << std::endl;
        logger.info("Top value=", top_data);
    }

    const bool found_105 = search_element(stack, 105);
    const bool found_999 = search_element(stack, 999);
    std::cout << "Search 105: " << (found_105 ? "found" : "not found") << std::endl;
    std::cout << "Search 999: " << (found_999 ? "found" : "not found") << std::endl;
    logger.info("Search 105 result=", found_105 ? "found" : "not found");
    logger.info("Search 999 result=", found_999 ? "found" : "not found");

    // pop(): LIFO order removes the most recently pushed values first.
    for (int count = 0; count < 3; ++count) {
        int popped_data = 0;
        if (pop_element(stack, &popped_data)) {
            std::cout << "Popped: " << popped_data << std::endl;
            logger.info("Popped data=", popped_data);
        }
    }

    std::cout << "After popping 3 values:" << std::endl;
    traverse_stack(stack);
    logger.info("After popping 3 values");
    logger.info(stack_to_string(stack));

    // Reusing freed slots proves the capacity is not consumed permanently.
    push_element(stack, 200);
    std::cout << "After pushing 200 into a reused slot:" << std::endl;
    traverse_stack(stack);
    logger.info("After pushing 200 into a reused slot");
    logger.info(stack_to_string(stack));

    while (pop_element(stack, nullptr)) {
        // Drain the stack to show the underflow behaviour.
    }

    std::cout << "After draining the stack:" << std::endl;
    traverse_stack(stack);
    logger.info("After draining the stack");
    logger.info(stack_to_string(stack));

    const bool underflow_pop = pop_element(stack, nullptr);
    std::cout << "Pop on empty stack: " << (underflow_pop ? "ok" : "rejected") << std::endl;
    logger.info("Pop on empty stack result=", underflow_pop ? "ok" : "rejected");

    destroy_stack(stack);
    stack = nullptr;

    logger.info("Array stack program completed successfully");

}
