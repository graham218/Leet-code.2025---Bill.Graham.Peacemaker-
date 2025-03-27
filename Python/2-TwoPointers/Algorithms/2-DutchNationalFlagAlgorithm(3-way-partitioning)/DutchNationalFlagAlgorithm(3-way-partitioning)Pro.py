# Advanced Dutch National Flag Algorithm Implementations
# Real-World Applications of 3-Way Partitioning

# Problem: Given an array with three unique values, sort them efficiently.
# This has applications in database partitioning, network traffic classification,
# and memory-efficient processing.

# Approach 1: In-Place Sorting (Efficient for Large Data Streams)
def in_place_sorting(arr):
    """
    Sorts an array with three unique values (0, 1, 2) in-place using the Dutch National Flag algorithm.

    This algorithm is highly efficient as it sorts the array with a single pass,
    making it suitable for large data streams where memory access is a bottleneck.

    Args:
        arr (list): The input list containing elements with values 0, 1, or 2.

    Returns:
        list: The sorted list.

    Algorithm:
        - Initialize three pointers: low, mid, and high.
        - 'low' points to the beginning of the 0s section.
        - 'mid' is the current element being examined.
        - 'high' points to the end of the 2s section.
        - Iterate through the array using the 'mid' pointer:
            - If arr[mid] is 0:
                - Swap arr[low] and arr[mid].
                - Increment both 'low' and 'mid'.
            - If arr[mid] is 1:
                - Increment 'mid'.
            - If arr[mid] is 2:
                - Swap arr[mid] and arr[high].
                - Decrement 'high'.  'mid' does not increment here because the swapped element
                  from 'high' could be any of 0, 1, or 2, and needs to be examined.
        - The loop continues until 'mid' crosses 'high'.
    """
    low, mid, high = 0, 0, len(arr) - 1  # Initialize pointers
    while mid <= high:  # Iterate until mid and high cross each other
        if arr[mid] == 0:
            arr[low], arr[mid] = arr[mid], arr[low]  # Swap arr[low] and arr[mid]
            low += 1  # Move low pointer to the next position
            mid += 1  # Move mid pointer to the next position
        elif arr[mid] == 1:
            mid += 1  # Move mid pointer to the next position
        else:  # arr[mid] == 2
            arr[mid], arr[high] = arr[high], arr[mid]  # Swap arr[mid] and arr[high]
            high -= 1  # Move high pointer to the previous position
            # Note: mid does not increment here
    return arr  # Return the sorted array

# Approach 2: Distributed Computing (Parallel Processing with MapReduce)
def distributed_sorting(arr):
    """
    Sorts an array with three unique values (0, 1, 2) using a counting-based approach,
    suitable for distributed computing environments like MapReduce.

    This approach is efficient for parallel processing because the counting step
    can be distributed across multiple nodes.  The final sorted array is then
    constructed by combining the counts from each node.

    Args:
        arr (list): The input list containing elements with values 0, 1, or 2.

    Returns:
        list: The sorted list.

    Algorithm:
        - Count the occurrences of 0, 1, and 2 in the array.
        - Create a new array by concatenating the appropriate number of 0s, 1s, and 2s.
    """
    from collections import Counter  # Import Counter class
    count = Counter(arr)  # Count occurrences of each element
    return [0] * count[0] + [1] * count[1] + [2] * count[2]  # Construct sorted array

# Approach 3: Database Partitioning (Efficient Query Processing)
def database_partitioning(records):
    """
    Partitions database records based on a category (assumed to be the second element
    in each record).  This is a common technique for improving query performance
    in large databases by dividing the data into smaller, more manageable chunks.

    Args:
        records (list of tuples): A list of database records, where each record is a tuple
                                 and the second element is the category (0, 1, or 2).

    Returns:
        dict: A dictionary where keys are categories (0, 1, 2) and values are lists of records
              belonging to that category.
    """
    partitions = {0: [], 1: [], 2: []}  # Initialize partitions for each category
    for record in records:
        partitions[record[1]].append(record)  # Append record to the appropriate partition
    return partitions  # Return the partitioned data

# Approach 4: Network Packet Prioritization (Real-Time Packet Classification)
def network_packet_sorting(packets):
    """
    Sorts network packets based on their priority (0, 1, or 2).  This is crucial for
    Quality of Service (QoS) in network communication, ensuring that high-priority
    packets are processed before lower-priority ones.

    Args:
        packets (list of dicts): A list of network packets, where each packet is a dictionary
                                 containing a 'priority' key with a value of 0, 1, or 2.

    Returns:
        dict: A dictionary where keys are priorities (0, 1, 2) and values are lists of packets
              with that priority.
    """
    priority_queues = {0: [], 1: [], 2: []}  # Initialize priority queues
    for packet in packets:
        priority_queues[packet['priority']].append(packet)  # Add packet to the correct queue
    return priority_queues  # Return the priority queues

# Approach 5: Memory-Optimized Sorting (Low RAM Environments)
def memory_optimized_sort(arr):
    """
    Sorts an array with three unique values (0, 1, 2) with minimal extra memory usage.
    This approach is suitable for environments with limited RAM.

    It works by iterating through the array multiple times, each time placing the
    correct number in its place.

    Args:
       arr (list): The input list containing elements with values 0, 1, or 2.

    Returns:
        list: The sorted list.
    """
    index = 0  # Initialize index to track the position for the next sorted element
    for i in range(3):  # Iterate through each unique value (0, 1, 2)
        for j in range(len(arr)):  # Iterate through the array
            if arr[j] == i:  # If the current element equals the target value
                arr[index], arr[j] = arr[j], arr[index]  # Swap the elements
                index += 1  # Increment the index
    return arr # Return sorted array

# Approach 6: Machine Learning Preprocessing (Feature Binning for Categorization)
def ml_feature_binning(features):
    """
    Bins continuous numerical features into three categories (0, 1, 2) based on predefined bins.
    This is a common preprocessing step in machine learning to convert continuous
    variables into categorical ones, which can be useful for certain algorithms.

    Args:
        features (list): A list of continuous numerical features.

    Returns:
        list: A list of binned features, where each value is 0, 1, or 2.
    """
    import numpy as np  # Import numpy
    binned_features = np.digitize(features, bins=[0.5, 1.5])  # Bin features using numpy.digitize
    return binned_features.tolist()  # Convert numpy array to list

# Test Cases
data = [2, 0, 2, 1, 1, 0, 0, 2, 1]
records = [(1, 0), (2, 1), (3, 2), (4, 0), (5, 1)]
packets = [{'priority': 2, 'data': 'A'}, {'priority': 1, 'data': 'B'}, {'priority': 0, 'data': 'C'}]
features = [0.2, 1.3, 2.1, 1.5, 0.8]

print("In-Place Sorting:", in_place_sorting(data.copy()))
print("Distributed Sorting:", distributed_sorting(data.copy()))
print("Database Partitioning:", database_partitioning(records))
print("Network Packet Sorting:", network_packet_sorting(packets))
print("Memory Optimized Sort:", memory_optimized_sort(data.copy()))
print("ML Feature Binning:", ml_feature_binning(features))
