import heapq
from collections import defaultdict

class Node:
    """
    A class representing a node in the Huffman tree.
    Each node has a frequency, a character (optional for internal nodes),
    a left child, and a right child.
    """
    def __init__(self, freq, char=None, left=None, right=None):
        self.freq = freq  # Frequency of the character or combined frequency
        self.char = char  # Character represented by the node (None for internal nodes)
        self.left = left  # Left child node
        self.right = right  # Right child node

    def __lt__(self, other):
        """
        Comparison method to compare two nodes based on their frequencies.
        This is crucial for using the Node class with the heapq module.
        """
        return self.freq < other.freq

    def __repr__(self):
        """
        String representation of the node, useful for debugging and printing.
        """
        return f"Node(freq={self.freq}, char={self.char})"

def calculate_frequency(data):
    """
    Calculates the frequency of each character in the input data.

    Args:
        data (str): The input string.

    Returns:
        dict: A dictionary where keys are characters and values are their frequencies.
              Returns an empty dictionary if the input data is empty.
    """
    if not data:
        return {}
    frequency = defaultdict(int)
    for char in data:
        frequency[char] += 1
    return frequency

def build_huffman_tree(frequency):
    """
    Builds the Huffman tree based on the character frequencies.

    Args:
        frequency (dict): A dictionary of character frequencies.

    Returns:
        Node: The root node of the Huffman tree.  Returns None if the frequency dict is empty.
    """
    if not frequency:
        return None

    # Create a priority queue (min-heap) of nodes
    heap = [Node(freq, char) for char, freq in frequency.items()]
    heapq.heapify(heap)

    # If there is only one unique character, return a single node tree
    if len(heap) == 1:
        return heap[0]

    # Merge nodes until only one node (the root) is left
    while len(heap) > 1:
        left = heapq.heappop(heap)  # Get the two nodes with the lowest frequencies
        right = heapq.heappop(heap)
        merged_node = Node(left.freq + right.freq, left=left, right=right)  # Create a new node
        heapq.heappush(heap, merged_node)  # Add the merged node back to the queue

    return heapq.heappop(heap)  # The last remaining node is the root of the tree

def generate_huffman_codes(node, code="", mapping=None):
    """
    Generates the Huffman codes for each character by traversing the tree.
    This is a recursive function.

    Args:
        node (Node): The current node in the Huffman tree.
        code (str, optional): The current Huffman code string. Defaults to "".
        mapping (dict, optional): The dictionary to store the character-code mappings.
                           If None, a new dictionary is created. Defaults to None.

    Returns:
        dict: A dictionary where keys are characters and values are their Huffman codes.
              Returns an empty dictionary if the input node is None.
    """
    if mapping is None:
        mapping = {}

    if node is None:
        return {}

    if node.char:  # If it's a leaf node, we have a complete code
        mapping[node.char] = code
        return mapping

    # Traverse left and right subtrees, adding "0" and "1" to the code, respectively
    generate_huffman_codes(node.left, code + "0", mapping)
    generate_huffman_codes(node.right, code + "1", mapping)
    return mapping

def encode_data(data, code_mapping):
    """
    Encodes the input data using the generated Huffman codes.

    Args:
        data (str): The input string to be encoded.
        code_mapping (dict): A dictionary of character-to-Huffman code mappings.

    Returns:
        str: The encoded string. Returns an empty string if input data or code_mapping is empty.
    """
    if not data or not code_mapping:
        return ""
    encoded_data = "".join(code_mapping[char] for char in data)
    return encoded_data

def decode_data(encoded_data, root):
    """
    Decodes the encoded data using the Huffman tree.

    Args:
        encoded_data (str): The encoded string.
        root (Node): The root node of the Huffman tree.

    Returns:
        str: The decoded string. Returns an empty string if either input is empty.
    """
    if not encoded_data or not root:
        return ""

    decoded_data = ""
    current_node = root
    for bit in encoded_data:
        if bit == "0":
            current_node = current_node.left
        else:
            current_node = current_node.right

        if current_node.char:  # If it's a leaf node, we found a character
            decoded_data += current_node.char
            current_node = root  # Reset to the root to start decoding the next character
    return decoded_data

def huffman_coding(data):
    """
    Performs Huffman coding on the input data.  This is the main function.

    Args:
        data (str): The input string to be encoded.

    Returns:
        tuple: A tuple containing:
            - str: The encoded string.
            - dict: The character-to-Huffman code mapping.
            - Node: The root node of the Huffman tree.
    """
    frequency = calculate_frequency(data)
    root = build_huffman_tree(frequency)
    if root is None:
        return "", {}, None  # Handle empty input
    code_mapping = generate_huffman_codes(root)
    encoded_data = encode_data(data, code_mapping)
    return encoded_data, code_mapping, root

