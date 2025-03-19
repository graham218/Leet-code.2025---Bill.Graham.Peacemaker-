// Dart program to implement a Min Stack using five different approaches

import 'dart:collection';

/// Approach 1: Using Two Stacks (One for elements, one for min values)
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

/// Approach 2: Using a Single Stack with Tuples (Pair of values: (val, min))
class MinStack2 {
  final List<MapEntry<int, int>> stack = [];

  void push(int val) {
    int minVal = stack.isEmpty ? val : stack.last.value < val ? stack.last.value : val;
    stack.add(MapEntry(val, minVal));
  }

  void pop() => stack.removeLast();

  int top() => stack.last.key;

  int getMin() => stack.last.value;
}

/// Approach 3: Using Linked List for O(1) Min Retrieval
class Node {
  int value;
  int min;
  Node? next;
  Node(this.value, this.min, this.next);
}

class MinStack3 {
  Node? head;

  void push(int val) {
    head = Node(val, head == null ? val : (val < head!.min ? val : head!.min), head);
  }

  void pop() {
    if (head != null) head = head!.next;
  }

  int top() => head!.value;

  int getMin() => head!.min;
}

/// Approach 4: Using Stack with Lazy Min Calculation (On Demand Min Search)
class MinStack4 {
  final List<int> stack = [];

  void push(int val) => stack.add(val);

  void pop() => stack.removeLast();

  int top() => stack.last;

  int getMin() => stack.reduce((a, b) => a < b ? a : b);
}

/// Approach 5: Using Priority Queue for Min Retrieval
class MinStack5 {
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

void main() {
  var minStack = MinStack1();
  minStack.push(5);
  minStack.push(2);
  minStack.push(7);
  print("Min: ${minStack.getMin()}"); // 2
  minStack.pop();
  print("Top: ${minStack.top()}"); // 2
  print("Min: ${minStack.getMin()}"); // 2
}