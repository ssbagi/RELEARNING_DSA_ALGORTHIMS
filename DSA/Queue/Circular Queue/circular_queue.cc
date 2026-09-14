#include <iostream>
#include <sstream>
#include <string>
#include "logger.h"
#include "circular_queue.h"


namespace {

    constexpr const char* LOG_FILE = "circular_queue.log";

    std::string queue_to_string(Node* head) {
        std::ostringstream output;
        output << "Circular Queue: ";

        if (head == nullptr) {
            output << "nullptr";
            return output.str();
        }

        Node* current = head;

        // One full loop: stop once the walk returns to the starting node.
        do {
            output << current->data << " -> ";
            current = current->tail;
        } while (current != head);

        output << "(back to " << head->data << ")";
        return output.str();
    }

}  // namespace

// Insert a node just before the start node, i.e. at the logical end of the circle.
// Time: O(1), because the previous node is reachable through the start node's head link.
// Auxiliary space: O(1), excluding the newly allocated node.
Node* insert_node(Node* node, int data) {
    /*
    Basic Circular Queue concept without a capacity limit :
        - The queue grows on demand, one node per insertion.
        - The list stays closed at all times, so no link is ever nullptr.
        - A single node is its own previous and next node.
        - With two or more nodes the last node's tail points to the first node
          and the first node's head points to the last node.
    */

    Node* new_entry = new Node();
    new_entry->data = data;

    // First node closes the circle on itself.
    if (node == nullptr) {
        new_entry->head = new_entry;
        new_entry->tail = new_entry;
        return new_entry;
    }

    Node* last = node->head;   // Current last node, reachable in O(1).

    new_entry->head = last;
    new_entry->tail = node;
    last->tail = new_entry;
    node->head = new_entry;   // Circle stays closed after the insertion.

    return node;
}

// Delete the first node with the requested data and return the updated start node.
// Time: O(n), because one full loop may be scanned.
// Auxiliary space: O(1).
Node* delete_node(Node* node, int data) {
    // Return unchanged when the list is empty.
    if (node == nullptr) {
        return node;
    }

    Node* current = node;

    // Walk at most one full loop looking for the value.
    do {
        if (current->data == data) {
            break;
        }
        current = current->tail;
    } while (current != node);

    // Return unchanged when the value does not exist in the queue.
    if (current->data != data) {
        return node;
    }

    // Delete the only node in the circle.
    if (current->tail == current) {
        delete current;
        return nullptr;
    }

    // Move the returned start node forward when deleting the current start node.
    if (current == node) {
        node = current->tail;
    }

    // Relink the neighbours so the circle stays closed. With two nodes both
    // links collapse onto the single surviving node, pointing it at itself.
    current->head->tail = current->tail;
    current->tail->head = current->head;

    delete current;
    return node;
}

// Search a node in the circular doubly linked list using forward traversal.
// Time: O(n) worst case, including the not-found case.
// Auxiliary space: O(1)
bool search_node(Node* node, int data) {
    // A nullptr starting node means the list is empty.
    if (node == nullptr) {
        return false;
    }

    /*
        The list is circular, so there is no nullptr terminator even when the
        search starts from a node in the middle. Returning to the starting node
        marks one full loop and ends the search.
    */
    Node* current = node;
    do {
        if (current->data == data) {
            return true;
        }
        current = current->tail;
    } while (current != node);

    // Element not found
    return false;
}

// Traverse forward and print each node value.
// Time: O(n), because every node is visited once.
// Auxiliary space: O(1), excluding output-stream storage.
void traverse_list(Node* head) {
    std::cout << queue_to_string(head) << std::endl;
}

// Count the nodes in one full loop.
// Time: O(n). Auxiliary space: O(1).
int queue_size(Node* node) {
    if (node == nullptr) {
        return 0;
    }

    int size = 0;
    Node* current = node;
    do {
        ++size;
        current = current->tail;
    } while (current != node);

    return size;
}

// Release every node in the circle.
// Time: O(n). Auxiliary space: O(1).
void clear_list(Node* node) {
    if (node == nullptr) {
        return;
    }

    // Break the circle first so the walk reaches a nullptr terminator.
    node->head->tail = nullptr;

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

    logger.info("Circular queue program started");

    Node* head = nullptr;

    traverse_list(head);
    logger.info("Initial queue state");
    logger.info(queue_to_string(head));

    // Build the list from an empty starting pointer; the queue grows on demand.
    for (int data = 100; data <= 110; ++data) {
        head = insert_node(head, data);
        logger.info("Inserted node with data=", data);
    }

    std::cout << "After inserting 11 nodes:" << std::endl;
    traverse_list(head);
    std::cout << "Size: " << queue_size(head) << std::endl;
    logger.info("After inserting 11 nodes");
    logger.info(queue_to_string(head));

    const bool found_105 = search_node(head, 105);
    const bool found_999 = search_node(head, 999);
    std::cout << "Search 105: " << (found_105 ? "found" : "not found") << std::endl;
    std::cout << "Search 999: " << (found_999 ? "found" : "not found") << std::endl;
    logger.info("Search 105 result=", found_105 ? "found" : "not found");
    logger.info("Search 999 result=", found_999 ? "found" : "not found");

    head = delete_node(head, 100);
    std::cout << "After deleting head node 100:" << std::endl;
    traverse_list(head);
    logger.info("After deleting head node 100");
    logger.info(queue_to_string(head));

    head = delete_node(head, 105);
    std::cout << "After deleting middle node 105:" << std::endl;
    traverse_list(head);
    logger.info("After deleting middle node 105");
    logger.info(queue_to_string(head));

    head = delete_node(head, 110);
    std::cout << "After deleting tail node 110:" << std::endl;
    traverse_list(head);
    logger.info("After deleting tail node 110");
    logger.info(queue_to_string(head));

    head = delete_node(head, 999);
    std::cout << "After trying to delete missing node 999:" << std::endl;
    traverse_list(head);
    std::cout << "Size: " << queue_size(head) << std::endl;
    logger.info("After trying to delete missing node 999");
    logger.info(queue_to_string(head));
    logger.info("Deleted test nodes with data=100, 105, and 110");

    // Shrink down to two nodes, then one, to show the circle staying closed.
    // 105 is already gone, so the range runs to 107 to leave exactly 108 and 109.
    for (int data = 101; data <= 107; ++data) {
        head = delete_node(head, data);
    }
    std::cout << "Down to two nodes:" << std::endl;
    traverse_list(head);
    logger.info("Down to two nodes");
    logger.info(queue_to_string(head));

    head = delete_node(head, 108);
    std::cout << "Down to a single self-linked node:" << std::endl;
    traverse_list(head);
    logger.info("Down to a single self-linked node");
    logger.info(queue_to_string(head));

    clear_list(head);
    head = nullptr;
    traverse_list(head);
    logger.info("After cleanup");
    logger.info(queue_to_string(head));

    logger.info("Circular queue program completed successfully");

}






















































































