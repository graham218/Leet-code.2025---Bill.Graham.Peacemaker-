import java.util.*;
import java.lang.*;

public class ActivitySelection {

    // 1. Greedy Approach: Sort by finish times (Most common and efficient)
    public static List<Activity> selectActivitiesByFinishTime(Activity[] activities) {
        // Sort activities by finish times using a lambda expression for concise sorting
        Arrays.sort(activities, (a, b) -> Integer.compare(a.finish, b.finish));

        List<Activity> selectedActivities = new ArrayList<>();
        // The first activity is always selected
        selectedActivities.add(activities[0]);
        int lastFinishTime = activities[0].finish;

        // Iterate through the remaining activities
        for (int i = 1; i < activities.length; i++) {
            // If the start time of the current activity is greater than or equal to the finish
            // time of the last selected activity, select it
            if (activities[i].start >= lastFinishTime) {
                selectedActivities.add(activities[i]);
                lastFinishTime = activities[i].finish; // Update lastFinishTime
            }
        }
        return selectedActivities;
    }

    // 2. Greedy Approach: Sort by start times (Incorrect but included for comparison)
    public static List<Activity> selectActivitiesByStartTime(Activity[] activities) {
        // Sort activities by start times.  This is generally NOT the correct approach
        Arrays.sort(activities, (a, b) -> Integer.compare(a.start, b.start));

        List<Activity> selectedActivities = new ArrayList<>();
        selectedActivities.add(activities[0]);
        int lastFinishTime = activities[0].finish;

        for (int i = 1; i < activities.length; i++) {
            if (activities[i].start >= lastFinishTime) {
                selectedActivities.add(activities[i]);
                lastFinishTime = activities[i].finish;
            }
        }
        return selectedActivities;
    }

    // 3. Recursive Approach:  (Less efficient, demonstrates the concept)
    public static List<Activity> selectActivitiesRecursive(Activity[] activities, int k, int lastFinishTime, List<Activity> selected) {
        // Base case: If no more activities to process, return the selected activities
        if (k >= activities.length) {
            return selected;
        }

        // Recursive step:
        // Option 1: Don't include the current activity
        List<Activity> withoutCurrent = selectActivitiesRecursive(activities, k + 1, lastFinishTime, new ArrayList<>(selected));

        // Option 2: Include the current activity if it's compatible
        List<Activity> withCurrent = new ArrayList<>(selected);
        if (activities[k].start >= lastFinishTime) {
            withCurrent.add(activities[k]);
            withCurrent = selectActivitiesRecursive(activities, k + 1, activities[k].finish, withCurrent);
        }

        // Return the option that results in more activities.
        return (withCurrent.size() > withoutCurrent.size()) ? withCurrent : withoutCurrent;
    }

    // 4. Dynamic Programming Approach: (More complex, for comparison)
    public static List<Activity> selectActivitiesDP(Activity[] activities) {
        int n = activities.length;
        // Sort by finish times, as DP approach also relies on sorted finish times for correctness
        Arrays.sort(activities, (a, b) -> Integer.compare(a.finish, b.finish));

        // dp[i] stores the maximum number of compatible activities ending at activity i
        int[] dp = new int[n];
        int[] prev = new int[n]; // To store the index of the previous activity in the optimal solution
        Arrays.fill(prev, -1);

        dp[0] = 1; // Base case: The first activity is always selected
        // Iterate through the activities
        for (int i = 1; i < n; i++) {
            dp[i] = 1; // Initialize with 1 (the current activity itself)
            for (int j = 0; j < i; j++) {
                // If activity j is compatible with activity i
                if (activities[j].finish <= activities[i].start) {
                    // Update dp[i] if including activity j gives a better solution
                    if (dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        prev[i] = j; // Store the previous activity index
                    }
                }
            }
        }

        // Find the index of the last activity in the optimal solution
        int maxActivities = 0;
        int lastActivityIndex = 0;
        for (int i = 0; i < n; i++) {
            if (dp[i] > maxActivities) {
                maxActivities = dp[i];
                lastActivityIndex = i;
            }
        }

        // Backtrack to construct the list of selected activities
        List<Activity> selectedActivities = new ArrayList<>();
        while (lastActivityIndex != -1) {
            selectedActivities.add(activities[lastActivityIndex]);
            lastActivityIndex = prev[lastActivityIndex];
        }
        Collections.reverse(selectedActivities); // Reverse to get correct order
        return selectedActivities;
    }

    // 5. Using a TreeSet to maintain sorted order (Alternative to sorting)
    public static List<Activity> selectActivitiesTreeSet(Activity[] activities) {
        // Use a TreeSet to automatically maintain activities sorted by finish time
        TreeSet<Activity> sortedActivities = new TreeSet<>(Comparator.comparingInt(a -> a.finish));
        Collections.addAll(sortedActivities, activities); // Add all activities

        List<Activity> selectedActivities = new ArrayList<>();
        if (sortedActivities.isEmpty()) return selectedActivities;

        Activity firstActivity = sortedActivities.pollFirst();
        selectedActivities.add(firstActivity);
        int lastFinishTime = firstActivity.finish;

        // Iterate through the remaining activities in the TreeSet
        while (!sortedActivities.isEmpty())
        {
            Activity currentActivity = sortedActivities.pollFirst();
            if (currentActivity.start >= lastFinishTime)
            {
                selectedActivities.add(currentActivity);
                lastFinishTime = currentActivity.finish;
            }
        }
        return selectedActivities;
    }
    public static void main(String[] args) {
        // Example usage:
        Activity[] activities = {
                new Activity(1, 2),
                new Activity(3, 4),
                new Activity(0, 6),
                new Activity(5, 7),
                new Activity(8, 9),
                new Activity(5, 9),
                new Activity(6, 10),
                new Activity(8, 11),
                new Activity(12, 16),
                new Activity(14, 18)
        };

        System.out.println("Activities: " + Arrays.toString(activities));

        System.out.println("\n1. Selected Activities (Greedy - Sort by finish time):");
        List<Activity> selected1 = selectActivitiesByFinishTime(activities);
        System.out.println(selected1);

        System.out.println("\n2. Selected Activities (Greedy - Sort by start time - INCORRECT):");
        List<Activity> selected2 = selectActivitiesByStartTime(activities);
        System.out.println(selected2);

        System.out.println("\n3. Selected Activities (Recursive):");
        List<Activity> selected3 = selectActivitiesRecursive(activities, 0, 0, new ArrayList<>());
        System.out.println(selected3);

        System.out.println("\n4. Selected Activities (Dynamic Programming):");
        List<Activity> selected4 = selectActivitiesDP(activities);
        System.out.println(selected4);

        System.out.println("\n5. Selected Activities (TreeSet):");
        List<Activity> selected5 = selectActivitiesTreeSet(activities);
        System.out.println(selected5);
    }
}

class Activity {
    int start, finish;

    public Activity(int start, int finish) {
        this.start = start;
        this.finish = finish;
    }

    public String toString() {
        return "(" + start + ", " + finish + ")";
    }
}