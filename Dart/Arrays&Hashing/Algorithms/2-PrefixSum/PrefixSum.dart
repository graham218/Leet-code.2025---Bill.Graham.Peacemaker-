class PrefixSum {
  /// Approach 1: Simple Prefix Sum Calculation (O(n))
  List<int> computePrefixSum(List<int> nums) {
    List<int> prefixSum = List.filled(nums.length, 0);
    prefixSum[0] = nums[0];

    for (int i = 1; i < nums.length; i++) {
      prefixSum[i] = prefixSum[i - 1] + nums[i];
    }
    return prefixSum;
  }

  /// Approach 2: Query Range Sum using Prefix Sum (O(1) per query)
  int rangeSum(List<int> prefixSum, int left, int right) {
    return left == 0 ? prefixSum[right] : prefixSum[right] - prefixSum[left - 1];
  }

  /// Approach 3: 2D Prefix Sum for Matrix (O(n*m) Preprocessing, O(1) Query)
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

  /// Approach 4: Space Optimized Prefix Sum (for large data sets)
  int optimizedPrefixSum(List<int> nums, int start, int end) {
    int sum = 0;
    for (int i = start; i <= end; i++) {
      sum += nums[i];
    }
    return sum;
  }

  /// Approach 5: Parallel Processing for Prefix Sum (using asynchronous computation)
  Future<List<int>> parallelPrefixSum(List<int> nums) async {
    return await Future(() => computePrefixSum(nums));
  }
}

void main() async {
  List<int> nums = [1, 2, 3, 4, 5];
  PrefixSum ps = PrefixSum();

  print("Prefix Sum: ${ps.computePrefixSum(nums)}");
  print("Range Sum (1 to 3): ${ps.rangeSum(ps.computePrefixSum(nums), 1, 3)}");
  print("Optimized Range Sum (2 to 4): ${ps.optimizedPrefixSum(nums, 2, 4)}");
  print("Parallel Prefix Sum: ${await ps.parallelPrefixSum(nums)}");

  List<List<int>> matrix = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
  ];
  print("2D Prefix Sum: ${ps.compute2DPrefixSum(matrix)}");
}
