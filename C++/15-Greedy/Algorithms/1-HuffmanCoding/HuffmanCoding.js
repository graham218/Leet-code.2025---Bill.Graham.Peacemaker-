// Huffman Coding in JavaScript - 5 Approaches

// 1. Basic Huffman Coding (Priority Queue with Array)
// ------------------------------------------------------

/**
 * Node class for the Huffman tree.
 */
class HuffmanNode {
  constructor(char, freq) {
    this.char = char;
    this.freq = freq;
    this.left = null;
    this.right = null;
  }
}

/**
 * Builds the Huffman tree and returns the root node.
 * Uses a simple array as a priority queue (not very efficient for large inputs).
 */
function buildHuffmanTreeBasic(charFreq) {
  if (!charFreq || charFreq.length === 0) {
    return null; // Handle empty input
  }
  const nodes = charFreq.map(([char, freq]) => new HuffmanNode(char, freq));

  while (nodes.length > 1) {
    // Sort to get the two smallest frequencies
    nodes.sort((a, b) => a.freq - b.freq);
    const left = nodes.shift();
    const right = nodes.shift();
    const newNode = new HuffmanNode(null, left.freq + right.freq);
    newNode.left = left;
    newNode.right = right;
    nodes.push(newNode);
  }

  return nodes[0]; // Root of the Huffman tree
}

/**
 * Generates the Huffman codes from the Huffman tree.
 */
function generateHuffmanCodesBasic(node, code = "", codes = {}) {
  if (!node) return codes; //handle empty node
  if (node.char) {
    codes[node.char] = code;
    return codes;
  }

  generateHuffmanCodesBasic(node.left, code + "0", codes);
  generateHuffmanCodesBasic(node.right, code + "1", codes);
  return codes;
}

/**
 * Encodes the text using the Huffman codes.
 */
function encodeTextBasic(text, codes) {
  if (!codes) return ""; // Handle empty codes
  let encodedText = "";
  for (const char of text) {
    encodedText += codes[char] || ''; // Handle chars not in codes
  }
  return encodedText;
}

/**
 * Decodes the text using the Huffman tree.
 */
function decodeTextBasic(encodedText, root) {
  if (!root) return ""; // Handle empty tree
  let decodedText = "";
  let currentNode = root;
  for (const bit of encodedText) {
    if (bit === "0") {
      currentNode = currentNode.left;
    } else {
      currentNode = currentNode.right;
    }

    if (currentNode && currentNode.char) { //check if currentNode is valid
      decodedText += currentNode.char;
      currentNode = root; // Reset to the root for the next character
    }
    else if (!currentNode) {
      return decodedText; //handle invalid encoded text
    }
  }
  return decodedText;
}

// 2. Huffman Coding with Optimized Priority Queue (Min Heap)
// ------------------------------------------------------------
class MinHeap {
  constructor() {
    this.heap = [];
  }

  getLeftChildIndex(index) { return 2 * index + 1; }
  getRightChildIndex(index) { return 2 * index + 2; }
  getParentIndex(index) { return Math.floor((index - 1) / 2); }

  hasLeftChild(index) { return this.getLeftChildIndex(index) < this.heap.length; }
  hasRightChild(index) { return this.getRightChildIndex(index) < this.heap.length; }
  hasParent(index) { return this.getParentIndex(index) >= 0; }

  leftChild(index) { return this.heap[this.getLeftChildIndex(index)]; }
  rightChild(index) { return this.heap[this.getRightChildIndex(index)]; }
  parent(index) { return this.heap[this.getParentIndex(index)]; }

  size() { return this.heap.length; }

  peek() {
    if (this.size() === 0) return null;
    return this.heap[0];
  }

  poll() {
    if (this.size() === 0) return null;
    if (this.size() === 1) return this.heap.pop();

    const item = this.heap[0];
    this.heap[0] = this.heap.pop();
    this.heapifyDown(0);
    return item;
  }

  add(item) {
    this.heap.push(item);
    this.heapifyUp(this.heap.length - 1);
  }

  heapifyUp(index) {
    while (this.hasParent(index) && this.parent(index).freq > this.heap[index].freq) {
      this.swap(index, this.getParentIndex(index));
      index = this.getParentIndex(index);
    }
  }

  heapifyDown(index) {
    while (this.hasLeftChild(index)) {
      let smallerChildIndex = this.getLeftChildIndex(index);
      if (this.hasRightChild(index) && this.rightChild(index).freq < this.leftChild(index).freq) {
        smallerChildIndex = this.getRightChildIndex(index);
      }

      if (this.heap[index].freq < this.heap[smallerChildIndex].freq) {
        break;
      } else {
        this.swap(index, smallerChildIndex);
      }
      index = smallerChildIndex;
    }
  }

  swap(index1, index2) {
    const temp = this.heap[index1];
    this.heap[index1] = this.heap[index2];
    this.heap[index2] = temp;
  }
}

