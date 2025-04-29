#include <iostream>
#include <string>
#include <vector>
#include <memory> // For smart pointers
#include <algorithm> // For std::remove_if

// Approach 1: Basic Trie with Raw Pointers
// - Uses raw pointers for node management.
// - Requires manual memory management (allocation and deallocation).
// - Prone to memory leaks if not handled carefully.
class TrieNode1 {
public:
    static const int ALPHABET_SIZE = 26;
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
            delete children[i]; // Corrected: Use delete for raw pointers
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
        delete root; // Corrected: Use delete for raw pointers
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
        return current->isEndOfWord;
    }

    // Delete operation - Iterative Approach
    void deleteWord(const std::string& word) {
        if (!search(word)) return; // Word not present

        std::vector<TrieNode1*> path;
        TrieNode1* current = root;
        for (char c : word) {
            int index = c - 'a';
            path.push_back(current);
            current = current->children[index];
        }
        path.push_back(current); // Add the last node (end of word)

        // 1. Mark the end of the word as not end of word.
        current->isEndOfWord = false;

        // 2. Iterate from the end of the word, and delete nodes if they have no children and are not the end of another word.
        for (int i = word.size(); i > 0; --i) {
            current = path[i];
            int index = word[i - 1] - 'a';
            if (hasNoChildren(current->children[index]) && !current->children[index]->isEndOfWord) {
                delete current->children[index];
                current->children[index] = nullptr;
            } else {
                break; // Stop deleting when a node has children or is the end of a word
            }
        }
    }

    bool hasNoChildren(TrieNode1* node) {
        if (!node) return true;
        for (int i = 0; i < TrieNode1::ALPHABET_SIZE; ++i) {
            if (node->children[i]) return false;
        }
        return true;
    }
};

// Approach 2: Trie with Unique Pointers
// - Uses std::unique_ptr for automatic memory management.
// - Prevents issues with manual memory deallocation.
// - Only one unique_ptr can point to an object at a time.
class TrieNode2 {
public:
    static const int ALPHABET_SIZE = 26;
    std::unique_ptr<TrieNode2> children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode2() : isEndOfWord(false) {}
};

class Trie2 {
private:
    std::unique_ptr<TrieNode2> root;

public:
    Trie2() : root(std::make_unique<TrieNode2>()) {}

    void insert(const std::string& word) {
        TrieNode2* current = root.get(); // Use get() to get the raw pointer
        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index]) {
                current->children[index] = std::make_unique<TrieNode2>();
            }
            current = current->children[index].get(); // Use get()
        }
        current->isEndOfWord = true;
    }

    bool search(const std::string& word) {
        TrieNode2* current = root.get(); // Use get()
        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index].get(); // Use get()
        }
        return current->isEndOfWord;
    }

    // Delete operation - Recursive Approach
    void deleteWord(const std::string& word) {
        deleteWordHelper(root.get(), word, 0);
    }

private:
    bool deleteWordHelper(TrieNode2* node, const std::string& word, int index) {
        if (!node) return false;

        if (index == word.size()) {
            if (node->isEndOfWord) {
                node->isEndOfWord = false;
                return hasNoChildren(node); // Return true if node has no children
            }
            return false;
        }

        int charIndex = word[index] - 'a';
        if (deleteWordHelper(node->children[charIndex].get(), word, index + 1)) { // Use get()
            node->children[charIndex] = nullptr; // Reset the unique_ptr
            return !node->isEndOfWord && hasNoChildren(node);
        }
        return false;
    }

    bool hasNoChildren(TrieNode2* node) {
        if (!node) return true;
        for (int i = 0; i < TrieNode2::ALPHABET_SIZE; ++i) {
            if (node->children[i]) return false;
        }
        return true;
    }
};

