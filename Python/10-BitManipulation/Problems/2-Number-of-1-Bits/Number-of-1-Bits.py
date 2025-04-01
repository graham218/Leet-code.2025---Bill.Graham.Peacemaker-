def count_set_bits_approach1(n):
    """
    Approach 1: Iterating through bits and checking each one.
    This approach iterates through the bits of the number, checking each one individually.

    Time Complexity: O(log n), where n is the number.  The number of iterations is
                    proportional to the number of bits in n.
    Space Complexity: O(1), constant space.
    """
    count = 0
    while n > 0:
        if n & 1:  # Check if the least significant bit is 1
            count += 1
        n >>= 1  # Right shift to check the next bit
    return count

def count_set_bits_approach2(n):
    """
    Approach 2: Using the Brian Kernighan's Algorithm.
    This approach is more efficient as it clears the least significant set bit in each iteration.

    Time Complexity: O(k), where k is the number of set bits in n.  This is because
                    the loop iterates only as many times as there are 1s in the number.
    Space Complexity: O(1), constant space.
    """
    count = 0
    while n > 0:
        n &= (n - 1)  # Clear the least significant set bit
        count += 1
    return count

def count_set_bits_approach3(n):
    """
    Approach 3: Using built-in bin() and count().
    This approach converts the integer to its binary representation (string)
    and counts the number of '1's in the string.

    Time Complexity: O(log n), where n is the number.  Converting to binary string is O(log n),
                    and count is O(log n) in the worst case.
    Space Complexity: O(log n), to store the binary string.
    """
    return bin(n).count('1')

def count_set_bits_approach4(n):
    """
    Approach 4: Using bit_count() method (Python 3.10+).
    Python 3.10 provides a built-in method to count set bits. This is the most efficient
    among the given approaches.

    Time Complexity: O(1), typically implemented using a lookup table or optimized CPU instruction.
    Space Complexity: O(1), constant space.
    """
    return n.bit_count() # Directly use the bit_count() method

def count_set_bits_approach5(n):
    """
    Approach 5: Using a lookup table (for 8-bit numbers).
    This approach pre-computes the number of set bits for all 8-bit numbers
    and stores them in a table.  For larger numbers, we process them in 8-bit chunks.
    This approach is very fast for repeated calls with smaller numbers.

    Time Complexity: O(log n), where n is the number.  We process the number in 8-bit chunks.
    Space Complexity: O(1), the lookup table size is constant (256 entries).
    """
    # Create a lookup table for 8-bit numbers
    lookup_table = [0] * 256
    for i in range(256):
        count = 0
        temp = i
        for _ in range(8): # Loop 8 times because we are dealing with 8 bits
            if temp & 1:
                count += 1
            temp >>= 1
        lookup_table[i] = count

    count = 0
    while n > 0:
        # Get the last 8 bits of n and use it as an index into the table
        count += lookup_table[n & 0xFF]  # 0xFF is 255 (11111111 in binary)
        n >>= 8  # Right shift by 8 bits
    return count

if __name__ == "__main__":
    test_number = 27  # Example number (binary 11011)
    print(f"Number: {test_number}, Binary: {bin(test_number)}")

    print("\nApproach 1: Iterating through bits")
    print(f"Number of 1 bits: {count_set_bits_approach1(test_number)}")  # Output: 3

    print("\nApproach 2: Brian Kernighan's Algorithm")
    print(f"Number of 1 bits: {count_set_bits_approach2(test_number)}")  # Output: 3

    print("\nApproach 3: Using bin() and count()")
    print(f"Number of 1 bits: {count_set_bits_approach3(test_number)}")  # Output: 3

    print("\nApproach 4: Using bit_count() (Python 3.10+)")
    print(f"Number of 1 bits: {count_set_bits_approach4(test_number)}")

    print("\nApproach 5: Using a lookup table")
    print(f"Number of 1 bits: {count_set_bits_approach5(test_number)}")
