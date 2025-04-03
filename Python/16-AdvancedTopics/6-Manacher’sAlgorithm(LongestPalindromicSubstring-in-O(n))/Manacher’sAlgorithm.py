def manacher(s: str) -> str:
    """
    Manacher's Algorithm for finding the longest palindromic substring in linear time.

    Args:
        s: The input string.

    Returns:
        The longest palindromic substring in s.

    Example:
        >>> manacher("babad")
        'bab'
        >>> manacher("cbbd")
        'bb'
        >>> manacher("a")
        'a'
        >>> manacher("ac")
        'a'
        >>> manacher("racecar")
        'racecar'
        >>> manacher("madam")
        'madam'
        >>> manacher("level")
        'level'
    """
    # 1. Preprocess the string to handle even length palindromes.
    #    Insert a special character (e.g., '#') between each character
    #    and at the beginning and end.
    t = "#" + "#".join(list(s)) + "#"  # e.g., "babad" becomes "#b#a#b#a#d#"

    # 2. Create an array to store the palindrome lengths.
    n = len(t)
    p = [0] * n  # p[i] stores the radius of the longest palindrome centered at t[i]

    # 3. Initialize center and right boundary of the rightmost palindrome.
    center = 0
    right = 0

    # 4. Iterate through the preprocessed string.
    for i in range(n):
        # 5. Utilize symmetry to initialize p[i].
        if i < right:
            mirror = 2 * center - i  # Mirror position of i with respect to center
            p[i] = min(right - i, p[mirror])  # Take the minimum of the two possible values.

        # 6. Expand the palindrome centered at i.
        #   Try to expand, while still a valid palindrome
        while i - (1 + p[i]) >= 0 and i + (1 + p[i]) < n and t[i - (1 + p[i])] == t[i + (1 + p[i])]:
            p[i] += 1

        # 7. Update center and right boundary if necessary.
        if i + p[i] > right:
            center = i
            right = i + p[i]

    # 8. Find the maximum palindrome length and its center.
    max_len = 0
    center_index = 0
    for i in range(n):
        if p[i] > max_len:
            max_len = p[i]
            center_index = i

    # 9. Extract the longest palindromic substring from the original string.
    start = (center_index - max_len) // 2  # Map back to original string index. Integer division is crucial
    longest_palindrome = s[start : start + max_len]

    return longest_palindrome

if __name__ == "__main__":
    test_string = "babad"  # You can change this to any string you want to test with
    result = manacher(test_string)
    print(f"The longest palindromic substring of '{test_string}' is: '{result}'")
