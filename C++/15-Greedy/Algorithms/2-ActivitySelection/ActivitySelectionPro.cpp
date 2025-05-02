#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <numeric> // For std::iota

using namespace std;

// Structure to represent an activity
struct Activity {
    int start;
    int finish;
    int index; // To keep track of the original index
};

// Function to print the selected activities
void printSelectedActivities(const vector<Activity>& activities, const vector<int>& selected) {
    cout << "Selected activities: ";
    for (int i : selected) {
        cout << activities[i].index << " "; // Print original indices
    }
    cout << endl;
}

// 1. Greedy Approach: Sort by finish times (Most Common)
//   - Sort activities by finish times.
//   - Select the first activity.
//   - Iterate through the remaining activities, selecting those that
//     don't overlap with the previously selected activity.
vector<int> greedyActivitySelection(vector<Activity>& activities) {
    // Custom comparator for sorting activities by finish times
    auto compareByFinishTime = [](const Activity& a, const Activity& b) {
        return a.finish < b.finish;
    };

    // Sort the activities by finish times
    sort(activities.begin(), activities.end(), compareByFinishTime);

    vector<int> selectedActivities;
    selectedActivities.push_back(activities[0].index); // Select the first activity
    int lastFinishTime = activities[0].finish;

    // Iterate through the remaining activities
    for (int i = 1; i < activities.size(); ++i) {
        if (activities[i].start >= lastFinishTime) {
            // If the activity doesn't overlap, select it
            selectedActivities.push_back(activities[i].index);
            lastFinishTime = activities[i].finish;
        }
    }
    return selectedActivities;
}

// 2. Greedy Approach: Sort by start times (Incorrect but illustrative)
//    - Sort activities by start times.
//    - This approach is generally incorrect for the standard activity selection problem
//      as it doesn't guarantee the maximum number of non-overlapping activities.
//    - It's included here for demonstration and comparison.  It will often give a
//      valid, but suboptimal, solution.
vector<int> greedyActivitySelectionByStartTime(vector<Activity>& activities) {
    // Custom comparator for sorting activities by start times
    auto compareByStartTime = [](const Activity& a, const Activity& b) {
        return a.start < b.start;
    };

    // Sort the activities by start times
    sort(activities.begin(), activities.end(), compareByStartTime);

    vector<int> selectedActivities;
    selectedActivities.push_back(activities[0].index); // Select the first activity
    int lastFinishTime = activities[0].finish;

    // Iterate through the remaining activities
    for (int i = 1; i < activities.size(); ++i) {
        if (activities[i].start >= lastFinishTime) {
            // If the activity doesn't overlap, select it
            selectedActivities.push_back(activities[i].index);
            lastFinishTime = activities[i].finish;
        }
    }
    return selectedActivities;
}

// 3. Recursive Approach
//   - A recursive approach to solve the activity selection problem.
//   - It explores all possible combinations of activities to find the
//     maximum set of non-overlapping activities.
//   - This approach is less efficient than the greedy approach (Approach 1) but
//     provides a different way to understand the problem.
int recursiveActivitySelection(const vector<Activity>& activities, int k, int lastFinishTime, vector<int>& selectedActivities) {
    int n = activities.size();
    int maxActivities = 0;

    for (int i = k; i < n; ++i) {
        if (activities[i].start >= lastFinishTime) {
            // Include current activity
            selectedActivities.push_back(activities[i].index);
            // Recursively call for the remaining activities
            int count = 1 + recursiveActivitySelection(activities, i + 1, activities[i].finish, selectedActivities);
            maxActivities = max(maxActivities, count);
            selectedActivities.pop_back(); // Backtrack: remove the activity to explore other possibilities
        }
    }
    return maxActivities;
}

// 4. Dynamic Programming Approach
//    - Solves the activity selection problem using dynamic programming.
//    - It builds a table to store the maximum number of non-overlapping activities
//      that can be selected up to a certain point.
//    - This approach is more efficient than the recursive approach but may use
//      more memory.
vector<int> dynamicProgrammingActivitySelection(vector<Activity>& activities) {
    int n = activities.size();
    // Sort by finish times (DP approach also requires sorted activities)
    sort(activities.begin(), activities.end(), [](const Activity& a, const Activity& b) {
        return a.finish < b.finish;
    });

    vector<int> dp(n); // dp[i] stores the max activities up to index i
    vector<int> last(n); // last[i] stores the index of the last activity included before i

    dp[0] = 1; // Base case: first activity is always selected
    last[0] = -1;

    for (int i = 1; i < n; ++i) {
        int j = i - 1;
        // Find the latest non-overlapping activity
        while (j >= 0 && activities[j].finish > activities[i].start) {
            j--;
        }
        if (j >= 0) {
            // If a non-overlapping activity is found
            if (dp[j] + 1 > dp[i - 1])
            {
                dp[i] = dp[j] + 1;
                last[i] = j;
            }
            else
            {
                dp[i] = dp[i-1];
                last[i] = last[i-1];
            }
        } else {
            // If no non-overlapping activity is found
            dp[i] = max(1, dp[i - 1]); // either take current activity or previous best
            last[i] = (dp[i] == 1) ? -1 : last[i-1];
        }
    }

    // Backtrack to find the selected activities
    vector<int> selectedActivities;
    int i = n - 1;
    while (i >= 0 && last[i] != -1) {
        if (dp[i] != (i > 0 ? dp[i-1] : 0))
        {
            selectedActivities.push_back(activities[i].index);
            i = last[i];
        }
        else
            i--;
    }
    if (i == 0 && dp[0] == 1)
        selectedActivities.push_back(activities[0].index);
    reverse(selectedActivities.begin(), selectedActivities.end()); // Reverse to get correct order
    return selectedActivities;
}

