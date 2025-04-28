#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <limits>
#include <functional> // Include for std::function

using namespace std;

// Function to find all possible one-character variations of a word
vector<string> getNeighbors(const string& word, const unordered_set<string>& wordList) {
    vector<string> neighbors;
    string temp = word; // Create a copy to avoid modifying the original word

    for (int i = 0; i < word.length(); ++i) {
        char originalChar = temp[i]; // Store the original character
        for (char c = 'a'; c <= 'z'; ++c) {
            if (c != originalChar) { // Skip if the character is the same
                temp[i] = c; // Change the character at the current position
                if (wordList.find(temp) != wordList.end()) { // Check if the modified word is in the dictionary
                    neighbors.push_back(temp); // Add the neighbor to the list
                }
            }
        }
        temp[i] = originalChar; // Restore the original character for the next iteration
    }
    return neighbors;
}

// Approach 1: Breadth-First Search (BFS) - Basic Implementation
int wordLadderBFS(const string& beginWord, const string& endWord, const vector<string>& wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end()); // Convert vector to set for faster lookup
    if (dict.find(endWord) == dict.end()) {
        return 0; // End word not in dictionary
    }

    queue<pair<string, int>> q; // Queue to store word and its level
    q.push({beginWord, 1});
    dict.erase(beginWord); // Mark beginWord as visited

    while (!q.empty()) {
        string currentWord = q.front().first;
        int level = q.front().second;
        q.pop();

        if (currentWord == endWord) {
            return level; // Found the end word, return the level
        }

        vector<string> neighbors = getNeighbors(currentWord, dict); // Get neighbors
        for (const string& neighbor : neighbors) {
            q.push({neighbor, level + 1}); // Add neighbor to queue with incremented level
            dict.erase(neighbor);       // Mark neighbor as visited
        }
    }
    return 0; // No path found
}

// Approach 2: Breadth-First Search (BFS) - Optimized using unordered_set for visited
int wordLadderBFSOptimized(const string& beginWord, const string& endWord, const vector<string>& wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if (dict.find(endWord) == dict.end()) return 0;

    queue<pair<string, int>> q;
    q.push({beginWord, 1});
    unordered_set<string> visited; // Use a set to track visited words
    visited.insert(beginWord);

    while (!q.empty()) {
        string currentWord = q.front().first;
        int level = q.front().second;
        q.pop();

        if (currentWord == endWord) return level;

        vector<string> neighbors = getNeighbors(currentWord, dict);
        for (const string& neighbor : neighbors) {
            if (visited.find(neighbor) == visited.end()) { // Check if neighbor is visited
                q.push({neighbor, level + 1});
                visited.insert(neighbor); // Mark neighbor as visited
            }
        }
    }
    return 0;
}

// Approach 3: Bidirectional BFS
int wordLadderBidirectionalBFS(const string& beginWord, const string& endWord, const vector<string>& wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if (dict.find(endWord) == dict.end()) return 0;

    unordered_set<string> head, tail, visited; // head starts from beginWord, tail from endWord
    head.insert(beginWord);
    tail.insert(endWord);
    int level = 1;

    while (!head.empty() && !tail.empty()) {
        // Always expand the smaller set to optimize
        if (head.size() > tail.size()) {
            swap(head, tail);
        }

        unordered_set<string> nextHead; // Store the next level of head
        for (const string& word : head) {
            visited.insert(word);
            vector<string> neighbors = getNeighbors(word, dict);
            for (const string& neighbor : neighbors) {
                if (tail.find(neighbor) != tail.end()) {
                    return level + 1; // Meet in the middle
                }
                if (visited.find(neighbor) == visited.end()) {
                    nextHead.insert(neighbor);
                }
            }
        }
        head = nextHead; // Move to the next level
        level++;
    }
    return 0;
}

// Approach 4: A* Search (Heuristic Search) - Manhattan Distance Heuristic
int wordLadderAStar(const string& beginWord, const string& endWord, const vector<string>& wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if (dict.find(endWord) == dict.end()) return 0;

    // Heuristic function: Manhattan distance between two words
    auto heuristic = [&](const string& word) {
        int distance = 0;
        for (int i = 0; i < word.length(); ++i) {
            distance += abs(word[i] - endWord[i]);
        }
        return distance;
    };

    // Use priority queue (min heap) based on f = g + h, where g is the level, h is heuristic
    priority_queue<pair<int, pair<string, int>>, vector<pair<int, pair<string, int>>>, greater<pair<int, pair<string, int>>>> pq;
    pq.push({heuristic(beginWord), {beginWord, 1}}); // {f, {word, g}}
    unordered_set<string> visited;
    visited.insert(beginWord);

    while (!pq.empty()) {
        string currentWord = pq.top().second.first;
        int level = pq.top().second.second;
        pq.pop();

        if (currentWord == endWord) return level;

        vector<string> neighbors = getNeighbors(currentWord, dict);
        for (const string& neighbor : neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                pq.push({level + 1 + heuristic(neighbor), {neighbor, level + 1}}); // Calculate f
            }
        }
    }
    return 0;
}

// Approach 5: Depth-First Search (DFS) - Recursive
int wordLadderDFS(const string& beginWord, const string& endWord, const vector<string>& wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if (dict.find(endWord) == dict.end()) return 0;

    int minLength = numeric_limits<int>::max(); // Initialize with max value
    unordered_set<string> visited;

    std::function<void(const string&, int)> dfs = [&](const string& currentWord, int level) { // Use a lambda for the recursive function
        if (currentWord == endWord) {
            minLength = min(minLength, level); // Update minLength
            return;
        }

        visited.insert(currentWord);
        vector<string> neighbors = getNeighbors(currentWord, dict);
        for (const string& neighbor : neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                dfs(neighbor, level + 1); // Recursive call
            }
        }
        visited.erase(currentWord); // Backtrack: Remove the current word from visited
    };

    dfs(beginWord, 1); // Start DFS

    return (minLength == numeric_limits<int>::max()) ? 0 : minLength; // Return 0 if no path found
}

int main() {
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    string beginWord = "hit";
    string endWord = "cog";

    cout << "Word Ladder Problem" << endl;
    cout << "Begin Word: " << beginWord << ", End Word: " << endWord << endl;
    cout << "Word List: ";
    for (const string& word : wordList) {
        cout << word << " ";
    }
    cout << endl << endl;

    cout << "Approach 1: BFS - Basic: " << wordLadderBFS(beginWord, endWord, wordList) << endl;
    cout << "Approach 2: BFS - Optimized: " << wordLadderBFSOptimized(beginWord, endWord, wordList) << endl;
    cout << "Approach 3: Bidirectional BFS: " << wordLadderBidirectionalBFS(beginWord, endWord, wordList) << endl;
    cout << "Approach 4: A* Search: " << wordLadderAStar(beginWord, endWord, wordList) << endl;
    cout << "Approach 5: DFS: " << wordLadderDFS(beginWord, endWord, wordList) << endl;

    return 0;
}
