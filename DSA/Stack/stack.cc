#include <iostream>
#include <sstream>
#include <string>
#include "logger.h"
#include "stack.h"


namespace {

    constexpr const char* LOG_FILE = "stack.log";

    std::string stack_to_string(Node* node) {
        std::ostringstream output;
        output << "Stack (bottom -> top): ";

        if (node == nullptr) {
            output << "empty";
            return output.str();
        }

        Node* current = node;
        while (current != nullptr) {
            output << current->data;
            if (current->tail != nullptr) {
                output << " -> ";
            }
            current = current->tail;
        }

        output << " <- top";
        return output.str();
    }

}  // namespace

/*
    Basic DSA Concept : Stack using a doubly linked list
        1. push() maps to insert_node(), appending at the end of the list
        2. pop() maps to delete_node(), removing the last node
        3. top() maps to peek_node(), reading the last node
        4. LIFO order: the node inserted last is the node removed first
*/

// push(): insert a node at the top of the stack, i.e. the end of the list.
// Time: O(n), because the list is traversed to find the last node.
// Auxiliary space: O(1), excluding the newly allocated node.
Node* insert_node(Node* node, int data) {
    // Empty stack: the new node becomes the bottom and the top at once.
    if (node == nullptr) {
        Node* new_entry = new Node();
        new_entry->data = data;
        return new_entry;
    }

    Node* last = node;

    // Worst-case traversal visits every existing node: O(n).
    while (last->tail != nullptr) {
        last = last->tail;
    }

    Node* new_entry = new Node();
    new_entry->data = data;
    new_entry->head = last;
    last->tail = new_entry;

    // The bottom node is unchanged, so the same pointer is returned.
    return node;
}

// pop(): delete the last node and return the updated bottom node.
// Time: O(n), because the list is traversed to find the last node.
// Auxiliary space: O(1).
Node* delete_node(Node* node, int* popped_data) {
    // Nothing to remove from an empty stack.
    if (node == nullptr) {
        return nullptr;
    }

    Node* last = node;
    while (last->tail != nullptr) {
        last = last->tail;
    }

    if (popped_data != nullptr) {
        *popped_data = last->data;
    }

    // The only node is being removed, so the stack becomes empty.
    if (last->head == nullptr) {
        delete last;
        return nullptr;
    }

    // Detach the top node so the new last node terminates the list.
    last->head->tail = nullptr;
    delete last;
    return node;
}

// top(): read the value at the top of the stack without removing it.
// Time: O(n). Auxiliary space: O(1).
bool peek_node(Node* node, int* top_data) {
    if (node == nullptr) {
        return false;
    }

    Node* last = node;
    while (last->tail != nullptr) {
        last = last->tail;
    }

    if (top_data != nullptr) {
        *top_data = last->data;
    }

    return true;
}

// Search a value using forward traversal from the bottom node.
// Time: O(n) worst case, including the not-found case.
// Auxiliary space: O(1).
bool search_node(Node* node, int data) {
    // A nullptr starting node means the stack is empty.
    if (node == nullptr) {
        return false;
    }

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
void traverse_list(Node* node) {
    std::cout << stack_to_string(node) << std::endl;
}

// Count the nodes from bottom to top.
// Time: O(n). Auxiliary space: O(1).
int stack_size(Node* node) {
    int size = 0;
    Node* current = node;
    while (current != nullptr) {
        ++size;
        current = current->tail;
    }
    return size;
}

// Release every node in the stack.
// Time: O(n). Auxiliary space: O(1).
void clear_list(Node* node) {
    while (node != nullptr) {
        Node* next = node->tail;
        delete node;
        node = next;
    }
}



int main() {
    common::Logger logger(LOG_FILE);
    if (!logger.is_open()) {
        logger.fatal("Unable to open log file: " + std::string(LOG_FILE));
    }

    logger.info("Linked-list stack program started");

    Node* bottom = nullptr;

    traverse_list(bottom);
    logger.info("Initial stack state");
    logger.info(stack_to_string(bottom));

    // push(): the stack grows on demand, one node per call.
    for (int data = 100; data <= 110; ++data) {
        bottom = insert_node(bottom, data);
        logger.info("Pushed node with data=", data);
    }

    std::cout << "After pushing 11 values:" << std::endl;
    traverse_list(bottom);
    std::cout << "Size: " << stack_size(bottom) << std::endl;
    logger.info("After pushing 11 values");
    logger.info(stack_to_string(bottom));

    int top_data = 0;
    if (peek_node(bottom, &top_data)) {
        std::cout << "Top: " << top_data << std::endl;
        logger.info("Top value=", top_data);
    }

    const bool found_105 = search_node(bottom, 105);
    const bool found_999 = search_node(bottom, 999);
    std::cout << "Search 105: " << (found_105 ? "found" : "not found") << std::endl;
    std::cout << "Search 999: " << (found_999 ? "found" : "not found") << std::endl;
    logger.info("Search 105 result=", found_105 ? "found" : "not found");
    logger.info("Search 999 result=", found_999 ? "found" : "not found");

    // pop(): LIFO order removes 110, then 109, then 108.
    for (int count = 0; count < 3; ++count) {
        int popped_data = 0;
        bottom = delete_node(bottom, &popped_data);
        std::cout << "Popped: " << popped_data << std::endl;
        logger.info("Popped node with data=", popped_data);
    }

    std::cout << "After popping 3 values:" << std::endl;
    traverse_list(bottom);
    std::cout << "Size: " << stack_size(bottom) << std::endl;
    logger.info("After popping 3 values");
    logger.info(stack_to_string(bottom));

    // Drain the stack to show the empty-stack behaviour.
    while (bottom != nullptr) {
        bottom = delete_node(bottom, nullptr);
    }

    std::cout << "After draining the stack:" << std::endl;
    traverse_list(bottom);
    logger.info("After draining the stack");
    logger.info(stack_to_string(bottom));

    // pop() and top() on an empty stack are safe no-ops.
    bottom = delete_node(bottom, nullptr);
    const bool peek_empty = peek_node(bottom, &top_data);
    std::cout << "Peek on empty stack: " << (peek_empty ? "ok" : "failed") << std::endl;
    logger.info("Peek on empty stack result=", peek_empty ? "ok" : "failed");

    clear_list(bottom);
    bottom = nullptr;

    logger.info("Linked-list stack program completed successfully");

}
