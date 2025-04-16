// Activity Selection Problem:
// Given a set of activities with start and finish times,
// find the maximum number of non-overlapping activities that can be performed.

// Define the Activity structure
class Activity {
  constructor(start, finish) {
    this.start = start;
    this.finish = finish;
  }
}

// Function to solve the Activity Selection problem using different greedy approaches
function activitySelection(activities, approach) {
  // Sort activities by finish time (common for most approaches)
  activities.sort((a, b) => a.finish - b.finish);

  const selectedActivities = [];
  let lastFinishTime = -1;

  switch (approach) {
    case 1: // Approach 1: Earliest Finish Time (Greedy Approach 1)
      console.log(`\nApproach 1: Earliest Finish Time`);
      selectedActivities.push(activities[0]);
      lastFinishTime = activities[0].finish;

      for (let i = 1; i < activities.length; i++) {
        if (activities[i].start >= lastFinishTime) {
          selectedActivities.push(activities[i]);
          lastFinishTime = activities[i].finish;
        }
      }
      break;

    case 2: // Approach 2: Earliest Start Time (Incorrect Greedy Approach, for comparison)
      console.log(`\nApproach 2: Earliest Start Time (Incorrect)`);
      // Sort by start time
      activities.sort((a, b) => a.start - b.start);
      selectedActivities.push(activities[0]);
      lastFinishTime = activities[0].finish;

      for (let i = 1; i < activities.length; i++) {
        if (activities[i].start >= lastFinishTime) {
          selectedActivities.push(activities[i]);
          lastFinishTime = activities[i].finish;
        }
      }
      break;

    case 3: // Approach 3: Shortest Activity Duration (Incorrect Greedy Approach, for comparison)
      console.log(`\nApproach 3: Shortest Activity Duration (Incorrect)`);
      // Sort by duration (finish - start)
      activities.sort((a, b) => (a.finish - a.start) - (b.finish - b.start));
      selectedActivities.push(activities[0]);
      lastFinishTime = activities[0].finish;

      for (let i = 1; i < activities.length; i++) {
        if (activities[i].start >= lastFinishTime) {
          selectedActivities.push(activities[i]);
          lastFinishTime = activities[i].finish;
        }
      }
      break;
    case 4: // Recursive Solution
        console.log(`\nApproach 4: Recursive Solution`);
        function recursiveActivitySelection(activities, k, lastFinishTime, selectedActivities) {
            if (k >= activities.length) {
                return;
            }

            if (activities[k].start >= lastFinishTime) {
                selectedActivities.push(activities[k]);
                recursiveActivitySelection(activities, k + 1, activities[k].finish, selectedActivities);
            } else {
                recursiveActivitySelection(activities, k + 1, lastFinishTime, selectedActivities);
            }
        }
        // Activities must be sorted by finish time for the recursive approach to work correctly.
        activities.sort((a, b) => a.finish - b.finish);
        recursiveActivitySelection(activities, 0, -1, selectedActivities);
        break;
    case 5: // Iterative with While Loop
      console.log(`\nApproach 5: Iterative with While Loop`);
        let i = 0;
        if(activities.length > 0){
          selectedActivities.push(activities[i]);
          lastFinishTime = activities[i].finish;
          i++;
        }

        while (i < activities.length) {
            if (activities[i].start >= lastFinishTime) {
                selectedActivities.push(activities[i]);
                lastFinishTime = activities[i].finish;
            }
            i++;
        }
        break;
    default:
      console.log("Invalid approach.");
      return [];
  }

  return selectedActivities;
}

// Example Usage:
const activities = [
  new Activity(1, 2),
  new Activity(3, 4),
  new Activity(0, 6),
  new Activity(5, 7),
  new Activity(8, 9),
  new Activity(5, 9),
  new Activity(6, 10),
  new Activity(8, 11),
  new Activity(8, 12),
  new Activity(2, 14),
  new Activity(12, 16),
];

// Run and display results for each approach
for (let approach = 1; approach <= 5; approach++) {
  const selectedActivities = activitySelection(activities.slice(), approach); // Pass a copy to avoid modifying original
  console.log(`Selected Activities (Approach ${approach}):`);
  selectedActivities.forEach(activity => {
    console.log(`Start: ${activity.start}, Finish: ${activity.finish}`);
  });
  console.log(`Number of activities selected: ${selectedActivities.length}`);
}

/*
Explanation of Approaches:

1.  Earliest Finish Time (Greedy Approach 1):
    * Sort activities by finish times.
    * Select the first activity.
    * Iterate through the remaining activities, selecting those that start after the previous activity's finish time.
    * This is the standard and optimal greedy solution.

2.  Earliest Start Time (Incorrect Greedy Approach):
    * Sort activities by start times.
    * Select the first activity.
    * Iterate through the remaining activities, selecting those that start after the previous activity's finish time.
    * This approach is incorrect because selecting activities with the earliest start time doesn't guarantee the maximum number of non-overlapping activities.

3.  Shortest Activity Duration (Incorrect Greedy Approach):
    * Sort activities by duration (finish time - start time).
    * Select the first activity.
    * Iterate through the remaining activities, selecting those that start after the previous activity's finish time.
    * This approach is incorrect because selecting the shortest activities doesn't guarantee the maximum number of non-overlapping activities.  A short activity might block out many other activities.

4.  Recursive Solution:
    * Sort activities by finish time.
    * Define a recursive function that takes the array of activities, the current index, the finish time of the last selected activity, and the array of selected activities.
    * The base case is when the current index is greater than or equal to the number of activities.
    * In each recursive step, check if the start time of the current activity is greater than or equal to the finish time of the last selected activity. If it is, select the activity and recursively call the function with the next index and the finish time of the current activity. Otherwise, recursively call the function with the next index and the same finish time.

 5. Iterative with While Loop:
    * Sort activities by their finish times.
    * Initialize an empty array to store the selected activities.
    * Use a while loop to iterate through the activities.
    * In each iteration, check if the current activity's start time is greater than or equal to the finish time of the last selected activity.
    * If it is, add the current activity to the selected activities array and update the finish time of the last selected activity.

*/
