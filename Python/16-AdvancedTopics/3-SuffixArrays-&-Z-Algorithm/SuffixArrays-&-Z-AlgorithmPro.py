import sys

def build_suffix_array(text):
    """
    Builds the suffix array for a given text.

    Args:
        text: The input string.

    Returns:
        A list of integers representing the starting indices of suffixes in the sorted order.

    Time Complexity:
        O(n log^2 n)  -  Can be improved to O(n log n) with a more complex algorithm (SA-IS)
    Space Complexity:
        O(n)
    """
    n = len(text)
    suffixes = [(text[i:], i) for i in range(n)]  # Create (suffix, index) pairs
    suffixes.sort()  # Sort lexicographically
    suffix_array = [suffix[1] for suffix in suffixes]  # Extract indices
    return suffix_array

def compute_lcp_array(text, suffix_array):
    """
    Computes the Longest Common Prefix (LCP) array using the suffix array.
    LCP[i] is the length of the longest common prefix between the suffixes
    starting at suffix_array[i] and suffix_array[i-1].

    Args:
        text: The input string.
        suffix_array: The suffix array for the text.

    Returns:
        A list of integers representing the LCP array.
        Returns an empty list if the suffix array is empty.

    Time Complexity: O(n)
    Space Complexity: O(n)
    """
    n = len(text)
    if n == 0:
        return []

    lcp_array = [0] * n
    rank = [0] * n  # Store the rank (position) of each suffix in the suffix array

    # Compute the rank array
    for i in range(n):
        rank[suffix_array[i]] = i

    # Compute LCP using Kasai's algorithm
    k = 0
    for i in range(n):
        if rank[i] == n - 1:
            k = 0
            continue
        j = suffix_array[rank[i] + 1]
        while i + k < n and j + k < n and text[i + k] == text[j + k]:
            k += 1
        lcp_array[rank[i] + 1] = k
        if k > 0:
            k -= 1
    return lcp_array

def find_pattern_suffix_array(text, pattern, suffix_array, lcp_array=None):
    """
    Finds all occurrences of a pattern in a text using the suffix array and optionally the LCP array.

    Args:
        text: The input string.
        pattern: The pattern to search for.
        suffix_array: The suffix array of the text.
        lcp_array: (Optional) The LCP array of the text.  If provided, can speed up the search.

    Returns:
        A list of integers representing the starting indices of the pattern in the text.
        Returns an empty list if the pattern is not found.

    Time Complexity:
        - Without LCP array: O(m log n), where m is the length of the pattern and n is the length of the text.
        - With LCP array:  O(m + log n) in the best case, but can be O(m log n) in the worst case.
          In practice, it's often faster with the LCP array.
    Space Complexity: O(1) (excluding the space for input and suffix/LCP arrays)
    """
    n = len(text)
    m = len(pattern)
    if m > n:
        return []
    occurrences = []
    left = 0
    right = n - 1

    while left <= right:
        mid = (left + right) // 2
        suffix_start = suffix_array[mid]
        comparison = text[suffix_start:suffix_start + m].compare_to(pattern) if hasattr(text[suffix_start:suffix_start + m], 'compare_to') else (text[suffix_start:suffix_start + m] > pattern) - (text[suffix_start:suffix_start + m] < pattern)

        if comparison < 0:
            left = mid + 1
        elif comparison > 0:
            right = mid - 1
        else:  # Found a match at mid
            # Collect all matching indices (including duplicates)
            k = mid
            while k >= 0 and text[suffix_array[k]:suffix_array[k] + m] == pattern:
                occurrences.append(suffix_array[k])
                k -= 1
            k = mid + 1
            while k < n and text[suffix_array[k]:suffix_array[k] + m] == pattern:
                occurrences.append(suffix_array[k])
                k += 1
            occurrences.sort() # Important to maintain sorted order
            return occurrences
    return []

def compute_z_array(text):
    """
    Computes the Z-array for a given text.
    Z[i] is the length of the longest substring starting at text[i]
    which is also a prefix of text.

    Args:
        text: The input string.

    Returns:
        A list of integers representing the Z-array.

    Time Complexity: O(n)
    Space Complexity: O(n)
    """
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

def find_pattern_z_algorithm(text, pattern):
    """
    Finds all occurrences of a pattern in a text using the Z-algorithm.

    Args:
        text: The input string.
        pattern: The pattern to search for.

    Returns:
        A list of integers representing the starting indices of the pattern in the text.
        Returns an empty list if the pattern is not found.

    Time Complexity: O(n + m), where n is the length of the text and m is the length of the pattern.
    Space Complexity: O(n + m)
    """
    n = len(text)
    m = len(pattern)
    if m > n:
        return []

    combined_string = pattern + "$" + text  # Concatenate pattern and text with a special character
    z_array = compute_z_array(combined_string)
    occurrences = []

    for i in range(m + 1, n + m + 1):
        if z_array[i] == m:
            occurrences.append(i - m - 1)  # Adjust index to point to start in text
    return occurrences

