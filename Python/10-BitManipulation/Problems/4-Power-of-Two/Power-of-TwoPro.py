def is_power_of_two_approach1(n):
    """
    Approach 1: Using the property that a power of 2 has only one bit set.

    Real-world application:
    - Memory allocation: Checking if a requested memory size is a power of 2 for efficient allocation.
    - Image processing: Some image formats or algorithms work optimally with power-of-2 dimensions.
    - Data structures: Hash table sizing often uses powers of 2 for efficient key distribution.

    Args:
        n: The integer to check.

    Returns:
        True if n is a power of 2, False otherwise.
    """
    if n <= 0:
        return False
    return (n & (n - 1)) == 0

def is_power_of_two_approach2(n):
    """
    Approach 2: Repeatedly divide by 2.

    Real-world application:
    - Audio processing:  Analyzing audio sample rates or buffer sizes, which are sometimes powers of 2.
    - Network protocols:  Handling data packet sizes or window sizes that might be constrained to powers of 2.
    - File systems:  Block sizes in file systems are often powers of 2 for efficient storage and retrieval.

    Args:
        n: The integer to check.

    Returns:
        True if n is a power of 2, False otherwise.
    """
    if n <= 0:
        return False
    while n % 2 == 0:
        n //= 2
    return n == 1

def is_power_of_two_approach3(n):
    """
    Approach 3: Using logarithms.

    Real-world application:
     - Scientific computing:  Analyzing exponential growth or decay where powers of 2 might be involved.
     - Financial modeling:  Calculating compound interest or growth rates over periods that are powers of 2.
     - Data analysis:  Identifying data points that fall on a logarithmic scale with base 2.

    Args:
        n: The integer to check.

    Returns:
        True if n is a power of 2, False otherwise.
    """
    import math
    if n <= 0:
        return False
    # Use log2, and check if the result is very close to an integer
    log_result = math.log2(n)
    return abs(log_result - round(log_result)) < 1e-10 # Use a small tolerance

def is_power_of_two_approach4(n):
    """
    Approach 4: Checking if n is a power of 2 using string representation.

    Real-world application:
    - Embedded systems:  Validating configuration settings read from a file or user input.
    - System configuration: Checking if a hardware resource allocation is a power of 2.
    - Parsing data:  Verifying data formats where power-of-2 values are expected.

    Args:
        n: The integer to check.

    Returns:
        True if n is a power of 2, False otherwise.
    """
    if n <= 0:
        return False
    binary_representation = bin(n)[2:]  # Remove "0b" prefix
    return binary_representation.count('1') == 1

def is_power_of_two_approach5(n):
    """
    Approach 5: Using bitwise AND with a precomputed power of 2.
    This approach exploits the fact that the largest power of 2 less than the maximum
    integer is 2**30 (for 32-bit integers).

    Real-world application:
    - Optimizing performance-critical code:  This method can be faster than repeated division or logarithms.
    - High-frequency trading:  Minimizing latency in time-sensitive calculations.
    - Game development:  Efficiently checking properties of game objects or world parameters.

    Args:
        n: The integer to check.

    Returns:
        True if n is a power of 2, False otherwise.
    """
    if n <= 0:
        return False
    # 2**30 is the largest power of 2 that fits in a 32-bit integer
    return (1 << 30) % n == 0 if n <= (1 << 30) else False #handles larger numbers

def is_power_of_two_approach6(n):
    """
    Approach 6:  Utilizing the math.isclose for comparison

     Real-world application:
        - Data validation: Ensuring input data conforms to expected power-of-two constraints.
        - System optimization:  Tuning system parameters that are most efficient when set to powers of 2.
        - Graphics rendering:  Verifying texture dimensions or buffer sizes.
    Args:
        n: The integer to check.

    Returns:
        True if n is a power of 2, False otherwise.
    """
    import math
    if n <= 0:
        return False
    if n == 1:
        return True
    x = math.log2(n)
    return math.isclose(x, round(x))

def main():
    """
    Main function to test the implementations.
    """
    test_cases = [0, 1, 2, 3, 4, 5, 8, 16, 24, 32, 64, 128, 256, 1024, 2048, 4096, -4, -8, 2**31, 2**30]
    approaches = [
        is_power_of_two_approach1,
        is_power_of_two_approach2,
        is_power_of_two_approach3,
        is_power_of_two_approach4,
        is_power_of_two_approach5,
        is_power_of_two_approach6,
    ]

    for n in test_cases:
        print(f"Testing for n = {n}:")
        for approach in approaches:
            result = approach(n)
            print(f"  {approach.__name__}: {result}")
        print("-" * 30)

if __name__ == "__main__":
    main()
