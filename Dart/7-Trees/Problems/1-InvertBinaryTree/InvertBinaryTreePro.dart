// Dart program demonstrating real-world implementations of inverting tree structures

import 'dart:collection';

// Class representing a directory or file in a file system
class FileSystemNode {
  String name;
  List<FileSystemNode> children;
  FileSystemNode(this.name, [this.children = const []]);
}

// 1. Inverting a File System Structure
FileSystemNode? invertFileSystem(FileSystemNode? root) {
  if (root == null) return null;
  root.children = root.children.reversed.toList();
  for (var child in root.children) {
    invertFileSystem(child);
  }
  return root;
}

// 2. Reversing an Organizational Hierarchy
class Employee {
  String name;
  List<Employee> subordinates;
  Employee(this.name, [this.subordinates = const []]);
}

Employee? invertHierarchy(Employee? root) {
  if (root == null) return null;
  root.subordinates = root.subordinates.reversed.toList();
  for (var subordinate in root.subordinates) {
    invertHierarchy(subordinate);
  }
  return root;
}

// 3. Mirroring a Decision Tree in AI Applications
class DecisionNode {
  String decision;
  DecisionNode? yesBranch, noBranch;
  DecisionNode(this.decision, [this.yesBranch, this.noBranch]);
}

DecisionNode? invertDecisionTree(DecisionNode? root) {
  if (root == null) return null;
  DecisionNode? temp = root.yesBranch;
  root.yesBranch = invertDecisionTree(root.noBranch);
  root.noBranch = invertDecisionTree(temp);
  return root;
}

// 4. Reversing a Web Sitemap Structure
class WebPage {
  String url;
  List<WebPage> links;
  WebPage(this.url, [this.links = const []]);
}

WebPage? invertSitemap(WebPage? root) {
  if (root == null) return null;
  root.links = root.links.reversed.toList();
  for (var link in root.links) {
    invertSitemap(link);
  }
  return root;
}

// 5. Reversing a Network Routing Path
class NetworkNode {
  String ip;
  List<NetworkNode> connections;
  NetworkNode(this.ip, [this.connections = const []]);
}

NetworkNode? invertNetwork(NetworkNode? root) {
  if (root == null) return null;
  root.connections = root.connections.reversed.toList();
  for (var node in root.connections) {
    invertNetwork(node);
  }
  return root;
}

// 6. Flipping a Graphical UI Tree (e.g., for dark mode conversion)
class UIElement {
  String name;
  List<UIElement> children;
  UIElement(this.name, [this.children = const []]);
}

UIElement? invertUITree(UIElement? root) {
  if (root == null) return null;
  root.children = root.children.reversed.toList();
  for (var child in root.children) {
    invertUITree(child);
  }
  return root;
}

void main() {
  // File System Example
  FileSystemNode fileRoot = FileSystemNode("Root", [
    FileSystemNode("Folder1", [
      FileSystemNode("File1.1"),
      FileSystemNode("File1.2"),
      FileSystemNode("SubFolder1.1", [FileSystemNode("File1.1.1"), FileSystemNode("File1.1.2")]),
    ]),
    FileSystemNode("Folder2", [FileSystemNode("File2.1"), FileSystemNode("File2.2")]),
    FileSystemNode("Folder3")
  ]);
  print("\nOriginal File System Structure: ${fileRoot.children.map((e) => e.name).toList()}");
  invertFileSystem(fileRoot);
  print("Inverted File System Structure: ${fileRoot.children.map((e) => e.name).toList()}");

  // Organizational Hierarchy Example
  Employee ceo = Employee("CEO", [
    Employee("Manager1", [
      Employee("Employee1"),
      Employee("Employee2"),
      Employee("TeamLead1", [Employee("Developer1"), Employee("Developer2")]),
    ]),
    Employee("Manager2", [Employee("Employee3"), Employee("Employee4")]),
    Employee("Manager3")
  ]);
  print("\nOriginal CEO Subordinates: ${ceo.subordinates.map((e) => e.name).toList()}");
  invertHierarchy(ceo);
  print("Inverted CEO Subordinates: ${ceo.subordinates.map((e) => e.name).toList()}");

  // Decision Tree Example
  DecisionNode decisionRoot = DecisionNode("Start",
      DecisionNode("Go Left", DecisionNode("Left-Yes"), DecisionNode("Left-No")),
      DecisionNode("Go Right", DecisionNode("Right-Yes"), DecisionNode("Right-No")));
  print("\nOriginal Decision: ${decisionRoot.decision}");
  invertDecisionTree(decisionRoot);
  print("Inverted Decision: ${decisionRoot.decision}");

  // Web Sitemap Example
  WebPage home = WebPage("Home", [
    WebPage("About", [WebPage("Team"), WebPage("History")]),
    WebPage("Contact", [WebPage("Support"), WebPage("Feedback")]),
    WebPage("Products")
  ]);
  print("\nOriginal Sitemap: ${home.links.map((e) => e.url).toList()}");
  invertSitemap(home);
  print("Inverted Sitemap: ${home.links.map((e) => e.url).toList()}");

  // Network Routing Example
  NetworkNode router = NetworkNode("192.168.1.1", [
    NetworkNode("192.168.1.2", [NetworkNode("10.0.0.1"), NetworkNode("10.0.0.2")]),
    NetworkNode("192.168.1.3"),
    NetworkNode("192.168.1.4")
  ]);
  print("\nOriginal Network Connections: ${router.connections.map((e) => e.ip).toList()}");
  invertNetwork(router);
  print("Inverted Network Connections: ${router.connections.map((e) => e.ip).toList()}");

  // UI Tree Example
  UIElement uiRoot = UIElement("Window", [
    UIElement("Header", [UIElement("Title"), UIElement("Menu")]),
    UIElement("Body", [UIElement("Content"), UIElement("Sidebar")]),
    UIElement("Footer")
  ]);
  print("\nOriginal UI Layout: ${uiRoot.children.map((e) => e.name).toList()}");
  invertUITree(uiRoot);
  print("Inverted UI Layout: ${uiRoot.children.map((e) => e.name).toList()}");
}