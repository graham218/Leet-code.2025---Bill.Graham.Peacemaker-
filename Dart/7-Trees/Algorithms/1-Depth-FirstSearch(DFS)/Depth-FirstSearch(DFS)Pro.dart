// Dart program demonstrating Depth-First Search (DFS)
// Real-world use case: File System Navigation
// Implementing 6 different DFS approaches

import 'dart:collection';

// File/Folder Node structure
class FileSystemNode {
  String name; // Name of the file or directory
  bool isFile; // Flag indicating if it's a file (true) or directory (false)
  List<FileSystemNode> children; // List of child nodes (files or directories)

  // Constructor to create a FileSystemNode
  FileSystemNode(this.name, {this.isFile = false}) : children = [];
}

// 1. Recursive DFS to List All Files and Directories
void listFilesRecursive(FileSystemNode node) {
  // Check if the current node is a file
  if (node.isFile) {
    print("File: ${node.name}"); // Print file name
  } else {
    print("Directory: ${node.name}"); // Print directory name
    // Recursively call listFilesRecursive for each child node
    for (var child in node.children) {
      listFilesRecursive(child);
    }
  }
}

// 2. Iterative DFS using List as Stack to List Files and Directories
void listFilesIterative(FileSystemNode root) {
  // Initialize a stack with the root node
  List<FileSystemNode> stack = [];
  stack.add(root);

  // Continue until the stack is empty
  while (stack.isNotEmpty) {
    // Pop the last node from the stack
    FileSystemNode node = stack.removeLast();
    // Check if the node is a file
    if (node.isFile) {
      print("File: ${node.name}"); // Print file name
    } else {
      print("Directory: ${node.name}"); // Print directory name
      // Add children to the stack in reverse order to maintain DFS order
      for (var child in node.children.reversed) {
        stack.add(child);
      }
    }
  }
}

// 3. DFS with Path Tracking
void dfsWithPath(FileSystemNode node, String path) {
  // Construct the current path by appending the node name to the existing path
  String currentPath = "$path/${node.name}";
  // Print the current path
  print(currentPath);
  // Recursively call dfsWithPath for each child node with the updated path
  for (var child in node.children) {
    dfsWithPath(child, currentPath);
  }
}

// 4. DFS for File Search
bool searchFile(FileSystemNode node, String fileName) {
  // Check if the current node matches the search criteria (name and isFile)
  if (node.name == fileName && node.isFile) return true;
  // Recursively call searchFile for each child node
  for (var child in node.children) {
    if (searchFile(child, fileName)) return true; // Return true if found in any child
  }
  // Return false if the file is not found in the current node or any of its children
  return false;
}

// 5. DFS to Count Total Files
int countFilesDFS(FileSystemNode node) {
  // Initialize count based on whether the current node is a file
  int count = node.isFile ? 1 : 0;
  // Recursively call countFilesDFS for each child node and add the count to the total
  for (var child in node.children) {
    count += countFilesDFS(child);
  }
  // Return the total count of files
  return count;
}

// 6. DFS to Find Largest File Name (Lexicographically)
String findLargestFile(FileSystemNode node) {
  // Initialize largest with the current node's name if it's a file, otherwise empty string
  String largest = node.isFile ? node.name : "";
  // Recursively call findLargestFile for each child node
  for (var child in node.children) {
    String childLargest = findLargestFile(child);
    // Compare the child's largest name with the current largest name
    if (childLargest.compareTo(largest) > 0) {
      // Update largest if the child's largest name is lexicographically greater
      largest = childLargest;
    }
  }
  // Return the largest file name found
  return largest;
}

void main() {
  // Constructing a sample file system
  FileSystemNode root = FileSystemNode("root");
  root.children.add(FileSystemNode("Documents"));
  root.children.add(FileSystemNode("Pictures"));
  root.children[0].children.add(FileSystemNode("resume.pdf", isFile: true));
  root.children[0].children.add(FileSystemNode("notes.txt", isFile: true));
  root.children[1].children.add(FileSystemNode("photo1.jpg", isFile: true));
  root.children[1].children.add(FileSystemNode("photo2.png", isFile: true));

  print("Recursive DFS Listing:");
  listFilesRecursive(root);

  print("\nIterative DFS Listing:");
  listFilesIterative(root);

  print("\nDFS with Path Tracking:");
  dfsWithPath(root, "");

  print("\nSearching for 'photo1.jpg': ${searchFile(root, "photo1.jpg")}");
  print("Searching for 'video.mp4': ${searchFile(root, "video.mp4")}");

  print("\nTotal Files Count: ${countFilesDFS(root)}");

  print("\nLargest File Name: ${findLargestFile(root)}");
}