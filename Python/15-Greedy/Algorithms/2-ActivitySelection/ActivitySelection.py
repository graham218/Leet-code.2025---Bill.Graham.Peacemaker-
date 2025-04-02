def print_activities(activities):
    """
    Helper function to print a list of activities in a user-friendly format.

    Args:
        activities (list): A list of activities, where each activity is a tuple (start_time, finish_time, index).
    """
    if not activities:
        print("No activities selected.")
        return

    print("Selected activities:")
    for activity in activities:
        print(f"Activity {activity[2] + 1}: Start={activity[0]}, Finish={activity[1]}")

def activity_selection_by_finish_time(activities):
    """
    Selects the maximum number of non-overlapping activities using a greedy approach.
    Sorts activities by finish time.

    Args:
        activities (list): A list of activities, where each activity is a tuple (start_time, finish_time, index).
            Index is added to keep track of original activity.

    Returns:
        list: A list of selected activities.
    """
    # Sort activities by finish time (ascending order)
    activities.sort(key=lambda x: x[1])  # Sort based on finish time
    n = len(activities)
    selected_activities = [activities[0]]  # Select the first activity (smallest finish time)
    last_finish_time = activities[0][1]  # Finish time of the last selected activity

    for i in range(1, n):
        if activities[i][0] >= last_finish_time:
            # If the start time of the current activity is greater than or equal to the finish time of the last selected activity,
            # then select this activity
            selected_activities.append(activities[i])
            last_finish_time = activities[i][1]

    return selected_activities

def activity_selection_by_start_time(activities):
    """
    Selects the maximum number of non-overlapping activities using a greedy approach.
    Sorts activities by start time.  This is NOT an optimal solution.

    Args:
        activities (list): A list of activities, where each activity is a tuple (start_time, finish_time, index).

    Returns:
        list: A list of selected activities.
    """
    # Sort activities by start time (ascending order)
    activities.sort(key=lambda x: x[0])
    n = len(activities)
    selected_activities = [activities[0]]
    last_finish_time = activities[0][1]

    for i in range(1, n):
        if activities[i][0] >= last_finish_time:
            selected_activities.append(activities[i])
            last_finish_time = activities[i][1]
    return selected_activities

def activity_selection_by_shortest_duration(activities):
    """
    Selects the maximum number of non-overlapping activities using a greedy approach.
    Sorts activities by duration (finish_time - start_time).  NOT optimal.

    Args:
        activities (list): A list of activities, where each activity is a tuple (start_time, finish_time, index).

    Returns:
        list: A list of selected activities.
    """
    # Sort activities by duration (ascending order)
    activities.sort(key=lambda x: (x[1] - x[0]))
    n = len(activities)
    selected_activities = [activities[0]]
    last_finish_time = activities[0][1]

    for i in range(1, n):
        if activities[i][0] >= last_finish_time:
            selected_activities.append(activities[i])
            last_finish_time = activities[i][1]
    return selected_activities

def activity_selection_by_latest_start_time(activities):
    """
    Selects the maximum number of non-overlapping activities using a greedy approach.
    Sorts activities by start time DESCENDING.  This is NOT optimal.

    Args:
        activities (list): A list of activities, where each activity is a tuple (start_time, finish_time, index).

    Returns:
        list: A list of selected activities.
    """
    # Sort activities by start time in descending order
    activities.sort(key=lambda x: x[0], reverse=True)
    n = len(activities)
    selected_activities = [activities[0]]
    last_finish_time = activities[0][1]

    for i in range(1, n):
        if activities[i][0] >= last_finish_time:
            selected_activities.append(activities[i])
            last_finish_time = activities[i][1]
    return selected_activities
def activity_selection_recursive(activities, k, last_finish_time, selected_activities):
    """
    Recursive approach to activity selection.  This is the CLEARLY sub-optimal,
    but demonstrates a different way of thinking about the problem.  It's inefficient.

    Args:
        activities (list): List of activities.
        k (int): Index of the current activity being considered.
        last_finish_time (int): Finish time of the last selected activity.
        selected_activities (list): List to store selected activities.

    Returns:
        list:  The updated selected_activities list.
    """
    if k >= len(activities):
        return selected_activities

    if activities[k][0] >= last_finish_time:
        selected_activities.append(activities[k])
        return activity_selection_recursive(activities, k + 1, activities[k][1], selected_activities)
    else:
        return activity_selection_recursive(activities, k + 1, last_finish_time, selected_activities)



if __name__ == "__main__":
    # Sample activities (start_time, finish_time, index)
    activities = [(1, 3, 0), (2, 4, 1), (3, 5, 2), (0, 6, 3), (5, 7, 4), (8, 9, 5), (5, 9, 6)]

    print("Original Activities (Start, Finish, Index):")
    for act in activities:
        print(act)
    print("\n")
    # 1. Activity Selection by Finish Time (Optimal)
    print("1. Activity Selection by Finish Time:")
    selected_activities_finish_time = activity_selection_by_finish_time(activities.copy()) # Pass a copy to avoid modifying original
    print_activities(selected_activities_finish_time)
    print("\n")

    # 2. Activity Selection by Start Time (NOT Optimal)
    print("2. Activity Selection by Start Time (NOT Optimal):")
    selected_activities_start_time = activity_selection_by_start_time(activities.copy())
    print_activities(selected_activities_start_time)
    print("\n")

    # 3. Activity Selection by Shortest Duration (NOT Optimal)
    print("3. Activity Selection by Shortest Duration (NOT Optimal):")
    selected_activities_duration = activity_selection_by_shortest_duration(activities.copy())
    print_activities(selected_activities_duration)
    print("\n")

    # 4. Activity Selection by Latest Start Time (NOT Optimal)
    print("4. Activity Selection by Latest Start Time (NOT Optimal):")
    selected_activities_latest_start = activity_selection_by_latest_start_time(activities.copy())
    print_activities(selected_activities_latest_start)
    print("\n")

    # 5. Activity Selection using Recursion (Sub-Optimal and Inefficient)
    print("5. Activity Selection using Recursion (Sub-Optimal):")
    activities_for_recursion = sorted(activities.copy(), key=lambda x: x[1])  # MUST sort by finish time for this recursive approach to have a chance.
    selected_activities_recursive = activity_selection_recursive(activities_for_recursion, 0, 0, [])
    print_activities(selected_activities_recursive)
