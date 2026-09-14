#pragma once

/*
    Stack : LIFO container built on a doubly linked list, so it grows on demand
    and has no fixed capacity. The last node is the top of the stack:
        - push() is insert_node(), which appends a node at the end.
        - pop()  is delete_node(), which removes the last node.
*/

// Doubly linked list node.
class Node {
public:
    // head points to the previous node and tail points to the next node.
    // For the bottom node head is nullptr. For the top node tail is nullptr.

    Node* head = nullptr;
    Node* tail = nullptr;

    // Value stored in this node.
    int data = 0;
};

// push(): appends a new node containing data at the top of the stack.
// Creates and returns the first node when node is nullptr.
Node* insert_node(Node* node, int data);

// pop(): deletes the last node, which is the top of the stack, and returns the
// updated bottom node. Writes the removed value to popped_data when it is not
// nullptr. Returns nullptr once the final node has been removed.
Node* delete_node(Node* node, int* popped_data);

// top(): copies the value of the last node into top_data without removing it.
// Returns false when the stack is empty.
bool peek_node(Node* node, int* top_data);

// Returns true when data is present in the stack; otherwise returns false.
// A nullptr node represents an empty stack.
bool search_node(Node* node, int data);

// Prints every value from the bottom node to the top node.
void traverse_list(Node* node);

// Returns the number of nodes in the stack.
int stack_size(Node* node);

// Deletes every node in the stack.
void clear_list(Node* node);
