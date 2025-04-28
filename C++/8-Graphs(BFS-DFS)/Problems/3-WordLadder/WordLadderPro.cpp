#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <limits>
#include <unordered_map> // Include for unordered_map
#include <functional>  // Include for std::function

using namespace std;

// Function to find all one-character different words from a given word
vector<string> getNeighbors(const string& word, const unordered_set<string>& wordSet) {
    vector<string> neighbors;
    string temp = word; // Create a copy to avoid modifying the original word

    for (int i = 0; i < temp.length(); ++i) {
        char originalChar = temp[i]; // Store the original character
        for (char c = 'a'; c <= 'z'; ++c) {
            if (c == originalChar) continue; // Skip the original character
            temp[i] = c; // Change the character at the current position
            if (wordSet.find(temp) != wordSet.end()) {
                neighbors.push_back(temp); // Add the neighbor if it exists in the word set
            }
        }
        temp[i] = originalChar; // Restore the original character
    }
    return neighbors;
}

// Approach 1: Breadth-First Search (BFS) - Standard Implementation
// Time Complexity: O(M * N), where M is the length of the word and N is the number of words in the wordList
// Space Complexity: O(N), for the queue and visited set
int wordLadderBFS(const string& beginWord, const string& endWord, const vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end()); // Convert to unordered_set for faster lookup
    if (wordSet.find(endWord) == wordSet.end()) return 0; // End word not in wordList
    wordSet.erase(beginWord); // Remove beginWord to avoid revisiting it
    queue<pair<string, int>> q; // Queue to store words and their levels
    q.push({beginWord, 1}); // Start with the beginWord at level 1

    while (!q.empty()) {
        string currentWord = q.front().first;
        int level = q.front().second;
        q.pop();

        if (currentWord == endWord) {
            return level; // Found the endWord, return the level
        }

        vector<string> neighbors = getNeighbors(currentWord, wordSet); // Get neighbors
        for (const string& neighbor : neighbors) {
            q.push({neighbor, level + 1}); // Enqueue the neighbor with increased level
            wordSet.erase(neighbor);       // Mark neighbor as visited by removing it from set
        }
    }
    return 0; // No path found
}

// Approach 2: BFS with Optimization - Early Exit
// Optimized by checking if a shorter path is found and exiting early.
int wordLadderBFS_Optimized(const string& beginWord, const string& endWord, const vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (wordSet.find(endWord) == wordSet.end()) return 0;
    wordSet.erase(beginWord);
    queue<pair<string, int>> q;
    q.push({beginWord, 1});
    int minLength = numeric_limits<int>::max(); // Initialize with max value

    while (!q.empty()) {
        string currentWord = q.front().first;
        int level = q.front().second;
        q.pop();

        if (currentWord == endWord) {
            minLength = level; // Update minLength
            break;             // Exit the loop, a shorter path is found.
        }

        if (level > minLength) continue; // If current level is already greater than minLength, skip.

        vector<string> neighbors = getNeighbors(currentWord, wordSet);
        for (const string& neighbor : neighbors) {
            q.push({neighbor, level + 1});
            wordSet.erase(neighbor);
        }
    }
    return minLength == numeric_limits<int>::max() ? 0 : minLength;
}


// Approach 3: Bidirectional BFS
// Search from both the beginWord and endWord simultaneously.
int wordLadderBFS_Bidirectional(const string& beginWord, const string& endWord, const vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (wordSet.find(endWord) == wordSet.end()) return 0;

    unordered_set<string> beginSet = {beginWord}; // Start from beginWord
    unordered_set<string> endSet = {endWord};   // Start from endWord
    int level = 1;
    wordSet.erase(beginWord);
    wordSet.erase(endWord);

    while (!beginSet.empty() && !endSet.empty()) {
        // Swap beginSet and endSet to always iterate the smaller set
        if (beginSet.size() > endSet.size()) {
            swap(beginSet, endSet);
        }

        unordered_set<string> nextSet; // Store the next level's words
        for (const string& word : beginSet) {
            vector<string> neighbors = getNeighbors(word, wordSet);
            for (const string& neighbor : neighbors) {
                if (endSet.find(neighbor) != endSet.end()) {
                    return level + 1; // Found intersection, path exists
                }
                if (wordSet.find(neighbor) != wordSet.end()) {
                    nextSet.insert(neighbor); // Add to next level
                    wordSet.erase(neighbor);  // Mark as visited
                }
            }
        }
        beginSet = nextSet; // Move to the next level
        level++;
    }
    return 0; // No path found
}

