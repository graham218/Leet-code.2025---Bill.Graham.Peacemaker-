#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <algorithm>

// Approach 1: Basic Aho-Corasick with Standard Library

// Structure for a node in the Trie
struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    TrieNode* failure; // Failure link
    bool isEndOfWord;
    int wordIndex; // Index of the word in the input array, -1 if not end of word.
    TrieNode() : failure(nullptr), isEndOfWord(false), wordIndex(-1) {}
};

// Class for Aho-Corasick automaton
class AhoCorasick {
public:
    TrieNode* root;
    std::vector<std::string> words; // Store the words

    AhoCorasick() : root(new TrieNode()) {}

    // Function to insert a word into the Trie
    void insert(const std::string& word, int index) {
        TrieNode* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
        current->wordIndex = index; // Store the word index
    }

     // Function to build the failure links
    void buildFailureLinks() {
        std::queue<TrieNode*> q;
        root->failure = root; // Failure link of root is root
        q.push(root);

        while (!q.empty()) {
            TrieNode* current = q.front();
            q.pop();

            for (auto& pair : current->children) {
                char ch = pair.first;
                TrieNode* child = pair.second;

                if (current == root) {
                    child->failure = root; // Failure link of direct children of root is root
                } else {
                    TrieNode* temp = current->failure;
                    while (temp != root && temp->children.find(ch) == temp->children.end()) {
                        temp = temp->failure;
                    }
                    if (temp->children.find(ch) != temp->children.end()) {
                        child->failure = temp->children[ch];
                    } else {
                        child->failure = root;
                    }
                }
                q.push(child);
            }
        }
    }

    // Function to search for occurrences of words in the text
    std::vector<std::pair<int, int>> search(const std::string& text) {
        std::vector<std::pair<int, int>> result; // Store (start index, word index)
        TrieNode* current = root;

        for (int i = 0; i < text.length(); ++i) {
            char ch = text[i];
            while (current != root && current->children.find(ch) == current->children.end()) {
                current = current->failure;
            }
            if (current->children.find(ch) != current->children.end()) {
                current = current->children[ch];
            }

            TrieNode* temp = current;
            while (temp != root)
             {
                if (temp->isEndOfWord)
                {
                    result.push_back({i - (int)words[temp->wordIndex].length() + 1, temp->wordIndex});
                }
                temp = temp->failure;
            }
        }
        return result;
    }

    // Function to add words.  Added to make the main() more concise
    void addWords(const std::vector<std::string>& wordList) {
        words = wordList; // Store the words
        for (int i = 0; i < wordList.size(); ++i) {
            insert(wordList[i], i);
        }
        buildFailureLinks();
    }

    ~AhoCorasick() {
        //Added a destructor to prevent memory leaks.
        std::queue<TrieNode*> q;
        q.push(root);
        while(!q.empty()){
            TrieNode* current = q.front();
            q.pop();
            for(auto child : current->children){
                q.push(child.second);
            }
            delete current;
        }
    }
};

// Approach 2: Optimized Aho-Corasick with Array-based Trie

const int ALPHABET_SIZE = 256; // Assuming ASCII characters

struct TrieNodeOptimized {
    int children[ALPHABET_SIZE];
    int failure;
    bool isEndOfWord;
    int wordIndex;
    TrieNodeOptimized() : failure(0), isEndOfWord(false), wordIndex(-1) {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            children[i] = 0;
        }
    }
};

class AhoCorasickOptimized {
public:
    std::vector<TrieNodeOptimized> trie;
    int nodeCount;
    std::vector<std::string> words;

    AhoCorasickOptimized() : nodeCount(1) {
        trie.resize(1); // Initialize with the root node
    }

    void insert(const std::string& word, int index) {
        int current = 0; // Start at the root
        for (char ch : word) {
            int chIndex = (unsigned char)ch; // Use unsigned char for indexing
            if (trie[current].children[chIndex] == 0) {
                trie[current].children[chIndex] = nodeCount++;
                trie.resize(nodeCount); // Resize the vector
            }
            current = trie[current].children[chIndex];
        }
        trie[current].isEndOfWord = true;
        trie[current].wordIndex = index;
    }

