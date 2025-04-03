import sys

def build_suffix_array(text):
    """
    Builds the suffix array for a given text.

    Args:
        text: The input string.

    Returns:
        A list of integers representing the suffix array.
        Returns an empty list if the input text is empty.
    """
    if not text:
        return []

    n = len(text)
    suffixes = [(text[i:], i) for i in range(n)]
    suffixes.sort()  # Sort lexicographically
    suffix_array = [suffix[1] for suffix in suffixes]
    return suffix_array

def compute_lcp_array(text, suffix_array):
    """
    Computes the Longest Common Prefix (LCP) array using the suffix array.
    Uses the Kasai's algorithm for efficient computation.

    Args:
        text: The input string.
        suffix_array: The suffix array for the input string.

    Returns:
        A list of integers representing the LCP array.
        Returns an empty list if the input text or suffix array is empty.
    """
    if not text or not suffix_array:
        return []

    n = len(text)
    lcp_array = [0] * n
    rank = [0] * n

    for i, index in enumerate(suffix_array):
        rank[index] = i

    k = 0
    for i in range(n):
        if rank[i] == n - 1:
            k = 0
            continue
        j = suffix_array[rank[i] + 1]
        while i + k < n and j + k < n and text[i + k] == text[j + k]:
            k += 1
        lcp_array[rank[i]] = k
        if k > 0:
            k -= 1
    return lcp_array

def search_pattern_suffix_array(text, pattern, suffix_array):
    """
    Searches for a pattern in a text using the suffix array.

    Args:
        text: The input string.
        pattern: The pattern to search for.
        suffix_array: The suffix array of the text.

    Returns:
        A list of starting indices where the pattern occurs in the text.
        Returns an empty list if the pattern is not found or input is invalid.
    """
    if not text or not pattern or not suffix_array:
        return []

    n = len(text)
    m = len(pattern)
    left = 0
    right = n - 1
    occurrences = []

    while left <= right:
        mid = (left + right) // 2
        suffix_start = suffix_array[mid]
        comparison = text[suffix_start:min(suffix_start + m, n)].compareTo(pattern) if hasattr(text[suffix_start:min(suffix_start + m, n)], 'compareTo') else (text[suffix_start:min(suffix_start + m, n)] > pattern) - (text[suffix_start:min(suffix_start + m, n)] < pattern)

        if comparison < 0:
            left = mid + 1
        elif comparison > 0:
            right = mid - 1
        else:  # Found a match
            index = mid
            # Find all occurrences to the left
            while index >= 0 and text[suffix_array[index]:min(suffix_array[index] + m, n)] == pattern:
                occurrences.append(suffix_array[index])
                index -= 1
            index = mid + 1
            # Find all occurrences to the right
            while index < n and text[suffix_array[index]:min(suffix_array[index] + m, n)] == pattern:
                occurrences.append(suffix_array[index])
                index += 1
            occurrences.sort()
            return occurrences

    return occurrences

def compute_z_array(text):
    """
    Computes the Z-array for a given text.

    Args:
        text: The input string.

    Returns:
        A list of integers representing the Z-array.
        Returns an empty list if the input text is empty.
    """
    if not text:
        return []

    n = len(text)
    z_array = [0] * n
    left = 0
    right = 0

    for i in range(1, n):
        if i > right:
            left = right = i
            while right < n and text[right - left] == text[right]:
                right += 1
            z_array[i] = right - left
            right -= 1
        else:
            k = i - left
            if z_array[k] < right - i + 1:
                z_array[i] = z_array[k]
            else:
                left = i
                while right < n and text[right - left] == text[right]:
                    right += 1
                z_array[i] = right - left
                right -= 1
    return z_array

def search_pattern_z_algorithm(text, pattern):
    """
    Searches for a pattern in a text using the Z-algorithm.

    Args:
        text: The input string.
        pattern: The pattern to search for.

    Returns:
        A list of starting indices where the pattern occurs in the text.
        Returns an empty list if the pattern is not found or input is invalid.
    """
    if not text or not pattern:
        return []

    n = len(text)
    m = len(pattern)
    combined_string = pattern + "$" + text  # Concatenate pattern and text
    z_array = compute_z_array(combined_string)
    occurrences = []

    for i in range(m + 1, n + m + 1):
        if z_array[i] == m:
            occurrences.append(i - m - 1)  # Adjust index to match original text
    return occurrences

