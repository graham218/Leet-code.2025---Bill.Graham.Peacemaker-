import heapq
from collections import defaultdict, deque
import math

class HuffmanNode:
    """Base class for Huffman Tree nodes"""
    def __init__(self, freq, char=None):
        self.char = char  # None for internal nodes
        self.freq = freq
        self.left = None
        self.right = None

    # For heap comparison
    def __lt__(self, other):
        return self.freq < other.freq

def build_frequency_table(data):
    """Build frequency table from input data"""
    freq_table = defaultdict(int)
    for char in data:
        freq_table[char] += 1
    return freq_table

# Approach 1: Basic Textbook Implementation
def huffman_basic(text):
    """
    Basic textbook implementation of Huffman coding.
    Good for understanding fundamentals but not optimized.
    """
    if not text:
        return {}, {}

    # Build frequency table
    freq_table = build_frequency_table(text)

    # Create priority queue
    heap = []
    for char, freq in freq_table.items():
        heapq.heappush(heap, HuffmanNode(freq, char))

    # Edge case: single character
    if len(heap) == 1:
        node = heapq.heappop(heap)
        return {node.char: "0"}, {node.char: node.freq}

    # Build Huffman tree
    while len(heap) > 1:
        left = heapq.heappop(heap)
        right = heapq.heappop(heap)
        merged = HuffmanNode(left.freq + right.freq)
        merged.left = left
        merged.right = right
        heapq.heappush(heap, merged)

    # Generate codes
    root = heapq.heappop(heap)
    codes = {}

    def traverse(node, current_code):
        if node.char is not None:
            codes[node.char] = current_code
            return
        traverse(node.left, current_code + "0")
        traverse(node.right, current_code + "1")

    traverse(root, "")

    return codes, freq_table

# Approach 2: Memory-Efficient Implementation (Fixed)
def huffman_memory_efficient(text):
    """
    Memory-efficient implementation that builds codes during tree construction.
    Reduces memory usage by not storing the entire tree structure.
    Useful for large datasets.
    """
    if not text:
        return {}, {}

    freq_table = build_frequency_table(text)
    heap = []

    # Create leaf nodes and push to heap
    for char, freq in freq_table.items():
        heapq.heappush(heap, (freq, char))

    # Edge case: single character
    if len(heap) == 1:
        freq, char = heapq.heappop(heap)
        return {char: "0"}, {char: freq}

    # Build codes during tree construction
    codes = {char: "" for char in freq_table.keys()}

    while len(heap) > 1:
        # Pop two smallest nodes
        left_freq, left_char = heapq.heappop(heap)
        right_freq, right_char = heapq.heappop(heap)

        # Update codes for the characters
        if isinstance(left_char, str):
            codes[left_char] = '0' + codes[left_char]
        else:
            # Left_char is actually a list of characters from merged nodes
            for char in left_char:
                codes[char] = '0' + codes[char]

        if isinstance(right_char, str):
            codes[right_char] = '1' + codes[right_char]
        else:
            # Right_char is actually a list of characters from merged nodes
            for char in right_char:
                codes[char] = '1' + codes[char]

        # Push merged node
        merged_chars = []
        if isinstance(left_char, str):
            merged_chars.append(left_char)
        else:
            merged_chars.extend(left_char)
        if isinstance(right_char, str):
            merged_chars.append(right_char)
        else:
            merged_chars.extend(right_char)

        heapq.heappush(heap, (left_freq + right_freq, merged_chars))

    return codes, freq_table

# Approach 3: Canonical Huffman Coding
def huffman_canonical(text):
    """
    Canonical Huffman coding implementation.
    Produces standardized codes that can be reconstructed with just code lengths.
    Useful for interoperability between systems.
    """
    # First build regular Huffman codes
    codes, freq_table = huffman_basic(text)

    if not codes:
        return codes, freq_table

    # Get code lengths for each symbol
    code_lengths = {char: len(code) for char, code in codes.items()}

    # Sort symbols by code length, then by symbol value
    sorted_symbols = sorted(code_lengths.keys(), key=lambda x: (code_lengths[x], x))

    # Generate canonical codes
    canonical_codes = {}
    current_code = 0
    prev_length = 0

    for symbol in sorted_symbols:
        length = code_lengths[symbol]
        if length > prev_length:
            current_code <<= (length - prev_length)
        canonical_codes[symbol] = bin(current_code)[2:].rjust(length, '0')
        current_code += 1
        prev_length = length

    return canonical_codes, freq_table

