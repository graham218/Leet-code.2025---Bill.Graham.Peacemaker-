import 'dart:collection';
import 'package:collection/collection.dart'; // Import the collection package

// --- 1. Huffman Coding Using a Priority Queue (Min Heap) ---
class HuffmanNode {
  int frequency;
  String? character;
  HuffmanNode? left, right;

  HuffmanNode(this.frequency, {this.character, this.left, this.right});

  // Define comparison for the PriorityQueue
  int compareTo(HuffmanNode other) {
    return frequency.compareTo(other.frequency);
  }
}

Map<String, String> buildHuffmanCodes(HuffmanNode? node, String code, Map<String, String> codes) {
  if (node == null) return codes;

  if (node.character != null) {
    codes[node.character!] = code;
    return codes;
  }

  buildHuffmanCodes(node.left, code + '0', codes);
  buildHuffmanCodes(node.right, code + '1', codes);
  return codes;
}

String huffmanEncode(String text) {
  if (text.isEmpty) return "";

  // 1. Calculate frequency of each character
  Map<String, int> frequencyMap = {};
  for (int i = 0; i < text.length; i++) {
    String char = text[i];
    frequencyMap[char] = (frequencyMap[char] ?? 0) + 1;
  }

  // 2. Create a priority queue (min heap)
  PriorityQueue<HuffmanNode> pq = PriorityQueue<HuffmanNode>((a, b) => a.compareTo(b));
  frequencyMap.forEach((char, freq) {
    pq.add(HuffmanNode(freq, character: char));
  });

  // 3. Build the Huffman tree
  while (pq.length > 1) {
    HuffmanNode left = pq.removeFirst();
    HuffmanNode right = pq.removeFirst();
    HuffmanNode parent = HuffmanNode(left.frequency + right.frequency, left: left, right: right);
    pq.add(parent);
  }

  // 4. Get the Huffman codes
  HuffmanNode? root = pq.first;
  Map<String, String> huffmanCodes = {};
  if(root != null) {
    huffmanCodes = buildHuffmanCodes(root, '', huffmanCodes);
  }


  // 5. Encode the text
  String encodedText = '';
  for (int i = 0; i < text.length; i++) {
    encodedText += huffmanCodes[text[i]] ?? ''; //handle null huffmanCodes[text[i]]
  }
  return encodedText;
}

String huffmanDecode(String encodedText, Map<String, String> huffmanCodes) {
  if (encodedText.isEmpty) return "";

  // Reverse the huffman codes for easier decoding
  Map<String, String> reversedHuffmanCodes = {};
  huffmanCodes.forEach((char, code) {
    reversedHuffmanCodes[code] = char;
  });

  String decodedText = '';
  String currentCode = '';
  for (int i = 0; i < encodedText.length; i++) {
    currentCode += encodedText[i];
    if (reversedHuffmanCodes.containsKey(currentCode)) {
      decodedText += reversedHuffmanCodes[currentCode]!;
      currentCode = '';
    }
  }
  return decodedText;
}

