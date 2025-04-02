"""
Trie (Prefix Tree) Implementation in Python: 6 Real-World Approaches

This document provides six Python implementations of the Trie data structure,
focusing on approaches used in real-world projects.  A Trie, also known as a prefix
tree, is a tree-like data structure that is highly efficient for storing and
retrieving strings, especially for prefix-based operations.

Each implementation includes a `TrieNode` class and methods for inserting,
searching, and deleting words.  The examples demonstrate how to use each
implementation.

1.  **Basic Trie with Dictionary (Standard):**
    * Uses a dictionary to represent the children of each node.
    * This is the most common and fundamental Trie implementation.
    * Suitable for general-purpose string storage and retrieval.

2.  **Trie with defaultdict (Concise):**
    * Uses `defaultdict(TrieNode)` to automatically create new nodes when a key
        is accessed.
    * Provides a more compact and readable way to implement the basic Trie.
    * Good for scenarios where code clarity and brevity are important.

3.  **Trie with Compressed Paths (Space-Optimized):**
    * Compresses paths with single children into a single node, reducing space
        usage.
    * Useful when memory efficiency is a primary concern, such as in large
        dictionaries or when dealing with a massive number of strings.

4.  **Trie for Autocomplete (Application-Specific):**
    * Implements a Trie with a method to suggest autocompletion for a given
        prefix.
    * Demonstrates how Tries can be used in applications like search engines
        and text editors.

5.  **Trie for Spell Checking (Application-Specific):**
    * Extends the Trie to provide spell-checking functionality, suggesting
        corrections for misspelled words.
    * Shows how Tries can be adapted for natural language processing tasks.

6.  **Concurrent Trie (Thread-Safe):**
        * Implements a thread-safe Trie using a locking mechanism.
        * Useful in multi-threaded applications.
"""

import threading
from collections import defaultdict
from typing import List, Optional, Tuple

# ------------------------------------------------------------------------------------------------
# 1. Basic Trie with Dictionary (Standard)
# ------------------------------------------------------------------------------------------------
class TrieNode1:
    """
    Represents a node in the Trie.  Each node stores a dictionary of child nodes
    and a flag indicating whether the node represents the end of a word.
    """
    def __init__(self):
        self.children = {}  # Dictionary of child nodes (character: TrieNode)
        self.is_end_of_word = False  # Flag to mark the end of a word

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
# 2. Trie with defaultdict (Concise)
# ------------------------------------------------------------------------------------------------
class TrieNode2:
    """
    Represents a node in the Trie using defaultdict.
    """
    def __init__(self):
        self.children = defaultdict(TrieNode2)  # Default dictionary of child nodes
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
# 3. Trie with Compressed Paths (Space-Optimized)
# ------------------------------------------------------------------------------------------------
class TrieNode3:
    """
    Represents a node in a compressed Trie.
    """
    def __init__(self, prefix=""):
        self.prefix = prefix  # The common prefix represented by this node
        self.children = {}  # Dictionary of child nodes (character: TrieNode)
        self.is_end_of_word = False

class Trie3:
    """
    Implements a compressed Trie (Radix Trie) to save space.
    """
    def __init__(self):
        self.root = TrieNode3()

    def insert(self, word: str) -> None:
        """Inserts a word into the compressed Trie."""
        node = self.root

        while True:
            # Find the common prefix
            i = 0
            while i < len(node.prefix) and i < len(word) and node.prefix[i] == word[i]:
                i += 1

            if i == len(node.prefix):
                # Node's prefix is a prefix of the word
                word = word[i:]
                if not word:
                    node.is_end_of_word = True
                    return

                if word[0] in node.children:
                    node = node.children[word[0]]
                    continue
                else:
                    new_node = TrieNode3(word)
                    new_node.is_end_of_word = True
                    node.children[word[0]] = new_node
                    return
            else:
                # Partial match
                common_prefix = node.prefix[:i]
                suffix1 = node.prefix[i:]
                suffix2 = word[i:]

                new_node = TrieNode3(common_prefix)
                child1 = TrieNode3(suffix1)
                child1.is_end_of_word = node.is_end_of_word
                child1.children = node.children
                new_node.children[suffix1[0]] = child1

                if suffix2:
                    child2 = TrieNode3(suffix2)
                    child2.is_end_of_word = True
                    new_node.children[suffix2[0]] = child2

                node.prefix = common_prefix
                node.is_end_of_word = False
                if common_prefix:
                    node.children = {common_prefix[0]: new_node}
                else:
                    node.children = {}
                return

    def search(self, word: str) -> bool:
        """Searches for a word in the compressed Trie."""
        node = self.root

        while True:
            if not word:
                return node.is_end_of_word

            i = 0
            while i < len(node.prefix) and i < len(word) and node.prefix[i] == word[i]:
                i += 1

            if i == 0:
                return False

            if i < len(node.prefix):
                return False

            word = word[i:]

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
# 4. Trie for Autocomplete (Application-Specific)
# ------------------------------------------------------------------------------------------------
class TrieNode4:
    """
    Represents a node in the Trie for autocomplete functionality.
    """
    def __init__(self):
        self.children = {}
        self.is_end_of_word = False
        self.suggestions = []  # List to store autocompletion suggestions

