def compute_lps_array(pattern):
    """
    Computes the Longest Prefix Suffix (LPS) array for the given pattern.

    The LPS array is used in the KMP algorithm to efficiently find occurrences of a
    pattern within a text.  lps[i] stores the length of the longest prefix of
    pattern[0...i] which is also a suffix of pattern[0...i].

    For example:
    - For pattern "ABABDABACD", the LPS array is [0, 0, 1, 2, 0, 1, 2, 3, 0, 0].
    - For pattern "AAAA", the LPS array is [0, 1, 2, 3].
    - For pattern "ABCDE", the LPS array is [0, 0, 0, 0, 0].

    Args:
        pattern: The pattern string (str).

    Returns:
        A list (list of int) representing the LPS array.
        Returns an empty list if the pattern is empty.
    """
    m = len(pattern)
    lps = [0] * m  # Initialize LPS array with 0s.  lps[i] will store the longest prefix
    # that is also a suffix of pattern[0...i].
    length = 0  # Length of the previous longest prefix suffix. This variable keeps
    # track of the length of the longest prefix that is also a suffix
    # of the current prefix being considered.
    i = 1  # Index for the current character in the pattern.  We start from index 1
    # because lps[0] is always 0.

    # Base case: lps[0] is always 0 because there is no proper prefix for the first character.
    lps[0] = 0

    # Calculate LPS array
    while i < m:
        if pattern[i] == pattern[length]:
            # If the current character matches the character at the 'length' position,
            # it means we have found a longer prefix suffix.
            length += 1  # Increment the length of the longest prefix suffix.
            lps[i] = length  # Store the length in the LPS array.
            i += 1  # Move to the next character in the pattern.
        else:
            # If the characters do not match, we need to check for shorter prefix suffixes.
            if length != 0:
                # This is the crucial part of the KMP algorithm.  Instead of starting
                # the comparison from the beginning of the pattern, we use the
                # information stored in the LPS array to backtrack efficiently.
                # We set 'length' to the value stored in lps[length-1]. This tells us
                # the length of the next smaller prefix that is also a suffix.
                length = lps[length - 1]
                # Note: We do not increment i here. We stay at the same character i
                # and compare it with the shorter prefix.
            else:
                # If length is 0, it means there is no prefix that is also a suffix,
                # so we set lps[i] to 0 and move to the next character.
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
    occurrences = []  # List to store starting indices of matches

    if m == 0:
        return [0] if n == 0 else [] # handle empty pattern edge case. If pattern is empty
        # and text is empty, return [0]. If pattern is empty
        # and text is not empty, return [].
    if n == 0:
        return [] # handle empty text edge case. If text is empty, there can be no occurrences.

    # Compute the LPS array for the pattern.  This is a pre-processing step that
    # optimizes the search.
    lps = compute_lps_array(pattern)

    i = 0  # Index for the text.
    j = 0  # Index for the pattern.

    while i < n:
        if text[i] == pattern[j]:
            # If the current characters match, move to the next characters in both
            # the text and the pattern.
            i += 1
            j += 1

        if j == m:
            # If j reaches the length of the pattern, it means we have found a complete match.
            occurrences.append(i - j)  # Store the starting index of the match.
            # i - j gives the index in 'text' where the match starts.
            j = lps[j - 1]  # Reset j to check for overlapping occurrences.  For example,
            # if text is "AAAAAAA" and pattern is "AAAA", after finding the
            # first match at index 0, we reset j to lps[3] which is 3,
            # so we find the next match at index 1.
        elif i < n and text[i] != pattern[j]:
            # If the characters do not match and we haven't reached the end of the text:
            if j != 0:
                # This is where the LPS array is used for optimization.  Instead of
                # resetting j to 0 and starting the comparison from the beginning of
                # the pattern, we use the LPS array to find the longest prefix of the
                # pattern that is also a suffix of the already matched part of the text.
                j = lps[j - 1]
            else:
                # If j is 0, it means there was no previous match, so we move to the
                # next character in the text.
                i += 1
    return occurrences

if __name__ == "__main__":
    # Example usage of the kmp_search function
    text1 = "ABABDABACDABABCABAB"
    pattern1 = "ABABCABAB"
    result1 = kmp_search(text1, pattern1)
    print(f"Text: {text1}")
    print(f"Pattern: {pattern1}")
    print(f"Occurrences: {result1}")  # Output: Occurrences: [10]

    text2 = "AAAAAAA"
    pattern2 = "AAAA"
    result2 = kmp_search(text2, pattern2)
    print(f"\nText: {text2}")
    print(f"Pattern: {pattern2}")
    print(f"Occurrences: {result2}")  # Output: Occurrences: [0, 1, 2, 3]

    text3 = "THIS IS A TEST TEXT"
    pattern3 = "TEST"
    result3 = kmp_search(text3, pattern3)
    print(f"\nText: {text3}")
    print(f"Pattern: {pattern3}")
    print(f"Occurrences: {result3}") # Output: Occurrences: [10]

    text4 = "aabaabaaa"
    pattern4 = "aaba"
    result4 = kmp_search(text4, pattern4)
    print(f"\nText: {text4}")
    print(f"Pattern: {pattern4}")
    print(f"Occurrences: {result4}") # Output:  [0, 3]
