import 'dart:async';

class AdvancedPrefixSum {
  /// Approach 1: Standard Prefix Sum (for cumulative sums in analytics)
  List<int> computePrefixSum(List<int> nums) {
    List<int> prefixSum = List.filled(nums.length, 0);
    prefixSum[0] = nums[0];

    for (int i = 1; i < nums.length; i++) {
      prefixSum[i] = prefixSum[i - 1] + nums[i];
    }
    return prefixSum;
  }

  /// Approach 2: Efficient Range Sum Queries (for financial transactions analysis)
  int rangeSum(List<int> prefixSum, int left, int right) {
    return left == 0 ? prefixSum[right] : prefixSum[right] - prefixSum[left - 1];
  }

  /// Approach 3: 2D Prefix Sum (for heatmap data aggregation in geospatial analysis)
  List<List<int>> compute2DPrefixSum(List<List<int>> matrix) {
    int rows = matrix.length;
    int cols = matrix[0].length;
    List<List<int>> prefixSum = List.generate(rows, (_) => List.filled(cols, 0));

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        int top = (i > 0) ? prefixSum[i - 1][j] : 0;
        int left = (j > 0) ? prefixSum[i][j - 1] : 0;
        int topLeft = (i > 0 && j > 0) ? prefixSum[i - 1][j - 1] : 0;
        prefixSum[i][j] = matrix[i][j] + top + left - topLeft;
      }
    }
    return prefixSum;
  }

  /// Approach 4: Streaming Prefix Sum (for processing real-time sensor data)
  Stream<int> streamingPrefixSum(Stream<int> input) async* {
    int sum = 0;
    await for (var value in input) {
      sum += value;
      yield sum;
    }
  }

  /// Approach 5: Parallel Processing (for big data computation)
  Future<List<int>> parallelPrefixSum(List<int> nums) async {
    return await Future(() => computePrefixSum(nums));
  }
}

void main() async {
  List<int> nums = [5, 10, 15, 20, 25];
  AdvancedPrefixSum aps = AdvancedPrefixSum();

  print("Prefix Sum: ${aps.computePrefixSum(nums)}");
  print("Range Sum (1 to 3): ${aps.rangeSum(aps.computePrefixSum(nums), 1, 3)}");
  print("Parallel Prefix Sum: ${await aps.parallelPrefixSum(nums)}");

  // 2D Prefix Sum Example
  List<List<int>> matrix = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
  ];
  print("2D Prefix Sum: ${aps.compute2DPrefixSum(matrix)}");

  // Streaming Prefix Sum Example
  Stream<int> inputStream = Stream.fromIterable(nums);
  aps.streamingPrefixSum(inputStream).listen((sum) => print("Streaming Sum: $sum"));
}
