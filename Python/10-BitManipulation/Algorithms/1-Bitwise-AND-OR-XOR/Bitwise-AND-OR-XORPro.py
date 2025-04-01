def print_binary(number):
    """
    Helper function to print the binary representation of a number, padded to 8 bits.

    Args:
        number (int): The integer to print in binary.
    """
    if not isinstance(number, int):
        print("Invalid input: Please provide an integer.")
        return
    if number < 0:
        print("Negative numbers are not handled in this simplified binary representation.")
        return
    print(f"{number:08b}")  # Pad with zeros to 8 bits.  For larger numbers, adjust the 8.

def bitwise_and_example(num1, num2):
    """
    Example of Bitwise AND (&) operation.

    Args:
        num1 (int): The first integer.
        num2 (int): The second integer.

    Returns:
        int: The result of the bitwise AND operation.
    """
    print("\nBitwise AND Example:")
    print(f"Number 1: {num1} (Binary: ", end="")
    print_binary(num1)
    print(f"Number 2: {num2} (Binary: ", end="")
    print_binary(num2)
    result = num1 & num2
    print(f"Result: {result} (Binary: ", end="")
    print_binary(result)
    return result

def bitwise_or_example(num1, num2):
    """
    Example of Bitwise OR (|) operation.

    Args:
        num1 (int): The first integer.
        num2 (int): The second integer.

    Returns:
        int: The result of the bitwise OR operation.
    """
    print("\nBitwise OR Example:")
    print(f"Number 1: {num1} (Binary: ", end="")
    print_binary(num1)
    print(f"Number 2: {num2} (Binary: ", end="")
    print_binary(num2)
    result = num1 | num2
    print(f"Result: {result} (Binary: ", end="")
    print_binary(result)
    return result

def bitwise_xor_example(num1, num2):
    """
    Example of Bitwise XOR (^) operation.

    Args:
        num1 (int): The first integer.
        num2 (int): The second integer.

    Returns:
        int: The result of the bitwise XOR operation.
    """
    print("\nBitwise XOR Example:")
    print(f"Number 1: {num1} (Binary: ", end="")
    print_binary(num1)
    print(f"Number 2: {num2} (Binary: ", end="")
    print_binary(num2)
    result = num1 ^ num2
    print(f"Result: {result} (Binary: ", end="")
    print_binary(result)
    return result

def bit_masking_example():
    """
    Example of Bit Masking to extract specific bits.
    Real-world application: Reading status flags from a register in embedded systems.
    """
    print("\nBit Masking Example:")
    status_register = 0b11010110  # Example status register value
    print(f"Status Register: {status_register} (Binary: ", end="")
    print_binary(status_register)

    # Define masks for the bits we want to extract
    mask_bit_3 = 0b00001000  # Mask for bit 3 (remember, we start at bit 0)
    mask_bit_5 = 0b00100000  # Mask for bit 5
    mask_bits_0_2 = 0b00000111 # Mask for bits 0, 1, and 2

    # Extract the bits using bitwise AND
    bit_3_value = (status_register & mask_bit_3) >> 3  # Right shift to get the bit value
    bit_5_value = (status_register & mask_bit_5) >> 5
    bits_0_2_value = status_register & mask_bits_0_2

    print(f"Bit 3 Value: {bit_3_value}")
    print(f"Bit 5 Value: {bit_5_value}")
    print(f"Bits 0-2 Value: {bits_0_2_value}")

def bit_toggling_example():
    """
    Example of Bit Toggling using XOR.
    Real-world application: Flipping the state of a GPIO pin in embedded systems,
                       or toggling a boolean flag in a program.
    """
    print("\nBit Toggling Example:")
    control_register = 0b10101010  # Example control register
    print(f"Control Register: {control_register} (Binary: ", end="")
    print_binary(control_register)

    # Toggle bit 2 (index 2)
    toggle_mask = 0b00000100
    control_register = control_register ^ toggle_mask
    print(f"After toggling bit 2: {control_register} (Binary: ", end="")
    print_binary(control_register)

    # Toggle bit 5 (index 5)
    toggle_mask = 0b00100000
    control_register = control_register ^ toggle_mask
    print(f"After toggling bit 5: {control_register} (Binary: ", end="")
    print_binary(control_register)
    return control_register

def check_if_power_of_two(n):
    """
    Checks if a number is a power of two using bitwise AND.
    Real-world application: Optimizing certain algorithms or data structures
                         that rely on powers of two (e.g., memory allocation,
                         fast Fourier transform).
    """
    print("\nCheck if Power of Two:")
    print(f"Number: {n}")
    if n <= 0:
        print(f"{n} is not a power of two.")
        return False
    # A power of two has only one bit set.  n & (n-1) clears the least significant bit.
    if (n & (n - 1)) == 0:
        print(f"{n} is a power of two.")
        return True
    else:
        print(f"{n} is not a power of two.")
        return False

def count_set_bits(n):
    """
    Counts the number of set bits (1s) in an integer using bitwise operations.
    Brian Kernighan's Algorithm
    Real-world application: Determining the Hamming weight of a number,
                         which has applications in cryptography, error detection,
                         and image processing.
    """
    print("\nCount Set Bits:")
    print(f"Number: {n} (Binary: ", end="")
    print_binary(n)
    count = 0
    while n > 0:
        n &= (n - 1)  # Clear the least significant set bit
        count += 1
    print(f"Number of set bits: {count}")
    return count

def main():
    """
    Main function to execute the examples.
    """
    num1 = 10  # Binary: 1010
    num2 = 6   # Binary: 0110

    bitwise_and_example(num1, num2)
    bitwise_or_example(num1, num2)
    bitwise_xor_example(num1, num2)
    bit_masking_example()
    bit_toggling_example()
    check_if_power_of_two(16)
    check_if_power_of_two(20)
    count_set_bits(0b10110101)  # Binary: 10110101 (7 set bits)

if __name__ == "__main__":
    main()
