// Huffman Coding Implementation in JavaScript

/**
 * Huffman Coding is a data compression algorithm.  It's "greedy" because it makes the locally optimal choice
 * at each step (choosing the two smallest frequencies to merge).
 *
 * Here's a breakdown of how it works:
 *
 * 1.  **Frequency Analysis:** Calculate the frequency of each character in the input text.
 * 2.  **Priority Queue (Min-Heap):** Create a priority queue (min-heap) where each node represents a character
 * and its frequency.  The node with the lowest frequency has the highest priority.
 * 3.  **Tree Construction:**
 * -   Repeatedly remove the two nodes with the lowest frequencies from the priority queue.
 * -   Create a new parent node whose frequency is the sum of the two child nodes' frequencies.
 * -   Make the two removed nodes the left and right children of this new parent node.
 * -   Insert the new parent node back into the priority queue.
 * -   Repeat until only one node remains in the queue; this is the root of the Huffman tree.
 * 4.  **Code Assignment:** Traverse the Huffman tree to assign a unique binary code to each character.
 * -   Typically, a left branch is assigned the bit '0', and a right branch is assigned '1'.
 * -   The code for a character is the sequence of bits encountered on the path from the root to that character.
 * 5.  **Encoding:** Replace each character in the input text with its corresponding Huffman code.
 * 6.  **Decoding:** Use the Huffman tree to decode the encoded text.
 * -   Start at the root of the tree.
 * -   For each bit in the encoded text:
 * -   If the bit is '0', move to the left child.
 * -   If the bit is '1', move to the right child.
 * -   When a leaf node is reached, the character at that leaf is the decoded character.
 * -   Return to the root and continue with the next bit in the encoded text.
 */

// --- Helper Functions ---

/**
 * Creates a min-heap (priority queue) from an array.  This is a very common utility.
 * @param {Array<{char: string, frequency: number}>} array - The input array of nodes.
 * @returns {Array<{char: string, frequency: number}>} - The min-heap.
 */
function createMinHeap(array) {
    const heap = [...array]; // Don't modify original array
    for (let i = Math.floor(heap.length / 2) - 1; i >= 0; i--) {
        minHeapify(heap, i);
    }
    return heap;
}

/**
 * Maintains the min-heap property starting from a given index.
 * @param {Array<{char: string, frequency: number}>} heap - The min-heap.
 * @param {number} i - The index to start from.
 */
function minHeapify(heap, i) {
    const left = 2 * i + 1;
    const right = 2 * i + 2;
    let smallest = i;

    if (left < heap.length && heap[left].frequency < heap[smallest].frequency) {
        smallest = left;
    }

    if (right < heap.length && heap[right].frequency < heap[smallest].frequency) {
        smallest = right;
    }

    if (smallest !== i) {
        [heap[i], heap[smallest]] = [heap[smallest], heap[i]]; // Swap
        minHeapify(heap, smallest);
    }
}

/**
 * Extracts the node with the minimum frequency from the min-heap.
 * @param {Array<{char: string, frequency: number}>} heap - The min-heap.
 * @returns {{char: string, frequency: number}} - The node with the minimum frequency, or null if the heap is empty.
 */
function extractMin(heap) {
    if (heap.length === 0) {
        return null;
    }
    if (heap.length === 1) {
        return heap.pop();
    }
    const min = heap[0];
    heap[0] = heap.pop();
    minHeapify(heap, 0);
    return min;
}

/**
 * Inserts a new node into the min-heap.
 * @param {Array<{char: string, frequency: number}>} heap - The min-heap.
 * @param {{char: string, frequency: number}} node - The node to insert.
 */
function insert(heap, node) {
    heap.push(node);
    let i = heap.length - 1;
    while (i > 0) {
        const parent = Math.floor((i - 1) / 2);
        if (heap[i].frequency < heap[parent].frequency) {
            [heap[i], heap[parent]] = [heap[parent], heap[i]]; // Swap
            i = parent;
        } else {
            break;
        }
    }
}

/**
 * Builds the Huffman tree from a frequency table.
 * @param {Array<{char: string, frequency: number}>} frequencyTable - An array of character frequencies.
 * @returns {{char: string, frequency: number, left?: any, right?: any} | null} - The root of the Huffman tree.
 */
function buildHuffmanTree(frequencyTable) {
    if (!frequencyTable || frequencyTable.length === 0) {
        return null;
    }

    const minHeap = createMinHeap(frequencyTable);

    while (minHeap.length > 1) {
        const left = extractMin(minHeap);
        const right = extractMin(minHeap);
        if (!left || !right) break; // defensive, should not happen with proper input
        const parent = {
            char: '', // Internal node, no actual character
            frequency: left.frequency + right.frequency,
            left: left,
            right: right,
        };
        insert(minHeap, parent);
    }

    return minHeap[0]; // The last remaining node is the root of the tree
}

