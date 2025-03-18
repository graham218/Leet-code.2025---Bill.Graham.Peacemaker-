void main() {
  List<int> numbers = [2, 7, 11, 15];
  int target = 9;

  List<int>? result = twoSum(numbers, target);
  if (result != null) {
    print("Indices: \${result[0]}, \${result[1]}");
  } else {
    print("No solution found");
  }
}

List<int>? twoSum(List<int> numbers, int target) {
  int left = 0, right = numbers.length - 1;
  while (left < right) {
    int sum = numbers[left] + numbers[right];
    if (sum == target) {
      return [left + 1, right + 1];
    } else if (sum < target) {
      left++;
    } else {
      right--;
    }
  }
  return null;
}
