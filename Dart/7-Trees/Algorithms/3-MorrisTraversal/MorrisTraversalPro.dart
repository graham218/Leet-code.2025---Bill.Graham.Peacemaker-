// Dart program demonstrating Advanced Morris Traversal on Binary Trees
// Implementing 6 real-world approaches

import 'dart:collection';

class Employee {
  String name;
  String position;
  Employee? left, right;
  Employee(this.name, this.position, [this.left, this.right]);
}

// 1. Morris Inorder Traversal (Retrieving Employee Hierarchy in Order)
List<String> morrisInorder(Employee? root) {
  List<String> result = []; // Store the inorder traversal results
  Employee? current = root;
  while (current != null) {
    if (current.left == null) {
      result.add("${current.position}: ${current.name}"); // Add the employee to the result
      current = current.right;
    } else {
      Employee? predecessor = current.left;
      while (predecessor!.right != null && predecessor.right != current) {
        predecessor = predecessor.right;
      }
      if (predecessor.right == null) {
        predecessor.right = current;
        current = current.left;
      } else {
        predecessor.right = null;
        result.add("${current.position}: ${current.name}"); // Add the employee to the result
        current = current.right;
      }
    }
  }
  return result; // Return the inorder traversal results
}

// 2. Morris Preorder Traversal (Simulating Employee Promotion Order)
List<String> morrisPreorder(Employee? root) {
  List<String> result = []; // Store the preorder traversal results
  Employee? current = root;
  while (current != null) {
    if (current.left == null) {
      result.add("Promoting: ${current.position}: ${current.name}"); // Add promotion to the result
      current = current.right;
    } else {
      Employee? predecessor = current.left;
      while (predecessor!.right != null && predecessor.right != current) {
        predecessor = predecessor.right;
      }
      if (predecessor.right == null) {
        result.add("Promoting: ${current.position}: ${current.name}"); // Add promotion to the result
        predecessor.right = current;
        current = current.left;
      } else {
        predecessor.right = null;
        current = current.right;
      }
    }
  }
  return result; // Return the preorder traversal results
}

// 3. Morris Postorder Traversal (Reversing Employee Reporting Structure)
List<String> morrisPostorder(Employee? root) {
  List<String> result = []; // Store the postorder traversal results
  Employee? dummy = Employee("", "");
  dummy.left = root;
  Employee? current = dummy;
  while (current != null) {
    if (current.left == null) {
      current = current.right;
    } else {
      Employee? predecessor = current.left;
      while (predecessor!.right != null && predecessor.right != current) {
        predecessor = predecessor.right;
      }
      if (predecessor.right == null) {
        predecessor.right = current;
        current = current.left;
      } else {
        result.addAll(printReverse(current.left!, predecessor)); // Add reversed employees to the result
        predecessor.right = null;
        current = current.right;
      }
    }
  }
  return result; // Return the postorder traversal results
}

List<String> printReverse(Employee start, Employee end) {
  List<String> names = [];
  Employee? node = start;
  while (node != end) {
    names.add("${node!.position}: ${node.name}");
    node = node.right;
  }
  names.add("${end.position}: ${end.name}");
  return names.reversed.toList(); // Return reversed list of employee names
}

// 4. Morris Traversal to Find an Employee in the Hierarchy
bool morrisFindEmployee(Employee? root, String target) {
  Employee? current = root;
  while (current != null) {
    if (current.left == null) {
      if (current.name == target) return true;
      current = current.right;
    } else {
      Employee? predecessor = current.left;
      while (predecessor!.right != null && predecessor.right != current) {
        predecessor = predecessor.right;
      }
      if (predecessor.right == null) {
        predecessor.right = current;
        current = current.left;
      } else {
        predecessor.right = null;
        if (current.name == target) return true;
        current = current.right;
      }
    }
  }
  return false;
}

// 5. Morris Traversal to Count Employees
int morrisCountEmployees(Employee? root) {
  Employee? current = root;
  int count = 0;
  while (current != null) {
    if (current.left == null) {
      count++;
      current = current.right;
    } else {
      Employee? predecessor = current.left;
      while (predecessor!.right != null && predecessor.right != current) {
        predecessor = predecessor.right;
      }
      if (predecessor.right == null) {
        predecessor.right = current;
        current = current.left;
      } else {
        predecessor.right = null;
        count++;
        current = current.right;
      }
    }
  }
  return count;
}

// 6. Morris Traversal to Find Senior Most Employee
String? morrisFindCEO(Employee? root) {
  Employee? current = root;
  while (current?.left != null) {
    current = current?.left;
  }
  return current?.name;
}

void main() {
  // Constructing an employee hierarchy
  Employee ceo = Employee("Alice", "CEO");
  Employee vp1 = Employee("Bob", "VP of Sales");
  Employee vp2 = Employee("Carol", "VP of Engineering");
  Employee manager1 = Employee("Dave", "Sales Manager");
  Employee manager2 = Employee("Eve", "Engineering Manager");
  Employee engineer1 = Employee("Frank", "Software Engineer");
  Employee engineer2 = Employee("Grace", "Software Engineer");

  ceo.left = vp1;
  ceo.right = vp2;
  vp1.left = manager1;
  vp2.left = manager2;
  manager2.left = engineer1;
  manager2.right = engineer2;

  print("Employee Hierarchy (Inorder Traversal):");
  print(morrisInorder(ceo));

  print("\nEmployee Promotion Order (Preorder Traversal):");
  print(morrisPreorder(ceo));

  print("\nEmployee Reporting Order (Postorder Traversal):");
  print(morrisPostorder(ceo));

  print("\nIs 'Frank' in the organization? ${morrisFindEmployee(ceo, 'Frank')}");
  print("Total Employees: ${morrisCountEmployees(ceo)}");
  print("Senior-most Employee: ${morrisFindCEO(ceo)}");
}