    void buildFailureLinks() {
        std::queue<int> q;
        trie[0].failure = 0; // Failure link of root is 0
        q.push(0);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int i = 0; i < ALPHABET_SIZE; ++i) {
                int child = trie[current].children[i];
                if (child != 0) {
                    if (current == 0) {
                        trie[child].failure = 0;
                    } else {
                        int temp = trie[current].failure;
                        while (temp != 0 && trie[temp].children[i] == 0) {
                            temp = trie[temp].failure;
                        }
                        if (trie[temp].children[i] != 0) {
                            trie[child].failure = trie[temp].children[i];
                        } else {
                            trie[child].failure = 0;
                        }
                    }
                    q.push(child);
                }
            }
        }
    }

    std::vector<std::pair<int, int>> search(const std::string& text) {
        std::vector<std::pair<int, int>> result;
        int current = 0;
        for (int i = 0; i < text.length(); ++i) {
            int chIndex = (unsigned char)text[i];
            while (current != 0 && trie[current].children[chIndex] == 0) {
                current = trie[current].failure;
            }
            if (trie[current].children[chIndex] != 0) {
                current = trie[current].children[chIndex];
            }
            int temp = current;
             while (temp != 0) {
                if (trie[temp].isEndOfWord) {
                    result.push_back({i - (int)words[trie[temp].wordIndex].length() + 1, trie[temp].wordIndex});
                }
                temp = trie[temp].failure;
            }
        }
        return result;
    }

    void addWords(const std::vector<std::string>& wordList) {
        words = wordList;
        for (int i = 0; i < wordList.size(); ++i) {
            insert(wordList[i], i);
        }
        buildFailureLinks();
    }
};

// Approach 3: Aho-Corasick with a Goto Function Matrix

const int MAX_STATES = 1000; // Maximum number of states in the automaton
const int MAX_CHARS = 256;  // Maximum number of characters (ASCII)

class AhoCorasickMatrix {
public:
    int gotoFunc[MAX_STATES][MAX_CHARS];
    int failure[MAX_STATES];
    bool isEndOfWord[MAX_STATES];
    int wordIndex[MAX_STATES]; //index of the word
    int numStates;
    std::vector<std::string> words;

    AhoCorasickMatrix() : numStates(1) {
        for (int i = 0; i < MAX_STATES; ++i) {
            for (int j = 0; j < MAX_CHARS; ++j) {
                gotoFunc[i][j] = 0; // 0 represents failure in goto function
            }
            failure[i] = 0;
            isEndOfWord[i] = false;
            wordIndex[i] = -1;
        }
    }

    void insert(const std::string& word, int index) {
        int currentState = 0;
        for (char ch : word) {
            int chIndex = (unsigned char)ch;
            if (gotoFunc[currentState][chIndex] == 0) {
                gotoFunc[currentState][chIndex] = numStates++;
            }
            currentState = gotoFunc[currentState][chIndex];
        }
        isEndOfWord[currentState] = true;
        wordIndex[currentState] = index;
    }

    void buildFailureLinks() {
        std::queue<int> q;
        failure[0] = 0;
        q.push(0);

        while (!q.empty()) {
            int currentState = q.front();
            q.pop();

            for (int i = 0; i < MAX_CHARS; ++i) {
                int nextState = gotoFunc[currentState][i];
                if (nextState != 0) {
                    if (currentState == 0) {
                        failure[nextState] = 0;
                    } else {
                        int temp = failure[currentState];
                        while (temp != 0 && gotoFunc[temp][i] == 0) {
                            temp = failure[temp];
                        }
                        if (gotoFunc[temp][i] != 0) {
                            failure[nextState] = gotoFunc[temp][i];
                        } else {
                            failure[nextState] = 0;
                        }
                    }
                    q.push(nextState);
                }
            }
        }
    }

