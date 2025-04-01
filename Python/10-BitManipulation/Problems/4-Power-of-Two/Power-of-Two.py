def is_power_of_two_approach1(n: int) -> bool:
    """
    Approach 1: Using the property that a power of 2 has only one bit set.
    Time Complexity: O(1)
    Space Complexity: O(1)

    Args:
        n: The integer to check.

    Returns:
        True if n is a power of two, False otherwise.
    """
    if n <= 0:
        return False  # Handle non-positive numbers
    return (n & (n - 1)) == 0  # n & (n-1) clears the least significant bit.  For powers of 2, this result is 0.

def is_power_of_two_approach2(n: int) -> bool:
    """
    Approach 2: Check if n is a power of 2 by repeatedly dividing by 2.
    Time Complexity: O(log n)
    Space Complexity: O(1)

    Args:
        n: The integer to check.

    Returns:
        True if n is a power of two, False otherwise.
    """
    if n <= 0:
        return False
    while n % 2 == 0:
        n //= 2  # Integer division
    return n == 1

def is_power_of_two_approach3(n: int) -> bool:
    """
    Approach 3: Using bitwise AND with the negation of the number.
    Time Complexity: O(1)
    Space Complexity: O(1)

    Args:
        n: The integer to check.

    Returns:
        True if n is a power of two, False otherwise.
    """
    if n <= 0:
        return False
    return (n & -n) == n  #  n & -n isolates the least significant bit.  For powers of 2, this equals n.

def is_power_of_two_approach4(n: int) -> bool:
    """
    Approach 4:  Using logarithms.
    Time Complexity: O(1)  (assuming log2 is constant time)
    Space Complexity: O(1)
    Args:
        n: The integer to check.

    Returns:
        True if n is a power of two, False otherwise.
    """
    import math
    if n <= 0:
        return False
    # Calculate the base-2 logarithm and check if it's an integer.
    log_result = math.log2(n)
    return abs(log_result - round(log_result)) < 1e-10 # Use a small tolerance for floating-point comparison

def is_power_of_two_approach5(n: int) -> bool:
    """
    Approach 5: Iterating through powers of 2.  This is efficient for a fixed-size integer.
    Time Complexity: O(1) -  The loop runs a maximum of 32 or 64 times (for 32-bit or 64-bit integers).
    Space Complexity: O(1)

    Args:
        n: The integer to check.

    Returns:
        True if n is a power of two, False otherwise.
    """
    if n <= 0:
        return False
    power_of_two = 1
    while power_of_two < n:
        power_of_two <<= 1  # Left shift is equivalent to multiplying by 2
    return power_of_two == n

def main():
    """
    Main function to test the implementations.
    """
    test_cases = [0, 1, 2, 3, 4, 8, 15, 16, 32, 1024, -1, -2, 2**31, 2**31 -1 ] #Added more test cases
    approaches = [
        is_power_of_two_approach1,
        is_power_of_two_approach2,
        is_power_of_two_approach3,
        is_power_of_two_approach4,
        is_power_of_two_approach5,
    ]

    for n in test_cases:
        print(f"Testing for n = {n}:")
        for approach in approaches:
            result = approach(n)
            print(f"  {approach.__name__}: {result}")
        print("-" * 30)

if __name__ == "__main__":
    main()
