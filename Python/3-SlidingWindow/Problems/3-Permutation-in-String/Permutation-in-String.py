'''
Sliding Window: Permutation in String

Problem Statement:
Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
'''

from collections import Counter

# 1. Brute Force (O(n! * m))
def check_permutation_brute_force(s1, s2):
    """
    Checks if s2 contains a permutation of s1 using a brute-force approach.
    It generates all permutations of s1 and checks if any of them are a substring of s2.
    This is very inefficient for larger strings.

    Args:
        s1 (str): The shorter string.
        s2 (str): The longer string.

    Returns:
        bool: True if s2 contains a permutation of s1, False otherwise.
    """
    from itertools import permutations  # Import the permutations function.
    perms = set("".join(p) for p in permutations(s1))  # Generate all permutations of s1 and store them in a set.
    # "".join(p) converts a permutation tuple to a string.  The set avoids duplicate permutations.
    for i in range(len(s2) - len(s1) + 1):  # Iterate through all possible starting positions of a substring of length s1 in s2.
        if s2[i:i+len(s1)] in perms:  # Check if the current substring of s2 is one of the permutations of s1.
            return True  # If a permutation is found, return True.
    return False  # If no permutation is found, return False.

# 2. Sorting Approach (O(m log m + n log n))
def check_permutation_sorting(s1, s2):
    """
    Checks if s2 contains a permutation of s1 by sorting both s1 and substrings of s2.
    If a sorted substring of s2 is equal to the sorted s1, then s2 contains a permutation of s1.

    Args:
        s1 (str): The shorter string.
        s2 (str): The longer string.

    Returns:
        bool: True if s2 contains a permutation of s1, False otherwise.
    """
    s1_sorted = sorted(s1)  # Sort the characters in s1.
    for i in range(len(s2) - len(s1) + 1):  # Iterate through all possible starting positions of a substring of length s1 in s2.
        if sorted(s2[i:i+len(s1)]) == s1_sorted:  # Sort the characters in the current substring of s2 and compare it with the sorted s1.
            return True  # If they are equal, return True.
    return False  # If no matching substring is found, return False.

# 3. Sliding Window with HashMap (O(n + m))
def check_permutation_sliding_window(s1, s2):
    """
    Checks if s2 contains a permutation of s1 using a sliding window and HashMaps (Counters).
    It maintains a character count of s1 and a character count of the current window in s2.

    Args:
        s1 (str): The shorter string.
        s2 (str): The longer string.

    Returns:
        bool: True if s2 contains a permutation of s1, False otherwise.
    """
    s1_count = Counter(s1)  # Create a Counter (HashMap) for the character counts in s1.
    window_count = Counter(s2[:len(s1)-1])  # Create a Counter for the character counts in the initial window of s2 (of size len(s1)-1).

    for i in range(len(s1)-1, len(s2)):  # Iterate through s2, starting from the index where the window has size len(s1).
        window_count[s2[i]] += 1  # Add the new character entering the window.
        if window_count == s1_count:  # If the character counts in the window match the character counts in s1,
            return True  # then a permutation is found.
        window_count[s2[i - len(s1) + 1]] -= 1  # Remove the character leaving the window.
        if window_count[s2[i - len(s1) + 1]] == 0:  # If the count of a character becomes 0,
            del window_count[s2[i - len(s1) + 1]]  # remove it from the Counter.

    return False  # If no permutation is found, return False.

# 4. Optimized Sliding Window with Fixed Array (O(n))
def check_permutation_optimized(s1, s2):
    """
    Checks if s2 contains a permutation of s1 using a sliding window and fixed-size arrays for character counts.
    This optimization is possible because the number of distinct characters is limited (e.g., 26 for lowercase English).

    Args:
        s1 (str): The shorter string.
        s2 (str): The longer string.

    Returns:
        bool: True if s2 contains a permutation of s1, False otherwise.
    """
    if len(s1) > len(s2):  # If s1 is longer than s2, s2 cannot contain a permutation of s1.
        return False

    s1_map = [0] * 26  # Create an array to store character counts for s1 (assuming lowercase English letters).
    s2_map = [0] * 26  # Create an array to store character counts for the sliding window in s2.
    a_ord = ord('a')  # Get the ASCII value of 'a' for efficient character index calculation.

    for i in range(len(s1)):  # Calculate character counts for s1 and the initial window of s2.
        s1_map[ord(s1[i]) - a_ord] += 1  # Increment the count for the corresponding character in s1_map.
        s2_map[ord(s2[i]) - a_ord] += 1  # Increment the count for the corresponding character in s2_map.

    matches = sum([s1_map[i] == s2_map[i] for i in range(26)])  # Count the number of characters with matching counts.

    for i in range(len(s1), len(s2)):  # Slide the window through s2.
        if matches == 26:  # If all 26 characters have matching counts, a permutation is found.
            return True

        left_char = ord(s2[i - len(s1)]) - a_ord  # Get the character leaving the window.
        right_char = ord(s2[i]) - a_ord  # Get the character entering the window.

        s2_map[right_char] += 1  # Add the new character to the window's count.
        if s1_map[right_char] == s2_map[right_char]:  # If the count now matches s1's count,
            matches += 1  # increment matches.
        elif s1_map[right_char] + 1 == s2_map[right_char]:  # If the count was one less than s1's count,
            matches -= 1  # decrement matches.

        s2_map[left_char] -= 1  # Remove the character leaving the window.
        if s1_map[left_char] == s2_map[left_char]:  # If the count now matches s1's count,
            matches += 1  # increment matches.
        elif s1_map[left_char] - 1 == s2_map[left_char]:  # If the count was one more than s1's count,
            matches -= 1  # decrement matches.

    return matches == 26  # After the loop, check if all characters have matching counts.

# 5. Two Pointers with Character Frequency (O(n))
def check_permutation_two_pointers(s1, s2):
    """
    Checks if s2 contains a permutation of s1 using two pointers and a character frequency counter.
    It maintains a sliding window in s2 and compares the character frequencies in the window with those in s1.

    Args:
        s1 (str): The shorter string.
        s2 (str): The longer string.

    Returns:
        bool: True if s2 contains a permutation of s1, False otherwise.
    """
    target_freq = Counter(s1)  # Create a Counter for the character frequencies in s1.
    window_freq = Counter()  # Create a Counter for the character frequencies in the current window of s2.

    left = 0  # Initialize the left pointer of the sliding window.
    for right in range(len(s2)):  # Iterate through s2 using the right pointer.
        window_freq[s2[right]] += 1  # Add the current character to the window's frequency count.
        if right - left + 1 > len(s1):  # If the window size exceeds the length of s1,
            window_freq[s2[left]] -= 1  # remove the leftmost character from the window.
            if window_freq[s2[left]] == 0:  # If the frequency of the leftmost character becomes 0,
                del window_freq[s2[left]]  # remove it from the Counter.
            left += 1  # Move the left pointer to shrink the window.

        if window_freq == target_freq:  # If the character frequencies in the window match those in s1,
            return True  # a permutation is found.
    return False  # If no permutation is found, return False.

# Test Cases
s1 = "ab"
s2 = "eidbaooo"
print("Brute Force:", check_permutation_brute_force(s1, s2))
print("Sorting Approach:", check_permutation_sorting(s1, s2))
print("Sliding Window with HashMap:", check_permutation_sliding_window(s1, s2))
print("Optimized Sliding Window:", check_permutation_optimized(s1, s2))
print("Two Pointers with Character Frequency:", check_permutation_two_pointers(s1, s2))
