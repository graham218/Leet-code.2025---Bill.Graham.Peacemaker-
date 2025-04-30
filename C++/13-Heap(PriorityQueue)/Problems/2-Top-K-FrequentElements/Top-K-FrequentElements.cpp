#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

// Function to find the top K frequent elements in a vector
// 5 Different Approaches are implemented and their time complexities are mentioned in comments.

// Approach 1: Using a Max Heap (Priority Queue)
// Time Complexity: O(N log K), where N is the number of elements in the vector
// Space Complexity: O(N + K),  N for the hash map, K for the heap
vector<int> topKFrequent_MaxHeap(vector<int>& nums, int k) {
    // 1. Count the frequency of each element using a hash map
    unordered_map<int, int> freqMap;
    for (int num : nums) {
        freqMap[num]++;
    }

    // 2. Create a max heap (priority queue) to store pairs of (frequency, element)
    //    The priority queue will automatically sort the elements based on their frequencies
    priority_queue<pair<int, int>> maxHeap;
    for (auto const& [num, freq] : freqMap) {
        maxHeap.push({freq, num}); // Push the pair (frequency, number)
    }

    // 3. Extract the top K elements from the max heap
    vector<int> result;
    for (int i = 0; i < k; i++) {
        result.push_back(maxHeap.top().second); // Get the number (second element of the pair)
        maxHeap.pop();
    }
    return result;
}

// Approach 2: Using a Min Heap (Priority Queue)
// Time Complexity: O(N log K), where N is the number of elements in the vector
// Space Complexity: O(N + K), N for the hash map, K for the heap
vector<int> topKFrequent_MinHeap(vector<int>& nums, int k) {
    // 1. Count the frequency of each element using a hash map
    unordered_map<int, int> freqMap;
    for (int num : nums) {
        freqMap[num]++;
    }

    // 2. Create a min heap (priority queue) to store pairs of (frequency, element)
    //    We use a min heap of size K.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

    for (auto const& [num, freq] : freqMap) {
        if (minHeap.size() < k) {
            minHeap.push({freq, num});
        } else if (freq > minHeap.top().first) {
            minHeap.pop();
            minHeap.push({freq, num});
        }
    }
    // 3. Extract the top K elements from the min heap
    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().second);
        minHeap.pop();
    }
    reverse(result.begin(), result.end()); // Reverse to get the correct order
    return result;
}

// Approach 3: Using Sorting
// Time Complexity: O(N log N), where N is the number of elements in the vector
// Space Complexity: O(N), for the hash map and the vector of pairs.
vector<int> topKFrequent_Sorting(vector<int>& nums, int k) {
    // 1. Count the frequency of each element using a hash map
    unordered_map<int, int> freqMap;
    for (int num : nums) {
        freqMap[num]++;
    }

    // 2. Store the elements and their frequencies as pairs in a vector
    vector<pair<int, int>> freqVector;
    for (auto const& [num, freq] : freqMap) {
        freqVector.push_back({num, freq});
    }

    // 3. Sort the vector in descending order of frequency
    sort(freqVector.begin(), freqVector.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; // Sort by frequency (second element)
    });

    // 4. Extract the top K elements from the sorted vector
    vector<int> result;
    for (int i = 0; i < k; i++) {
        result.push_back(freqVector[i].first); // Get the number
    }
    return result;
}

// Approach 4: Using a Multimap
// Time Complexity: O(N log N), where N is the number of elements in the vector.  The insertion into the multimap is O(log N)
// Space Complexity: O(N), for the hash map and the multimap.
vector<int> topKFrequent_Multimap(vector<int>& nums, int k) {
    // 1. Count the frequency of each element using a hash map
    unordered_map<int, int> freqMap;
    for (int num : nums) {
        freqMap[num]++;
    }

    // 2. Create a multimap to store frequencies as keys and elements as values.
    //    Multimap automatically sorts by keys (frequencies in this case) in descending order.
    multimap<int, int, greater<int>> freqMultiMap; // Use greater<int> for descending order
    for (auto const& [num, freq] : freqMap) {
        freqMultiMap.insert({freq, num}); // Store frequency as key, number as value
    }

    // 3. Extract the top K elements from the multimap
    vector<int> result;
    auto it = freqMultiMap.begin();
    for (int i = 0; i < k && it != freqMultiMap.end(); ++i, ++it) {
        result.push_back(it->second); // Get the number (value)
    }
    return result;
}

// Approach 5: Using a Bucket Sort
// Time Complexity: O(N), where N is the number of elements in the vector
// Space Complexity: O(N), for the hash map and the vector of buckets.
vector<int> topKFrequent_BucketSort(vector<int>& nums, int k) {
    // 1. Count the frequency of each element using a hash map
    unordered_map<int, int> freqMap;
    for (int num : nums) {
        freqMap[num]++;
    }

    // 2. Create a vector of buckets to store elements based on their frequencies.
    //    The index of the bucket represents the frequency, and the bucket stores a list of elements with that frequency.
    vector<vector<int>> buckets(nums.size() + 1); // Size is nums.size() + 1 because frequency can range from 1 to nums.size()
    for (auto const& [num, freq] : freqMap) {
        buckets[freq].push_back(num); // Place the number in the bucket corresponding to its frequency
    }

    // 3. Iterate through the buckets in reverse order of frequency to get the top K elements
    vector<int> result;
    for (int i = buckets.size() - 1; i >= 0 && result.size() < k; i--) {
        for (int num : buckets[i]) {
            result.push_back(num);
            if (result.size() == k) {
                break; // Stop when we have found k elements
            }
        }
    }
    return result;
}

int main() {
    vector<int> nums = {1, 1, 1, 2, 2, 3};
    int k = 2;

    cout << "Input Array: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
    cout << "K = " << k << endl;

    cout << "\nTop " << k << " Frequent Elements (Max Heap): ";
    vector<int> result1 = topKFrequent_MaxHeap(nums, k);
    for (int num : result1) {
        cout << num << " ";
    }
    cout << endl;

    cout << "\nTop " << k << " Frequent Elements (Min Heap): ";
    vector<int> result2 = topKFrequent_MinHeap(nums, k);
    for (int num : result2) {
        cout << num << " ";
    }
    cout << endl;

    cout << "\nTop " << k << " Frequent Elements (Sorting): ";
    vector<int> result3 = topKFrequent_Sorting(nums, k);
    for (int num : result3) {
        cout << num << " ";
    }
    cout << endl;

    cout << "\nTop " << k << " Frequent Elements (Multimap): ";
    vector<int> result4 = topKFrequent_Multimap(nums, k);
    for (int num : result4) {
        cout << num << " ";
    }
    cout << endl;

    cout << "\nTop " << k << " Frequent Elements (Bucket Sort): ";
    vector<int> result5 = topKFrequent_BucketSort(nums, k);
    for (int num : result5) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

