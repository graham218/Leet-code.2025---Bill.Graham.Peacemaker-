// Dart program implementing the Plus One problem using 6 advanced real-world approaches
import 'dart:async';
import 'dart:math';

void main() async { // Make main async to handle plusOneStream
  List<int> digits = [9, 9, 9];

  print("Advanced Plus One computations for ${digits} using different approaches:");
  print("1. Standard Iterative Approach: ${plusOneIterative(List.from(digits))}");
  print("2. Recursive Divide and Conquer Approach: ${plusOneRecursive(List.from(digits), digits.length - 1)}");
  print("3. BigInt Mathematical Approach: ${plusOneBigInt(digits)}");
  print("4. Functional Programming with Mapping: ${plusOneFunctional(digits)}");
  print("5. Stream-Based Real-Time Processing: ${await plusOneStream(digits)}"); // Await the stream result
  print("6. Blockchain Transaction ID Generator (Real-World Application): ${plusOneBlockchain(digits)}");
}

// Approach 1: Standard Iterative Approach
// Adds one to a list of digits representing a non-negative integer.
// Iterates from the least significant digit to the most significant digit.
List<int> plusOneIterative(List<int> digits) {
  for (int i = digits.length - 1; i >= 0; i--) { // Iterate from right to left.
    if (digits[i] < 9) { // If the digit is less than 9, increment and return.
      digits[i] += 1;
      return digits;
    }
    digits[i] = 0; // If the digit is 9, set to 0 and continue.
  }
  return [1] + digits; // If all digits were 9, add a leading 1.
}

// Approach 2: Recursive Divide and Conquer Approach
// Adds one to a list of digits using recursion.
// Simulates a divide and conquer approach, although not truly dividing the problem.
List<int> plusOneRecursive(List<int> digits, int index) {
  if (index < 0) { // Base case: reached the beginning, add leading 1.
    digits.insert(0, 1);
    return digits;
  }
  if (digits[index] < 9) { // If digit is less than 9, increment and return.
    digits[index] += 1;
    return digits;
  }
  digits[index] = 0; // If digit is 9, set to 0 and recurse.
  return plusOneRecursive(digits, index - 1);
}

// Approach 3: BigInt Mathematical Approach
// Handles very large numbers by converting the list to a BigInt.
// Adds one to the BigInt and converts back to a list of digits.
List<int> plusOneBigInt(List<int> digits) {
  BigInt number = BigInt.parse(digits.join()); // Convert list to BigInt.
  number += BigInt.one; // Add one to BigInt.
  return number.toString().split('').map(int.parse).toList(); // Convert back to list of digits.
}

// Approach 4: Functional Programming with Mapping
// Performs the same operation as BigInt approach but uses a functional style.
// Concise but may be less readable for those unfamiliar with functional programming.
List<int> plusOneFunctional(List<int> digits) {
  return (BigInt.parse(digits.map((d) => d.toString()).join()) + BigInt.one) // Convert to BigInt, add one.
      .toString()
      .split('')
      .map(int.parse)
      .toList(); // Convert back to list of digits.
}

// Approach 5: Stream-Based Real-Time Processing
// Wraps the iterative approach in a Stream and Future for asynchronous execution.
// Useful for scenarios where the operation might be part of a larger asynchronous pipeline.
Future<List<int>> plusOneStream(List<int> digits) async {
  return await Stream<List<int>>.fromFuture( // Create Stream from Future.
      Future(() => plusOneIterative(digits)) // Create Future to execute iterative approach.
  ).first; // Get first (and only) element from Stream.
}

// Approach 6: Blockchain Transaction ID Generator (Real-World Application)
// Simulates a blockchain transaction ID generator by incrementing a number and converting it to a hexadecimal string.
// In a real-world scenario, this would be part of a more complex transaction processing system.
String plusOneBlockchain(List<int> digits) {
  BigInt transactionID = BigInt.parse(digits.join()) + BigInt.one; // Convert to BigInt and add one.
  String hash = transactionID.toRadixString(16); // Convert to hexadecimal.
  return "TX-" + hash.toUpperCase(); // Prepend "TX-" and return.
}