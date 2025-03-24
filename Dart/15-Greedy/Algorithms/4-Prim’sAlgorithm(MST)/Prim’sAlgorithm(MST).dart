// Prim's Algorithm in Dart - Multiple Approaches
import 'dart:collection';
import 'package:collection/collection.dart';

void main() {
  List<List<int>> graphMatrix = [
    [0, 2, 0, 6, 0],
    [2, 0, 3, 8, 5],
    [0, 3, 0, 0, 7],
    [6, 8, 0, 0, 9],
    [0, 5, 7, 9, 0]
  ];

  print("Using Adjacency Matrix with Priority Queue:");
  primMatrixPQ(graphMatrix, 5);

  List<List<List<int>>> graphList = [
    [[1, 2], [3, 6]],
    [[0, 2], [2, 3], [3, 8], [4, 5]],
    [[1, 3], [4, 7]],
    [[0, 6], [1, 8], [4, 9]],
    [[1, 5], [2, 7], [3, 9]]
  ];

  print("\nUsing Adjacency List with Priority Queue:");
  primListPQ(graphList, 5);

  print("\nUsing Adjacency List with Simple Array:");
  primListSimple(graphList, 5);

  print("\nUsing Adjacency Matrix with Simple Selection:");
  primMatrixSimple(graphMatrix, 5);
}

// 1. Using Adjacency Matrix with Priority Queue
void primMatrixPQ(List<List<int>> graph, int vertices) {
  List<bool> inMST = List.filled(vertices, false);
  List<int> key = List.filled(vertices, double.maxFinite.toInt());
  List<int> parent = List.filled(vertices, -1);

  var pq = HeapPriorityQueue<List<int>>((a, b) => a[0] - b[0]);
  pq.add([0, 0]);
  key[0] = 0;

  while (pq.isNotEmpty) {
    int u = pq.removeFirst()[1];
    inMST[u] = true;

    for (int v = 0; v < vertices; v++) {
      if (graph[u][v] != 0 && !inMST[v] && graph[u][v] < key[v]) {
        key[v] = graph[u][v];
        parent[v] = u;
        pq.add([key[v], v]);
      }
    }
  }
  print("Parent Array: $parent");
}

// 2. Using Adjacency List with Priority Queue (Heap)
void primListPQ(List<List<List<int>>> graph, int vertices) {
  List<bool> inMST = List.filled(vertices, false);
  List<int> key = List.filled(vertices, double.maxFinite.toInt());
  List<int> parent = List.filled(vertices, -1);

  var pq = HeapPriorityQueue<List<int>>((a, b) => a[0] - b[0]);
  pq.add([0, 0]);
  key[0] = 0;

  while (pq.isNotEmpty) {
    int u = pq.removeFirst()[1];
    inMST[u] = true;

    for (var edge in graph[u]) {
      int v = edge[0], weight = edge[1];
      if (!inMST[v] && weight < key[v]) {
        key[v] = weight;
        parent[v] = u;
        pq.add([key[v], v]);
      }
    }
  }
  print("Parent Array: $parent");
}

// 3. Using Adjacency List with Simple Array
void primListSimple(List<List<List<int>>> graph, int vertices) {
  List<bool> inMST = List.filled(vertices, false);
  List<int> key = List.filled(vertices, double.maxFinite.toInt());
  List<int> parent = List.filled(vertices, -1);
  key[0] = 0;

  for (int i = 0; i < vertices - 1; i++) {
    int u = -1;
    for (int j = 0; j < vertices; j++) {
      if (!inMST[j] && (u == -1 || key[j] < key[u])) {
        u = j;
      }
    }
    inMST[u] = true;

    for (var edge in graph[u]) {
      int v = edge[0], weight = edge[1];
      if (!inMST[v] && weight < key[v]) {
        key[v] = weight;
        parent[v] = u;
      }
    }
  }
  print("Parent Array: $parent");
}

// 4. Using Adjacency Matrix with Simple Selection
void primMatrixSimple(List<List<int>> graph, int vertices) {
  List<bool> inMST = List.filled(vertices, false);
  List<int> key = List.filled(vertices, double.maxFinite.toInt());
  List<int> parent = List.filled(vertices, -1);
  key[0] = 0;

  for (int i = 0; i < vertices - 1; i++) {
    int u = -1;
    for (int j = 0; j < vertices; j++) {
      if (!inMST[j] && (u == -1 || key[j] < key[u])) {
        u = j;
      }
    }
    inMST[u] = true;

    for (int v = 0; v < vertices; v++) {
      if (graph[u][v] != 0 && !inMST[v] && graph[u][v] < key[v]) {
        key[v] = graph[u][v];
        parent[v] = u;
      }
    }
  }
  print("Parent Array: $parent");
}
