#include <iostream>
#include <sstream>
#include <string>
#include "logger.h"
#include "circular_queue.h"


namespace {

    constexpr const char* LOG_FILE = "circular_queue.log";

    std::string queue_to_string(Node* head, int capacity) {
        std::ostringstream output;
        output << "Circular Queue: ";

        if (head == nullptr || capacity <= 0) {
            output << "nullptr";
            return output.str();
        }

        Node* current = head;
        int size = 0;

        while (current != nullptr && size < capacity) {
            output << current->data;

            current = current->tail;
            ++size;

            if (current != nullptr && size < capacity) {
                output << " -> ";
            }
        }

        if (current == nullptr) {
            output << " -> nullptr";
        } else {
            output << " -> ...";
        }

        return output.str();
    }

}  // namespace

// Insert a node at the end of the list starting at node.
// Time: O(n), because the list may be traversed to find the last node.
// Auxiliary space: O(1), excluding the newly allocated node.
Node* insert_node(Node* node, int data, int capacity) {
    /*
    Basic Circular Queue COncept only with short change :
        - The queue has a fixed capacity.
        - New nodes are only added if the current size is less than the capacity.
        - The size of the queue is tracked to enforce the capacity constraint.
        - The Tail will overflow to the initial node when the capacity is reached.
        - Increment tail pointer on insertion/addition of the entry in the circular queue.
        - Decrement head pointer on deletion/removal of the entry in the circular queue.
    */
    
    // Basic Sanity Checks
    if (capacity <= 0) {
        return node;  // Cannot insert into a queue with non-positive capacity.
    }

    // If list is empty then create the first entry.
    int size = 0;   // Initialize the size of the circular queue.
    if (node == nullptr) {
        Node* new_entry = new Node();
        ++size;                         // Increment the size of the circular queue.
        new_entry->head = nullptr;
        new_entry->tail = nullptr;
        new_entry->data = data;
        return new_entry;
    }

    Node* new_entry = node;
    // Calculate the current size of the circular queue.
    while (new_entry != nullptr && size < capacity) {
        ++size;
        new_entry = new_entry->tail;
    }

    // Reinitialize new_entry to the head.
    new_entry = node;
    Node* inserted_node = nullptr;

    // Worst-case traversal visits every existing node: O(n).
    while (new_entry->tail != nullptr && size < capacity) {
        new_entry = new_entry->tail;
    }

    // Link the new node after the current last node.
    if (size < capacity) {
        new_entry->tail = new Node();
        new_entry->tail->head = new_entry;
        new_entry->tail->data = data;
        inserted_node = new_entry->tail;
        ++size;
    }

    // Link the final node back to the initial node when the queue reaches capacity.
    if (inserted_node != nullptr && size == capacity) {
        inserted_node->tail = node; // Reinitialize the tail to point back to the head, completing the circular link.
        node->head = inserted_node;
        std::cout << "Queue has reached its capacity." << std::endl;
    }

    return node;
}

// Delete the first node with the requested data and return the updated head.
// Time: O(n), because at most capacity nodes are scanned.
// Auxiliary space: O(1).
Node* delete_node(Node* node, int data, int capacity) {
    // Return unchanged when the list is empty or capacity is invalid.
    if (node == nullptr || capacity <= 0) {
        return node;
    }

    Node* current = node;
    int size = 0;

    // Move forward until the matching node is found, bounded for circular lists.
    while (current != nullptr && size < capacity && current->data != data) {
        current = current->tail;
        ++size;
    }

    // Return unchanged when the value does not exist within the queue capacity.
    if (current == nullptr || size == capacity) {
        return node;
    }

    // Delete the only node in a non-circular list.
    if (current->head == nullptr && current->tail == nullptr) {
        delete current;
        return nullptr;
    }

    // Delete the only node in a circular list.
    if (current->head == current && current->tail == current) {
        delete current;
        return nullptr;
    }

    // Move the returned start node forward when deleting the current start node.
    if (current == node) {
        node = current->tail;
    }

    // Relink the previous node when one exists.
    if (current->head != nullptr) {
        current->head->tail = current->tail;
    }

    // Relink the next node when one exists.
    if (current->tail != nullptr) {
        current->tail->head = current->head;
    }

    delete current;
    return node;
}



