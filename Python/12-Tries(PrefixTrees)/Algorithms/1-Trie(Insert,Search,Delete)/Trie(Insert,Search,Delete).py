"""
Trie (Prefix Tree) Implementation in Python: 5 Approaches

A Trie, also known as a prefix tree, is a tree-like data structure used for efficient storage and retrieval of strings.
It excels in prefix-based search operations.  This document provides five different ways to implement a Trie in Python.

1.  **Basic Trie with Dictionary:**
    * Uses a dictionary to represent the children of each node.
    * Simple and intuitive for understanding the basic Trie structure.

2.  **Trie with defaultdict:**
    * Uses `defaultdict(TrieNode)` to automatically create new nodes when a key is accessed.
    * Slightly more concise than the basic dictionary approach.

3.  **Trie with Node Class and List:**
    * Uses a list within the Node class.
    * Less Pythonic and generally less efficient than dictionary-based approaches, but shows an alternative.

4.  **Compressed Trie (Radix Trie):**
    * Optimizes space by merging nodes with single children into a single edge.
    * More complex to implement but can significantly reduce memory usage for certain datasets.

5.  **Trie with Explicit Deletion:**
    * Includes a `delete` method to remove words from the trie.
    * Demonstrates how to handle node removal and edge collapsing in a Trie.

Each approach includes a `TrieNode` class to represent nodes in the tree and methods for
inserting, searching, and deleting words.  The examples demonstrate how to use each
implementation.
"""

from collections import defaultdict
from typing import Optional, List, Tuple

# ------------------------------------------------------------------------------------------------
# 1. Basic Trie with Dictionary
# ------------------------------------------------------------------------------------------------
class TrieNode1:
    """
    Represents a node in the Trie.  Each node stores a dictionary of child nodes
    and a flag indicating whether the node represents the end of a word.
    """
    def __init__(self):
        self.children = {}  # Dictionary of child nodes (character: TrieNode)
        self.is_end_of_word = False # Flag to mark the end of a word

class Trie1:
    """
    Implements a Trie data structure using a dictionary.
    """
    def __init__(self):
        self.root = TrieNode1()  # Root node of the Trie

    def insert(self, word: str) -> None:
        """
        Inserts a word into the Trie.

        Args:
            word: The word to insert.
        """
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode1()  # Create a new node if the character is not present
            node = node.children[char]  # Move to the child node
        node.is_end_of_word = True  # Mark the last node as the end of the word

    def search(self, word: str) -> bool:
        """
        Searches for a word in the Trie.

        Args:
            word: The word to search for.

        Returns:
            True if the word is found, False otherwise.
        """
        node = self.root
        for char in word:
            if char not in node.children:
                return False  # Word not found if character not in children
            node = node.children[char]  # Move to the child node
        return node.is_end_of_word  # Check if the last node is the end of the word

    def starts_with(self, prefix: str) -> bool:
        """
        Checks if there is any word in the trie that starts with the given prefix.

        Args:
            prefix: The prefix to search for.

        Returns:
            True if there is a word with the prefix, False otherwise.
        """
        node = self.root
        for char in prefix:
            if char not in node.children:
                return False  # Prefix not found if character not in children
            node = node.children[char]  # Move to the child node
        return True  # Prefix found

# ------------------------------------------------------------------------------------------------
# 2. Trie with defaultdict
# ------------------------------------------------------------------------------------------------
class TrieNode2:
    """
    Represents a node in the Trie using defaultdict.
    """
    def __init__(self):
        self.children = defaultdict(TrieNode2) # Default dictionary of child nodes
        self.is_end_of_word = False

class Trie2:
    """
    Implements a Trie using defaultdict for more concise node creation.
    """
    def __init__(self):
        self.root = TrieNode2()

    def insert(self, word: str) -> None:
        node = self.root
        for char in word:
            node = node.children[char]  # Creates node if it doesn't exist
        node.is_end_of_word = True

    def search(self, word: str) -> bool:
        node = self.root
        for char in word:
            if char not in node.children:
                return False
            node = node.children[char]
        return node.is_end_of_word

    def starts_with(self, prefix: str) -> bool:
        node = self.root
        for char in prefix:
            if char not in node.children:
                return False
            node = node.children[char]
        return True

# ------------------------------------------------------------------------------------------------
# 3. Trie with Node Class and List
# ------------------------------------------------------------------------------------------------

class TrieNode3:
    """
    Represents a node in the Trie.  Uses a list to store children.
    This approach is less common and generally less efficient than using a dictionary.
    """
    def __init__(self):
        self.children = [None] * 26  # List of 26 possible children (a-z)
        self.is_end_of_word = False

    def get_child(self, char: str) -> Optional['TrieNode3']:
        """Gets the child node for a given character."""
        index = ord(char) - ord('a')
        return self.children[index]

    def set_child(self, char: str, node: 'TrieNode3') -> None:
        """Sets the child node for a given character."""
        index = ord(char) - ord('a')
        self.children[index] = node

