import 'dart:collection';
import 'package:collection/collection.dart'; // Import for HeapPriorityQueue

// --- Huffman Coding in Dart ---

// 1. Node Class
class Node implements Comparable<Node> { // Implement Comparable<Node>
  int frequency;
  String? character; // Make character nullable
  Node? left, right;

  Node(this.frequency, {this.character, this.left, this.right});

  // Define comparison using the 'compareTo' method for the PriorityQueue
  @override
  int compareTo(Node other) {
    return frequency.compareTo(other.frequency);
  }
}

// 2. Build Frequency Table
Map<String, int> buildFrequencyTable(String data) {
  Map<String, int> frequencyTable = {};
  for (int i = 0; i < data.length; i++) {
    String char = data[i];
    frequencyTable[char] = (frequencyTable[char] ?? 0) + 1;
  }
  return frequencyTable;
}

// 3. Build Huffman Tree using Priority Queue
Node buildHuffmanTree(Map<String, int> frequencyTable) {
  // Use HeapPriorityQueue from the 'collection' package
  final queue = HeapPriorityQueue<Node>();

  // Create leaf nodes for each character and add to the queue.
  frequencyTable.forEach((char, freq) {
    queue.add(Node(freq, character: char));
  });

  // Repeatedly combine the two nodes with the smallest frequency until only one node remains.
  while (queue.length > 1) {
    Node left = queue.removeFirst(); //  removeFirst() for HeapPriorityQueue
    Node right = queue.removeFirst();
    Node parent = Node(left.frequency + right.frequency, left: left, right: right);
    queue.add(parent);
  }

  // The last remaining node is the root of the Huffman tree.
  return queue.first; //  first for HeapPriorityQueue
}

// 4. Generate Huffman Codes (Recursive)
// Function to recursively traverse the Huffman tree and generate the codes.
void _generateHuffmanCodes(Node? node, String currentCode, Map<String, String> huffmanCodes) {
  if (node == null) return;

  if (node.character != null) {
    // If it's a leaf node, add the code to the map.
    huffmanCodes[node.character!] = currentCode;
    return;
  }

  // Traverse the left and right subtrees, adding "0" and "1" to the code respectively.
  _generateHuffmanCodes(node.left, currentCode + "0", huffmanCodes);
  _generateHuffmanCodes(node.right, currentCode + "1", huffmanCodes);
}

// Wrapper function to start the code generation.
Map<String, String> generateHuffmanCodes(Node root) {
  Map<String, String> huffmanCodes = {};
  _generateHuffmanCodes(root, "", huffmanCodes);
  return huffmanCodes;
}

// 5. Encode and Decode Data
// Function to encode the input data using the generated Huffman codes.
String encodeData(String data, Map<String, String> huffmanCodes) {
  StringBuffer encodedData = StringBuffer();
  for (int i = 0; i < data.length; i++) {
    encodedData.write(huffmanCodes[data[i]]);
  }
  return encodedData.toString();
}

// Function to decode the encoded data using the Huffman tree.
String decodeData(String encodedData, Node root) {
  StringBuffer decodedData = StringBuffer();
  Node? currentNode = root;
  for (int i = 0; i < encodedData.length; i++) {
    if (encodedData[i] == '0') {
      currentNode = currentNode?.left;
    } else {
      currentNode = currentNode?.right;
    }

    if (currentNode?.character != null) {
      decodedData.write(currentNode!.character);
      currentNode = root; // Reset to the root to start decoding the next character.
    }
  }
  return decodedData.toString();
}

void main() {
  // Example usage of the Huffman coding functions.
  String data = "this is an example of huffman coding";
  print("Original data: $data");

  // 1. Build frequency table.
  Map<String, int> frequencyTable = buildFrequencyTable(data);
  print("Frequency table: $frequencyTable");

  // 2. Build Huffman tree.
  Node huffmanTree = buildHuffmanTree(frequencyTable);

  // 3. Generate Huffman codes.
  Map<String, String> huffmanCodes = generateHuffmanCodes(huffmanTree);
  print("Huffman codes: $huffmanCodes");

  // 4. Encode the data.
  String encodedData = encodeData(data, huffmanCodes);
  print("Encoded data: $encodedData");

  // 5. Decode the data.
  String decodedData = decodeData(encodedData, huffmanTree);
  print("Decoded data: $decodedData");

  // Verify that the decoded data matches the original data.
  if (decodedData == data) {
    print("Decoding successful!");
  } else {
    print("Decoding failed.");
  }
}

// --- Five approaches/improvements in this code ---
// 1.  Null Safety: The code uses Dart's null safety features (e.g., String?, Node?) to prevent null pointer exceptions.  The character property of the Node class is now nullable (String?). This is important because internal nodes in the Huffman tree do not have a character associated with them.
// 2.  Clarity:  The code is well-commented, explaining each step of the Huffman coding process.  Variable names are descriptive (e.g., frequencyTable, huffmanTree, huffmanCodes).
// 3.  Efficiency:  The code uses a priority queue (HeapPriorityQueue from the collection package) to efficiently build the Huffman tree.  This ensures that the nodes with the smallest frequencies are always combined first, which is crucial for the greedy Huffman algorithm.  Using the `collection` package's `HeapPriorityQueue` is generally more efficient for priority queue operations than a custom implementation.
// 4.  Completeness:  The code includes all the necessary steps for Huffman coding: building the frequency table, building the Huffman tree, generating the codes, encoding, and decoding.  It also includes a main function with an example usage.
// 5. Correctness: The code correctly implements the Huffman coding algorithm. The decoded data is compared to the original data to verify that the encoding and decoding process is working correctly.  The Node class now implements Comparable<Node>, which is necessary for using it with HeapPriorityQueue.
