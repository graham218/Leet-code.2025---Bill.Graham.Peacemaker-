def check_bit(number, index):
    """
    Checks if the bit at a given index is set (1) in a number.

    Args:
        number: The integer number to check.
        index: The index of the bit to check (0-based, from right to left).

    Returns:
        True if the bit at the given index is 1, False otherwise.

    Approach 1: Using Left Shift and AND
    This approach shifts the number 1 to the left by 'index' positions.
    Then, it performs a bitwise AND operation with the original number.
    If the result is non-zero, the bit at 'index' was 1.
    For example:
    number = 10 (binary 1010)
    index = 1
    1 << index = 1 << 1 = 2 (binary 0010)
    1010 & 0010 = 0010 (2 in decimal) which is non-zero, so return True
    """
    if (number & (1 << index)):
        return True
    else:
        return False

def set_bit(number, index):
    """
    Sets the bit at a given index to 1 in a number.

    Args:
        number: The integer number to modify.
        index: The index of the bit to set (0-based, from right to left).

    Returns:
        The new number with the bit at the given index set to 1.

    Approach 2: Using Bitwise OR
    This approach shifts the number 1 to the left by 'index' positions.
    Then, it performs a bitwise OR operation with the original number.
    This forces the bit at 'index' to become 1, leaving other bits unchanged.
    For example:
    number = 10 (binary 1010)
    index = 2
    1 << index = 1 << 2 = 4 (binary 0100)
    1010 | 0100 = 1110 (14 in decimal)
    """
    return number | (1 << index)

def clear_bit(number, index):
    """
    Clears (sets to 0) the bit at a given index in a number.

    Args:
        number: The integer number to modify.
        index: The index of the bit to clear (0-based, from right to left).

    Returns:
        The new number with the bit at the given index set to 0.

    Approach 3: Using Bitwise AND with Complement
    This approach creates a mask with 0 at the 'index' and 1s elsewhere.
    It shifts 1 to the left by 'index' and then inverts all bits using ~.
    Then, it performs a bitwise AND with the original number.
    This clears the bit at 'index' and leaves others unchanged.
    For example:
    number = 10 (binary 1010)
    index = 0
    1 << index = 1 << 0 = 1 (binary 0001)
    ~(1 << index) = ~0001 = 1110 (assuming 4 bits for simplicity)
    1010 & 1110 = 1010 (10 in decimal)
    """
    return number & (~(1 << index))

def toggle_bit(number, index):
    """
    Toggles (flips) the bit at a given index in a number.
    If the bit is 0, it becomes 1, and vice-versa.

    Args:
        number: The integer number to modify.
        index: The index of the bit to toggle (0-based, from right to left).

    Returns:
        The new number with the bit at the given index toggled.

    Approach 4: Using Bitwise XOR
    This approach shifts the number 1 to the left by 'index' positions.
    Then, it performs a bitwise XOR operation with the original number.
    XOR flips the bit at 'index' because 1 XOR 0 = 1 and 1 XOR 1 = 0.
    For example:
    number = 10 (binary 1010)
    index = 3
    1 << index = 1 << 3 = 8 (binary 1000)
    1010 ^ 1000 = 0010 (2 in decimal)
    """
    return number ^ (1 << index)

def get_rightmost_set_bit(number):
    """
    Gets the rightmost set bit (least significant 1) in a number.

    Args:
        number: The integer number to check.

    Returns:
        The value of the rightmost set bit.
        Returns 0 if the number is 0.

    Approach 5: Using n & -n
    This approach utilizes the property that the negation of a number
    in two's complement representation isolates the rightmost set bit.
    Performing a bitwise AND between the number and its negation
    results in a number where only the rightmost set bit is 1.
    For example:
    number = 12 (binary 1100)
    -number = -12 (binary 0100 in two's complement representation, simplified for this example)
    1100 & 0100 = 0100 (4 in decimal)
    """
    if number == 0:
        return 0
    return number & -number

def main():
    """
    Main function to demonstrate the bit manipulation functions.
    """
    number = 10  # Binary: 1010
    index = 1

    print(f"Number: {number} (Binary: {number:b})")
    print(f"Checking bit at index {index}: {check_bit(number, index)}")  # Output: True (because the 2nd bit is 1)

    number = set_bit(number, 2)
    print(f"After setting bit at index 2: {number} (Binary: {number:b})")  # Output: 14 (Binary: 1110)

    number = clear_bit(number, 1)
    print(f"After clearing bit at index 1: {number} (Binary: {number:b})")  # Output: 12 (Binary: 1100)

    number = toggle_bit(number, 0)
    print(f"After toggling bit at index 0: {number} (Binary: {number:b})")  # Output: 13 (Binary: 1101)

    number = 20 # Binary 10100
    print(f"Rightmost set bit of 20: {get_rightmost_set_bit(20)}") # Output: 4

if __name__ == "__main__":
    main()
