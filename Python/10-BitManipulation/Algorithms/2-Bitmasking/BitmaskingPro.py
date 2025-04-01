"""
Bit Manipulation and Bitmasking in Python: 6 Approaches with Real-World Examples

Bit manipulation is the process of performing operations on individual bits (binary digits) of a number.
Bitmasking is a technique that uses bitwise operations to manipulate and extract specific sets of bits within a number.

This document explores six different approaches to bit manipulation and bitmasking in Python,
demonstrating their applications with real-world project implementations.

1.  Basic Bitwise Operations (AND, OR, XOR, NOT, Left Shift, Right Shift)
2.  Bitmasking for Feature Flags
3.  Bitmasking for Set Operations
4.  Bitmasking for Subsets
5.  Bit Manipulation for Optimized Counting
6.  Bit Manipulation for Graphics and Image Processing (Simplified)

"""

# 1. Basic Bitwise Operations
#    -   AND (&): Sets a bit to 1 only if both bits are 1.
#    -   OR (|): Sets a bit to 1 if either or both bits are 1.
#    -   XOR (^): Sets a bit to 1 if the bits are different.
#    -   NOT (~): Inverts all the bits.
#    -   Left Shift (<<): Shifts bits to the left, filling with zeros.
#    -   Right Shift (>>): Shifts bits to the right.  Behavior with signed numbers can vary.

def basic_bitwise_operations(a, b):
    """
    Demonstrates basic bitwise operations.

    Args:
        a: An integer.
        b: An integer.

    Returns:
        A dictionary containing the results of AND, OR, XOR, NOT (on a),
        left shift (a << 2), and right shift (a >> 2) operations.
    """
    results = {
        "AND": a & b,
        "OR": a | b,
        "XOR": a ^ b,
        "NOT a": ~a,
        "Left Shift (a << 2)": a << 2,
        "Right Shift (a >> 2)": a >> 2,
    }
    return results

# Example Usage
print("\n1. Basic Bitwise Operations:")
a = 10  # 1010 in binary
b = 7   # 0111 in binary
print(basic_bitwise_operations(a, b))
# Expected Output:
# {
#     'AND': 2,
#     'OR': 15,
#     'XOR': 13,
#     'NOT a': -11,
#     'Left Shift (a << 2)': 40,
#     'Right Shift (a >> 2)': 2
# }


# 2. Bitmasking for Feature Flags
#    -   Real-world application:  Enabling/disabling features in a software application.
#    -   Each bit in a number represents the state of a feature (1 for enabled, 0 for disabled).

def set_feature_flag(flags, feature_bit):
    """
    Sets a specific feature flag in the flags bitmask.

    Args:
        flags: The current flags bitmask (integer).
        feature_bit: The bit position representing the feature to enable (integer, 0-indexed).

    Returns:
        The updated flags bitmask with the feature enabled.
    """
    return flags | (1 << feature_bit)

def clear_feature_flag(flags, feature_bit):
    """
    Clears a specific feature flag in the flags bitmask.

    Args:
        flags: The current flags bitmask (integer).
        feature_bit: The bit position representing the feature to disable (integer, 0-indexed).

    Returns:
        The updated flags bitmask with the feature disabled.
    """
    return flags & ~(1 << feature_bit)

def check_feature_flag(flags, feature_bit):
    """
    Checks if a specific feature flag is set.

    Args:
        flags: The flags bitmask (integer).
        feature_bit: The bit position representing the feature to check (integer, 0-indexed).

    Returns:
        True if the feature is enabled, False otherwise.
    """
    return (flags >> feature_bit) & 1 == 1

# Example Usage
print("\n2. Bitmasking for Feature Flags:")
FEATURE_NEW_UI = 0
FEATURE_DARK_MODE = 1
FEATURE_ADVANCED_SEARCH = 2

flags = 0  # Initially, no features are enabled (0000 in binary)

flags = set_feature_flag(flags, FEATURE_NEW_UI)
print(f"Set New UI: {flags:b} (binary), {flags} (decimal)")  # Output: 0001, 1
flags = set_feature_flag(flags, FEATURE_DARK_MODE)
print(f"Set Dark Mode: {flags:b} (binary), {flags} (decimal)") # Output: 0011, 3

print(f"Is New UI enabled? {check_feature_flag(flags, FEATURE_NEW_UI)}") # Output: True
print(f"Is Advanced Search enabled? {check_feature_flag(flags, FEATURE_ADVANCED_SEARCH)}") # Output: False

flags = clear_feature_flag(flags, FEATURE_NEW_UI)
print(f"Clear New UI: {flags:b} (binary), {flags} (decimal)") # Output: 0010, 2



# 3. Bitmasking for Set Operations
#    -   Real-world application: Representing sets and performing operations like union, intersection, and difference.
#    -   Each bit represents the presence or absence of an element in the set.

def set_union(set1, set2):
    """
    Calculates the union of two sets represented as bitmasks.

    Args:
        set1: The first set (integer bitmask).
        set2: The second set (integer bitmask).

    Returns:
        The union of the two sets (integer bitmask).
    """
    return set1 | set2

