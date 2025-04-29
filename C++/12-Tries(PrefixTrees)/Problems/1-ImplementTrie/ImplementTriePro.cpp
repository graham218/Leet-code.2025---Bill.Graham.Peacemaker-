#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <queue>

// Approach 1: Basic Trie Implementation with Array
// - Uses a fixed-size array for children, assuming a limited character set (e.g., lowercase English letters).
// - Simple and efficient for small, known character sets.
// - Not suitable for large or Unicode character sets due to memory usage.
class TrieNode1 {
public:
    static const int ALPHABET_SIZE = 26; // For lowercase English letters
    TrieNode1* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode1() {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            children[i] = nullptr;
        }
        isEndOfWord = false;
    }

    ~TrieNode1() {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            delete children[i]; // Corrected: Recursively delete children
            children[i] = nullptr; // Prevent dangling pointers
        }
    }
};

class Trie1 {
private:
    TrieNode1* root;

public:
    Trie1() {
        root = new TrieNode1();
    }

    ~Trie1() {
        delete root; // Corrected:  Use the destructor to clean up.
        root = nullptr;
    }

    void insert(const std::string& word) {
        TrieNode1* current = root;
        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index]) {
                current->children[index] = new TrieNode1();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }

    bool search(const std::string& word) {
        TrieNode1* current = root;
        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index];
        }
        return current != nullptr && current->isEndOfWord; // Corrected: Check for nullptr
    }

    bool startsWith(const std::string& prefix) {
        TrieNode1* current = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index];
        }
        return current != nullptr; // Corrected: Return true if the prefix exists
    }
};

// Approach 2: Trie with Dynamic Allocation and Smart Pointers
// - Uses dynamic allocation for children, allowing for flexibility in character sets.
// - Uses smart pointers (unique_ptr) to manage memory automatically, preventing memory leaks.
// - More robust and safer than the basic array approach.
class TrieNode2 {
public:
    std::unordered_map<char, std::unique_ptr<TrieNode2>> children;
    bool isEndOfWord;

    TrieNode2() : isEndOfWord(false) {}
};

class Trie2 {
private:
    TrieNode2* root;

public:
    Trie2() {
        root = new TrieNode2();
    }

    ~Trie2() {
        delete root;
    }

    void insert(const std::string& word) {
        TrieNode2* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = std::make_unique<TrieNode2>();
            }
            current = current->children[c].get();
        }
        current->isEndOfWord = true;
    }

    bool search(const std::string& word) {
        TrieNode2* current = root;
        for (char c : word) {
            auto it = current->children.find(c);
            if (it == current->children.end()) {
                return false;
            }
            current = it->second.get();
        }
        return current != nullptr && current->isEndOfWord;
    }

    bool startsWith(const std::string& prefix) {
        TrieNode2* current = root;
        for (char c : prefix) {
            auto it = current->children.find(c);
            if (it == current->children.end()) {
                return false;
            }
            current = it->second.get();
        }
        return current != nullptr;
    }
};

// Approach 3: Trie with Compressed Paths (Radix Trie)
// - Optimizes space by merging nodes with single children into a single edge.
// - Useful for dictionaries with many words sharing common prefixes.
// - More complex to implement but saves memory.

class TrieNode3 {
public:
    std::unordered_map<char, std::unique_ptr<TrieNode3>> children;
    bool isEndOfWord;
    std::string path; // Store the compressed path string

    TrieNode3() : isEndOfWord(false), path("") {}
};

class Trie3 {
private:
    TrieNode3* root;

public:
    Trie3() {
        root = new TrieNode3();
    }
     ~Trie3() {
        delete root;
    }

    void insert(const std::string& word) {
        TrieNode3* current = root;
        int i = 0;
        while (i < word.length()) {
            char c = word[i];
            if (current->children.find(c) == current->children.end()) {
                // No existing path, create a new node for the remaining part of the word
                std::string remainingPath = word.substr(i);
                current->children[c] = std::make_unique<TrieNode3>();
                current->children[c]->path = remainingPath;
                current = current->children[c].get();
                i = word.length(); // Exit the loop
            } else {
                current = current->children[c].get();
                std::string& commonPath = current->path;
                int j = 0;
                while (j < commonPath.length() && i < word.length() && commonPath[j] == word[i]) {
                    ++j;
                    ++i;
                }
                if (j < commonPath.length()) {
                    // Split the edge
                    std::string newPath = commonPath.substr(j);
                    std::string prefix = commonPath.substr(0, j);

                    // Create a new node for the common prefix
                    auto newNode = std::make_unique<TrieNode3>();
                    newNode->path = prefix;
                    newNode->isEndOfWord = false; // Important:  prefix is not end of word.

                    // Adjust current node
                    current->path = newPath;

                    // Move the child to the new node
                    newNode->children[newPath[0]] = std::move(current->children[c]);
                    current->children[c] = std::move(newNode); // point the parent to the new node.
                    current = current->children[c].get(); // Move current to the new node
                }
                else if (j == commonPath.length() && i == word.length())
                {
                     current->isEndOfWord = true;
                     break;
                }
            }
        }
        current->isEndOfWord = true;
    }

