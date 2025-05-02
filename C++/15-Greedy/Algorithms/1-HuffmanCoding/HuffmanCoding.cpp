#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <functional>
#include <stack> // Include stack for iterative code generation

// Structure to represent a node in the Huffman tree
struct HuffmanNode {
    char data;
    unsigned frequency;
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(char data, unsigned frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}

    ~HuffmanNode() {
        delete left;
        delete right;
    }
};

// Function to compare two Huffman nodes (used for priority queue)
struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

// Function to build the Huffman tree
HuffmanNode* buildHuffmanTree(std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes>& pq) {
    // While there are more than one node in the queue
    while (pq.size() > 1) {
        // Get the two nodes with the lowest frequencies
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        // Create a new internal node with the sum of the two frequencies
        HuffmanNode* internalNode = new HuffmanNode('\0', left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        // Add the new internal node to the queue
        pq.push(internalNode);
    }
    // The last node remaining in the queue is the root of the Huffman tree
    return pq.top();
}

// Function to generate Huffman codes from the Huffman tree (Recursive Approach 1)
void generateHuffmanCodes(HuffmanNode* root, std::string code, std::map<char, std::string>& huffmanCodes) {
    if (root == nullptr) return; // handle null root
    if (root->data != '\0') {
        huffmanCodes[root->data] = code;
    } else {
        generateHuffmanCodes(root->left, code + "0", huffmanCodes);
        generateHuffmanCodes(root->right, code + "1", huffmanCodes);
    }
}

// Function to encode text using Huffman codes
std::string encodeText(const std::string& text, const std::map<char, std::string>& huffmanCodes) {
    std::string encodedText = "";
    for (char c : text) {
        encodedText += huffmanCodes.at(c); // Use .at() for bounds checking
    }
    return encodedText;
}

// Function to decode text using the Huffman tree
std::string decodeText(const std::string& encodedText, HuffmanNode* root) {
    std::string decodedText = "";
    HuffmanNode* current = root;
    for (char bit : encodedText) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        } else {
             throw std::invalid_argument("Invalid character in encoded text.  Must be '0' or '1'.");
        }

        if (current->left == nullptr && current->right == nullptr) {
            decodedText += current->data;
            current = root; // Reset to the root for the next character
        }
    }
    return decodedText;
}

// Function to calculate frequency of each character in the input text
std::map<char, unsigned> calculateFrequency(const std::string& text) {
    std::map<char, unsigned> frequencyMap;
    for (char c : text) {
        frequencyMap[c]++;
    }
    return frequencyMap;
}

// ------------------------------------------------------------------------------------------------
// Approach 1: Basic Huffman Coding
// ------------------------------------------------------------------------------------------------
void huffmanCodingBasic(const std::string& text) {
    std::cout << "\nApproach 1: Basic Huffman Coding\n";

    // 1. Calculate character frequencies
    std::map<char, unsigned> frequencyMap = calculateFrequency(text);

    // 2. Create a priority queue of Huffman nodes
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> pq;
    for (const auto& pair : frequencyMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    // Check for empty input
    if (pq.empty()) {
        std::cout << "Input text is empty.\n";
        return;
    }
     // Handle the special case where the input text has only one unique character.
    if (pq.size() == 1) {
        std::map<char, std::string> huffmanCodes;
        HuffmanNode* root = pq.top();
        huffmanCodes[root->data] = "0"; // Assign "0" as the code for the single character
        std::string encodedText = encodeText(text, huffmanCodes);
        std::cout << "Original text: " << text << "\n";
        std::cout << "Encoded text: " << encodedText << "\n";
        std::cout << "Decoded text: " << text << "\n"; // Decoding is the same as original
        return;
    }

    // 3. Build the Huffman tree
    HuffmanNode* root = buildHuffmanTree(pq);

    // 4. Generate Huffman codes
    std::map<char, std::string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // 5. Encode the text
    std::string encodedText = encodeText(text, huffmanCodes);

    // 6. Decode the text
    std::string decodedText = decodeText(encodedText, root);

    // 7. Print the results
    std::cout << "Original text: " << text << "\n";
    std::cout << "Encoded text: " << encodedText << "\n";
    std::cout << "Decoded text: " << decodedText << "\n";

    // 8. Clean up memory (Important!)
    delete root;
}

// ------------------------------------------------------------------------------------------------
// Approach 2: Huffman Coding with Optimized Frequency Calculation
// ------------------------------------------------------------------------------------------------
// In this approach, we optimize the frequency calculation by using an array instead of a map,
// assuming the input text uses ASCII characters (0-255).  This can be faster in some cases.
void huffmanCodingOptimizedFrequency(const std::string& text) {
    std::cout << "\nApproach 2: Huffman Coding with Optimized Frequency Calculation\n";

    // 1. Calculate character frequencies using an array
    unsigned frequencies[256] = {0}; // Assuming ASCII characters
    for (char c : text) {
        frequencies[static_cast<unsigned char>(c)]++; // Use static_cast to handle char to unsigned conversion
    }

    // 2. Create a priority queue of Huffman nodes
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> pq;
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            pq.push(new HuffmanNode(static_cast<char>(i), frequencies[i]));
        }
    }

    // Check for empty input
    if (pq.empty()) {
        std::cout << "Input text is empty.\n";
        return;
    }
     // Handle the special case where the input text has only one unique character.
    if (pq.size() == 1) {
        std::map<char, std::string> huffmanCodes;
        HuffmanNode* root = pq.top();
        huffmanCodes[root->data] = "0"; // Assign "0" as the code for the single character
        std::string encodedText = encodeText(text, huffmanCodes);
        std::cout << "Original text: " << text << "\n";
        std::cout << "Encoded text: " << encodedText << "\n";
        std::cout << "Decoded text: " << text << "\n"; // Decoding is the same as original
        return;
    }

    // 3. Build the Huffman tree
    HuffmanNode* root = buildHuffmanTree(pq);

    // 4. Generate Huffman codes
    std::map<char, std::string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // 5. Encode the text
    std::string encodedText = encodeText(text, huffmanCodes);

    // 6. Decode the text
    std::string decodedText = decodeText(encodedText, root);

    // 7. Print the results
    std::cout << "Original text: " << text << "\n";
    std::cout << "Encoded text: " << encodedText << "\n";
    std::cout << "Decoded text: " << decodedText << "\n";

    // 8. Clean up memory
    delete root;
}

