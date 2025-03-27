'''
Sliding Window: Minimum Window Substring

Problem Statement:
Given two strings s and t, return the minimum window in s which contains all the characters of t in any order.
If no such window exists, return an empty string "".
'''

from collections import Counter

# 1. Brute Force (O(n^2 * m))
def min_window_brute_force(s, t):
    """
    Finds the minimum window substring using a brute-force approach.  It checks every possible substring in s
    to see if it contains all the characters in t.

    Args:
        s (str): The string to search in.
        t (str): The string containing the characters to find.

    Returns:
        str: The minimum window substring, or "" if no such window exists.
    """
    if not t or not s:  # Handle edge cases where either t or s is empty.
        return ""

    t_count = Counter(t)  # Count the frequency of each character in t.
    min_len = float("inf")  # Initialize the minimum length to infinity.
    min_substring = ""  # Initialize the minimum substring to an empty string.

    for left in range(len(s)):  # Iterate through all possible start indices of the window.
        window_count = Counter()  # Count the frequency of characters in the current window.
        for right in range(left, len(s)):  # Iterate through all possible end indices for the current window.
            window_count[s[right]] += 1  # Add the character at the right pointer to the window count.
            # Check if the current window contains all characters in t with the required frequencies.
            if all(window_count[c] >= t_count[c] for c in t_count):
                if right - left + 1 < min_len:  # If the current window is smaller than the minimum length found so far,
                    min_len = right - left + 1  # update the minimum length,
                    min_substring = s[left:right+1]  # and update the minimum substring.
                break  # Once a valid window is found, no need to check larger windows starting at the same left.
    return min_substring  # Return the minimum window substring.

# 2. Sliding Window with HashMap (O(n))
def min_window_sliding_window(s, t):
    """
    Finds the minimum window substring using a sliding window approach with a HashMap (Counter).

    Args:
        s (str): The string to search in.
        t (str): The string containing the characters to find.

    Returns:
        str: The minimum window substring, or "" if no such window exists.
    """
    if not t or not s:
        return ""

    t_count = Counter(t)  # Count the frequency of each character in t.
    window_count = Counter()  # Count the frequency of characters in the current window.
    required_chars = len(t_count)  # Number of unique characters in t that need to be formed.
    formed_chars = 0  # Count of unique characters in the window that meet the required frequency.
    left = 0  # Left pointer of the sliding window.
    min_len = float("inf")  # Initialize minimum length.
    min_substring = ""  # Initialize minimum substring.

    for right in range(len(s)):  # Right pointer of the sliding window.
        window_count[s[right]] += 1  # Add the character at the right pointer to the window count.
        if s[right] in t_count and window_count[s[right]] == t_count[s[right]]:
            # If the character is in t and its frequency in the window matches its frequency in t,
            formed_chars += 1  # increment formed_chars.

        while left <= right and formed_chars == required_chars:  # While the window is valid (contains all chars in t).
            if right - left + 1 < min_len:  # Update minimum length and substring if a smaller valid window is found.
                min_len = right - left + 1
                min_substring = s[left:right+1]

            window_count[s[left]] -= 1  # Remove the character at the left pointer from the window count.
            if s[left] in t_count and window_count[s[left]] < t_count[s[left]]:
                # If removing the character makes the window invalid,
                formed_chars -= 1  # decrement formed_chars.
            left += 1  # Move the left pointer to shrink the window.

    return min_substring  # Return the minimum window substring.

# 3. Optimized Two Pointers (O(n))
def min_window_two_pointers(s, t):
    """
    Finds the minimum window substring using two pointers, optimized for performance.  This is essentially the same
    as the sliding window approach, but may be referred to as "two pointers".

    Args:
        s (str): The string to search in.
        t (str): The string containing the characters to find.

    Returns:
        str: The minimum window substring, or "" if no such window exists.
    """
    if not t or not s:
        return ""

    t_count = Counter(t)
    window_count = Counter()
    required_chars = len(t_count)
    formed_chars = 0
    left = 0
    min_len = float("inf")
    min_substring = ""

    for right in range(len(s)):
        char = s[right]
        window_count[char] += 1

        if char in t_count and window_count[char] == t_count[char]:
            formed_chars += 1

        while left <= right and formed_chars == required_chars:
            if right - left + 1 < min_len:
                min_len = right - left + 1
                min_substring = s[left:right+1]

            window_count[s[left]] -= 1
            if s[left] in t_count and window_count[s[left]] < t_count[s[left]]:
                formed_chars -= 1
            left += 1

    return min_substring

# 4. Character Frequency Array (O(n))
def min_window_char_array(s, t):
    """
    Finds the minimum window substring using character frequency arrays instead of HashMaps.  This can be more
    efficient for strings with a limited character set (e.g., ASCII).

    Args:
        s (str): The string to search in.
        t (str): The string containing the characters to find.

    Returns:
        str: The minimum window substring, or "" if no such window exists.
    """
    if not t or not s:
        return ""

    t_count = [0] * 128  # Array to store character frequencies for t (assuming ASCII characters).
    window_count = [0] * 128  # Array to store character frequencies for the current window.

    for char in t:
        t_count[ord(char)] += 1  # Populate the t_count array.

    left, formed, required_chars = 0, 0, sum(1 for c in t_count if c > 0)  # Calculate required_chars.
    min_len, min_substring = float("inf"), ""

    for right in range(len(s)):
        char_index = ord(s[right])  # Get the ASCII value of the current character.
        window_count[char_index] += 1  # Update the character count for the window.

        if t_count[char_index] and window_count[char_index] == t_count[char_index]:
            # If the character is in t and its frequency matches,
            formed += 1  # increment formed.

        while left <= right and formed == required_chars:
            if right - left + 1 < min_len:
                min_len = right - left + 1
                min_substring = s[left:right+1]

            window_count[ord(s[left])] -= 1
            if t_count[ord(s[left])] and window_count[ord(s[left])] < t_count[ord(s[left])]:
                formed -= 1
            left += 1

    return min_substring

# 5. Sliding Window with Queue (O(n))
from collections import deque

def min_window_queue(s, t):
    """
    Finds the minimum window substring using a sliding window and a queue.  This approach maintains the order
    of characters in the window using a queue.

    Args:
        s (str): The string to search in.
        t (str): The string containing the characters to find.

    Returns:
        str: The minimum window substring, or "" if no such window exists.
    """
    if not t or not s:
        return ""

    t_count = Counter(t)
    window_count = Counter()
    required_chars = len(t_count)
    formed_chars = 0
    min_len = float("inf")
    min_substring = ""
    queue = deque()  # Use a deque as a queue.

    for right in range(len(s)):
        queue.append(s[right])  # Add the character to the queue.
        window_count[s[right]] += 1

        if s[right] in t_count and window_count[s[right]] == t_count[s[right]]:
            formed_chars += 1

        while queue and formed_chars == required_chars:
            if len(queue) < min_len:
                min_len = len(queue)
                min_substring = "".join(queue)  # Convert the queue to a string.

            removed_char = queue.popleft()  # Remove the leftmost character.
            window_count[removed_char] -= 1
            if removed_char in t_count and window_count[removed_char] < t_count[removed_char]:
                formed_chars -= 1

    return min_substring

# Test Cases
s = "ADOBECODEBANC"
t = "ABC"
print("Brute Force:", min_window_brute_force(s, t))
print("Sliding Window with HashMap:", min_window_sliding_window(s, t))
print("Two Pointers:", min_window_two_pointers(s, t))
print("Character Frequency Array:", min_window_char_array(s, t))
print("Sliding Window with Queue:", min_window_queue(s, t))
