// Dart program for advanced validation of parentheses with real-world applications

import 'dart:collection';

/// This solution checks for valid parentheses in real-world applications such as:
/// - HTML/XML tag validation
/// - Code syntax validation
/// - Expression balancing in compilers
/// - Formula validation in mathematical expressions

class ParenthesesValidator {
  /// Validates a given string containing parentheses and ensures it follows correct nesting.
  /// Uses a stack-based approach optimized with a linked list for efficiency.
  bool isValid(String s) {
    final Queue<String> stack = Queue(); // Efficient stack using linked list
    final Map<String, String> brackets = {')': '(', '}': '{', ']': '['};

    for (String char in s.split('')) {
      if (brackets.containsValue(char)) {
        stack.addLast(char); // Push opening bracket onto stack
      } else if (brackets.containsKey(char)) {
        if (stack.isEmpty || stack.removeLast() != brackets[char]) {
          return false; // Mismatch or unbalanced closing bracket
        }
      }
    }
    return stack.isEmpty;
  }

  /// Validates an HTML-like string ensuring that all opening tags have a corresponding closing tag.
  /// Example: "<div><p>Hello</p></div>" is valid, but "<div><p></div>" is invalid.
  bool isValidHtml(String s) {
    final RegExp tagPattern = RegExp(r"<(/?\w+)>", caseSensitive: false);
    final Queue<String> stack = Queue();

    for (Match match in tagPattern.allMatches(s)) {
      String tag = match.group(1)!;
      if (!tag.startsWith('/')) {
        stack.addLast(tag); // Push opening tag onto stack
      } else {
        if (stack.isEmpty || stack.removeLast() != tag.substring(1)) {
          return false; // Mismatched or unclosed tag
        }
      }
    }
    return stack.isEmpty;
  }

  /// Validates mathematical expressions ensuring that parentheses, brackets, and braces are balanced.
  /// Example: "(5+3) * [2-{4/2}]" is valid, but "(5+3 * [2-{4/2}" is invalid.
  bool isValidMathExpression(String expression) {
    return isValid(expression.replaceAll(RegExp(r"[^(){}\[\]]"), ""));
  }
}

void main() {
  final validator = ParenthesesValidator();

  // Test cases for standard parentheses validation
  print("Valid Parentheses: ${validator.isValid("{[()]}")}"); // true
  print("Invalid Parentheses: ${validator.isValid("{[(])}")}"); // false

  // Test cases for HTML tag validation
  print("Valid HTML: ${validator.isValidHtml("<html><body><p>Hello</p></body></html>")}"); // true
  print("Invalid HTML: ${validator.isValidHtml("<div><p>Hello</div></p>")}"); // false

  // Test cases for mathematical expression validation
  print("Valid Math Expression: ${validator.isValidMathExpression("(3+5) * [2-{4/2}]")}"); // true
  print("Invalid Math Expression: ${validator.isValidMathExpression("(3+5 * [2-{4/2}")}"); // false
}