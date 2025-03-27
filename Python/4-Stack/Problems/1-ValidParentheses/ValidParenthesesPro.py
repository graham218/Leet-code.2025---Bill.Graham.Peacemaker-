'''
Advanced Valid Parentheses - Real-World Implementations

Problem Statement:
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
An input string is valid if:
  1. Open brackets must be closed by the same type of brackets.
  2. Open brackets must be closed in the correct order.
  3. Every close bracket has a corresponding open bracket of the same type.
'''

from collections import deque
import re

# 1. Web Form Validation (Using Stack - O(N))
def validate_form_input(s):
    """
    Validates user input in web forms to ensure that parentheses and brackets are correctly matched.
    This is crucial for preventing errors and ensuring data integrity.  For example, ensuring that
    mathematical expressions or code snippets entered in a form are syntactically correct.

    Args:
        s: The input string from the web form.

    Returns:
        True if the input is valid, False otherwise.
    """
    stack = []  # Initialize an empty stack to store opening brackets.
    mapping = {')': '(', '}': '{', ']': '['}  # Define the mapping of closing to opening brackets.
    for char in s:  # Iterate through each character in the input string.
        if char in mapping:  # If the character is a closing bracket...
            top_element = stack.pop() if stack else '#'  # Get the top element from the stack, or '#' if the stack is empty.
            if mapping[char] != top_element:  # If the corresponding opening bracket doesn't match...
                return False  # ...the input is invalid.
        else:  # If the character is an opening bracket...
            stack.append(char)  # ...push it onto the stack.
    return not stack  # The input is valid if the stack is empty at the end.

# 2. Code Syntax Checking (Using Dictionary - O(N))
def validate_code_syntax(s):
    """
    Checks the syntax of code snippets or entire code files to ensure that brackets,
    braces, and parentheses are correctly matched.  This is essential for compilers,
    interpreters, and code editors to identify syntax errors.

    Args:
        s: The code snippet or file content.

    Returns:
        True if the syntax is valid, False otherwise.
    """
    stack = []  # Initialize an empty stack.
    bracket_map = {')': '(', '}': '{', ']': '['}  # Define the bracket mapping.
    for char in s:  # Iterate through the code.
        if char in bracket_map:  # If the character is a closing bracket...
            if not stack or stack.pop() != bracket_map[char]:  # If the stack is empty or the top element doesn't match...
                return False  # ...the syntax is invalid.
        else:  # If the character is an opening bracket...
            stack.append(char)  # ...push it onto the stack.
    return len(stack) == 0  # The syntax is valid if the stack is empty.

# 3. JSON/XML Validation (Using Deque - O(N))
def validate_json_xml(s):
    """
    Validates the structure of JSON or XML data to ensure that tags and brackets are correctly nested.
    This is crucial for data parsing and exchange, as invalidly formatted data can cause errors.
    A deque is used here, but the performance difference with a list is minimal in this case.

    Args:
        s: The JSON or XML string.

    Returns:
        True if the structure is valid, False otherwise.
    """
    stack = deque()  # Initialize an empty deque.
    mapping = {')': '(', '}': '{', ']': '['}  # Define the bracket mapping.
    for char in s:  # Iterate through the string.
        if char in mapping:  # If the character is a closing bracket...
            if not stack or stack.pop() != mapping[char]:  # If the stack is empty or the top element doesn't match...
                return False  # ...the structure is invalid.
        else:  # If the character is an opening bracket...
            stack.append(char)  # ...push it onto the deque.
    return not stack  # The structure is valid if the deque is empty.

# 4. Secure Input Sanitization (Using Regular Expressions - O(N))
def sanitize_input(s):
    """
    Sanitizes user input to remove potentially harmful or invalid bracket sequences.
    This is a security measure to prevent injection attacks or other vulnerabilities that could
    arise from malformed input.  This approach uses regular expressions.

    Args:
        s: The input string to sanitize.

    Returns:
        The sanitized string (with valid bracket pairs removed).  Returns empty string if all brackets are paired, which is then evaluated to  True
    """
    pattern = re.compile(r'\(\)|\[\]|\{\}')  # Define a regex pattern to match (), [], or {}.
    prev = None  # Initialize a variable to store the previous state of the string.
    while prev != s:  # Continue looping as long as the string changes (i.e., pairs are removed).
        prev = s  # Store the current string.
        s = pattern.sub('', s)  # Remove all matching pairs from the string.
    return not s  # The string is valid if it's empty after removing all pairs.

# 5. Auto-Completion System (Using AI Heuristics - O(N))
def autocomplete_parentheses(s):
    """
    Implements a simplified auto-completion system for parentheses and brackets.  In a real-world
    scenario, AI heuristics would be used to predict the most likely closing brackets based on
    the context, but this function provides a basic example using a stack.

    Args:
        s: The input string with potentially unclosed brackets.

    Returns:
        The string needed to complete the parentheses/brackets.
    """
    stack = []  # Initialize a stack to store opening brackets.
    mapping = {')': '(', '}': '{', ']': '['}  # Define the mapping.
    completion = "" # Initialize empty string.
    for char in s:
        if char in mapping:
            if not stack or stack[-1] != mapping[char]:
                return False # Return False for invalid input
            stack.pop()
        else:
            stack.append(char)
    while stack:
        completion += {"(": ")", "[": "]", "{": "}"}[stack.pop()]
    return completion if completion else True # Returns True if the input string s is valid, otherwise returns the completion string.

# 6. HTML Tag Validation (Using Stack with Custom Handling - O(N))
def validate_html_tags(s):
    """
    Validates the nesting of HTML tags in a simplified HTML string.  This is a basic example;
    real-world HTML validation is more complex and would typically involve a dedicated HTML parser.

    Args:
        s: The simplified HTML string.

    Returns:
        True if the HTML tags are validly nested, False otherwise.
    """
    stack = []  # Initialize a stack to store opening HTML tags.
    tag_map = {'</div>': '<div>', '</p>': '<p>', '</span>': '<span>'}  # Define a mapping of closing to opening tags.
    for word in s.split():  # Iterate through the "words" (tags) in the HTML string.
        if word in tag_map:  # If it's a closing tag...
            if not stack or stack.pop() != tag_map[word]:  # Check for mismatch or empty stack.
                return False  # ...the HTML is invalid.
        elif word in tag_map.values():  # If it's an opening tag...
            stack.append(word)  # ...push it onto the stack.
    return not stack  # The HTML is valid if the stack is empty.

# Test Cases
inputs = ["()", "()[]{}", "(]", "([)]", "{[]}", "((([])))"]
html_inputs = ["<div> <p> </p> </div>", "<div> <span> </span> </p>"]

for s in inputs:
    print(f"Web Form Validation: {s} -> {validate_form_input(s)}")
    print(f"Code Syntax Checking: {s} -> {validate_code_syntax(s)}")
    print(f"JSON/XML Validation: {s} -> {validate_json_xml(s)}")
    print(f"Secure Input Sanitization: {s} -> {sanitize_input(s)}")
    print(f"Auto-Completion System: {s} -> {autocomplete_parentheses(s)}")
    print("-")

for s in html_inputs:
    print(f"HTML Tag Validation: {s} -> {validate_html_tags(s)}")