    bool search(const std::string& word) {
        TrieNode3* current = root;
        int i = 0;
        while (current != nullptr && i < word.length()) {
            char c = word[i];
            auto it = current->children.find(c);
            if (it == current->children.end()) {
                return false;
            }
            current = it->second.get();
            std::string& commonPath = current->path;
            int j = 0;
            while (j < commonPath.length() && i < word.length() && commonPath[j] == word[i]) {
                ++j;
                ++i;
            }
            if (j != commonPath.length()) {
                return false;
            }
        }
        return current != nullptr && current->isEndOfWord;
    }

    bool startsWith(const std::string& prefix) {
        TrieNode3* current = root;
        int i = 0;
        while (current != nullptr && i < prefix.length()) {
            char c = prefix[i];
            auto it = current->children.find(c);
            if (it == current->children.end()) {
                return false;
            }
            current = it->second.get();
            std::string& commonPath = current->path;
            int j = 0;
            while (j < commonPath.length() && i < prefix.length() && commonPath[j] == prefix[i]) {
                ++j;
                ++i;
            }
            if (j != commonPath.length()) {
                return false;
            }
        }
        return current != nullptr;
    }
};

// Approach 4: Trie with a Ternary Search Tree (TST)
// - Uses a balanced ternary search tree for each node, offering a compromise between space and search efficiency.
// - Efficient for lookups, especially with a large number of words.
// - More complex than a standard trie but can be more space-efficient.

class TrieNode4 {
public:
    char data;
    TrieNode4* left, * mid, * right;
    bool isEndOfWord;

    TrieNode4(char data) : data(data), left(nullptr), mid(nullptr), right(nullptr), isEndOfWord(false) {}
    ~TrieNode4()
    {
        delete left;
        delete mid;
        delete right;
    }
};

class Trie4 {
private:
    TrieNode4* root;

    TrieNode4* insert(TrieNode4* node, const std::string& word, int index) {
        if (!node) {
            node = new TrieNode4(word[index]);
        }

        if (word[index] < node->data) {
            node->left = insert(node->left, word, index);
        } else if (word[index] > node->data) {
            node->right = insert(node->right, word, index);
        } else {
            if (index + 1 == word.length()) {
                node->isEndOfWord = true;
            } else {
                node->mid = insert(node->mid, word, index + 1);
            }
        }
        return node;
    }

    bool search(TrieNode4* node, const std::string& word, int index) {
        if (!node) {
            return false;
        }

        if (word[index] < node->data) {
            return search(node->left, word, index);
        } else if (word[index] > node->data) {
            return search(node->right, word, index);
        } else {
            if (index + 1 == word.length()) {
                return node->isEndOfWord;
            } else {
                return search(node->mid, word, index + 1);
            }
        }
    }
     bool startsWith(TrieNode4* node, const std::string& word, int index) {
        if (!node) {
            return false;
        }

        if (word[index] < node->data) {
            return startsWith(node->left, word, index);
        } else if (word[index] > node->data) {
            return startsWith(node->right, word, index);
        } else {
            if (index + 1 == word.length()) {
                return true; // Found the prefix
            } else {
                return startsWith(node->mid, word, index + 1);
            }
        }
    }

public:
    Trie4() : root(nullptr) {}
     ~Trie4() {
        delete root;
    }

    void insert(const std::string& word) {
        root = insert(root, word, 0);
    }

    bool search(const std::string& word) {
        return search(root, word, 0);
    }

    bool startsWith(const std::string& prefix) {
       return startsWith(root, prefix, 0);
    }
};

// Approach 5: Trie with a Hash Table for Children
// - Uses a hash table (unordered_map) to store children.
// - Provides efficient insertion and search operations.
// - Suitable for large character sets and dynamic data.
class TrieNode5 {
public:
    std::unordered_map<char, TrieNode5*> children;
    bool isEndOfWord;

    TrieNode5() : isEndOfWord(false) {}
    ~TrieNode5() {
        for (auto const& [key, val] : children) {
            delete val;
        }
    }
};

class Trie5 {
private:
    TrieNode5* root;

public:
    Trie5() {
        root = new TrieNode5();
    }
     ~Trie5() {
        delete root;
    }

    void insert(const std::string& word) {
        TrieNode5* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode5();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }

