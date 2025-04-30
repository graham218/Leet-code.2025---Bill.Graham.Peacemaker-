#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional> // Required for std::greater and std::less

// Approach 1: Manual Implementation (Max Heap and Min Heap)
//   - Provides the most control and understanding of the heap data structure.
//   - Implements the basic heap operations: insert, getTop, removeTop, and heapify.
//   - Uses a vector as the underlying storage.
//   - Includes both Max Heap and Min Heap implementations in the same struct.

struct ManualHeap {
    std::vector<int> maxHeap; // Vector to store the elements of the max heap
    std::vector<int> minHeap; // Vector to store the elements of the min heap

    // Helper function to maintain the max heap property.
    void maxHeapify(std::vector<int>& heap, int i) {
        int left = 2 * i + 1;  // Index of the left child
        int right = 2 * i + 2; // Index of the right child
        int largest = i;       // Index of the largest element among the node and its children

        if (left < heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != i) {
            std::swap(heap[i], heap[largest]); // Swap if the largest is not the current node
            maxHeapify(heap, largest);         // Recursively heapify the affected subtree
        }
    }

    // Helper function to maintain the min heap property.
    void minHeapify(std::vector<int>& heap, int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap.size() && heap[left] < heap[smallest]) {
            smallest = left;
        }

