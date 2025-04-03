def compute_lps_array(pattern):
    """
    Computes the Longest Prefix Suffix (LPS) array for a given pattern.

    The LPS array is used in the KMP algorithm to efficiently find occurrences of
    the pattern in a text.  LPS[i] stores the length of the longest proper prefix
    of pattern[0...i] which is also a suffix of pattern[0...i].

    Args:
        pattern: The pattern string (str).

    Returns:
        A list (list of int) representing the LPS array.
    """
    m = len(pattern)
    lps = [0] * m  # Initialize LPS array with 0s
    length = 0  # Length of the previous longest prefix suffix
    i = 1  # Index for the pattern string

    # lps[0] is always 0, so we start from i = 1
    lps[0] = 0

    while i < m:
        if pattern[i] == pattern[length]:
            # If characters match, increment length and update LPS array
            length += 1
            lps[i] = length
            i += 1
        else:
            # Characters don't match
            if length != 0:
                # Backtrack using the information from the LPS array itself
                length = lps[length - 1]
                # Note that we do not increment i here
            else:
                # If length is 0, there is no previous longest prefix suffix
                lps[i] = 0
                i += 1
    return lps


def kmp_search(text, pattern):
    """
    Implements the Knuth-Morris-Pratt (KMP) algorithm to find occurrences of a
    pattern within a text.

    Args:
        text: The text string to search within (str).
        pattern: The pattern string to search for (str).

    Returns:
        A list (list of int) containing the starting indices of all occurrences
        of the pattern in the text. Returns an empty list if no occurrences are found.
    """
    n = len(text)
    m = len(pattern)
    lps = compute_lps_array(pattern)  # Precompute the LPS array
    i = 0  # Index for the text string
    j = 0  # Index for the pattern string
    occurrences = []  # List to store starting indices of matches

    while i < n:
        if pattern[j] == text[i]:
            # If characters match, move to the next characters in both text and pattern
            i += 1
            j += 1

        if j == m:
            # If the entire pattern is matched
            occurrences.append(i - j)  # Store the starting index of the match
            j = lps[j - 1]  # Look for the next possible match
        elif i < n and pattern[j] != text[i]:
            # If characters don't match
            if j != 0:
                # Use the LPS array to avoid unnecessary comparisons
                j = lps[j - 1]
            else:
                # If j is 0, simply move to the next character in the text
                i += 1
    return occurrences

def kmp_search_with_count(text, pattern):
    """
    Implements the Knuth-Morris-Pratt (KMP) algorithm to find occurrences of a
    pattern within a text, and counts the number of occurrences.

    Args:
        text: The text string to search within (str).
        pattern: The pattern string to search for (str).

    Returns:
        A tuple (int, list of int). The first element is the number of occurrences
        of the pattern in the text. The second element is a list containing the
        starting indices of all occurrences.
    """
    n = len(text)
    m = len(pattern)
    lps = compute_lps_array(pattern)
    i = 0
    j = 0
    occurrences = []
    count = 0

    while i < n:
        if pattern[j] == text[i]:
            i += 1
            j += 1

        if j == m:
            occurrences.append(i - j)
            count += 1
            j = lps[j - 1]
        elif i < n and pattern[j] != text[i]:
            if j != 0:
                j = lps[j - 1]
            else:
                i += 1
    return count, occurrences

if __name__ == "__main__":
    # Example usage of the KMP search functions
    text = "ABABDABACDABABCABAB"
    pattern = "ABABCABAB"

    # Find all occurrences and print the starting indices
    occurrences = kmp_search(text, pattern)
    print(f"Pattern '{pattern}' found at indices: {occurrences}")

    # Find all occurrences and print the count
    count, occurrences = kmp_search_with_count(text, pattern)
    print(f"Pattern '{pattern}' occurs {count} times in text.  Indices: {occurrences}")

    text2 = "THIS IS A TEST TEXT FOR KMP ALGORITHM"
    pattern2 = "TEST"
    occurrences2 = kmp_search(text2, pattern2)
    print(f"Pattern '{pattern2}' found at indices: {occurrences2}")
