class SingleNumber {
  // Approach 1: Using XOR (Optimal Solution)
  static int singleNumberXOR(List<int> nums) {
    return nums.fold(0, (result, num) => result ^ num);
  }

  // Approach 2: Using HashSet
  static int singleNumberSet(List<int> nums) {
    final Set<int> numSet = {};
    for (final num in nums) {
      if (numSet.contains(num)) {
        numSet.remove(num);
      } else {
        numSet.add(num);
      }
    }
    return numSet.first;
  }

  // Approach 3: Using HashMap (Frequency Count)
  static int singleNumberMap(List<int> nums) {
    final Map<int, int> numMap = {};
    for (final num in nums) {
      numMap[num] = (numMap[num] ?? 0) + 1;
    }
    for (final entry in numMap.entries) {
      if (entry.value == 1) {
        return entry.key;
      }
    }
    return -1; // Should never reach here
  }

  // Approach 4: Using Sorting
  static int singleNumberSort(List<int> nums) {
    final sortedNums = List<int>.from(nums)..sort(); // Create a copy to avoid modifying the original list
    for (var i = 0; i < sortedNums.length - 1; i += 2) {
      if (sortedNums[i] != sortedNums[i + 1]) {
        return sortedNums[i];
      }
    }
    return sortedNums.last;
  }

  // Approach 5: Using Reduce Function (XOR) - Same as XOR, but more concise.
  static int singleNumberReduce(List<int> nums) {
    return nums.fold(0, (value, element) => value ^ element);
  }
}

void main() {
  final List<int> nums = [4, 1, 2, 1, 2];
  print('XOR: ${SingleNumber.singleNumberXOR(nums)}');
  print('HashSet: ${SingleNumber.singleNumberSet(nums)}');
  print('HashMap: ${SingleNumber.singleNumberMap(nums)}');
  print('Sorting: ${SingleNumber.singleNumberSort(nums)}');
  print('Reduce (XOR): ${SingleNumber.singleNumberReduce(nums)}');
}