// ------------------------------------------------------------------------------------------------
// Approach 3: Huffman Coding with Iterative Code Generation
// ------------------------------------------------------------------------------------------------
//  Instead of recursion, use a stack to generate the codes.
void generateHuffmanCodesIterative(HuffmanNode* root, std::map<char, std::string>& huffmanCodes) {
    if (!root) return;

    std::stack<std::pair<HuffmanNode*, std::string>> s;
    s.push({root, ""});

    while (!s.empty()) {
        HuffmanNode* node = s.top().first;
        std::string code = s.top().second;
        s.pop();

        if (node->data != '\0') {
            huffmanCodes[node->data] = code;
        } else {
            if (node->right) s.push({node->right, code + "1"});
            if (node->left) s.push({node->left, code + "0"});
        }
    }
}

void huffmanCodingIterativeCodeGeneration(const std::string& text) {
    std::cout << "\nApproach 3: Huffman Coding with Iterative Code Generation\n";
      // 1. Calculate character frequencies
    std::map<char, unsigned> frequencyMap = calculateFrequency(text);

    // 2. Create a priority queue of Huffman nodes
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> pq;
    for (const auto& pair : frequencyMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    // Check for empty input
    if (pq.empty()) {
        std::cout << "Input text is empty.\n";
        return;
    }
     // Handle the special case where the input text has only one unique character.
    if (pq.size() == 1) {
        std::map<char, std::string> huffmanCodes;
        HuffmanNode* root = pq.top();
        huffmanCodes[root->data] = "0"; // Assign "0" as the code for the single character
        std::string encodedText = encodeText(text, huffmanCodes);
        std::cout << "Original text: " << text << "\n";
        std::cout << "Encoded text: " << encodedText << "\n";
        std::cout << "Decoded text: " << text << "\n"; // Decoding is the same as original
        return;
    }

    // 3. Build the Huffman tree
    HuffmanNode* root = buildHuffmanTree(pq);

    // 4. Generate Huffman codes (Iterative)
    std::map<char, std::string> huffmanCodes;
    generateHuffmanCodesIterative(root, huffmanCodes);

    // 5. Encode the text
    std::string encodedText = encodeText(text, huffmanCodes);

    // 6. Decode the text
    std::string decodedText = decodeText(encodedText, root);

    // 7. Print the results
    std::cout << "Original text: " << text << "\n";
    std::cout << "Encoded text: " << encodedText << "\n";
    std::cout << "Decoded text: " << decodedText << "\n";

    // 8. Clean up memory
    delete root;
}

// ------------------------------------------------------------------------------------------------
// Approach 4: Huffman Coding with Pre-calculated Frequencies
// ------------------------------------------------------------------------------------------------
// This approach takes the frequency map as input, allowing for pre-calculated frequencies.
void huffmanCodingWithFrequencies(const std::string& text, const std::map<char, unsigned>& frequencyMap) {
    std::cout << "\nApproach 4: Huffman Coding with Pre-calculated Frequencies\n";

    // 1. Use the provided frequency map.  No need to calculate it again.

    // 2. Create a priority queue of Huffman nodes
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> pq;
    for (const auto& pair : frequencyMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    // Check for empty input
    if (pq.empty()) {
        std::cout << "Input text is empty.\n";
        return;
    }
     // Handle the special case where the input text has only one unique character.
    if (pq.size() == 1) {
        std::map<char, std::string> huffmanCodes;
        HuffmanNode* root = pq.top();
        huffmanCodes[root->data] = "0"; // Assign "0" as the code for the single character
        std::string encodedText = encodeText(text, huffmanCodes);
        std::cout << "Original text: " << text << "\n";
        std::cout << "Encoded text: " << encodedText << "\n";
        std::cout << "Decoded text: " << text << "\n"; // Decoding is the same as original
        return;
    }

    // 3. Build the Huffman tree
    HuffmanNode* root = buildHuffmanTree(pq);

    // 4. Generate Huffman codes
    std::map<char, std::string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // 5. Encode the text
    std::string encodedText = encodeText(text, huffmanCodes);

    // 6. Decode the text
    std::string decodedText = decodeText(encodedText, root);

    // 7. Print the results
    std::cout << "Original text: " << text << "\n";
    std::cout << "Encoded text: " << encodedText << "\n";
    std::cout << "Decoded text: " << decodedText << "\n";

    // 8. Clean up memory
    delete root;
}

// ------------------------------------------------------------------------------------------------
// Approach 5: Huffman Coding with Custom Comparison Function
// ------------------------------------------------------------------------------------------------
//  Use a custom comparison function (functor) instead of a struct.
struct CompareNodesFunctor {
     bool operator()(const HuffmanNode* a, const HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};
void huffmanCodingCustomComparison(const std::string& text) {
    std::cout << "\nApproach 5: Huffman Coding with Custom Comparison Function\n";

    // 1. Calculate character frequencies
    std::map<char, unsigned> frequencyMap = calculateFrequency(text);

    // 2. Create a priority queue of Huffman nodes, using the functor
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodesFunctor> pq;
    for (const auto& pair : frequencyMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    // Check for empty input
    if (pq.empty()) {
        std::cout << "Input text is empty.\n";
        return;
    }
     // Handle the special case where the input text has only one unique character.
    if (pq.size() == 1) {
        std::map<char, std::string> huffmanCodes;
        HuffmanNode* root = pq.top();
        huffmanCodes[root->data] = "0"; // Assign "0" as the code for the single character
        std::string encodedText = encodeText(text, huffmanCodes);
        std::cout << "Original text: " << text << "\n";
        std::cout << "Encoded text: " << encodedText << "\n";
        std::cout << "Decoded text: " << text << "\n"; // Decoding is the same as original
        return;
    }

    // 3. Build the Huffman tree
    // Changed to use CompareNodesFunctor
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> pq2;
    while(!pq.empty()){
        pq2.push(pq.top());
        pq.pop();
    }
    HuffmanNode* root = buildHuffmanTree(pq2);

    // 4. Generate Huffman codes
    std::map<char, std::string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // 5. Encode the text
    std::string encodedText = encodeText(text, huffmanCodes);

    // 6. Decode the text
    std::string decodedText = decodeText(encodedText, root);

    // 7. Print the results
    std::cout << "Original text: " << text << "\n";
    std::cout << "Encoded text: " << encodedText << "\n";
    std::cout << "Decoded text: " << decodedText << "\n";

    // 8. Clean up memory
    delete root;
}

int main() {
    std::string text = "this is an example of huffman coding";

    // Approach 1: Basic Huffman Coding
    huffmanCodingBasic(text);

    // Approach 2: Huffman Coding with Optimized Frequency Calculation
    huffmanCodingOptimizedFrequency(text);

    // Approach 3: Huffman Coding with Iterative Code Generation
    huffmanCodingIterativeCodeGeneration(text);

    // Approach 4: Huffman Coding with Pre-calculated Frequencies
    std::map<char, unsigned> frequencyMap = calculateFrequency(text);
    huffmanCodingWithFrequencies(text, frequencyMap);

     // Approach 5: Huffman Coding with Custom Comparison Function
    huffmanCodingCustomComparison(text);
    return 0;
}