    std::vector<std::pair<int, int>> search(const std::string& text) {
        std::vector<std::pair<int, int>> result;
        int currentState = 0;
        for (int i = 0; i < text.length(); ++i) {
            int chIndex = (unsigned char)text[i];
            while (currentState != 0 && gotoFunc[currentState][chIndex] == 0) {
                currentState = failure[currentState];
            }
            if (gotoFunc[currentState][chIndex] != 0) {
                currentState = gotoFunc[currentState][chIndex];
            }
            int temp = currentState;
            while(temp != 0){
                if(isEndOfWord[temp]){
                    result.push_back({i - (int)words[wordIndex[temp]].length() + 1, wordIndex[temp]});
                }
                temp = failure[temp];
            }
        }
        return result;
    }

     void addWords(const std::vector<std::string>& wordList) {
        words = wordList;
        for (int i = 0; i < wordList.size(); ++i) {
            insert(wordList[i], i);
        }
        buildFailureLinks();
    }
};

// Approach 4: Aho-Corasick with Unordered Map Optimization
struct TrieNodeUM {
    std::unordered_map<char, int> children;
    int failure;
    bool isEndOfWord;
    int wordIndex;
    TrieNodeUM() : failure(0), isEndOfWord(false), wordIndex(-1) {}
};

class AhoCorasickUM {
public:
    std::vector<TrieNodeUM> trie;
    int nodeCount;
    std::vector<std::string> words;

    AhoCorasickUM() : nodeCount(1) {
        trie.resize(1);
    }

    void insert(const std::string& word, int index) {
        int current = 0;
        for (char ch : word) {
            if (trie[current].children.find(ch) == trie[current].children.end()) {
                trie[current].children[ch] = nodeCount++;
                trie.resize(nodeCount);
            }
            current = trie[current].children[ch];
        }
        trie[current].isEndOfWord = true;
        trie[current].wordIndex = index;
    }

    void buildFailureLinks() {
        std::queue<int> q;
        trie[0].failure = 0;
        q.push(0);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (auto& pair : trie[current].children) {
                char ch = pair.first;
                int child = pair.second;

                if (current == 0) {
                    trie[child].failure = 0;
                } else {
                    int temp = trie[current].failure;
                    while (temp != 0 && trie[temp].children.find(ch) == trie[temp].children.end()) {
                        temp = trie[temp].failure;
                    }
                    if (trie[temp].children.find(ch) != trie[temp].children.end()) {
                        trie[child].failure = trie[temp].children[ch];
                    } else {
                        trie[child].failure = 0;
                    }
                }
                q.push(child);
            }
        }
    }

    std::vector<std::pair<int, int>> search(const std::string& text) {
        std::vector<std::pair<int, int>> result;
        int current = 0;
        for (int i = 0; i < text.length(); ++i) {
            char ch = text[i];
            while (current != 0 && trie[current].children.find(ch) == trie[current].children.end()) {
                current = trie[current].failure;
            }
            if (trie[current].children.find(ch) != trie[current].children.end()) {
                current = trie[current].children[ch];
            }
            int temp = current;
            while(temp != 0){
                if(trie[temp].isEndOfWord){
                    result.push_back({i - (int)words[trie[temp].wordIndex].length() + 1, trie[temp].wordIndex});
                }
                temp = trie[temp].failure;
            }
        }
        return result;
    }
    void addWords(const std::vector<std::string>& wordList) {
        words = wordList;
        for (int i = 0; i < wordList.size(); ++i) {
            insert(wordList[i], i);
        }
        buildFailureLinks();
    }
};

// Approach 5: Using vectors instead of maps.
struct TrieNodeVector {
    std::vector<int> children;
    int failure;
    bool isEndOfWord;
    int wordIndex;
    TrieNodeVector() : failure(0), isEndOfWord(false), wordIndex(-1), children(256, 0) {}
};

class AhoCorasickVector {
public:
    std::vector<TrieNodeVector> trie;
    int nodeCount;
    std::vector<std::string> words;

    AhoCorasickVector() : nodeCount(1) {
        trie.resize(1);
    }

