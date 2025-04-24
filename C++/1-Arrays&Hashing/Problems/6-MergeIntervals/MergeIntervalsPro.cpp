#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <tuple>
#include <limits>
#include <functional> // Include for std::function and std::greater

using namespace std;

// Definition for an interval.
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}

    // Add this operator> for use with std::greater in the priority queue
    bool operator>(const Interval& other) const {
        return start > other.start; // Compare based on start time for min-heap
    }
};

// Function to print a vector of intervals
void printIntervals(const vector<Interval>& intervals) {
    cout << "[";
    for (size_t i = 0; i < intervals.size(); ++i) {
        cout << "[" << intervals[i].start << "," << intervals[i].end << "]";
        if (i < intervals.size() - 1) {
            cout << ",";
        }
    }
    cout << "]" << endl;
}

// Approach 1: Sorting and Merging (Greedy)
// Time Complexity: O(n log n) for sorting, O(n) for merging.  Overall: O(n log n)
// Space Complexity: O(1) if sorting in place, O(n) otherwise (depending on sort implementation).
//
// Real-world application:
// - Calendar event management: Merging overlapping appointments to optimize schedule.
// - Resource scheduling: Combining overlapping time slots for resource allocation (e.g., meeting rooms, equipment).
vector<Interval> mergeIntervals_Sorting(vector<Interval>& intervals) {
    if (intervals.empty()) return {};

    // 1. Sort the intervals by start time.  Using a lambda for custom comparison.
    sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
        return a.start < b.start;
    });

    // 2. Iterate through the sorted intervals and merge overlapping ones.
    vector<Interval> mergedIntervals;
    Interval currentInterval = intervals[0]; // Initialize with the first interval.

    for (size_t i = 1; i < intervals.size(); ++i) {
        if (intervals[i].start <= currentInterval.end) {
            // Overlapping interval found: Extend the current interval's end.
            currentInterval.end = max(currentInterval.end, intervals[i].end); // Important:  Take the max of the ends.
        } else {
            // Non-overlapping interval: Add the current interval to the result and update currentInterval.
            mergedIntervals.push_back(currentInterval);
            currentInterval = intervals[i];
        }
    }
    // 3. Add the last interval to the result.  Crucial!
    mergedIntervals.push_back(currentInterval);
    return mergedIntervals;
}

// Approach 2: Using Stack
// Time Complexity: O(n log n) for sorting, O(n) for merging. Overall: O(n log n)
// Space Complexity: O(n) for the stack.
//
// Real-world application:
// - Text editor:  Handling multiple undo/redo operations that involve changes over ranges of text.  Merging sequential changes.
vector<Interval> mergeIntervals_Stack(vector<Interval>& intervals) {
    if (intervals.empty()) return {};

    // 1. Sort intervals by start time
    sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
        return a.start < b.start;
    });

    // 2. Use a stack to keep track of merged intervals
    stack<Interval> mergedStack;
    mergedStack.push(intervals[0]); // Push the first interval onto the stack

    for (size_t i = 1; i < intervals.size(); ++i) {
        Interval top = mergedStack.top();
        if (intervals[i].start <= top.end) {
            // Overlapping interval:  Update the end of the top interval on the stack.
            top.end = max(top.end, intervals[i].end);
            mergedStack.pop();
            mergedStack.push(top);
        } else {
            // Non-overlapping interval: Push the current interval onto the stack.
            mergedStack.push(intervals[i]);
        }
    }

    // 3. Pop the intervals from the stack and store them in a vector.
    vector<Interval> mergedIntervals;
    while (!mergedStack.empty()) {
        mergedIntervals.push_back(mergedStack.top());
        mergedStack.pop();
    }
    reverse(mergedIntervals.begin(), mergedIntervals.end()); // Reverse to get the correct order.
    return mergedIntervals;
}

// Approach 3: Priority Queue (Min-Heap)
// Time Complexity: O(n log n) for building the heap and extracting elements.
// Space Complexity: O(n) for the priority queue.
//
// Real-world application:
// - Meeting scheduling with priorities:  Intervals represent meeting requests with priorities (start time).  Merge and schedule based on priority and availability.
vector<Interval> mergeIntervals_PriorityQueue(vector<Interval>& intervals) {
    if (intervals.empty()) return {};

    // 1. Create a min-heap (priority queue) based on start times.  Use std::greater for min-heap.
    priority_queue<Interval, vector<Interval>, std::greater<Interval>> pq;

    // 2. Push all intervals into the priority queue.
    for (const auto& interval : intervals) {
        pq.push(interval);
    }

    // 3. Merge intervals from the priority queue.
    vector<Interval> mergedIntervals;
    Interval currentInterval = pq.top();
    pq.pop();

    while (!pq.empty()) {
        Interval nextInterval = pq.top();
        pq.pop();
        if (nextInterval.start <= currentInterval.end) {
            currentInterval.end = max(currentInterval.end, nextInterval.end);
        } else {
            mergedIntervals.push_back(currentInterval);
            currentInterval = nextInterval;
        }
    }
    mergedIntervals.push_back(currentInterval); // Add the last interval.
    return mergedIntervals;
}

