import 'dart:math';

void main() {
  // Execute each example demonstrating Min Heap and Max Heap usage
  stockPriceMinHeap();
  stockPriceMaxHeap();
  eventSchedulerMinHeap();
  taskPriorityMaxHeap();
  customDijkstraMinHeap();
  leaderboardMaxHeap();
}

// Custom Min Heap Implementation
class MinHeap<T> {
  // Internal list to store heap elements
  List<T> _heap = [];

  // Adds a new element to the min heap and maintains the heap property
  void add(T value) {
    _heap.add(value);
    // Sort the list to maintain min-heap property after adding the element
    _heap.sort((a, b) => (a as Comparable).compareTo(b));
  }

  // Removes and returns the minimum element from the heap
  T remove() {
    // Remove the first element (minimum in min-heap)
    return _heap.removeAt(0);
  }

  // Checks if the heap is not empty
  bool get isNotEmpty => _heap.isNotEmpty;
}

// Custom Max Heap Implementation
class MaxHeap<T> {
  // Internal list to store heap elements
  List<T> _heap = [];

  // Adds a new element to the max heap and maintains the heap property
  void add(T value) {
    _heap.add(value);
    // Sort the list in descending order to maintain max-heap property
    _heap.sort((a, b) => (b as Comparable).compareTo(a));
  }

  // Removes and returns the maximum element from the heap
  T remove() {
    // Remove the first element (maximum in max-heap)
    return _heap.removeAt(0);
  }

  // Checks if the heap is not empty
  bool get isNotEmpty => _heap.isNotEmpty;
}

// Approach 1: Stock Price Tracker (Min Heap - Real-time stock price monitoring)
void stockPriceMinHeap() {
  // Create a min heap to store stock prices
  MinHeap<num> stockPrices = MinHeap<num>();
  // Add stock prices to the heap
  stockPrices.add(320);
  stockPrices.add(450);
  stockPrices.add(290);
  stockPrices.add(500);
  stockPrices.add(310);
  // Print stock prices in ascending order (min heap order)
  print("Stock Prices in Ascending Order:");
  while (stockPrices.isNotEmpty) {
    print(stockPrices.remove());
  }
}

// Approach 2: Stock Price Tracker (Max Heap - Finding highest stock price quickly)
void stockPriceMaxHeap() {
  // Create a max heap to store stock prices
  MaxHeap<num> stockPrices = MaxHeap<num>();
  // Add stock prices to the heap
  stockPrices.add(320);
  stockPrices.add(450);
  stockPrices.add(290);
  stockPrices.add(500);
  stockPrices.add(310);
  // Print stock prices in descending order (max heap order)
  print("Stock Prices in Descending Order:");
  while (stockPrices.isNotEmpty) {
    print(stockPrices.remove());
  }
}

// Approach 3: Event Scheduler (Min Heap - Scheduling events by nearest time)
class Event implements Comparable<Event> {
  // Event properties: name and time
  String name;
  DateTime time;
  // Constructor for Event
  Event(this.name, this.time);
  // Compare events based on their time for min heap sorting
  @override
  int compareTo(Event other) => time.compareTo(other.time);
}

void eventSchedulerMinHeap() {
  // Create a min heap to store events
  MinHeap<Event> eventQueue = MinHeap<Event>();
  // Add events to the heap
  eventQueue.add(Event("Meeting", DateTime(2025, 6, 15, 10, 30)));
  eventQueue.add(Event("Conference", DateTime(2025, 6, 14, 9, 00)));
  eventQueue.add(Event("Workshop", DateTime(2025, 6, 16, 14, 00)));
  // Print events in chronological order (min heap order)
  print("Upcoming Events:");
  while (eventQueue.isNotEmpty) {
    Event e = eventQueue.remove();
    print("${e.name} at ${e.time}");
  }
}

// Approach 4: Task Priority Manager (Max Heap - Prioritizing tasks)
class Task implements Comparable<Task> {
  // Task properties: description and priority
  String description;
  int priority;
  // Constructor for Task
  Task(this.description, this.priority);
  // Compare tasks based on their priority for max heap sorting
  @override
  int compareTo(Task other) => priority.compareTo(other.priority);
}

void taskPriorityMaxHeap() {
  // Create a max heap to store tasks
  MaxHeap<Task> taskQueue = MaxHeap<Task>();
  // Add tasks to the heap
  taskQueue.add(Task("Fix critical bug", 10));
  taskQueue.add(Task("Code review", 6));
  taskQueue.add(Task("Write documentation", 3));
  // Print tasks in priority order (max heap order)
  print("Task Priority List:");
  while (taskQueue.isNotEmpty) {
    Task t = taskQueue.remove();
    print("${t.description} (Priority: ${t.priority})");
  }
}

// Approach 5: Dijkstra's Algorithm for Shortest Path (Min Heap)
class GraphNode implements Comparable<GraphNode> {
  // Graph node properties: node and distance
  int node;
  int distance;
  // Constructor for GraphNode
  GraphNode(this.node, this.distance);
  // Compare graph nodes based on their distance for min heap sorting
  @override
  int compareTo(GraphNode other) => distance.compareTo(other.distance);
}

void customDijkstraMinHeap() {
  // Create a min heap to store graph nodes
  MinHeap<GraphNode> minHeap = MinHeap<GraphNode>();
  // Add graph nodes to the heap
  minHeap.add(GraphNode(1, 10));
  minHeap.add(GraphNode(2, 5));
  minHeap.add(GraphNode(3, 15));
  // Print graph nodes in shortest distance order (min heap order)
  print("Processing Nodes in Shortest Distance Order:");
  while (minHeap.isNotEmpty) {
    GraphNode node = minHeap.remove();
    print("Node ${node.node} (Distance: ${node.distance})");
  }
}

// Approach 6: Gaming Leaderboard (Max Heap - Highest Scores First)
class Player implements Comparable<Player> {
  // Player properties: name and score
  String name;
  int score;
  // Constructor for Player
  Player(this.name, this.score);
  // Compare players based on their score for max heap sorting
  @override
  int compareTo(Player other) => score.compareTo(other.score);
}

void leaderboardMaxHeap() {
  // Create a max heap to store players
  MaxHeap<Player> leaderboard = MaxHeap<Player>();
  // Add players to the heap
  leaderboard.add(Player("Alice", 1200));
  leaderboard.add(Player("Bob", 1500));
  leaderboard.add(Player("Charlie", 1100));
  // Print players in descending score order (max heap order)
  print("Leaderboard:");
  while (leaderboard.isNotEmpty) {
    Player p = leaderboard.remove();
    print("${p.name} (Score: ${p.score})");
  }
}