# ----------------------------
# 1. Huffman Coding: Basic
# ----------------------------
def huffman_coding_basic(data):
    """
    Basic implementation of Huffman coding.

    Args:
        data (str): The input string.

    Returns:
       tuple: (encoded string, code mapping, Huffman tree root)
    """
    frequency = calculate_frequency(data)
    if not frequency:
        return "", {}, None

    priority_queue = [Node(freq, char) for char, freq in frequency.items()]
    heapq.heapify(priority_queue)

    while len(priority_queue) > 1:
        left = heapq.heappop(priority_queue)
        right = heapq.heappop(priority_queue)
        merged_node = Node(left.freq + right.freq, left=left, right=right)
        heapq.heappush(priority_queue, merged_node)

    huffman_tree_root = priority_queue[0]
    code_mapping = {}
    _generate_codes(huffman_tree_root, "", code_mapping)  # Use helper function
    encoded_data = encode_data(data, code_mapping)
    return encoded_data, code_mapping, huffman_tree_root

def _generate_codes(node, current_code, code_mapping):
    """Helper function for huffman_coding_basic to generate codes recursively."""
    if node is None:
        return
    if node.char:
        code_mapping[node.char] = current_code
        return
    _generate_codes(node.left, current_code + "0", code_mapping)
    _generate_codes(node.right, current_code + "1", code_mapping)

# ----------------------------
# 2. Huffman Coding: Optimized Tree Building
# ----------------------------
def huffman_coding_optimized(data):
    """
    Huffman coding with an optimized tree building process.

    Args:
        data (str): The input string.

    Returns:
       tuple: (encoded string, code mapping, Huffman tree root)
    """
    frequency = calculate_frequency(data)
    if not frequency:
        return "", {}, None

    nodes = [Node(freq, char) for char, freq in frequency.items()]
    heapq.heapify(nodes)

    while len(nodes) > 1:
        left = heapq.heappop(nodes)
        right = heapq.heappop(nodes)
        merged_node = Node(left.freq + right.freq, left=left, right=right)
        heapq.heappush(nodes, merged_node)

    root = nodes[0]
    code_mapping = {}
    _generate_codes_optimized(root, "", code_mapping) # Use helper
    encoded_data = encode_data(data, code_mapping)
    return encoded_data, code_mapping, root

def _generate_codes_optimized(node, code, mapping):
    """Helper function for huffman_coding_optimized to generate codes."""
    if node is None:
        return
    if node.char:
        mapping[node.char] = code
        return
    _generate_codes_optimized(node.left, code + "0", mapping)
    _generate_codes_optimized(node.right, code + "1", mapping)

# ----------------------------
# 3. Huffman Coding: Using defaultdict
# ----------------------------
from collections import defaultdict

def huffman_coding_defaultdict(data):
    """
    Huffman coding using defaultdict for frequency counting.

    Args:
        data (str): The input string.

    Returns:
       tuple: (encoded string, code mapping, Huffman tree root)
    """
    frequency = defaultdict(int)
    for char in data:
        frequency[char] += 1

    if not frequency:
        return "", {}, None

    nodes = [Node(freq, char) for char, freq in frequency.items()]
    heapq.heapify(nodes)

    while len(nodes) > 1:
        left = heapq.heappop(nodes)
        right = heapq.heappop(nodes)
        merged_node = Node(left.freq + right.freq, left=left, right=right)
        heapq.heappush(nodes, merged_node)

    root = nodes[0]
    code_mapping = {}
    _generate_codes_dd(root, "", code_mapping) # Helper
    encoded_data = encode_data(data, code_mapping)
    return encoded_data, code_mapping, root

def _generate_codes_dd(node, code, mapping):
    """Helper for huffman_coding_defaultdict to generate codes."""
    if node is None:
        return
    if node.char:
        mapping[node.char] = code
        return
    _generate_codes_dd(node.left, code + "0", mapping)
    _generate_codes_dd(node.right, code + "1", mapping)

# ----------------------------
# 4. Huffman Coding: Iterative Code Generation
# ----------------------------
def huffman_coding_iterative(data):
    """
    Huffman coding with iterative code generation.

     Args:
        data (str): The input string.

    Returns:
       tuple: (encoded string, code mapping, Huffman tree root)
    """
    frequency = calculate_frequency(data)
    if not frequency:
        return "", {}, None

    nodes = [Node(freq, char) for char, freq in frequency.items()]
    heapq.heapify(nodes)

    while len(nodes) > 1:
        left = heapq.heappop(nodes)
        right = heapq.heappop(nodes)
        merged_node = Node(left.freq + right.freq, left=left, right=right)
        heapq.heappush(nodes, merged_node)

    root = nodes[0]
    code_mapping = {}
    if root: # handle edge case of empty input.
        stack = [(root, "")]
        while stack:
            node, code = stack.pop()
            if node.char:
                code_mapping[node.char] = code
            else:
                if node.right:
                    stack.append((node.right, code + "1"))
                if node.left:
                    stack.append((node.left, code + "0"))
    encoded_data = encode_data(data, code_mapping)
    return encoded_data, code_mapping, root

