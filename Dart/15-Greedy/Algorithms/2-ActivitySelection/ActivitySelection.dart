import 'package:collection/collection.dart';

// Activity Selection Problem
// You are given n activities with their start and finish times. Select the maximum number of activities that can be performed by a single person, assuming that a person can only work on a single activity at a time.

// 1. Greedy Approach 1: Sort by finish time (Recursive)
List<Activity> selectActivitiesByFinishTimeRecursive(List<Activity> activities, int k) {
  if (activities.isEmpty || k >= activities.length) {
    return [];
  }
  List<Activity> selectedActivities = [activities[k]];
  for (int m = k + 1; m < activities.length; m++) {
    if (activities[m].start >= activities[k].finish) {
      selectedActivities.addAll(selectActivitiesByFinishTimeRecursive(activities, m));
      break; // Important: Only one recursive call needed here
    }
  }
  return selectedActivities;
}

// 2. Greedy Approach 2: Sort by finish time (Iterative)
List<Activity> selectActivitiesByFinishTimeIterative(List<Activity> activities) {
  if (activities.isEmpty) {
    return [];
  }
  // Sort activities by finish time
  activities.sort((a, b) => a.finish.compareTo(b.finish));

  List<Activity> selectedActivities = [activities[0]];
  int lastFinishedTime = activities[0].finish;

  for (int i = 1; i < activities.length; i++) {
    if (activities[i].start >= lastFinishedTime) {
      selectedActivities.add(activities[i]);
      lastFinishedTime = activities[i].finish;
    }
  }
  return selectedActivities;
}

// 3. Greedy Approach 3: Sort by start time (and then finish time) -  Incorrect for general case, but showing the approach
List<Activity> selectActivitiesByStartTime(List<Activity> activities) {
  if (activities.isEmpty) {
    return [];
  }
  // Sort activities by start time, then by finish time if starts are equal.
  activities.sort((a, b) {
    int startComparison = a.start.compareTo(b.start);
    if (startComparison == 0) {
      return a.finish.compareTo(b.finish);
    }
    return startComparison;
  });

  List<Activity> selectedActivities = [activities[0]];
  int lastFinishedTime = activities[0].finish;

  for (int i = 1; i < activities.length; i++) {
    if (activities[i].start >= lastFinishedTime) {
      selectedActivities.add(activities[i]);
      lastFinishedTime = activities[i].finish;
    }
  }
  return selectedActivities;
}

// 4.  Greedy Approach 4: Consider both start and finish times, prioritizing short duration - May not be optimal, but a different heuristic
List<Activity> selectActivitiesByShortestDuration(List<Activity> activities) {
  if (activities.isEmpty) {
    return [];
  }
  // Sort activities by duration (finish - start)
  activities.sort((a, b) => (a.finish - a.start).compareTo(b.finish - b.start));

  List<Activity> selectedActivities = [activities[0]];
  int lastFinishedTime = activities[0].finish;

  for (int i = 1; i < activities.length; i++) {
    if (activities[i].start >= lastFinishedTime) {
      selectedActivities.add(activities[i]);
      lastFinishedTime = activities[i].finish;
    }
  }
  return selectedActivities;
}

// 5. Using a custom comparator and the `sorted` method from the collection package.
List<Activity> selectActivitiesWithSorted(List<Activity> activities) {
  if (activities.isEmpty) return [];

  List<Activity> sortedActivities = activities.sorted((a, b) => a.finish.compareTo(b.finish));
  List<Activity> selected = [sortedActivities.first];
  int lastFinishTime = sortedActivities.first.finish;

  for (int i = 1; i < sortedActivities.length; i++) {
    if (sortedActivities[i].start >= lastFinishTime) {
      selected.add(sortedActivities[i]);
      lastFinishTime = sortedActivities[i].finish;
    }
  }
  return selected;
}

// Activity class to represent an activity with start and finish times
class Activity {
  int start;
  int finish;

  Activity(this.start, this.finish);

  @override
  String toString() {
    return '($start, $finish)';
  }
  @override
  bool operator ==(Object other) {
    if (identical(this, other)) return true;
    return other is Activity && start == other.start && finish == other.finish;
  }

  @override
  int get hashCode => start.hashCode ^ finish.hashCode;
}

void main() {
  // Example usage:
  List<Activity> activities = [
    Activity(1, 2),
    Activity(3, 4),
    Activity(0, 6),
    Activity(5, 7),
    Activity(8, 9),
    Activity(5, 9),
    Activity(6, 10),
    Activity(8, 11),
    Activity(8, 12),
    Activity(2, 13),
    Activity(12, 14),
  ];

  print("Activities: $activities");

  // 1. Greedy Approach 1: Sort by finish time (Recursive)
  List<Activity> selectedActivities1 = selectActivitiesByFinishTimeRecursive(List.from(activities)..sort((a, b) => a.finish.compareTo(b.finish)), 0);
  print("Selected Activities (Greedy 1 - Recursive): $selectedActivities1"); // Expected: [(1, 2), (3, 4), (5, 7), (8, 9), (12, 14)]

  // 2. Greedy Approach 2: Sort by finish time (Iterative) - Correct Approach
  List<Activity> selectedActivities2 = selectActivitiesByFinishTimeIterative(activities);
  print("Selected Activities (Greedy 2 - Iterative): $selectedActivities2"); // Expected: [(1, 2), (3, 4), (5, 7), (8, 9), (12, 14)]

  // 3. Greedy Approach 3: Sort by start time (and then finish time) - Incorrect for general case
  List<Activity> selectedActivities3 = selectActivitiesByStartTime(activities);
  print("Selected Activities (Greedy 3 - Start Time): $selectedActivities3"); // Not Optimal

  // 4. Greedy Approach 4: Sort by shortest duration - May not be optimal
  List<Activity> selectedActivities4 = selectActivitiesByShortestDuration(activities);
  print("Selected Activities (Greedy 4 - Shortest Duration): $selectedActivities4"); // Not Optimal

  // 5. Using sorted from collection package.
  List<Activity> selectedActivities5 = selectActivitiesWithSorted(activities);
  print("Selected Activities (Greedy 5 - Sorted): $selectedActivities5");
  // Additional test case to demonstrate the importance of sorting by finish time.
  List<Activity> testActivities = [Activity(0, 10), Activity(2, 14), Activity(12, 16)];
  List<Activity> result = selectActivitiesByFinishTimeIterative(testActivities);
  print("Test Activities: $testActivities");
  print("Selected Activities (Test Case): $result"); // Expected: [(0, 10), (12, 16)] , if sorted by finish time
}
