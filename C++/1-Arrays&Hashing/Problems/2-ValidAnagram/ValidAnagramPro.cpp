#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <chrono> // For timing comparisons

// Function to check if two strings are anagrams

// Approach 1: Sorting (STL sort)
// Time Complexity: O(n log n), Space Complexity: O(1) (or O(n) depending on sort implementation)
// Real-world use case: Good for comparing relatively short strings where simplicity is preferred.  Often used as a baseline.
bool isAnagram_sorting(const std::string& s, const std::string& t) {
    if (s.length() != t.length()) {
        return false;
    }
    std::string sorted_s = s; // Create copies to avoid modifying original strings
    std::string sorted_t = t;
    std::sort(sorted_s.begin(), sorted_s.end()); // Use the standard library sort
    std::sort(sorted_t.begin(), sorted_t.end());
    return sorted_s == sorted_t;
}

// Approach 2: Character Counting with vector (Optimized for ASCII)
// Time Complexity: O(n), Space Complexity: O(1) (fixed size array of 256)
// Real-world use case: Suitable when dealing with ASCII character sets, such as in many text processing scenarios.  Very efficient.
bool isAnagram_counting_vector(const std::string& s, const std::string& t) {
    if (s.length() != t.length()) {
        return false;
    }
    std::vector<int> char_counts(256, 0); // Assume ASCII character set

    for (char c : s) {
        char_counts[static_cast<unsigned char>(c)]++; // Use unsigned char to handle extended ASCII correctly
    }
    for (char c : t) {
        char_counts[static_cast<unsigned char>(c)]--;
        if (char_counts[static_cast<unsigned char>(c)] < 0) {
            return false;
        }
    }
    return true;
}

// Approach 3: Character Counting with unordered_map (Handles Unicode)
// Time Complexity: O(n), Space Complexity: O(n) in the worst case
// Real-world use case:  Essential when dealing with Unicode strings, where the character set is not limited to ASCII.  Handles a wider range of characters.
bool isAnagram_counting_map(const std::string& s, const std::string& t) {
    if (s.length() != t.length()) {
        return false;
    }
    std::unordered_map<char, int> char_counts; // Use unordered_map for Unicode characters

    for (char c : s) {
        char_counts[c]++;
    }
    for (char c : t) {
        char_counts[c]--;
        if (char_counts[c] < 0) {
            return false;
        }
    }
    return true;
}

// Approach 4: Using std::equal and std::mismatch (Less common, but shows alternative)
// Time Complexity: O(n log n) due to sorting, Space Complexity: O(n)
bool isAnagram_equal_mismatch(const std::string& s, const std::string& t) {
    if (s.length() != t.length()) {
        return false;
    }
    std::string sorted_s = s;
    std::string sorted_t = t;
    std::sort(sorted_s.begin(), sorted_s.end());
    std::sort(sorted_t.begin(), sorted_t.end());

    // std::equal checks if two ranges are equal
    return std::equal(sorted_s.begin(), sorted_s.end(), sorted_t.begin());
    // Or, using std::mismatch:
    // auto mismatch_pair = std::mismatch(sorted_s.begin(), sorted_s.end(), sorted_t.begin());
    // return mismatch_pair.first == sorted_s.end();
}

// Approach 5: Optimized Counting with Early Exit
// Time Complexity: O(n) in best and average case, O(n) in worst case, Space Complexity: O(1) for ASCII, O(n) for Unicode
bool isAnagram_optimized_counting(const std::string& s, const std::string& t) {
    if (s.length() != t.length()) {
        return false;
    }

    // Choose the appropriate data structure based on character set.
    if (s.length() < 256) { //if the length of the string is less than 256, assume ASCII
        std::vector<int> counts(256, 0); // For ASCII
         for (char c : s) {
            counts[static_cast<unsigned char>(c)]++;
        }
        for (char c : t) {
            counts[static_cast<unsigned char>(c)]--;
            if (counts[static_cast<unsigned char>(c)] < 0) {
                return false; // Early exit if a character count goes negative
            }
        }
        return true;
    }
    else{
        std::unordered_map<char, int> counts; // For Unicode
        for (char c : s) {
            counts[c]++;
        }
        for (char c : t) {
            counts[c]--;
            if (counts[c] < 0) {
                return false; // Early exit if a character count goes negative
            }
        }
        return true;
    }
}



