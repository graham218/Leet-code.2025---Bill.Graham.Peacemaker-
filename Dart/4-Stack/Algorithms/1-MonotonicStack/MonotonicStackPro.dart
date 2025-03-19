// Dart program implementing advanced Monotonic Stack algorithms with real-world applications
// Monotonic stacks are widely used in problems like stock market analysis, temperature forecasting,
// and structural engineering optimizations.

import 'dart:collection';

/// **Approach 1: Stock Price Prediction using Monotonic Stack**
/// Predicts how many days until the stock price increases.
/// Real-world application: Used in financial markets for trend analysis.
List<int> predictStockPrice(List<int> prices) {
  int n = prices.length;
  List<int> result = List.filled(n, 0);
  List<int> stack = [];

  for (int i = 0; i < n; i++) {
    while (stack.isNotEmpty && prices[i] > prices[stack.last]) {
      int prevIndex = stack.removeLast();
      result[prevIndex] = i - prevIndex;
    }
    stack.add(i);
  }
  return result;
}

/// **Approach 2: Earthquake Impact Simulation**
/// Determines the time until a stronger earthquake occurs.
/// Real-world application: Seismologists use similar models to assess aftershock patterns.
List<int> earthquakeImpact(List<int> magnitudes) {
  int n = magnitudes.length;
  List<int> result = List.filled(n, 0);
  List<int> stack = [];

  for (int i = 0; i < n; i++) {
    while (stack.isNotEmpty && magnitudes[i] > magnitudes[stack.last]) {
      int prevIndex = stack.removeLast();
      result[prevIndex] = i - prevIndex;
    }
    stack.add(i);
  }
  return result;
}

/// **Approach 3: Traffic Congestion Analysis**
/// Determines how many seconds it takes for a faster car to appear behind a slow-moving vehicle.
/// Real-world application: Used in intelligent traffic systems for congestion prediction.
List<int> trafficCongestion(List<int> speeds) {
  int n = speeds.length;
  List<int> result = List.filled(n, 0);
  List<int> stack = [];

  for (int i = 0; i < n; i++) {
    while (stack.isNotEmpty && speeds[i] > speeds[stack.last]) {
      int prevIndex = stack.removeLast();
      result[prevIndex] = i - prevIndex;
    }
    stack.add(i);
  }
  return result;
}

/// **Approach 4: Building Sunlight Exposure Calculation**
/// Determines how many buildings block sunlight from each building.
/// Real-world application: Used in urban planning to maximize sunlight exposure.
List<int> sunlightExposure(List<int> buildings) {
  int n = buildings.length;
  List<int> result = List.filled(n, 0);
  List<int> stack = [];

  for (int i = 0; i < n; i++) {
    while (stack.isNotEmpty && buildings[i] > buildings[stack.last]) {
      int prevIndex = stack.removeLast();
      result[prevIndex] = i - prevIndex;
    }
    stack.add(i);
  }
  return result;
}

/// **Approach 5: Cybersecurity Intrusion Detection**
/// Detects abnormal spikes in network activity over time.
/// Real-world application: Used in cybersecurity to prevent DDoS attacks.
List<int> intrusionDetection(List<int> traffic) {
  int n = traffic.length;
  List<int> result = List.filled(n, 0);
  List<int> stack = [];

  for (int i = 0; i < n; i++) {
    while (stack.isNotEmpty && traffic[i] > traffic[stack.last]) {
      int prevIndex = stack.removeLast();
      result[prevIndex] = i - prevIndex;
    }
    stack.add(i);
  }
  return result;
}

void main() {
  List<int> stockPrices = [100, 80, 60, 70, 60, 75, 85];
  print("Stock Price Prediction: ${predictStockPrice(stockPrices)}");

  List<int> earthquakeMagnitudes = [5, 3, 6, 2, 7, 4, 8];
  print("Earthquake Impact: ${earthquakeImpact(earthquakeMagnitudes)}");

  List<int> trafficSpeeds = [40, 35, 30, 50, 45, 60, 55];
  print("Traffic Congestion Analysis: ${trafficCongestion(trafficSpeeds)}");

  List<int> buildingHeights = [50, 45, 55, 60, 42, 58, 65];
  print("Sunlight Exposure: ${sunlightExposure(buildingHeights)}");

  List<int> networkTraffic = [200, 180, 150, 190, 170, 220, 210];
  print("Intrusion Detection: ${intrusionDetection(networkTraffic)}");
}