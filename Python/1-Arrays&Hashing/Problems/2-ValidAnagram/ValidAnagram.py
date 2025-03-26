"""
Problem: Valid Anagram
Given two strings s and t, return true if t is an anagram of s, and false otherwise.
An anagram is a word or phrase formed by rearranging the letters of another, using all the original letters exactly once.
"""

def is_anagram_sorting(s, t):
    """
    Approach 1: Sorting
    Time Complexity: O(n log n) - Due to sorting
    Space Complexity: O(1) - Sorting is done in place (if allowed)
    """
    return sorted(s) == sorted(t)

def is_anagram_hashmap(s, t):
    """
    Approach 2: Hash Map (Dictionary Count)
    Time Complexity: O(n) - Single pass to count occurrences
    Space Complexity: O(1) - Since only 26 letters are stored
    """
    if len(s) != len(t):
        return False

    count_s, count_t = {}, {}
    for char in s:
        count_s[char] = count_s.get(char, 0) + 1
    for char in t:
        count_t[char] = count_t.get(char, 0) + 1

    return count_s == count_t

def is_anagram_counter(s, t):
    """
    Approach 3: Using Counter from collections
    Time Complexity: O(n) - Single pass count comparison
    Space Complexity: O(1) - Only 26 letters stored
    """
    from collections import Counter
    return Counter(s) == Counter(t)

def is_anagram_array(s, t):
    """
    Approach 4: Using Fixed-Size Array (Optimized for lowercase English letters)
    Time Complexity: O(n) - Single pass count comparison
    Space Complexity: O(1) - Fixed array size of 26
    """
    if len(s) != len(t):
        return False

    char_count = [0] * 26  # Assuming only lowercase English letters
    for char in s:
        char_count[ord(char) - ord('a')] += 1
    for char in t:
        char_count[ord(char) - ord('a')] -= 1

    return all(count == 0 for count in char_count)

def is_anagram_xor(s, t):
    """
    Approach 5: XOR Trick (Works only for unique characters)
    Time Complexity: O(n) - Single pass XOR computation
    Space Complexity: O(1) - No extra space used
    """
    if len(s) != len(t):
        return False

    xor_sum = 0
    for char in s + t:
        xor_sum ^= ord(char)

    return xor_sum == 0

# Test cases
s, t = "anagram", "nagaram"
print("Sorting Approach:", is_anagram_sorting(s, t))
print("Hash Map Approach:", is_anagram_hashmap(s, t))
print("Counter Approach:", is_anagram_counter(s, t))
print("Fixed Array Approach:", is_anagram_array(s, t))
print("XOR Trick Approach:", is_anagram_xor(s, t))
