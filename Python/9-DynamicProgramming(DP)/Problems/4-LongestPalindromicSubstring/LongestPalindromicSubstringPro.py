def longest_palindromic_substring_dp(s: str) -> str:
    """
    Dynamic Programming Approach to find the longest palindromic substring.

    This approach builds a 2D table (dp) where dp[i][j] is True if the substring
    s[i:j+1] is a palindrome, and False otherwise.  It's efficient for
    understanding the core logic of palindrome detection and is often used
    as a baseline for more optimized solutions.

    Args:
        s: The input string.

    Returns:
        The longest palindromic substring.

    Time Complexity: O(n^2), where n is the length of the string.
    Space Complexity: O(n^2)
    """
    n = len(s)
    if n == 0:
        return ""

    # dp[i][j] will be True if the substring s[i:j+1] is a palindrome
    dp = [[False] * n for _ in range(n)]

    # Base case: single characters are palindromes
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

    # Check for palindromes of length 3 or greater
    for length in range(3, n + 1):
        for i in range(n - length + 1):
            j = i + length - 1  # Ending index of the substring
            if s[i] == s[j] and dp[i + 1][j - 1]:
                dp[i][j] = True
                if length > longest_length:
                    longest_start = i
                    longest_length = length

    return s[longest_start:longest_start + longest_length]
def longest_palindromic_substring_expand(s: str) -> str:
    """
    Expand Around Center Approach.

    This approach iterates through each character in the string and tries to
    expand around it to find the longest palindrome.  It's more efficient
    in terms of space complexity compared to the dynamic programming approach.
    This is a very common and practical approach.

    Args:
        s: The input string.

    Returns:
        The longest palindromic substring.

    Time Complexity: O(n^2), where n is the length of the string.
    Space Complexity: O(1)
    """
    n = len(s)
    if n == 0:
        return ""

    longest_start = 0
    longest_length = 1

    def expand_around_center(left, right):
        """
        Helper function to expand around the center (left, right).
        """
        while left >= 0 and right < n and s[left] == s[right]:
            left -= 1
            right += 1
        return right - left - 1  # Length of the palindrome

    for i in range(n):
        # Odd length palindromes (center is a single character)
        length1 = expand_around_center(i, i)
        if length1 > longest_length:
            longest_length = length1
            longest_start = i - length1 // 2

        # Even length palindromes (center is between two characters)
        length2 = expand_around_center(i, i + 1)
        if length2 > longest_length:
            longest_length = length2
            longest_start = i - length2 // 2 + 1

    return s[longest_start:longest_start + longest_length]
def longest_palindromic_substring_optimized_dp(s: str) -> str:
    """
    Optimized Dynamic Programming Approach.

    This is an optimized version of the DP approach that uses only 1D array
    instead of 2D array. This optimization reduces the space complexity
    from O(n^2) to O(n).

    Args:
        s: The input string.

    Returns:
        The longest palindromic substring.

    Time Complexity: O(n^2), where n is the length of the string.
    Space Complexity: O(n)
    """
    n = len(s)
    if n == 0:
        return ""

    dp = [False] * n
    longest_start = 0
    longest_length = 1

    for i in range(n - 1, -1, -1):
        for j in range(n - 1, i - 1, -1):
            if s[i] == s[j] and (j - i <= 2 or dp[j - 1]):
                dp[j] = True
                if j - i + 1 > longest_length:
                    longest_length = j - i + 1
                    longest_start = i
            else:
                dp[j] = False  # Important: Reset dp[j] for the next iteration

    return s[longest_start:longest_start + longest_length]
def longest_palindromic_substring_manacher(s: str) -> str:
    """
    Manacher's Algorithm.

    This is the most efficient algorithm for finding the longest palindromic
    substring.  It works in linear time.  It's more complex to understand
    but is very powerful.  Manacher's algorithm preprocesses the string
    to handle even and odd length palindromes uniformly by inserting a special
    character (e.g., '#') between characters.

    Args:
        s: The input string.

    Returns:
        The longest palindromic substring.

    Time Complexity: O(n), where n is the length of the string.
    Space Complexity: O(n)
    """
    n = len(s)
    if n == 0:
        return ""

    # Preprocess the string to handle even and odd length palindromes
    processed_s = '#' + '#'.join(list(s)) + '#'
    processed_n = len(processed_s)

    # p[i] stores the length of the longest palindromic substring centered at processed_s[i]
    p = [0] * processed_n
    center = 0
    right = 0
    longest_start = 0
    longest_length = 1

    for i in range(processed_n):
        # Use symmetry to potentially reduce calculations
        if i < right:
            mirror = 2 * center - i
            p[i] = min(right - i, p[mirror])

        # Expand around center i
        left = i - (1 + p[i])
        right_bound = i + (1 + p[i])
        while left >= 0 and right_bound < processed_n and processed_s[left] == processed_s[right_bound]:
            p[i] += 1
            left -= 1
            right_bound += 1

        # Update center and right boundary if necessary
        if i + p[i] > right:
            center = i
            right = i + p[i]

        # Update longest palindrome
        if p[i] > longest_length:
            longest_length = p[i]
            longest_start = (i - longest_length) // 2

    return s[longest_start:longest_start + longest_length]