// 5. Using Priority Queue (for activities with weights - but adapted for this problem)
//    -  This approach can be adapted for the basic activity selection (without weights)
//    -  It's more commonly used when activities have weights or priorities.
//    -  Here, we adapt it to select activities based on finish times, similar to the
//       greedy approach, but using a priority queue.  This is not the most efficient
//       way to do standard activity selection, but it demonstrates how a priority
//       queue *could* be used in a related, more complex, scenario.
vector<int> priorityQueueActivitySelection(vector<Activity>& activities) {
    // Custom comparator for the priority queue (sort by finish times - ascending)
    auto compareByFinishTimePQ = [](const Activity& a, const Activity& b) {
        return a.finish > b.finish; // Changed to > for min-heap (smallest finish time at top)
    };

    // Create a priority queue (min-heap)
    priority_queue<Activity, vector<Activity>, decltype(compareByFinishTimePQ)> pq(compareByFinishTimePQ);

    // Push all activities into the priority queue
    for (const auto& activity : activities) {
        pq.push(activity);
    }

    vector<int> selectedActivities;
    if (pq.empty()) return selectedActivities;

    Activity currentActivity = pq.top();
    pq.pop();
    selectedActivities.push_back(currentActivity.index);
    int lastFinishTime = currentActivity.finish;


    while (!pq.empty()) {
        Activity nextActivity = pq.top();
        pq.pop();
        if (nextActivity.start >= lastFinishTime) {
            selectedActivities.push_back(nextActivity.index);
            lastFinishTime = nextActivity.finish;
        }
    }
    return selectedActivities;
}

int main() {
    // Example activities (start and finish times)
    vector<Activity> activities = {
        {1, 2, 1},  // Activity 1
        {3, 4, 2},  // Activity 2
        {0, 6, 3},  // Activity 3
        {5, 7, 4},  // Activity 4
        {8, 9, 5},  // Activity 5
        {5, 9, 6}, // Activity 6
        {6, 10, 7}, // Activity 7
        {8, 11, 8}, // Activity 8
        {12, 16, 9}, // Activity 9
        {14, 18, 10}  // Activity 10
    };

    cout << "Activity Selection Problem" << endl;
    cout << "--------------------------" << endl;

    // 1. Greedy Approach: Sort by finish times
    cout << "1. Greedy Approach (Sort by finish times):" << endl;
    vector<int> selectedActivities1 = greedyActivitySelection(activities);
    printSelectedActivities(activities, selectedActivities1);
    cout << endl;

    // 2. Greedy Approach: Sort by start times (Incorrect)
    cout << "2. Greedy Approach (Sort by start times - INCORRECT):" << endl;
    vector<int> selectedActivities2 = greedyActivitySelectionByStartTime(activities);
    printSelectedActivities(activities, selectedActivities2);
    cout << endl;

    // 3. Recursive Approach
    cout << "3. Recursive Approach:" << endl;
    vector<int> selectedActivities3;
    int maxActivities = recursiveActivitySelection(activities, 0, 0, selectedActivities3);
    // Need to find a way to print the activities selected in the recursive calls, the function
    // only returns the count.
    cout << "Maximum activities selected: " << maxActivities << endl;
    // The selectedActivities3 vector inside the recursive function does not hold the final set
    // of selected activities in the main function.  The recursive calls create their own vectors.
    cout << "Selected Activities (Recursive -  Partial/Incorrect): ";
    for (int i = 0; i < selectedActivities3.size(); ++i)
        cout << selectedActivities3[i] << " ";
    cout << endl << endl;


    // 4. Dynamic Programming Approach
    cout << "4. Dynamic Programming Approach:" << endl;
    vector<int> selectedActivities4 = dynamicProgrammingActivitySelection(activities);
    printSelectedActivities(activities, selectedActivities4);
    cout << endl;

    // 5. Using Priority Queue
    cout << "5. Using Priority Queue:" << endl;
    vector<int> selectedActivities5 = priorityQueueActivitySelection(activities);
    printSelectedActivities(activities, selectedActivities5);
    cout << endl;

    return 0;
}

