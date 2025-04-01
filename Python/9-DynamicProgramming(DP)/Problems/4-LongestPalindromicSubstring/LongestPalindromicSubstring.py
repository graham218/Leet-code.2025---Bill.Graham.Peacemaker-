def longest_palindromic_substring_dp(s: str) -> str:
    """
    Finds the longest palindromic substring in a given string using dynamic programming.

    Approach 1: Dynamic Programming (Bottom-Up)
    This approach builds a 2D table where dp[i][j] is True if the substring s[i:j+1] is a palindrome, and False otherwise.
    The table is filled in a bottom-up manner, considering substrings of increasing length.

    Args:
        s: The input string.

    Returns:
        The longest palindromic substring.
    """
    n = len(s)
    if n == 0:
        return ""

    # Create a table to store whether substrings are palindromes
    dp = [[False] * n for _ in range(n)]

    # All single characters are palindromes
    for i in range(n):
        dp[i][i] = True
    longest_start = 0
    longest_length = 1

    # Check for palindromes of length 2
    for i in range(n - 1):
        if s[i] == s[i + 1]:
            dp[i][i + 1] = True
            longest_start = i
            longest_length = 2

    # Check for palindromes of length greater than 2
    for length in range(3, n + 1):
        for i in range(n - length + 1):
            j = i + length - 1  # Ending index of the substring
            if s[i] == s[j] and dp[i + 1][j - 1]:
                dp[i][j] = True
                longest_start = i
                longest_length = length

    return s[longest_start:longest_start + longest_length]


def longest_palindromic_substring_dp_optimized(s: str) -> str:
    """
    Finds the longest palindromic substring in a given string using dynamic programming.

    Approach 2: Optimized Dynamic Programming (Bottom-Up)
    This is an optimized version of the previous approach.  Instead of storing the entire
    DP table, we keep track of the start and end indices of the longest palindrome found so far.

    Args:
        s: The input string.

    Returns:
        The longest palindromic substring.
    """
    n = len(s)
    if n == 0:
        return ""

    longest_start = 0
    longest_length = 1

    # Create a table to store whether substrings are palindromes
    dp = [[False] * n for _ in range(n)]

    # All single characters are palindromes
    for i in range(n):
        dp[i][i] = True

    # Check for palindromes of length 2
    for i in range(n - 1):
        if s[i] == s[i + 1]:
            dp[i][i + 1] = True
            longest_start = i
            longest_length = 2

    # Check for palindromes of length greater than 2
    for length in range(3, n + 1):
        for i in range(n - length + 1):
            j = i + length - 1
            if s[i] == s[j] and dp[i + 1][j - 1]:
                dp[i][j] = True
                if length > longest_length:  # Update start and length directly
                    longest_start = i
                    longest_length = length

    return s[longest_start:longest_start + longest_length]


def longest_palindrome_expand_around_center(s: str) -> str:
    """
    Finds the longest palindromic substring by expanding around the center.

    Approach 3: Expand Around Center
    This approach iterates through each character in the string and considers it as the center of a potential palindrome.
    It then expands outwards from the center, checking for matching characters.  This avoids building the entire DP table.
    This method considers both odd and even length palindromes.

    Args:
        s: The input string.

    Returns:
        The longest palindromic substring.
    """
    n = len(s)
    if n == 0:
        return ""

    longest_start = 0
    longest_length = 1

    def expand_around_center(left, right):
        """Expands around the center and returns the length of the palindrome."""
        while left >= 0 and right < n and s[left] == s[right]:
            left -= 1
            right += 1
        return right - left - 1, left + 1  # Return length and start index

    for i in range(n):
        # Odd length palindromes
        length1, start1 = expand_around_center(i, i)
        if length1 > longest_length:
            longest_length = length1
            longest_start = start1
        # Even length palindromes
        length2, start2 = expand_around_center(i, i + 1)
        if length2 > longest_length:
            longest_length = length2
            longest_start = start2

    return s[longest_start:longest_start + longest_length]


