#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <functional> // Required for std::function

using namespace std;

// Definition for an interval.
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
    // Added for easy comparison in sorting.  Essential for many solutions.
    bool operator<(const Interval& other) const {
        return start < other.start;
    }
    // Added for comparing intervals in the priority queue.  Crucial for the priority queue approach.
     bool operator>(const Interval& other) const {
        return start > other.start;
    }
};

// 1. Sorting Approach
// Time Complexity: O(n log n) for sorting, O(n) for merging.  Overall: O(n log n)
// Space Complexity: O(1) extra space (in-place sort), or O(n) if sorting creates a copy.
vector<Interval> merge1(vector<Interval>& intervals) {
    if (intervals.empty()) return {};

    // Sort the intervals by their start times.  This is crucial.
    sort(intervals.begin(), intervals.end());

    vector<Interval> merged;
    merged.push_back(intervals[0]); // Start with the first interval

    for (int i = 1; i < intervals.size(); ++i) {
        Interval& lastMerged = merged.back(); // Get reference to the last merged interval
        Interval& current = intervals[i];

        if (current.start <= lastMerged.end) {
            // Overlapping intervals:  Extend the end of the last merged interval.
            lastMerged.end = max(lastMerged.end, current.end); // Important:  Take the max of the ends.
        } else {
            // Non-overlapping interval: Add the current interval to the result.
            merged.push_back(current);
        }
    }
    return merged;
}

// 2. Using a Stack (Similar to sorting, but uses a stack)
// Time Complexity: O(n log n) for sorting, O(n) for merging. Overall: O(n log n)
// Space Complexity: O(n) for the stack.
vector<Interval> merge2(vector<Interval>& intervals) {
    if (intervals.empty()) return {};

    sort(intervals.begin(), intervals.end()); // Sort by start time

    stack<Interval> s;
    s.push(intervals[0]);

    for (int i = 1; i < intervals.size(); ++i) {
        Interval top = s.top();
        Interval& current = intervals[i];

        if (current.start <= top.end) {
            // Overlap: Update the end of the top interval on the stack.
            top.end = max(top.end, current.end);
            s.pop();
            s.push(top);
        } else {
            // No overlap: Push the current interval onto the stack.
            s.push(current);
        }
    }

    // Copy the intervals from the stack to a vector.
    vector<Interval> merged;
    while (!s.empty()) {
        merged.push_back(s.top());
        s.pop();
    }
    reverse(merged.begin(), merged.end()); // Stack stores in reverse order, so reverse.
    return merged;
}

// 3. In-place Merging (Destructive, modifies the input)
// Time Complexity: O(n log n) for sorting, O(n) for merging. Overall: O(n log n)
// Space Complexity: O(1) (modifies input in-place)
vector<Interval> merge3(vector<Interval>& intervals) {
    if (intervals.empty()) return {};

    sort(intervals.begin(), intervals.end()); // Sort by start time

    int index = 0; // Index of the last merged interval
    for (int i = 1; i < intervals.size(); ++i) {
        if (intervals[i].start <= intervals[index].end) {
            // Overlap:  Extend the current merged interval.
            intervals[index].end = max(intervals[index].end, intervals[i].end);
        } else {
            // No overlap: Move to the next position and update.
            index++;
            intervals[index] = intervals[i];
        }
    }
    intervals.resize(index + 1); // Resize the vector to remove the extra intervals.
    return intervals;
}

// 4. Using a Priority Queue (More complex, not optimal for this problem, but shows the use of PQ)
// Time Complexity: O(n log n) to insert all intervals into the priority queue, and O(n log n) to extract.  Overall: O(n log n)
// Space Complexity: O(n) for the priority queue.
vector<Interval> merge4(vector<Interval>& intervals) {
    if (intervals.empty()) return {};

    // Use a min-priority queue to store intervals, ordered by start time.
    priority_queue<Interval, vector<Interval>, greater<Interval>> pq; // min heap
    for (const auto& interval : intervals) {
        pq.push(interval);
    }

    vector<Interval> merged;
    while (!pq.empty()) {
        Interval current = pq.top();
        pq.pop();

        if (merged.empty() || current.start > merged.back().end) {
            merged.push_back(current);
        } else {
            merged.back().end = max(merged.back().end, current.end);
        }
    }
    return merged;
}

// 5.  Using std::accumulate (Functional Approach, C++14 and later)
// Time Complexity: O(n log n) due to sorting. The accumulate part is O(n). Overall O(n log n)
// Space Complexity: O(n) for the result vector in the accumulate function.
#include <numeric> // For std::accumulate
vector<Interval> merge5(vector<Interval>& intervals) {
     if (intervals.empty()) return {};

    sort(intervals.begin(), intervals.end()); // Sort is still needed

    //  Use std::accumulate.  The lambda function does the merging.
    vector<Interval> merged = std::accumulate(intervals.begin(), intervals.end(), vector<Interval>{},
        [](vector<Interval> acc, const Interval& interval) {
            if (acc.empty() || interval.start > acc.back().end) {
                acc.push_back(interval);
            } else {
                acc.back().end = max(acc.back().end, interval.end);
            }
            return acc;
        });
    return merged;
}