// Approach 4: Using a Vector of Tuples (Start, End, Original Index)
// Time Complexity: O(n log n) for sorting, O(n) for merging. Overall: O(n log n)
// Space Complexity: O(n) for the vector of tuples.
//
// Real-world application:
//   -  Data analysis:  Merging time ranges of events, while preserving the original order or source of the events using the index.
vector<Interval> mergeIntervals_Tuples(vector<Interval>& intervals) {
    if (intervals.empty()) return {};

    // 1. Create a vector of tuples: (start, end, original index).
    vector<tuple<int, int, int>> intervalTuples;
    for (size_t i = 0; i < intervals.size(); ++i) {
        intervalTuples.emplace_back(intervals[i].start, intervals[i].end, i); // Store original index
    }

    // 2. Sort the tuples based on the start time.
    sort(intervalTuples.begin(), intervalTuples.end(), [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
        return get<0>(a) < get<0>(b); // Compare based on the first element (start).
    });

    // 3. Merge the intervals represented by the tuples.
    vector<Interval> mergedIntervals;
    int currentStart = get<0>(intervalTuples[0]);
    int currentEnd = get<1>(intervalTuples[0]);

    for (size_t i = 1; i < intervalTuples.size(); ++i) {
        int nextStart = get<0>(intervalTuples[i]);
        int nextEnd = get<1>(intervalTuples[i]);
        if (nextStart <= currentEnd) {
            currentEnd = max(currentEnd, nextEnd);
        } else {
            mergedIntervals.emplace_back(currentStart, currentEnd);
            currentStart = nextStart;
            currentEnd = nextEnd;
        }
    }
    mergedIntervals.emplace_back(currentStart, currentEnd); // Add the last interval.
    return mergedIntervals;
}

// Approach 5: In-Place Merging (for when input array can be modified) - Tricky and Efficient
// Time Complexity: O(n log n) for sorting, O(n) for merging. Overall: O(n log n)
// Space Complexity: O(1) -  Modifies the input array in-place.
//
// Real-world application:
//  -  Optimizing memory usage in embedded systems:  Merging intervals directly in a memory-constrained environment where creating new arrays is expensive.
vector<Interval> mergeIntervals_InPlace(vector<Interval>& intervals) {
    if (intervals.empty()) return {};

    // 1. Sort the intervals by start time.
    sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
        return a.start < b.start;
    });

    // 2. In-place merging.  Use 'i' to track the merged interval's position.
    int i = 0; // Index of the last merged interval
    for (int j = 1; j < intervals.size(); ++j) {
        if (intervals[j].start <= intervals[i].end) {
            // Overlap: Extend the current merged interval in-place.
            intervals[i].end = max(intervals[i].end, intervals[j].end);
        } else {
            // No overlap: Move the next non-overlapping interval to the correct position.
            i++; // Move 'i' to the next position.
            intervals[i] = intervals[j]; // Copy the non-overlapping interval to position 'i'.
        }
    }
    // 3.  Resize the vector to remove the extra intervals at the end.
    intervals.resize(i + 1); // 'i' is 0-indexed, so the size is i+1.
    return intervals;
}

int main() {
    // Example usage of the mergeIntervals functions
    vector<Interval> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    cout << "Original Intervals: ";
    printIntervals(intervals);

    cout << "\nApproach 1: Sorting and Merging" << endl;
    vector<Interval> merged1 = mergeIntervals_Sorting(intervals);
    printIntervals(merged1);

    cout << "\nApproach 2: Using Stack" << endl;
    vector<Interval> merged2 = mergeIntervals_Stack(intervals); // Use original intervals
    printIntervals(merged2);

    cout << "\nApproach 3: Priority Queue" << endl;
    vector<Interval> merged3 = mergeIntervals_PriorityQueue(intervals); // Use original intervals
    printIntervals(merged3);

    cout << "\nApproach 4: Using Tuples" << endl;
    vector<Interval> merged4 = mergeIntervals_Tuples(intervals);
    printIntervals(merged4);

    cout << "\nApproach 5: In-Place Merging" << endl;
    vector<Interval> intervals5 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}}; // Create a *copy* for in-place modification!
    vector<Interval> merged5 = mergeIntervals_InPlace(intervals5);
    printIntervals(merged5);
    cout << "Modified Original (In-Place): ";
    printIntervals(intervals5); // Show the modified vector.

    return 0;
}