/**
 * Generates the Huffman codes from the Huffman tree.  This is a recursive function.
 * @param {{char: string, frequency: number, left?: any, right?: any} | null} node - The current node in the Huffman tree.
 * @param {string} code - The current Huffman code string.
 * @param {Object<string, string>} codeMap - The map to store the generated codes.
 */
function generateHuffmanCodes(node, code, codeMap) {
    if (!node) return;

    if (node.char) {
        codeMap[node.char] = code;
    } else {
        generateHuffmanCodes(node.left, code + '0', codeMap);
        generateHuffmanCodes(node.right, code + '1', codeMap);
    }
}

/**
 * Encodes the input text using the Huffman codes.
 * @param {string} text - The input text to encode.
 * @param {Object<string, string>} codeMap - The map of character to Huffman codes.
 * @returns {string} - The encoded text.
 */
function encodeText(text, codeMap) {
    let encodedText = '';
    for (const char of text) {
        encodedText += codeMap[char];
    }
    return encodedText;
}

/**
 * Decodes the encoded text using the Huffman tree.
 * @param {string} encodedText - The encoded text.
 * @param {{char: string, frequency: number, left?: any, right?: any} | null} root - The root of the Huffman tree.
 * @returns {string} - The decoded text.
 */
function decodeText(encodedText, root) {
    if (!root) return '';
    let decodedText = '';
    let currentNode = root;
    for (const bit of encodedText) {
        if (bit === '0') {
            currentNode = currentNode.left;
        } else {
            currentNode = currentNode.right;
        }

        if (currentNode.char) {
            decodedText += currentNode.char;
            currentNode = root; // Reset to the root to start decoding the next character
        }
    }
    return decodedText;
}

/**
 * Calculates the frequency of each character in the input text.
 * @param {string} text - The input text.
 * @returns {Array<{char: string, frequency: number}>} - An array of character frequencies.
 */
function getCharacterFrequencies(text) {
    const frequencyMap = new Map();
    for (const char of text) {
        frequencyMap.set(char, (frequencyMap.get(char) || 0) + 1);
    }
    const frequencyTable = [];
    for (const [char, frequency] of frequencyMap) {
        frequencyTable.push({ char, frequency });
    }
    return frequencyTable;
}

// --- Main Function ---

/**
 * Performs Huffman coding on the input text.
 * @param {string} text - The input text to encode and decode.
 * @returns {{
 * originalText: string,
 * encodedText: string,
 * decodedText: string,
 * codeMap: Object<string, string>,
 * tree: any // The huffman tree
 * }} - The original text, encoded text, decoded text, and the Huffman code mapping.
 */
function huffmanCoding(text) {
    if (!text) {
      return {
        originalText: "",
        encodedText: "",
        decodedText: "",
        codeMap: {},
        tree: null,
      };
    }
    const frequencyTable = getCharacterFrequencies(text);
    const tree = buildHuffmanTree(frequencyTable);
    const codeMap = {};
    generateHuffmanCodes(tree, '', codeMap);
    const encodedText = encodeText(text, codeMap);
    const decodedText = decodeText(encodedText, tree);

    return {
        originalText: text,
        encodedText: encodedText,
        decodedText: decodedText,
        codeMap: codeMap,
        tree: tree
    };
}

// --- Example Usage ---

const text = "this is an example of huffman coding";
const result = huffmanCoding(text);

console.log("Original Text:", result.originalText);
console.log("Encoded Text:", result.encodedText);
console.log("Decoded Text:", result.decodedText);
console.log("Huffman Codes:", result.codeMap);
console.log("Huffman Tree:", result.tree);


// --- 5 Real-World Project Implementations and Explanations ---

// 1. File Compression (e.g., gzip)
//    - Explanation:  gzip (and other compression tools like zip, bzip2) often use Huffman coding as one stage
//      in their compression pipeline.  They might use it in combination with other algorithms like Lempel-Ziv
//      (LZ77, LZ78) for better compression.  The frequency table is either pre-defined or calculated
//      for each file being compressed and stored in the file header, so the decompressor knows how to decode it.
//    - JavaScript Implementation:  While you wouldn't implement the entire gzip algorithm in JavaScript for
//      production (it's usually done in C for performance), you could use the core Huffman coding part.
//      For example, you might have a web application that compresses small text snippets before sending
//      them to a server.  Libraries like `pako` (which is a zlib port) are more commonly used.  Here's a conceptual
//      example:

