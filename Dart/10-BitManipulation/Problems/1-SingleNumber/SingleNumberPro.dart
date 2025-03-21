class SingleNumberAdvanced {
  // Approach 1: XOR Method (Optimal Solution)
  static int singleNumberXOR(List<int> nums) {
    return nums.fold(0, (acc, num) => acc ^ num);
  }

  // Approach 2: HashSet for Unique Tracking
  static int singleNumberSet(List<int> nums) {
    final Set<int> numSet = {};
    for (final num in nums) {
      if (!numSet.add(num)) {
        numSet.remove(num);
      }
    }
    return numSet.first;
  }

  // Approach 3: HashMap Frequency Counter
  static int singleNumberMap(List<int> nums) {
    final Map<int, int> numMap = {};
    for (final num in nums) {
      numMap[num] = (numMap[num] ?? 0) + 1;
    }
    return numMap.entries.firstWhere((entry) => entry.value == 1).key;
  }

  // Approach 4: Mathematical Sum Formula
  static int singleNumberMath(List<int> nums) {
    final int uniqueSum = nums.toSet().fold(0, (a, b) => a + b); // Use fold for clarity
    final int actualSum = nums.fold(0, (a, b) => a + b); // Use fold for clarity
    return 2 * uniqueSum - actualSum;
  }

  // Approach 5: Sorting and Pairing
  static int singleNumberSort(List<int> nums) {
    final sortedNums = List<int>.from(nums)..sort(); // Create a copy
    for (var i = 0; i < sortedNums.length - 1; i += 2) {
      if (sortedNums[i] != sortedNums[i + 1]) return sortedNums[i];
    }
    return sortedNums.last;
  }

  // Approach 6: Bitwise AND & XOR Combo (For Large Datasets)
  static int singleNumberBitwise(List<int> nums) {
    int ones = 0, twos = 0;
    for (final num in nums) {
      ones = (ones ^ num) & ~twos;
      twos = (twos ^ num) & ~ones;
    }
    return ones;
  }
}

void main() {
  final List<int> nums = [7, 3, 5, 3, 5, 7, 9];
  print('XOR: ${SingleNumberAdvanced.singleNumberXOR(nums)}');
  print('HashSet: ${SingleNumberAdvanced.singleNumberSet(nums)}');
  print('HashMap: ${SingleNumberAdvanced.singleNumberMap(nums)}');
  print('Math: ${SingleNumberAdvanced.singleNumberMath(nums)}');
  print('Sort: ${SingleNumberAdvanced.singleNumberSort(nums)}');
  print('Bitwise: ${SingleNumberAdvanced.singleNumberBitwise(nums)}');
}