// Greedy Activity Selection Problem

/*
Problem Description:
You are given n activities with their start and finish times. Select the maximum number of activities that can be performed by a single person, assuming that a person can only work on a single activity at a time.

Different Approaches and Real-World Project Implementations:

1.  **Earliest Finish Time First (Most Common Greedy Approach)**
    * Description: Sort activities by their finish times and then select activities in that order, as long as they don't overlap with previously selected activities.
    * Real-World Application: Scheduling meetings or appointments.  The goal is to maximize the number of meetings scheduled in a given time frame.  This approach is very common and effective.

2.  **Earliest Start Time First**
    * Description: Sort activities by their start times and then select activities in that order, as long as they don't overlap.
    * Real-World Application:  This is less common, but could be used in scenarios where you want to start activities as soon as possible.  For example, in a manufacturing process, you might want to start jobs as early as possible, even if they have longer durations.  However, this is NOT optimal for maximizing the *number* of activities.

3.  **Shortest Activity Duration First**
     * Description: Sort activities by their duration (finish time - start time) and select the shortest activities first, as long as they don't overlap.
     * Real-World Application:  This might be used in a system where you want to minimize the time that resources are tied up.  For example, in a computer operating system, you might want to schedule the shortest jobs first to improve overall throughput (though this is often combined with other factors).  Not ideal for maximizing *count*.

4.  **Maximum Compatible Activities First**
    * Description: For each activity, find the number of non-overlapping activities. Sort the activities in decreasing order of non-overlapping count. This approach tries to pick the activity that conflicts with the least number of other activities.
    * Real-World Application:  A more complex scheduling scenario where you want to minimize disruptions or conflicts.  For example, in a project management setting, you might want to schedule tasks that have the fewest dependencies or resource conflicts first.  This is a more sophisticated approach than the basic earliest-finish-time.

5.  **Recursive Solution (Optimal Solution Using Dynamic Programming Concepts - Not Greedy, but Included for Completeness and Comparison)**
    * Description:  This approach uses recursion (and can be optimized with memoization - dynamic programming) to find the optimal solution.  It explores all possible combinations of activities.  It's not a greedy approach, as it doesn't make a locally optimal choice at each step.  It's included here to show the *actual* optimal solution for comparison.
    * Real-World Application:  While the recursive solution itself might be too slow for large problems, the underlying concept of exploring all possibilities is fundamental to many optimization problems.  Dynamic programming, which builds on this, is used in a wide range of applications, such as route planning, resource allocation, and bioinformatics.  For example, finding the absolute best schedule in a very complex project with many interdependencies.
*/

// Helper function to print the selected activities
function printSelectedActivities(activities, selected) {
    console.log("Selected Activities:");
    for (let i of selected) {
        console.log(`Activity ${i + 1}: Start=${activities[i][0]}, Finish=${activities[i][1]}`);
    }
    console.log("---");
}

// 1. Earliest Finish Time First
function earliestFinishTimeFirst(activities) {
    // Sort activities by finish time
    const sortedActivities = [...activities].sort((a, b) => a[1] - b[1]);
    const selectedActivities = [0]; // Always select the first activity (after sorting)
    let lastFinishTime = sortedActivities[0][1];

    for (let i = 1; i < sortedActivities.length; i++) {
        if (sortedActivities[i][0] >= lastFinishTime) {
            selectedActivities.push(i);
            lastFinishTime = sortedActivities[i][1];
        }
    }
    return selectedActivities;
}

// 2. Earliest Start Time First (NOT Optimal for Activity COUNT)
function earliestStartTimeFirst(activities) {
    // Sort activities by start time
    const sortedActivities = [...activities].sort((a, b) => a[0] - b[0]);
    const selectedActivities = [0];
    let lastFinishTime = sortedActivities[0][1];

    for (let i = 1; i < sortedActivities.length; i++) {
        if (sortedActivities[i][0] >= lastFinishTime) {
            selectedActivities.push(i);
            lastFinishTime = sortedActivities[i][1];
        }
    }
    return selectedActivities;
}

