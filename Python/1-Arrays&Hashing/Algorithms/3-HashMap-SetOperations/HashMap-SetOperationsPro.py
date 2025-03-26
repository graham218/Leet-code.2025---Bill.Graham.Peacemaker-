"""
Problem: HashMap/Set Operations (Advanced Real-World Implementations)

Approaches:
1. Dictionary-based HashMap (Standard Key-Value Storage)
    -   Leverages Python's built-in dictionary, which is highly optimized.
    -   Suitable for general-purpose key-value storage where performance is good enough out-of-the-box.
    -   Simplest to implement.
    -   No need to handle collisions explicitly as Python dict handles it.

2. Custom Hashing Function (Efficient Key Distribution)
    -   Implements a custom hash function to distribute keys more evenly, potentially improving performance compared to the default hash function in some cases.
    -   Handles collisions using separate chaining (each bucket stores a list of key-value pairs).
    -   Useful when you have specific knowledge about your data distribution.

3. LRU Cache Implementation (Optimized Caching Strategy)
    -   Implements a Least Recently Used (LRU) cache, which evicts the least recently accessed items when the cache is full.
    -   Uses an OrderedDict to maintain the order of items based on their last access time.
    -   Essential for caching scenarios where you want to keep the most frequently used data in memory.

4. Bloom Filter Simulation (Efficient Membership Check)
    -   Simulates a Bloom filter, a probabilistic data structure used to test whether an element is a member of a set.
    -   Uses a Python set to approximate the behavior.  A real Bloom filter uses a bit array and multiple hash functions.
    -   Offers very efficient membership checks with a small chance of false positives.
    -   Useful for applications like checking if a username is already taken or if a URL has been visited.

5. Trie-Based Prefix Storage (Efficient Lookup)
    -   Implements a Trie (also known as a prefix tree), a tree-like data structure used for efficient prefix searching.
    -   Each node represents a character, and paths from the root to leaf nodes represent words.
    -   Extremely efficient for prefix-based searches, autocomplete, and dictionary implementations.

6. Multi-Level Hashing (For Scalable Storage)
    -   Implements a two-level hash table to improve scalability and reduce collisions.
    -   Uses a primary hash table, where each entry points to a secondary hash table.
    -   Reduces the load on individual hash tables, leading to better performance for large datasets.
    -   Helpful for scenarios where you expect a large number of keys and want to maintain good performance.
"""

from collections import OrderedDict

class HashMap:
    """
    Approach 1: Dictionary-based HashMap
    Uses Python's built-in dictionary for key-value storage.
    This is the simplest and often the most efficient general-purpose hash map in Python.
    """
    def __init__(self):
        """
        Initializes the HashMap with an empty dictionary.
        """
        self.data = {}  # Use a Python dictionary as the underlying storage.

    def insert(self, key, value):
        """
        Inserts a key-value pair into the HashMap.

        Args:
            key: The key to insert (must be hashable).
            value: The value associated with the key.
        """
        self.data[key] = value  # Directly insert into the dictionary.  Python handles collisions.

    def get(self, key):
        """
        Retrieves the value associated with a key.

        Args:
            key: The key to retrieve the value for.

        Returns:
            The value associated with the key, or None if the key is not found.
        """
        return self.data.get(key, None)  # Use .get() to avoid KeyError if the key doesn't exist.

    def delete(self, key):
        """
        Deletes a key-value pair from the HashMap.

        Args:
            key: The key to delete.
        """
        if key in self.data:  # Check for existence before deleting to avoid KeyError.
            del self.data[key]  # Delete the key-value pair.

