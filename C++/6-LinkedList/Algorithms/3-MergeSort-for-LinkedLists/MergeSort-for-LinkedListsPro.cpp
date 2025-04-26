/**
 * Merge Sort for Linked Lists - 5 Approaches in One File
 * 1. Classic Recursive Merge Sort
 * 2. Iterative Bottom-Up Merge Sort
 * 3. Merge Sort with Tail Pointer Optimization
 * 4. Merge Sort with Smart Pointers (Modern C++)
 * 5. Merge Sort with Custom Memory Pool
 */

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// Common Node structure for first 3 approaches
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Utility functions shared by multiple approaches
void printList(Node* node) {
    while (node != nullptr) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

void push(Node** headRef, int newData) {
    Node* newNode = new Node(newData);
    newNode->next = *headRef;
    *headRef = newNode;
}

// Approach 1: Classic Recursive Merge Sort
namespace ClassicRecursive {
    Node* merge(Node* left, Node* right) {
        if (!left) return right;
        if (!right) return left;

        Node* result = nullptr;

        if (left->data <= right->data) {
            result = left;
            result->next = merge(left->next, right);
        } else {
            result = right;
            result->next = merge(left, right->next);
        }

        return result;
    }

    void split(Node* source, Node** front, Node** back) {
        Node* slow = source;
        Node* fast = source->next;

        while (fast != nullptr) {
            fast = fast->next;
            if (fast != nullptr) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *front = source;
        *back = slow->next;
        slow->next = nullptr;
    }

    void mergeSort(Node** headRef) {
        Node* head = *headRef;
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        Node* left;
        Node* right;

        split(head, &left, &right);

        mergeSort(&left);
        mergeSort(&right);

        *headRef = merge(left, right);
    }

    void test() {
        cout << "\nApproach 1: Classic Recursive Merge Sort\n";
        Node* head = nullptr;
        push(&head, 15);
        push(&head, 10);
        push(&head, 5);
        push(&head, 20);
        push(&head, 3);
        push(&head, 2);

        cout << "Original List: ";
        printList(head);

        mergeSort(&head);

        cout << "Sorted List: ";
        printList(head);

        // Cleanup
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
}

// Approach 2: Iterative Bottom-Up Merge Sort
namespace IterativeBottomUp {
    Node* merge(Node* left, Node* right) {
        Node dummy(0);
        Node* tail = &dummy;

        while (left && right) {
            if (left->data <= right->data) {
                tail->next = left;
                left = left->next;
            } else {
                tail->next = right;
                right = right->next;
            }
            tail = tail->next;
        }

        tail->next = left ? left : right;
        return dummy.next;
    }

    int getSize(Node* head) {
        int count = 0;
        while (head) {
            count++;
            head = head->next;
        }
        return count;
    }

    Node* split(Node* head, int n) {
        for (int i = 1; head && i < n; i++) {
            head = head->next;
        }

        if (!head) return nullptr;

        Node* rest = head->next;
        head->next = nullptr;
        return rest;
    }

    void mergeSort(Node** headRef) {
        if (!headRef || !*headRef || !(*headRef)->next) {
            return;
        }

        Node* head = *headRef;
        int size = getSize(head);
        Node* dummy = new Node(0);
        dummy->next = head;

        for (int blockSize = 1; blockSize < size; blockSize *= 2) {
            Node* prev = dummy;
            Node* curr = dummy->next;

            while (curr) {
                Node* left = curr;
                Node* right = split(left, blockSize);
                curr = split(right, blockSize);
                prev->next = merge(left, right);

                while (prev->next) {
                    prev = prev->next;
                }
            }
        }

        *headRef = dummy->next;
        delete dummy;
    }

    void test() {
        cout << "\nApproach 2: Iterative Bottom-Up Merge Sort\n";
        Node* head = nullptr;
        push(&head, 15);
        push(&head, 10);
        push(&head, 5);
        push(&head, 20);
        push(&head, 3);
        push(&head, 2);

        cout << "Original List: ";
        printList(head);

        mergeSort(&head);

        cout << "Sorted List: ";
        printList(head);

        // Cleanup
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
}

// Approach 3: Merge Sort with Tail Pointer Optimization
namespace TailPointer {
    struct List {
        Node* head;
        Node* tail;
        List() : head(nullptr), tail(nullptr) {}
    };

    List merge(List left, List right) {
        List result;
        Node* a = left.head;
        Node* b = right.head;

        if (!a) return right;
        if (!b) return left;

        if (a->data <= b->data) {
            result.head = result.tail = a;
            a = a->next;
        } else {
            result.head = result.tail = b;
            b = b->next;
        }

        while (a && b) {
            if (a->data <= b->data) {
                result.tail->next = a;
                result.tail = a;
                a = a->next;
            } else {
                result.tail->next = b;
                result.tail = b;
                b = b->next;
            }
        }

        if (a) {
            result.tail->next = a;
            result.tail = left.tail;
        } else {
            result.tail->next = b;
            result.tail = right.tail;
        }

        return result;
    }

    List split(List source) {
        List left, right;
        if (!source.head || !source.head->next) {
            left = source;
            return left;
        }

        Node* slow = source.head;
        Node* fast = source.head->next;

        while (fast) {
            fast = fast->next;
            if (fast) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        left.head = source.head;
        left.tail = slow;
        right.head = slow->next;
        right.tail = source.tail;
        slow->next = nullptr;

        return right;
    }

    List mergeSort(List list) {
        if (!list.head || !list.head->next) {
            return list;
        }

        List right = split(list);
        list.tail = right.head ? right.head : list.tail;

        List leftSorted = mergeSort(list);
        List rightSorted = mergeSort(right);

        return merge(leftSorted, rightSorted);
    }

    void push(List* list, int newData) {
        Node* newNode = new Node(newData);
        if (!list->head) {
            list->head = list->tail = newNode;
        } else {
            newNode->next = list->head;
            list->head = newNode;
        }
    }

    void test() {
        cout << "\nApproach 3: Merge Sort with Tail Pointer Optimization\n";
        List list;
        push(&list, 15);
        push(&list, 10);
        push(&list, 5);
        push(&list, 20);
        push(&list, 3);
        push(&list, 2);

        cout << "Original List: ";
        printList(list.head);

        List sorted = mergeSort(list);

        cout << "Sorted List: ";
        printList(sorted.head);

        // Cleanup
        Node* current = sorted.head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

// Approach 4: Merge Sort with Smart Pointers (Modern C++)
namespace SmartPointer {
    struct Node {
        int data;
        shared_ptr<Node> next;
        Node(int val) : data(val), next(nullptr) {}
    };

    using NodePtr = shared_ptr<Node>;

    NodePtr merge(NodePtr left, NodePtr right) {
        if (!left) return right;
        if (!right) return left;

        NodePtr result;

        if (left->data <= right->data) {
            result = left;
            result->next = merge(left->next, right);
        } else {
            result = right;
            result->next = merge(left, right->next);
        }

        return result;
    }

    void split(NodePtr source, NodePtr* front, NodePtr* back) {
        if (!source || !source->next) {
            *front = source;
            *back = nullptr;
            return;
        }

        NodePtr slow = source;
        NodePtr fast = source->next;

        while (fast) {
            fast = fast->next;
            if (fast) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *front = source;
        *back = slow->next;
        slow->next = nullptr;
    }

    void mergeSort(NodePtr* headRef) {
        NodePtr head = *headRef;
        if (!head || !head->next) {
            return;
        }

        NodePtr left;
        NodePtr right;

        split(head, &left, &right);

        mergeSort(&left);
        mergeSort(&right);

        *headRef = merge(left, right);
    }

    void printList(NodePtr node) {
        while (node) {
            cout << node->data << " ";
            node = node->next;
        }
        cout << endl;
    }

    void push(NodePtr* headRef, int newData) {
        NodePtr newNode = make_shared<Node>(newData);
        newNode->next = *headRef;
        *headRef = newNode;
    }

    void test() {
        cout << "\nApproach 4: Merge Sort with Smart Pointers (Modern C++)\n";
        NodePtr head = nullptr;
        push(&head, 15);
        push(&head, 10);
        push(&head, 5);
        push(&head, 20);
        push(&head, 3);
        push(&head, 2);

        cout << "Original List: ";
        printList(head);

        mergeSort(&head);

        cout << "Sorted List: ";
        printList(head);

        // Smart pointers will automatically clean up
    }
}

// Approach 5: Merge Sort with Custom Memory Pool
namespace MemoryPool {
    class NodePool {
        vector<Node*> pool;
    public:
        Node* allocate(int data) {
            if (pool.empty()) {
                return new Node(data);
            }
            Node* node = pool.back();
            pool.pop_back();
            node->data = data;
            node->next = nullptr;
            return node;
        }

        void deallocate(Node* node) {
            if (node) {
                pool.push_back(node);
            }
        }

        ~NodePool() {
            for (Node* node : pool) {
                delete node;
            }
        }
    };

    NodePool nodePool;

    Node* merge(Node* left, Node* right) {
        Node* dummy = nodePool.allocate(0); // Allocate dummy node from pool
        Node* tail = dummy;

        while (left && right) {
            if (left->data <= right->data) {
                tail->next = left;
                left = left->next;
            } else {
                tail->next = right;
                right = right->next;
            }
            tail = tail->next;
        }

        tail->next = left ? left : right;
        Node* result = dummy->next;
        nodePool.deallocate(dummy); // Deallocate the dummy node
        return result;
    }

    void split(Node* source, Node** front, Node** back) {
        if (!source || !source->next) {
            *front = source;
            *back = nullptr;
            return;
        }

        Node* slow = source;
        Node* fast = source->next;

        while (fast) {
            fast = fast->next;
            if (fast) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *front = source;
        *back = slow->next;
        slow->next = nullptr;
    }

    void mergeSort(Node** headRef) {
        Node* head = *headRef;
        if (!head || !head->next) {
            return;
        }

        Node* left;
        Node* right;

        split(head, &left, &right);

        mergeSort(&left);
        mergeSort(&right);

        *headRef = merge(left, right);
    }

    void push(Node** headRef, int newData) {
        Node* newNode = nodePool.allocate(newData);
        newNode->next = *headRef;
        *headRef = newNode;
    }

    void deleteList(Node** headRef) {
        Node* current = *headRef;
        while (current) {
            Node* next = current->next;
            nodePool.deallocate(current);
            current = next;
        }
        *headRef = nullptr;
    }

    void test() {
        cout << "\nApproach 5: Merge Sort with Custom Memory Pool\n";
        Node* head = nullptr;
        MemoryPool::push(&head, 15); // Use MemoryPool::push
        MemoryPool::push(&head, 10);
        MemoryPool::push(&head, 5);
        MemoryPool::push(&head, 20);
        MemoryPool::push(&head, 3);
        MemoryPool::push(&head, 2);

        cout << "Original List: ";
        printList(head);

        mergeSort(&head);

        cout << "Sorted List: ";
        printList(head);

        deleteList(&head);
    }
}

int main() {
    cout << "Merge Sort for Linked Lists - 5 Approaches\n";

    // Test all approaches
    ClassicRecursive::test();
    IterativeBottomUp::test();
    TailPointer::test();
    SmartPointer::test();
    MemoryPool::test();

    return 0;
}
