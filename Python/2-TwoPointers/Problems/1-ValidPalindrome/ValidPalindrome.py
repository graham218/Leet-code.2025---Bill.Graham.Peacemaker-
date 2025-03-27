import re  # Import the regular expression module

# Valid Palindrome - Two Pointers Approaches
# The problem involves checking if a given string is a palindrome, considering only alphanumeric characters and ignoring cases.

# Approach 1: Two Pointers (Optimized for Space)
# Time Complexity: O(n), Space Complexity: O(1)
def is_palindrome_two_pointers(s):
    """
    Checks if a string is a palindrome using the two-pointers approach.

    Args:
        s (str): The input string.

    Returns:
        bool: True if the string is a palindrome, False otherwise.
    """
    left, right = 0, len(s) - 1  # Initialize two pointers, one at the start and one at the end
    while left < right:  # Continue as long as the left pointer is to the left of the right pointer
        while left < right and not s[left].isalnum():
            # Move the left pointer to the right until it points to an alphanumeric character
            left += 1
        while left < right and not s[right].isalnum():
            # Move the right pointer to the left until it points to an alphanumeric character
            right -= 1
        if s[left].lower() != s[right].lower():
            # If the characters at the two pointers (converted to lowercase) are not equal,
            # the string is not a palindrome
            return False
        left += 1  # Move the left pointer one step to the right
        right -= 1  # Move the right pointer one step to the left
    return True  # If the loop finishes without finding any mismatched characters, the string is a palindrome

# Approach 2: Using Regular Expressions and Reversed String
# Time Complexity: O(n), Space Complexity: O(n)
def is_palindrome_regex(s):
    """
    Checks if a string is a palindrome using regular expressions and string reversal.

    Args:
        s (str): The input string.

    Returns:
        bool: True if the string is a palindrome, False otherwise.
    """
    cleaned = re.sub(r'[^a-zA-Z0-9]', '', s).lower()  # Remove non-alphanumeric characters and convert to lowercase
    return cleaned == cleaned[::-1]  # Compare the cleaned string with its reversed version

# Approach 3: Using Stack (LIFO)
# Time Complexity: O(n), Space Complexity: O(n)
def is_palindrome_stack(s):
    """
    Checks if a string is a palindrome using a stack.

    Args:
        s (str): The input string.

    Returns:
        bool: True if the string is a palindrome, False otherwise.
    """
    stack = []  # Initialize an empty stack
    for char in s:
        if char.isalnum():
            stack.append(char.lower())  # Push alphanumeric characters (in lowercase) onto the stack
    # Now the stack contains the alphanumeric characters in forward order.
    for char in s:
        if char.isalnum() and (stack.pop() != char.lower()):
            return False
    return True

# Approach 4: Recursion (Not Recommended for Large Strings)
# Time Complexity: O(n), Space Complexity: O(n) (Due to recursive stack)
def is_palindrome_recursive(s, left=0, right=None):
    """
    Checks if a string is a palindrome using recursion.

    Args:
        s (str): The input string.
        left (int, optional): The left pointer. Defaults to 0.
        right (int, optional): The right pointer. Defaults to None.

    Returns:
        bool: True if the string is a palindrome, False otherwise.
    """
    if right is None:
        s = ''.join(c.lower() for c in s if c.isalnum())  # Clean the string and convert it to lowercase
        right = len(s) - 1  # Initialize the right pointer
    if left >= right:
        # Base case: if the left pointer crosses or meets the right pointer, it's a palindrome
        return True
    if s[left] != s[right]:
        # If the characters at the two pointers are not equal, it's not a palindrome
        return False
    # Recursive step: check the substring excluding the characters at the current pointers
    return is_palindrome_recursive(s, left + 1, right - 1)

# Approach 5: Deque (Efficient for Pop from Both Ends)
# Time Complexity: O(n), Space Complexity: O(n)
from collections import deque  # Import the deque class from the collections module

def is_palindrome_deque(s):
    """
    Checks if a string is a palindrome using a deque.

    Args:
        s (str): The input string.

    Returns:
        bool: True if the string is a palindrome, False otherwise.
    """
    d = deque()  # Initialize an empty deque
    for char in s:
        if char.isalnum():
            d.append(char.lower())  # Append alphanumeric characters (in lowercase) to the deque
    while len(d) > 1:
        # Continue as long as the deque has more than one element
        if d.popleft() != d.pop():
            # Compare the characters at both ends; if they are not equal, it's not a palindrome
            return False
    return True  # If the loop finishes without finding any mismatched characters, it's a palindrome

# Test Cases
test_cases = ["A man, a plan, a canal: Panama", "race a car", "", "abba", "No 'x' in Nixon"]

for i, test in enumerate(test_cases, 1):
    print(f"Test Case {i}: {test}")
    print("Two Pointers:", is_palindrome_two_pointers(test))
    print("Regex Method:", is_palindrome_regex(test))
    print("Stack Method:", is_palindrome_stack(test))
    print("Recursive Method:", is_palindrome_recursive(test))
    print("Deque Method:", is_palindrome_deque(test))
    print()
