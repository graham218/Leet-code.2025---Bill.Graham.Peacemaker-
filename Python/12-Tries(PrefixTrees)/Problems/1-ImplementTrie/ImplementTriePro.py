"""
Trie (Prefix Tree) Implementations in Python

A Trie, also known as a prefix tree, is a tree-like data structure used for efficient storage and retrieval of strings.
It excels at prefix-based searches, making it suitable for applications like:

-   Autocomplete (e.g., in search bars)
-   Spell checking
-   IP routing (longest prefix matching)
-   Storing dictionaries
-   Data compression

Here, we provide six different approaches to implementing a Trie in Python, each with a focus on real-world applicability
and detailed comments.  We'll cover basic implementation, space optimization, and handling large datasets.

Approach 1: Basic Trie Implementation with a Dictionary

This is the most straightforward implementation, using a dictionary to represent the children of each node.
"""


class TrieNode1:
    def __init__(self):
        """
        Initializes a Trie node.
        -   `children`: A dictionary where keys are characters and values are TrieNode1 objects.
        -   `is_end_of_word`: A boolean indicating if this node marks the end of a word.
        """
        self.children = {}
        self.is_end_of_word = False

    def __repr__(self):  # Added for better debugging
        return f"TrieNode1(children={list(self.children.keys())}, is_end={self.is_end_of_word})"


class Trie1:
    def __init__(self):
        """
        Initializes the Trie.
        -   `root`: The root node of the Trie.
        """
        self.root = TrieNode1()

    def insert(self, word: str) -> None:
        """
        Inserts a word into the Trie.
        Time Complexity: O(n), where n is the length of the word.
        Space Complexity: O(n) in the worst case (for a word with no common prefix with others).

        Args:
            word: The word to insert.
        """
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode1()
            node = node.children[char]
        node.is_end_of_word = True

    def search(self, word: str) -> bool:
        """
        Searches for a word in the Trie.
        Time Complexity: O(n), where n is the length of the word.
        Space Complexity: O(1).

        Args:
            word: The word to search for.

        Returns:
            True if the word is found, False otherwise.
        """
        node = self.root
        for char in word:
            if char not in node.children:
                return False
            node = node.children[char]
        return node.is_end_of_word

    def starts_with(self, prefix: str) -> bool:
        """
        Checks if there is any word in the Trie that starts with the given prefix.
        Time Complexity: O(p), where p is the length of the prefix.
        Space Complexity: O(1).

        Args:
            prefix: The prefix to search for.

        Returns:
            True if there is a word with the prefix, False otherwise.
        """
        node = self.root
        for char in prefix:
            if char not in node.children:
                return False
            node = node.children[char]
        return True  # Important:  We only check if the prefix *exists*, not if it's a complete word.


# Example Usage for Approach 1
trie1 = Trie1()
trie1.insert("apple")
trie1.insert("app")
trie1.insert("banana")

print("--- Approach 1: Basic Trie with Dictionary ---")
print(f"Search 'apple': {trie1.search('apple')}")
print(f"Search 'app': {trie1.search('app')}")
print(f"Search 'banana': {trie1.search('banana')}")
print(f"Search 'orange': {trie1.search('orange')}")
print(f"Starts with 'app': {trie1.starts_with('app')}")
print(f"Starts with 'ban': {trie1.starts_with('ban')}")
print(f"Starts with 'ora': {trie1.starts_with('ora')}")
print(f"Trie structure: {trie1.root}")  #prints the trie structure


"""
Approach 2: Trie with defaultdict for Simpler Insertion

This approach uses `defaultdict` to simplify the insertion process.  Instead of checking if a child exists
before creating it, `defaultdict` automatically creates a new node if a child is accessed that doesn't exist.
This makes the code more concise, but the underlying logic is the same as Approach 1.
"""

from collections import defaultdict


class TrieNode2:
    def __init__(self):
        self.children = defaultdict(TrieNode2)  # defaultdict simplifies node creation
        self.is_end_of_word = False

    def __repr__(self):
        return f"TrieNode2(children={list(self.children.keys())}, is_end={self.is_end_of_word})"


class Trie2:
    def __init__(self):
        self.root = TrieNode2()

    def insert(self, word: str) -> None:
        node = self.root
        for char in word:
            node = node.children[char]  # No need to check if child exists
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



# Example Usage for Approach 2
trie2 = Trie2()
trie2.insert("apple")
trie2.insert("app")
trie2.insert("banana")

print("\n--- Approach 2: Trie with defaultdict ---")
print(f"Search 'apple': {trie2.search('apple')}")
print(f"Search 'app': {trie2.search('app')}")
print(f"Search 'banana': {trie2.search('banana')}")
print(f"Search 'orange': {trie2.search('orange')}")
print(f"Starts with 'app': {trie2.starts_with('app')}")
print(f"Starts with 'ban': {trie2.starts_with('ban')}")
print(f"Starts with 'ora': {trie2.starts_with('ora')}")
print(f"Trie structure: {trie2.root}")


