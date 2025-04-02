def print_activities(activities):
    """
    Helper function to print a list of activities in a user-friendly format.

    Args:
        activities (list of tuples): A list where each tuple represents an activity
                                     with (start_time, finish_time, activity_name).
    """
    if not activities:
        print("No activities selected.")
        return

    print("Selected activities:")
    for activity in activities:
        print(f"  Activity: {activity[2]}, Start: {activity[0]}, Finish: {activity[1]}")

def greedy_activity_selection_by_finish_time(activities):
    """
    Greedy approach to select activities based on the earliest finish time.
    This is the most common and optimal approach for the activity selection problem.

    Args:
        activities (list of tuples): A list where each tuple represents an activity
                                     with (start_time, finish_time, activity_name).
    Returns:
        list of tuples: A list of selected activities.
    """
    # Sort activities by finish time
    activities.sort(key=lambda x: x[1])  # Sort by the second element (finish time)
    selected_activities = []
    if not activities:
        return selected_activities

    selected_activities.append(activities[0])  # Select the first activity (earliest finish)
    last_finish_time = activities[0][1]

    for i in range(1, len(activities)):
        if activities[i][0] >= last_finish_time:
            selected_activities.append(activities[i])
            last_finish_time = activities[i][1]
    return selected_activities

def greedy_activity_selection_by_start_time(activities):
    """
    Greedy approach to select activities based on the earliest start time.
    This approach is NOT optimal, but it's included for comparison.

    Args:
        activities (list of tuples): A list where each tuple represents an activity
                                     with (start_time, finish_time, activity_name).
    Returns:
        list of tuples: A list of selected activities.
    """
    # Sort activities by start time
    activities.sort(key=lambda x: x[0])
    selected_activities = []
    if not activities:
        return selected_activities
    selected_activities.append(activities[0])
    last_finish_time = activities[0][1]

    for i in range(1, len(activities)):
        if activities[i][0] >= last_finish_time:
            selected_activities.append(activities[i])
            last_finish_time = activities[i][1]
    return selected_activities

def greedy_activity_selection_by_shortest_duration(activities):
    """
    Greedy approach to select activities based on the shortest duration.
    This approach is NOT optimal.

    Args:
        activities (list of tuples): A list where each tuple represents an activity
                                     with (start_time, finish_time, activity_name).
    Returns:
        list of tuples: A list of selected activities.
    """
    # Sort activities by duration (finish_time - start_time)
    activities.sort(key=lambda x: x[1] - x[0])
    selected_activities = []
    if not activities:
        return selected_activities

    selected_activities.append(activities[0])
    last_finish_time = activities[0][1]

    for i in range(1, len(activities)):
        if activities[i][0] >= last_finish_time:
            selected_activities.append(activities[i])
            last_finish_time = activities[i][1]
    return selected_activities

def greedy_activity_selection_by_most_overlap(activities):
    """
    Greedy approach that tries to select activities that have the least overlap
    with other activities. This is a more complex, non-optimal approach.  It calculates
    the overlap of each activity with all others and sorts by the least overlap.

    Args:
        activities (list of tuples): A list where each tuple represents an activity
                                     with (start_time, finish_time, activity_name).
    Returns:
        list of tuples: A list of selected activities.
    """
    def calculate_overlap(activity, other_activities):
        """Calculates the total overlap of an activity with a list of other activities."""
        overlap = 0
        for other in other_activities:
            if max(activity[0], other[0]) < min(activity[1], other[1]):
                overlap += min(activity[1], other[1]) - max(activity[0], other[0])
        return overlap

    # Calculate overlap for each activity
    overlaps = [(i, calculate_overlap(act, activities[:i] + activities[i+1:])) for i, act in enumerate(activities)]

    # Sort activities by their overlap
    overlaps.sort(key=lambda x: x[1])  # Sort by the overlap value
    sorted_indices = [x[0] for x in overlaps] # Get original indices sorted by overlap

    selected_activities = []
    if not activities:
        return selected_activities

    selected_activities.append(activities[sorted_indices[0]])
    last_finish_time = activities[sorted_indices[0]][1]

    for i in range(1, len(activities)):
        activity_index = sorted_indices[i]
        if activities[activity_index][0] >= last_finish_time:
            selected_activities.append(activities[activity_index])
            last_finish_time = activities[activity_index][1]
    return selected_activities

