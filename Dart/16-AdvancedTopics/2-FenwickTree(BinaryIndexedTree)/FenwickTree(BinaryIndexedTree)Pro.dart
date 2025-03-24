import 'dart:math';

void main() {
  // Example usage for all implementations
  List<double> sensorData = [12.5, 15.2, 10.8, 18.1, 14.7, 9.5, 16.3, 11.9];
  int n = sensorData.length;

  // Approach 1: Basic Fenwick Tree (for educational purposes)
  print("Approach 1 - Basic Fenwick Tree:");
  FenwickTreeBasic basicTree = FenwickTreeBasic(n);
  for (int i = 0; i < n; i++) {
    basicTree.update(i, sensorData[i].toInt()); // Store as int for simplicity
  }
  print("Sum of first 4 elements: ${basicTree.query(3)}");
  basicTree.update(2, 5);
  print("Sum of first 4 elements after update: ${basicTree.query(3)}");

  // Approach 2: Fenwick Tree for Real-Time Data Analysis (Sensor Data)
  print("\nApproach 2 - Real-Time Data Analysis (Sensor Data):");
  RealTimeDataAnalyzer analyzer = RealTimeDataAnalyzer(sensorData);
  print("Initial total sensor reading: ${analyzer.getTotalReading()}");
  print("Sum of first 3 sensor data points: ${analyzer.getPartialSum(2)}");
  analyzer.updateSensorData(1, 17.5); // Simulate updated sensor reading
  print("Total sensor reading after update: ${analyzer.getTotalReading()}");
  print("Sum of first 3 sensor data points after update: ${analyzer.getPartialSum(2)}");

  // Approach 3: Fenwick Tree for E-commerce Analytics (Product Sales)
  print("\nApproach 3 - E-commerce Analytics (Product Sales):");
  SalesDataTracker salesTracker = SalesDataTracker(n); // Assuming n products
  for (int i = 0; i < n; i++) {
    salesTracker.updateSales(i, sensorData[i]); // Use sensor data as initial sales
  }

  print("Total sales: ${salesTracker.getTotalSales()}");
  print("Sales of first 5 products: ${salesTracker.getSalesForProducts(4)}");
  salesTracker.updateSales(2, 25.0); // Simulate a sale
  print("Total sales after update: ${salesTracker.getTotalSales()}");
  print("Sales of first 5 products after update: ${salesTracker.getSalesForProducts(4)}");

  // Approach 4:  Fenwick Tree for Financial Data Analysis
  print("\nApproach 4 - Financial Data Analysis:");
  FinancialDataAnalyzer financialAnalyzer = FinancialDataAnalyzer(sensorData);
  print("Total value: ${financialAnalyzer.getTotalValue()}");
  print("Value till index 3: ${financialAnalyzer.getValueTill(2)}");

  financialAnalyzer.updateValue(1, 20.0);
  print("Total value after update: ${financialAnalyzer.getTotalValue()}");
  print("Value till index 3 after update: ${financialAnalyzer.getValueTill(2)}");

  // Approach 5: Fenwick Tree for Game Development (Score Tracking)
  print("\nApproach 5 - Game Development (Score Tracking):");
  ScoreTracker scoreTracker = ScoreTracker(n); // For n players
  for (int i = 0; i < n; i++) {
    scoreTracker.updateScore(i, sensorData[i].toInt()); // Use sensor data as initial scores
  }
  print("Total score: ${scoreTracker.getTotalScore()}");
  print("Player scores till 4: ${scoreTracker.getScoreTill(3)}");
  scoreTracker.updateScore(2, 30);
  print("Total score after update: ${scoreTracker.getTotalScore()}");
  print("Player scores till 4 after update: ${scoreTracker.getScoreTill(3)}");

  // Approach 6:  Fenwick Tree for Inventory Management
  print("\nApproach 6 - Inventory Management:");
  InventoryManager inventoryManager = InventoryManager(sensorData.map((e) => e.toInt()).toList()); // Sensor data as initial inventory
  print("Total inventory: ${inventoryManager.getTotalInventory()}");
  print("Inventory till item 5: ${inventoryManager.getInventoryTill(4)}");
  inventoryManager.updateInventory(2, 10);
  print("Total inventory after update: ${inventoryManager.getTotalInventory()}");
  print("Inventory till item 5 after update: ${inventoryManager.getInventoryTill(4)}");
}

// Approach 1: Basic Fenwick Tree (for educational purposes)
class FenwickTreeBasic {
  late List<int> tree;
  int n;

  FenwickTreeBasic(this.n) {
    tree = List.filled(n + 1, 0);
  }

  void update(int index, int value) {
    index++;
    while (index <= n) {
      tree[index] += value;
      index += (index & -index);
    }
  }

  int query(int index) {
    index++;
    int sum = 0;
    while (index > 0) {
      sum += tree[index];
      index -= (index & -index);
    }
    return sum;
  }
}

