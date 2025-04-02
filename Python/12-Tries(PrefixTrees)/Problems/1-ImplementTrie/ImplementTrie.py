"""
Implement a Trie (Prefix Tree) in Python - 5 Approaches

A Trie (pronounced "try") or prefix tree is a tree-like data structure used for efficient storage and retrieval of strings.  It's particularly useful for:

-   **Prefix matching:** Finding all strings with a given prefix.
-   **Autocomplete:** Suggesting words as the user types.
-   **Spell checking:** Checking if a word is in a dictionary.

Here, we'll explore five different ways to implement a Trie in Python.

Approach 1: Using a Simple Dictionary (Beginner-Friendly)
--------------------------------------------------------
This is the most straightforward approach, using a nested dictionary to represent the trie.
Each node in the trie is a dictionary where keys are characters and values are either
another dictionary (for an intermediate node) or a special marker (for a word end).

Pros:
-   Simple to understand and implement.
-   Good for small datasets.

Cons:
-   Can be less memory-efficient for large datasets with many long strings.
-   No explicit node class.

Approach 2: Using a Node Class and Dictionary
---------------------------------------------
This approach defines a `TrieNode` class to represent each node in the trie.  Each node
stores a dictionary of children and a boolean flag to indicate the end of a word.

Pros:
-   More structured and organized than the simple dictionary approach.
-   Clear representation of nodes.

Cons:
-   Slightly more complex than the first approach.
-   Still uses dictionaries, which can have some overhead.

Approach 3: Using defaultdict for Children
-----------------------------------------
This is a variation of Approach 2 that uses `defaultdict(TrieNode)` for the children
dictionary.  This simplifies the `insert` method, as we don't need to check if a child
node exists before creating it.

Pros:
-   More concise `insert` method.
-   Avoids `KeyError` exceptions.

Cons:
-   Slightly less explicit about node creation.

Approach 4: Using a List/Array for Children (for lowercase alphabets)
----------------------------------------------------------------------
If we know that the trie will only contain lowercase English letters (a-z), we can
use a fixed-size list (array) of length 26 to store the children of each node.  This can
be more memory-efficient than a dictionary in this specific case.  We use the
character's ASCII value to determine the index in the list (e.g., 'a' -> 0, 'b' -> 1, ..., 'z' -> 25).

Pros:
-   Potentially more memory-efficient for lowercase alphabets.
-   Faster character lookup (constant time).

Cons:
-   Only works for a limited character set (lowercase letters).
-   Less flexible than a dictionary-based approach.

Approach 5:  Using a Compressed Trie (Radix Trie) -  Basic Idea
----------------------------------------------------------------
A Radix Trie (or compressed trie) optimizes space by merging nodes with only one child.
Instead of storing single characters, it stores *strings* (or "labels") on the edges.
This approach outlines the basic idea.  A full implementation is more complex.

Pros:
-   Most space-efficient (especially for tries with long common prefixes).
-   Faster search for complete words.

Cons:
-   More complex to implement.
-   Insertion and deletion can be more complicated.

Note: This implementation provides the basic idea. A full Radix Trie implementation
would involve more complex logic for splitting and merging edges during insertion and deletion.
"""

from collections import defaultdict

# Approach 1: Using a Simple Dictionary
class Trie1:
    def __init__(self):
        """
        Initialize the trie.
        """
        self.root = {}  # The root node is an empty dictionary

    def insert(self, word: str) -> None:
        """
        Insert a word into the trie.
        """
        node = self.root
        for char in word:
            if char not in node:
                node[char] = {}  # Create a new dictionary for the character
            node = node[char]
        node['#'] = True  # Use '#' to mark the end of a word

    def search(self, word: str) -> bool:
        """
        Search for a word in the trie.
        """
        node = self.root
        for char in word:
            if char not in node:
                return False  # Character not found
            node = node[char]
        return '#' in node  # Check for the end-of-word marker

    def startsWith(self, prefix: str) -> bool:
        """
        Check if there is any word in the trie that starts with the given prefix.
        """
        node = self.root
        for char in prefix:
            if char not in node:
                return False  # Character not found
            node = node[char]
        return True  # Prefix found (doesn't need to be a complete word)

    def display(self):
        """
        Display the trie structure (for debugging/visualization).  Prints a nested dictionary.
        """
        print(self.root)

