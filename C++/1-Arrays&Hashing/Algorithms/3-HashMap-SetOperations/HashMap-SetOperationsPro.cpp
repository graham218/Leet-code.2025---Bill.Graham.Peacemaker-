#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <random>
#include <chrono>

// 1.  Data Deduplication and Unique Element Identification
//
//      * **Use Case:** Processing large datasets where duplicate entries need to be removed,
//          and unique elements identified.  This is common in data cleaning, log analysis,
//          and database management.
//      * **Implementation:** Using `std::unordered_set` to efficiently store and retrieve
//          unique elements.
//
//      * **Real-World Application:** A system that processes user activity logs.  We want to
//          identify unique user IDs to analyze user engagement without counting duplicates.
std::vector<int> getUniqueUserIds(const std::vector<int>& userIds) {
    std::unordered_set<int> uniqueUserIdsSet;
    std::vector<int> uniqueUserIds;

    for (int userId : userIds) {
        uniqueUserIdsSet.insert(userId); // Inserts only if the element is not already present.
    }

    // Copy the unique IDs from the set to a vector for ordered output (if needed).
    for (int userId : uniqueUserIdsSet) {
        uniqueUserIds.push_back(userId);
    }
    return uniqueUserIds;
}

// 2.  Frequency Counting
//
//      * **Use Case:** Counting the occurrences of each distinct element in a collection.
//          This is fundamental in statistical analysis, text processing, and database indexing.
//      * **Implementation:** Using `std::unordered_map` to store elements as keys and their
//          frequencies as values.
//
//      * **Real-World Application:** A system that analyzes website traffic.  We want to count
//          how many times each unique URL was visited to identify popular pages.
std::unordered_map<std::string, int> countUrlVisits(const std::vector<std::string>& urls) {
    std::unordered_map<std::string, int> urlVisitCounts;

    for (const std::string& url : urls) {
        urlVisitCounts[url]++; //  Increments the count for the URL. If the URL is not
                               //  present, it inserts it with a count of 1.
    }
    return urlVisitCounts;
}

// 3.  Membership Testing
//
//      * **Use Case:** Checking if an element exists within a collection.  This is crucial
//          for validation, search operations, and implementing set operations.
//      * **Implementation:** Using `std::unordered_set` for fast membership checks.
//
//      * **Real-World Application:** A spell checker.  We want to quickly determine if a
//          word is in a dictionary of valid words.
bool isWordValid(const std::string& word, const std::unordered_set<std::string>& dictionary) {
    return dictionary.find(word) != dictionary.end(); // Efficient lookup in the set.
}

// 4.  Caching
//
// * **Use Case**: Implementing a simple cache to store frequently accessed data for fast retrieval.
// * **Implementation**: Using `std::unordered_map` to store key-value pairs.  For simplicity,
//     this example doesn't include eviction policies (like LRU), but focuses on the core
//     caching mechanism.
// * **Real-World Application**: A web server caching frequently accessed files (e.g., images, HTML).
//     This reduces the load on the server and improves response times.
class SimpleCache {
public:
    SimpleCache(size_t capacity) : capacity_(capacity) {}

    std::string get(int key) {
        if (cache_.find(key) != cache_.end()) {
            return cache_[key]; // Return cached value
        }
        return ""; // Return empty string if key not found.  A more robust
                      //  solution might throw an exception or return a special value.
    }

    void put(int key, const std::string& value) {
        if (cache_.size() >= capacity_) {
            // Very basic eviction: Remove a random element.  In a real cache, you'd
            //  use a policy like LRU (Least Recently Used).
            if (!cache_.empty()) {
                auto it = cache_.begin();
                std::advance(it, std::rand() % cache_.size()); // Advance to a random element.
                cache_.erase(it);
            }
        }
        cache_[key] = value; // Insert or update the key-value pair.
    }
private:
    std::unordered_map<int, std::string> cache_;
    size_t capacity_;
};

