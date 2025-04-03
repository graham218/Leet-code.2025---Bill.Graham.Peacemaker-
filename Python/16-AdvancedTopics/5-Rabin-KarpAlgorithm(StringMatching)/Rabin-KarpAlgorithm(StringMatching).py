def rabin_karp(text, pattern):
    """
    Implements the Rabin-Karp algorithm for string matching.

    Args:
        text: The text string to search within.
        pattern: The pattern string to search for.

    Returns:
        A list of starting indices where the pattern is found in the text.
        Returns an empty list if the pattern is not found.
    """
    n = len(text)
    m = len(pattern)
    if m > n:
        return []  # Pattern cannot be longer than the text

    # Base prime number for hashing
    prime = 101  # You can experiment with different prime numbers
    # Calculate the hash value of the pattern
    pattern_hash = 0
    for i in range(m):
        pattern_hash = (pattern_hash * prime + ord(pattern[i])) % n

    # Calculate the hash value of the first window of the text
    text_hash = 0
    for i in range(m):
        text_hash = (text_hash * prime + ord(text[i])) % n

    occurrences = []

    # Slide the window through the text
    for i in range(n - m + 1):
        # If the hash values match, compare the strings character by character
        if pattern_hash == text_hash:
            match = True
            for j in range(m):
                if text[i + j] != pattern[j]:
                    match = False
                    break
            if match:
                occurrences.append(i)  # Add the starting index to the result

        # Calculate the hash value for the next window of the text
        if i < n - m:
            text_hash = (text_hash - ord(text[i]) * (prime ** (m - 1))) % n
            text_hash = (text_hash * prime + ord(text[i + m])) % n
            # Ensure the hash value is non-negative
            if text_hash < 0:
                text_hash += n

    return occurrences

def main():
    """
    Main function to demonstrate the Rabin-Karp algorithm.
    """
    text = "ABABDABACDABABCABAB"
    pattern = "ABABCABAB"
    result = rabin_karp(text, pattern)
    if result:
        print(f"Pattern found at indices: {result}")
    else:
        print("Pattern not found in the text.")

    text2 = "This is a test string for testing the Rabin-Karp algorithm."
    pattern2 = "test"
    result2 = rabin_karp(text2, pattern2)
    if result2:
        print(f"Pattern found at indices: {result2}")
    else:
        print("Pattern not found in the text.")

    text3 = "AAAAAAA"
    pattern3 = "AAA"
    result3 = rabin_karp(text3, pattern3)
    if result3:
        print(f"Pattern found at indices: {result3}")
    else:
        print("Pattern not found in the text.")

    text4 = "abcdefgh"
    pattern4 = "xyz"
    result4 = rabin_karp(text4, pattern4)
    if result4:
        print(f"Pattern found at indices: {result4}")
    else:
        print("Pattern not found in the text.")

    text5 = ""
    pattern5 = ""
    result5 = rabin_karp(text5, pattern5)
    if result5:
        print(f"Pattern found at indices: {result5}")
    else:
        print("Pattern not found in the text.")


if __name__ == "__main__":
    main()