// Approach 2: Fenwick Tree for Real-Time Data Analysis (Sensor Data)
class RealTimeDataAnalyzer {
  late List<double> tree;
  int n;
  late List<double> originalData;

  RealTimeDataAnalyzer(List<double> data) : n = data.length {
    tree = List.filled(n + 1, 0.0);
    originalData = List.from(data);
    for (int i = 0; i < n; i++) {
      _updateTree(i, data[i]);
    }
  }

  void _updateTree(int index, double value) {
    index++;
    while (index <= n) {
      tree[index] += value;
      index += (index & -index);
    }
  }

  void updateSensorData(int index, double newValue) {
    double diff = newValue - originalData[index];
    originalData[index] = newValue;
    _updateTree(index, diff);
  }

  double getTotalReading() {
    return _queryTree(n - 1);
  }

  double getPartialSum(int index) {
    return _queryTree(index);
  }

  double _queryTree(int index) {
    index++;
    double sum = 0.0;
    while (index > 0) {
      sum += tree[index];
      index -= (index & -index);
    }
    return sum;
  }
}

// Approach 3: Fenwick Tree for E-commerce Analytics (Product Sales)
class SalesDataTracker {
  late List<double> salesTree;
  int n;

  SalesDataTracker(this.n) {
    salesTree = List.filled(n + 1, 0.0);
  }

  void updateSales(int productIndex, double sales) {
    int index = productIndex + 1;
    while (index <= n) {
      salesTree[index] += sales;
      index += (index & -index);
    }
  }

  double getTotalSales() {
    double total = 0.0;
    int index = n;
    while (index > 0) {
      total += salesTree[index];
      index -= (index & -index);
    }
    return total;
  }

  double getSalesForProducts(int productIndex) {
    double sum = 0.0;
    int index = productIndex + 1;
    while (index > 0) {
      sum += salesTree[index];
      index -= (index & -index);
    }
    return sum;
  }
}

// Approach 4: Fenwick Tree for Financial Data Analysis
class FinancialDataAnalyzer {
  late List<double> tree;
  int n;
  late List<double> originalValues;

  FinancialDataAnalyzer(List<double> data) : n = data.length {
    tree = List.filled(n + 1, 0.0);
    originalValues = List.from(data);
    for (int i = 0; i < n; i++) {
      _updateTree(i, data[i]);
    }
  }

  void _updateTree(int index, double value) {
    index++;
    while (index <= n) {
      tree[index] += value;
      index += (index & -index);
    }
  }

  void updateValue(int index, double newValue) {
    double diff = newValue - originalValues[index];
    originalValues[index] = newValue;
    _updateTree(index, diff);
  }

  double getTotalValue() {
    return _queryTree(n - 1);
  }

  double getValueTill(int index) {
    return _queryTree(index);
  }

  double _queryTree(int index) {
    index++;
    double sum = 0.0;
    while (index > 0) {
      sum += tree[index];
      index -= (index & -index);
    }
    return sum;
  }
}

// Approach 5: Fenwick Tree for Game Development (Score Tracking)
class ScoreTracker {
  late List<int> scoreTree;
  int n;

  ScoreTracker(this.n) {
    scoreTree = List.filled(n + 1, 0);
  }

  void updateScore(int playerIndex, int score) {
    int index = playerIndex + 1;
    while (index <= n) {
      scoreTree[index] += score;
      index += (index & -index);
    }
  }

  int getTotalScore() {
    int total = 0;
    int index = n;
    while (index > 0) {
      total += scoreTree[index];
      index -= (index & -index);
    }
    return total;
  }

  int getScoreTill(int playerIndex) {
    int sum = 0;
    int index = playerIndex + 1;
    while (index > 0) {
      sum += scoreTree[index];
      index -= (index & -index);
    }
    return sum;
  }
}

// Approach 6: Fenwick Tree for Inventory Management
class InventoryManager {
  late List<int> inventoryTree;
  int n;
  late List<int> originalInventory;

  InventoryManager(List<int> initialInventory) : n = initialInventory.length {
    inventoryTree = List.filled(n + 1, 0);
    originalInventory = List.from(initialInventory);
    for (int i = 0; i < n; i++) {
      _updateTree(i, initialInventory[i]);
    }
  }

  void _updateTree(int index, int value) {
    index++;
    while (index <= n) {
      inventoryTree[index] += value;
      index += (index & -index);
    }
  }

  void updateInventory(int itemIndex, int change) {
    originalInventory[itemIndex] += change;
    _updateTree(itemIndex, change);
  }

  int getTotalInventory() {
    return _queryTree(n - 1);
  }

  int getInventoryTill(int itemIndex) {
    return _queryTree(itemIndex);
  }

  int _queryTree(int index) {
    index++;
    int sum = 0;
    while (index > 0) {
      sum += inventoryTree[index];
      index -= (index & -index);
    }
    return sum;
  }
}