# Approach 2: Using a Node Class and Dictionary
class TrieNode2:
    def __init__(self):
        """
        Initialize a trie node.
        """
        self.children = {}  # Dictionary of child nodes (character: TrieNode)
        self.is_end_of_word = False  # Flag to indicate end of a word

class Trie2:
    def __init__(self):
        """
        Initialize the trie.
        """
        self.root = TrieNode2()  # The root node is a TrieNode object

    def insert(self, word: str) -> None:
        """
        Insert a word into the trie.
        """
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode2()  # Create a new node
            node = node.children[char]
        node.is_end_of_word = True  # Mark the end of the word

    def search(self, word: str) -> bool:
        """
        Search for a word in the trie.
        """
        node = self.root
        for char in word:
            if char not in node.children:
                return False
            node = node.children[char]
        return node.is_end_of_word  # Check if it's the end of a word

    def startsWith(self, prefix: str) -> bool:
        """
        Check if there is any word in the trie that starts with the given prefix.
        """
        node = self.root
        for char in prefix:
            if char not in node.children:
                return False
            node = node.children[char]
        return True # No need to check for end of word, just that the prefix exists

    def display(self, node=None, prefix=""):
        """
        Display the trie structure (for debugging).  Prints the words.
        """
        if node is None:
            node = self.root
        if node.is_end_of_word:
            print(prefix)
        for char, child in node.children.items():
            self.display(child, prefix + char)

# Approach 3: Using defaultdict for Children
class TrieNode3:
    def __init__(self):
        """
        Initialize a trie node.
        """
        self.children = defaultdict(TrieNode3) # Default to creating a new TrieNode
        self.is_end_of_word = False

class Trie3:
    def __init__(self):
        """
        Initialize the trie.
        """
        self.root = TrieNode3()

    def insert(self, word: str) -> None:
        """
        Insert a word into the trie.
        """
        node = self.root
        for char in word:
            node = node.children[char] #  No need to check if the child exists
        node.is_end_of_word = True

    def search(self, word: str) -> bool:
        """
        Search for a word in the trie.
        """
        node = self.root
        for char in word:
            if char not in node.children:
                return False
            node = node.children[char]
        return node.is_end_of_word

    def startsWith(self, prefix: str) -> bool:
        """
        Check if there is any word in the trie that starts with the given prefix.
        """
        node = self.root
        for char in prefix:
            if char not in node.children:
                return False
            node = node.children[char]
        return True

    def display(self, node=None, prefix=""):
        """
        Display the trie structure (for debugging).
        """
        if node is None:
            node = self.root
        if node.is_end_of_word:
            print(prefix)
        for char, child in node.children.items():
            self.display(child, prefix + char)

# Approach 4: Using a List/Array for Children (for lowercase alphabets)
class TrieNode4:
    def __init__(self):
        """
        Initialize a trie node.
        """
        self.children = [None] * 26  # Array of 26 for 'a' to 'z'
        self.is_end_of_word = False

class Trie4:
    def __init__(self):
        """
        Initialize the trie.
        """
        self.root = TrieNode4()

    def insert(self, word: str) -> None:
        """
        Insert a word into the trie.
        """
        node = self.root
        for char in word:
            index = ord(char) - ord('a')  # Calculate index (0 for 'a', 1 for 'b', ...)
            if not node.children[index]:
                node.children[index] = TrieNode4()
            node = node.children[index]
        node.is_end_of_word = True

    def search(self, word: str) -> bool:
        """
        Search for a word in the trie.
        """
        node = self.root
        for char in word:
            index = ord(char) - ord('a')
            if not node.children[index]:
                return False
            node = node.children[index]
        return node.is_end_of_word

    def startsWith(self, prefix: str) -> bool:
        """
        Check if there is any word in the trie that starts with the given prefix.
        """
        node = self.root
        for char in prefix:
            index = ord(char) - ord('a')
            if not node.children[index]:
                return False
            node = node.children[index]
        return True

    def display(self, node=None, prefix=""):
        """
        Display the trie
        """
        if node is None:
            node = self.root
        if node.is_end_of_word:
            print(prefix)
        for i, child in enumerate(node.children):
            if child:
                self.display(child, prefix + chr(i + ord('a'))) # convert index back to character

