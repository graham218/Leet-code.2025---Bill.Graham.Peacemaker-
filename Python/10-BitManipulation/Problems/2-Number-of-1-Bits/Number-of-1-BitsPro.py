def count_set_bits_approach1(n):
    """
    Approach 1: Iterative Bit Check (Right Shift)

    This is a straightforward approach where we repeatedly check the least significant bit (LSB)
    and right-shift the number until it becomes zero.  This is similar to how you might inspect
    the individual bits of a number in a very low-level, hardware-oriented context.

    Args:
        n: The integer whose set bits we want to count.

    Returns:
        The number of set bits in n.

    Example:
        count_set_bits_approach1(13)  # 13 (1101 in binary) has three 1s. Returns 3
    """
    count = 0
    while n > 0:
        # Check if the LSB is 1 using the modulo operator.
        if n % 2 == 1:
            count += 1
        # Right-shift n by 1 (equivalent to dividing by 2 and discarding the remainder).
        n = n // 2
    return count

def count_set_bits_approach2(n):
    """
    Approach 2: Iterative Bit Check (Bitwise AND with 1)

    This approach is similar to the first one, but instead of using the modulo operator,
    it uses the bitwise AND operator (&) to check if the least significant bit is 1.
    This is a very common and efficient way to isolate the LSB in bit manipulation.  It's often
    used in embedded systems or performance-critical applications.

    Args:
        n: The integer.

    Returns:
        The number of set bits.

    Example:
        count_set_bits_approach2(7) # 7 (111 in binary) has three 1s. Returns 3
    """
    count = 0
    while n > 0:
        # Check if the LSB is 1 by performing a bitwise AND with 1.
        if n & 1:
            count += 1
        # Right-shift n by 1.
        n = n >> 1
    return count


def count_set_bits_approach3(n):
    """
    Approach 3: Brian Kernighan's Algorithm

    This is a very clever and efficient algorithm.  The key idea is that the expression `n & (n - 1)`
    removes the least significant set bit of n.  By repeatedly applying this operation,
    we can count the number of times we remove a set bit, which is equal to the total
    number of set bits.  This algorithm is often used in performance-sensitive scenarios
    where minimizing the number of operations is crucial.

    Args:
        n: The integer.

    Returns:
        The number of set bits.

    Example:
        count_set_bits_approach3(9)  # 9 (1001 in binary) has two 1s. Returns 2
    """
    count = 0
    while n > 0:
        n &= (n - 1)  # Clear the least significant set bit
        count += 1
    return count


def count_set_bits_approach4(n):
    """
    Approach 4: Using the built-in bin() function and counting '1's

    This approach leverages Python's built-in `bin()` function, which converts an integer to its
    binary representation as a string (e.g., '0b1011').  We then simply count the number of '1'
    characters in the string.  This is a concise and readable way to achieve the goal,
    and it's often preferred for its simplicity when performance is not the absolute
    top priority.

    Args:
        n: The integer.

    Returns:
        The number of set bits.

    Example:
        count_set_bits_approach4(15) # 15 (1111 in binary) has four 1s. Returns 4
    """
    return bin(n).count('1')



import ctypes  # Import the ctypes library

def count_set_bits_approach5(n):
    """
    Approach 5: Using ctypes for unsigned 32-bit integer and a loop

    This approach uses the ctypes library to work with unsigned 32-bit integers,
    which can be useful when dealing with specific data types or interfacing with
    C libraries.  It then iterates through the bits of the number, similar to
    the first approach.  This is more explicit about the data type and can be
    helpful in certain low-level applications.

    Args:
        n: The integer.

    Returns:
        The number of set bits.
    """
    # Ensure n is treated as an unsigned 32-bit integer.
    n = ctypes.c_uint32(n).value
    count = 0
    while n > 0:
        if n & 1:
            count += 1
        n >>= 1
    return count


def count_set_bits_approach6(n):
    """
    Approach 6: Using bit_count() method (Python 3.10+)

    This is the most modern and often the most efficient approach in recent versions of Python.
    The `int.bit_count()` method is a built-in function specifically designed for this purpose.
    It's typically implemented using highly optimized machine instructions, making it very fast.
    If you're using Python 3.10 or later, this is the recommended way to count set bits.

    Args:
        n: The integer.

    Returns:
        The number of set bits.

    Example:
        count_set_bits_approach6(255) # 255 (11111111 in binary) has eight 1s. Returns 8
    """
    return n.bit_count() # Direct use of the bit_count() method


if __name__ == "__main__":
    # Example usage and output for each approach
    number = 42  # Example number (binary representation: 00101010)

    print(f"Number: {number}")
    print(f"Binary representation: {bin(number)}") #prints the binary representation

    print("\nApproach 1: Iterative Bit Check (Right Shift)")
    result1 = count_set_bits_approach1(number)
    print(f"Number of set bits: {result1}")  # Output: 2

    print("\nApproach 2: Iterative Bit Check (Bitwise AND with 1)")
    result2 = count_set_bits_approach2(number)
    print(f"Number of set bits: {result2}")  # Output: 2

    print("\nApproach 3: Brian Kernighan's Algorithm")
    result3 = count_set_bits_approach3(number)
    print(f"Number of set bits: {result3}")  # Output: 2

    print("\nApproach 4: Using bin() and counting '1's")
    result4 = count_set_bits_approach4(number)
    print(f"Number of set bits: {result4}")  # Output: 2

    print("\nApproach 5: Using ctypes for unsigned 32-bit integer")
    result5 = count_set_bits_approach5(number)
    print(f"Number of set bits: {result5}")  # Output: 2

    print("\nApproach 6: Using bit_count() method (Python 3.10+)")
    result6 = count_set_bits_approach6(number)
    print(f"Number of set bits: {result6}")  # Output: 2