"""
Approach 3: Trie with a List of Children (for limited character sets)

If the character set is limited and known (e.g., lowercase English letters), using a list instead of a dictionary
can improve space efficiency.  This avoids the overhead of dictionary hash tables.  For ASCII characters,
a list of size 256 would be used.  Here, we assume lowercase letters.
"""


class TrieNode3:
    def __init__(self):
        self.children = [None] * 26  # For lowercase letters 'a' to 'z'
        self.is_end_of_word = False

    def __repr__(self):
        children_present = [chr(i + ord('a')) for i, child in enumerate(self.children) if child]
        return f"TrieNode3(children={children_present}, is_end={self.is_end_of_word})"


class Trie3:
    def __init__(self):
        self.root = TrieNode3()

    def _char_to_index(self, char: str) -> int:
        """
        Helper function to convert a character to its corresponding index (0-25 for a-z).
        """
        return ord(char) - ord('a')

    def insert(self, word: str) -> None:
        node = self.root
        for char in word:
            index = self._char_to_index(char)
            if not node.children[index]:
                node.children[index] = TrieNode3()
            node = node.children[index]
        node.is_end_of_word = True

    def search(self, word: str) -> bool:
        node = self.root
        for char in word:
            index = self._char_to_index(char)
            if not node.children[index]:
                return False
            node = node.children[index]
        return node.is_end_of_word

    def starts_with(self, prefix: str) -> bool:
        node = self.root
        for char in prefix:
            index = self._char_to_index(char)
            if not node.children[index]:
                return False
            node = node.children[index]
        return True



# Example Usage for Approach 3
trie3 = Trie3()
trie3.insert("apple")
trie3.insert("app")
trie3.insert("banana")

print("\n--- Approach 3: Trie with List of Children ---")
print(f"Search 'apple': {trie3.search('apple')}")
print(f"Search 'app': {trie3.search('app')}")
print(f"Search 'banana': {trie3.search('banana')}")
print(f"Search 'orange': {trie3.search('orange')}")
print(f"Starts with 'app': {trie3.starts_with('app')}")
print(f"Starts with 'ban': {trie3.starts_with('ban')}")
print(f"Starts with 'ora': {trie3.starts_with('ora')}")
print(f"Trie structure: {trie3.root}")


"""
Approach 4: Trie with Node Pooling for Memory Efficiency

For very large datasets, creating a new node for every character can consume a lot of memory.  Node pooling involves
pre-allocating a pool of nodes and reusing them as needed.  This can significantly reduce memory usage, especially
if there are many common prefixes.  This is a more advanced technique.
"""

class TrieNode4:
    def __init__(self):
        self.children = {}
        self.is_end_of_word = False
        self.id = -1 # Add an ID to the node

    def __repr__(self):
        return f"TrieNode4(id={self.id}, children={list(self.children.keys())}, is_end={self.is_end_of_word})"


class Trie4:
    def __init__(self, pool_size=100000):  # Increased pool size
        self.node_pool = [TrieNode4() for _ in range(pool_size)]
        self.pool_index = 0
        self.node_count = 0 # Initialize node_count here
        self.root = self._get_node()

    def _get_node(self):
        """
        Gets a node from the pool.
        """
        if self.pool_index >= len(self.node_pool):
            raise MemoryError("Node pool is exhausted")  # Handle pool exhaustion
        node = self.node_pool[self.pool_index]
        node.id = self.node_count  # Assign an ID
        self.node_count += 1
        self.pool_index += 1
        return node

    def insert(self, word: str) -> None:
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = self._get_node()
            node = node.children[char]
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

    def display_pool_usage(self):
        """
        Displays the number of nodes used from the pool.
        """
        print(f"Nodes used from pool: {self.pool_index} / {len(self.node_pool)}")


# Example Usage for Approach 4
trie4 = Trie4(pool_size=200)  # Smaller pool for demonstration
trie4.insert("apple")
trie4.insert("app")
trie4.insert("banana")
trie4.insert("application")  # Add more words to see pool usage
trie4.insert("apricot")
trie4.insert("ball")
trie4.insert("bat")
trie4.insert("car")
trie4.insert("cat")
trie4.insert("dog")


print("\n--- Approach 4: Trie with Node Pooling ---")
print(f"Search 'apple': {trie4.search('apple')}")
print(f"Search 'app': {trie4.search('app')}")
print(f"Search 'banana': {trie4.search('banana')}")
print(f"Search 'orange': {trie4.search('orange')}")
print(f"Starts with 'app': {trie4.starts_with('app')}")
print(f"Starts with 'ban': {trie4.starts_with('ban')}")
print(f"Starts with 'ora': {trie4.starts_with('ora')}")
trie4.display_pool_usage()
print(f"Trie structure: {trie4.root}")

"""
Approach 5: Compressed Trie (Radix Trie) for Space Optimization

A compressed trie, also known as a radix trie or patricia trie, optimizes space by merging nodes with single children.
Instead of storing individual characters, it stores strings (edges) that represent sequences of characters.
This can significantly reduce the number of nodes, especially when there are long common prefixes.
"""


