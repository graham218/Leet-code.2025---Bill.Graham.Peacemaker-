def manachers_algorithm_advanced(s: str) -> str:
    """
    Manacher's Algorithm for finding the longest palindromic substring in O(n) time.
    This version includes more detailed comments, debugging print statements,
    and handles edge cases robustly.

    Args:
        s: The input string.

    Returns:
        The longest palindromic substring.

    Raises:
        TypeError: If the input is not a string.
        ValueError: If the input string is None.
    """
    if not isinstance(s, str):
        raise TypeError("Input must be a string.")
    if s is None:
        raise ValueError("Input string cannot be None.")

    if not s:  # Handle empty string case
        print("Input string is empty. Returning empty string.")
        return ""

    # 1. Preprocess the string to handle even length palindromes.
    #    Insert a special character (e.g., '#') between each character
    #    and at the beginning and end.  This transforms the string
    #    into a form where all palindromes have odd length.
    processed_s = '#' + '#'.join(list(s)) + '#'
    print(f"Processed string: {processed_s}")

    # 2. Initialize variables.
    n = len(processed_s)
    # radius[i] stores the radius of the longest palindrome centered at i
    radius = [0] * n
    center = 0  # Center of the current rightmost palindrome
    right = 0   # Right boundary of the current rightmost palindrome
    max_len = 0  # Length of the longest palindrome found so far
    max_center = 0 # Center of the longest palindrome found so far

    print(f"Initialized: n = {n}, radius = {radius}, center = {center}, right = {right}, max_len = {max_len}, max_center = {max_center}")

    # 3. Iterate through the processed string.
    for i in range(n):
        print(f"\n--- Processing index i = {i} ---")
        # 3.1. Use symmetry to initialize radius[i].
        #      If i is within the right boundary of the current rightmost
        #      palindrome, we can use the mirror property to get a lower bound
        #      for radius[i].  The mirror position is calculated with respect to the center.
        mirror = 2 * center - i  # Mirror position of i with respect to center
        print(f"Mirror of i ({i}) with respect to center ({center}): {mirror}")
        if i < right:
            radius[i] = min(right - i, radius[mirror])
            print(f"i ({i}) is within right boundary ({right}). Initial radius[{i}] = min({right} - {i}, radius[{mirror}]) = {radius[i]}")
        else:
            print(f"i ({i}) is outside right boundary ({right}). Initial radius[{i}] = 0")

        # 3.2. Expand the palindrome centered at i.
        #      Try to expand the palindrome centered at i by comparing characters
        #      on the left and right.
        left = i - (1 + radius[i])
        right_bound = i + (1 + radius[i])
        print(f"Initial left: {left}, right_bound: {right_bound}")
        while left >= 0 and right_bound < n and processed_s[left] == processed_s[right_bound]:
            radius[i] += 1
            left -= 1
            right_bound += 1
            print(f"Expanding: left = {left}, right_bound = {right_bound}, radius[{i}] = {radius[i]}")

        # 3.3. Update the center and right boundary of the current rightmost
        #      palindrome if necessary.  This is crucial for the algorithm's efficiency.
        if i + radius[i] > right:
            center = i
            right = i + radius[i]
            print(f"Updated center: {center}, right: {right} (i + radius[i] = {i + radius[i]})")

        # 3.4. Update the maximum palindrome length and center.
        if radius[i] > max_len:
            max_len = radius[i]
            max_center = i
            print(f"New max_len: {max_len}, max_center: {max_center}")

        print(f"End of iteration i = {i}: radius = {radius}, center = {center}, right = {right}")

    print(f"\nFinal radius array: {radius}")
    print(f"Max palindrome center: {max_center}, Max palindrome length: {max_len}")

    # 4. Extract the longest palindromic substring from the original string.
    #    The start index in the original string is calculated using the center
    #    and radius of the longest palindrome in the processed string.
    start = (max_center - max_len) // 2
    longest_palindrome = s[start:start + max_len]
    print(f"Start index in original string: {start}")
    print(f"Longest palindromic substring: {longest_palindrome}")

    return longest_palindrome
def test_manachers_algorithm():
    """
    Test function for Manacher's Algorithm with various test cases.
    """
    print("\n--- Testing Manacher's Algorithm ---")
    test_cases = [
        "babad",
        "cbbd",
        "a",
        "ac",
        "racecar",
        "madam",
        "level",
        "rotor",
        "noon",
        "aabaabaa",
        "abaxyzzyxf",
        "substring",
        "bananas",
        "million",
        " ", #single space
        "",  # Empty string
        "aaaaaaaaaa", #Long repeated string
        "redder",
        "civic",
        "stats",
    ]

    for s in test_cases:
        print(f"\nTesting with input string: '{s}'")
        try:
            result = manachers_algorithm_advanced(s)
            print(f"Longest palindrome: '{result}'")
        except Exception as e:
            print(f"Error: {e}")

def main():
    """
    Main function to run Manacher's Algorithm and demonstrate its usage.
    """
    test_manachers_algorithm() # Run the tests.

    # Example Usage in Real-World Applications:
    print("\n--- Real-World Applications ---")
    # 1. Bioinformatics - Finding palindromic sequences in DNA
    dna_sequence = "AGCTAGCTGAATTCCGAATTCGCTAGC"
    palindrome_dna = manachers_algorithm_advanced(dna_sequence)
    print(f"1. DNA Sequence: {dna_sequence}, Longest Palindromic Subsequence: {palindrome_dna}")

    # 2. Text Processing - Identifying palindromic words or phrases
    text = "A man, a plan, a canal: Panama"
    # Remove non-alphanumeric characters and convert to lowercase
    processed_text = ''.join(c for c in text if c.isalnum()).lower()
    palindrome_text = manachers_algorithm_advanced(processed_text)
    print(f"2. Text: '{text}', Longest Palindromic Substring: '{palindrome_text}'")

    # 3. Data Compression - Palindromes can be used for data compression (though not the most efficient)
    data = "abracadabrabarbarabrabracadabra"
    palindrome_data = manachers_algorithm_advanced(data)
    print(f"3. Data: '{data}', Longest Palindromic Substring: '{palindrome_data}'")

    # 4. Image Processing (Finding symmetric patterns) -  Although not a direct application,
    #    the core logic can be adapted.  For example, you could represent pixel
    #    intensities in a 1D array along a row or column and look for palindromic
    #    patterns of pixel intensities.  This is a simplified example.  Real image
    #    processing for symmetry would be much more complex and typically 2D.
    image_data_1d = [100, 120, 150, 120, 100, 200, 250, 200, 250, 200] # Example 1D image data
    image_data_str = ''.join(map(chr, image_data_1d))  # Convert to string (for simplicity of using Manacher's)
    palindrome_image = manachers_algorithm_advanced(image_data_str)
    print(f"4. 1D Image Data: {image_data_1d},  Longest Palindromic Substring: (Reprsenting Pixel Data) '{palindrome_image}'")

    image_data_1d_2 = [200, 210, 220, 210, 200, 50, 60, 50]
    image_data_str_2 = ''.join(map(chr, image_data_1d_2))
    palindrome_image_2 = manachers_algorithm_advanced(image_data_str_2)
    print(f"5. 1D Image Data 2: {image_data_1d_2}, Longest Palindromic Substring: (Representing Pixel Data) '{palindrome_image_2}'")
if __name__ == "__main__":
    main()