int main() {
    std::string s1 = "listen";
    std::string t1 = "silent";
    std::string s2 = "hello";
    std::string t2 = "world";
    std::string s3 = "你好世界"; // Example with Chinese characters (Unicode)
    std::string t3 = "界世你好";

    // --- Timing and Output ---
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration;

    std::cout << "--- Anagram Check ---" << std::endl;

    // Approach 1: Sorting
    start = std::chrono::high_resolution_clock::now();
    std::cout << "Sorting: " << s1 << " and " << t1 << " are anagrams: " << (isAnagram_sorting(s1, t1) ? "true" : "false") << std::endl;
    std::cout << "Sorting: " << s2 << " and " << t2 << " are anagrams: " << (isAnagram_sorting(s2, t2) ? "true" : "false") << std::endl;
    std::cout << "Sorting: " << s3 << " and " << t3 << " are anagrams: " << (isAnagram_sorting(s3, t3) ? "true" : "false") << std::endl;
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Sorting Time: " << duration.count() << " seconds" << std::endl;

    // Approach 2: Counting with vector (ASCII)
    start = std::chrono::high_resolution_clock::now();
    std::cout << "Counting Vector: " << s1 << " and " << t1 << " are anagrams: " << (isAnagram_counting_vector(s1, t1) ? "true" : "false") << std::endl;
    std::cout << "Counting Vector: " << s2 << " and " << t2 << " are anagrams: " << (isAnagram_counting_vector(s2, t2) ? "true" : "false") << std::endl;
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Counting Vector Time: " << duration.count() << " seconds" << std::endl;

    // Approach 3: Counting with unordered_map (Unicode)
    start = std::chrono::high_resolution_clock::now();
    std::cout << "Counting Map: " << s1 << " and " << t1 << " are anagrams: " << (isAnagram_counting_map(s1, t1) ? "true" : "false") << std::endl;
    std::cout << "Counting Map: " << s2 << " and " << t2 << " are anagrams: " << (isAnagram_counting_map(s2, t2) ? "true" : "false") << std::endl;
    std::cout << "Counting Map: " << s3 << " and " << t3 << " are anagrams: " << (isAnagram_counting_map(s3, t3) ? "true" : "false") << std::endl;
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Counting Map Time: " << duration.count() << " seconds" << std::endl;

    // Approach 4: Using std::equal and std::mismatch
    start = std::chrono::high_resolution_clock::now();
    std::cout << "Equal/Mismatch: " << s1 << " and " << t1 << " are anagrams: " << (isAnagram_equal_mismatch(s1, t1) ? "true" : "false") << std::endl;
    std::cout << "Equal/Mismatch: " << s2 << " and " << t2 << " are anagrams: " << (isAnagram_equal_mismatch(s2, t2) ? "true" : "false") << std::endl;
    std::cout << "Equal/Mismatch: " << s3 << " and " << t3 << " are anagrams: " << (isAnagram_equal_mismatch(s3, t3) ? "true" : "false") << std::endl;
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Equal/Mismatch Time: " << duration.count() << " seconds" << std::endl;

     // Approach 5: Optimized Counting
    start = std::chrono::high_resolution_clock::now();
    std::cout << "Optimized Counting: " << s1 << " and " << t1 << " are anagrams: " << (isAnagram_optimized_counting(s1, t1) ? "true" : "false") << std::endl;
    std::cout << "Optimized Counting: " << s2 << " and " << t2 << " are anagrams: " << (isAnagram_optimized_counting(s2, t2) ? "true" : "false") << std::endl;
    std::cout << "Optimized Counting: " << s3 << " and " << t3 << " are anagrams: " << (isAnagram_optimized_counting(s3, t3) ? "true" : "false") << std::endl;
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Optimized Counting Time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
