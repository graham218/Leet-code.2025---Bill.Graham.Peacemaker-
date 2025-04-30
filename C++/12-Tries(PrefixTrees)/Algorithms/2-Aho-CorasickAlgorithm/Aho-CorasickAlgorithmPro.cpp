// Aho-Corasick Algorithm in C++: Multiple Real-World Implementations
// Author: OpenAI ChatGPT

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

// Node structure for the Trie
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    TrieNode* fail; // Failure link
    vector<int> output; // List of pattern indices
    TrieNode() : fail(nullptr) {}
};

class AhoCorasick {
private:
    TrieNode* root;
    vector<string> patterns;

public:
    AhoCorasick(const vector<string>& words) : patterns(words) {
        root = new TrieNode();
        buildTrie();
        buildFailureLinks();
    }

    // Build the Trie from the patterns
    void buildTrie() {
        for (int i = 0; i < patterns.size(); ++i) {
            TrieNode* node = root;
            for (char ch : patterns[i]) {
                if (!node->children[ch]) {
                    node->children[ch] = new TrieNode();
                }
                node = node->children[ch];
            }
            node->output.push_back(i); // store pattern index
        }
    }

    // Build failure links using BFS
    void buildFailureLinks() {
        queue<TrieNode*> q;
        for (auto& [ch, child] : root->children) {
            child->fail = root;
            q.push(child);
        }

        while (!q.empty()) {
            TrieNode* current = q.front(); q.pop();

            for (auto& [ch, child] : current->children) {
                TrieNode* fallback = current->fail;
                while (fallback && !fallback->children[ch]) {
                    fallback = fallback->fail;
                }
                if (fallback) {
                    child->fail = fallback->children[ch];
                } else {
                    child->fail = root;
                }
                // Append output links
                child->output.insert(child->output.end(),
                                     child->fail->output.begin(),
                                     child->fail->output.end());
                q.push(child);
            }
        }
    }

    // Search the text for patterns
    vector<pair<int, int>> search(const string& text) {
        vector<pair<int, int>> results; // (position, pattern_index)
        TrieNode* node = root;

        for (int i = 0; i < text.size(); ++i) {
            char ch = text[i];
            while (node && !node->children[ch]) {
                node = node->fail;
            }
            if (node) node = node->children[ch];
            else node = root;

            for (int patternIndex : node->output) {
                results.emplace_back(i - patterns[patternIndex].size() + 1, patternIndex);
            }
        }
        return results;
    }
};

// ----------------------------
// REAL-WORLD IMPLEMENTATIONS
// ----------------------------

// 1. Spam Filter: Detect presence of blacklisted phrases
void spamFilterDemo() {
    vector<string> blacklist = {"buy now", "click here", "subscribe"};
    AhoCorasick ac(blacklist);
    string email = "Please click here to subscribe to our newsletter";
    auto matches = ac.search(email);
    cout << "Spam matches:\n";
    for (auto [pos, index] : matches) {
        cout << "Found '" << blacklist[index] << "' at position " << pos << endl;
    }
}

// 2. Malware Signature Detection in Files
void malwareSignatureDemo() {
    vector<string> signatures = {"virus123", "worm.bat", "trojan.exe"};
    AhoCorasick ac(signatures);
    string fileContent = "This file contains virus123 and a worm.bat script.";
    auto matches = ac.search(fileContent);
    cout << "Malware signatures found:\n";
    for (auto [pos, index] : matches) {
        cout << "Detected '" << signatures[index] << "' at position " << pos << endl;
    }
}

// 3. Plagiarism Detection in Academic Texts
void plagiarismDemo() {
    vector<string> knownPhrases = {"machine learning", "deep neural network", "training dataset"};
    AhoCorasick ac(knownPhrases);
    string studentText = "The deep neural network was trained on a large training dataset.";
    auto matches = ac.search(studentText);
    cout << "Potential plagiarism detected:\n";
    for (auto [pos, index] : matches) {
        cout << "Matched '" << knownPhrases[index] << "' at position " << pos << endl;
    }
}

// 4. Log Monitoring for Security Alerts
void logMonitoringDemo() {
    vector<string> alerts = {"unauthorized access", "failed login", "security breach"};
    AhoCorasick ac(alerts);
    string logText = "User reported unauthorized access followed by a failed login attempt.";
    auto matches = ac.search(logText);
    cout << "Security alerts:\n";
    for (auto [pos, index] : matches) {
        cout << "Alert: '" << alerts[index] << "' at position " << pos << endl;
    }
}

// 5. Real-time Chat Moderation for Offensive Words
void chatModerationDemo() {
    vector<string> offensiveWords = {"badword1", "offensivephrase", "curseword"};
    AhoCorasick ac(offensiveWords);
    string chat = "This message contains badword1 and other stuff.";
    auto matches = ac.search(chat);
    cout << "Offensive language detected:\n";
    for (auto [pos, index] : matches) {
        cout << "Blocked '" << offensiveWords[index] << "' at position " << pos << endl;
    }
}

// Main driver to run all examples
int main() {
    spamFilterDemo();
    cout << "\n";
    malwareSignatureDemo();
    cout << "\n";
    plagiarismDemo();
    cout << "\n";
    logMonitoringDemo();
    cout << "\n";
    chatModerationDemo();
    return 0;
}
