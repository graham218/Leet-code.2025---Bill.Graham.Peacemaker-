'''
Sliding Window: Longest Substring Without Repeating Characters

Problem Statement:
Given a string s, find the length of the longest substring without repeating characters.
'''

# 1. Brute Force Approach (O(n^3))
def longest_unique_substring_brute_force(s):
    """
    Finds the length of the longest substring without repeating characters using a brute-force approach.
    It checks every possible substring for uniqueness.

    Args:
        s (str): The input string.

    Returns:
        int: The length of the longest unique substring.
    """
    max_length = 0  # Initialize the maximum length to 0.
    for i in range(len(s)):  # Iterate through all possible start indices of substrings.
        for j in range(i, len(s)):  # Iterate through all possible end indices for each start index.
            if len(set(s[i:j+1])) == (j - i + 1):  # Check if the substring s[i:j+1] has unique characters.
                # set(s[i:j+1]) creates a set of characters in the substring.
                # If the length of the set is equal to the length of the substring, all characters are unique.
                max_length = max(max_length, j - i + 1)  # Update max_length if the current substring is longer.
    return max_length  # Return the maximum length found.

# 2. Sliding Window with HashSet (O(n))
def longest_unique_substring_hashset(s):
    """
    Finds the length of the longest unique substring using a sliding window and a HashSet.
    The HashSet stores the characters in the current window.

    Args:
        s (str): The input string.

    Returns:
        int: The length of the longest unique substring.
    """
    seen = set()  # Initialize an empty HashSet to store characters in the current window.
    left = 0  # Initialize the left pointer of the sliding window.
    max_length = 0  # Initialize the maximum length to 0.
    for right in range(len(s)):  # Iterate through the string using the right pointer.
        while s[right] in seen:  # If the current character is already in the HashSet (i.e.,重复),
            seen.remove(s[left])  # Remove the leftmost character from the HashSet.
            left += 1  # Shrink the window from the left.
        seen.add(s[right])  # Add the current character to the HashSet.
        max_length = max(max_length, right - left + 1)  # Update max_length with the current window size.
    return max_length  # Return the maximum length.

# 3. Sliding Window with HashMap (O(n))
def longest_unique_substring_hashmap(s):
    """
    Finds the length of the longest unique substring using a sliding window and a HashMap.
    The HashMap stores characters and their indices.

    Args:
        s (str): The input string.

    Returns:
        int: The length of the longest unique substring.
    """
    char_index = {}  # Initialize an empty HashMap to store character indices.
    left = 0  # Initialize the left pointer of the sliding window.
    max_length = 0  # Initialize the maximum length to 0.
    for right in range(len(s)):  # Iterate through the string using the right pointer.
        if s[right] in char_index and char_index[s[right]] >= left:
            # If the current character is in the HashMap and its last seen index is within the current window:
            left = char_index[s[right]] + 1  # Move the left pointer to the position after the last occurrence of the character.
        char_index[s[right]] = right  # Update the index of the current character in the HashMap.
        max_length = max(max_length, right - left + 1)  # Update max_length.
    return max_length  # Return the maximum length.

# 4. Optimized Sliding Window with Array (O(n))
def longest_unique_substring_array(s):
    """
    Finds the length of the longest unique substring using a sliding window and an array.
    This approach is optimized for ASCII characters.

    Args:
        s (str): The input string.

    Returns:
        int: The length of the longest unique substring.
    """
    char_pos = [-1] * 128  # Initialize an array of size 128 (for ASCII characters) with -1.
    # char_pos[ord(c)] stores the last seen index of character c.
    left = 0  # Initialize the left pointer of the sliding window.
    max_length = 0  # Initialize the maximum length to 0.
    for right in range(len(s)):  # Iterate through the string using the right pointer.
        left = max(left, char_pos[ord(s[right])] + 1)  # Update left pointer.
        # ord(s[right]) gets the ASCII value of the character.
        # If the character has been seen before, char_pos[ord(s[right])] will be >= 0.
        # We move left to one position after the last occurrence.
        char_pos[ord(s[right])] = right  # Update the last seen position of the current character.
        max_length = max(max_length, right - left + 1)  # Update max_length.
    return max_length  # Return the maximum length.

# 5. Two Pointers with Frequency Map (O(n))
def longest_unique_substring_frequency_map(s):
    """
    Finds the length of the longest unique substring using two pointers and a frequency map (dictionary).

    Args:
        s (str): The input string.

    Returns:
        int: The length of the longest unique substring.
    """
    freq = {}  # Initialize an empty dictionary to store character frequencies.
    left = 0  # Initialize the left pointer.
    max_length = 0  # Initialize the maximum length.
    for right in range(len(s)):  # Iterate through the string using the right pointer.
        freq[s[right]] = freq.get(s[right], 0) + 1  # Increment the frequency of the current character.
        while freq[s[right]] > 1:  # If the frequency of the current character is greater than 1 (i.e., repeating),
            freq[s[left]] -= 1  # Decrement the frequency of the leftmost character.
            left += 1  # Move the left pointer to shrink the window.
        max_length = max(max_length, right - left + 1)  # Update max_length.
    return max_length  # Return the maximum length.

# Test Cases
s = "abcabcbb"
print("Brute Force:", longest_unique_substring_brute_force(s))
print("Sliding Window with HashSet:", longest_unique_substring_hashset(s))
print("Sliding Window with HashMap:", longest_unique_substring_hashmap(s))
print("Optimized Sliding Window with Array:", longest_unique_substring_array(s))
print("Two Pointers with Frequency Map:", longest_unique_substring_frequency_map(s))
