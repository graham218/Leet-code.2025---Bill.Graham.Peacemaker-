// Dart program to solve the 'Daily Temperatures' problem using five different approaches
// Given a list of daily temperatures, return a list that tells you how many days
// you would have to wait until a warmer temperature occurs.

import 'dart:collection';

/// Approach 1: Using Stack (Optimized Solution)
/// Time Complexity: O(n)
/// Space Complexity: O(n)
List<int> dailyTemperaturesStack(List<int> temperatures) {
  int n = temperatures.length;
  List<int> result = List.filled(n, 0);
  List<int> stack = [];

  for (int i = 0; i < n; i++) {
    while (stack.isNotEmpty && temperatures[i] > temperatures[stack.last]) {
      int prevIndex = stack.removeLast();
      result[prevIndex] = i - prevIndex;
    }
    stack.add(i);
  }

  return result;
}

/// Approach 2: Brute Force (Naive Solution)
/// Time Complexity: O(n^2)
/// Space Complexity: O(1)
List<int> dailyTemperaturesBruteForce(List<int> temperatures) {
  int n = temperatures.length;
  List<int> result = List.filled(n, 0);

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (temperatures[j] > temperatures[i]) {
        result[i] = j - i;
        break;
      }
    }
  }

  return result;
}

/// Approach 3: Using a Queue (Breadth-First Processing)
/// Time Complexity: O(n)
/// Space Complexity: O(n)
List<int> dailyTemperaturesQueue(List<int> temperatures) {
  int n = temperatures.length;
  List<int> result = List.filled(n, 0);
  Queue<int> queue = Queue();

  for (int i = 0; i < n; i++) {
    while (queue.isNotEmpty && temperatures[i] > temperatures[queue.first]) {
      int prevIndex = queue.removeFirst();
      result[prevIndex] = i - prevIndex;
    }
    queue.addLast(i);
  }

  return result;
}

/// Approach 4: Reverse Traversal with Caching
/// Time Complexity: O(n)
/// Space Complexity: O(n)
List<int> dailyTemperaturesReverse(List<int> temperatures) {
  int n = temperatures.length;
  List<int> result = List.filled(n, 0);
  int maxTemp = 0;

  for (int i = n - 1; i >= 0; i--) {
    if (temperatures[i] >= maxTemp) {
      maxTemp = temperatures[i];
      continue;
    }
    int days = 1;
    while (temperatures[i + days] <= temperatures[i]) {
      days += result[i + days];
    }
    result[i] = days;
  }

  return result;
}

/// Approach 5: Binary Search for Next Warmer Day
/// Time Complexity: O(n log n)
/// Space Complexity: O(n)
List<int> dailyTemperaturesBinarySearch(List<int> temperatures) {
  int n = temperatures.length;
  List<int> result = List.filled(n, 0);
  SplayTreeMap<int, int> tempMap = SplayTreeMap();

  for (int i = n - 1; i >= 0; i--) {
    var higher = tempMap.keys.where((key) => key > temperatures[i]).isNotEmpty
        ? tempMap[tempMap.keys.firstWhere((key) => key > temperatures[i])]
        : null;
    if (higher != null) {
      result[i] = higher - i;
    }
    tempMap[temperatures[i]] = i;
  }

  return result;
}

void main() {
  List<int> temperatures = [73, 74, 75, 71, 69, 72, 76, 73];
  print("Stack Approach: ${dailyTemperaturesStack(temperatures)}");
  print("Brute Force Approach: ${dailyTemperaturesBruteForce(temperatures)}");
  print("Queue Approach: ${dailyTemperaturesQueue(temperatures)}");
  print("Reverse Traversal Approach: ${dailyTemperaturesReverse(temperatures)}");
  print("Binary Search Approach: ${dailyTemperaturesBinarySearch(temperatures)}");
}