# ----------------------------
# 5. Huffman Coding:  Pre-Sorted Frequency List
# ----------------------------

def huffman_coding_pre_sorted(data):
    """
    Huffman coding with a pre-sorted frequency list.  This assumes the
    frequency is already provided, not calculated from the data.

    Args:
        data (list of tuples):  A list of (character, frequency) tuples.
            For example: [('a', 5), ('b', 9), ('c', 12), ('d', 13), ('e', 16), ('f', 45)]

    Returns:
       tuple: (encoded string, code mapping, Huffman tree root)
    """
    # In this version, the input 'data' is assumed to be a list of (char, freq) tuples.
    if not data:
        return "", {}, None

    nodes = [Node(freq, char) for char, freq in data]
    heapq.heapify(nodes)

    while len(nodes) > 1:
        left = heapq.heappop(nodes)
        right = heapq.heappop(nodes)
        merged_node = Node(left.freq + right.freq, left=left, right=right)
        heapq.heappush(nodes, merged_node)

    root = nodes[0]
    code_mapping = {}
    _generate_codes_ps(root, "", code_mapping) # Helper
    #  Since we don't have the original string, we can't encode it.
    return "", code_mapping, root

def _generate_codes_ps(node, code, mapping):
    """Helper for huffman_coding_pre_sorted to generate codes."""
    if node is None:
        return
    if node.char:
        mapping[node.char] = code
        return
    _generate_codes_ps(node.left, code + "0", mapping)
    _generate_codes_ps(node.right, code + "1", mapping)

def main():
    """
    Main function to demonstrate the Huffman coding implementations.
    """
    test_data = "this is an example of a huffman tree"
    print(f"Original data: {test_data}")

    # 1. Basic Huffman Coding
    print("\n1. Basic Huffman Coding:")
    encoded_basic, code_mapping_basic, root_basic = huffman_coding_basic(test_data)
    print(f"Encoded data: {encoded_basic}")
    print(f"Code mapping: {code_mapping_basic}")
    decoded_basic = decode_data(encoded_basic, root_basic)
    print(f"Decoded data: {decoded_basic}")
    print(f"Original == Decoded: {test_data == decoded_basic}")

    # 2. Optimized Tree Building
    print("\n2. Huffman Coding - Optimized Tree:")
    encoded_optimized, code_mapping_optimized, root_optimized = huffman_coding_optimized(test_data)
    print(f"Encoded data: {encoded_optimized}")
    print(f"Code mapping: {code_mapping_optimized}")
    decoded_optimized = decode_data(encoded_optimized, root_optimized)
    print(f"Decoded data: {decoded_optimized}")
    print(f"Original == Decoded: {test_data == decoded_optimized}")

    # 3. Using defaultdict
    print("\n3. Huffman Coding - defaultdict:")
    encoded_defaultdict, code_mapping_defaultdict, root_defaultdict = huffman_coding_defaultdict(test_data)
    print(f"Encoded data: {encoded_defaultdict}")
    print(f"Code mapping: {code_mapping_defaultdict}")
    decoded_defaultdict = decode_data(encoded_defaultdict, root_defaultdict)
    print(f"Decoded data: {decoded_defaultdict}")
    print(f"Original == Decoded: {test_data == decoded_defaultdict}")

    # 4. Iterative Code Generation
    print("\n4. Huffman Coding - Iterative Code Generation:")
    encoded_iterative, code_mapping_iterative, root_iterative = huffman_coding_iterative(test_data)
    print(f"Encoded data: {encoded_iterative}")
    print(f"Code mapping: {code_mapping_iterative}")
    decoded_iterative = decode_data(encoded_iterative, root_iterative)
    print(f"Decoded data: {decoded_iterative}")
    print(f"Original == Decoded: {test_data == decoded_iterative}")

    # 5. Pre-sorted Frequency List
    print("\n5. Huffman Coding - Pre-sorted Frequency List:")
    # Example pre-sorted frequency data:
    frequency_data = [('a', 5), ('b', 9), ('c', 12), ('d', 13), ('e', 16), ('f', 45)]
    encoded_presorted, code_mapping_presorted, root_presorted = huffman_coding_pre_sorted(frequency_data)
    print(f"Code mapping: {code_mapping_presorted}")
    #  We don't have the original encoded data in this case.

if __name__ == "__main__":
    main()
