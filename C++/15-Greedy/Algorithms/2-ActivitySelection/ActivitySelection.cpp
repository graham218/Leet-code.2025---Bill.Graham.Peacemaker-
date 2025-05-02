#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional> // Required for greater<>

using namespace std;

// Structure to represent an activity
struct Activity {
    int start;
    int finish;
    int index; // Keep track of the original index
};

// Function to print the selected activities
void printSelectedActivities(const vector<Activity>& activities, const vector<int>& selected) {
    cout << "Selected activities: ";
    for (int i = 0; i < selected.size(); ++i) {
        cout << activities[selected[i]].index << " "; // Print original indices
    }
    cout << endl;
}

// 1. Greedy Approach 1: Sort by finish time (MOST COMMON and EFFICIENT)
// Sort activities by finish time and select the next activity with start time >= finish time of the previously selected activity.
void activitySelection_FinishTime(vector<Activity>& activities) {
    // Custom comparator for sorting by finish time (ascending order)
    auto compareByFinishTime = [](const Activity& a, const Activity& b) {
        return a.finish < b.finish;
    };

    // Sort the activities by finish time
    sort(activities.begin(), activities.end(), compareByFinishTime);

    int n = activities.size();
    vector<int> selectedActivities;
    selectedActivities.push_back(0); // Select the first activity (after sorting)

    int lastFinishTime = activities[0].finish; // Finish time of the last selected activity

    for (int i = 1; i < n; ++i) {
        if (activities[i].start >= lastFinishTime) {
            selectedActivities.push_back(i); // Select this activity
            lastFinishTime = activities[i].finish; // Update lastFinishTime
        }
    }

    printSelectedActivities(activities, selectedActivities);
}

// 2. Greedy Approach 2: Sort by start time
// Sort activities by start time and select activities that don't overlap.  This is NOT optimal.
void activitySelection_StartTime(vector<Activity>& activities) {
    // Sort by start time (ascending order)
    sort(activities.begin(), activities.end(), [](const Activity& a, const Activity& b) {
        return a.start < b.start;
    });

    int n = activities.size();
    vector<int> selectedActivities;
    selectedActivities.push_back(0); // Select the first activity (after sorting)
    int lastFinishTime = activities[0].finish;

    for (int i = 1; i < n; ++i) {
        if (activities[i].start >= lastFinishTime) {
            selectedActivities.push_back(i);
            lastFinishTime = activities[i].finish;
        }
    }

    printSelectedActivities(activities, selectedActivities);
    //This approach is NOT optimal.
}

// 3. Greedy Approach 3: Sort by activity duration (finish - start)
// Sort activities by duration and select the shortest activities that don't overlap.  This is NOT optimal.
void activitySelection_Duration(vector<Activity>& activities) {
    // Sort by duration (ascending order)
    sort(activities.begin(), activities.end(), [](const Activity& a, const Activity& b) {
        return (a.finish - a.start) < (b.finish - b.start);
    });

    int n = activities.size();
    vector<int> selectedActivities;
    selectedActivities.push_back(0);
    int lastFinishTime = activities[0].finish;

    for (int i = 1; i < n; ++i) {
        if (activities[i].start >= lastFinishTime) {
            selectedActivities.push_back(i);
            lastFinishTime = activities[i].finish;
        }
    }

    printSelectedActivities(activities, selectedActivities);
    //This approach is NOT optimal.
}

// 4. Greedy Approach 4: Sort by Latest Start Time
void activitySelection_LatestStartTime(vector<Activity>& activities) {
    // Sort activities by start time in descending order (latest start time first)
    sort(activities.begin(), activities.end(), [](const Activity& a, const Activity& b) {
        return a.start > b.start;
    });

    int n = activities.size();
    vector<int> selectedActivities;
    selectedActivities.push_back(0); // Select the first activity (which has the latest start time after sorting)
    int lastFinishTime = activities[0].finish;

    for (int i = 1; i < n; ++i) {
        if (activities[i].start >= lastFinishTime) {
            selectedActivities.push_back(i);
            lastFinishTime = activities[i].finish;
        }
    }
    printSelectedActivities(activities, selectedActivities);
    // This approach is NOT optimal
}

// 5. Using Priority Queue (Sort by finish time using a min-heap)
void activitySelection_PriorityQueue(vector<Activity>& activities) {
    // Create a min-heap based on finish times.
    priority_queue<Activity, vector<Activity>, function<bool(const Activity&, const Activity&)>>
        pq([](const Activity& a, const Activity& b) { return a.finish > b.finish; });

    // Push all activities into the priority queue.
    for (const auto& activity : activities) {
        pq.push(activity);
    }

    vector<int> selectedActivities;
    Activity currentActivity = pq.top();
    pq.pop();
    selectedActivities.push_back(currentActivity.index-1); // Store the index.  Adjust for the original input.
    int lastFinishTime = currentActivity.finish;

    while (!pq.empty()) {
        Activity nextActivity = pq.top();
        pq.pop();
        if (nextActivity.start >= lastFinishTime) {
            selectedActivities.push_back(nextActivity.index-1); // Store the index
            lastFinishTime = nextActivity.finish;
        }
    }
    printSelectedActivities(activities, selectedActivities);
}

int main() {
    // Example activities (start, finish, index)
    vector<Activity> activities = {
        {5, 9, 1},
        {1, 2, 2},
        {3, 4, 3},
        {0, 6, 4},
        {5, 7, 5},
        {8, 9, 6}
    };

    cout << "Activity Selection Problem" << endl;
    cout << "--------------------------" << endl;

    cout << "\n1. Greedy Approach (Sort by finish time):" << endl;
    vector<Activity> activities1 = activities; // Create a copy for each approach
    activitySelection_FinishTime(activities1);

    cout << "\n2. Greedy Approach (Sort by start time):" << endl;
    vector<Activity> activities2 = activities;
    activitySelection_StartTime(activities2); // Not optimal

    cout << "\n3. Greedy Approach (Sort by duration):" << endl;
    vector<Activity> activities3 = activities;
    activitySelection_Duration(activities3); // Not optimal

    cout << "\n4. Greedy Approach (Sort by Latest Start Time):" << endl;
    vector<Activity> activities4 = activities;
    activitySelection_LatestStartTime(activities4); // Not optimal

    cout << "\n5. Using Priority Queue (Sort by finish time):" << endl;
    vector<Activity> activities5 = activities;
    activitySelection_PriorityQueue(activities5);

    return 0;
}