class TrieNode5:
    def __init__(self):
        self.children = {}  # Use string keys for children
        self.is_end_of_word = False

    def __repr__(self):
        return f"TrieNode5(children={list(self.children.keys())}, is_end={self.is_end_of_word})"


class Trie5:
    def __init__(self):
        self.root = TrieNode5()

    def insert(self, word: str) -> None:
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
                # No matching edge found
                remaining_suffix = word[i:]
                node.children[remaining_suffix] = TrieNode5()
                node = node.children[remaining_suffix]
                node.is_end_of_word = True
                return

        node.is_end_of_word = True  # Set end of word for the last node

    def search(self, word: str) -> bool:
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

    def starts_with(self, prefix: str) -> bool:
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



# Example Usage for Approach 5
trie5 = Trie5()
trie5.insert("apple")
trie5.insert("app")
trie5.insert("banana")
trie5.insert("application")  # Demonstrates compression with "app"
trie5.insert("apricot")

print("\n--- Approach 5: Compressed Trie (Radix Trie) ---")
print(f"Search 'apple': {trie5.search('apple')}")
print(f"Search 'app': {trie5.search('app')}")
print(f"Search 'banana': {trie5.search('banana')}")
print(f"Search 'orange': {trie5.search('orange')}")
print(f"Starts with 'app': {trie5.starts_with('app')}")
print(f"Starts with 'ban': {trie5.starts_with('ban')}")
print(f"Starts with 'ora': {trie5.starts_with('ora')}")
print(f"Trie structure: {trie5.root}")


"""
Approach 6: Trie with External Storage (for massive datasets)

For datasets that are too large to fit in memory, the Trie can be stored externally (e.g., in a database or on disk).
This involves serializing Trie nodes and storing them, and then loading them as needed.  This is a complex approach
and often involves a key-value store.  Here's a simplified example using a dictionary for demonstration,
but in a real-world scenario, you'd use a database like Redis or LevelDB.  This approach focuses on the
serialization aspect.
"""

import json


class TrieNode6:
    def __init__(self):
        self.children = {}
        self.is_end_of_word = False

    def __repr__(self):
        return f"TrieNode6(children={list(self.children.keys())}, is_end={self.is_end_of_word})"

    def to_dict(self):
        """
        Serializes the node to a dictionary.  Used for external storage.
        """
        children_dict = {char: child.to_dict() for char, child in self.children.items()}
        return {
            'children': children_dict,
            'is_end_of_word': self.is_end_of_word,
        }

    @staticmethod
    def from_dict(data):
        """
        Deserializes a dictionary back into a TrieNode6.
        """
        node = TrieNode6()
        node.is_end_of_word = data['is_end_of_word']
        for char, child_data in data['children'].items():
            node.children[char] = TrieNode6.from_dict(child_data)
        return node



class Trie6:
    def __init__(self, storage_file="trie_data.json"):  # Use a file for "storage"
        self.root = TrieNode6()
        self.storage_file = storage_file
        self.load()  # Load data on initialization

    def insert(self, word: str) -> None:
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode6()
            node = node.children[char]
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

    def save(self):
        """
        Saves the Trie to external storage (in this case, a JSON file).
        """
        data = self.root.to_dict()
        try:
            with open(self.storage_file, 'w') as f:
                json.dump(data, f, indent=4)  # Pretty printing for readability
        except Exception as e:
            print(f"Error saving Trie to {self.storage_file}: {e}") #error handling

    def load(self):
        """
        Loads the Trie from external storage (a JSON file).
        """
        try:
            with open(self.storage_file, 'r') as f:
                data = json.load(f)
            self.root = TrieNode6.from_dict(data)
        except FileNotFoundError:
            print(f"File not found: {self.storage_file}.  Starting with an empty Trie.")
            self.root = TrieNode6() # set to empty trie
        except json.JSONDecodeError:
            print(f"Error decoding JSON from {self.storage_file}.  Starting with an empty Trie.")
            self.root = TrieNode6()  # Handle corrupted file
        except Exception as e:
            print(f"Error loading Trie from {self.storage_file}: {e}")
            self.root = TrieNode6()

# Example Usage for Approach 6
trie6 = Trie6("my_trie.json")  # Specify a filename
trie6.insert("apple")
trie6.insert("app")
trie6.insert("banana")
trie6.save()  # Save the Trie to disk

trie6_loaded = Trie6("my_trie.json")  # Load from disk
print("\n--- Approach 6: Trie with External Storage ---")
print(f"Search 'apple': {trie6_loaded.search('apple')}")
print(f"Search 'app': {trie6_loaded.search('app')}")
print(f"Search 'banana': {trie6_loaded.search('banana')}")
print(f"Search 'orange': {trie6_loaded.search('orange')}")
print(f"Starts with 'app': {trie6_loaded.starts_with('app')}")
print(f"Starts with 'ban': {trie6_loaded.starts_with('ban')}")
print(f"Starts with 'ora': {trie6_loaded.starts_with('ora')}")
print(f"Trie structure: {trie6_loaded.root}")
