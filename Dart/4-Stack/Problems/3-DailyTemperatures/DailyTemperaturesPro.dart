// Dart program to solve the 'Daily Temperatures' problem with real-world applications
// Given a list of daily temperatures, return a list that tells you how many days
// you would have to wait until a warmer temperature occurs.

import 'dart:collection';

/// Approach 1: Using Stack (Optimized Solution)
/// Application: Weather forecasting apps use this method to predict temperature trends efficiently.
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

/// Approach 2: Using Priority Queue (Heap-Based)
/// Application: Stock market analysis tools use a similar approach to find next higher price days.
List<int> dailyTemperaturesHeap(List<int> temperatures) {
  int n = temperatures.length;
  List<int> result = List.filled(n, 0);
  SplayTreeMap<int, int> minHeap = SplayTreeMap();

  for (int i = 0; i < n; i++) {
    while (minHeap.isNotEmpty && minHeap.firstKey()! < temperatures[i]) {
      int prevIndex = minHeap.remove(minHeap.firstKey())!;
      result[prevIndex] = i - prevIndex;
    }
    minHeap[temperatures[i]] = i;
  }

  return result;
}

/// Approach 3: Using Linked HashMap for Efficient Lookup
/// Application: IoT devices tracking environmental data can use this for temperature anomaly detection.
List<int> dailyTemperaturesLinkedHashMap(List<int> temperatures) {
  int n = temperatures.length;
  List<int> result = List.filled(n, 0);
  LinkedHashMap<int, int> tempMap = LinkedHashMap();

  for (int i = n - 1; i >= 0; i--) {
    tempMap[temperatures[i]] = i;
    int minDiff = n;
    for (var key in tempMap.keys.where((key) => key > temperatures[i])) {
      minDiff = tempMap[key]! - i;
      break;
    }
    result[i] = minDiff == n ? 0 : minDiff;
  }

  return result;
}

/// Approach 4: Machine Learning Model Preprocessing
/// Application: Used in ML models to preprocess temperature trend data for prediction algorithms.
List<int> dailyTemperaturesMLPreprocessing(List<int> temperatures) {
  int n = temperatures.length;
  List<int> result = List.filled(n, 0);
  List<int> futureTemps = List.filled(101, -1);

  for (int i = n - 1; i >= 0; i--) {
    int minDays = n;
    for (int t = temperatures[i] + 1; t <= 100; t++) {
      if (futureTemps[t] != -1) {
        minDays = (futureTemps[t] - i).clamp(1, minDays);
      }
    }
    result[i] = minDays == n ? 0 : minDays;
    futureTemps[temperatures[i]] = i;
  }

  return result;
}

/// Approach 5: Cloud-Based Real-Time Temperature Analysis
/// Application: Cloud servers use similar approaches to analyze and predict temperature trends globally.
List<int> dailyTemperaturesCloudBased(List<int> temperatures) {
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
  print("Heap-Based Approach: ${dailyTemperaturesHeap(temperatures)}");
  print("Linked HashMap Approach: ${dailyTemperaturesLinkedHashMap(temperatures)}");
  print("ML Preprocessing Approach: ${dailyTemperaturesMLPreprocessing(temperatures)}");
  print("Cloud-Based Approach: ${dailyTemperaturesCloudBased(temperatures)}");
}