void main() {
  // Example usage of Huffman Coding
  String text = "hello world";
  String encodedText = huffmanEncode(text);
  Map<String, String> huffmanCodes = {};
  //build huffman codes.
  if (text.isNotEmpty) {
    Map<String, int> frequencyMap = {};
    for (int i = 0; i < text.length; i++) {
      String char = text[i];
      frequencyMap[char] = (frequencyMap[char] ?? 0) + 1;
    }
    PriorityQueue<HuffmanNode> pq = PriorityQueue<HuffmanNode>((a, b) => a.compareTo(b));
    frequencyMap.forEach((char, freq) {
      pq.add(HuffmanNode(freq, character: char));
    });
    while (pq.length > 1) {
      HuffmanNode left = pq.removeFirst();
      HuffmanNode right = pq.removeFirst();
      HuffmanNode parent = HuffmanNode(left.frequency + right.frequency, left: left, right: right);
      pq.add(parent);
    }
    HuffmanNode? root = pq.first;
    if(root != null){
      huffmanCodes = buildHuffmanCodes(root, '', huffmanCodes);
    }

  }

  print("Original text: $text");
  print("Encoded text: $encodedText");
  print("Huffman Codes: $huffmanCodes");
  String decodedText = huffmanDecode(encodedText, huffmanCodes);
  print("Decoded text: $decodedText");
  print("--------------------------------------------------------");

  // --- 2. Huffman Coding Using a Sorted List ---
  String text2 = "banana";
  var result2 = huffmanCodingSortedList(text2);
  print("Huffman Coding with Sorted List:");
  print("Original text: $text2");
  print("Encoded text: ${result2['encodedText']}");
  print("Huffman Codes: ${result2['codes']}");
  print("Decoded text: ${huffmanDecode(result2['encodedText'], result2['codes'])}");
  print("--------------------------------------------------------");

  // --- 3. Huffman Coding Using Recursive Approach ---
  String text3 = "mississippi";
  var result3 = huffmanCodingRecursive(text3);
  print("Huffman Coding with Recursion:");
  print("Original text: $text3");
  print("Encoded text: ${result3['encodedText']}");
  print("Huffman Codes: ${result3['codes']}");
  print("Decoded text: ${huffmanDecode(result3['encodedText'], result3['codes'])}");
  print("--------------------------------------------------------");

  // --- 4. Huffman Coding with Optimized Frequency Counting ---
  String text4 = "aabbccddeeff";
  var result4 = huffmanCodingOptimized(text4);
  print("Huffman Coding with Optimized Frequency Counting:");
  print("Original text: $text4");
  print("Encoded text: ${result4['encodedText']}");
  print("Huffman Codes: ${result4['codes']}");
  print("Decoded text: ${huffmanDecode(result4['encodedText'], result4['codes'])}");
  print("--------------------------------------------------------");

  // --- 5. Huffman Coding with Prebuilt Frequency Table ---
  String text5 = "foobar";
  Map<String, int> frequencyTable = {
    'f': 1,
    'o': 2,
    'b': 1,
    'a': 1,
    'r': 1,
  };
  var result5 = huffmanCodingPrebuiltTable(text5, frequencyTable);
  print("Huffman Coding with Prebuilt Frequency Table:");
  print("Original text: $text5");
  print("Encoded text: ${result5['encodedText']}");
  print("Huffman Codes: ${result5['codes']}");
  print("Decoded text: ${huffmanDecode(result5['encodedText'], result5['codes'])}");
}

// --- 2. Huffman Coding Using a Sorted List ---
// Node class for the Huffman tree
class Node {
  int frequency;
  String? character;
  Node? left;
  Node? right;

  Node(this.frequency, {this.character, this.left, this.right});
}

// Function to build the Huffman tree
Node buildHuffmanTree(List<Node> nodes) {
  while (nodes.length > 1) {
    nodes.sort((a, b) => a.frequency.compareTo(b.frequency)); // Sort by frequency
    Node left = nodes.removeAt(0);
    Node right = nodes.removeAt(0);
    Node parent = Node(left.frequency + right.frequency, left: left, right: right);
    nodes.insert(0, parent); // Insert the new node back into the list
  }
  return nodes[0]; // Return the root of the tree
}

// Function to generate Huffman codes
Map<String, String> generateHuffmanCodes(Node? node, String code, Map<String, String> codes) {
  if (node == null) return codes;
  if (node.character != null) {
    codes[node.character!] = code;
    return codes;
  }
  generateHuffmanCodes(node.left, code + '0', codes);
  generateHuffmanCodes(node.right, code + '1', codes);
  return codes;
}

// Huffman coding function
Map<String, dynamic> huffmanCodingSortedList(String text) {
  // Calculate character frequencies
  Map<String, int> frequencyMap = {};
  for (int i = 0; i < text.length; i++) {
    String char = text[i];
    frequencyMap[char] = (frequencyMap[char] ?? 0) + 1;
  }

  // Create a list of nodes
  List<Node> nodes = frequencyMap.entries.map((entry) => Node(entry.value, character: entry.key)).toList();

  // Build the Huffman tree
  Node root = buildHuffmanTree(nodes);

  // Generate Huffman codes
  Map<String, String> codes = {};
  if(root != null){
    codes = generateHuffmanCodes(root, '', codes);
  }


  // Encode the text
  String encodedText = text.split('').map((char) => codes[char] ?? '').join(''); //handle null codes[char]

  return {'encodedText': encodedText, 'codes': codes};
}

// --- 3. Huffman Coding Using Recursive Approach ---
class RecursiveNode {
  int frequency;
  String? character;
  RecursiveNode? left, right;

  RecursiveNode(this.frequency, {this.character, this.left, this.right});
}

// Function to build Huffman tree recursively
RecursiveNode buildHuffmanTreeRecursive(Map<String, int> frequencyMap) {
  if (frequencyMap.isEmpty) {
    return RecursiveNode(0);
  }
  if (frequencyMap.length == 1) {
    String char = frequencyMap.keys.first;
    return RecursiveNode(frequencyMap[char]!, character: char);
  }

  // Find the two smallest frequencies
  List<MapEntry<String, int>> sortedFrequencies = frequencyMap.entries.toList()..sort((a, b) => a.value.compareTo(b.value));
  String char1 = sortedFrequencies[0].key;
  String char2 = sortedFrequencies[1].key;
  int freq1 = sortedFrequencies[0].value;
  int freq2 = sortedFrequencies[1].value;

  // Remove the two smallest frequencies from the map
  frequencyMap.remove(char1);
  frequencyMap.remove(char2);

  // Create a new parent node
  RecursiveNode parent = RecursiveNode(freq1 + freq2,
      left: RecursiveNode(freq1, character: char1),
      right: RecursiveNode(freq2, character: char2));

  // Recursively build the rest of the tree
  frequencyMap[char1 + char2] = parent.frequency; // Use a combined key
  return buildHuffmanTreeRecursive(frequencyMap);
}

