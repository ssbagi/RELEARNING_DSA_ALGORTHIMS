#pragma once

// A single node in a singly linked list.
class Node {
public:
    // Points to the next node, or nullptr for the last node.
    Node* next = nullptr;

    // Value stored in this node.
    int data = 0;
};

// Appends a new node containing data to the end of the list.
// Does nothing when head is nullptr.
void insert_node(Node* head, int data);

// Returns true when data is present in the list; otherwise returns false.
// A nullptr head represents an empty list.
bool search_node(Node* head, int data);

// Prints every value in the list from head to tail.
void traverse_list(Node* head);

// Deletes the first node containing data and returns the updated list head.
// Returns the original head when data is not found or the list is empty.
// The caller owns the list nodes and must release the remaining nodes.
Node* delete_node(Node* head, int data);
