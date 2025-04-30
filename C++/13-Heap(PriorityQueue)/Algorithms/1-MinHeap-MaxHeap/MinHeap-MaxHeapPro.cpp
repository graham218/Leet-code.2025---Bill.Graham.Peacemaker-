#include <iostream>
#include <vector>
#include <queue>
#include <functional> // For std::greater and std::less
#include <algorithm> // For std::make_heap, std::push_heap, std::pop_heap, std::sort_heap
#include <random> // For generating random data
#include <chrono> // For seeding the random number generator

// Function to print the heap (for demonstration purposes)
void printHeap(const std::vector<int>& heap) {
    std::cout << "Heap: ";
    for (int value : heap) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

// 1.  C++ Standard Library - std::priority_queue (Max Heap and Min Heap)
//      -   Advantages:  Simplest and most efficient for basic heap operations.  Highly optimized.
//      -   Disadvantages: Less flexible for custom heap implementations.
//      -   Real-world application: Task scheduling in an operating system.  Higher priority tasks
//          are processed before lower priority ones.  Event management.
void stdPriorityQueueExample() {
    std::cout << "\n1. std::priority_queue Example (Task Scheduling)\n";

    // Max Heap (default)
    std::priority_queue<int> maxHeap;
    maxHeap.push(30);
    maxHeap.push(10);
    maxHeap.push(60);
    maxHeap.push(20);
    maxHeap.push(50);

    std::cout << "Max Heap (Task Priorities):" << std::endl;
    while (!maxHeap.empty()) {
        std::cout << "Processing Task with Priority: " << maxHeap.top() << std::endl;
        maxHeap.pop();
    }

    // Min Heap using std::greater
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    minHeap.push(30);
    minHeap.push(10);
    minHeap.push(60);
    minHeap.push(20);
    minHeap.push(50);

    std::cout << "\nMin Heap (Shortest Job First):" << std::endl;
    while (!minHeap.empty()) {
        std::cout << "Processing Job with Time: " << minHeap.top() << std::endl;
        minHeap.pop();
    }
}


// 2.  std::make_heap, std::push_heap, std::pop_heap (Max Heap)
//      -   Advantages: Provides more control over the underlying vector.  Useful when you
//          already have data in a vector and want to heapify it.
//      -   Disadvantages: Slightly more verbose than std::priority_queue.
//      -   Real-world application: Sorting algorithms (Heap Sort).  Efficiently sorting
//          a large dataset in place.
void stdMakeHeapExample() {
    std::cout << "\n2. std::make_heap Example (Heap Sort)\n";
    std::vector<int> heapVector = {30, 10, 60, 20, 50};

    // Create a max heap from the vector
    std::make_heap(heapVector.begin(), heapVector.end());  // Default: Max Heap
    printHeap(heapVector);

     // Push a new element onto the heap
    heapVector.push_back(40);
    std::push_heap(heapVector.begin(), heapVector.end());
    printHeap(heapVector);

    // Pop the maximum element from the heap
    std::pop_heap(heapVector.begin(), heapVector.end());
    int maxElement = heapVector.back();
    heapVector.pop_back();
    std::cout << "Popped Element: " << maxElement << std::endl;
    printHeap(heapVector);

    // Sort the heap (Heap Sort)
    std::sort_heap(heapVector.begin(), heapVector.end());
    std::cout << "Sorted Vector (Heap Sort): ";
    for (int value : heapVector) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

// 3.  Custom Heap Implementation (Max Heap)
//     -   Advantages:  Maximum flexibility.  You can implement any custom behavior
//         or data structure within the heap.
//     -   Disadvantages:  More complex to implement and debug.  Less efficient than
//         the standard library implementations unless highly optimized.
//     -   Real-world application:  Implementing a custom priority queue with
//         specialized behavior, such as a heap where elements have both a priority
//         and a timestamp, and older elements with the same priority are served first.
class MaxHeapCustom {
private:
    std::vector<int> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index] > heap[parentIndex]) {
                std::swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int leftChild, rightChild, largest;
        while (true) {
            leftChild = 2 * index + 1;
            rightChild = 2 * index + 2;
            largest = index;

            if (leftChild < heap.size() && heap[leftChild] > heap[largest]) {
                largest = leftChild;
            }
            if (rightChild < heap.size() && heap[rightChild] > heap[largest]) {
                largest = rightChild;
            }

            if (largest != index) {
                std::swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    MaxHeapCustom() {}

    bool empty() const {
        return heap.empty();
    }

    size_t size() const{
        return heap.size();
    }

    void push(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    int top() const {
        if (empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heap[0];
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("Heap is empty");
        }
        if (heap.size() == 1){
            heap.pop_back();
            return;
        }
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }
    void print() const {
        printHeap(heap);
    }
};

void customMaxHeapExample() {
    std::cout << "\n3. Custom Max Heap Example (Custom Priority Queue)\n";
    MaxHeapCustom maxHeap;
    maxHeap.push(30);
    maxHeap.push(10);
    maxHeap.push(60);
    maxHeap.push(20);
    maxHeap.push(50);
    maxHeap.print();

    std::cout << "Max Element: " << maxHeap.top() << std::endl;
    maxHeap.pop();
    maxHeap.print();

    while (!maxHeap.empty()) {
        std::cout << "Popped: " << maxHeap.top() << std::endl;
        maxHeap.pop();
    }
}

// 4.  Custom Heap Implementation (Min Heap)
//  - Advantages: Same as custom max heap, full control.
//  - Disadvantages: Same as custom max heap, more complex.
//  - Real-world application:  Resource allocation with minimum cost.  For example,
//     finding the cheapest available server in a cloud computing environment.
class MinHeapCustom {
private:
    std::vector<int> heap;

     void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index] < heap[parentIndex]) { // Changed comparison to < for Min Heap
                std::swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int leftChild, rightChild, smallest; // Changed variable name to smallest
        while (true) {
            leftChild = 2 * index + 1;
            rightChild = 2 * index + 2;
            smallest = index; // Changed variable name to smallest

            if (leftChild < heap.size() && heap[leftChild] < heap[smallest]) { // Changed comparison to <
                smallest = leftChild;
            }
            if (rightChild < heap.size() && heap[rightChild] < heap[smallest]) { // Changed comparison to <
                smallest = rightChild;
            }

            if (smallest != index) {
                std::swap(heap[index], heap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }

public:
    MinHeapCustom() {}

    bool empty() const {
        return heap.empty();
    }

     size_t size() const{
        return heap.size();
    }

    void push(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    int top() const {
        if (empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heap[0];
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("Heap is empty");
        }
         if (heap.size() == 1){
            heap.pop_back();
            return;
        }
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    void print() const {
        printHeap(heap);
    }
};

void customMinHeapExample() {
    std::cout << "\n4. Custom Min Heap Example (Resource Allocation)\n";
    MinHeapCustom minHeap;
    minHeap.push(30);
    minHeap.push(10);
    minHeap.push(60);
    minHeap.push(20);
    minHeap.push(50);
    minHeap.print();

    std::cout << "Min Element: " << minHeap.top() << std::endl;
    minHeap.pop();
    minHeap.print();

    while (!minHeap.empty()) {
        std::cout << "Popped: " << minHeap.top() << std::endl;
        minHeap.pop();
    }
}

// 5.  Heap with Custom Data Structure (Example with Process struct)
//   -  Advantages:  Demonstrates how to use heaps with more complex data.
//   -  Disadvantages: Requires defining a custom comparison function.
//   -  Real-world application:  Job scheduling with priorities and arrival times.
//      A process with higher priority or earlier arrival time should be processed first.
struct Process {
    int id;
    int priority;
    int arrivalTime;

    Process(int i, int p, int a) : id(i), priority(p), arrivalTime(a) {}
};

// Custom comparison function for a min-priority queue based on priority and arrival time.
struct ProcessCompare {
    bool operator()(const Process& a, const Process& b) {
        if (a.priority != b.priority) {
            return a.priority > b.priority; // Lower number means higher priority (min heap)
        }
        return a.arrivalTime > b.arrivalTime;    // If priorities are equal, earlier arrival time first
    }
};

void customDataStructureHeapExample() {
    std::cout << "\n5. Heap with Custom Data Structure (Job Scheduling)\n";
    std::priority_queue<Process, std::vector<Process>, ProcessCompare> processQueue;

    processQueue.push(Process(1, 3, 0)); // Process ID 1, Priority 3, Arrival Time 0
    processQueue.push(Process(2, 1, 5)); // Process ID 2, Priority 1, Arrival Time 5
    processQueue.push(Process(3, 2, 2)); // Process ID 3, Priority 2, Arrival Time 2
    processQueue.push(Process(4, 1, 1)); // Process ID 4, Priority 1, Arrival Time 1
    processQueue.push(Process(5, 3, 3)); // Process ID 5, Priority 3, Arrival Time 3

    std::cout << "Process Scheduling Order:" << std::endl;
    while (!processQueue.empty()) {
        Process p = processQueue.top();
        processQueue.pop();
        std::cout << "Process ID: " << p.id
                  << ", Priority: " << p.priority
                  << ", Arrival Time: " << p.arrivalTime << std::endl;
    }
}

int main() {
    // Seed the random number generator for variety in output.
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    stdPriorityQueueExample();
    stdMakeHeapExample();
    customMaxHeapExample();
    customMinHeapExample();
    customDataStructureHeapExample();

    return 0;
}
