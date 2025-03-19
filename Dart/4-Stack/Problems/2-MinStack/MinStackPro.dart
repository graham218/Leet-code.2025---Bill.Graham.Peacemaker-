// Dart program for an advanced Min Stack implementation with real-world applications

import 'dart:collection';

/// Real-World Applications of Min Stack:
/// - **Stock Market Analysis:** Keeping track of the minimum stock price in a rolling time window.
/// - **Memory Management:** Keeping track of the minimum available memory at different stages.
/// - **Undo/Redo Mechanism:** Tracking the smallest operation cost in a sequence.
/// - **AI/ML Algorithms:** Keeping track of minimum losses in optimization problems.
/// - **Banking Systems:** Maintaining the lowest balance in a transaction history.

/// Approach 1: Using Two Stacks with Optimized Space
/// Instead of storing duplicate values in the min stack, we store only when necessary.
class MinStack1 {
  final List<int> stack = [];
  final List<int> minStack = [];

  void push(int val) {
    stack.add(val);
    if (minStack.isEmpty || val <= minStack.last) {
      minStack.add(val);
    }
  }

  void pop() {
    if (stack.isNotEmpty) {
      if (stack.removeLast() == minStack.last) {
        minStack.removeLast();
      }
    }
  }

  int top() => stack.last;

  int getMin() => minStack.last;
}

/// Approach 2: Using a Single Stack with Struct-Like Objects
/// Each stack element stores both its value and the minimum up to that point.
class StackNode {
  int value;
  int min;
  StackNode(this.value, this.min);
}

class MinStack2 {
  final List<StackNode> stack = [];

  void push(int val) {
    int minVal = stack.isEmpty ? val : (val < stack.last.min ? val : stack.last.min);
    stack.add(StackNode(val, minVal));
  }

  void pop() => stack.removeLast();

  int top() => stack.last.value;

  int getMin() => stack.last.min;
}

/// Approach 3: Using a Doubly Linked List for Efficient Min Operations
class Node {
  int value;
  int min;
  Node? prev;
  Node(this.value, this.min, this.prev);
}

class MinStack3 {
  Node? head;

  void push(int val) {
    head = Node(val, head == null ? val : (val < head!.min ? val : head!.min), head);
  }

  void pop() {
    if (head != null) head = head!.prev;
  }

  int top() => head!.value;

  int getMin() => head!.min;
}

/// Approach 4: Using Self-Balancing Tree for Dynamic Min Retrieval
/// Used in financial analysis to maintain a sorted list of stock prices.
class MinStack4 {
  final ListQueue<int> stack = ListQueue();
  final List<int> sortedList = [];

  void push(int val) {
    stack.addLast(val);
    sortedList.add(val);
    sortedList.sort(); // Keeps min at index 0
  }

  void pop() {
    if (stack.isNotEmpty) {
      sortedList.remove(stack.removeLast());
    }
  }

  int top() => stack.last;

  int getMin() => sortedList.first;
}

/// Approach 5: Using Indexed Min Cache
/// Used in AI/ML algorithms for tracking minimum losses in optimization problems.
class MinStack5 {
  final List<int> stack = [];
  final Map<int, int> minCache = {};

  void push(int val) {
    int minVal = stack.isEmpty ? val : (val < minCache[stack.length - 1]! ? val : minCache[stack.length - 1]!);
    stack.add(val);
    minCache[stack.length - 1] = minVal;
  }

  void pop() {
    if (stack.isNotEmpty) {
      minCache.remove(stack.length - 1);
      stack.removeLast();
    }
  }

  int top() => stack.last;

  int getMin() => minCache[stack.length - 1]!;
}

void main() {
  var minStack = MinStack1();
  minStack.push(3);
  minStack.push(1);
  minStack.push(4);
  print("Min: ${minStack.getMin()}"); // 1
  minStack.pop();
  print("Top: ${minStack.top()}"); // 1
  print("Min: ${minStack.getMin()}"); // 1
}