function compressData(data) {
    const result = huffmanCoding(data); // Use our huffmanCoding function
    // In a real implementation, you would need to store the codeMap (or the Huffman tree)
    // along with the encoded data so it can be decoded.  This is a simplified example.
    return {
      compressedData: result.encodedText,
      codeMap: result.codeMap
    };
}

function decompressData(compressedData, codeMap) {
    // In a real implementation you would reconstruct the tree from the codeMap
    const reconstructedTree = buildTreeFromCodeMap(codeMap); // Not implemented here.
    const result = huffmanCoding(" ");
    result.tree = reconstructedTree;
    const decoded = decodeText(compressedData, result.tree);
    return decoded;
}
function buildTreeFromCodeMap(codeMap) {
  const characters = Object.keys(codeMap);
  const frequencies = characters.map(char => ({char: char, frequency: 1})); // Made up freqs
  const tree = buildHuffmanTree(frequencies);
  return tree;
}

const dataToCompress = "This is data for compression";
const compressed = compressData(dataToCompress);
const decompressed = decompressData(compressed.compressedData, compressed.codeMap);

console.log("1. File Compression:");
console.log("Original Data:", dataToCompress);
console.log("Compressed Data:", compressed.compressedData);
console.log("Decompressed Data:", decompressed);


// 2. Image Compression (JPEG)
//    - Explanation: JPEG uses a technique called Discrete Cosine Transform (DCT) to convert images into frequency
//      components.  Huffman coding is then used to compress these frequency components.  Specifically, it's
//      used to compress the quantized DCT coefficients.  JPEG uses a standardized set of Huffman tables,
//      though optimized tables can also be used.
//    - JavaScript Implementation:  Directly implementing JPEG compression in JavaScript is complex.
//      Browsers handle JPEG decoding natively.  For encoding, you'd typically use a library (though many are
//      large).  Here's a *very* simplified conceptual example focusing on the Huffman part:
function compressImage(imageData) {
  // Simplified: Assume we have DCT coefficients (in reality, this is much more complex)
  const coefficients = [50, 10, 5, 5, 2, 2, 0, 0, 0, 1, -1, -1, -2, 0, 0, 0]; // Example data
  const frequencyTable = getCharacterFrequencies(coefficients.join('')); // Naive frequency
  const tree = buildHuffmanTree(frequencyTable);
  const codeMap = {};
  generateHuffmanCodes(tree, '', codeMap);
  const compressedCoefficients = encodeText(coefficients.join(''), codeMap);

  return { compressedData: compressedCoefficients, codeMap: codeMap };
}

function decompressImage(compressedData, codeMap) {
    const reconstructedTree = buildTreeFromCodeMap(codeMap);
    const result = huffmanCoding(" ");
    result.tree = reconstructedTree;
    const decodedCoefficients = decodeText(compressedData, result.tree);
  return decodedCoefficients;
}
const imageData = { width: 100, height: 100, data: [] }; //  fixed image data.  The '...' was causing the error.
const compressedImage = compressImage(imageData);
const decompressedImage = decompressImage(compressedImage.compressedData, compressedImage.codeMap);

console.log("2. Image Compression (Conceptual):");
console.log("Compressed Image Data:", compressedImage.compressedData);
console.log("Decompressed Image Data:", decompressedImage);


// 3. Text Compression in Databases
//    - Explanation: Some database systems use Huffman coding (or similar compression techniques) to reduce the
//      storage space required for text data, especially for columns containing repetitive text.  This can improve
//      storage efficiency and potentially also I/O performance.
//    - JavaScript Implementation:  This would usually be part of the database's internal implementation, not
//      directly accessible to JavaScript.  However, you could simulate this for a web application that uses
//      a local database (like IndexedDB) to store compressed text.
function storeCompressedText(db, text, key) {
    const transaction = db.transaction(['textData'], 'readwrite');
    const store = transaction.objectStore('textData');
    const compressedData = huffmanCoding(text); // Use our function
    // Store both the compressed text and the codeMap (or enough info to reconstruct the tree)
    store.put({ key: key, compressedText: compressedData.encodedText, codeMap: compressedData.codeMap });
    return compressedData;
}

function retrieveAndDecompressText(db, key) {
    const transaction = db.transaction(['textData'], 'readonly');
    const store = transaction.objectStore('textData');
    const request = store.get(key);
    return new Promise((resolve, reject) => {
        request.onsuccess = (event) => {
            const data = event.target.result;
            if (data) {
                const reconstructedTree = buildTreeFromCodeMap(data.codeMap);
                const result = huffmanCoding(" ");
                result.tree = reconstructedTree;
                const decompressedText = decodeText(data.compressedText, result.tree);
                resolve(decompressedText);
            } else {
                resolve(null); // Key not found
            }
        };
        request.onerror = () => reject(request.error);
    });
}
// Mock IndexedDB
const mockDB = {
    transaction: (stores, mode) => ({
        objectStore: (storeName) => {
            const dataStore = {};
            return {
                put: (data) => {
                    dataStore[data.key] = data;
                },
                get: (key) => {
                    return {
                        onsuccess: (callback) => {
                            callback({ target: { result: dataStore[key] } });
                        },
                        onerror: (callback) => {

                        },
                    };
                },
            };
        },
    }),
};

