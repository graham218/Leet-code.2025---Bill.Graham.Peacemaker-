def rabin_karp(text, pattern, prime=101):
    """
    Rabin-Karp algorithm for string matching.

    Args:
        text: The text string to search within.
        pattern: The pattern string to search for.
        prime: A prime number used for hashing.  It's important to choose a
               prime number to minimize collisions.  Common choices are 101,
               31, or larger primes.  If you're dealing with a very large
               character set (like extended Unicode), you might need a larger
               prime.

    Returns:
        A list of starting indices where the pattern is found in the text.
        Returns an empty list if the pattern is not found.
    """
    n = len(text)
    m = len(pattern)
    occurrences = []

    if m > n:
        return occurrences  # Pattern cannot be longer than text.

    # Calculate the hash value of the pattern and the initial hash
    # of the first window of the text.
    pattern_hash = 0
    text_hash = 0
    for i in range(m):
        pattern_hash = (pattern_hash * prime + ord(pattern[i]))  # Rolling Hash
        text_hash = (text_hash * prime + ord(text[i]))

    # Precompute the value of prime^(m-1) for efficient rolling hash update
    h = pow(prime, m - 1) # Removed float('inf'),  pow with 3 args requires integers

    # Slide the window through the text
    for i in range(n - m + 1):
        # Check if the hash values match
        if pattern_hash == text_hash:
            # Verify character by character to avoid spurious hits (collisions)
            if text[i:i + m] == pattern:
                occurrences.append(i)

        # Calculate the hash value for the next window of the text.
        # This is the "rolling hash" part: we subtract the contribution of
        # the outgoing character and add the contribution of the incoming character.
        if i < n - m:
            text_hash = (text_hash - ord(text[i]) * h) * prime + ord(text[i + m])

    return occurrences

def rabin_karp_example():
    """
    Example usage of the Rabin-Karp algorithm.
    """
    text = "ABABDABACDABABCABAB"
    pattern = "ABABC"
    prime_number = 101  # You can experiment with different prime numbers

    result = rabin_karp(text, pattern, prime_number)
    if result:
        print(f"Pattern found at indices: {result}")
    else:
        print("Pattern not found.")

    text2 = "This is a test string for the Rabin-Karp algorithm.  The algorithm is efficient."
    pattern2 = "algorithm"
    result2 = rabin_karp(text2, pattern2)
    print(f"Pattern '{pattern2}' found at indices: {result2} in text2")

    text3 = "AABAACAADAABAABA"
    pattern3 = "AABA"
    result3 = rabin_karp(text3, pattern3)
    print(f"Pattern '{pattern3}' found at indices: {result3} in text3")

    text4 = "The quick brown fox jumps over the lazy fox."
    pattern4 = "fox"
    result4 = rabin_karp(text4, pattern4)
    print(f"Pattern '{pattern4}' found at indices: {result4} in text4")


if __name__ == "__main__":
    rabin_karp_example()
