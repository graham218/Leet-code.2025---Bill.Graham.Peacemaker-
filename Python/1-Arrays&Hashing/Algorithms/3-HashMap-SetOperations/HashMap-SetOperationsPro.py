"""
Problem: HashMap/Set Operations (Advanced Real-World Implementations)

Approaches:
1. Dictionary-based HashMap (Standard Key-Value Storage)
2. Custom Hashing Function (Efficient Key Distribution)
3. LRU Cache Implementation (Optimized Caching Strategy)
4. Bloom Filter Simulation (Efficient Membership Check)
5. Trie-Based Prefix Storage (Efficient Lookup)
6. Multi-Level Hashing (For Scalable Storage)
"""

from collections import OrderedDict

class HashMap:
    """
    Approach 1: Dictionary-based HashMap
    Uses Python's built-in dictionary for key-value storage.
    """
    def __init__(self):
        self.data = {}

    def insert(self, key, value):
        self.data[key] = value

    def get(self, key):
        return self.data.get(key, None)

    def delete(self, key):
        if key in self.data:
            del self.data[key]

# Custom Hashing Function
class CustomHashMap:
    """
    Approach 2: Custom Hashing Function
    Implements a basic hash function for better key distribution.
    """
    def __init__(self, size=10):
        self.size = size
        self.data = [[] for _ in range(size)]

    def _hash(self, key):
        return sum(ord(char) for char in key) % self.size

    def insert(self, key, value):
        index = self._hash(key)
        for pair in self.data[index]:
            if pair[0] == key:
                pair[1] = value
                return
        self.data[index].append([key, value])

    def get(self, key):
        index = self._hash(key)
        for pair in self.data[index]:
            if pair[0] == key:
                return pair[1]
        return None

# LRU Cache
class LRUCache:
    """
    Approach 3: LRU Cache Implementation
    Implements an LRU cache using OrderedDict.
    """
    def __init__(self, capacity=3):
        self.cache = OrderedDict()
        self.capacity = capacity

    def get(self, key):
        if key in self.cache:
            self.cache.move_to_end(key)
            return self.cache[key]
        return None

    def put(self, key, value):
        if key in self.cache:
            self.cache.move_to_end(key)
        elif len(self.cache) >= self.capacity:
            self.cache.popitem(last=False)
        self.cache[key] = value

# Bloom Filter Simulation
class BloomFilter:
    """
    Approach 4: Bloom Filter Simulation
    A simple set-based simulation of a Bloom filter.
    """
    def __init__(self):
        self.data = set()

    def add(self, item):
        self.data.add(item)

    def check(self, item):
        return item in self.data

# Trie-Based Prefix Storage
class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end_of_word = False

class Trie:
    """
    Approach 5: Trie-Based Prefix Storage
    Used for efficient prefix searches.
    """
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word):
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
        node.is_end_of_word = True

    def search(self, word):
        node = self.root
        for char in word:
            if char not in node.children:
                return False
            node = node.children[char]
        return node.is_end_of_word

# Multi-Level Hashing
class MultiLevelHashing:
    """
    Approach 6: Multi-Level Hashing
    Uses two-level hashing for scalable storage.
    """
    def __init__(self, primary_size=5, secondary_size=3):
        self.primary_size = primary_size
        self.secondary_size = secondary_size
        self.data = [{} for _ in range(primary_size)]

    def _primary_hash(self, key):
        return hash(key) % self.primary_size

    def _secondary_hash(self, key):
        return hash(key) % self.secondary_size

    def insert(self, key, value):
        primary_index = self._primary_hash(key)
        secondary_index = self._secondary_hash(key)
        self.data[primary_index][secondary_index] = (key, value)

    def get(self, key):
        primary_index = self._primary_hash(key)
        secondary_index = self._secondary_hash(key)
        return self.data[primary_index].get(secondary_index, (None, None))[1]

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
