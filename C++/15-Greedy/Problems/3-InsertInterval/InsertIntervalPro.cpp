#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> // Required for numeric_limits

// Definition for an interval.  Added for clarity and self-containment.
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

// Function to print intervals (for easier debugging and demonstration)
void printIntervals(const std::vector<Interval>& intervals) {
    std::cout << "[";
    for (size_t i = 0; i < intervals.size(); ++i) {
        std::cout << "[" << intervals[i].start << "," << intervals[i].end << "]";
        if (i < intervals.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "]" << std::endl;
}

// Approach 1: Iterative with Merging (Most Common, Project-Ready)
//
// * Time Complexity: O(n), where n is the number of intervals.
// * Space Complexity: O(n) in the worst case (new intervals vector).
// * Real-world suitability:  Excellent.  This is the most straightforward and
//     efficient approach for general use.  Easy to understand, maintain,
//     and optimize.  Preferred for most projects.
std::vector<Interval> insertInterval_Iterative(std::vector<Interval>& intervals, Interval newInterval) {
    std::vector<Interval> result;
    size_t i = 0;

    // 1. Add intervals occurring before the new interval.
    while (i < intervals.size() && intervals[i].end < newInterval.start) {
        result.push_back(intervals[i]);
        ++i;
    }

    // 2. Merge overlapping intervals.
    while (i < intervals.size() && intervals[i].start <= newInterval.end) {
        newInterval.start = std::min(newInterval.start, intervals[i].start);
        newInterval.end = std::max(newInterval.end, intervals[i].end);
        ++i;
    }

    // 3. Add the merged (or the original if no overlap) new interval.
    result.push_back(newInterval);

    // 4. Add the remaining intervals.
    while (i < intervals.size()) {
        result.push_back(intervals[i]);
        ++i;
    }

    return result;
}

// Approach 2:  In-place Modification (Optimized for Space, Tricky)
//
// * Time Complexity: O(n)
// * Space Complexity: O(1) if allowed to modify the input vector.  O(n) if
//     a copy is made.
// * Real-world suitability: Good for memory-constrained environments, but
//     modifying the input vector in-place can be risky if the caller
//     expects the original vector to remain unchanged.  Less readable
//     than the iterative approach.  Use with caution and clear
//     documentation.
std::vector<Interval> insertInterval_InPlace(std::vector<Interval>& intervals, Interval newInterval) {
    // Create a copy to avoid modifying the original input, if necessary
    // If modifying the input is acceptable, this line can be removed for true O(1) space
    std::vector<Interval> result = intervals; // Make a copy
    size_t i = 0;

    // 1. Skip non-overlapping intervals before newInterval
    while (i < result.size() && result[i].end < newInterval.start) {
        ++i;
    }

    // 2. Merge overlapping intervals
    while (i < result.size() && result[i].start <= newInterval.end) {
        newInterval.start = std::min(newInterval.start, result[i].start);
        newInterval.end = std::max(newInterval.end, result[i].end);
        result.erase(result.begin() + i); // Erase the merged interval
        // Do NOT increment i here, as we've removed an element.  The next
        // element will now be at the current index.
    }

    // 3. Insert the new interval
    result.insert(result.begin() + i, newInterval);

    return result;
}

// Approach 3: Using std::lower_bound (For Sorted Input, Advanced)
//
// * Time Complexity: O(n log n) in the worst case if the insertion into
//       the vector takes O(n).  O(n) if insertion at the end is amortized.
// * Space Complexity: O(n)
// * Real-world suitability:  Useful if the input intervals are *already sorted*
//     or if you can guarantee sorted input.  The `lower_bound` part
//     is efficient, but repeated insertion into a vector can be costly
//     if not at the end.  Good for specialized cases where sorted input
//     is a given.
std::vector<Interval> insertInterval_LowerBound(std::vector<Interval>& intervals, Interval newInterval) {
    std::vector<Interval> result;
    auto it = intervals.begin();

    // 1. Find the insertion point using lower_bound based on start time.
    it = std::lower_bound(intervals.begin(), intervals.end(), newInterval,
                             [](const Interval& a, const Interval& b) { return a.start < b.start; });

    // 2. Insert the new interval at the correct position.
    result.insert(result.end(), intervals.begin(), it);  // copy intervals before insert position
    size_t insertIndex = result.size();
    result.push_back(newInterval); // push newInterval to the back first.

    // 3. Merge overlapping intervals.  Similar to the iterative approach, but
    //    we're working with the 'result' vector now.
    size_t i = insertIndex; // Start merging from the inserted interval's position
    while (i < result.size() -1 && result[i].end >= result[i+1].start)
    {
        result[i].end = std::max(result[i].end, result[i+1].end);
        result.erase(result.begin() + i + 1);
    }
     i = 0;
     while (i < result.size() -1)
    {
        if(result[i].end >= result[i+1].start)
        {
             result[i].end = std::max(result[i].end, result[i+1].end);
             result.erase(result.begin() + i + 1);
        }
        else
            i++;
    }
    // 4. Add the remaining intervals.
    result.insert(result.end(), it, intervals.end());

    return result;
}

// Approach 4: Using a List (Good for Frequent Insertions, Less Common)
//
// * Time Complexity: O(n)
// * Space Complexity: O(n)
// * Real-world suitability:  If you expect *frequent* insertions into the
//     middle of the interval list, `std::list` can be more efficient
//     than `std::vector` because list insertion is O(1).  However, for
//     most cases, `std::vector` is preferred due to cache locality.  Use
//     `std::list` only if you have a specific performance requirement
//     related to insertion frequency.
#include <list>
std::vector<Interval> insertInterval_List(std::vector<Interval>& intervals, Interval newInterval) {
    std::list<Interval> intervalList(intervals.begin(), intervals.end()); // Copy to a list
    std::list<Interval> resultList;
    auto it = intervalList.begin();

    // 1. Add intervals before the overlap
    while (it != intervalList.end() && it->end < newInterval.start) {
        resultList.push_back(*it);
        ++it;
    }

    // 2. Merge overlapping intervals
    while (it != intervalList.end() && it->start <= newInterval.end) {
        newInterval.start = std::min(newInterval.start, it->start);
        newInterval.end = std::max(newInterval.end, it->end);
        it = intervalList.erase(it); // erase and get the next iterator.
    }

    // 3. Add the merged interval
    resultList.push_back(newInterval);

    // 4. Add the remaining intervals
    resultList.insert(resultList.end(), it, intervalList.end());

    return std::vector<Interval>(resultList.begin(), resultList.end()); // Convert back to vector
}

// Approach 5:  Binary Search with Post-Processing (Optimized for Large Datasets, Complex)
//
// * Time Complexity: O(log n + m), where n is the number of intervals, and m is the number of merging steps.
// * Space Complexity: O(n)
// * Real-world suitability: This approach is optimized for *very large* datasets
//     where the initial search for the insertion point needs to be fast.  It's
//     more complex than the iterative approach, so it's best suited for
//     performance-critical applications where the input size justifies the
//     added complexity.  Requires the input intervals to be sorted.
std::vector<Interval> insertInterval_BinarySearch(std::vector<Interval>& intervals, Interval newInterval) {
    std::vector<Interval> result;
    int left = 0, right = intervals.size() - 1;
    int insertPos = intervals.size(); // Default: insert at the end

    // 1. Binary search to find the insertion point (optimized for large datasets)
    while (left <= right) {
        int mid = left + (right - left) / 2; // Prevent overflow
        if (intervals[mid].start > newInterval.end) {
            insertPos = mid;
            right = mid - 1;
        } else if (intervals[mid].end < newInterval.start) {
            left = mid + 1;
        } else {
            // Overlap found during binary search!  Merge immediately, and this becomes
            // the newInterval.  Then, continue searching for *earlier* overlaps.
            newInterval.start = std::min(newInterval.start, intervals[mid].start);
            newInterval.end = std::max(newInterval.end, intervals[mid].end);
            insertPos = mid; // Mark this position as a potential insertion point
            right = mid - 1;  // Continue searching for earlier overlaps
        }
    }

    // 2. Add intervals before the insertion point
    result.insert(result.end(), intervals.begin(), intervals.begin() + insertPos);
    result.push_back(newInterval); // Insert the new (potentially merged) interval

    // 3.  Merge forward.  We might have already merged some in the binary search
    //      if we encountered overlaps *during* the search.  This loop handles
    //      any remaining merges *after* the insertion.
    size_t i = insertPos + 1;
    while (i < intervals.size() && result.back().end >= intervals[i].start) {
        result.back().end = std::max(result.back().end, intervals[i].end);
        ++i;
    }
    // 4. Add the remaining intervals.
    result.insert(result.end(), intervals.begin() + i, intervals.end());
    return result;
}

int main() {
    // Example usage of each approach
    std::vector<Interval> intervals1 = {{1, 3}, {6, 9}};
    Interval newInterval1 = {2, 5};
    std::cout << "Approach 1 (Iterative):" << std::endl;
    printIntervals(insertInterval_Iterative(intervals1, newInterval1));

    std::vector<Interval> intervals2 = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    Interval newInterval2 = {4, 8};
    std::cout << "Approach 2 (In-Place):" << std::endl;
    std::vector<Interval> result2 = insertInterval_InPlace(intervals2, newInterval2);
    printIntervals(result2);
    std::cout << "Original intervals2 (modified in-place):" << std::endl;
    printIntervals(intervals2);

    std::vector<Interval> intervals3 = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    Interval newInterval3 = {4, 8};
    std::cout << "Approach 3 (Lower Bound):" << std::endl;
    printIntervals(insertInterval_LowerBound(intervals3, newInterval3));

     std::vector<Interval> intervals4 = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    Interval newInterval4 = {4, 8};
    std::cout << "Approach 4 (List):" << std::endl;
    printIntervals(insertInterval_List(intervals4, newInterval4));

    std::vector<Interval> intervals5 = {{1, 3}, {6, 9}};
    Interval newInterval5 = {2, 5};
    std::cout << "Approach 5 (Binary Search):" << std::endl;
    printIntervals(insertInterval_BinarySearch(intervals5, newInterval5));

    std::vector<Interval> intervals6 = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    Interval newInterval6 = {4, 8};
    std::cout << "Approach 5 (Binary Search, complex case):" << std::endl;
    printIntervals(insertInterval_BinarySearch(intervals6, newInterval6));

    std::vector<Interval> intervals7 = {{1, 3}, {6, 9}};
    Interval newInterval7 = {10, 12};
    std::cout << "Approach 5 (Binary Search, insert at the end):" << std::endl;
    printIntervals(insertInterval_BinarySearch(intervals7, newInterval7));

    std::vector<Interval> intervals8 = {{1, 3}, {6, 9}};
     Interval newInterval8 = {0, 1};
     std::cout << "Approach 5 (Binary Search, insert at the beginning):" << std::endl;
     printIntervals(insertInterval_BinarySearch(intervals8, newInterval8));

    return 0;
}
