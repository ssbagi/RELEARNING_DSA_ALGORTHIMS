#pragma once

/*
    Circular queue : Using a doubly linked list that grows dynamically, no fixed capacity.
    The list is always closed: the last node's tail points back to the first node and the
    first node's head points back to the last node. A lone node links to itself both ways.
*/

class Node {
public:
    // head points to the previous node and tail points to the next node.
    // Neither link is ever nullptr once the node belongs to a list.

    Node* head = nullptr;
    Node* tail = nullptr;

    // Value stored in this node.
    int data = 0;
};

// Appends a new node containing data just before the start node and returns the start node.
// Creates and returns a self-linked node when node is nullptr.
Node* insert_node(Node* node, int data);

// Returns true when data is present in the list; otherwise returns false.
// A nullptr node represents an empty list.
bool search_node(Node* node, int data);

// Prints every value in the list starting at node and walking exactly one full loop.
void traverse_list(Node* node);

// Deletes the first node containing data and returns the updated start node.
// Returns the original start node when data is not found or the list is empty.
// Returns nullptr when the last remaining node is deleted.
Node* delete_node(Node* node, int data);

// Returns the number of nodes in the list.
int queue_size(Node* node);

// Deletes every node in the list.
void clear_list(Node* node);


