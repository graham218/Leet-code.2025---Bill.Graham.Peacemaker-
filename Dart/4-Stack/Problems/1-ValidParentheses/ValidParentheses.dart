void main() {
  List<String> testCases = [
    "()",
    "()[]{}",
    "(]",
    "([)]",
    "{[]}",
    "((()))",
    "[{()}]",
    "([{}])",
    "" // Test empty string
  ];

  for (String test in testCases) {
    print("Test string: '$test'");
    print("Stack Method: ${isValidUsingStack(test)}");
    print("Count Method: ${isValidUsingCount(test)}");
    print("Replace Method: ${isValidUsingReplace(test)}");
    print("Recursion Method: ${isValidUsingRecursion(test)}");
    print("ASCII Method: ${isValidUsingAscii(test)}");
    print("--------------------------------");
  }
}

// Approach 1: Using Stack (Most Common Approach)
bool isValidUsingStack(String s) {
  List<String> stack = [];
  Map<String, String> brackets = {')': '(', '}': '{', ']': '['};

  for (String char in s.split('')) {
    if (brackets.containsValue(char)) {
      stack.add(char); // Push opening bracket onto stack
    } else if (brackets.containsKey(char)) {
      if (stack.isEmpty || stack.removeLast() != brackets[char]) {
        return false; // Mismatch or unbalanced closing bracket
      }
    }
  }
  return stack.isEmpty; // Stack should be empty if all brackets are balanced
}

// Approach 2: Counting Method (Limited to single type of parentheses)
bool isValidUsingCount(String s) {
  int count = 0;
  for (String char in s.split('')) {
    if (char == '(') {
      count++;
    } else if (char == ')') {
      count--;
    }
    if (count < 0) return false; // More closing brackets than opening
  }
  return count == 0;
}

// Approach 3: Using Replace Method (Remove pairs iteratively)
bool isValidUsingReplace(String s) {
  int prevLength;
  do {
    prevLength = s.length;
    s = s.replaceAll('()', '').replaceAll('{}', '').replaceAll('[]', '');
  } while (s.length != prevLength);
  return s.isEmpty;
}

// Approach 4: Using Recursion
bool isValidUsingRecursion(String s) {
  if (s.isEmpty) return true;
  String reduced = s.replaceAll('()', '').replaceAll('{}', '').replaceAll('[]', '');
  return reduced == s ? false : isValidUsingRecursion(reduced);
}

// Approach 5: Using ASCII Values (Alternative Stack Method)
bool isValidUsingAscii(String s) {
  List<int> stack = [];
  for (int char in s.codeUnits) {
    if (char == 40 || char == 123 || char == 91) { // '(' or '{' or '['
      stack.add(char);
    } else {
      if (stack.isEmpty) return false;
      int last = stack.removeLast();
      if ((char == 41 && last != 40) || // ')'
          (char == 125 && last != 123) || // '}'
          (char == 93 && last != 91)) { // ']'
        return false;
      }
    }
  }
  return stack.isEmpty;
}