def set_intersection(set1, set2):
    """
    Calculates the intersection of two sets represented as bitmasks.

    Args:
        set1: The first set (integer bitmask).
        set2: The second set (integer bitmask).

    Returns:
        The intersection of the two sets (integer bitmask).
    """
    return set1 & set2

def set_difference(set1, set2):
    """
    Calculates the difference between two sets (set1 - set2) represented as bitmasks.

    Args:
        set1: The first set (integer bitmask).
        set2: The second set (integer bitmask).

    Returns:
        The difference between the two sets (integer bitmask).
    """
    return set1 & ~set2

# Example Usage
print("\n3. Bitmasking for Set Operations:")
# Suppose we have a universe of 5 elements {a, b, c, d, e}
# Let's represent sets using bitmasks:
# a: 00001, b: 00010, c: 00100, d: 01000, e: 10000
set1 = 0b00110  # {b, c}
set2 = 0b01100  # {c, d}

union_set = set_union(set1, set2)
print(f"Union: {union_set:b} (binary), {union_set} (decimal)")  # {b, c, d}

intersection_set = set_intersection(set1, set2)
print(f"Intersection: {intersection_set:b} (binary), {intersection_set} (decimal)")  # {c}

difference_set = set_difference(set1, set2)
print(f"Difference (set1 - set2): {difference_set:b} (binary), {difference_set} (decimal)")  # {b}



# 4. Bitmasking for Subsets
#    -   Real-world application: Generating all possible combinations or subsets of a given set.
#    -   Each bitmask represents a subset, where a 1 indicates the presence of an element and a 0 indicates its absence.

def generate_subsets(elements):
    """
    Generates all possible subsets of a given set.

    Args:
        elements: A list of elements.

    Returns:
        A list of lists, where each inner list represents a subset.
    """
    n = len(elements)
    subsets = []
    for i in range(2**n):  # Iterate through all possible bitmasks (0 to 2^n - 1)
        subset = []
        for j in range(n):
            if (i >> j) & 1:  # Check if the j-th bit is set in the current bitmask
                subset.append(elements[j])
        subsets.append(subset)
    return subsets

# Example Usage
print("\n4. Bitmasking for Subsets:")
my_set = ['a', 'b', 'c']
all_subsets = generate_subsets(my_set)
print(f"All Subsets: {all_subsets}")
# Expected Output:
# All Subsets: [[], ['a'], ['b'], ['a', 'b'], ['c'], ['a', 'c'], ['b', 'c'], ['a', 'b', 'c']]



# 5. Bit Manipulation for Optimized Counting
#   - Real-world application: Counting set bits (number of 1s) in a number efficiently.
#   - Useful in scenarios where you need to analyze the properties of a binary representation.
def count_set_bits(n):
    """
    Counts the number of set bits (1s) in an integer using Brian Kernighan's Algorithm.
    This is more efficient than iterating through the bits.

    Args:
        n: The integer.

    Returns:
        The number of set bits in n.
    """
    count = 0
    while n > 0:
        n &= (n - 1)  # Clears the least significant set bit
        count += 1
    return count

# Example Usage
print("\n5. Bit Manipulation for Optimized Counting:")
num = 0b101101  # 45 in decimal
set_bit_count = count_set_bits(num)
print(f"Number of set bits in {num:b} ({num}): {set_bit_count}")  # Output: 3

# 6. Bit Manipulation for Graphics and Image Processing (Simplified)
#    -   Real-world application:  Basic color manipulation (simplified for demonstration).
#    -   In real image processing, libraries like Pillow/OpenCV are used, but this illustrates the core concept.
def get_red_component(color):
    """
    Extracts the red component from a 24-bit RGB color.

    Args:
        color: A 24-bit RGB color represented as an integer (0xRRGGBB).

    Returns:
        The red component (0-255).
    """
    return (color >> 16) & 0xFF

def get_green_component(color):
    """
    Extracts the green component from a 24-bit RGB color.

    Args:
        color: A 24-bit RGB color represented as an integer (0xRRGGBB).

    Returns:
        The green component (0-255).
    """
    return (color >> 8) & 0xFF

def get_blue_component(color):
    """
    Extracts the blue component from a 24-bit RGB color.

    Args:
        color: A 24-bit RGB color represented as an integer (0xRRGGBB).

    Returns:
        The blue component (0-255).
    """
    return color & 0xFF

def combine_rgb(red, green, blue):
    """
    Combines red, green, and blue components into a 24-bit RGB color.

    Args:
        red: The red component (0-255).
        green: The green component (0-255).
        blue: The blue component (0-255).

    Returns:
        A 24-bit RGB color represented as an integer (0xRRGGBB).
    """
    return (red << 16) | (green << 8) | blue

# Example Usage
print("\n6. Bit Manipulation for Graphics and Image Processing (Simplified):")
color = 0xFF8000  # Orange (255, 128, 0) in hexadecimal
red = get_red_component(color)
green = get_green_component(color)
blue = get_blue_component(color)
print(f"Color: 0x{color:06X}, Red: {red}, Green: {green}, Blue: {blue}")

# Example of modifying the color (making it more red)
new_color = combine_rgb(255, 0, 0) #pure red
print(f"New Color: 0x{new_color:06X}")