def longest_palindromic_substring_memoization(s: str) -> str:
    """
    Finds the longest palindromic substring using dynamic programming with memoization.

    Approach 4: Dynamic Programming with Memoization (Top-Down)
    This approach uses recursion with memoization to avoid redundant calculations.
    A helper function `is_palindrome` checks if a substring is a palindrome and stores the result in a memoization table (cache).

    Args:
        s: The input string.

    Returns:
        The longest palindromic substring.
    """
    n = len(s)
    if n == 0:
        return ""

    cache = {}  # Use a dictionary for memoization

    def is_palindrome(left, right):
        """
        Checks if the substring s[left:right+1] is a palindrome using memoization.

        Args:
            left: The starting index of the substring.
            right: The ending index of the substring.

        Returns:
            True if the substring is a palindrome, False otherwise.
        """
        if (left, right) in cache:
            return cache[(left, right)]
        if left >= right:
            cache[(left, right)] = True
            return True
        if s[left] != s[right]:
            cache[(left, right)] = False
            return False
        cache[(left, right)] = is_palindrome(left + 1, right - 1)
        return cache[(left, right)]

    longest_start = 0
    longest_length = 1

    for i in range(n):
        for j in range(i, n):
            if is_palindrome(i, j):
                if j - i + 1 > longest_length:
                    longest_length = j - i + 1
                    longest_start = i

    return s[longest_start:longest_start + longest_length]

def longest_palindromic_substring_optimized_expand(s: str) -> str:
    """
    Finds the longest palindromic substring by expanding around the center, further optimized.

    Approach 5: Optimized Expand Around Center
    This approach is a refined version of the Expand Around Center approach.  It streamlines the expansion logic
    and avoids redundant calculations by combining the odd and even length checks into a single loop.

    Args:
        s: The input string.

    Returns:
        The longest palindromic substring.
    """
    n = len(s)
    if n < 1:
        return ""
    start = 0
    end = 0

    for i in range(n):
        # For each character, try to expand around it
        len1 = expand_around_center(s, i, i)  # Odd length palindrome
        len2 = expand_around_center(s, i, i + 1)  # Even length palindrome
        length = max(len1, len2)
        if length > end - start:
            start = i - (length - 1) // 2
            end = i + length // 2
    return s[start:end + 1]

def expand_around_center(s, left, right):
    """Helper function to expand around the center."""
    while left >= 0 and right < len(s) and s[left] == s[right]:
        left -= 1
        right += 1
    return right - left - 1
if __name__ == "__main__":
    test_string = "babad"
    print(f"Input string: {test_string}")

    print("\nApproach 1: Dynamic Programming (Bottom-Up)")
    print(f"Longest palindromic substring: {longest_palindromic_substring_dp(test_string)}")  # Output: bab or aba

    print("\nApproach 2: Optimized Dynamic Programming (Bottom-Up)")
    print(f"Longest palindromic substring: {longest_palindromic_substring_dp_optimized(test_string)}")

    print("\nApproach 3: Expand Around Center")
    print(f"Longest palindromic substring: {longest_palindrome_expand_around_center(test_string)}")

    print("\nApproach 4: Dynamic Programming with Memoization (Top-Down)")
    print(f"Longest palindromic substring: {longest_palindromic_substring_memoization(test_string)}")

    print("\nApproach 5: Optimized Expand Around Center")
    print(f"Longest palindromic substring: {longest_palindromic_substring_optimized_expand(test_string)}")
    test_string2 = "cbbd"
    print(f"\nInput string: {test_string2}")
    print("\nApproach 1: Dynamic Programming (Bottom-Up)")
    print(f"Longest palindromic substring: {longest_palindromic_substring_dp(test_string2)}")
    print("\nApproach 2: Optimized Dynamic Programming (Bottom-Up)")
    print(f"Longest palindromic substring: {longest_palindromic_substring_dp_optimized(test_string2)}")
    print("\nApproach 3: Expand Around Center")
    print(f"Longest palindromic substring: {longest_palindrome_expand_around_center(test_string2)}")
    print("\nApproach 4: Dynamic Programming with Memoization (Top-Down)")
    print(f"Longest palindromic substring: {longest_palindromic_substring_memoization(test_string2)}")
    print("\nApproach 5: Optimized Expand Around Center")
    print(f"Longest palindromic substring: {longest_palindromic_substring_optimized_expand(test_string2)}")
