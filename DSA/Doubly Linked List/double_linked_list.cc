#include <iostream>
#include <string>
#include "logger.h"
#include "double_linked_list.h"


namespace {

    constexpr const char* LOG_FILE = "double_linked_list.log";

}  // namespace

/*
    Basic DSA Concept : Doubly Linked List
        1. Node creation or insertion
        2. Forward traversal
        3. Node search
        4. Node deletion with previous and next link updates
*/

// Insert a node at the end of the list starting at node.
// Time: O(n), because the list may be traversed to find the last node.
// Auxiliary space: O(1), excluding the newly allocated node.
Node* insert_node(Node* node, int data) {
    // If list is empty then create the first entry.
    if (node == nullptr) {
        Node* new_entry = new Node();
        new_entry->head = nullptr;
        new_entry->tail = nullptr;
        new_entry->data = data;
        return new_entry;
    }

    Node* new_entry = node;

    // Worst-case traversal visits every existing node: O(n).
    while (new_entry->tail != nullptr) {
        new_entry = new_entry->tail;
    }

    // Link the new node after the current last node.
    new_entry->tail = new Node();
    new_entry->tail->head = new_entry;
    new_entry->tail->data = data;
    return node;
}

// Delete the first node with the requested data and return the updated head.
// Time: O(n) overall. search_node() may scan n nodes, followed by another scan
// of at most n nodes to find and relink the matching node.
// Auxiliary space: O(1).
Node* delete_node(Node* node, int data) {
    // Return unchanged when the list is empty or the value does not exist.
    if (!search_node(node, data)) {
        return node;
    }

    Node* current = node;

    // Move forward until the matching node is found.
    while (current != nullptr && current->data != data) {
        current = current->tail;
    }

    // Relink the previous node, or move the list head when deleting first node.
    if (current->head != nullptr) {
        current->head->tail = current->tail;
    } else {
        node = current->tail;
    }

    // Relink the next node when the deleted node is not the last node.
    if (current->tail != nullptr) {
        current->tail->head = current->head;
    }

    delete current;
    return node;
}



// Search a node in the doubly linked list using forward traversal.
// Time: O(n) worst case, including the not-found case.
// Auxiliary space: O(1).
bool search_node(Node* node, int data) {

    // A nullptr starting node means the list is empty.
    if (node == nullptr) {
        return false;
    }

    // The loop visits each node at most once: O(n).
    Node* current = node;
    while (current != nullptr) {
        if (current->data == data) {
            return true;
        }
        current = current->tail;
    }

    // Element not found
    return false;
}

// Traverse forward and print each node value.
// Time: O(n), because every node is visited once.
// Auxiliary space: O(1), excluding output-stream storage.
void traverse_list(Node* head) {
    std::cout << "Doubly Linked List: ";

    Node* current = head;
    // Each iteration advances exactly one node: O(n) total.
    while (current != nullptr) {
        std::cout << current->data;
        if (current->tail != nullptr) {
            std::cout << " -> ";
        }
        current = current->tail;
    }

    std::cout << " -> nullptr" << std::endl;
}



int main() {
    common::Logger logger(LOG_FILE);
    if (!logger.is_open()) {
        logger.fatal("Unable to open log file: " + std::string(LOG_FILE));
    }

    logger.info("Linked-list program started");

    Node* head = nullptr;

    // Build the list from an empty starting pointer.
    for (int data = 100; data <= 110; ++data) {
        head = insert_node(head, data);
        logger.info("Inserted node with data=", data);
    }

    std::cout << "After inserting 11 nodes:" << std::endl;
    traverse_list(head);

    const bool found_105 = search_node(head, 105);
    const bool found_999 = search_node(head, 999);
    std::cout << "Search 105: " << (found_105 ? "found" : "not found") << std::endl;
    std::cout << "Search 999: " << (found_999 ? "found" : "not found") << std::endl;
    logger.info("Search 105 result=", found_105 ? "found" : "not found");
    logger.info("Search 999 result=", found_999 ? "found" : "not found");

    head = delete_node(head, 100);
    std::cout << "After deleting head node 100:" << std::endl;
    traverse_list(head);

    head = delete_node(head, 105);
    std::cout << "After deleting middle node 105:" << std::endl;
    traverse_list(head);

    head = delete_node(head, 110);
    std::cout << "After deleting tail node 110:" << std::endl;
    traverse_list(head);

    head = delete_node(head, 999);
    std::cout << "After trying to delete missing node 999:" << std::endl;
    traverse_list(head);
    logger.info("Deleted test nodes with data=100, 105, and 110");

    // Each allocated node is deleted once: O(n) time and O(1) auxiliary space.
    while (head != nullptr) {
        Node* next = head->tail;
        delete head;
        head = next;
    }

    logger.info("Linked-list program completed successfully");

}




























