    void insert(const std::string& word, int index) {
        int current = 0;
        for (char ch : word) {
            int chIndex = (unsigned char)ch;
            if (trie[current].children[chIndex] == 0) {
                trie[current].children[chIndex] = nodeCount++;
                trie.resize(nodeCount);
            }
            current = trie[current].children[chIndex];
        }
        trie[current].isEndOfWord = true;
        trie[current].wordIndex = index;
    }

    void buildFailureLinks() {
        std::queue<int> q;
        trie[0].failure = 0;
        q.push(0);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int i = 0; i < 256; ++i) {
                int child = trie[current].children[i];
                if (child != 0) {
                    if (current == 0) {
                        trie[child].failure = 0;
                    } else {
                        int temp = trie[current].failure;
                        while (temp != 0 && trie[temp].children[i] == 0) {
                            temp = trie[temp].failure;
                        }
                        if (trie[temp].children[i] != 0) {
                            trie[child].failure = trie[temp].children[i];
                        } else {
                            trie[child].failure = 0;
                        }
                    }
                    q.push(child);
                }
            }
        }
    }

    std::vector<std::pair<int, int>> search(const std::string& text) {
        std::vector<std::pair<int, int>> result;
        int current = 0;
        for (int i = 0; i < text.length(); ++i) {
            unsigned char ch = text[i];
            while (current != 0 && trie[current].children[ch] == 0) {
                current = trie[current].failure;
            }
            if (trie[current].children[ch] != 0) {
                current = trie[current].children[ch];
            }
            int temp = current;
            while (temp != 0) {
                if (trie[temp].isEndOfWord) {
                    result.push_back({i - (int)words[trie[temp].wordIndex].length() + 1, trie[temp].wordIndex});
                }
                temp = trie[temp].failure;
            }
        }
        return result;
    }

    void addWords(const std::vector<std::string>& wordList) {
        words = wordList;
        for (int i = 0; i < wordList.size(); ++i) {
            insert(wordList[i], i);
        }
        buildFailureLinks();
    }
};

int main() {
    // Example usage
    std::vector<std::string> words = {"he", "she", "his", "hers"};
    std::string text = "ahishers";

    // Approach 1: Basic Aho-Corasick
    std::cout << "Approach 1: Basic Aho-Corasick\n";
    AhoCorasick ac;
    ac.addWords(words);
    std::vector<std::pair<int, int>> result = ac.search(text);
    for (const auto& pair : result) {
        std::cout << "Found '" << words[pair.second] << "' at index " << pair.first << std::endl;
    }
    std::cout << std::endl;

    // Approach 2: Optimized Aho-Corasick with Array-based Trie
    std::cout << "Approach 2: Optimized Aho-Corasick\n";
    AhoCorasickOptimized acOptimized;
    acOptimized.addWords(words);
    result = acOptimized.search(text);
    for (const auto& pair : result) {
        std::cout << "Found '" << words[pair.second] << "' at index " << pair.first << std::endl;
    }
    std::cout << std::endl;

    // Approach 3: Aho-Corasick with a Goto Function Matrix
    std::cout << "Approach 3: Aho-Corasick with Matrix\n";
    AhoCorasickMatrix acMatrix;
    acMatrix.addWords(words);
    result = acMatrix.search(text);
    for (const auto& pair : result) {
        std::cout << "Found '" << words[pair.second] << "' at index " << pair.first << std::endl;
    }
    std::cout << std::endl;

    // Approach 4: Aho-Corasick with Unordered Map
    std::cout << "Approach 4: Aho-Corasick with Unordered Map\n";
    AhoCorasickUM acUM;
    acUM.addWords(words);
    result = acUM.search(text);
    for (const auto& pair : result) {
        std::cout << "Found '" << words[pair.second] << "' at index " << pair.first << std::endl;
    }
    std::cout << std::endl;

     // Approach 5: Aho-Corasick with Vector
    std::cout << "Approach 5: Aho-Corasick with Vector\n";
    AhoCorasickVector acVector;
    acVector.addWords(words);
    result = acVector.search(text);
    for (const auto& pair : result) {
        std::cout << "Found '" << words[pair.second] << "' at index " << pair.first << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