// Approach 4: A* Search (Heuristic Search)
// Uses a heuristic function to guide the search.  Manhattan distance is used here.
int wordLadderAStar(const string& beginWord, const string& endWord, const vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (wordSet.find(endWord) == wordSet.end()) return 0;

    // Heuristic function: Manhattan distance (number of different characters)
    auto heuristic = [&](const string& word) {
        int distance = 0;
        for (size_t i = 0; i < word.length(); ++i) {
            if (word[i] != endWord[i]) {
                distance++;
            }
        }
        return distance;
    };

    // Priority queue to store words with their cost (f = g + h)
    priority_queue<pair<int, pair<string, int>>, vector<pair<int, pair<string, int>>>, greater<pair<int, pair<string, int>>>> pq; // Min-heap
    pq.push({heuristic(beginWord), {beginWord, 1}}); // {f, {word, g}}
    unordered_map<string, int> gScore;            // Store the cost to reach each word (g)
    gScore[beginWord] = 1;
    unordered_set<string> visited;

    while (!pq.empty()) {
        string currentWord = pq.top().second.first;
        int currentG = pq.top().second.second;
        pq.pop();

        if (currentWord == endWord) {
            return currentG;
        }
        if(visited.find(currentWord) != visited.end()) continue;
        visited.insert(currentWord);

        vector<string> neighbors = getNeighbors(currentWord, wordSet);
        for (const string& neighbor : neighbors) {
            int tentativeG = currentG + 1; // Cost to reach neighbor
            if (gScore.find(neighbor) == gScore.end() || tentativeG < gScore[neighbor]) {
                // Found a better path to the neighbor
                gScore[neighbor] = tentativeG;
                int h = heuristic(neighbor);
                int f = tentativeG + h;
                pq.push({f, {neighbor, tentativeG}});
            }
        }
    }
    return 0;
}

// Approach 5: Iterative Deepening Depth-First Search (IDDFS)
// Combine DFS's space efficiency with BFS's completeness.
int wordLadderIDDFS(const string& beginWord, const string& endWord, const vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (wordSet.find(endWord) == wordSet.end()) return 0;

    function<int(const string&, int, int, unordered_set<string>)> dfs =  // Fix: Added std::
        [&](const string& currentWord, int level, int maxDepth, unordered_set<string> visited) {
            if (currentWord == endWord) return level;
            if (level > maxDepth) return 0; // Depth limit reached

            visited.insert(currentWord);
            vector<string> neighbors = getNeighbors(currentWord, wordSet);
            for (const string& neighbor : neighbors) {
                if (visited.find(neighbor) == visited.end()) {
                    int result = dfs(neighbor, level + 1, maxDepth, visited);
                    if (result != 0) return result;
                }
            }
            return 0;
        };

    // Iteratively increase the depth limit
    for (int maxDepth = 1; ; ++maxDepth) {
        unordered_set<string> visited;
        int result = dfs(beginWord, 1, maxDepth, visited);
        if (result != 0) return result; // Path found
        if (maxDepth > wordList.size()) return 0; //If maxDepth exceeds wordList size, no solution
    }
}

int main() {
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};

    cout << "Word Ladder - BFS: " << wordLadderBFS(beginWord, endWord, wordList) << endl;
    cout << "Word Ladder - BFS Optimized: " << wordLadderBFS_Optimized(beginWord, endWord, wordList) << endl;
    cout << "Word Ladder - Bidirectional BFS: " << wordLadderBFS_Bidirectional(beginWord, endWord, wordList) << endl;
    cout << "Word Ladder - A* Search: " << wordLadderAStar(beginWord, endWord, wordList) << endl;
    cout << "Word Ladder - IDDFS: " << wordLadderIDDFS(beginWord, endWord, wordList) << endl;

    return 0;
}
