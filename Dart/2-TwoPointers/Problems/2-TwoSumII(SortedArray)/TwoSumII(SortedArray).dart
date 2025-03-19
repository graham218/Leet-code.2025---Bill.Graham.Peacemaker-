void main() {
  List<int> numbers = [2, 7, 11, 15];
  int target = 9;

  List<int>? result = twoSum(numbers, target);
  if (result != null) {
    print("Indices: ${result[0]}, ${result[1]}");
  } else {
    print("No solution found");
  }

  List<int>? result2 = twoSumUnsorted(numbers, target);
  if (result2 != null) {
    print("Unsorted Indices: ${result2[0]}, ${result2[1]}");
  } else {
    print("No solution found for unsorted list");
  }
}

// Two-pointer approach (requires sorted list)
List<int>? twoSum(List<int> numbers, int target) {
  List<int> sortedNumbers = List.from(numbers); // Create a copy
  sortedNumbers.sort(); // Sort the copied list
  int left = 0, right = sortedNumbers.length - 1;
  while (left < right) {
    int sum = sortedNumbers[left] + sortedNumbers[right];
    if (sum == target) {
      // Find the original indices
      int firstIndex = numbers.indexOf(sortedNumbers[left]);
      int secondIndex = numbers.lastIndexOf(sortedNumbers[right]); // use lastIndexOf to handle duplicate values.
      if (firstIndex == secondIndex){
        secondIndex = numbers.indexOf(sortedNumbers[right], firstIndex+1);
      }

      return [firstIndex, secondIndex];
    } else if (sum < target) {
      left++;
    } else {
      right--;
    }
  }
  return null;
}

// Hashmap approach (works on unsorted list)
List<int>? twoSumUnsorted(List<int> numbers, int target) {
  Map<int, int> numMap = {};
  for (int i = 0; i < numbers.length; i++) {
    int complement = target - numbers[i];
    if (numMap.containsKey(complement)) {
      return [numMap[complement]!, i];
    }
    numMap[numbers[i]] = i;
  }
  return null;
}