class Trie4:
    """
    Implements a Trie for autocomplete suggestions.
    """
    def __init__(self):
        self.root = TrieNode4()
        self.max_suggestions = 5

    def insert(self, word: str) -> None:
        """Inserts a word into the Trie."""
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode4()
            node = node.children[char]
        node.is_end_of_word = True

    def search(self, word: str) -> bool:
        """Searches for a word in the Trie."""
        node = self.root
        for char in word:
            if char not in node.children:
                return False
            node = node.children[char]
        return node.is_end_of_word

    def get_suggestions(self, prefix: str) -> List[str]:
        """
        Gets autocompletion suggestions for a given prefix.

        Args:
            prefix: The prefix to get suggestions for.

        Returns:
            A list of suggested words.
        """
        node = self.root
        for char in prefix:
            if char not in node.children:
                return []  # No suggestions if prefix not found
            node = node.children[char]

        self._collect_suggestions(node, prefix)
        return node.suggestions

    def _collect_suggestions(self, node: TrieNode4, current_word: str) -> None:
        """
        Recursively collects suggestions from the Trie.

        Args:
            node: The current node.
            current_word: The current word being formed.
        """
        if len(node.suggestions) >= self.max_suggestions:
            return

        if node.is_end_of_word:
            node.suggestions.append(current_word)

        for char, child in node.children.items():
            self._collect_suggestions(child, current_word + char)

# ------------------------------------------------------------------------------------------------
# 5. Trie for Spell Checking (Application-Specific)
# ------------------------------------------------------------------------------------------------
class TrieNode5:
    """
    Represents a node in the Trie for spell-checking.
    """
    def __init__(self):
        self.children = {}
        self.is_end_of_word = False

class Trie5:
    """
    Implements a Trie for spell checking.
    """
    def __init__(self):
        self.root = TrieNode5()
        self.alphabet = 'abcdefghijklmnopqrstuvwxyz'

    def insert(self, word: str) -> None:
        """Inserts a word into the Trie."""
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode5()
            node = node.children[char]
        node.is_end_of_word = True

    def search(self, word: str) -> bool:
        """Searches for a word in the Trie."""
        node = self.root
        for char in word:
            if char not in node.children:
                return False
            node = node.children[char]
        return node.is_end_of_word

    def suggest_corrections(self, word: str) -> List[str]:
        """
        Suggests spelling corrections for a given word.

        Args:
            word: The misspelled word.

        Returns:
            A list of suggested corrections.
        """
        if self.search(word):
            return [word]  # The word is already correct

        suggestions = set()
        self._collect_corrections(self.root, word, "", 0, suggestions)
        return list(suggestions)

    def _collect_corrections(self, node: TrieNode5, word: str, current_word: str, index: int, suggestions: set) -> None:
        """
        Recursively collects spelling corrections.

        Args:
            node: The current node in the Trie.
            word: The misspelled word.
            current_word: The current word being formed.
            index: The current character index in the misspelled word.
            suggestions: The set to store suggested corrections.
        """
        if index == len(word):
            if node.is_end_of_word:
                suggestions.add(current_word)
            return

        char = word[index]

        # Check for correct character
        if char in node.children:
            self._collect_corrections(node.children[char], word, current_word + char, index + 1, suggestions)

        # Check for substitution
        for c in self.alphabet:
            if c in node.children:
                self._collect_corrections(node.children[c], word, current_word + c, index + 1, suggestions)

        # Check for insertion
        for c in self.alphabet:
            if c in node.children:
                self._collect_corrections(node.children[c], word, current_word + char + c, index + 1, suggestions)
        #Deletion
        if index + 1 <= len(word):
            self._collect_corrections(node, word, current_word, index+1, suggestions)