function buildHuffmanTreeOptimized(charFreq) {
  if (!charFreq || charFreq.length === 0) {
    return null;
  }
  const minHeap = new MinHeap();
  charFreq.forEach(([char, freq]) => {
    minHeap.add(new HuffmanNode(char, freq));
  });

  while (minHeap.size() > 1) {
    const left = minHeap.poll();
    const right = minHeap.poll();
    const newNode = new HuffmanNode(null, left.freq + right.freq);
    newNode.left = left;
    newNode.right = right;
    minHeap.add(newNode);
  }
  return minHeap.peek();
}

function generateHuffmanCodesOptimized(node, code = "", codes = {}) {
  if (!node) return codes;
  if (node.char) {
    codes[node.char] = code;
    return codes;
  }
  generateHuffmanCodesOptimized(node.left, code + "0", codes);
  generateHuffmanCodesOptimized(node.right, code + "1", codes);
  return codes;
}

function encodeTextOptimized(text, codes) {
  if (!codes) return "";
  let encodedText = "";
  for (const char of text) {
    encodedText += codes[char] || '';
  }
  return encodedText;
}

function decodeTextOptimized(encodedText, root) {
  if (!root) return "";
  let decodedText = "";
  let currentNode = root;
  for (const bit of encodedText) {
    if (bit === "0") {
      currentNode = currentNode.left;
    } else {
      currentNode = currentNode.right;
    }
    if (currentNode && currentNode.char) {
      decodedText += currentNode.char;
      currentNode = root;
    }
     else if (!currentNode) {
      return decodedText;
    }
  }
  return decodedText;
}

// 3. Huffman Coding with ES6 Map and Optimized Object Creation
// ----------------------------------------------------------------------

function buildHuffmanTreeES6(charFreq) {
  if (!charFreq || charFreq.length === 0) {
    return null;
  }
  const nodes = charFreq.map(([char, freq]) => ({ char, freq, left: null, right: null }));
  const priorityQueue = [...nodes];

  while (priorityQueue.length > 1) {
    priorityQueue.sort((a, b) => a.freq - b.freq);
    const left = priorityQueue.shift();
    const right = priorityQueue.shift();
    const newNode = {
      char: null,
      freq: left.freq + right.freq,
      left,
      right,
    };
    priorityQueue.push(newNode);
  }
  return priorityQueue[0];
}

function generateHuffmanCodesES6(node, code = "", codes = new Map()) {
  if (!node) return codes;
  if (node.char) {
    codes.set(node.char, code);
    return codes;
  }
  generateHuffmanCodesES6(node.left, code + "0", codes);
  generateHuffmanCodesES6(node.right, code + "1", codes);
  return codes;
}

function encodeTextES6(text, codes) {
  if (!codes) return "";
  let encodedText = "";
  for (const char of text) {
    encodedText += codes.get(char) || '';
  }
  return encodedText;
}

function decodeTextES6(encodedText, root) {
  if (!root) return "";
  let decodedText = "";
  let currentNode = root;
  for (const bit of encodedText) {
    currentNode = bit === "0" ? currentNode.left : currentNode.right;
    if (currentNode && currentNode.char) {
      decodedText += currentNode.char;
      currentNode = root;
    }
    else if (!currentNode) {
      return decodedText;
    }
  }
  return decodedText;
}

// 4. Huffman Coding with Class and Static Methods
// ------------------------------------------------------
class HuffmanCoder {
  constructor(charFreq) {
    this.charFreq = charFreq;
    this.root = this.buildHuffmanTree();
    this.codes = this.generateHuffmanCodes();
  }

  buildHuffmanTree() {
    if (!this.charFreq || this.charFreq.length === 0) {
      return null;
    }
    const nodes = this.charFreq.map(([char, freq]) => ({ char, freq, left: null, right: null }));
    const priorityQueue = [...nodes];

    while (priorityQueue.length > 1) {
      priorityQueue.sort((a, b) => a.freq - b.freq);
      const left = priorityQueue.shift();
      const right = priorityQueue.shift();
      const newNode = { char: null, freq: left.freq + right.freq, left, right };
      priorityQueue.push(newNode);
    }
    return priorityQueue[0];
  }

  generateHuffmanCodes(node = this.root, code = "", codes = {}) {
    if (!node) return codes;
    if (node.char) {
      codes[node.char] = code;
    } else {
      this.generateHuffmanCodes(node.left, code + "0", codes);
      this.generateHuffmanCodes(node.right, code + "1", codes);
    }
    return codes;
  }

  encodeText(text) {
    if (!this.codes) return "";
    let encodedText = "";
    for (const char of text) {
      encodedText += this.codes[char] || '';
    }
    return encodedText;
  }

  decodeText(encodedText) {
    if (!this.root) return "";
    let decodedText = "";
    let currentNode = this.root;
    for (const bit of encodedText) {
      currentNode = bit === "0" ? currentNode.left : currentNode.right;
      if (currentNode && currentNode.char) {
        decodedText += currentNode.char;
        currentNode = this.root;
      }
      else if (!currentNode) {
        return decodedText;
      }
    }
    return decodedText;
  }