# Custom Hashing Function
class CustomHashMap:
    """
    Approach 2: Custom Hashing Function
    Implements a basic hash function for better key distribution.
    This demonstrates how to handle collisions explicitly using separate chaining.
    """
    def __init__(self, size=10):
        """
        Initializes the CustomHashMap with a given size.

        Args:
            size: The size of the hash table (number of buckets).
        """
        self.size = size
        self.data = [[] for _ in range(size)]  # Create a list of lists to store key-value pairs.
        # Each inner list represents a bucket.

    def _hash(self, key):
        """
        A simple hash function that calculates the hash value of a key.

        Args:
            key: The key to hash (must be a string in this example, but could be adapted).

        Returns:
            The hash value of the key (an integer).
        """
        return sum(ord(char) for char in key) % self.size  # Sum of ASCII values modulo size.

    def insert(self, key, value):
        """
        Inserts a key-value pair into the CustomHashMap.  Handles collisions.

        Args:
            key: The key to insert.
            value: The value associated with the key.
        """
        index = self._hash(key)  # Calculate the index using the hash function.
        for pair in self.data[index]:  # Iterate through the list at the index (collision handling).
            if pair[0] == key:
                pair[1] = value  # Update the value if the key already exists.
                return
        self.data[index].append([key, value])  # Append the new key-value pair to the list.

    def get(self, key):
        """
        Retrieves the value associated with a key.  Handles collisions.

        Args:
            key: The key to retrieve the value for.

        Returns:
            The value associated with the key, or None if the key is not found.
        """
        index = self._hash(key)  # Calculate the index.
        for pair in self.data[index]:  # Iterate through the list at the index.
            if pair[0] == key:
                return pair[1]  # Return the value if the key is found.
        return None  # Return None if the key is not found.

# LRU Cache
class LRUCache:
    """
    Approach 3: LRU Cache Implementation
    Implements an LRU cache using OrderedDict.  An LRU cache evicts the least recently used item
    when the cache is full.
    """
    def __init__(self, capacity=3):
        """
        Initializes the LRUCache with a given capacity.

        Args:
            capacity: The maximum number of items the cache can hold.
        """
        self.cache = OrderedDict()  # Use OrderedDict to maintain insertion order (for LRU).
        self.capacity = capacity

    def get(self, key):
        """
        Retrieves the value associated with a key and updates its position in the cache.

        Args:
            key: The key to retrieve the value for.

        Returns:
            The value associated with the key, or None if the key is not found.
        """
        if key in self.cache:
            self.cache.move_to_end(key)  # Move the key to the end to mark it as recently used.
            return self.cache[key]
        return None

    def put(self, key, value):
        """
        Inserts a key-value pair into the cache, evicting the least recently used item if necessary.

        Args:
            key: The key to insert.
            value: The value associated with the key.
        """
        if key in self.cache:
            self.cache.move_to_end(key)  # Move to end if it already exists.
        elif len(self.cache) >= self.capacity:
            self.cache.popitem(last=False)  # Remove the first item (least recently used).
        self.cache[key] = value  # Insert/update the key-value pair.

# Bloom Filter Simulation
class BloomFilter:
    """
    Approach 4: Bloom Filter Simulation
    A simple set-based simulation of a Bloom filter.  A real Bloom filter uses a bit array
    and multiple hash functions, but this simulation uses a set for simplicity.
    Bloom filters are probabilistic and can have false positives, but not false negatives.
    """
    def __init__(self):
        """
        Initializes the BloomFilter simulation.
        """
        self.data = set()  # Use a set to store the "hashed" items.  In a real Bloom filter,
        # this would be a bit array.

    def add(self, item):
        """
        Adds an item to the Bloom filter.

        Args:
            item: The item to add.
        """
        self.data.add(item)  # "Hash" the item (in this simulation, just add it to the set).

    def check(self, item):
        """
        Checks if an item is possibly in the Bloom filter.

        Args:
            item: The item to check for.

        Returns:
            True if the item is possibly in the filter, False if it is definitely not.
        """
        return item in self.data  # Check if the item is in the set.  This simulates the
        # probabilistic check of a Bloom filter.
        #  A real bloom filter may return True even if the item was not added.
        #  It will never return False if the item was added.

# Trie-Based Prefix Storage
class TrieNode:
    """
    Represents a node in the Trie data structure.
    Each node stores a dictionary of child nodes (characters) and a flag indicating
    whether the node represents the end of a word.
    """
    def __init__(self):
        """
        Initializes a TrieNode.
        """
        self.children = {}  # Dictionary to store child nodes (characters).
        self.is_end_of_word = False  # Flag to indicate if this node marks the end of a word.