def greedy_activity_selection_recursive(activities, k, last_finish_time, selected_activities):
    """
    Recursive implementation of the optimal activity selection algorithm (based on finish times).

    Args:
        activities (list of tuples): A list where each tuple represents an activity
                                     with (start_time, finish_time, activity_name).
        k (int): Index of the last selected activity.
        last_finish_time (int): Finish time of the last selected activity.
        selected_activities (list of tuples): List to store selected activities.

    Returns:
        list of tuples: A list of selected activities.
    """
    n = len(activities)
    m = k + 1
    while m < n and activities[m][0] < last_finish_time:
        m += 1
    if m < n:
        selected_activities.append(activities[m])
        return greedy_activity_selection_recursive(activities, m, activities[m][1], selected_activities)
    else:
        return selected_activities
def greedy_activity_selection_with_conflicts(activities):
    """
    Greedy approach that handles activity conflicts and prints them.
    This approach selects the maximum number of non-conflicting activities
    and also identifies the conflicting ones.

    Args:
        activities (list of tuples): A list where each tuple represents an activity
                                     with (start_time, finish_time, activity_name).
    Returns:
        tuple: (list of selected activities, list of conflicting activities)
    """
    activities.sort(key=lambda x: x[1])  # Sort by finish time
    selected_activities = []
    conflicting_activities = []
    if not activities:
        return selected_activities, conflicting_activities

    selected_activities.append(activities[0])
    last_finish_time = activities[0][1]

    for i in range(1, len(activities)):
        if activities[i][0] >= last_finish_time:
            selected_activities.append(activities[i])
            last_finish_time = activities[i][1]
        else:
            conflicting_activities.append(activities[i])
    return selected_activities, conflicting_activities
if __name__ == "__main__":
    # Sample activities (start_time, finish_time, activity_name)
    activities = [
        (1, 4, "A1"),
        (3, 5, "A2"),
        (0, 6, "A3"),
        (5, 7, "A4"),
        (3, 9, "A5"),
        (5, 9, "A6"),
        (6, 10, "A7"),
        (8, 11, "A8"),
        (8, 12, "A9"),
        (2, 14, "A10"),
        (12, 16, "A11"),
    ]

    print("Original Activities:")
    print_activities(activities)
    print("\n")

    # 1. Activity Selection by Earliest Finish Time (Optimal)
    print("1. Activity Selection by Earliest Finish Time (Optimal):")
    selected_activities_finish_time = greedy_activity_selection_by_finish_time(activities.copy())
    print_activities(selected_activities_finish_time)
    print("\n")

    # 2. Activity Selection by Earliest Start Time (Non-Optimal)
    print("2. Activity Selection by Earliest Start Time (Non-Optimal):")
    selected_activities_start_time = greedy_activity_selection_by_start_time(activities.copy())
    print_activities(selected_activities_start_time)
    print("\n")

    # 3. Activity Selection by Shortest Duration (Non-Optimal)
    print("3. Activity Selection by Shortest Duration (Non-Optimal):")
    selected_activities_duration = greedy_activity_selection_by_shortest_duration(activities.copy())
    print_activities(selected_activities_duration)
    print("\n")

    # 4. Activity Selection by Least Overlap (Non-Optimal, Complex)
    print("4. Activity Selection by Least Overlap (Non-Optimal, Complex):")
    selected_activities_overlap = greedy_activity_selection_by_most_overlap(activities.copy())
    print_activities(selected_activities_overlap)
    print("\n")

    # 5. Activity Selection (Recursive)
    print("5. Activity Selection (Recursive - Optimal):")
    activities_sorted = sorted(activities.copy(), key=lambda x: x[1]) # Need to sort by finish time for recursive
    selected_activities_recursive = [activities_sorted[0]]
    selected_activities_recursive = greedy_activity_selection_recursive(activities_sorted, 0, activities_sorted[0][1], selected_activities_recursive)
    print_activities(selected_activities_recursive)
    print("\n")

    # 6. Activity Selection with Conflict Reporting
    print("6. Activity Selection with Conflict Reporting:")
    selected_activities_conflicts, conflicting_activities = greedy_activity_selection_with_conflicts(activities.copy())
    print_activities(selected_activities_conflicts)
    print("\nConflicting Activities:")
    print_activities(conflicting_activities)
