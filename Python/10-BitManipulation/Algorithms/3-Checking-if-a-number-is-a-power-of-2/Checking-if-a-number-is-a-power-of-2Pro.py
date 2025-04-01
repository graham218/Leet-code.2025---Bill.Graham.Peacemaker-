def is_power_of_two_approach1(n):
    """
    Approach 1: Using the property that powers of 2 have only one bit set.

    Real-world application:
    - Optimizing resource allocation: In systems where resources are allocated in powers of 2 (e.g., memory pages, buffer sizes),
      this method can quickly validate if a requested size is a valid power of 2, preventing fragmentation and ensuring efficient use.
    - Implementing binary trees or heaps: Checking for power of 2 is crucial in data structures like complete binary trees or heaps,
      where the number of nodes at each level is a power of 2.

    Time Complexity: O(1) - Bitwise operations are constant time.
    Space Complexity: O(1) - No extra space is used.
    """
    if n <= 0:  # Handle non-positive numbers as they are not powers of 2
        return False
    return (n & (n - 1)) == 0  # Key idea: (n & (n-1)) clears the least significant bit.
    #  For powers of 2, this results in 0.

def is_power_of_two_approach2(n):
    """
    Approach 2: Repeatedly dividing by 2.

    Real-world application:
    - Image processing: Some image formats or algorithms might require dimensions (width, height) to be powers of 2.
      This method can validate image dimensions before processing or resizing.
    - Audio processing:  Buffer sizes in audio processing are often powers of 2 for efficient FFT (Fast Fourier Transform) calculations.
      This method can validate buffer sizes.

    Time Complexity: O(log n) - Number of divisions depends on the magnitude of n.
    Space Complexity: O(1) - No extra space is used.
    """
    if n <= 0:
        return False
    while n % 2 == 0:
        n //= 2  # Integer division to handle Python's behavior with large numbers
    return n == 1

def is_power_of_two_approach3(n):
    """
    Approach 3: Using logarithms.

    Real-world application:
     - Scientific computing: In simulations or modeling, you might need to check if a certain parameter or grid size
       is a power of 2 for computational efficiency.
     - Data binning or bucketing: When creating histograms or binning data, you might want the number of bins to be a power of 2
       for balanced distribution.

    Time Complexity: O(1) - Logarithm calculation is generally considered constant time.
    Space Complexity: O(1) - No extra space is used.
    """
    import math  # Import the math module

    if n <= 0:
        return False
    # Calculate log base 2.  Use math.log2 for better precision
    log_result = math.log2(n)
    # Check if the result is very close to an integer
    return abs(log_result - round(log_result)) < 1e-10 # Use a small tolerance for floating-point comparison

def is_power_of_two_approach4(n):
    """
    Approach 4:  Bit manipulation with left shift.

    Real-world application:
    - Embedded systems: In low-level programming, especially in embedded systems, generating powers of 2
      using bit shifts is common for configuring hardware registers or memory addresses. This function could validate
      if a given value matches a pre-calculated power of 2.
    - Network protocols: Some network protocols use fields with lengths that are powers of 2.  This can validate field lengths.

    Time Complexity: O(log n) - The loop iterates a maximum of log2(n) times.
    Space Complexity: O(1) - No extra space is used.
    """
    if n <= 0:
        return False
    power = 1
    while power < n:
        power <<= 1  # Left shift (multiply by 2)
    return power == n

def is_power_of_two_approach5(n):
    """
    Approach 5: Using regular expressions (string representation).

    Real-world application:
    - Input validation: When reading configuration files or user input, you might receive numbers as strings.
      This method can validate if the string represents a power of 2.  For example, validating input in a server configuration.
    - Data serialization/deserialization:  When parsing data from a file or network stream, you might need to check if a numerical
      value represented as a string is a power of 2.

    Time Complexity: O(log n) - String conversion is O(log n), regex is then applied
    Space Complexity: O(log n) -  String conversion creates a string of length log n.
    """
    import re

    if n <= 0:
        return False
    binary_representation = bin(n)[2:]  # Convert to binary string, remove "0b" prefix
    # Regular expression to check for "1" followed by all "0"s
    return re.match(r"^10*$", binary_representation) is not None

def is_power_of_two_approach6(n):
    """
    Approach 6: Using bit manipulation and counting set bits.

    Real-world application:
    - Error detection/correction: In some error detection/correction codes, the number of set bits in a data word
      can be used to detect errors.  This approach can be adapted to count set bits and check if only one bit is set.
    - Cryptography:  Bit manipulation is fundamental in cryptography.  Checking the number of set bits can be a component
      in some cryptographic algorithms.

    Time Complexity: O(log n) in the worst case, where n has many set bits.  Can be O(1) in some cases.
    Space Complexity: O(1) - No extra space is used.
    """
    if n <= 0:
        return False
    count = 0
    while n > 0:
        n &= (n - 1)  # Clear the least significant bit
        count += 1
    return count == 1 # A power of two has only one bit set

def main():
    """
    Main function to demonstrate all approaches with various test cases.
    """
    test_cases = [0, 1, 2, 3, 4, 8, 15, 16, 32, 64, 100, 128, 256, -1, -2, 1024, 2048, 4096]

    print("Checking if numbers are powers of 2:")
    print("-" * 50)

    for num in test_cases:
        print(f"\nNumber: {num}")
        print(f"Approach 1: {is_power_of_two_approach1(num)}")
        print(f"Approach 2: {is_power_of_two_approach2(num)}")
        print(f"Approach 3: {is_power_of_two_approach3(num)}")
        print(f"Approach 4: {is_power_of_two_approach4(num)}")
        print(f"Approach 5: {is_power_of_two_approach5(num)}")
        print(f"Approach 6: {is_power_of_two_approach6(num)}")
        print("-" * 50)

if __name__ == "__main__":
    main()
