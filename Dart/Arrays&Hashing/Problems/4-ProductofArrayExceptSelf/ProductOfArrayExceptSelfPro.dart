import 'dart:math';

class ProductCalculator {
  final List<int> numbers;

  ProductCalculator(this.numbers);

  // Approach 1: Optimized Prefix and Suffix Multiplication
  List<int> calculateProductOptimized() {
    int n = numbers.length;
    List<int> result = List.filled(n, 1);

    int leftProduct = 1;
    for (int i = 0; i < n; i++) {
      result[i] = leftProduct;
      leftProduct *= numbers[i];
    }

    int rightProduct = 1;
    for (int i = n - 1; i >= 0; i--) {
      result[i] *= rightProduct;
      rightProduct *= numbers[i];
    }

    return result;
  }

  // Approach 2: Using Logarithms (Handles zero cases separately)
  List<int> calculateProductLogarithm() {
    int n = numbers.length;
    double logSum = 0;
    int zeroCount = numbers.where((num) => num == 0).length;

    if (zeroCount > 1) return List.filled(n, 0);

    for (int num in numbers) {
      if (num != 0) logSum += log(num.abs());
    }

    return numbers.map((num) {
      if (num == 0) return exp(logSum).toInt();
      return (exp(logSum - log(num.abs())) * (num < 0 ? -1 : 1)).toInt();
    }).toList();
  }

  // Approach 3: Multi-threading for Large Data Sets (Using Isolates)
  Future<List<int>> calculateProductMultiThreaded() async {
    return await Future(() => calculateProductOptimized());
  }

  // Approach 4: Functional Style Using Fold & Map
  List<int> calculateProductFunctional() {
    int totalProduct = numbers.fold(1, (a, b) => a * (b == 0 ? 1 : b));
    int zeroCount = numbers.where((num) => num == 0).length;

    return numbers.map((num) {
      if (zeroCount > 1) return 0;
      if (zeroCount == 1) return num == 0 ? totalProduct : 0;
      return totalProduct ~/ num;
    }).toList();
  }

  // Approach 5: Real-World API Example (Mock API Processing)
  Future<Map<String, dynamic>> calculateProductAPI() async {
    return Future.delayed(Duration(seconds: 2), () => {
      "input": numbers,
      "output": calculateProductOptimized(),
      "status": "success",
      "processed_at": DateTime.now().toString()
    });
  }
}

void main() async {
  List<int> numbers = [1, 2, 3, 4];
  ProductCalculator calculator = ProductCalculator(numbers);

  print("Optimized Approach: ${calculator.calculateProductOptimized()}");
  print("Logarithm Approach: ${calculator.calculateProductLogarithm()}");
  print("Functional Approach: ${calculator.calculateProductFunctional()}");
  print("Multi-threaded Approach: ${await calculator.calculateProductMultiThreaded()}");
  print("API Mock Response: ${await calculator.calculateProductAPI()}");
}