# Approach 4: Adaptive Huffman Coding (FGK Algorithm)
class AdaptiveHuffman:
    """
    Adaptive Huffman coding (FGK algorithm) implementation.
    Builds the tree dynamically as data is processed.
    Useful for streaming data where full dataset isn't available upfront.
    """
    def __init__(self):
        # NYT (Not Yet Transmitted) node
        self.root = HuffmanNode(0, "NYT")
        self.nodes = {"NYT": self.root}
        self.seen = {}

    def encode(self, text):
        """Encode text using adaptive Huffman coding"""
        output = []
        for char in text:
            output.append(self._encode_char(char))
            self._update_tree(char)
        return ''.join(output)

    def _encode_char(self, char):
        """Encode a single character"""
        if char in self.seen:
            node = self.seen[char]
            return self._get_code(node)
        else:
            nyt_code = self._get_code(self.nodes["NYT"])
            return nyt_code + format(ord(char), '08b')  # Send ASCII as fallback

    def _get_code(self, node):
        """Get code for a node by traversing up to root"""
        code = []
        while node != self.root:
            parent = None
            # Find parent (this is inefficient, but kept simple for demonstration)
            for n in self.nodes.values():
                if n.left == node or n.right == node:
                    parent = n
                    break
            if parent.left == node:
                code.append('0')
            else:
                code.append('1')
            node = parent
        return ''.join(reversed(code))

    def _update_tree(self, char):
        """Update the tree after processing a character"""
        if char in self.seen:
            node = self.seen[char]
        else:
            # Split NYT node
            nyt_node = self.nodes["NYT"]
            nyt_node.char = None
            nyt_node.left = HuffmanNode(0, "NYT")
            nyt_node.right = HuffmanNode(1, char)

            self.nodes["NYT"] = nyt_node.left
            self.seen[char] = nyt_node.right
            self.nodes[char] = nyt_node.right
            node = nyt_node  # Now update frequencies up the tree

        # Update frequencies up the tree
        while node is not None:
            node.freq += 1
            # Check for sibling with higher frequency to swap (not implemented for simplicity)
            node = None  # Normally would find parent here

# Approach 5: Huffman Coding with Binary Heap and Bitarray
def huffman_bitarray(text):
    """
    Huffman coding implementation using bitarray for more efficient bit manipulation.
    More suitable for actual production systems dealing with binary data.
    """
    try:
        from bitarray import bitarray
    except ImportError:
        print("bitarray module not found. Please install it with 'pip install bitarray'")
        return None, None, None

    # First build regular Huffman codes
    codes, freq_table = huffman_basic(text)

    if not codes:
        return bitarray(), None, {}

    # Convert codes to bitarray format
    bit_codes = {char: bitarray(code) for char, code in codes.items()}

    # Encode the text
    encoded = bitarray()
    for char in text:
        encoded += bit_codes[char]

    return encoded, freq_table, codes

# Approach 6: Parallel Huffman Coding (Map-Reduce Style)
def huffman_parallel(text, chunk_size=1000):
    """
    Parallel implementation of Huffman coding using chunking.
    Processes text in chunks and combines results.
    Useful for very large datasets that need parallel processing.
    """
    from multiprocessing import Pool

    if not text:
        return {}, {}

    # Split text into chunks
    chunks = [text[i:i+chunk_size] for i in range(0, len(text), chunk_size)]

    # Process each chunk in parallel
    with Pool() as pool:
        results = pool.map(huffman_basic, chunks)

    # Combine frequency tables
    combined_freq = defaultdict(int)
    for _, freq_table in results:
        for char, freq in freq_table.items():
            combined_freq[char] += freq

    # Build global Huffman tree
    heap = []
    for char, freq in combined_freq.items():
        heapq.heappush(heap, HuffmanNode(freq, char))

    while len(heap) > 1:
        left = heapq.heappop(heap)
        right = heapq.heappop(heap)
        merged = HuffmanNode(left.freq + right.freq)
        merged.left = left
        merged.right = right
        heapq.heappush(heap, merged)

    # Generate global codes
    root = heapq.heappop(heap)
    global_codes = {}

    def traverse(node, current_code):
        if node.char is not None:
            global_codes[node.char] = current_code
            return
        traverse(node.left, current_code + "0")
        traverse(node.right, current_code + "1")

    traverse(root, "")

    return global_codes, combined_freq

# Utility functions
def print_results(method_name, codes, freq_table):
    """Print results in a readable format"""
    print(f"\n{method_name} Results:")
    print("Character | Frequency | Huffman Code")
    print("------------------------------------")
    for char in sorted(codes.keys()):
        print(f"'{char}'     | {freq_table[char]:9} | {codes[char]}")

def calculate_compression_ratio(original_text, codes):
    """Calculate compression ratio"""
    original_bits = len(original_text) * 8
    compressed_bits = sum(len(codes[char]) for char in original_text)
    ratio = compressed_bits / original_bits
    return ratio

# Demo
if __name__ == "__main__":
    sample_text = "this is an example for huffman encoding"

    print("Original text:", sample_text)
    print("Original size (bits):", len(sample_text) * 8)

    # Test all approaches
    approaches = [
        ("Basic Textbook Implementation", huffman_basic),
        ("Memory-Efficient Implementation", huffman_memory_efficient),
        ("Canonical Huffman Coding", huffman_canonical),
        # Adaptive requires different handling
        ("Huffman with Bitarray", huffman_bitarray),
        ("Parallel Huffman Coding", huffman_parallel)
    ]

    for name, func in approaches:
        if name == "Adaptive Huffman Coding":
            adaptive = AdaptiveHuffman()
            encoded = adaptive.encode(sample_text)
            print(f"\n{name} Results:")
            print("Encoded binary:", encoded)
            print("Encoded size (bits):", len(encoded))
            original_size = len(sample_text) * 8
            ratio = len(encoded) / original_size
            print(f"Compression ratio: {ratio:.2f}")
        elif name == "Huffman with Bitarray":
            encoded, freq_table, codes = func(sample_text)
            if encoded is not None:
                print_results(name, codes, freq_table)
                ratio = calculate_compression_ratio(sample_text, codes)
                print(f"Compression ratio: {ratio:.2f}")
                print("Encoded binary:", encoded.to01())
        else:
            codes, freq_table = func(sample_text)
            print_results(name, codes, freq_table)
            ratio = calculate_compression_ratio(sample_text, codes)
            print(f"Compression ratio: {ratio:.2f}")