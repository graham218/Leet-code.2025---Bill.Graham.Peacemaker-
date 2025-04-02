def my_pow_v1(x: float, n: int) -> float:
    """
    Approach 1: Iterative multiplication.

    This is the most basic approach, where we multiply x by itself n times.
    It's simple to understand but can be inefficient for large values of n.

    Args:
        x: The base number.
        n: The exponent.

    Returns:
        The result of x raised to the power of n.
    """
    if n == 0:
        return 1.0
    if n < 0:
        x = 1 / x
        n = -n
    result = 1.0
    for _ in range(n):
        result *= x
    return result

def my_pow_v2(x: float, n: int) -> float:
    """
    Approach 2: Recursive exponentiation.

    This approach uses recursion and the property that x^n = (x^(n/2))^2 if n is even,
    and x^n = x * x^(n-1) if n is odd.  This is more efficient than the iterative approach.

    Args:
        x: The base number.
        n: The exponent.

    Returns:
        The result of x raised to the power of n.
    """
    if n == 0:
        return 1.0
    if n < 0:
        x = 1 / x
        n = -n
    if n % 2 == 0:
        half_pow = my_pow_v2(x, n // 2)
        return half_pow * half_pow
    else:
        return x * my_pow_v2(x, n - 1)

def my_pow_v3(x: float, n: int) -> float:
    """
    Approach 3: Iterative binary exponentiation.

    This is an iterative version of the recursive approach. It's very efficient and
    commonly used.  It exploits the binary representation of the exponent.

    Args:
        x: The base number.
        n: The exponent.

    Returns:
        The result of x raised to the power of n.
    """
    if n == 0:
        return 1.0
    if n < 0:
        x = 1 / x
        n = -n
    result = 1.0
    while n > 0:
        if n % 2 == 1:
            result *= x
        x *= x
        n //= 2
    return result

def my_pow_v4(x: float, n: int) -> float:
    """
    Approach 4: Using Python's built-in pow function.

    This approach simply uses Python's built-in pow() function, which is highly optimized.
    For most practical purposes, this is the recommended approach.

    Args:
        x: The base number.
        n: The exponent.

    Returns:
        The result of x raised to the power of n.
    """
    return pow(x, n)

def my_pow_v5(x: float, n: int) -> float:
    """
    Approach 5: Iterative binary exponentiation with bitwise operations.

    This is a slightly optimized version of Approach 3, using bitwise operations
    for checking odd/even and dividing by 2.  It can be slightly faster in some cases.

    Args:
        x: The base number.
        n: The exponent.

    Returns:
        The result of x raised to the power of n.
    """
    if n == 0:
        return 1.0
    if n < 0:
        x = 1 / x
        n = -n
    result = 1.0
    while n > 0:
        if n & 1:  # Check if n is odd
            result *= x
        x *= x
        n >>= 1  # Divide n by 2
    return result

def main():
    """
    Main function to demonstrate the different approaches.
    """
    test_cases = [
        (2.0, 10),
        (2.0, -2),
        (0.5, 5),
        (2.0, 0),
        (3.0, 4),
        (1.0, 10000),
        (2.0, 31),  # Test with a large exponent
        (1.00001, 1024)
    ]
    approaches = {
        "Approach 1: Iterative": my_pow_v1,
        "Approach 2: Recursive": my_pow_v2,
        "Approach 3: Iterative Binary": my_pow_v3,
        "Approach 4: Python's pow()": my_pow_v4,
        "Approach 5: Bitwise Iterative Binary": my_pow_v5,
    }

    print("Testing Pow(x, n) with different approaches:")
    for x, n in test_cases:
        print(f"\nInput: x = {x}, n = {n}")
        for approach_name, approach_func in approaches.items():
            result = approach_func(x, n)
            print(f"  {approach_name}: {result}")

if __name__ == "__main__":
    main()