// Approach 3: Trie with Shared Pointers
// - Uses std::shared_ptr for shared ownership of nodes.
// - Multiple shared_ptrs can point to the same object.
// - Uses a custom deleter to avoid double deletion issues.
class TrieNode3 {
public:
    static const int ALPHABET_SIZE = 26;
    std::shared_ptr<TrieNode3> children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode3() : isEndOfWord(false) {}
};

class Trie3 {
private:
    std::shared_ptr<TrieNode3> root;

public:
    Trie3() : root(std::make_shared<TrieNode3>()) {}

    void insert(const std::string& word) {
        std::shared_ptr<TrieNode3> current = root;
        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index]) {
                current->children[index] = std::make_shared<TrieNode3>();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }

    bool search(const std::string& word) {
        std::shared_ptr<TrieNode3> current = root;
        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index];
        }
        return current->isEndOfWord;
    }

    // Delete operation - Modified Iterative
    void deleteWord(const std::string& word) {
        if (!search(word)) return;

        std::vector<std::shared_ptr<TrieNode3>> path;
        std::shared_ptr<TrieNode3> current = root;
        for(char c : word){
            int index = c - 'a';
            path.push_back(current);
            current = current->children[index];
        }
        path.push_back(current);
        current->isEndOfWord = false;

        for(int i = word.size(); i > 0; --i){
            current = path[i];
            int index = word[i-1] - 'a';
            if(hasNoChildren(current->children[index]) && !current->children[index]->isEndOfWord){
                current->children[index] = nullptr;
            }
            else{
                break;
            }
        }
    }

    bool hasNoChildren(const std::shared_ptr<TrieNode3>& node) {
        if (!node) return true;
        for (int i = 0; i < TrieNode3::ALPHABET_SIZE; ++i) {
            if (node->children[i]) return false;
        }
        return true;
    }
};

// Approach 4: Trie with a fixed-size array and manual memory management
// This approach is similar to Approach 1, but uses a fixed-size array instead of a dynamically allocated array for children.
// This can be more memory-efficient if the alphabet size is known and relatively small.
class TrieNode4 {
public:
    static const int ALPHABET_SIZE = 26;
    TrieNode4* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode4() : isEndOfWord(false) {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            children[i] = nullptr;
        }
    }

     ~TrieNode4() {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            delete children[i];
        }
    }
};

class Trie4 {
private:
    TrieNode4* root;

public:
    Trie4() : root(new TrieNode4()) {}

    ~Trie4(){
        delete root;
    }

    void insert(const std::string& word) {
        TrieNode4* current = root;
        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index]) {
                current->children[index] = new TrieNode4();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }

    bool search(const std::string& word) {
        TrieNode4* current = root;
        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index];
        }
        return current->isEndOfWord;
    }

    // Delete operation for Approach 4
    void deleteWord(const std::string& word) {
       if (!search(word)) return;

        std::vector<TrieNode4*> path;
        TrieNode4* current = root;
        for (char c : word) {
            int index = c - 'a';
            path.push_back(current);
            current = current->children[index];
        }
        path.push_back(current);
        current->isEndOfWord = false;

        for (int i = word.size(); i > 0; --i) {
            current = path[i];
            int index = word[i - 1] - 'a';
            if (hasNoChildren(current->children[index]) && !current->children[index]->isEndOfWord) {
                delete current->children[index];
                current->children[index] = nullptr;
            } else {
                break;
            }
        }
    }

    bool hasNoChildren(TrieNode4* node) {
        if (!node) return true;
        for (int i = 0; i < TrieNode4::ALPHABET_SIZE; ++i) {
            if (node->children[i]) return false;
        }
        return true;
    }
};

// Approach 5: Using a map within each node.
// This approach uses a map (std::map) to store the children of each node.  This is more flexible
// than using a fixed-size array, especially if the alphabet is large or not contiguous, but it can have a higher memory overhead.
#include <map>

