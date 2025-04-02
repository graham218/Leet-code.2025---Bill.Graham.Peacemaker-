def fast_exponentiation_recursive(base, exponent):
    """
    Recursive implementation of fast exponentiation.

    Args:
        base: The base number.
        exponent: The exponent (non-negative integer).

    Returns:
        The result of base raised to the power of exponent.

    Time Complexity: O(log n), where n is the exponent.
    Space Complexity: O(log n) due to the recursive call stack.
    """
    if exponent == 0:
        return 1
    if exponent == 1:
        return base

    # If the exponent is even, calculate b^(n/2) and square it.
    if exponent % 2 == 0:
        half_power = fast_exponentiation_recursive(base, exponent // 2)
        return half_power * half_power
    # If the exponent is odd, calculate b^(n-1) * b.
    else:
        return base * fast_exponentiation_recursive(base, exponent - 1)

def fast_exponentiation_iterative(base, exponent):
    """
    Iterative implementation of fast exponentiation.

    Args:
        base: The base number.
        exponent: The exponent (non-negative integer).

    Returns:
        The result of base raised to the power of exponent.

    Time Complexity: O(log n), where n is the exponent.
    Space Complexity: O(1) - constant space.
    """
    result = 1
    while exponent > 0:
        # If the exponent is odd, multiply the result by the base.
        if exponent % 2 == 1:
            result *= base
        # Divide the exponent by 2 and square the base.
        exponent //= 2
        base *= base
    return result

def fast_exponentiation_binary_method(base, exponent):
    """
    Fast exponentiation using the binary method (iterative).  This is essentially
    the same as the iterative method, but with more explicit variable names
    to highlight how the binary representation of the exponent is used.

    Args:
        base: The base number.
        exponent: The exponent (non-negative integer).

    Returns:
        The result of base raised to the power of exponent.

    Time Complexity: O(log n), where n is the exponent.
    Space Complexity: O(1) - constant space.
    """
    result = 1
    power = base
    while exponent > 0:
        # Check the least significant bit of the exponent.
        if exponent & 1:  # Equivalent to exponent % 2 == 1
            result *= power
        # Right shift the exponent (divide by 2) and square the power.
        exponent >>= 1  # Equivalent to exponent //= 2
        power *= power
    return result

def fast_exponentiation_recursive_optimized(base, exponent, memo={}):
    """
    Recursive implementation of fast exponentiation with memoization.

    Args:
        base: The base number.
        exponent: The exponent (non-negative integer).
        memo: A dictionary to store previously computed results (optional).

    Returns:
        The result of base raised to the power of exponent.

    Time Complexity: O(log n), where n is the exponent (due to memoization).
    Space Complexity: O(log n) for the memoization dictionary and recursive stack.
    """
    if exponent == 0:
        return 1
    if exponent == 1:
        return base

    if (base, exponent) in memo:
        return memo[(base, exponent)]

    if exponent % 2 == 0:
        half_power = fast_exponentiation_recursive_optimized(base, exponent // 2, memo)
        result = half_power * half_power
        memo[(base, exponent)] = result  # Store the result
        return result
    else:
        result = base * fast_exponentiation_recursive_optimized(base, exponent - 1, memo)
        memo[(base, exponent)] = result
        return result

def fast_exponentiation_builtin(base, exponent):
    """
    Fast exponentiation using Python's built-in power operator (**).

    Args:
        base: The base number.
        exponent: The exponent (non-negative integer).

    Returns:
        The result of base raised to the power of exponent.

    Time Complexity: O(log n) in most implementations.
    Space Complexity: O(1)
    """
    return base ** exponent

if __name__ == "__main__":
    # Example usage
    base = 2
    exponent = 10
    print(f"Base: {base}, Exponent: {exponent}")

    print("\n1. Recursive Method:")
    result_recursive = fast_exponentiation_recursive(base, exponent)
    print(f"Result: {result_recursive}")  # Output: 1024

    print("\n2. Iterative Method:")
    result_iterative = fast_exponentiation_iterative(base, exponent)
    print(f"Result: {result_iterative}")  # Output: 1024

    print("\n3. Binary Method (Iterative):")
    result_binary = fast_exponentiation_binary_method(base, exponent)
    print(f"Result: {result_binary}")  # Output: 1024

    print("\n4. Recursive with Memoization:")
    result_memo = fast_exponentiation_recursive_optimized(base, exponent)
    print(f"Result: {result_memo}")  # Output: 1024

    print("\n5. Built-in Operator (**):")
    result_builtin = fast_exponentiation_builtin(base, exponent)
    print(f"Result: {result_builtin}")  # Output: 1024

    # Example with a larger exponent
    base = 3
    exponent = 20
    print(f"\nBase: {base}, Exponent: {exponent}")
    print(f"Result (Iterative): {fast_exponentiation_iterative(base, exponent)}") # 3486784401
