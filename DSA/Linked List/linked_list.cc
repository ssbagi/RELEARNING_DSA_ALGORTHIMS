#include <iostream>
#include <string>
#include "logger.h"
#include "linked_list.h"

namespace {

    constexpr const char* LOG_FILE = "linked_list.log";

}  // namespace

/*
    Basic DSA Concept : Linked List 
        1. Node Creation or Addition.
        2. Node Traversal
        3. Node Deletion
        4. Node Search
*/

// Insert a node at the end of the list starting at head.
// Time: O(n), because the list may be traversed to find the tail.
// Auxiliary space: O(1), excluding the newly allocated node.
void insert_node(Node* head, int data) {
    if (head == nullptr) {
        return;
    }

    Node* tail = head;

    // Worst-case traversal visits every existing node: O(n).
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    // Last Node found now insert the things into this node.
    tail->next = new Node();
    tail->next->data = data;
}

// Delete the first node with the requested data and return the updated head.
// Time: O(n) overall. search_node() may scan n nodes, followed by another
// scan of at most n nodes to relink the matching node.
// Auxiliary space: O(1).
Node* delete_node(Node* head, int data) {
    //Traverse and check whether the given data exists in the Node or not.
    if (!search_node(head, data)) {
        return head;
    }

    // head : First Node
    if (head->data == data) {
        Node* new_head = head->next;
        delete head;
        return new_head;
    }

    Node* previous = head;
    Node* current = head->next;

    // Traversal like a two pointer method
    while (current != nullptr && current->data != data) {
        // Keep on update the previous and current pointer and stuff.
        previous = current;
        current = current->next;
    }

    // Found that current node is the matched or required node.
    previous->next = current->next;
    delete current;
    return head;
}



// Search a node in the linked list.
// Time: O(n) worst case, including the not-found case.
// Auxiliary space: O(1).
bool search_node(Node* node, int data) {

    // The LinkedList has No Nodes : It is Empty
    if (node == nullptr) {
        return false;
    }

    // The loop visits each node at most once: O(n).
    Node* tail = node;
    while (tail != nullptr) {
        if (tail->data == data) {
            return true;
        }
        tail = tail->next;
    }

    // Element not found
    return false;
}

// Traverse the list and print each node value.
// Time: O(n), because every node is visited once.
// Auxiliary space: O(1), excluding output-stream storage.
void traverse_list(Node* head) {
    std::cout << "Linked List: ";

    Node* current = head;
    // Each iteration advances exactly one node: O(n) total.
    while (current != nullptr) {
        std::cout << current->data;
        if (current->next != nullptr) {
            std::cout << " -> ";
        }
        current = current->next;
    }

    std::cout << " -> nullptr" << std::endl;
}



int main() {
    common::Logger logger(LOG_FILE);
    if (!logger.is_open()) {
        logger.fatal("Unable to open log file: " + std::string(LOG_FILE));
    }

    logger.info("Linked-list program started");

    Node* head = new Node();
    head->data = 100;
    logger.info("Created head node with data=", head->data);

    // Each insert_node() scans the current list, so repeated tail insertion
    // makes this demo loop O(n^2) overall.
    for (int data = 101; data <= 110; ++data) {
        insert_node(head, data);
        logger.info("Inserted node with data=", data);
    }

    std::cout << "After inserting 10 nodes:" << std::endl;
    traverse_list(head);

    const bool found_105 = search_node(head, 105);
    const bool found_999 = search_node(head, 999);
    std::cout << "Search 105: " << (found_105 ? "found" : "not found") << std::endl;
    std::cout << "Search 999: " << (found_999 ? "found" : "not found") << std::endl;
    logger.info("Search 105 result=", found_105 ? "found" : "not found");
    logger.info("Search 999 result=", found_999 ? "found" : "not found");

    head = delete_node(head, 103);
    head = delete_node(head, 108);
    logger.info("Deleted nodes with data=103 and data=108");

    std::cout << "After deleting 103 and 108:" << std::endl;
    traverse_list(head);

    // Each allocated node is deleted once: O(n) time and O(1) auxiliary space.
    while (head != nullptr) {
        Node* next = head->next;
        delete head;
        head = next;
    }

    logger.info("Linked-list program completed successfully");

}


























































