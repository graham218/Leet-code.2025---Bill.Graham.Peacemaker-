def is_power_of_two_approach1(n):
    """
    Approach 1: Using the property that powers of 2 have only one bit set.

    This method checks if the number is positive and if subtracting 1 from it
    results in a number that, when ANDed with the original number, equals 0.
    For example:
    8 (1000)
    7 (0111)
    8 & 7 = 0

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

    This method repeatedly divides the number by 2. If the number is a power of 2,
    it will eventually become 1.  Handles the edge case where n is initially 0.

    Args:
        n: The integer to check.

    Returns:
        True if n is a power of 2, False otherwise.
    """
    if n <= 0:
        return False  # 0 and negative numbers are not powers of 2
    while n % 2 == 0:
        n //= 2
    return n == 1

def is_power_of_two_approach3(n):
    """
    Approach 3: Using logarithms.

    This method uses the logarithm base 2. If the number is a power of 2,
    the logarithm base 2 will be an integer.  We check if the log base 2
    is close to an integer to account for potential floating point errors.

    Args:
        n: The integer to check.

    Returns:
        True if n is a power of 2, False otherwise.
    """
    import math
    if n <= 0:
        return False
    # Calculate log base 2.
    log_result = math.log(n, 2)
    # Check if the result is close to an integer
    return abs(log_result - round(log_result)) < 1e-10 # Use a small tolerance

def is_power_of_two_approach4(n):
    """
    Approach 4: Bitwise AND with a precomputed power of 2.

    This approach leverages the fact that the largest power of 2 within
    the range of a 32-bit integer is 2^31.  We can check if n divides this
    largest power of 2 without any remainder.  This is efficient, but
    it's limited by the maximum integer size.  We use 2**32, as the problem
    does not specify the bit size, and this will work for 32 and 64 bit
    systems.
    Args:
        n: The integer to check.

    Returns:
        True if n is a power of 2, False otherwise.
    """
    if n <= 0:
        return False
    return (2**32) % n == 0 and (n & (n-1)) == 0 # Added check n&(n-1) == 0

def is_power_of_two_approach5(n):
    """
    Approach 5: Using ffs (find first set) -  most efficient.

    This approach uses the built-in `bit_count()` method (ffs - find first set)
    which returns the number of set bits.  For a power of two, there is only
    one set bit.

    Args:
        n: The integer to check.

    Returns:
        True if n is a power of 2, False otherwise.
    """
    if n <= 0:
        return False
    return n.bit_count() == 1
    #return bin(n).count('1') == 1 # alternative

def main():
    """
    Main function to demonstrate the usage of the different approaches.
    """
    test_numbers = [0, 1, 2, 3, 4, 8, 15, 16, 32, 64, -1, -8, 256, 1024, 2048]

    print("Checking if numbers are powers of 2:")
    for num in test_numbers:
        print(f"\nNumber: {num}")
        print(f"Approach 1: {is_power_of_two_approach1(num)}")
        print(f"Approach 2: {is_power_of_two_approach2(num)}")
        print(f"Approach 3: {is_power_of_two_approach3(num)}")
        print(f"Approach 4: {is_power_of_two_approach4(num)}")
        print(f"Approach 5: {is_power_of_two_approach5(num)}")

if __name__ == "__main__":
    main()
