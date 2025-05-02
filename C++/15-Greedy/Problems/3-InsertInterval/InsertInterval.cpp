#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> // Required for numeric_limits

using namespace std;

// Definition for an interval.
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
    // Added for easier comparison and sorting.  Essential for many solutions.
    bool operator<(const Interval& other) const {
        return start < other.start;
    }
};

// Function to merge overlapping intervals.  Used by several solutions.
vector<Interval> mergeIntervals(vector<Interval>& intervals) {
    if (intervals.empty()) {
        return {}; // Return empty vector for empty input
    }

    // Sort intervals by start time.  Crucial for merging.
    sort(intervals.begin(), intervals.end());

    vector<Interval> mergedIntervals;
    mergedIntervals.push_back(intervals[0]); // Start with the first interval

    for (size_t i = 1; i < intervals.size(); ++i) {
        Interval& current = intervals[i];
        Interval& lastMerged = mergedIntervals.back();

        if (current.start <= lastMerged.end) {
            // Overlapping, so merge
            lastMerged.end = max(lastMerged.end, current.end); // Extend the end
        } else {
            // Non-overlapping, add the current interval
            mergedIntervals.push_back(current);
        }
    }
    return mergedIntervals;
}

// Approach 1: Iterative with Merging (Clear and Concise)
// Time Complexity: O(n log n) due to sorting, O(n) for merging.  Overall: O(n log n)
// Space Complexity: O(n) for the merged intervals (worst case).
vector<Interval> insertInterval_approach1(vector<Interval>& intervals, Interval newInterval) {
    intervals.push_back(newInterval); // Add first, then merge
    return mergeIntervals(intervals);  // Reuse the mergeIntervals function
}

// Approach 2: Iterative with In-Place Modification (Optimized Space)
// Time Complexity: O(n log n) due to sorting, O(n) for the in-place merging. Overall: O(n log n)
// Space Complexity: O(1) extra space (modifies the input vector directly, excluding the result vector).
vector<Interval> insertInterval_approach2(vector<Interval>& intervals, Interval newInterval) {
    // 1. Insert the new interval into the correct sorted position.
    auto insertIt = lower_bound(intervals.begin(), intervals.end(), newInterval);
    intervals.insert(insertIt, newInterval);

    // 2. Merge overlapping intervals in-place.
    vector<Interval> result;
    result.push_back(intervals[0]);

    for (size_t i = 1; i < intervals.size(); ++i) {
        Interval& current = intervals[i];
        Interval& lastMerged = result.back();

        if (current.start <= lastMerged.end) {
            lastMerged.end = max(lastMerged.end, current.end);
        } else {
            result.push_back(current);
        }
    }
    return result;
}

// Approach 3: Without Sorting (Less Efficient, Demonstrative)
// Time Complexity: O(n^2) in the worst case (inserting and merging can both be O(n) in a loop).
// Space Complexity: O(n) for the merged intervals.
vector<Interval> insertInterval_approach3(vector<Interval>& intervals, Interval newInterval) {
    vector<Interval> mergedIntervals;

    // 1. Iterate through original intervals, merging as we go
    bool inserted = false;
    for (const auto& interval : intervals) {
        if (!inserted) {
            if (newInterval.end < interval.start) {
                // newInterval comes before current interval
                mergedIntervals.push_back(newInterval);
                mergedIntervals.push_back(interval);
                inserted = true;
                continue;
            } else if (newInterval.start > interval.end) {
                // newInterval comes after current interval
                mergedIntervals.push_back(interval);
                continue;
            } else {
                // Overlap, merge with newInterval
                newInterval.start = min(newInterval.start, interval.start);
                newInterval.end = max(newInterval.end, interval.end);
                continue; // Don't add the original interval
            }
        }
        mergedIntervals.push_back(interval); //if inserted, add the rest of intervals.
    }

    if (!inserted) {
        mergedIntervals.push_back(newInterval); // Add newInterval if it wasn't inserted
    }
    return mergeIntervals(mergedIntervals); // Use mergeIntervals to handle any remaining overlaps
}