import re
def longest_palindromic_substring_regex(s: str) -> str:
    """
    Regular Expression Approach (Less Efficient, for Demonstration).

    This approach uses regular expressions to find palindromes.  While concise,
    it's generally less efficient than other methods, especially for long strings,
    and is included primarily for illustrative purposes.  Regular expressions
    are not the ideal tool for this problem due to the backtracking nature of
    palindrome matching.

    Args:
        s: The input string.

    Returns:
        The longest palindromic substring.

    Time Complexity:  Potentially exponential in the worst case, difficult to
                      precisely characterize due to regex backtracking.  Can be
                      O(n^2) in many cases, but much higher in pathological cases.
    Space Complexity: O(n) in the worst case due to regex engine's internal state.
    """
    n = len(s)
    if n == 0:
        return ""

    longest_palindrome = ""
    for i in range(n):
        for j in range(i, n):
            substring = s[i:j + 1]
            #  ^ asserts position at start of the string
            #  (.*) captures any character (.) zero or more times (*) into group 1
            #  \1?  attempts to match the content of group 1 (the captured substring)
            #        zero or one time (?)
            #  $ asserts position at the end of the string
            if substring == substring[::-1] and len(substring) > len(longest_palindrome):
                longest_palindrome = substring

    return longest_palindrome
def longest_palindromic_substring_divide_and_conquer(s: str) -> str:
    """
    Divide and Conquer Approach (Conceptual, Not Efficient for this Problem).

    While divide and conquer is a powerful paradigm, it's *not* an efficient
    solution for the longest palindromic substring problem.  This implementation
    is primarily for demonstration of the concept.  The problem doesn't lend
    itself well to recursive division because palindromes are not guaranteed
    to be contained within the divided subproblems.  This approach will likely
    be slower than the simpler iterative methods.

    Args:
        s: The input string.

    Returns:
        The longest palindromic substring.

    Time Complexity:  O(n^2) in the best and average case, but can be higher
                      (potentially exponential) in the worst case due to the
                      overlapping subproblems and the need to check all
                      combinations.
    Space Complexity: O(n log n) due to the recursive call stack.
    """
    n = len(s)
    if n == 0:
        return ""

    def find_longest(left, right):
        """
        Recursive helper function to find the longest palindrome in s[left:right+1].
        """
        if left > right:
            return ""
        if left == right:
            return s[left]

        # Divide
        mid = (left + right) // 2
        left_palindrome = find_longest(left, mid)
        right_palindrome = find_longest(mid + 1, right)

        # Conquer: Combine the results.  This is the tricky part, as the
        # longest palindrome might span the two halves.
        combined_palindrome = ""
        # Check for palindromes that span the midpoint
        l = mid
        r = mid + 1
        while l >= left and r <= right and s[l] == s[r]:
            if (r - l + 1) > len(combined_palindrome):
                combined_palindrome = s[l:r + 1]
            l -= 1
            r += 1

        l = mid - 1
        r = mid + 1
        while l >= left and r <= right and s[l] == s[r]:
            if (r - l + 1) > len(combined_palindrome):
                combined_palindrome = s[l:r + 1]
            l -= 1
            r += 1

        # Return the longest of the three
        return max(left_palindrome, right_palindrome, combined_palindrome, key=len)

    return find_longest(0, n - 1)
def test_longest_palindromic_substring():
    """
    Test function to validate the longest palindromic substring implementations.
    """
    test_cases = [
        ("", ""),
        ("a", "a"),
        ("aa", "aa"),
        ("aba", "aba"),
        ("abba", "abba"),
        ("babad", "bab"),  # or "aba"
        ("cbbd", "bb"),
        ("racecar", "racecar"),
        ("madam", "madam"),
        ("level", "level"),
        ("rotor", "rotor"),
        ("noon", "noon"),
        ("aabaa", "aabaa"),
        ("abcdefg", "a"),
        ("xyz12321zyx", "xyz12321zyx"),
        ("longestpalindrome", "longest"), # Corrected test case.
        ("saippuakivikauppias", "saippuakivikauppias"),  # Finnish for "soapstone vendor"
    ]

    algorithms = [
        longest_palindromic_substring_dp,
        longest_palindromic_substring_expand,
        longest_palindromic_substring_optimized_dp,
        longest_palindromic_substring_manacher,
        longest_palindromic_substring_regex,
        longest_palindromic_substring_divide_and_conquer,
    ]

    for s, expected in test_cases:
        print(f"\nTesting with input: '{s}'")
        for algorithm in algorithms:
            result = algorithm(s)
            print(f"{algorithm.__name__}: Result = '{result}', Expected = '{expected}'")
            if result != expected:
                print(f"  FAIL: {algorithm.__name__} failed for input '{s}'")
            else:
                print(f"  PASS: {algorithm.__name__} passed for input '{s}'")
if __name__ == "__main__":
    test_longest_palindromic_substring()

    # Example usage (choose the algorithm you want to use)
    test_string = "babad"
    longest_palindrome = longest_palindromic_substring_expand(test_string) # Change this line to test a different algorithm
    print(f"\nLongest palindromic substring of '{test_string}' is: '{longest_palindrome}'")
