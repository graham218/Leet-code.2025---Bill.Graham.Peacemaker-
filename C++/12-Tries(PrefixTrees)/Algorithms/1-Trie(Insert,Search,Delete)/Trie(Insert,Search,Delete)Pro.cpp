#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <variant>
#include <optional> // Include for std::optional
// Approach 1: Basic Trie with Raw Pointers (Educational Example)
// -   Simplest implementation for understanding the core concept.
// -   Good for small, static datasets where memory management is not critical.
// -   NOT recommended for production due to manual memory management.
struct TrieNodeBasic {
    static const int ALPHABET_SIZE = 26;
    TrieNodeBasic* children[ALPHABET_SIZE];
    bool isEndOfWord;
    TrieNodeBasic() {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            children[i] = nullptr;
        }
        isEndOfWord = false;
    }
    ~TrieNodeBasic() {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (children[i]) {
                delete children[i];
                children[i] = nullptr; // Prevent double deletion
            }
        }
    }
};
class TrieBasic {
private:
    TrieNodeBasic* root;
public:
    TrieBasic() {
        root = new TrieNodeBasic();
    }
    ~TrieBasic() {
        delete root;
    }
    void insert(const std::string& word) {
        TrieNodeBasic* current = root;
        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index]) {
                current->children[index] = new TrieNodeBasic();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }
    bool search(const std::string& word) {
        TrieNodeBasic* current = root;
        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index];
        }
        return current->isEndOfWord;
    }
    // Delete operation (iterative version)
    void deleteWord(const std::string& word) {
        if (!search(word))
            return; // Word not in trie
        std::vector<TrieNodeBasic*> path;
        TrieNodeBasic* current = root;
        for (char c : word) {
            int index = c - 'a';
            path.push_back(current);
            current = current->children[index];
        }
        path.push_back(current); // Add the end node
        current->isEndOfWord = false; // Mark the end of the word as not end.
        //Iterate from the end of the word, and delete nodes if they have no children and are not the end of another word.
        for (int i = word.size(); i > 0; --i) {
            TrieNodeBasic* node = path[i];
            TrieNodeBasic* parent = path[i - 1];
            int index = word[i - 1] - 'a';
            // If the current node has children, or is the end of another word, stop deleting.
            bool hasChildren = false;
            for (int j = 0; j < TrieNodeBasic::ALPHABET_SIZE; ++j) {
                if (node->children[j]) {
                    hasChildren = true;
                    break;
                }
            }
            if (hasChildren || node->isEndOfWord) {
                break;
            }
            // Delete the node and update the parent
            delete node;
            parent->children[index] = nullptr;
        }
    }
};
// ----------------------------------------------------------------------------------------------------
// Approach 2: Trie with Smart Pointers (Modern C++)
// -   Uses std::unique_ptr for automatic memory management.
// -   Safer and more robust than raw pointers.
// -   Recommended for most applications.
struct TrieNodeSmart {
    static const int ALPHABET_SIZE = 26;
    std::unique_ptr<TrieNodeSmart> children[ALPHABET_SIZE];
    bool isEndOfWord;
    TrieNodeSmart() : isEndOfWord(false) {}
};
class TrieSmart {
private:
    std::unique_ptr<TrieNodeSmart> root;
public:
    TrieSmart() : root(std::make_unique<TrieNodeSmart>()) {}
    void insert(const std::string& word) {
        TrieNodeSmart* current = root.get(); // Use get() to get raw pointer
        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index]) {
                current->children[index] = std::make_unique<TrieNodeSmart>();
            }
            current = current->children[index].get();
        }
        current->isEndOfWord = true;
    }
    bool search(const std::string& word) {
        const TrieNodeSmart* current = root.get();
        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index].get();
        }
        return current->isEndOfWord;
    }
    void deleteWord(const std::string& word) {
        if (!search(word))
            return;
        std::vector<TrieNodeSmart*> path;
        TrieNodeSmart* current = root.get();
        for (char c : word) {
            int index = c - 'a';
            path.push_back(current);
            current = current->children[index].get();
        }
        path.push_back(current);
        current->isEndOfWord = false;
        for (int i = word.size(); i > 0; --i) {
            TrieNodeSmart* node = path[i];
            TrieNodeSmart* parent = path[i - 1];
            int index = word[i - 1] - 'a';
            bool hasChildren = false;
            for (int j = 0; j < TrieNodeSmart::ALPHABET_SIZE; ++j) {
                if (node->children[j]) {
                    hasChildren = true;
                    break;
                }
            }
            if (hasChildren || node->isEndOfWord) {
                break;
            }
            parent->children[index].reset(); // Release the unique_ptr
        }
    }
};
// ----------------------------------------------------------------------------------------------------
// Approach 3: Trie with a Map for Children (Space Optimization)
// -   Uses std::map to store children, saving space for sparse tries.
// -   Good for languages with large alphabets or when many words have few common prefixes.
// -   Slightly slower insertion/search than array-based tries due to map lookups.
struct TrieNodeMap {
    std::map<char, std::unique_ptr<TrieNodeMap>> children;
    bool isEndOfWord;
    TrieNodeMap() : isEndOfWord(false) {}
};
class TrieMap {
private:
    std::unique_ptr<TrieNodeMap> root;
public:
    TrieMap() : root(std::make_unique<TrieNodeMap>()) {}
    void insert(const std::string& word) {
        TrieNodeMap* current = root.get();
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = std::make_unique<TrieNodeMap>();
            }
            current = current->children[c].get();
        }
        current->isEndOfWord = true;
    }
    bool search(const std::string& word) {
        const TrieNodeMap* current = root.get();
        for (char c : word) {
            auto it = current->children.find(c);
            if (it == current->children.end()) {
                return false;
            }
            current = it->second.get();
        }
        return current->isEndOfWord;
    }
    void deleteWord(const std::string& word) {
        if (!search(word))
            return;
        std::vector<TrieNodeMap*> path;
        TrieNodeMap* current = root.get();
        for (char c : word) {
            path.push_back(current);
            current = current->children[c].get();
        }
        path.push_back(current);
        current->isEndOfWord = false;
        for (int i = word.size(); i > 0; --i) {
            TrieNodeMap* node = path[i];
            TrieNodeMap* parent = path[i - 1];
            char c = word[i - 1];
            bool hasChildren = (node->children.size() > 0);
            if (hasChildren || node->isEndOfWord) {
                break;
            }
            parent->children.erase(c);
        }
    }
};
// ----------------------------------------------------------------------------------------------------
// Approach 4: Trie with a Compressed Path (Space Optimization for Long Common Prefixes)
// -   Compresses paths with single children into a single node, reducing space.
// -   Good for dictionaries with many words sharing long prefixes.
// -   More complex to implement.
struct TrieNodeCompressed {
    std::string prefix;
    std::map<char, std::unique_ptr<TrieNodeCompressed>> children;
    bool isEndOfWord;
    TrieNodeCompressed(const std::string& p = "") : prefix(p), isEndOfWord(false) {}
};
class TrieCompressed {
private:
    std::unique_ptr<TrieNodeCompressed> root;
public:
    TrieCompressed() : root(std::make_unique<TrieNodeCompressed>()) {}
    void insert(const std::string& word) {
        TrieNodeCompressed* current = root.get();
        int i = 0;
        while (i < word.size()) {
            // Check for prefix match
            if (!current->prefix.empty()) {
                int matchLen = 0;
                while (matchLen < current->prefix.size() && i + matchLen < word.size() &&
                       current->prefix[matchLen] == word[i + matchLen]) {
                    ++matchLen;
                }
                if (matchLen == current->prefix.size()) {
                    // Full prefix match, continue to children
                    i += matchLen;
                } else {
                    // Partial match, split the node
                    std::string commonPrefix = current->prefix.substr(0, matchLen);
                    std::string existingSuffix = current->prefix.substr(matchLen);
                    std::string newSuffix = word.substr(i + matchLen);
                    // Create new nodes
                    std::unique_ptr<TrieNodeCompressed> newNode = std::make_unique<TrieNodeCompressed>(commonPrefix);
                    std::unique_ptr<TrieNodeCompressed> existingChild = std::make_unique<TrieNodeCompressed>(existingSuffix);
                    existingChild->isEndOfWord = current->isEndOfWord; // Preserve isEndOfWord
                    for (auto& child : current->children) {
                        existingChild->children = std::move(child.second->children);
                    }
                    newNode->children[existingSuffix[0]] = std::move(existingChild);
                    if (!newSuffix.empty()) {
                        newNode->children[newSuffix[0]] = std::make_unique<TrieNodeCompressed>(newSuffix);
                    } else {
                        newNode->isEndOfWord = true;
                    }
                    current->prefix = commonPrefix;
                    current->isEndOfWord = false; // The current node is no longer an end of word.
                    current->children.clear();
                    current->children[existingSuffix[0]] = std::move(newNode->children[existingSuffix[0]]);
                    if (!newSuffix.empty()) {
                        current->children[newSuffix[0]] = std::move(newNode->children[newSuffix[0]]);
                    }
                    current->children[existingSuffix[0]]->isEndOfWord = (newSuffix.empty());
                    return;
                }
            } else {
                // No prefix, create child
                char c = word[i];
                if (current->children.find(c) == current->children.end()) {
                    current->children[c] = std::make_unique<TrieNodeCompressed>(word.substr(i));
                    current->children[c]->isEndOfWord = true;
                    return;
                }
                current = current->children[c].get();
                i += current->prefix.size();
            }
        }
        current->isEndOfWord = true;
    }
    bool search(const std::string& word) {
        const TrieNodeCompressed* current = root.get();
        int i = 0;
        while (i < word.size()) {
            if (current->prefix.empty()) {
                if (i >= word.size())
                    return current->isEndOfWord;
                char c = word[i];
                auto it = current->children.find(c);
                if (it == current->children.end()) {
                    return false;
                }
                current = it->second.get();
                i++;
            } else {
                if (i + current->prefix.size() > word.size())
                    return false;
                if (word.substr(i, current->prefix.size()) != current->prefix) {
                    return false;
                }
                i += current->prefix.size();
                if (i == word.size())
                    return current->isEndOfWord;
                char nextChar = word[i];
                auto it = current->children.find(nextChar);
                if (it == current->children.end()) {
                    return false;
                }
                current = it->second.get();
            }
        }
        return current->isEndOfWord;
    }
    void deleteWord(const std::string& word) {
        if (!search(word))
            return;
        std::vector<std::pair<TrieNodeCompressed*, char>> path; // Store node and char to reach it
        TrieNodeCompressed* current = root.get();
        int i = 0;
        while (i < word.size()) {
            if (!current->prefix.empty()) {
                i += current->prefix.size();
                if (i < word.size()) {
                    char nextChar = word[i];
                    path.push_back({current, nextChar});
                    current = current->children[nextChar].get();
                }
            } else {
                char nextChar = word[i];
                path.push_back({current, nextChar});
                current = current->children[nextChar].get();
                i++;
            }
        }
        current->isEndOfWord = false;
        for (int j = path.size() - 1; j >= 0; --j) {
            TrieNodeCompressed* node = path[j].first;
            char edgeChar = path[j].second;
            if (node->children.size() > 1 || node->isEndOfWord) {
                break;
            } else if (node->children.size() == 1) {
                auto it = node->children.begin();
                if (it->second->children.empty() && !it->second->isEndOfWord) {
                    node->children.erase(it->first);
                } else {
                    break;
                }
            } else {
                node->children.erase(edgeChar);
            }
        }
    }
};
// ----------------------------------------------------------------------------------------------------
// Approach 5: Trie with a Hash Map and Value Storage (Key-Value Store)
// -   Uses a hash map (std::unordered_map) for children and stores a value with each word.
// -   Suitable for implementing a dictionary or key-value store using a trie.
// -   Provides efficient insertion, search, and retrieval of values associated with keys.
// Use std::variant to store different types of values (C++17 and later)
using ValueType = std::variant<int, std::string, double>; // Example: store int, string, or double
struct TrieNodeValue {
    std::unordered_map<char, std::unique_ptr<TrieNodeValue>> children;
    bool isEndOfWord;
    std::optional<ValueType> value; // Use std::optional to indicate presence or absence of a value
    TrieNodeValue() : isEndOfWord(false), value(std::nullopt) {}
};
class TrieValue {
private:
    std::unique_ptr<TrieNodeValue> root;
public:
    TrieValue() : root(std::make_unique<TrieNodeValue>()) {}
    // Insert a key-value pair into the trie
    void insert(const std::string& key, const ValueType& val) {
        TrieNodeValue* current = root.get();
        for (char c : key) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = std::make_unique<TrieNodeValue>();
            }
            current = current->children[c].get();
        }
        current->isEndOfWord = true;
        current->value = val; // Store the value
    }
    // Search for a key and retrieve its associated value
    std::optional<ValueType> search(const std::string& key) {
        const TrieNodeValue* current = root.get();
        for (char c : key) {
            auto it = current->children.find(c);
            if (it == current->children.end()) {
                return std::nullopt; // Key not found
            }
            current = it->second.get();
        }
        if (current->isEndOfWord) {
            return current->value; // Return the value if the key is found
        }
        return std::nullopt; // Key is a prefix, but not a complete word
    }
    // Delete a key-value pair
    void deleteWord(const std::string& key) {
        std::optional<ValueType> searchValue = search(key);
        if (!searchValue.has_value())
            return;
        std::vector<TrieNodeValue*> path;
        TrieNodeValue* current = root.get();
        for (char c : key) {
            path.push_back(current);
            current = current->children[c].get();
        }
        path.push_back(current);
        current->isEndOfWord = false;
        current->value = std::nullopt; // Remove value.
        for (int i = key.size(); i > 0; --i) {
            TrieNodeValue* node = path[i];
            TrieNodeValue* parent = path[i - 1];
            char c = key[i - 1];
            bool hasChildren = (node->children.size() > 0);
            if (hasChildren || node->isEndOfWord) {
                break;
            }
            parent->children.erase(c);
        }
    }
};
// ----------------------------------------------------------------------------------------------------
int main() {
    // Example Usage (Uncomment to run)
    // Approach 1: Basic Trie
    std::cout << "\n--- Basic Trie Example ---" << std::endl;
    TrieBasic trieBasic;
    trieBasic.insert("apple");
    trieBasic.insert("banana");
    trieBasic.insert("app");
    std::cout << "Search 'apple': " << (trieBasic.search("apple") ? "true" : "false") << std::endl; // Output: true
    std::cout << "Search 'app': " << (trieBasic.search("app") ? "true" : "false") << std::endl;     // Output: true
    std::cout << "Search 'banana': " << (trieBasic.search("banana") ? "true" : "false") << std::endl;
    std::cout << "Search 'orange': " << (trieBasic.search("orange") ? "true" : "false") << std::endl; // Output: false
    trieBasic.deleteWord("apple");
    std::cout << "Search 'apple' after deletion: " << (trieBasic.search("apple") ? "true" : "false") << std::endl; //false
    std::cout << "Search 'app' after deleting apple: " << (trieBasic.search("app") ? "true" : "false") << std::endl;
    // Approach 2: Smart Pointer Trie
    std::cout << "\n--- Smart Pointer Trie Example ---" << std::endl;
    TrieSmart trieSmart;
    trieSmart.insert("apple");
    trieSmart.insert("banana");
    trieSmart.insert("app");
    std::cout << "Search 'apple': " << (trieSmart.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app': " << (trieSmart.search("app") ? "true" : "false") << std::endl;
    std::cout << "Search 'orange': " << (trieSmart.search("orange") ? "true" : "false") << std::endl;
    trieSmart.deleteWord("apple");
    std::cout << "Search 'apple' after deletion: " << (trieSmart.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app' after deleting apple: " << (trieSmart.search("app") ? "true" : "false") << std::endl;
    // Approach 3: Map-based Trie
    std::cout << "\n--- Map-based Trie Example ---" << std::endl;
    TrieMap trieMap;
    trieMap.insert("apple");
    trieMap.insert("banana");
    trieMap.insert("app");
    std::cout << "Search 'apple': " << (trieMap.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app': " << (trieMap.search("app") ? "true" : "false") << std::endl;
    std::cout << "Search 'orange': " << (trieMap.search("orange") ? "true" : "false") << std::endl;
    trieMap.deleteWord("apple");
    std::cout << "Search 'apple' after deletion: " << (trieMap.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app' after deleting apple: " << (trieMap.search("app") ? "true" : "false") << std::endl;
    // Approach 4: Compressed Trie
    std::cout << "\n--- Compressed Trie Example ---" << std::endl;
    TrieCompressed trieCompressed;
    trieCompressed.insert("apple");
    trieCompressed.insert("application");
    trieCompressed.insert("app");
    trieCompressed.insert("banana");
    trieCompressed.insert("ban");
    std::cout << "Search 'apple': " << (trieCompressed.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'application': " << (trieCompressed.search("application") ? "true" : "false") << std::endl;
    std::cout << "Search 'app': " << (trieCompressed.search("app") ? "true" : "false") << std::endl;
    std::cout << "Search 'banana': " << (trieCompressed.search("banana") ? "true" : "false") << std::endl;
    std::cout << "Search 'ban': " << (trieCompressed.search("ban") ? "true" : "false") << std::endl;
    std::cout << "Search 'orange': " << (trieCompressed.search("orange") ? "true" : "false") << std::endl;
    trieCompressed.deleteWord("apple");
    std::cout << "Search 'apple' after deletion: " << (trieCompressed.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app' after deleting apple: " << (trieCompressed.search("app") ? "true" : "false") << std::endl;
    std::cout << "Search 'application' after deleting apple: " << (trieCompressed.search("application") ? "true" : "false") << std::endl;
    // Approach 5: Trie with Value Storage
    std::cout << "\n--- Trie with Value Storage Example ---" << std::endl;
    TrieValue trieValue;
    trieValue.insert("apple", 1);
    trieValue.insert("banana", "yellow");
    trieValue.insert("orange", 3.14);
    std::optional<ValueType> appleValue = trieValue.search("apple");
    if (appleValue.has_value()) {
        std::cout << "Value of 'apple': " << std::get<int>(*appleValue) << std::endl; // Output: 1
    }
    std::optional<ValueType> bananaValue = trieValue.search("banana");
    if (bananaValue.has_value()) {
        std::cout << "Value of 'banana': " << std::get<std::string>(*bananaValue) << std::endl; // Output: yellow
    }
    std::optional<ValueType> orangeValue = trieValue.search("orange");
    if (orangeValue.has_value()) {
        std::cout << "Value of 'orange': " << std::get<double>(*orangeValue) << std::endl; // Output: 3.14
    }
    std::optional<ValueType> nonExistentValue = trieValue.search("grape");
    if (!nonExistentValue.has_value()) {
        std::cout << "Value of 'grape': Not found" << std::endl;
    }
    trieValue.deleteWord("banana");
    bananaValue = trieValue.search("banana");
    if (!bananaValue.has_value()) {
        std::cout << "Value of 'banana' after deletion: Not found" << std::endl;
    }
    return 0;
}

