// Dart program demonstrating real-world Breadth-First Search (BFS) on Trees
// Implementing 6 different BFS approaches using an organizational hierarchy example

import 'dart:collection';

// Employee Node structure representing an organizational hierarchy
class Employee {
  String name; // Name of the employee
  String position; // Position of the employee in the hierarchy
  List<Employee> subordinates; // List of subordinates

  // Constructor to create an Employee node
  Employee(this.name, this.position) : subordinates = [];
}

// 1. Standard BFS Traversal (Prints hierarchy)
void bfsTraversal(Employee ceo) {
  // Initialize a queue for BFS
  Queue<Employee> queue = Queue();
  // Add the CEO (root) to the queue
  queue.add(ceo);

  // Continue while the queue is not empty
  while (queue.isNotEmpty) {
    // Dequeue the first employee
    Employee emp = queue.removeFirst();
    // Print the employee's position and name
    print("${emp.position}: ${emp.name}");
    // Enqueue all subordinates of the current employee
    for (var subordinate in emp.subordinates) {
      queue.add(subordinate);
    }
  }
  // This function prints the organization hierarchy level by level.
}

// 2. BFS with Level Order Traversal (Returning levels in hierarchy)
List<List<String>> bfsLevelOrder(Employee ceo) {
  // Initialize a list to store the level-wise employee names
  List<List<String>> result = [];
  // Initialize a queue for BFS
  Queue<Employee> queue = Queue();
  // Add the CEO to the queue
  queue.add(ceo);

  // Continue while the queue is not empty
  while (queue.isNotEmpty) {
    // Get the number of employees at the current level
    int size = queue.length;
    // Initialize a list to store names at the current level
    List<String> levelNames = [];
    // Process all employees at the current level
    for (int i = 0; i < size; i++) {
      // Dequeue the first employee
      Employee emp = queue.removeFirst();
      // Add the employee's position and name to the levelNames list
      levelNames.add("${emp.position}: ${emp.name}");
      // Enqueue all subordinates of the current employee
      for (var subordinate in emp.subordinates) {
        queue.add(subordinate);
      }
    }
    // Add the levelNames list to the result list
    result.add(levelNames);
  }
  // Returns a list of lists, where each inner list represents a level in the hierarchy.
  return result;
}

// 3. BFS to Find the Maximum Depth (Levels of hierarchy)
int bfsMaxDepth(Employee ceo) {
  // If the CEO is null, the depth is 0
  if (ceo == null) return 0;
  // Initialize a queue for BFS
  Queue<Employee> queue = Queue();
  // Add the CEO to the queue
  queue.add(ceo);
  // Initialize the depth counter
  int depth = 0;

  // Continue while the queue is not empty
  while (queue.isNotEmpty) {
    // Get the number of employees at the current level
    int size = queue.length;
    // Process all employees at the current level
    for (int i = 0; i < size; i++) {
      // Dequeue the first employee
      Employee emp = queue.removeFirst();
      // Enqueue all subordinates of the current employee
      for (var subordinate in emp.subordinates) {
        queue.add(subordinate);
      }
    }
    // Increment the depth counter after processing each level
    depth++;
  }
  // Returns the maximum depth of the hierarchy.
  return depth;
}

// 4. BFS to Find the Total Number of Employees
int bfsTotalEmployees(Employee ceo) {
  // Initialize a queue for BFS
  Queue<Employee> queue = Queue();
  // Add the CEO to the queue
  queue.add(ceo);
  // Initialize the employee counter
  int count = 0;

  // Continue while the queue is not empty
  while (queue.isNotEmpty) {
    // Dequeue the first employee
    Employee emp = queue.removeFirst();
    // Increment the employee counter
    count++;
    // Enqueue all subordinates of the current employee
    for (var subordinate in emp.subordinates) {
      queue.add(subordinate);
    }
  }
  // Returns the total number of employees in the hierarchy.
  return count;
}

// 5. BFS to Find an Employee by Name
bool bfsFindEmployee(Employee ceo, String targetName) {
  // Initialize a queue for BFS
  Queue<Employee> queue = Queue();
  // Add the CEO to the queue
  queue.add(ceo);

  // Continue while the queue is not empty
  while (queue.isNotEmpty) {
    // Dequeue the first employee
    Employee emp = queue.removeFirst();
    // Check if the employee's name matches the target name
    if (emp.name == targetName) return true; // Return true if found
    // Enqueue all subordinates of the current employee
    for (var subordinate in emp.subordinates) {
      queue.add(subordinate);
    }
  }
  // Return false if the employee is not found.
  return false;
}

// 6. BFS to Check If Hierarchy is Balanced (Each manager has similar number of subordinates)
bool isHierarchyBalanced(Employee ceo) {
  // Initialize a queue for BFS
  Queue<Employee> queue = Queue();
  // Add the CEO to the queue
  queue.add(ceo);

  // Continue while the queue is not empty
  while (queue.isNotEmpty) {
    // Dequeue the first employee
    Employee emp = queue.removeFirst();
    // Check if the employee has subordinates
    if (emp.subordinates.isNotEmpty) {
      // Calculate the minimum and maximum number of subordinates among the current employee's subordinates
      int minSub = emp.subordinates.map((e) => e.subordinates.length).reduce((a, b) => a < b ? a : b);
      int maxSub = emp.subordinates.map((e) => e.subordinates.length).reduce((a, b) => a > b ? a : b);
      // If the difference between the maximum and minimum number of subordinates is greater than 1, the hierarchy is not balanced
      if ((maxSub - minSub) > 1) return false;
    }
    // Enqueue all subordinates of the current employee
    for (var subordinate in emp.subordinates) {
      queue.add(subordinate);
    }
  }
  // Returns true if the hierarchy is balanced, false otherwise.
  return true;
}

void main() {
  // Constructing an organizational hierarchy
  Employee ceo = Employee("Alice", "CEO");
  Employee vp1 = Employee("Bob", "VP of Sales");
  Employee vp2 = Employee("Carol", "VP of Engineering");
  Employee manager1 = Employee("Dave", "Sales Manager");
  Employee manager2 = Employee("Eve", "Engineering Manager");
  Employee engineer1 = Employee("Frank", "Software Engineer");
  Employee engineer2 = Employee("Grace", "Software Engineer");

  ceo.subordinates.add(vp1);
  ceo.subordinates.add(vp2);
  vp1.subordinates.add(manager1);
  vp2.subordinates.add(manager2);
  manager2.subordinates.add(engineer1);
  manager2.subordinates.add(engineer2);

  print("Organizational Hierarchy (BFS Traversal):");
  bfsTraversal(ceo);

  print("\nLevel Order Hierarchy:");
  print(bfsLevelOrder(ceo));

  print("\nMaximum Hierarchy Depth: ${bfsMaxDepth(ceo)}");
  print("Total Employees: ${bfsTotalEmployees(ceo)}");
  print("Is Employee 'Frank' Present? ${bfsFindEmployee(ceo, 'Frank')}");
  print("Is Employee 'Tom' Present? ${bfsFindEmployee(ceo, 'Tom')}");
  print("Is Hierarchy Balanced? ${isHierarchyBalanced(ceo)}");
}