# ------------------------------------------------------------------------------------------------
# 6. Concurrent Trie (Thread-Safe)
# ------------------------------------------------------------------------------------------------
class TrieNode6:
    """
    Represents a node in the thread-safe Trie.
    """
    def __init__(self):
        self.children = {}
        self.is_end_of_word = False
        self.lock = threading.Lock()  # Lock for thread safety

class Trie6:
    """
    Implements a thread-safe Trie using a lock.
    """
    def __init__(self):
        self.root = TrieNode6()

    def insert(self, word: str) -> None:
        """Inserts a word into the Trie in a thread-safe manner."""
        node = self.root
        for char in word:
            with node.lock:  # Acquire lock before accessing children
                if char not in node.children:
                    node.children[char] = TrieNode6()
                node = node.children[char]
        with node.lock:
            node.is_end_of_word = True

    def search(self, word: str) -> bool:
        """Searches for a word in the Trie in a thread-safe manner."""
        node = self.root
        for char in word:
            with node.lock:
                if char not in node.children:
                    return False
                node = node.children[char]
        with node.lock:
            return node.is_end_of_word

    def starts_with(self, prefix: str) -> bool:
        """Checks for a prefix in a thread-safe manner."""
        node = self.root
        for char in prefix:
            with node.lock:
                if char not in node.children:
                    return False
                node = node.children[char]
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

    # Example 3: Trie with Compressed Paths
    print("\nExample 3: Trie with Compressed Paths")
    trie3 = Trie3()
    trie3.insert("apple")
    trie3.insert("app")
    trie3.insert("application")
    trie3.insert("banana")
    print(f"Search 'apple': {trie3.search('apple')}")
    print(f"Search 'app': {trie3.search('app')}")
    print(f"Search 'application': {trie3.search('application')}")
    print(f"Search 'banana': {trie3.search('banana')}")
    print(f"Search 'ban': {trie3.search('ban')}")
    print(f"Starts with 'app': {trie3.starts_with('app')}")
    print(f"Starts with 'ban': {trie3.starts_with('ban')}")
    print(f"Starts with 'xy': {trie3.starts_with('xy')}")

    # Example 4: Trie for Autocomplete
    print("\nExample 4: Trie for Autocomplete")
    trie4 = Trie4()
    trie4.insert("apple")
    trie4.insert("app")
    trie4.insert("application")
    trie4.insert("banana")
    print(f"Suggestions for 'app': {trie4.get_suggestions('app')}")
    print(f"Suggestions for 'ban': {trie4.get_suggestions('ban')}")
    print(f"Suggestions for 'x': {trie4.get_suggestions('x')}")

    # Example 5: Trie for Spell Checking
    print("\nExample 5: Trie for Spell Checking")
    trie5 = Trie5()
    trie5.insert("apple")
    trie5.insert("banana")
    trie5.insert("application")
    print(f"Suggestions for 'appl': {trie5.suggest_corrections('appl')}")
    print(f"Suggestions for 'banan': {trie5.suggest_corrections('banan')}")
    print(f"Suggestions for 'applcation': {trie5.suggest_corrections('applcation')}")
    print(f"Suggestions for 'xyz': {trie5.suggest_corrections('xyz')}")

    # Example 6: Concurrent Trie
    print("\nExample 6: Concurrent Trie")
    trie6 = Trie6()
    trie6.insert("apple")
    trie6.insert("app")

    def search_thread(word):
        print(f"Thread {threading.current_thread().name} searching for '{word}': {trie6.search(word)}")

    def insert_thread(word):
        trie6.insert(word)
        print(f"Thread {threading.current_thread().name} inserted '{word}'")

    # Create multiple threads to simulate concurrent access
    threads = []
    for i in range(5):
        thread = threading.Thread(target=search_thread, args=("apple",), name=f"SearchThread-{i}")
        threads.append(thread)
        thread.start()

    thread = threading.Thread(target=insert_thread, args=("banana",), name="InsertThread")
    threads.append(thread)
    thread.start()

    for thread in threads:
        thread.join()  # Wait for all threads to finish

    print(f"Search 'banana' after insertion: {trie6.search('banana')}")

if __name__ == "__main__":
    main()