# Helper function to compare strings (needed for Python 2 compatibility)
def compareTo(str1, str2):
    if str1 == str2:
        return 0
    elif str1 > str2:
        return 1
    else:
        return -1

# Example usage (Main function for testing)
if __name__ == "__main__":
    text = "banana"
    pattern = "ana"

    # Suffix Array and LCP Array
    suffix_array = build_suffix_array(text)
    print(f"Suffix Array of '{text}': {suffix_array}")  # Output: [5, 3, 1, 0, 4, 2]
    lcp_array = compute_lcp_array(text, suffix_array)
    print(f"LCP Array of '{text}': {lcp_array}") # Output: [0, 1, 3, 0, 0, 2]

    # Search using Suffix Array
    occurrences_suffix_array = search_pattern_suffix_array(text, pattern, suffix_array)
    print(f"Pattern '{pattern}' found at indices (using Suffix Array): {occurrences_suffix_array}")  # Output: [1, 3]

    # Z-Algorithm
    z_array = compute_z_array(text)
    print(f"Z-Array of '{text}': {z_array}")  # Output: [0, 0, 1, 0, 3, 0]

    # Search using Z-Algorithm
    occurrences_z_algorithm = search_pattern_z_algorithm(text, pattern)
    print(f"Pattern '{pattern}' found at indices (using Z-Algorithm): {occurrences_z_algorithm}")  # Output: [1, 3]

    # Test case with no occurrences
    text2 = "abracadabra"
    pattern2 = "xyz"
    suffix_array2 = build_suffix_array(text2)
    occurrences_suffix_array2 = search_pattern_suffix_array(text2, pattern2, suffix_array2)
    occurrences_z_algorithm2 = search_pattern_z_algorithm(text2, pattern2)
    print(f"Pattern '{pattern2}' found at indices (using Suffix Array) in '{text2}': {occurrences_suffix_array2}")  # Output: []
    print(f"Pattern '{pattern2}' found at indices (using Z-Algorithm) in '{text2}': {occurrences_z_algorithm2}")  # Output: []

    # Test case with empty text
    text3 = ""
    pattern3 = "a"
    suffix_array3 = build_suffix_array(text3)
    occurrences_suffix_array3 = search_pattern_suffix_array(text3, pattern3, suffix_array3)
    occurrences_z_algorithm3 = search_pattern_z_algorithm(text3, pattern3)
    print(f"Pattern '{pattern3}' found at indices (using Suffix Array) in empty text: {occurrences_suffix_array3}")  # Output: []
    print(f"Pattern '{pattern3}' found at indices (using Z-Algorithm) in empty text: {occurrences_z_algorithm3}")  # Output: []

    # Test case with empty pattern
    text4 = "abc"
    pattern4 = ""
    suffix_array4 = build_suffix_array(text4)
    occurrences_suffix_array4 = search_pattern_suffix_array(text4, pattern4, suffix_array4)
    occurrences_z_algorithm4 = search_pattern_z_algorithm(text4, pattern4)
    print(f"Pattern '' found at indices (using Suffix Array) in 'abc': {occurrences_suffix_array4}")  # Output: []
    print(f"Pattern '' found at indices (using Z-Algorithm) in 'abc': {occurrences_z_algorithm4}")  # Output: []

    # Test case with pattern longer than text.
    text5 = "abc"
    pattern5 = "abcd"
    suffix_array5 = build_suffix_array(text5)
    occurrences_suffix_array5 = search_pattern_suffix_array(text5, pattern5, suffix_array5)
    occurrences_z_algorithm5 = search_pattern_z_algorithm(text5, pattern5)
    print(f"Pattern '{pattern5}' found at indices (using Suffix Array) in '{text5}': {occurrences_suffix_array5}")
    print(f"Pattern '{pattern5}' found at indices (using Z-Algorithm) in '{text5}': {occurrences_z_algorithm5}")
