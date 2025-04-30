#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <functional> // Required for std::greater

// Definition for a node.  Although this problem doesn't use a node *directly*,
// it's common to use nodes in tree-based implementations of priority queues.
struct Node {
    int val;
    int frequency;
    Node(int v, int f) : val(v), frequency(f) {}
};

// 1. Using a Min-Heap (Priority Queue) of Pairs
// - Time Complexity: O(N log K), where N is the number of elements in the vector.
// - Space Complexity: O(N + K), for the hash map and the heap.
std::vector<int> topKFrequent_MinHeapPairs(std::vector<int>& nums, int k) {
    // Count the frequency of each element using an unordered_map.
    std::unordered_map<int, int> frequencyMap;
    for (int num : nums) {
        frequencyMap[num]++;
    }

    // Create a min-heap (priority queue) to store pairs of (frequency, element).
    // The priority queue automatically sorts the pairs in ascending order of frequency.
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> minHeap;

    // Iterate through the frequency map and push elements into the min-heap.
    for (auto const& [element, frequency] : frequencyMap) {
        minHeap.push({frequency, element}); // {frequency, element} pair
        if (minHeap.size() > k) {
            minHeap.pop(); // Keep only the top k frequent elements in the heap.
        }
    }

    // Extract the top k frequent elements from the min-heap.
    std::vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().second); // Get the element (second of the pair)
        minHeap.pop();
    }
    return result;
}

// 2. Using a Min-Heap (Priority Queue) of Custom Node Struct
// - Time Complexity: O(N log K)
// - Space Complexity: O(N + K)
std::vector<int> topKFrequent_MinHeapNodes(std::vector<int>& nums, int k) {
    // Count frequencies.
    std::unordered_map<int, int> frequencyMap;
    for (int num : nums) {
        frequencyMap[num]++;
    }

    // Use a min-heap with a custom comparator (using a lambda).  This approach
    // uses a custom struct `Node` to encapsulate the value and its frequency.
    auto compare = [](const Node& a, const Node& b) {
        return a.frequency > b.frequency; // Min-heap based on frequency.
    };
    std::priority_queue<Node, std::vector<Node>, decltype(compare)> minHeap(compare);

    for (auto const& [element, frequency] : frequencyMap) {
        minHeap.push(Node(element, frequency));
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }

    std::vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().val);
        minHeap.pop();
    }
    return result;
}

// 3. Using a Max-Heap (Priority Queue)
// - Time Complexity: O(N log N)  (Can be optimized to O(N + K log K) using bucket sort first)
// - Space Complexity: O(N)
std::vector<int> topKFrequent_MaxHeap(std::vector<int>& nums, int k) {
    // Count frequencies.
    std::unordered_map<int, int> frequencyMap;
    for (int num : nums) {
        frequencyMap[num]++;
    }

    // Create a max-heap (priority queue).  The default `std::priority_queue` is a max-heap.
    std::priority_queue<std::pair<int, int>> maxHeap; // {frequency, element}

    // Push all frequencies and elements into the max-heap.
    for (auto const& [element, frequency] : frequencyMap) {
        maxHeap.push({frequency, element});
    }

    // Extract the top k frequent elements from the max-heap.
    std::vector<int> result;
    for (int i = 0; i < k && !maxHeap.empty(); ++i) {
        result.push_back(maxHeap.top().second);
        maxHeap.pop();
    }
    return result;
}

// 4. Using std::nth_element (Partial Sort)
// - Time Complexity: O(N) on average (worst case O(N^2)), faster than full sort.
// - Space Complexity: O(1) (excluding the result vector)
std::vector<int> topKFrequent_NthElement(std::vector<int>& nums, int k) {
    // Count frequencies.
    std::unordered_map<int, int> frequencyMap;
    for (int num : nums) {
        frequencyMap[num]++;
    }

    // Create a vector of (element, frequency) pairs.
    std::vector<std::pair<int, int>> frequencyPairs;
    for (auto const& [element, frequency] : frequencyMap) {
        frequencyPairs.push_back({element, frequency});
    }

    // Use std::nth_element to partially sort the vector such that the kth largest
    // element (in terms of frequency) is in its correct position.
    std::nth_element(frequencyPairs.begin(), frequencyPairs.begin() + k - 1, frequencyPairs.end(),
                     [](const auto& a, const auto& b) { return a.second > b.second; });

    // The first k elements of frequencyPairs now contain the top k frequent elements.
    std::vector<int> result;
    for (int i = 0; i < k; ++i) {
        result.push_back(frequencyPairs[i].first);
    }
    return result;
}

// 5. Using Bucket Sort
// - Time Complexity: O(N)
// - Space Complexity: O(N)
std::vector<int> topKFrequent_BucketSort(std::vector<int>& nums, int k) {
    // Count frequencies.
    std::unordered_map<int, int> frequencyMap;
    for (int num : nums) {
        frequencyMap[num]++;
    }

    // Create buckets based on frequencies.  The index represents the frequency,
    // and the value is a vector of elements with that frequency.
    std::vector<std::vector<int>> buckets(nums.size() + 1); // size + 1 because frequency can be at most nums.size()

    for (auto const& [element, frequency] : frequencyMap) {
        buckets[frequency].push_back(element);
    }

    // Collect the top k frequent elements from the buckets, starting from the highest frequency.
    std::vector<int> result;
    for (int i = buckets.size() - 1; i >= 0 && result.size() < k; --i) {
        for (int element : buckets[i]) {
            result.push_back(element);
            if (result.size() == k) {
                break;
            }
        }
    }
    return result;
}

int main() {
    std::vector<int> nums = {1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 5};
    int k = 2;

    std::cout << "Input: nums = [";
    for (int num : nums) {
        std::cout << num << " ";
    }
    std::cout << "], k = " << k << std::endl;

    std::cout << "\nTop " << k << " Frequent Elements:\n";

    std::cout << "\n1. Using Min-Heap (Pairs): ";
    std::vector<int> result1 = topKFrequent_MinHeapPairs(nums, k);
    for (int num : result1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "2. Using Min-Heap (Nodes): ";
    std::vector<int> result2 = topKFrequent_MinHeapNodes(nums, k);
    for (int num : result2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "3. Using Max-Heap: ";
    std::vector<int> result3 = topKFrequent_MaxHeap(nums, k);
    for (int num : result3) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "4. Using nth_element: ";
    std::vector<int> result4 = topKFrequent_NthElement(nums, k);
    for (int num : result4) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "5. Using Bucket Sort: ";
    std::vector<int> result5 = topKFrequent_BucketSort(nums, k);
    for (int num : result5) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
