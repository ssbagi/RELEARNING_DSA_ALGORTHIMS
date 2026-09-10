#pragma once

// Doubly linked list node.
class Node {
public:
    // In this implementation, head points to the previous node and tail points
    // to the next node. For the first node, head is nullptr. For the last node,
    // tail is nullptr.

    Node* head = nullptr;
    Node* tail = nullptr;

    // Value stored in this node.
    int data = 0;
};

// Appends a new node containing data to the end of the list.
// Creates and returns the first node when node is nullptr.
Node* insert_node(Node* node, int data);

// Returns true when data is present in the list; otherwise returns false.
// A nullptr node represents an empty list.
bool search_node(Node* node, int data);

// Prints every value in the list from first node to last node.
void traverse_list(Node* node);

// Deletes the first node containing data and returns the updated list head.
// Returns the original head when data is not found or the list is empty.
// The caller owns the list nodes and must release the remaining nodes.
Node* delete_node(Node* node, int data);
