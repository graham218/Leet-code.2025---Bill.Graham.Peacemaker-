'''
Valid Parentheses - Five Different Approaches

Problem Statement:
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
An input string is valid if:
  1. Open brackets must be closed by the same type of brackets.
  2. Open brackets must be closed in the correct order.
  3. Every close bracket has a corresponding open bracket of the same type.
'''

# 1. Using Stack (Standard Approach - O(N))
def is_valid_stack(s):
    """
    Checks if a string of parentheses is valid using a stack.

    Args:
        s: The input string containing parentheses.

    Returns:
        True if the string is valid, False otherwise.
    """
    stack = []  # Initialize an empty stack to store open brackets.
    mapping = {')': '(', '}': '{', ']': '['}  # Define a mapping of closing to opening brackets.

    for char in s:  # Iterate through each character in the string.
        if char in mapping:  # If the character is a closing bracket...
            top_element = stack.pop() if stack else '#'  # Get the top element from the stack, or '#' if the stack is empty.  Using '#' as a default to handle empty stack case.
            if mapping[char] != top_element:  # If the corresponding opening bracket doesn't match the top of the stack...
                return False  # ...the string is invalid.
        else:  # If the character is an opening bracket...
            stack.append(char)  # ...push it onto the stack.

    return not stack  # The string is valid if the stack is empty at the end (all brackets are closed).

# 2. Using Dictionary with Stack (Optimized - O(N))
def is_valid_dict_stack(s):
    """
    Checks if a string of parentheses is valid using a stack and a dictionary.  This is a slightly optimized version.

    Args:
        s: The input string containing parentheses.

    Returns:
        True if the string is valid, False otherwise.
    """
    stack = []  # Initialize an empty stack.
    bracket_map = {')': '(', '}': '{', ']': '['}  # Define the bracket mapping.

    for char in s:  # Iterate through the string.
        if char in bracket_map:  # If the character is a closing bracket...
            if not stack or stack.pop() != bracket_map[char]:  # If the stack is empty OR the top element doesn't match...
                return False  # ...the string is invalid.  Combine the pop and comparison into one check.
        else:  # If the character is an opening bracket...
            stack.append(char)  # ...push it onto the stack.

    return len(stack) == 0  # The string is valid if the stack is empty.

# 3. Using a Deque (Efficient Pop Operation - O(N))
from collections import deque  # Import the deque class.

def is_valid_deque(s):
    """
    Checks if a string of parentheses is valid using a deque (double-ended queue) as a stack.
    A deque provides slightly more efficient pop operations in some cases, but the time complexity remains O(N).
    For this problem, the performance difference is usually negligible.

    Args:
        s: The input string containing parentheses.

    Returns:
        True if the string is valid, False otherwise.
    """
    stack = deque()  # Initialize an empty deque.
    mapping = {')': '(', '}': '{', ']': '['}  # Define the bracket mapping.

    for char in s:  # Iterate through the string.
        if char in mapping:  # If the character is a closing bracket...
            if not stack or stack.pop() != mapping[char]:  # Check if the stack is empty or the top element doesn't match.
                return False  # ...the string is invalid.
        else:  # If the character is an opening bracket...
            stack.append(char)  # ...push it onto the deque.

    return not stack  # The string is valid if the deque is empty.

# 4. Using Regular Expressions (Filtering and Checking - O(N))
import re  # Import the regular expression module.

def is_valid_regex(s):
    """
    Checks if a string of parentheses is valid using regular expressions.
    This approach repeatedly removes matching pairs of parentheses until no more pairs can be removed.

    Args:
        s: The input string containing parentheses.

    Returns:
        True if the string is valid, False otherwise.
    """
    pattern = re.compile(r'\(\)|\[\]|\{\}')  # Define a regex pattern to match (), [], or {}.
    prev = None  # Initialize a variable to store the previous state of the string.
    while prev != s:  # Continue looping as long as the string changes (i.e., pairs are removed).
        prev = s  # Store the current string.
        s = pattern.sub('', s)  # Remove all matching pairs from the string.
    return not s  # The string is valid if it's empty after removing all pairs.

# 5. Counting Method (Only for Parentheses - O(N))
def is_valid_counting(s):
    """
    Checks if a string containing ONLY '(' and ')' is valid using a counter.
    This method is specifically for simple parentheses and does not work for other types of brackets.

    Args:
        s: The input string containing parentheses.

    Returns:
        True if the string is valid, False otherwise.
    """
    count = 0  # Initialize a counter for the balance of parentheses.
    for char in s:  # Iterate through the string.
        if char == '(':  # If it's an opening parenthesis...
            count += 1  # ...increment the counter.
        elif char == ')':  # If it's a closing parenthesis...
            count -= 1  # ...decrement the counter.
            if count < 0:  # If the count becomes negative, there's a closing bracket without a matching open bracket...
                return False  # ...the string is invalid.
    return count == 0  # The string is valid if the count is 0 at the end.

# Test Cases
strings = ["()", "()[]{}", "(]", "([)]", "{[]}", "((([])))"]

for s in strings:
    print(f"Stack Approach: {s} -> {is_valid_stack(s)}")
    print(f"Dictionary Stack: {s} -> {is_valid_dict_stack(s)}")
    print(f"Deque Approach: {s} -> {is_valid_deque(s)}")
    print(f"Regex Approach: {s} -> {is_valid_regex(s)}")
    print(f"Counting Approach: {s} -> {is_valid_counting(s)}")
    print("-")
