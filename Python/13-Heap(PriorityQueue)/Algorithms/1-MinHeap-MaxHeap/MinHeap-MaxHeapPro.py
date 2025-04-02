import heapq  # Python's built-in heap implementation
import random
import time
from dataclasses import dataclass
from typing import Any, List, Optional, Tuple, Callable

# ======================================================================================================================
# 1. Basic Min Heap with heapq (Library Implementation)
# ======================================================================================================================
#   - Uses Python's `heapq` module, which provides an efficient implementation of the heap queue algorithm.
#   - This is the most straightforward and recommended way to use heaps in Python.
#   - Real-world application: Task scheduling, finding the smallest element quickly.
#   - Key Concepts:
#     - `heapq.heappush(heap, item)`: Pushes the item onto the heap, maintaining the heap invariant.
#     - `heapq.heappop(heap)`: Pops and returns the smallest item from the heap, maintaining the heap invariant.
#     - `heapq.heapify(list)`: Transforms a list into a heap, in-place, in linear time.
#   - Example: Implementing a priority queue for tasks where lower numbers indicate higher priority.
def basic_min_heap_example():
    print("\n[1. Basic Min Heap with heapq]")
    task_queue = []  # Initialize an empty list to represent the heap
    tasks = [
        (3, "Low Priority Task"),  # (priority, task_name)
        (1, "High Priority Task"),
        (2, "Medium Priority Task"),
        (5, "Very Low Priority Task"),
        (4, "Lower Medium Priority Task"),
        (1, "Another High Priority Task")
    ]

    # Push tasks onto the heap.  Lower number = higher priority.
    for priority, task_name in tasks:
        heapq.heappush(task_queue, (priority, task_name))  # Push as a tuple

    print("Task queue (heap):", task_queue)  # Output the heap structure (not necessarily sorted)

    # Pop tasks from the heap in priority order
    print("Processing tasks in priority order:")
    while task_queue:
        priority, task_name = heapq.heappop(task_queue)
        print(f"  Priority {priority}: {task_name}")  # tasks are printed in sorted order based on priority

    # Example of using heapify on an existing list
    numbers = [5, 2, 9, 1, 5, 6]
    print("\nOriginal list:", numbers)
    heapq.heapify(numbers)  # In-place heapification
    print("Heapified list:", numbers)
    print("Popping elements:", [heapq.heappop(numbers) for _ in range(len(numbers))]) # prints in sorted order

# ======================================================================================================================
# 2. Max Heap Implementation using heapq (by negating values)
# ======================================================================================================================
#   - Python's `heapq` directly implements a min-heap. To simulate a max-heap, we can negate the values
#     before pushing them onto the heap, and then negate them again when popping.
#   - Real-world application: Finding the largest elements, e.g., top-N scores in a game.
#   - Key Concepts:
#     - Negating values to reverse the order.
#     - Using a wrapper function for easier max-heap operations.
def max_heap_example():
    print("\n[2. Max Heap Implementation using heapq]")

    def max_heappush(heap, item):
        heapq.heappush(heap, -item)  # Negate before pushing

    def max_heappop(heap):
        return -heapq.heappop(heap)  # Negate after popping

    scores = [85, 92, 78, 95, 88, 90]
    max_heap = []
    for score in scores:
        max_heappush(max_heap, score)

    print("Scores (max heap):", [-x for x in max_heap])  # Show original values

    print("Top 3 scores:")
    for _ in range(3):
        print(" ", max_heappop(max_heap))

# ======================================================================================================================
# 3. Heap of Custom Objects using Tuples (Min Heap)
# ======================================================================================================================
#   -  Using tuples as elements in the heap, where the first element of the tuple is used for comparison
#   -  Real-world application: Event scheduling based on timestamps, task management with priorities and deadlines.
#   -  Key Concepts:
#      -  Tuples are compared lexicographically (element by element).
#      -  The first element in the tuple determines the priority.
#   -  Important:
#       - If the first items are equal, the second item is compared, and so on.
#       - If you have complex objects, use a custom class and define a `__lt__` method.
def custom_object_heap_example():
    print("\n[3. Heap of Custom Objects using Tuples (Min Heap)]")
    events = [
        (1678886400, "Meeting with Team A"),  # (timestamp, event_name) - 2023-03-15
        (1678972800, "Project Deadline"),       # 2023-03-16
        (1678800000, "Team Lunch"),           # 2023-03-14
        (1679059200, "Client Presentation"),    # 2023-03-17
        (1678886400, "Meeting with Team B") # 2023-03-15, same time as Team A
    ]

    event_queue = []
    for event in events:
        heapq.heappush(event_queue, event)

    print("Event queue (min heap, based on timestamp):")
    for item in event_queue:
        print("  ", item)

    print("\nUpcoming events:")
    while event_queue:
        timestamp, event_name = heapq.heappop(event_queue)
        print(f"  {event_name} at {time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(timestamp))}")