// Search a node in the doubly linked list using forward traversal.
// Time: O(n) worst case, including the not-found case.
// Auxiliary space: O(1)
bool search_node(Node* node, int data, int capacity) {

    // A nullptr starting node means the list is empty.
    int size = 0;   // Initialize the size of the circular queue.
    if (node == nullptr || capacity <= 0) {
        return false;
    }
    /*
        Problem : 
            Let's say I called search_node with some in between node lets say 3rd/4th node is passed to the function call.
            So, there will be no nullptr at all since it is a circular buffer. 
            Since made size = 0, the loop will terminate after visiting 'capacity' number of nodes at most.
            Since, the list is circular, we need to limit the number of nodes we visit to the capacity to avoid an infinite loop.
    */
    // The loop visits each node at most once: O(n).
    Node* current = node;
    while (current != nullptr && size < capacity) {
        if (current->data == data) {
            return true;
        }
        current = current->tail;
        ++size;   // Increment the size of the circular queue.
    }

    // Element not found
    return false;
}

// Traverse forward and print each node value.
// Time: O(n), because every node is visited once.
// Auxiliary space: O(1), excluding output-stream storage.
void traverse_list(Node* head, int capacity) {
    std::cout << queue_to_string(head, capacity) << std::endl;
}



int main() {
    common::Logger logger(LOG_FILE);
    if (!logger.is_open()) {
        logger.fatal("Unable to open log file: " + std::string(LOG_FILE));
    }

    logger.info("Circular queue program started");

    Node* head = nullptr;
    int size = 0;   // Initialize the size of the circular queue.
    int capacity = 11;   // Set the capacity of the circular queue.

    traverse_list(head, size);
    logger.info("Initial queue state");
    logger.info(queue_to_string(head, size));

    // Build the list from an empty starting pointer.
    for (int data = 100; data <= 110; ++data) {
        head = insert_node(head, data, capacity);
        ++size;   // Increment the size of the circular queue.
        logger.info("Inserted node with data=", data);
    }

    std::cout << "After inserting 11 nodes:" << std::endl;
    traverse_list(head, size);
    logger.info("After inserting 11 nodes");
    logger.info(queue_to_string(head, size));

    const bool found_105 = search_node(head, 105, size);
    const bool found_999 = search_node(head, 999, size);
    std::cout << "Search 105: " << (found_105 ? "found" : "not found") << std::endl;
    std::cout << "Search 999: " << (found_999 ? "found" : "not found") << std::endl;
    logger.info("Search 105 result=", found_105 ? "found" : "not found");
    logger.info("Search 999 result=", found_999 ? "found" : "not found");

    head = delete_node(head, 100, size);
    --size;   // Decrement the size of the circular queue.
    std::cout << "After deleting head node 100:" << std::endl;
    traverse_list(head, size);
    logger.info("After deleting head node 100");
    logger.info(queue_to_string(head, size));

    head = delete_node(head, 105, size);
    --size;   // Decrement the size of the circular queue.
    std::cout << "After deleting middle node 105:" << std::endl;
    traverse_list(head, size);
    logger.info("After deleting middle node 105");
    logger.info(queue_to_string(head, size));

    head = delete_node(head, 110, size);
    --size;   // Decrement the size of the circular queue.  
    std::cout << "After deleting tail node 110:" << std::endl;
    traverse_list(head, size);
    logger.info("After deleting tail node 110");
    logger.info(queue_to_string(head, size));

    head = delete_node(head, 999, size);
    std::cout << "After trying to delete missing node 999:" << std::endl;
    traverse_list(head, size);
    logger.info("After trying to delete missing node 999");
    logger.info(queue_to_string(head, size));
    logger.info("Deleted test nodes with data=100, 105, and 110");

    while (head != nullptr && size > 0) {
        Node* next = head->tail;
        delete head;
        head = next;
        --size;
    }
    traverse_list(head, size);
    logger.info("After cleanup");
    logger.info(queue_to_string(head, size));
    head = nullptr;

    logger.info("Circular queue program completed successfully");

}






















































































