"""
Problem: HashMap and Set Operations
Implement different HashMap and Set operations using various approaches.

Approaches:
1. Direct HashMap Implementation (Python Dictionary)
2. Custom HashMap with Separate Chaining (Linked List)
3. Custom HashMap with Open Addressing (Linear Probing)
4. Bloom Filter (Approximate Set Membership)
5. Trie-Based Set (Prefix Tree)
"""

import hashlib
from typing import List

# Approach 1: Direct HashMap Implementation (Using Python Dictionary)
def direct_hashmap_operations():
    # Create a dictionary (built-in HashMap in Python)
    hashmap = {}
    # Insert key-value pairs
    hashmap["apple"] = 10
    hashmap["banana"] = 20
    hashmap["cherry"] = 30
    return hashmap

# Approach 2: Custom HashMap with Separate Chaining
class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None

class HashMapChaining:
    def __init__(self, size=10):
        self.size = size
        self.table = [None] * self.size

    def hash_function(self, key):
        # Simple hash function using modulo
        return hash(key) % self.size

    def insert(self, key, value):
        index = self.hash_function(key)
        if not self.table[index]:
            # If the bucket is empty, create a new node
            self.table[index] = Node(key, value)
        else:
            # If there's a collision, traverse the linked list
            curr = self.table[index]
            while curr.next:
                if curr.key == key:
                    # Update value if key already exists
                    curr.value = value
                    return
                curr = curr.next
            # Add new node at the end of the list
            curr.next = Node(key, value)

    def get(self, key):
        index = self.hash_function(key)
        curr = self.table[index]
        # Traverse the linked list to find the key
        while curr:
            if curr.key == key:
                return curr.value
            curr = curr.next
        return None

def hashmap_separate_chaining():
    hashmap = HashMapChaining()
    hashmap.insert("apple", 10)
    hashmap.insert("banana", 20)
    hashmap.insert("cherry", 30)
    return hashmap.get("banana")

# Approach 3: Custom HashMap with Open Addressing (Linear Probing)
class HashMapOpenAddressing:
    def __init__(self, size=10):
        self.size = size
        self.table = [None] * self.size

    def hash_function(self, key):
        # Simple hash function using modulo
        return hash(key) % self.size

    def insert(self, key, value):
        index = self.hash_function(key)
        # Find the next available slot using linear probing
        while self.table[index] is not None:
            index = (index + 1) % self.size
        self.table[index] = (key, value)

    def get(self, key):
        index = self.hash_function(key)
        # Search for the key using linear probing
        while self.table[index]:
            if self.table[index][0] == key:
                return self.table[index][1]
            index = (index + 1) % self.size
        return None

def hashmap_open_addressing():
    hashmap = HashMapOpenAddressing()
    hashmap.insert("apple", 10)
    hashmap.insert("banana", 20)
    hashmap.insert("cherry", 30)
    return hashmap.get("cherry")

# Approach 4: Bloom Filter (Approximate Set Membership)
class BloomFilter:
    def __init__(self, size=100):
        self.size = size
        self.bit_array = [0] * self.size

    def _hash(self, item):
        # Use two hash functions for better distribution
        hash1 = int(hashlib.md5(item.encode()).hexdigest(), 16) % self.size
        hash2 = int(hashlib.sha256(item.encode()).hexdigest(), 16) % self.size
        return hash1, hash2

    def add(self, item):
        hash1, hash2 = self._hash(item)
        # Set bits at calculated positions
        self.bit_array[hash1] = 1
        self.bit_array[hash2] = 1

    def check(self, item):
        hash1, hash2 = self._hash(item)
        # Check if both bits are set
        return self.bit_array[hash1] == 1 and self.bit_array[hash2] == 1

def bloom_filter_operations():
    bf = BloomFilter()
    bf.add("apple")
    bf.add("banana")
    return bf.check("banana"), bf.check("grape")

# Approach 5: Trie-Based Set (Prefix Tree)
class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end_of_word = False

class TrieSet:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word):
        node = self.root
        for char in word:
            # Create new nodes for characters not present
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

def trie_operations():
    # Create a new TrieSet instance
    trie = TrieSet()
    
    # Insert the word "apple" into the trie
    trie.insert("apple")
    
    # Insert the word "banana" into the trie
    trie.insert("banana")
    
    # Return a tuple containing:
    # 1. The result of searching for "apple" (should be True)
    # 2. The result of searching for "grape" (should be False)
    return trie.search("apple"), trie.search("grape")

# Outputs
print("Direct HashMap:", direct_hashmap_operations())
print("Separate Chaining:", hashmap_separate_chaining())
print("Open Addressing:", hashmap_open_addressing())
print("Bloom Filter:", bloom_filter_operations())
print("Trie-Based Set:", trie_operations())