    bool search(const std::string& word) {
        TrieNode5* current = root;
        for (char c : word) {
            auto it = current->children.find(c);
            if (it == current->children.end()) {
                return false;
            }
            current = it->second;
        }
        return current != nullptr && current->isEndOfWord;
    }

    bool startsWith(const std::string& prefix) {
        TrieNode5* current = root;
        for (char c : prefix) {
            auto it = current->children.find(c);
            if (it == current->children.end()) {
                return false;
            }
            current = it->second;
        }
        return current != nullptr;
    }
};

int main() {
    // Example Usage
    std::cout << "--- Trie 1: Basic Array Implementation ---" << std::endl;
    Trie1 trie1;
    trie1.insert("apple");
    trie1.insert("app");
    std::cout << "search(\"apple\"): " << (trie1.search("apple") ? "true" : "false") << std::endl;
    std::cout << "search(\"app\"): " << (trie1.search("app") ? "true" : "false") << std::endl;
    std::cout << "search(\"banana\"): " << (trie1.search("banana") ? "true" : "false") << std::endl;
    std::cout << "startsWith(\"app\"): " << (trie1.startsWith("app") ? "true" : "false") << std::endl;

    std::cout << "\n--- Trie 2: Dynamic Allocation with Smart Pointers ---" << std::endl;
    Trie2 trie2;
    trie2.insert("apple");
    trie2.insert("app");
    std::cout << "search(\"apple\"): " << (trie2.search("apple") ? "true" : "false") << std::endl;
    std::cout << "search(\"app\"): " << (trie2.search("app") ? "true" : "false") << std::endl;
    std::cout << "search(\"banana\"): " << (trie2.search("banana") ? "true" : "false") << std::endl;
     std::cout << "startsWith(\"app\"): " << (trie2.startsWith("app") ? "true" : "false") << std::endl;

    std::cout << "\n--- Trie 3: Radix Trie (Compressed Paths) ---" << std::endl;
    Trie3 trie3;
    trie3.insert("apple");
    trie3.insert("app");
    trie3.insert("application");
    trie3.insert("ap");
    std::cout << "search(\"apple\"): " << (trie3.search("apple") ? "true" : "false") << std::endl;
    std::cout << "search(\"app\"): " << (trie3.search("app") ? "true" : "false") << std::endl;
    std::cout << "search(\"application\"): " << (trie3.search("application") ? "true" : "false") << std::endl;
    std::cout << "search(\"ap\"): " << (trie3.search("ap") ? "true" : "false") << std::endl;
    std::cout << "search(\"banana\"): " << (trie3.search("banana") ? "true" : "false") << std::endl;
    std::cout << "startsWith(\"app\"): " << (trie3.startsWith("app") ? "true" : "false") << std::endl;
    std::cout << "startsWith(\"ap\"): " << (trie3.startsWith("ap") ? "true" : "false") << std::endl;
    std::cout << "startsWith(\"appl\"): " << (trie3.startsWith("appl") ? "true" : "false") << std::endl;

    std::cout << "\n--- Trie 4: Ternary Search Tree ---" << std::endl;
    Trie4 trie4;
    trie4.insert("apple");
    trie4.insert("app");
    trie4.insert("application");
    trie4.insert("ap");
    std::cout << "search(\"apple\"): " << (trie4.search("apple") ? "true" : "false") << std::endl;
    std::cout << "search(\"app\"): " << (trie4.search("app") ? "true" : "false") << std::endl;
    std::cout << "search(\"application\"): " << (trie4.search("application") ? "true" : "false") << std::endl;
    std::cout << "search(\"ap\"): " << (trie4.search("ap") ? "true" : "false") << std::endl;
    std::cout << "search(\"banana\"): " << (trie4.search("banana") ? "true" : "false") << std::endl;
    std::cout << "startsWith(\"app\"): " << (trie4.startsWith("app") ? "true" : "false") << std::endl;
     std::cout << "startsWith(\"ap\"): " << (trie4.startsWith("ap") ? "true" : "false") << std::endl;
    std::cout << "startsWith(\"appl\"): " << (trie4.startsWith("appl") ? "true" : "false") << std::endl;

    std::cout << "\n--- Trie 5: Hash Table for Children ---" << std::endl;
    Trie5 trie5;
    trie5.insert("apple");
    trie5.insert("app");
    std::cout << "search(\"apple\"): " << (trie5.search("apple") ? "true" : "false") << std::endl;
    std::cout << "search(\"app\"): " << (trie5.search("app") ? "true" : "false") << std::endl;
    std::cout << "search(\"banana\"): " << (trie5.search("banana") ? "true" : "false") << std::endl;
    std::cout << "startsWith(\"app\"): " << (trie5.startsWith("app") ? "true" : "false") << std::endl;

    return 0;
}