class Trie3:
    """
    Implements a Trie using a list to store children.
    """
    def __init__(self):
        self.root = TrieNode3()

    def insert(self, word: str) -> None:
        node = self.root
        for char in word:
            child_node = node.get_child(char)
            if not child_node:
                new_node = TrieNode3()
                node.set_child(char, new_node)
                node = new_node
            else:
                node = child_node
        node.is_end_of_word = True

    def search(self, word: str) -> bool:
        node = self.root
        for char in word:
            child_node = node.get_child(char)
            if not child_node:
                return False
            node = child_node
        return node.is_end_of_word

    def starts_with(self, prefix: str) -> bool:
        node = self.root
        for char in prefix:
            child_node = node.get_child(char)
            if not child_node:
                return False
            node = child_node
        return True

# ------------------------------------------------------------------------------------------------
# 4. Compressed Trie (Radix Trie)
# ------------------------------------------------------------------------------------------------
class RadixTrieNode:
    """
    Represents a node in a Radix Trie.  Each node stores a common prefix
    and a dictionary of child nodes.
    """
    def __init__(self, prefix=""):
        self.prefix = prefix  # The common prefix represented by this node
        self.children = {}  # Dictionary of child nodes (character: RadixTrieNode)
        self.is_end_of_word = False

class RadixTrie:
    """
    Implements a Radix Trie (Compressed Trie).
    """
    def __init__(self):
        self.root = RadixTrieNode()

    def insert(self, word: str) -> None:
        """Inserts a word into the Radix Trie."""
        node = self.root

        while True:
            # Find the common prefix between the word and the current node's prefix
            i = 0
            while i < len(node.prefix) and i < len(word) and node.prefix[i] == word[i]:
                i += 1

            if i == len(node.prefix):
                # The node's prefix is a prefix of the word
                word = word[i:]  # Remaining part of the word
                if not word:
                    node.is_end_of_word = True
                    return

                # Check if the next character of the word exists as a child
                if word[0] in node.children:
                    node = node.children[word[0]]
                    continue  # Continue to the next node
                else:
                    # Create a new node for the remaining word
                    new_node = RadixTrieNode(word)
                    new_node.is_end_of_word = True
                    node.children[word[0]] = new_node
                    return
            else:
                # The node's prefix and the word have a common prefix, but it's not the whole node prefix
                common_prefix = node.prefix[:i]
                suffix1 = node.prefix[i:]
                suffix2 = word[i:]

                # Create a new node for the common prefix
                new_node = RadixTrieNode(common_prefix)

                # Create a node for the existing node's suffix
                child1 = RadixTrieNode(suffix1)
                child1.is_end_of_word = node.is_end_of_word

                # Move the existing node's children to the new child node
                child1.children = node.children

                new_node.children[suffix1[0]] = child1

                if suffix2:
                    # Create a node for the remaining word's suffix
                    child2 = RadixTrieNode(suffix2)
                    child2.is_end_of_word = True
                    new_node.children[suffix2[0]] = child2

                node.prefix = common_prefix # important
                node.is_end_of_word = False
                if common_prefix:
                    node.children = {common_prefix[0]: new_node}
                else:
                    node.children = {}
                return


    def search(self, word: str) -> bool:
        """Searches for a word in the Radix Trie."""
        node = self.root

        while True:
            if not word:
                return node.is_end_of_word

            # Find the common prefix
            i = 0
            while i < len(node.prefix) and i < len(word) and node.prefix[i] == word[i]:
                i += 1

            if i == 0:
                return False  # No common prefix

            if i < len(node.prefix):
                return False  # Partial match of node prefix, but not complete word

            word = word[i:]  # Consume the matched part of the word

            if not word:
                return node.is_end_of_word

            if word[0] not in node.children:
                return False

            node = node.children[word[0]]

    def starts_with(self, prefix: str) -> bool:
        """Checks if any word starts with the given prefix."""
        node = self.root

        while prefix:
            i = 0
            while i < len(node.prefix) and i < len(prefix) and node.prefix[i] == prefix[i]:
                i += 1

            if i == 0:
                return False

            prefix = prefix[i:]

            if not prefix:
                return True

            if prefix[0] not in node.children:
                return False

            node = node.children[prefix[0]]
        return True

# ------------------------------------------------------------------------------------------------
# 5. Trie with Explicit Deletion
# ------------------------------------------------------------------------------------------------

class TrieNode5:
    """
    Represents a node in the Trie, supporting deletion.
    """
    def __init__(self):
        self.children = {}
        self.is_end_of_word = False
        self.count = 0  # Keep track of how many times a word passes through this node