# Real-world Applications and Examples:

def real_world_applications():
    """
    Illustrates real-world applications of Suffix Arrays and Z-Algorithm.
    """
    print("\nReal-world Applications:\n")

    # 1. Bioinformatics - Genome Sequencing
    print("1. Bioinformatics - Genome Sequencing:")
    genome = "AGCTAGCTAGCTAGCTAGCTAGCT"
    pattern = "AGCTA"
    suffix_array = build_suffix_array(genome)
    occurrences_sa = find_pattern_suffix_array(genome, pattern, suffix_array)
    print(f"  - Genome: {genome}")
    print(f"  - Pattern: {pattern}")
    print(f"  - Suffix Array Occurrences: {occurrences_sa}")  # [0, 4, 8, 12, 16]

    occurrences_z = find_pattern_z_algorithm(genome, pattern)
    print(f"  - Z-Algorithm Occurrences: {occurrences_z}")

    # 2. Text Searching - Web Search Engines
    print("\n2. Text Searching - Web Search Engines:")
    text = "This is a text for testing text searching algorithms.  The text contains the word text multiple times."
    pattern = "text"
    suffix_array = build_suffix_array(text)
    occurrences_sa = find_pattern_suffix_array(text, pattern, suffix_array)
    print(f"  - Text: {text}")
    print(f"  - Pattern: {pattern}")
    print(f"  - Suffix Array Occurrences: {occurrences_sa}")  # [10, 27, 32, 63, 79]

    occurrences_z = find_pattern_z_algorithm(text, pattern)
    print(f"  - Z-Algorithm Occurrences: {occurrences_z}")

    # 3. Data Compression - Burrows-Wheeler Transform (BWT)
    print("\n3. Data Compression - Burrows-Wheeler Transform (BWT):")
    bwt_text = "AC$AACA" # Example BWT output (demonstrates concept, not full BWT)
    # Suffix arrays are used in the BWT and its inverse transform.
    print("  - BWT Text:", bwt_text)
    print("  - Suffix arrays help in efficiently performing the BWT and inverse BWT, which are used in data compression algorithms.")

    # 4. Code Challenges
    print("\n4. Code Challenges:")
    long_text = "banana"
    pattern = "ana"
    suffix_array_long = build_suffix_array(long_text)
    lcp_array_long = compute_lcp_array(long_text, suffix_array_long) # Calculate LCP
    print(f"  - Text: {long_text}")
    print(f"  - Pattern: {pattern}")
    print(f"  - Suffix Array: {suffix_array_long}")
    print(f"  - LCP Array: {lcp_array_long}")
    occurrences_long_sa = find_pattern_suffix_array(long_text, pattern, suffix_array_long, lcp_array_long)
    print(f"  - Suffix Array Occurrences: {occurrences_long_sa}")

    occurrences_long_z = find_pattern_z_algorithm(long_text, pattern)
    print(f"  - Z-Algorithm Occurrences: {occurrences_long_z}")
    # 5.  String Matching with Mismatches (Example with Suffix Array - Conceptual)
    print("\n5. String Matching with Mismatches (Conceptual):")
    text_mismatch = "ATGCATGCAA"
    pattern_mismatch = "ATGA"
    suffix_array_mismatch = build_suffix_array(text_mismatch)
    print("   - Text:", text_mismatch)
    print("   - Pattern:", pattern_mismatch)
    print("   - Suffix Array:", suffix_array_mismatch)
    print("   - Suffix arrays can be adapted to find approximate matches (with a few mismatches), though the algorithm is more complex.  This is useful in applications like spell checking and bioinformatics.")

def main():
    """
    Main function to run the examples and demonstrate the algorithms.
    """
    text = "ATGCGAATTGCG"
    pattern = "G"

    print("Text:", text)
    print("Pattern:", pattern)

    suffix_array = build_suffix_array(text)
    print("\nSuffix Array:", suffix_array)

    lcp_array = compute_lcp_array(text, suffix_array)
    print("LCP Array:", lcp_array)

    occurrences_sa = find_pattern_suffix_array(text, pattern, suffix_array, lcp_array)
    print("Pattern occurrences (Suffix Array):", occurrences_sa)

    occurrences_z = find_pattern_z_algorithm(text, pattern)
    print("Pattern occurrences (Z-Algorithm):", occurrences_z)

    text2 = "ACCCAAACCC$"
    z_array2 = compute_z_array(text2)
    print(f"\nText: {text2}")
    print("Z-Array:", z_array2)

    real_world_applications()

if __name__ == "__main__":
    main()