# Approach 5: Using a Compressed Trie (Radix Trie) - Basic Idea
class RadixTrieNode:
    def __init__(self):
        """
        Initialize a radix trie node.
        """
        self.children = {}  # Dictionary of children, key is the edge label (string)
        self.is_end_of_word = False

class RadixTrie:
    def __init__(self):
        """
        Initialize the radix trie.
        """
        self.root = RadixTrieNode()

    def insert(self, word: str) -> None:
        """
        Insert a word into the radix trie (basic idea).
        """
        node = self.root
        i = 0
        while i < len(word):
            found_match = False
            for edge, child in node.children.items():
                if word.startswith(edge, i):
                    # Found a matching edge
                    node = child
                    i += len(edge)
                    found_match = True
                    break
            if not found_match:
                # No matching edge, add a new edge
                remaining_word = word[i:]
                node.children[remaining_word] = RadixTrieNode()
                node = node.children[remaining_word]
                i = len(word) # Exit the loop
        node.is_end_of_word = True

    def search(self, word: str) -> bool:
        """
        Search for a word in the radix trie (basic idea).
        """
        node = self.root
        i = 0
        while i < len(word):
            found_match = False
            for edge, child in node.children.items():
                if word.startswith(edge, i):
                    node = child
                    i += len(edge)
                    found_match = True
                    break
            if not found_match:
                return False
        return node.is_end_of_word

    def startsWith(self, prefix: str) -> bool:
        """
        Check if any word starts with the prefix (basic idea).
        """
        node = self.root
        i = 0
        while i < len(prefix):
            found_match = False
            for edge, child in node.children.items():
                if prefix.startswith(edge, i):
                    node = child
                    i += len(edge)
                    found_match = True
                    break
            if not found_match:
                return False
        return True

    def display(self, node=None, prefix=""):
        """
        Display the radix trie (for debugging).
        """
        if node is None:
            node = self.root
        if node.is_end_of_word:
            print(prefix)
        for edge, child in node.children.items():
            self.display(child, prefix + edge)

def test_trie_functionality(trie_class):
    """
    Test the functionality of a Trie implementation.

    Args:
        trie_class: The Trie class to test (e.g., Trie1, Trie2, Trie3, Trie4, RadixTrie).
    """
    print(f"\nTesting Trie implementation: {trie_class.__name__}")
    trie = trie_class()
    words = ["apple", "app", "banana", "orange", "application", "apricot", "ball"]
    for word in words:
        trie.insert(word)
        print(f"Inserted: {word}")

    print("\n--- Search ---")
    print(f"Search 'apple': {trie.search('apple')}")  # True
    print(f"Search 'app': {trie.search('app')}")  # True
    print(f"Search 'banana': {trie.search('banana')}")  # True
    print(f"Search 'orange': {trie.search('orange')}")  # True
    print(f"Search 'application': {trie.search('application')}") # True
    print(f"Search 'apri': {trie.search('apri')}")  # False
    print(f"Search 'ball': {trie.search('ball')}") # True
    print(f"Search 'bat': {trie.search('bat')}")  # False
    print(f"Search 'appl': {trie.search('appl')}") # False

    print("\n--- StartsWith ---")
    print(f"startsWith 'app': {trie.startsWith('app')}")  # True
    print(f"startsWith 'appl': {trie.startsWith('appl')}")  # True
    print(f"startsWith 'bana': {trie.startsWith('bana')}")  # True
    print(f"startsWith 'ap': {trie.startsWith('ap')}")  # True
    print(f"startsWith 'or': {trie.startsWith('or')}")  # True
    print(f"startsWith 'ba': {trie.startsWith('ba')}")  # True
    print(f"startsWith 'x': {trie.startsWith('x')}")  # False

    print("\n--- Display Trie ---")
    print("Trie contents:")
    trie.display() # Call the display method

if __name__ == "__main__":
    test_trie_functionality(Trie1)
    test_trie_functionality(Trie2)
    test_trie_functionality(Trie3)
    test_trie_functionality(Trie4)
    test_trie_functionality(RadixTrie) # Test RadixTrie as well
