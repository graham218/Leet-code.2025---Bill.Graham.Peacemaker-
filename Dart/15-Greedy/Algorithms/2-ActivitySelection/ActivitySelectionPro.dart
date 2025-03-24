import 'package:collection/collection.dart';

// Activity Selection Problem
// You are given n activities with their start and finish times. Select the maximum number of activities that can be performed by a single person, assuming that a person can only work on a single activity at a time.

// Activity class to represent an activity with start and finish times.  Now includes a name/ID.
class Activity {
  String name; // Added name for real-world context
  int start;
  int finish;

  Activity(this.name, this.start, this.finish);

  @override
  String toString() {
    return '$name (Start: $start, Finish: $finish)';
  }

  @override
  bool operator ==(Object other) {
    if (identical(this, other)) return true;
    return other is Activity &&
        name == other.name &&
        start == other.start &&
        finish == other.finish;
  }

  @override
  int get hashCode => name.hashCode ^ start.hashCode ^ finish.hashCode;
}

// 1. Greedy Approach: Sort by finish time (Iterative) -  Most efficient and practical
List<Activity> selectActivitiesByFinishTime(List<Activity> activities) {
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

void main() {
  // 1. Example: Scheduling Meetings in a Conference Room
  //   * Activities: Meetings with start and end times.
  //   * Goal: Maximize the number of meetings scheduled in a single room.
  List<Activity> meetings = [
    Activity("Meeting A", 9, 10),
    Activity("Meeting B", 11, 13),
    Activity("Meeting C", 9, 11),
    Activity("Meeting D", 13, 14),
    Activity("Meeting E", 10, 12),
    Activity("Meeting F", 14, 16),
  ];
  List<Activity> selectedMeetings = selectActivitiesByFinishTime(meetings);
  print("\n--- Meeting Scheduling Example ---");
  print("Available Meetings: $meetings");
  print("Selected Meetings: $selectedMeetings"); // Expected: [Meeting A (Start: 9, Finish: 10), Meeting B (Start: 11, Finish: 13), Meeting D (Start: 13, Finish: 14), Meeting F (Start: 14, Finish: 16)]

  // 2. Example: Job Sequencing on a Single Processor
  //   * Activities: Jobs with start and end times (processing intervals).
  //   * Goal: Maximize the number of jobs that can be executed on a single processor.
  List<Activity> jobs = [
    Activity("Job 1", 1, 3),
    Activity("Job 2", 2, 5),
    Activity("Job 3", 6, 8),
    Activity("Job 4", 4, 7),
    Activity("Job 5", 8, 10),
    Activity("Job 6", 9, 11),
  ];
  List<Activity> selectedJobs = selectActivitiesByFinishTime(jobs);
  print("\n--- Job Scheduling Example ---");
  print("Available Jobs: $jobs");
  print("Selected Jobs: $selectedJobs"); // Expected: [Job 1 (Start: 1, Finish: 3), Job 2 (Start: 2, Finish: 5), Job 3 (Start: 6, Finish: 8), Job 5 (Start: 8, Finish: 10), Job 6 (Start: 9, Finish: 11)] or [Job 1, Job 3, Job 4, Job 5]

  // 3. Example:  TV Show Scheduling
  // * Activities: TV Shows with start and end times.
  // * Goal: Maximize the number of TV shows that can be aired without overlap.
  List<Activity> tvShows = [
    Activity("Show A", 8, 9),
    Activity("Show B", 9, 10),
    Activity("Show C", 10, 11),
    Activity("Show D", 11, 12),
    Activity("Show E", 8, 10),
    Activity("Show F", 10, 12),
  ];

  List<Activity> selectedShows = selectActivitiesByFinishTime(tvShows);
  print("\n--- TV Show Scheduling Example ---");
  print("Available Shows: $tvShows");
  print("Selected Shows: $selectedShows");

  // 4. Example:  Band Concert Scheduling
  // * Activities: Band Concert with start and end times.
  // * Goal: Maximize the number of Bands that can perform without overlap.
  List<Activity> bands = [
    Activity("Band A", 8, 9),
    Activity("Band B", 9, 10),
    Activity("Band C", 10, 11),
    Activity("Band D", 11, 12),
    Activity("Band E", 8, 10),
    Activity("Band F", 10, 12),
  ];

  List<Activity> selectedBands = selectActivitiesByFinishTime(bands);
  print("\n--- Band Concert Scheduling Example ---");
  print("Available Bands: $bands");
  print("Selected Bands: $selectedBands");
}
