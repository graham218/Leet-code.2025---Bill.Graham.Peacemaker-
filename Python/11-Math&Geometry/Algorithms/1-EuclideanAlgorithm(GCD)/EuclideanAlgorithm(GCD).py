def gcd_recursive(a, b):
    """
    Recursive implementation of the Euclidean Algorithm.

    Args:
        a: The first integer.
        b: The second integer.

    Returns:
        The greatest common divisor of a and b.

    Example:
        gcd_recursive(48, 18) == 6
    """
    if b == 0:
        return a
    else:
        return gcd_recursive(b, a % b)

def gcd_iterative(a, b):
    """
    Iterative implementation of the Euclidean Algorithm.

    Args:
        a: The first integer.
        b: The second integer.

    Returns:
        The greatest common divisor of a and b.

    Example:
        gcd_iterative(48, 18) == 6
    """
    while b:
        a, b = b, a % b
    return a

def gcd_subtraction(a, b):
    """
    GCD calculation using repeated subtraction.

    Args:
        a: The first integer.
        b: The second integer.

    Returns:
        The greatest common divisor of a and b.

    Example:
        gcd_subtraction(48, 18) == 6
    """
    while a != b:
        if a > b:
            a -= b
        else:
            b -= a
    return a

def gcd_binary_recursive(a, b):
    """
    Recursive implementation of the Binary (Stein's) Algorithm.
    This is often faster than the Euclidean algorithm, especially for large numbers.

    Args:
        a: The first integer.
        b: The second integer.

    Returns:
        The greatest common divisor of a and b.

    Example:
        gcd_binary_recursive(48, 18) == 6
    """
    if a == 0:
        return b
    if b == 0:
        return a
    if a == b:
        return a

    if (a % 2 == 0) and (b % 2 == 0):  # Both even
        return 2 * gcd_binary_recursive(a // 2, b // 2)
    elif (a % 2 == 0):  # a is even, b is odd
        return gcd_binary_recursive(a // 2, b)
    elif (b % 2 == 0):  # a is odd, b is even
        return gcd_binary_recursive(a, b // 2)
    elif a > b:
        return gcd_binary_recursive((a - b) // 2, b)
    else:
        return gcd_binary_recursive((b - a) // 2, a)

def gcd_extended(a, b):
    """
    Extended Euclidean Algorithm.  Finds GCD of a and b,
    and also finds x and y such that ax + by = gcd(a, b)

    Args:
        a: The first integer.
        b: The second integer.

    Returns:
        A tuple (gcd, x, y) where gcd is the GCD of a and b,
        and x and y satisfy the equation ax + by = gcd.

    Example:
        gcd_extended(48, 18) == (6, -1, 3)  # 48*(-1) + 18*(3) = 6
    """
    if b == 0:
        return a, 1, 0
    else:
        gcd, x, y = gcd_extended(b, a % b)
        return gcd, y, x - (a // b) * y

# Example usage and output:
a = 48
b = 18

print(f"GCD({a}, {b}) using recursion:", gcd_recursive(a, b))
print(f"GCD({a}, {b}) using iteration:", gcd_iterative(a, b))
print(f"GCD({a}, {b}) using subtraction:", gcd_subtraction(a, b))
print(f"GCD({a}, {b}) using binary recursion:", gcd_binary_recursive(a, b))

gcd, x, y = gcd_extended(a, b)
print(f"GCD({a}, {b}) using extended algorithm:", gcd)
print(f"Extended GCD: {a}*{x} + {b}*{y} = {gcd}")