  static getFrequencies(text) {
    const freqMap = new Map();
    for (const char of text) {
      freqMap.set(char, (freqMap.get(char) || 0) + 1);
    }
    return Array.from(freqMap.entries());
  }
}

// 5. Huffman Coding with Modern ES6 (Classes, Maps, Concise Syntax)
// ----------------------------------------------------------------------
class HuffmanEncoder {
  constructor(text) {
    this.text = text;
    this.frequencies = this.calculateFrequencies();
    this.root = this.buildTree();
    this.codes = this.generateCodes();
  }

  calculateFrequencies() {
    const freqMap = new Map();
    for (const char of this.text) {
      freqMap.set(char, (freqMap.get(char) || 0) + 1);
    }
    return Array.from(freqMap.entries());
  }

  buildTree() {
    if (!this.frequencies || this.frequencies.length === 0) {
      return null;
    }
    const nodes = Array.from(this.frequencies).map(([char, freq]) => ({ char, freq, left: null, right: null }));
    const queue = [...nodes];

    while (queue.length > 1) {
      queue.sort((a, b) => a.freq - b.freq);
      const left = queue.shift();
      const right = queue.shift();
      const parent = { char: null, freq: left.freq + right.freq, left, right };
      queue.push(parent);
    }
    return queue[0];
  }

  generateCodes(node = this.root, code = "") {
    const codes = new Map();
    const _generate = (node, code) => { // Inner recursive function
      if (!node) return;
      if (node.char) {
        codes.set(node.char, code);
      } else {
        _generate(node.left, code + "0");
        _generate(node.right, code + "1");
      }
    };
    _generate(node, code); // Start the recursion
    return codes;
  }

  encode() {
    if (!this.codes) return "";
    return this.text.split('').map(char => this.codes.get(char) || '').join('');
  }

  decode(encodedText) {
    if (!this.root) return "";
    let decodedText = '';
    let current = this.root;
    for (const bit of encodedText) {
      current = bit === '0' ? current.left : current.right;
      if (current && current.char) {
        decodedText += current.char;
        current = this.root;
      }
      else if (!current) {
        return decodedText;
      }
    }
    return decodedText;
  }
}

// Example Usage and Output
// ----------------------
const text = "hello world";
const charFreq = [...new Map().entries(new Map(text.split('').map(c => [c, text.split('').filter(x => x === c).length])))]; // Calculate character frequencies

console.log("Input Text:", text);
console.log("Character Frequencies:", charFreq);

// 1. Basic Huffman Coding
console.log("\n1. Basic Huffman Coding:");
const rootBasic = buildHuffmanTreeBasic(charFreq);
const codesBasic = generateHuffmanCodesBasic(rootBasic);
const encodedTextBasic = encodeTextBasic(text, codesBasic);
const decodedTextBasic = decodeTextBasic(encodedTextBasic, rootBasic);
console.log("Codes:", codesBasic);
console.log("Encoded Text:", encodedTextBasic);
console.log("Decoded Text:", decodedTextBasic);

// 2. Huffman Coding with Optimized Priority Queue (Min Heap)
console.log("\n2. Huffman Coding with Optimized Priority Queue (Min Heap):");
const rootOptimized = buildHuffmanTreeOptimized(charFreq);
const codesOptimized = generateHuffmanCodesOptimized(rootOptimized);
const encodedTextOptimized = encodeTextOptimized(text, codesOptimized);
const decodedTextOptimized = decodeTextOptimized(encodedTextOptimized, rootOptimized);
console.log("Codes:", codesOptimized);
console.log("Encoded Text:", encodedTextOptimized);
console.log("Decoded Text:", decodedTextOptimized);

// 3. Huffman Coding with ES6 Map
console.log("\n3. Huffman Coding with ES6 Map:");
const rootES6 = buildHuffmanTreeES6(charFreq);
const codesES6 = generateHuffmanCodesES6(rootES6);
const encodedTextES6 = encodeTextES6(text, codesES6);
const decodedTextES6 = decodeTextES6(encodedTextES6, rootES6);
console.log("Codes:", codesES6);
console.log("Encoded Text:", encodedTextES6);
console.log("Decoded Text:", decodedTextES6);

// 4. Huffman Coding with Class and Static Methods
console.log("\n4. Huffman Coding with Class and Static Methods:");
const coder = new HuffmanCoder(charFreq);
const encodedTextClass = coder.encodeText(text);
const decodedTextClass = coder.decodeText(encodedTextClass);
console.log("Codes:", coder.codes);
console.log("Encoded Text:", encodedTextClass);
console.log("Decoded Text:", decodedTextClass);

// 5. Huffman Coding with Modern ES6
console.log("\n5. Huffman Coding with Modern ES6:");
const encoder = new HuffmanEncoder(text);
const encodedTextModern = encoder.encode();
const decodedTextModern = encoder.decode(encodedTextModern);
console.log("Codes:", encoder.codes);
console.log("Encoded Text:", encodedTextModern);
console.log("Decoded Text:", decodedTextModern);
