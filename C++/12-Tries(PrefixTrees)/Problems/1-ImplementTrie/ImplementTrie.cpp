#include <iostream>
#include <vector>
#include <string>
#include <memory> // For smart pointers
#include <unordered_map>

// Approach 1: Basic Trie with Raw Pointers
// - Uses raw pointers for node management.
// - Simple and straightforward, but requires manual memory management.
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
            delete children[i]; // Corrected: delete instead of delete[]
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
        delete root;
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

    bool startsWith(const std::string& prefix) {
        TrieNode1* current = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index];
        }
        return true;
    }
};

// Approach 2: Trie with Unique Pointers
// - Uses std::unique_ptr for automatic memory management.
// - Prevents issues with manual memory deallocation.
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
        TrieNode2* current = root.get(); // Use get() to get the raw pointer.
        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index]) {
                current->children[index] = std::make_unique<TrieNode2>();
            }
            current = current->children[index].get();
        }
        current->isEndOfWord = true;
    }

    bool search(const std::string& word) {
        TrieNode2* current = root.get();
        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index].get();
        }
        return current->isEndOfWord;
    }

    bool startsWith(const std::string& prefix) {
        TrieNode2* current = root.get();
        for (char c : prefix) {
            int index = c - 'a';
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index].get();
        }
        return true;
    }
};

// Approach 3: Trie with Shared Pointers
// - Uses std::shared_ptr for shared ownership of nodes.
// - Useful in scenarios where multiple parts of the code need to access the same Trie nodes.
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

    bool startsWith(const std::string& prefix) {
        std::shared_ptr<TrieNode3> current = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index];
        }
        return true;
    }
};

// Approach 4: Trie with Vector-Based Children
// - Uses a vector instead of a fixed-size array for children.
// - More memory-efficient if the alphabet size is large and many nodes have few children.
class TrieNode4 {
public:
    std::vector<std::pair<char, std::unique_ptr<TrieNode4>>> children;
    bool isEndOfWord;

    TrieNode4() : isEndOfWord(false) {}
};

class Trie4 {
private:
    std::unique_ptr<TrieNode4> root;

public:
    Trie4() : root(std::make_unique<TrieNode4>()) {}

    void insert(const std::string& word) {
        TrieNode4* current = root.get();
        for (char c : word) {
            bool found = false;
            for (auto& child : current->children) {
                if (child.first == c) {
                    current = child.second.get();
                    found = true;
                    break;
                }
            }
            if (!found) {
                std::unique_ptr<TrieNode4> newNode = std::make_unique<TrieNode4>();
                TrieNode4* newNodePtr = newNode.get(); // Keep a raw pointer
                current->children.push_back({c, std::move(newNode)});
                current = newNodePtr;
            }
        }
        current->isEndOfWord = true;
    }

    bool search(const std::string& word) {
        TrieNode4* current = root.get();
        for (char c : word) {
            bool found = false;
            for (auto& child : current->children) {
                if (child.first == c) {
                    current = child.second.get();
                    found = true;
                    break;
                }
            }
            if (!found) {
                return false;
            }
        }
        return current->isEndOfWord;
    }

    bool startsWith(const std::string& prefix) {
        TrieNode4* current = root.get();
        for (char c : prefix) {
            bool found = false;
            for (auto& child : current->children) {
                if (child.first == c) {
                    current = child.second.get();
                    found = true;
                    break;
                }
            }
            if (!found) {
                return false;
            }
        }
        return true;
    }
};

// Approach 5: Trie with Unordered Map
// - Uses an unordered map to store children.
// - Provides efficient lookup and is suitable for larger alphabets (e.g., Unicode).
class TrieNode5 {
public:
    std::unordered_map<char, std::unique_ptr<TrieNode5>> children;
    bool isEndOfWord;

    TrieNode5() : isEndOfWord(false) {}
};

class Trie5 {
private:
    std::unique_ptr<TrieNode5> root;

public:
    Trie5() : root(std::make_unique<TrieNode5>()) {}

    void insert(const std::string& word) {
        TrieNode5* current = root.get();
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = std::make_unique<TrieNode5>();
            }
            current = current->children[c].get();
        }
        current->isEndOfWord = true;
    }

    bool search(const std::string& word) {
        TrieNode5* current = root.get();
        for (char c : word) {
            auto it = current->children.find(c);
            if (it == current->children.end()) {
                return false;
            }
            current = it->second.get();
        }
        return current->isEndOfWord;
    }

    bool startsWith(const std::string& prefix) {
        TrieNode5* current = root.get();
        for (char c : prefix) {
            auto it = current->children.find(c);
            if (it == current->children.end()) {
                return false;
            }
            current = it->second.get();
        }
        return true;
    }
};

int main() {
    // Example usage of each Trie implementation
    std::cout << "Approach 1: Basic Trie with Raw Pointers\n";
    Trie1 trie1;
    trie1.insert("apple");
    trie1.insert("app");
    std::cout << "Search 'apple': " << (trie1.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app': " << (trie1.search("app") ? "true" : "false") << std::endl;
    std::cout << "StartsWith 'app': " << (trie1.startsWith("app") ? "true" : "false") << std::endl;
    std::cout << "StartsWith 'appl': " << (trie1.startsWith("appl") ? "true" : "false") << std::endl;


    std::cout << "\nApproach 2: Trie with Unique Pointers\n";
    Trie2 trie2;
    trie2.insert("apple");
    trie2.insert("app");
    std::cout << "Search 'apple': " << (trie2.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app': " << (trie2.search("app") ? "true" : "false") << std::endl;
    std::cout << "StartsWith 'app': " << (trie2.startsWith("app") ? "true" : "false") << std::endl;
    std::cout << "StartsWith 'appl': " << (trie2.startsWith("appl") ? "true" : "false") << std::endl;

    std::cout << "\nApproach 3: Trie with Shared Pointers\n";
    Trie3 trie3;
    trie3.insert("apple");
    trie3.insert("app");
    std::cout << "Search 'apple': " << (trie3.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app': " << (trie3.search("app") ? "true" : "false") << std::endl;
    std::cout << "StartsWith 'app': " << (trie3.startsWith("app") ? "true" : "false") << std::endl;
    std::cout << "StartsWith 'appl': " << (trie3.startsWith("appl") ? "true" : "false") << std::endl;

    std::cout << "\nApproach 4: Trie with Vector-Based Children\n";
    Trie4 trie4;
    trie4.insert("apple");
    trie4.insert("app");
    std::cout << "Search 'apple': " << (trie4.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app': " << (trie4.search("app") ? "true" : "false") << std::endl;
    std::cout << "StartsWith 'app': " << (trie4.startsWith("app") ? "true" : "false") << std::endl;
     std::cout << "StartsWith 'appl': " << (trie4.startsWith("appl") ? "true" : "false") << std::endl;

    std::cout << "\nApproach 5: Trie with Unordered Map\n";
    Trie5 trie5;
    trie5.insert("apple");
    trie5.insert("app");
    std::cout << "Search 'apple': " << (trie5.search("apple") ? "true" : "false") << std::endl;
    std::cout << "Search 'app': " << (trie5.search("app") ? "true" : "false") << std::endl;
    std::cout << "StartsWith 'app': " << (trie5.startsWith("app") ? "true" : "false") << std::endl;
    std::cout << "StartsWith 'appl': " << (trie5.startsWith("appl") ? "true" : "false") << std::endl;

    return 0;
}