# ======================================================================================================================
# 4. Heap of Custom Objects using a Class and __lt__ (Min Heap)
# ======================================================================================================================
#   -  Defining a custom class and overriding the `__lt__` (less than) method to define the comparison logic for the heap.
#   -  Real-world application:  Managing objects with complex priority rules, like tasks with priority and creation time.
#   - Key Concepts:
#     -  The `__lt__` method defines how instances of the class are compared.
#     -  The heap uses this method to maintain the heap property.
#   -  Important:
#      -  For min-heap, `self < other` should return True if `self` has higher priority than `other`.
@dataclass
class Task:
    priority: int
    description: str
    created_at: float  # Add a timestamp for more complex comparisons

    def __lt__(self, other):
        # Lower priority value means higher priority.  If priorities are equal, compare creation time.
        if self.priority != other.priority:
            return self.priority < other.priority
        return self.created_at < other.created_at # If priorities equal, earlier created task is higher

def custom_class_heap_example():
    print("\n[4. Heap of Custom Objects using a Class and __lt__ (Min Heap)]")
    tasks = [
        Task(3, "Cleanup Database", time.time() - 60),
        Task(1, "Fix Critical Bug", time.time()),
        Task(2, "Implement New Feature", time.time() - 30),
        Task(1, "Another Critical Bug", time.time() - 10),
        Task(3, "Refactor Code", time.time() - 120),
    ]

    task_queue = []
    for task in tasks:
        heapq.heappush(task_queue, task)

    print("Task queue (min heap, based on priority and creation time):")
    for task in task_queue:
        print(f"  Priority {task.priority}: {task.description} (Created at: {time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(task.created_at))})")

    print("\nProcessing tasks:")
    while task_queue:
        task = heapq.heappop(task_queue)
        print(f"  Priority {task.priority}: {task.description}")

# ======================================================================================================================
# 5.  K Largest Elements from a List
# ======================================================================================================================
#   -  Finding the k largest elements in a list using a min-heap.
#   -  Real-world application: Top-k ranking, finding the most frequent items, outlier detection.
#   - Key Concepts:
#     -  Maintain a min-heap of size k.
#     -  Iterate through the rest of the elements, replacing the smallest element in the heap
#        if the current element is larger.
#   - Efficiency: O(N log k), where N is the size of the input list.
def k_largest_elements(numbers: List[int], k: int) -> List[int]:
    """
    Finds the k largest elements in a list.

    Args:
        numbers: The list of numbers.
        k: The number of largest elements to find.

    Returns:
        A list containing the k largest elements.
    """
    if k <= 0:
        return []
    if k >= len(numbers):
        return sorted(numbers, reverse=True)  # if k is larger than list, just sort

    heap = numbers[:k]  # Initialize heap with the first k elements
    heapq.heapify(heap)  # Convert the first k elements into a min-heap

    for i in range(k, len(numbers)):
        if numbers[i] > heap[0]:  # If the current element is larger than the smallest in the heap
            heapq.heapreplace(heap, numbers[i])  # Replace the smallest with the current

    return sorted(heap, reverse=True)  # Sort the heap to get the k largest in descending order

def k_largest_example():
    print("\n[5. K Largest Elements from a List]")
    numbers = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]
    k = 3
    largest_numbers = k_largest_elements(numbers, k)
    print(f"The {k} largest numbers in {numbers} are: {largest_numbers}")

    k = 5
    largest_numbers = k_largest_elements(numbers, k)
    print(f"The {k} largest numbers in {numbers} are: {largest_numbers}")

# ======================================================================================================================
# 6. Median Maintenance using Heaps
# ======================================================================================================================
#   -  Maintaining the median of a stream of numbers using two heaps: a max-heap for the smaller half and a min-heap for the larger half.
#   -  Real-world application: Real-time data analysis, tracking percentiles, financial data processing.
#   - Key Concepts:
#     -  Max-heap stores the smaller half of the numbers.
#     -  Min-heap stores the larger half of the numbers.
#     -  The heaps are balanced to ensure that the median can be calculated efficiently.
#   - Efficiency: O(log N) for each insertion, O(1) for getting the median.
def median_maintenance(numbers: List[int]) -> List[float]:
    """
    Calculates the median of a stream of numbers after each insertion.

    Args:
        numbers: The list of numbers representing the stream.

    Returns:
        A list containing the median after each number is added.
    """
    medians = []
    max_heap = []  # Stores the smaller half (max heap)
    min_heap = []  # Stores the larger half (min heap)

    for number in numbers:
        if not max_heap or number <= -max_heap[0]:
            heapq.heappush(max_heap, -number)  # negate for max heap
        else:
            heapq.heappush(min_heap, number)

        # Balance the heaps
        if len(max_heap) > len(min_heap) + 1:
            heapq.heappush(min_heap, -heapq.heappop(max_heap))
        elif len(min_heap) > len(max_heap):
            heapq.heappush(max_heap, -heapq.heappop(min_heap))

        # Calculate the median
        if len(max_heap) == len(min_heap):
            median = (-max_heap[0] + min_heap[0]) / 2.0
        else:
            median = -max_heap[0]  # max_heap has one more element
        medians.append(median)
    return medians

def median_maintenance_example():
    print("\n[6. Median Maintenance using Heaps]")
    stream = [2, 1, 5, 7, 2, 0, 5]
    medians = median_maintenance(stream)
    print(f"Medians of the stream {stream} are: {medians}")

if __name__ == "__main__":
    basic_min_heap_example()
    max_heap_example()
    custom_object_heap_example()
    custom_class_heap_example()
    k_largest_example()
    median_maintenance_example()
