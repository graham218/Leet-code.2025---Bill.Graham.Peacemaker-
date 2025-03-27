# Advanced Valid Palindrome Implementations
# Real-World Applications of Palindrome Checking

import re  # Import the regular expression module for string manipulation
from collections import deque  # Import the deque class for efficient left/right popping

# Approach 1: Real-Time Text Processing (Efficient Two Pointers)
# Used in text validation for secure inputs in chat applications
def is_palindrome_real_time(s):
    """
    Checks if a string is a palindrome in real-time, ignoring non-alphanumeric characters.

    This approach is efficient because it uses two pointers, one starting from the
    beginning of the string and the other from the end, moving towards the center.
    It's suitable for applications where speed is critical, such as validating
    user input in chat applications as it's being typed.

    Args:
        s: The string to check.

    Returns:
        True if the string is a palindrome, False otherwise.
    """
    left, right = 0, len(s) - 1  # Initialize left and right pointers
    while left < right:  # Continue as long as the left pointer is before the right pointer
        while left < right and not s[left].isalnum():
            left += 1  # Move left pointer to the next alphanumeric character
        while left < right and not s[right].isalnum():
            right -= 1  # Move right pointer to the previous alphanumeric character
        if s[left].lower() != s[right].lower():
            return False  # If characters don't match, it's not a palindrome
        left += 1  # Move left pointer one step forward
        right -= 1  # Move right pointer one step backward
    return True  # If the loop finishes without finding mismatches, it's a palindrome

# Approach 2: Search Engine Optimization (Ignoring Stopwords)
# Used in SEO ranking algorithms to compare search queries
def is_palindrome_seo(s):
    """
    Checks if a string is a palindrome, ignoring common stopwords.

    This approach is useful in SEO for comparing search queries, where certain
    words like "a", "the", and "is" can be ignored to focus on the more
    meaningful parts of the query.  This helps in ranking similar queries.

    Args:
        s: The string to check.

    Returns:
        True if the string is a palindrome (after removing stopwords), False otherwise.
    """
    stopwords = {"a", "the", "is", "in", "at", "of", "and"}  # Define a set of stopwords
    words = re.findall(r"\w+", s.lower())  # Extract words, convert to lowercase
    filtered = [word for word in words if word not in stopwords]  # Remove stopwords
    return filtered == filtered[::-1]  # Check if the filtered list is equal to its reverse

# Approach 3: Genetic Sequencing (DNA Palindrome Check)
# Used in bioinformatics for DNA pattern recognition
def is_palindrome_dna(sequence):
    """
    Checks if a DNA sequence is a palindrome (reverse complement).

    In genetics, palindromic sequences are important for processes like DNA
    replication and gene regulation. This function checks if a DNA sequence
    is equal to its reverse complement.

    Args:
        sequence: The DNA sequence string (e.g., "ATCGCGAT").

    Returns:
        True if the DNA sequence is a palindrome, False otherwise.
    """
    complement = {"A": "T", "T": "A", "C": "G", "G": "C"}  # Define base complements
    rev_comp = ''.join(complement.get(base, base) for base in reversed(sequence))  # Generate the reverse complement
    return sequence.upper() == rev_comp #check if the uppercase version of sequence is equal to the reverse complement

# Approach 4: Data Validation in Databases (Using SQL Normalization)
# Used in database systems to validate and compare normalized text inputs
def is_palindrome_database(s):
    """
    Checks if a string is a palindrome after normalizing it for database storage.

    Databases often need to validate data to ensure consistency.  This function
    normalizes a string by removing non-alphanumeric characters and converting
    it to lowercase, which is a common step before comparing strings in a database.

    Args:
        s: The string to check.

    Returns:
        True if the normalized string is a palindrome, False otherwise.
    """
    normalized = re.sub(r'[^a-zA-Z0-9]', '', s).lower()  # Normalize the string
    return normalized == normalized[::-1]  # Check if the normalized string is a palindrome

# Approach 5: AI Chatbot Responses (Efficient with Deque)
# Used in AI/NLP systems to recognize palindromic queries efficiently
def is_palindrome_chatbot(s):
    """
    Checks if a string is a palindrome using a deque (double-ended queue).

    A deque is more efficient than a regular list for this purpose because
    removing elements from both ends is fast.  This is useful in AI chatbots
    for quickly processing user input to understand if a query is palindromic.

    Args:
        s: The string to check.

    Returns:
        True if the string is a palindrome, False otherwise.
    """
    d = deque()  # Initialize a deque
    for char in s:
        if char.isalnum():
            d.append(char.lower())  # Add alphanumeric characters to the deque
    while len(d) > 1:
        if d.popleft() != d.pop():
            return False  # Compare characters from both ends
    return True  # If the deque is empty or has one element, it's a palindrome

# Approach 6: Cryptographic Security (Reverse Hash Matching)
# Used in cryptographic hash functions to validate integrity
def is_palindrome_crypto(s):
    """
    Checks if a string is a palindrome by comparing the hashes of the string
    and its reverse.

    In cryptography, hashing is used to ensure data integrity.  This function
    checks if a string is a palindrome by comparing the MD5 hash of the
    normalized string with the MD5 hash of its reverse.

    Args:
        s: The string to check.

    Returns:
        True if the hashes of the string and its reverse match, False otherwise.
    """
    import hashlib  # Import the hashlib module
    normalized = re.sub(r'[^a-zA-Z0-9]', '', s).lower()  # Normalize the string
    forward_hash = hashlib.md5(normalized.encode()).hexdigest()  # Hash the forward string
    reverse_hash = hashlib.md5(normalized[::-1].encode()).hexdigest()  # Hash the reversed string
    return forward_hash == reverse_hash  # Compare the hashes

# Test Cases
test_cases = [
    "A man, a plan, a canal: Panama",  # Classic palindrome
    "race a car",  # Not a palindrome
    "ATCGCGAT",  # DNA sequence (not palindromic)
    "Was it a car or a cat I saw",  # Sentence palindrome
    "Madam In Eden, I’m Adam",  # Complex case
]

# Iterate through the test cases and print the results of each palindrome check.
for i, test in enumerate(test_cases, 1):
    print(f"Test Case {i}: {test}")
    print("Real-Time Text Processing:", is_palindrome_real_time(test))
    print("SEO Optimization:", is_palindrome_seo(test))
    print("DNA Palindrome Check:", is_palindrome_dna(test.replace(' ', '').upper()))
    print("Database Validation:", is_palindrome_database(test))
    print("Chatbot Processing:", is_palindrome_chatbot(test))
    print("Cryptographic Security:", is_palindrome_crypto(test))
    print()