int main() {
    // Test Cases
    vector<Interval> intervals1 = {{1,3},{2,6},{8,10},{15,18}};
    vector<Interval> intervals2 = {{1,4},{4,5}};
    vector<Interval> intervals3 = {{1,4},{0,4}};
    vector<Interval> intervals4 = {{1,4},{0,0}};
    vector<Interval> intervals5 = {{1,4},{0,2}, {3, 5}};
    vector<Interval> intervals6 = {{2,3},{4,5},{6,7},{8,9},{1,10}};

    // Function pointer to select which merge function to use.
    //  This makes it easy to test different approaches.
    std::function<vector<Interval>(vector<Interval>&)> mergeFunc;

    cout << "Test Case 1: {{1,3},{2,6},{8,10},{15,18}}\n";
    cout << "------------------------------------------\n";
    for (int i = 1; i <= 5; ++i) {
        cout << "Approach " << i << ": ";
        switch (i) {
            case 1: mergeFunc = merge1; break;
            case 2: mergeFunc = merge2; break;
            case 3: mergeFunc = merge3; break;
            case 4: mergeFunc = merge4; break;
            case 5: mergeFunc = merge5; break;
        }
        vector<Interval> result = mergeFunc(intervals1);
        for (const auto& interval : result) {
            cout << "[" << interval.start << "," << interval.end << "] ";
        }
        cout << endl;
    }

    cout << "\nTest Case 2: {{1,4},{4,5}}\n";
    cout << "--------------------------\n";
    for (int i = 1; i <= 5; ++i) {
        cout << "Approach " << i << ": ";
        switch (i) {
            case 1: mergeFunc = merge1; break;
            case 2: mergeFunc = merge2; break;
            case 3: mergeFunc = merge3; break;
            case 4: mergeFunc = merge4; break;
            case 5: mergeFunc = merge5; break;
        }
        vector<Interval> result = mergeFunc(intervals2);
        for (const auto& interval : result) {
            cout << "[" << interval.start << "," << interval.end << "] ";
        }
        cout << endl;
    }

    cout << "\nTest Case 3: {{1,4},{0,4}}\n";
    cout << "--------------------------\n";
     for (int i = 1; i <= 5; ++i) {
        cout << "Approach " << i << ": ";
        switch (i) {
            case 1: mergeFunc = merge1; break;
            case 2: mergeFunc = merge2; break;
            case 3: mergeFunc = merge3; break;
            case 4: mergeFunc = merge4; break;
            case 5: mergeFunc = merge5; break;
        }
        vector<Interval> result = mergeFunc(intervals3);
        for (const auto& interval : result) {
            cout << "[" << interval.start << "," << interval.end << "] ";
        }
        cout << endl;
    }

    cout << "\nTest Case 4: {{1,4},{0,0}}\n";
    cout << "--------------------------\n";
    for (int i = 1; i <= 5; ++i) {
        cout << "Approach " << i << ": ";
        switch (i) {
            case 1: mergeFunc = merge1; break;
            case 2: mergeFunc = merge2; break;
            case 3: mergeFunc = merge3; break;
            case 4: mergeFunc = merge4; break;
            case 5: mergeFunc = merge5; break;
        }
        vector<Interval> result = mergeFunc(intervals4);
        for (const auto& interval : result) {
            cout << "[" << interval.start << "," << interval.end << "] ";
        }
        cout << endl;
    }

    cout << "\nTest Case 5: {{1,4},{0,2}, {3, 5}}\n";
    cout << "--------------------------\n";
    for (int i = 1; i <= 5; ++i) {
        cout << "Approach " << i << ": ";
        switch (i) {
            case 1: mergeFunc = merge1; break;
            case 2: mergeFunc = merge2; break;
            case 3: mergeFunc = merge3; break;
            case 4: mergeFunc = merge4; break;
            case 5: mergeFunc = merge5; break;
        }
        vector<Interval> result = mergeFunc(intervals5);
        for (const auto& interval : result) {
            cout << "[" << interval.start << "," << interval.end << "] ";
        }
        cout << endl;
    }

     cout << "\nTest Case 6: {{2,3},{4,5},{6,7},{8,9},{1,10}}\n";
    cout << "--------------------------\n";
    for (int i = 1; i <= 5; ++i) {
        cout << "Approach " << i << ": ";
        switch (i) {
            case 1: mergeFunc = merge1; break;
            case 2: mergeFunc = merge2; break;
            case 3: mergeFunc = merge3; break;
            case 4: mergeFunc = merge4; break;
            case 5: mergeFunc = merge5; break;
        }
        vector<Interval> result = mergeFunc(intervals6);
        for (const auto& interval : result) {
            cout << "[" << interval.start << "," << interval.end << "] ";
        }
        cout << endl;
    }

    return 0;
}