class Trie5:
    """
    Implements a Trie with explicit deletion of words.
    """
    def __init__(self):
        self.root = TrieNode5()

    def insert(self, word: str) -> None:
        """Inserts a word into the Trie."""
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode5()
            node = node.children[char]
            node.count += 1 # Increment count as we traverse
        node.is_end_of_word = True

    def search(self, word: str) -> bool:
        """Searches for a word in the Trie."""
        node = self.root
        for char in word:
            if char not in node.children:
                return False
            node = node.children[char]
        return node.is_end_of_word

    def starts_with(self, prefix: str) -> bool:
        """Checks if any word starts with the given prefix."""
        node = self.root
        for char in prefix:
            if char not in node.children:
                return False
            node = node.children[char]
        return True

    def delete(self, word: str) -> bool:
        """
        Deletes a word from the Trie.

        Args:
            word: The word to delete.

        Returns:
            True if the word was deleted, False if the word was not found.
        """
        return self._delete(self.root, word, 0)

    def _delete(self, node: TrieNode5, word: str, index: int) -> bool:
        """
        Recursive helper function for deleting a word.

        Args:
            node: The current node.
            word: The word to delete.
            index: The current character index in the word.

        Returns:
            True if the word was deleted, False if the word was not found.
        """
        if index == len(word):
            if not node.is_end_of_word:
                return False  # Word not found
            node.is_end_of_word = False
            node.count -= 1
            return True

        char = word[index]
        if char not in node.children:
            return False  # Word not found

        child = node.children[char]
        deleted = self._delete(child, word, index + 1)
        if not deleted:
            return False

        # Post-processing: check if the child node can be removed
        child.count -= 1
        if child.count == 0:
            del node.children[char] # remove the child
            return True
        return True

# ------------------------------------------------------------------------------------------------
# Example Usage
# ------------------------------------------------------------------------------------------------

def main():
    """
    Main function to demonstrate the usage of the Trie implementations.
    """
    # Example 1: Basic Trie with Dictionary
    print("\nExample 1: Basic Trie with Dictionary")
    trie1 = Trie1()
    trie1.insert("apple")
    trie1.insert("app")
    print(f"Search 'apple': {trie1.search('apple')}")
    print(f"Search 'app': {trie1.search('app')}")
    print(f"Search 'ap': {trie1.search('ap')}")
    print(f"Starts with 'ap': {trie1.starts_with('ap')}")

    # Example 2: Trie with defaultdict
    print("\nExample 2: Trie with defaultdict")
    trie2 = Trie2()
    trie2.insert("apple")
    trie2.insert("app")
    print(f"Search 'apple': {trie2.search('apple')}")
    print(f"Search 'app': {trie2.search('app')}")
    print(f"Search 'ap': {trie2.search('ap')}")
    print(f"Starts with 'ap': {trie2.starts_with('ap')}")

    # Example 3: Trie with Node Class and List
    print("\nExample 3: Trie with Node Class and List")
    trie3 = Trie3()
    trie3.insert("apple")
    trie3.insert("app")
    print(f"Search 'apple': {trie3.search('apple')}")
    print(f"Search 'app': {trie3.search('app')}")
    print(f"Search 'ap': {trie3.search('ap')}")
    print(f"Starts with 'ap': {trie3.starts_with('ap')}")

    # Example 4: Compressed Trie (Radix Trie)
    print("\nExample 4: Compressed Trie (Radix Trie)")
    trie4 = RadixTrie()
    trie4.insert("apple")
    trie4.insert("app")
    trie4.insert("application")
    trie4.insert("banana")
    print(f"Search 'apple': {trie4.search('apple')}")
    print(f"Search 'app': {trie4.search('app')}")
    print(f"Search 'application': {trie4.search('application')}")
    print(f"Search 'banana': {trie4.search('banana')}")
    print(f"Search 'ban': {trie4.search('ban')}")
    print(f"Starts with 'app': {trie4.starts_with('app')}")
    print(f"Starts with 'ban': {trie4.starts_with('ban')}")
    print(f"Starts with 'xy': {trie4.starts_with('xy')}")

    # Example 5: Trie with Explicit Deletion
    print("\nExample 5: Trie with Explicit Deletion")
    trie5 = Trie5()
    trie5.insert("apple")
    trie5.insert("app")
    trie5.insert("application")
    print(f"Search 'apple': {trie5.search('apple')}")
    print(f"Search 'app': {trie5.search('app')}")
    print(f"Search 'application': {trie5.search('application')}")
    print(f"Starts with 'app': {trie5.starts_with('app')}")

    print(f"Delete 'app': {trie5.delete('app')}")
    print(f"Search 'app': {trie5.search('app')}")
    print(f"Search 'apple': {trie5.search('apple')}")
    print(f"Starts with 'app': {trie5.starts_with('app')}")

    print(f"Delete 'apple': {trie5.delete('apple')}")
    print(f"Search 'apple': {trie5.search('apple')}")
    print(f"Starts with 'app': {trie5.starts_with('app')}")

    print(f"Delete 'application': {trie5.delete('application')}")
    print(f"Search 'application': {trie5.search('application')}")
    print(f"Starts with 'app': {trie5.starts_with('app')}")
    print(f"Starts with 'a': {trie5.starts_with('a')}")

if __name__ == "__main__":
    main()