class Trie:
    """
    Approach 5: Trie-Based Prefix Storage
    Used for efficient prefix searches.  A Trie (prefix tree) stores strings
    such that strings with common prefixes share a common ancestor.
    """
    def __init__(self):
        """
        Initializes the Trie.
        """
        self.root = TrieNode()  # The root node of the Trie.

    def insert(self, word):
        """
        Inserts a word into the Trie.

        Args:
            word: The word to insert.
        """
        node = self.root  # Start at the root.
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()  # Create a new node if the character doesn't exist.
            node = node.children[char]  # Move to the next node.
        node.is_end_of_word = True  # Mark the last node as the end of a word.

    def search(self, word):
        """
        Searches for a word in the Trie.

        Args:
            word: The word to search for.

        Returns:
            True if the word exists in the Trie, False otherwise.
        """
        node = self.root  # Start at the root.
        for char in word:
            if char not in node.children:
                return False  # If a character is not found, the word doesn't exist.
            node = node.children[char]  # Move to the next node.
        return node.is_end_of_word  # Check if the last node marks the end of a word.

# Multi-Level Hashing
class MultiLevelHashing:
    """
    Approach 6: Multi-Level Hashing
    Uses two-level hashing for scalable storage.  This reduces collisions by using
    a secondary hash table for each bucket in the primary hash table.
    """
    def __init__(self, primary_size=5, secondary_size=3):
        """
        Initializes the MultiLevelHashing with primary and secondary table sizes.

        Args:
            primary_size: The size of the primary hash table.
            secondary_size: The size of the secondary hash tables.
        """
        self.primary_size = primary_size
        self.secondary_size = secondary_size
        self.data = [{} for _ in range(primary_size)]  # Create a list of dictionaries.
        # Each dictionary is a secondary hash table.

    def _primary_hash(self, key):
        """
        Primary hash function to determine the index in the primary hash table.

        Args:
            key: The key to hash.

        Returns:
            The index in the primary hash table.
        """
        return hash(key) % self.primary_size

    def _secondary_hash(self, key):
        """
        Secondary hash function to determine the index in the secondary hash table.

        Args:
            key: The key to hash.

        Returns:
            The index in the secondary hash table.
        """
        return hash(key) % self.secondary_size

    def insert(self, key, value):
        """
        Inserts a key-value pair using two-level hashing.

        Args:
            key: The key to insert.
            value: The value associated with the key.
        """
        primary_index = self._primary_hash(key)  # Get the index in the primary table.
        secondary_index = self._secondary_hash(key)  # Get the index in the secondary table.
        self.data[primary_index][secondary_index] = (key, value)  # Store the pair.

    def get(self, key):
        """
        Retrieves the value associated with a key using two-level hashing.

        Args:
            key: The key to retrieve the value for.

        Returns:
            The value associated with the key, or None if the key is not found.
        """
        primary_index = self._primary_hash(key)  # Get primary index
        secondary_index = self._secondary_hash(key)  # Get secondary index
        return self.data[primary_index].get(secondary_index, (None, None))[1]  # Get the value,
        #  handling the case where the secondary index
        #  doesn't exist.

# Testing the implementations
print("Dictionary-based HashMap:")
hm = HashMap()
hm.insert("key1", "value1")
print(hm.get("key1"))

print("Custom Hashing:")
chm = CustomHashMap()
chm.insert("key2", "value2")
print(chm.get("key2"))

print("LRU Cache:")
lru = LRUCache()
lru.put("key3", "value3")
print(lru.get("key3"))

print("Bloom Filter:")
bf = BloomFilter()
bf.add("test")
print(bf.check("test"))
print(bf.check("random"))

print("Trie-Based Storage:")
trie = Trie()
trie.insert("hello")
print(trie.search("hello"))
print(trie.search("world"))

print("Multi-Level Hashing:")
mlh = MultiLevelHashing()
mlh.insert("key4", "value4")
print(mlh.get("key4"))