// 3. Shortest Activity Duration First (NOT Optimal for Activity COUNT)
function shortestDurationFirst(activities) {
    // Sort activities by duration
    const sortedActivities = [...activities].sort((a, b) => (a[1] - a[0]) - (b[1] - b[0]));
    const selectedActivities = [0];
    let lastFinishTime = sortedActivities[0][1];

    for (let i = 1; i < sortedActivities.length; i++) {
        if (sortedActivities[i][0] >= lastFinishTime) {
            selectedActivities.push(i);
            lastFinishTime = sortedActivities[i][1];
        }
    }
    return selectedActivities;
}

// 4. Maximum Compatible Activities First
function maxCompatibleActivitiesFirst(activities) {
  const n = activities.length;
  const compatibleCounts = [];

  // Calculate the number of compatible activities for each activity
  for (let i = 0; i < n; i++) {
    let count = 0;
    for (let j = 0; j < n; j++) {
      if (i !== j) {
        // Check for non-overlap:
        // Activity i finishes before activity j starts, OR activity j finishes before activity i starts.
        if (activities[i][1] <= activities[j][0] || activities[j][1] <= activities[i][0]) {
          count++;
        }
      }
    }
    compatibleCounts.push(count);
  }

  // Sort activities based on the number of compatible activities (descending order)
  const sortedActivityIndices = [...Array(n).keys()].sort((a, b) => compatibleCounts[b] - compatibleCounts[a]);

  const selectedActivities = [];
  const selectedIndices = new Set(); // Keep track of selected activity indices for quick checks.

  for (let i = 0; i < n; i++) {
    const currentActivityIndex = sortedActivityIndices[i];
    let isCompatible = true;

    for (const selectedIndex of selectedIndices) {
      // Check if the current activity overlaps with any of the already selected activities.
      if (!(activities[currentActivityIndex][1] <= activities[selectedIndex][0] ||
            activities[selectedIndex][1] <= activities[currentActivityIndex][0])) {
        isCompatible = false;
        break;
      }
    }

    if (isCompatible) {
      selectedActivities.push(currentActivityIndex);
      selectedIndices.add(currentActivityIndex);
    }
  }
  return selectedActivities;
}

// 5. Recursive Solution (Optimal Solution - Dynamic Programming Concept)
function recursiveActivitySelection(activities, k, lastFinishTime, selectedActivities = []) {
    if (k >= activities.length) {
        return selectedActivities;
    }

    // Case 1: Exclude the current activity
    const excludeCurrent = recursiveActivitySelection(activities, k + 1, lastFinishTime, [...selectedActivities]);

    // Case 2: Include the current activity if it's compatible
    let includeCurrent = [];
    if (activities[k][0] >= lastFinishTime) {
        includeCurrent = recursiveActivitySelection(activities, k + 1, activities[k][1], [...selectedActivities, k]);
    }

    // Return the solution (activity list) that results in more activities.
    return includeCurrent.length > excludeCurrent.length ? includeCurrent : excludeCurrent;
}



// Example Usage (Driver Code)
const activities = [
    [1, 3],  // Activity 1
    [2, 4],  // Activity 2
    [3, 5],  // Activity 3
    [0, 6],  // Activity 4
    [5, 7],  // Activity 5
    [8, 9],  // Activity 6
    [8, 10], // Activity 7
    [6, 11], // Activity 8
    [12, 16], // Activity 9
    [12, 14], // Activity 10
];

console.log("--- Earliest Finish Time First ---");
const selected1 = earliestFinishTimeFirst(activities);
printSelectedActivities(activities, selected1); // Expected Output:  1, 2, 5, 6, 9 (or 10)

console.log("--- Earliest Start Time First ---");
const selected2 = earliestStartTimeFirst(activities);
printSelectedActivities(activities, selected2); // Expected Output: 1, 3, 5, 6, 9

console.log("--- Shortest Activity Duration First ---");
const selected3 = shortestDurationFirst(activities);
printSelectedActivities(activities, selected3); // Expected Output: 1, 2, 5, 6, 9 (or 10)

console.log("--- Maximum Compatible Activities First ---");
const selected4 = maxCompatibleActivitiesFirst(activities);
printSelectedActivities(activities, selected4);

console.log("--- Recursive Solution (Optimal) ---");
const selected5 = recursiveActivitySelection(activities, 0, 0);
printSelectedActivities(activities, selected5); // Expected Output: 1, 3, 5, 6, 9