class TrieNode5 {
public:
    std::map<char, TrieNode5*> children;
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
    Trie5() : root(new TrieNode5()) {}

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
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return current->isEndOfWord;
    }

    // Delete operation for Approach 5
    void deleteWord(const std::string& word) {
        if (!search(word)) return;

        std::vector<TrieNode5*> path;
        TrieNode5* current = root;
        for (char c : word) {
            path.push_back(current);
            current = current->children[c];
        }
        path.push_back(current);
        current->isEndOfWord = false;

        for (int i = word.size(); i > 0; --i) {
            current = path[i];
            char c = word[i - 1];
            if (hasNoChildren(current->children[c]) && !current->children[c]->isEndOfWord) {
                delete current->children[c];
                current->children.erase(c);
            } else {
                break;
            }
        }
    }

    bool hasNoChildren(TrieNode5* node) {
        if (!node) return true;
        return node->children.empty();
    }
};

int main() {
    // Example Usage
    std::cout << "Approach 1: Basic Trie with Raw Pointers\n";
    Trie1 trie1;
    trie1.insert("apple");
    trie1.insert("app");
    std::cout << "Search 'apple': " << (trie1.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app': " << (trie1.search("app") ? "true" : "false") << std::endl;
    std::cout << "Search 'banana': " << (trie1.search("banana") ? "true" : "false") << std::endl;
    trie1.deleteWord("apple");
    std::cout << "Search 'apple' after deletion: " << (trie1.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app' after deletion: " << (trie1.search("app") ? "true" : "false") << std::endl; //make sure "app" is still there

    std::cout << "\nApproach 2: Trie with Unique Pointers\n";
    Trie2 trie2;
    trie2.insert("apple");
    trie2.insert("app");
    std::cout << "Search 'apple': " << (trie2.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app': " << (trie2.search("app") ? "true" : "false") << std::endl;
    std::cout << "Search 'banana': " << (trie2.search("banana") ? "true" : "false") << std::endl;
    trie2.deleteWord("apple");
    std::cout << "Search 'apple' after deletion: " << (trie2.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app' after deletion: " << (trie2.search("app") ? "true" : "false") << std::endl;

    std::cout << "\nApproach 3: Trie with Shared Pointers\n";
    Trie3 trie3;
    trie3.insert("apple");
    trie3.insert("app");
    std::cout << "Search 'apple': " << (trie3.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app': " << (trie3.search("app") ? "true" : "false") << std::endl;
    std::cout << "Search 'banana': " << (trie3.search("banana") ? "true" : "false") << std::endl;
    trie3.deleteWord("apple");
    std::cout << "Search 'apple' after deletion: " << (trie3.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app' after deletion: " << (trie3.search("app") ? "true" : "false") << std::endl;

    std::cout << "\nApproach 4: Trie with Fixed-Size Array\n";
    Trie4 trie4;
    trie4.insert("apple");
    trie4.insert("app");
    std::cout << "Search 'apple': " << (trie4.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app': " << (trie4.search("app") ? "true" : "false") << std::endl;
    std::cout << "Search 'banana': " << (trie4.search("banana") ? "true" : "false") << std::endl;
    trie4.deleteWord("apple");
    std::cout << "Search 'apple' after deletion: " << (trie4.search("apple") ? "true" : "false") << std::endl;
     std::cout << "Search 'app' after deletion: " << (trie4.search("app") ? "true" : "false") << std::endl;

    std::cout << "\nApproach 5: Trie with Map\n";
    Trie5 trie5;
    trie5.insert("apple");
    trie5.insert("app");
    std::cout << "Search 'apple': " << (trie5.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app': " << (trie5.search("app") ? "true" : "false") << std::endl;
    std::cout << "Search 'banana': " << (trie5.search("banana") ? "true" : "false") << std::endl;
    trie5.deleteWord("apple");
    std::cout << "Search 'apple' after deletion: " << (trie5.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app' after deletion: " << (trie5.search("app") ? "true" : "false") << std::endl;

    return 0;
}
