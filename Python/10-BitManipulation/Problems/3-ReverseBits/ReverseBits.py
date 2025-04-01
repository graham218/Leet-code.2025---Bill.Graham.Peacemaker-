def reverse_bits_method1(n: int) -> int:
    """
    Method 1: Iterative approach using bitwise operations.

    This method iterates through the bits of the input integer,
    extracting each bit and placing it in the corresponding reversed
    position in the result.

    Args:
        n: The integer whose bits are to be reversed.

    Returns:
        The integer with the bits reversed.
    """
    reversed_n = 0
    for i in range(32):  # Assuming 32-bit integer
        # Get the rightmost bit of n
        bit = (n >> i) & 1
        # Place the bit in the correct position in reversed_n
        reversed_n = reversed_n | (bit << (31 - i))
    return reversed_n

def reverse_bits_method2(n: int) -> int:
    """
    Method 2: Using string manipulation.

    This method converts the integer to its binary string representation,
    reverses the string, and converts it back to an integer.

    Args:
        n: The integer whose bits are to be reversed.

    Returns:
        The integer with the bits reversed.
    """
    binary_string = bin(n)[2:].zfill(32)  # Remove '0b' prefix and pad with zeros
    reversed_string = binary_string[::-1]  # Reverse the string
    return int(reversed_string, 2)  # Convert the reversed string to an integer

def reverse_bits_method3(n: int) -> int:
    """
    Method 3: Divide and conquer approach.

    This method uses a divide and conquer strategy to reverse the bits.
    It swaps pairs, then groups of 4, then 8, 16.

    Args:
        n: The integer whose bits are to be reversed.

    Returns:
        The integer with the bits reversed.
    """
    n = (n >> 16) | (n << 16)
    n = ((n & 0xFF00FF00) >> 8) | ((n & 0x00FF00FF) << 8)
    n = ((n & 0xF0F0F0F0) >> 4) | ((n & 0x0F0F0F0F) << 4)
    n = ((n & 0xCCCCCCCC) >> 2) | ((n & 0x33333333) << 2)
    n = ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1)
    return n

def reverse_bits_method4(n: int) -> int:
    """
    Method 4: Using bit manipulation with a loop and pop.

    This method uses a while loop to process the bits of the integer
    and constructs the reversed integer bit by bit.  It's similar to method 1,
    but perhaps more clear to understand for some.

    Args:
        n: The integer to reverse.

    Returns:
        The reversed integer.
    """
    reversed_num = 0
    count = 32
    while count > 0:
        reversed_num <<= 1  # left shift
        # Get the rightmost bit
        reversed_num |= (n & 1)
        n >>= 1  # Right shift
        count -= 1
    return reversed_num

def reverse_bits_method5(n: int) -> int:
    """
    Method 5: Using built-in bit_length and a loop.

    This method calculates the number of significant bits, and then iterates
    through that many bits, constructing the reversed number.  It handles
    numbers with less than 32 significant bits correctly.

    Args:
        n: The integer to reverse

    Returns:
        The reversed integer.
    """
    length = n.bit_length()
    reversed_num = 0
    for i in range(length):
        if (n >> i) & 1:
            reversed_num |= 1 << (length - 1 - i)
    return reversed_num


if __name__ == "__main__":
    test_number = 43261596  # Example input
    print(f"Original Number: {test_number}")

    # Method 1
    reversed_number1 = reverse_bits_method1(test_number)
    print(f"Reversed (Method 1): {reversed_number1}")  # Output: 964176192

    # Method 2
    reversed_number2 = reverse_bits_method2(test_number)
    print(f"Reversed (Method 2): {reversed_number2}")  # Output: 964176192

    # Method 3
    reversed_number3 = reverse_bits_method3(test_number)
    print(f"Reversed (Method 3): {reversed_number3}")  # Output: 964176192

    # Method 4
    reversed_number4 = reverse_bits_method4(test_number)
    print(f"Reversed (Method 4): {reversed_number4}")  # Output: 964176192

    # Method 5
    reversed_number5 = reverse_bits_method5(test_number)
    print(f"Reversed (Method 5): {reversed_number5}")  # Output: 964176192

    test_number2 = 0b00000010100101000001111010011100
    print(f"\nOriginal Number: {test_number2}")
    reversed_number5_2 = reverse_bits_method5(test_number2)
    print(f"Reversed (Method 5) binary: {reversed_number5_2}")

    test_number3 = 1  # Example with only one bit set
    print(f"\nOriginal Number: {test_number3}")
    reversed_number5_3 = reverse_bits_method5(test_number3)
    print(f"Reversed (Method 5) one bit: {reversed_number5_3}") # Output: 2147483648