// 5.  Inverted Index for Text Search
//
//      * **Use Case:** Creating an index that maps words to the documents (or positions)
//          where they appear.  This is the core of search engines.
//      * **Implementation:** Using `std::unordered_map` where keys are words and values are
//          vectors of document IDs.
//
//      * **Real-World Application:** A simplified search engine.  Given a set of documents,
//          we want to quickly find which documents contain a specific word.
std::unordered_map<std::string, std::vector<int>> buildInvertedIndex(const std::vector<std::string>& documents) {
    std::unordered_map<std::string, std::vector<int>> invertedIndex;

    for (int i = 0; i < documents.size(); ++i) {
        std::string document = documents[i];
        //  Basic word splitting (for simplicity).  A real-world application would
        //  use a more sophisticated tokenizer.
        std::string word;
        for (char c : document) {
            if (std::isalpha(c)) {
                word += c;
            } else if (!word.empty()) {
                // Convert to lowercase for case-insensitive search
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                invertedIndex[word].push_back(i); // Add document ID to the word's list.
                word.clear();
            }
        }
        if (!word.empty()) { //handle the last word
             std::transform(word.begin(), word.end(), word.begin(), ::tolower);
             invertedIndex[word].push_back(i);
        }
    }
    return invertedIndex;
}

// Function to perform search using the inverted index
std::vector<int> searchDocuments(const std::string& query, const std::unordered_map<std::string, std::vector<int>>& index) {
    std::string lowercaseQuery = query;
    std::transform(lowercaseQuery.begin(), lowercaseQuery.end(), lowercaseQuery.begin(), ::tolower);
    if (index.find(lowercaseQuery) != index.end()) {
        return index.at(lowercaseQuery);
    } else {
        return {}; // Return an empty vector if the word is not found.
    }
}

int main() {
    // Seed for the random number generator.  Good practice to do this once at the start.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // 1. Data Deduplication
    std::vector<int> userIds = {1, 5, 2, 5, 3, 1, 4, 2, 6};
    std::vector<int> uniqueUserIds = getUniqueUserIds(userIds);
    std::cout << "Unique User IDs: ";
    for (int userId : uniqueUserIds) {
        std::cout << userId << " ";
    }
    std::cout << std::endl;

    // 2. Frequency Counting
    std::vector<std::string> urls = {
        "https://www.example.com/",
        "https://www.example.com/about",
        "https://www.example.com/",
        "https://www.example.com/contact",
        "https://www.example.com/",
        "https://www.example.com/about"
    };
    std::unordered_map<std::string, int> urlVisitCounts = countUrlVisits(urls);
    std::cout << "URL Visit Counts:\n";
    for (const auto& pair : urlVisitCounts) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // 3. Membership Testing
    std::unordered_set<std::string> dictionary = {"apple", "banana", "cherry", "date"};
    std::cout << "Is 'banana' a valid word? " << (isWordValid("banana", dictionary) ? "Yes" : "No") << std::endl;
    std::cout << "Is 'grape' a valid word? " << (isWordValid("grape", dictionary) ? "Yes" : "No") << std::endl;

    // 4. Caching
    SimpleCache cache(3); // Cache with a capacity of 3
    cache.put(1, "value1");
    cache.put(2, "value2");
    cache.put(3, "value3");
    std::cout << "Cache get(1): " << cache.get(1) << std::endl; // Output: value1
    std::cout << "Cache get(4): " << cache.get(4) << std::endl; // Output: (empty string)
    cache.put(4, "value4"); // This will evict one of the existing items (randomly)
    std::cout << "Cache get(2): " << cache.get(2) << std::endl; //May or may not exist

    // 5. Inverted Index for Text Search
    std::vector<std::string> documents = {
        "The quick brown fox jumps over the lazy dog.",
        "A journey of a thousand miles begins with a single step.",
        "The best way to predict the future is to invent it.",
        "An apple a day keeps the doctor away.",
        "To be or not to be, that is the question."
    };
    std::unordered_map<std::string, std::vector<int>> invertedIndex = buildInvertedIndex(documents);

    std::string searchQuery = "the";
    std::vector<int> searchResults = searchDocuments(searchQuery, invertedIndex);
    std::cout << "Documents containing '" << searchQuery << "': ";
    if (searchResults.empty())
    {
        std::cout<< "None";
    }
    for (int docId : searchResults) {
        std::cout << docId << " ";
    }
    std::cout << std::endl;

    searchQuery = "future";
    searchResults = searchDocuments(searchQuery, invertedIndex);
    std::cout << "Documents containing '" << searchQuery << "': ";
    if (searchResults.empty())
    {
        std::cout<< "None";
    }
    for (int docId : searchResults) {
        std::cout << docId << " ";
    }
    std::cout << std::endl;

    return 0;
}