        if (right < heap.size() && heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest != i) {
            std::swap(heap[i], heap[smallest]);
            minHeapify(heap, smallest);
        }
    }

    // Function to insert an element into the max heap.
    void insertMaxHeap(int value) {
        maxHeap.push_back(value); // Add the new element to the end of the vector
        int i = maxHeap.size() - 1; // Index of the newly inserted element

        // Maintain the max heap property by moving the element up the tree if necessary.
        while (i > 0 && maxHeap[(i - 1) / 2] < maxHeap[i]) {
            std::swap(maxHeap[i], maxHeap[(i - 1) / 2]); // Swap with the parent
            i = (i - 1) / 2;                           // Update the index to the parent's index
        }
    }

    // Function to insert an element into the min heap.
    void insertMinHeap(int value) {
        minHeap.push_back(value);
        int i = minHeap.size() - 1;

        while (i > 0 && minHeap[(i - 1) / 2] > minHeap[i]) {
            std::swap(minHeap[i], minHeap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    // Function to get the top element (maximum) of the max heap.
    int getMaxTop() {
        if (maxHeap.empty()) {
            std::cout << "Max Heap is empty" << std::endl;
            return -1; // Return -1 to indicate an empty heap (or throw an exception)
        }
        return maxHeap[0]; // The maximum element is always at the root (index 0)
    }

    // Function to get the top element (minimum) of the min heap.
    int getMinTop() {
        if (minHeap.empty()) {
            std::cout << "Min Heap is empty" << std::endl;
            return -1;
        }
        return minHeap[0];
    }

    // Function to remove the top element (maximum) from the max heap.
    void removeMaxTop() {
        if (maxHeap.empty()) {
            std::cout << "Max Heap is empty, cannot remove top" << std::endl;
            return;
        }
        maxHeap[0] = maxHeap.back(); // Replace the root with the last element
        maxHeap.pop_back();         // Remove the last element
        maxHeapify(maxHeap, 0);       // Restore the max heap property
    }

    // Function to remove the top element (minimum) from the min heap.
    void removeMinTop() {
        if (minHeap.empty()) {
            std::cout << "Min Heap is empty, cannot remove top" << std::endl;
            return;
        }
        minHeap[0] = minHeap.back();
        minHeap.pop_back();
        minHeapify(minHeap, 0);
    }

     // Function to build a max heap from a vector.
    void buildMaxHeap(std::vector<int>& arr) {
        maxHeap = arr;
        for (int i = maxHeap.size() / 2 - 1; i >= 0; i--) {
            maxHeapify(maxHeap, i);
        }
    }

    // Function to build a min heap from a vector.
    void buildMinHeap(std::vector<int>& arr) {
        minHeap = arr;
        for (int i = minHeap.size() / 2 - 1; i >= 0; i--) {
            minHeapify(minHeap, i);
        }
    }
};

// Approach 2: Using std::priority_queue (Max Heap)
//   - Leverages the C++ Standard Library's priority_queue, which is a max heap by default.
//   - Provides a simple and efficient way to use a max heap.
//   - The priority_queue automatically maintains the heap property.

void useStdPriorityQueueMax() {
    std::priority_queue<int> maxHeap; // Declares a max heap of integers

    maxHeap.push(5); // Inserts elements into the heap
    maxHeap.push(2);
    maxHeap.push(8);
    maxHeap.push(1);

    std::cout << "Max Heap using std::priority_queue (Max):" << std::endl;
    while (!maxHeap.empty()) {
        std::cout << maxHeap.top() << " "; // Accesses the top element (maximum)
        maxHeap.pop();                   // Removes the top element
    }
    std::cout << std::endl;
}

// Approach 3: Using std::priority_queue (Min Heap)
//   - Uses std::priority_queue with a custom comparator (std::greater<int>) to create a min heap.
//   - Demonstrates how to customize the behavior of std::priority_queue.

void useStdPriorityQueueMin() {
    // Declares a min heap of integers using std::greater<int> as the comparator
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    minHeap.push(5);
    minHeap.push(2);
    minHeap.push(8);
    minHeap.push(1);

    std::cout << "Min Heap using std::priority_queue (Min):" << std::endl;
    while (!minHeap.empty()) {
        std::cout << minHeap.top() << " ";
        minHeap.pop();
    }
    std::cout << std::endl;
}

// Approach 4: Using std::make_heap (Max Heap)
//  - Uses `std::make_heap`, `std::push_heap`, and `std::pop_heap` to manage a heap within a vector.
//  - Provides more control over the underlying vector than `std::priority_queue`.

void useStdMakeHeapMax() {
    std::vector<int> heapVector = {5, 2, 8, 1}; // Initialize a vector

    std::make_heap(heapVector.begin(), heapVector.end()); // Convert the vector into a max heap

    std::cout << "Max Heap using std::make_heap (Max):" << std::endl;
    for (int value : heapVector) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::cout << "Top element: " << heapVector.front() << std::endl; // Access the top element

    std::pop_heap(heapVector.begin(), heapVector.end()); // Move the top element to the end
    int poppedValue = heapVector.back();             // Get the value that was at the top
    heapVector.pop_back();                           // Remove the element from the end

    std::cout << "Popped element: " << poppedValue << std::endl;

    std::cout << "Heap after pop:" << std::endl;
     for (int value : heapVector) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    heapVector.push_back(6);             // Add a new element to the vector
    std::push_heap(heapVector.begin(), heapVector.end()); // Restore the heap property

     std::cout << "Heap after push:" << std::endl;
     for (int value : heapVector) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

// Approach 5: Using std::make_heap (Min Heap)
//   - Demonstrates using `std::make_heap` with a custom comparator to create a min heap.

void useStdMakeHeapMin() {
    std::vector<int> heapVector = {5, 2, 8, 1};
    // Use std::greater<int> to create a min heap
    std::make_heap(heapVector.begin(), heapVector.end(), std::greater<int>());

    std::cout << "Min Heap using std::make_heap (Min):" << std::endl;
     for (int value : heapVector) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::cout << "Top element: " << heapVector.front() << std::endl;

    std::pop_heap(heapVector.begin(), heapVector.end(), std::greater<int>());
    int poppedValue = heapVector.back();
    heapVector.pop_back();

    std::cout << "Popped element: " << poppedValue << std::endl;
    std::cout << "Heap after pop:" << std::endl;
     for (int value : heapVector) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    heapVector.push_back(6);
    std::push_heap(heapVector.begin(), heapVector.end(), std::greater<int>());
     std::cout << "Heap after push:" << std::endl;
     for (int value : heapVector) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Approach 1: Manual Implementation
    std::cout << "Approach 1: Manual Implementation" << std::endl;
    ManualHeap manualHeap;

    // Max Heap
    manualHeap.insertMaxHeap(5);
    manualHeap.insertMaxHeap(2);
    manualHeap.insertMaxHeap(8);
    manualHeap.insertMaxHeap(1);

    std::cout << "Max Heap: ";
    std::vector<int> tempMax = manualHeap.maxHeap; //copy the maxHeap
    while(!tempMax.empty()){
        std::cout<< tempMax[0] << " ";
        tempMax.erase(tempMax.begin());
    }
    std::cout << std::endl;
    std::cout << "Max Top: " << manualHeap.getMaxTop() << std::endl; // 8
    manualHeap.removeMaxTop();
    std::cout << "Max Top after removal: " << manualHeap.getMaxTop() << std::endl; // 5

     std::vector<int> initialMaxHeap = { 10, 5, 3, 7, 1 };
    manualHeap.buildMaxHeap(initialMaxHeap);

    std::cout << "Max Heap after buildMaxHeap: ";
     tempMax = manualHeap.maxHeap; //copy the maxHeap
    while(!tempMax.empty()){
        std::cout<< tempMax[0] << " ";
         tempMax.erase(tempMax.begin());
    }
    std::cout << std::endl;


    // Min Heap
    manualHeap.insertMinHeap(5);
    manualHeap.insertMinHeap(2);
    manualHeap.insertMinHeap(8);
    manualHeap.insertMinHeap(1);

    std::cout << "Min Heap: ";
    std::vector<int> tempMin = manualHeap.minHeap; //copy the minHeap
    while(!tempMin.empty()){
        std::cout<< tempMin[0] << " ";
        tempMin.erase(tempMin.begin());
    }
    std::cout << std::endl;
    std::cout << "Min Top: " << manualHeap.getMinTop() << std::endl; // 1
    manualHeap.removeMinTop();
    std::cout << "Min Top after removal: " << manualHeap.getMinTop() << std::endl; // 2

     std::vector<int> initialMinHeap = { 10, 5, 3, 7, 1 };
    manualHeap.buildMinHeap(initialMinHeap);
    std::cout << "Min Heap after buildMinHeap: ";
    tempMin = manualHeap.minHeap; //copy the minHeap
    while(!tempMin.empty()){
        std::cout<< tempMin[0] << " ";
        tempMin.erase(tempMin.begin());
    }
    std::cout << std::endl;

    // Approach 2: Using std::priority_queue (Max Heap)
    std::cout << "\nApproach 2: Using std::priority_queue (Max Heap)" << std::endl;
    useStdPriorityQueueMax();

    // Approach 3: Using std::priority_queue (Min Heap)
    std::cout << "\nApproach 3: Using std::priority_queue (Min Heap)" << std::endl;
    useStdPriorityQueueMin();

    // Approach 4: Using std::make_heap (Max Heap)
    std::cout << "\nApproach 4: Using std::make_heap (Max Heap)" << std::endl;
    useStdMakeHeapMax();

    // Approach 5: Using std::make_heap (Min Heap)
    std::cout << "\nApproach 5: Using std::make_heap (Min Heap)" << std::endl;
    useStdMakeHeapMin();

    return 0;
}