const textKey = 'myText';
const textToStore = 'This is some text to store in the database.';
const compressedTextData = storeCompressedText(mockDB, textToStore, textKey);

retrieveAndDecompressText(mockDB, textKey).then(retrievedText => {
    console.log("3. Text Compression in Databases (Conceptual):");
    console.log("Stored Compressed Text:", compressedTextData.encodedText);
    console.log("Retrieved and Decompressed Text:", retrievedText);
});


// 4. Network Protocol Optimization (e.g., HTTP/2 HPACK)
//    - Explanation: HTTP/2's HPACK (Header Compression) uses Huffman coding to compress HTTP headers.  Headers
//      are often repetitive (e.g., many requests to the same server have the same `Host` header), so compressing
//      them can significantly reduce the amount of data transmitted, improving performance.  HPACK uses a
//      predefined Huffman table.
//    - JavaScript Implementation:  You wouldn't implement HPACK from scratch in JavaScript for a typical web
//      application.  Browsers and servers handle HTTP/2 negotiation and header compression.  But, you could
//      demonstrate the Huffman coding part conceptually.

const httpHeaders = {
    method: 'GET',
    path: '/',
    host: 'example.com',
    'user-agent': 'MyBrowser/1.0',
    'content-type': 'application/json',
    'accept-encoding': 'gzip, deflate',
    host: 'example.com', // Repeated header
    method: 'GET'
};

function compressHttpHeaders(headers) {
    let headerString = '';
    for (const [key, value] of Object.entries(headers)) {
        headerString += `${key}:${value};`;
    }
    const frequencyTable = getCharacterFrequencies(headerString);
    const tree = buildHuffmanTree(frequencyTable);
    const codeMap = {};
    generateHuffmanCodes(tree, '', codeMap);
    const compressedHeaders = encodeText(headerString, codeMap);
    return { compressedHeaders, codeMap };
}

function decompressHttpHeaders(compressedHeaders, codeMap) {
  const reconstructedTree = buildTreeFromCodeMap(codeMap);
  const result = huffmanCoding(" ");
  result.tree = reconstructedTree;
  const decompressedHeaders = decodeText(compressedHeaders, result.tree);
  return decompressedHeaders;
}
const compressedHeadersData = compressHttpHeaders(httpHeaders);
const decompressedHeadersData = decompressHttpHeaders(compressedHeadersData.compressedHeaders, compressedHeadersData.codeMap);

console.log("4. Network Protocol Optimization (Conceptual):");
console.log("Original Headers:", httpHeaders);
console.log("Compressed Headers:", compressedHeadersData.compressedHeaders);
console.log("Decompressed Headers:", decompressedHeadersData);


// 5. Data Serialization (Custom Formats)
//   - Explanation: When you need to serialize data into a compact binary format (e.g., for efficient storage
//     or network transmission), you can use Huffman coding to compress frequently occurring data patterns.
//     This is useful when you have control over both the encoding and decoding sides.
//   - JavaScript Implementation:  You might use this in a game or a real-time application where you're
//     sending data between a server and a client, and you want to minimize bandwidth.

function serializeData(data) {
    const dataString = JSON.stringify(data); // Example: Serialize a JS object
    const result = huffmanCoding(dataString);
    return {
      serializedData: result.encodedText,
      codeMap: result.codeMap
    };
}

function deserializeData(serializedData, codeMap) {
  try{
    const reconstructedTree = buildTreeFromCodeMap(codeMap);
    const result = huffmanCoding(" ");
    result.tree = reconstructedTree;
    const decodedData = decodeText(serializedData, result.tree);
    return JSON.parse(decodedData);
  } catch(e){
    console.error("Error during deserialization", e);
    return null;
  }
}
const dataToSerialize = {
    type: 'message',
    payload: {
        text: 'Hello, world!',
        timestamp: Date.now(),
        sender: 'user123',
    },
    priority: 'high',
};

const serialized = serializeData(dataToSerialize);
const deserialized = deserializeData(serialized.serializedData, serialized.codeMap);

console.log("5. Data Serialization (Conceptual):");
console.log("Original Data:", dataToSerialize);
console.log("Serialized Data:", serialized.serializedData);
console.log("Deserialized Data:", deserialized);