// Approach 4:  More Detailed Iteration (Handles Edge Cases Explicitly)
// Time Complexity: O(n), assuming the input 'intervals' is already sorted. If not sorted, O(n log n).
// Space Complexity: O(n) for the result vector.
vector<Interval> insertInterval_approach4(vector<Interval>& intervals, Interval newInterval) {
    vector<Interval> result;
    size_t i = 0;

    // 1. Add intervals occurring before the newInterval
    while (i < intervals.size() && intervals[i].end < newInterval.start) {
        result.push_back(intervals[i]);
        ++i;
    }

    // 2. Merge overlapping intervals
    while (i < intervals.size() && intervals[i].start <= newInterval.end) {
        newInterval.start = min(newInterval.start, intervals[i].start);
        newInterval.end = max(newInterval.end, intervals[i].end);
        ++i;
    }
    result.push_back(newInterval); // Add the merged interval

    // 3. Add the remaining intervals
    while (i < intervals.size()) {
        result.push_back(intervals[i]);
        ++i;
    }
    return result;
}

// Approach 5: Using std::lower_bound and std::upper_bound (C++ Standard Library)
// Time Complexity: O(n log n)  due to sorting. lower_bound and upper_bound are O(log n) each.
// Space Complexity: O(n) for the result vector.
vector<Interval> insertInterval_approach5(vector<Interval>& intervals, Interval newInterval) {
    vector<Interval> result;

    // 1. Find the insertion point using lower_bound (for start)
    auto start_it = lower_bound(intervals.begin(), intervals.end(), newInterval);
    size_t start_index = distance(intervals.begin(), start_it);

    // 2. Add non-overlapping intervals before the merge
    for (size_t i = 0; i < start_index; ++i) {
        result.push_back(intervals[i]);
    }

    // 3. Find the end of the overlapping intervals using upper_bound (for end)
    auto end_it = upper_bound(intervals.begin() + start_index, intervals.end(), newInterval,
                              [](const Interval& a, const Interval& b) { return a.end < b.end; });
    size_t end_index = distance(intervals.begin(), end_it);

    // 4. Merge overlapping intervals
    for (size_t i = start_index; i < end_index; ++i) {
        newInterval.start = min(newInterval.start, intervals[i].start);
        newInterval.end = max(newInterval.end, intervals[i].end);
    }
    result.push_back(newInterval);

    // 5. Add non-overlapping intervals after the merge
    for (size_t i = end_index; i < intervals.size(); ++i) {
        result.push_back(intervals[i]);
    }
    return result;
}

// Function to print intervals (helper function)
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

int main() {
    // Example usage
    vector<Interval> intervals = {{1, 3}, {6, 9}};
    Interval newInterval = {2, 5};

    cout << "Original Intervals: ";
    printIntervals(intervals);
    cout << "New Interval: [" << newInterval.start << "," << newInterval.end << "]" << endl;

    // Approach 1
    vector<Interval> result1 = insertInterval_approach1(intervals, newInterval);
    cout << "Approach 1: ";
    printIntervals(result1);

    // Approach 2
    vector<Interval> result2 = insertInterval_approach2(intervals, newInterval);
    cout << "Approach 2: ";
    printIntervals(result2);

    // Approach 3
    vector<Interval> result3 = insertInterval_approach3(intervals, newInterval);
    cout << "Approach 3: ";
    printIntervals(result3);

    // Approach 4
    vector<Interval> result4 = insertInterval_approach4(intervals, newInterval);
    cout << "Approach 4: ";
    printIntervals(result4);

     // Approach 5
    vector<Interval> result5 = insertInterval_approach5(intervals, newInterval);
    cout << "Approach 5: ";
    printIntervals(result5);

    return 0;
}