// Function to generate Huffman codes
Map<String, String> generateHuffmanCodesRecursive(RecursiveNode? node, String code, Map<String, String> codes) {
  if (node == null) return codes;

  if (node.character != null) {
    codes[node.character!] = code;
    return codes;
  }

  generateHuffmanCodesRecursive(node.left, code + '0', codes);
  generateHuffmanCodesRecursive(node.right, code + '1', codes);
  return codes;
}

// Huffman coding function
Map<String, dynamic> huffmanCodingRecursive(String text) {
  // Calculate character frequencies
  Map<String, int> frequencyMap = {};
  for (int i = 0; i < text.length; i++) {
    String char = text[i];
    frequencyMap[char] = (frequencyMap[char] ?? 0) + 1;
  }

  // Build the Huffman tree
  RecursiveNode root = buildHuffmanTreeRecursive(frequencyMap);

  // Generate Huffman codes
  Map<String, String> codes = {};
  if(root != null){
    codes = generateHuffmanCodesRecursive(root, '', codes);
  }


  // Encode the text
  String encodedText = text.split('').map((char) => codes[char] ?? '').join(''); //handle null codes[char]


  return {'encodedText': encodedText, 'codes': codes};
}

// --- 4. Huffman Coding with Optimized Frequency Counting ---
Map<String, dynamic> huffmanCodingOptimized(String text) {
  // 1. Calculate frequency of each character using a list
  List<int> frequencies = List.filled(256, 0); // Assuming ASCII characters
  for (int i = 0; i < text.length; i++) {
    frequencies[text.codeUnitAt(i)]++;
  }

  // 2. Create a priority queue (min heap)
  PriorityQueue<HuffmanNode> pq = PriorityQueue<HuffmanNode>((a, b) => a.compareTo(b));
  for (int i = 0; i < 256; i++) {
    if (frequencies[i] > 0) {
      pq.add(HuffmanNode(frequencies[i], character: String.fromCharCode(i)));
    }
  }

  // 3. Build the Huffman tree
  while (pq.length > 1) {
    HuffmanNode left = pq.removeFirst();
    HuffmanNode right = pq.removeFirst();
    HuffmanNode parent = HuffmanNode(left.frequency + right.frequency, left: left, right: right);
    pq.add(parent);
  }

  // 4. Get the Huffman codes
  HuffmanNode? root = pq.first;
  Map<String, String> huffmanCodes = {};
  if(root != null) {
    huffmanCodes = buildHuffmanCodes(root, '', huffmanCodes);
  }

  // 5. Encode the text
  String encodedText = '';
  for (int i = 0; i < text.length; i++) {
    encodedText += huffmanCodes[text[i]] ?? '';  //handle null huffmanCodes[text[i]]
  }
  return {'encodedText': encodedText, 'codes': huffmanCodes};
}

// --- 5. Huffman Coding with Prebuilt Frequency Table ---
Map<String, dynamic> huffmanCodingPrebuiltTable(String text, Map<String, int> frequencyTable) {
  // 1. Create a priority queue (min heap)
  PriorityQueue<HuffmanNode> pq = PriorityQueue<HuffmanNode>((a, b) => a.compareTo(b));
  frequencyTable.forEach((char, freq) {
    pq.add(HuffmanNode(freq, character: char));
  });

  // 2. Build the Huffman tree
  while (pq.length > 1) {
    HuffmanNode left = pq.removeFirst();
    HuffmanNode right = pq.removeFirst();
    HuffmanNode parent = HuffmanNode(left.frequency + right.frequency, left: left, right: right);
    pq.add(parent);
  }

  // 3. Get the Huffman codes
  HuffmanNode? root = pq.first;
  Map<String, String> huffmanCodes = {};
  if(root != null){
    huffmanCodes = buildHuffmanCodes(root, '', huffmanCodes);
  }

  // 4. Encode the text
  String encodedText = '';
  for (int i = 0; i < text.length; i++) {
    encodedText += huffmanCodes[text[i]] ?? ''; //handle null huffmanCodes[text[i]]
  }
  return {'encodedText': encodedText, 'codes': huffmanCodes};
}
