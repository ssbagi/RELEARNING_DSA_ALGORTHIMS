#pragma once

/*
    Stack : LIFO container built on a fixed-size array. The capacity is decided
    once at creation and never changes, so push() fails when the stack is full.
        - top is the index of the element at the top of the stack.
        - top == -1 means the stack is empty.
        - top == capacity - 1 means the stack is full.
*/

class ArrayStack {
public:
    // Contiguous storage of exactly capacity elements.
    int* items = nullptr;

    // Number of slots allocated; fixed for the lifetime of the stack.
    int capacity = 0;

    // Index of the top element, or -1 when the stack is empty.
    int top = -1;
};

// Allocates a stack that can hold capacity elements.
// Returns nullptr when capacity is not positive or allocation is refused.
ArrayStack* create_stack(int capacity);

// push(): stores data at the next free slot.
// Returns false when the stack is full or the stack pointer is nullptr.
bool push_element(ArrayStack* stack, int data);

// pop(): removes the top element and writes it to popped_data when it is not
// nullptr. Returns false when the stack is empty.
bool pop_element(ArrayStack* stack, int* popped_data);

// top(): copies the top element into top_data without removing it.
// Returns false when the stack is empty.
bool peek_element(const ArrayStack* stack, int* top_data);

// Returns true when the stack holds no elements.
bool is_empty(const ArrayStack* stack);

// Returns true when the stack has reached its fixed capacity.
bool is_full(const ArrayStack* stack);

// Returns the number of elements currently stored.
int stack_size(const ArrayStack* stack);

// Returns true when data is present in the stack; otherwise returns false.
bool search_element(const ArrayStack* stack, int data);

// Prints every element from the bottom of the stack to the top.
void traverse_stack(const ArrayStack* stack);

// Releases the storage and the stack object itself.
void destroy_stack(ArrayStack* stack);
