def power_recursive(x, n):
    """
    1.  Recursive Approach

    Calculates x^n using a straightforward recursive algorithm.  Handles
    positive, negative, and zero exponents.

    Real-world application:
    -   Symbolic computation:  Used in computer algebra systems (like SymPy)
        for evaluating mathematical expressions involving powers.
    -   Fractal generation:  Recursive power calculations are fundamental in
        generating certain fractal patterns (e.g., the Mandelbrot set).

    Args:
        x: The base number.
        n: The exponent.

    Returns:
        The result of x^n.

    Output:
    >>> power_recursive(2, 3)
    8
    >>> power_recursive(2, -2)
    0.25
    >>> power_recursive(5, 0)
    1
    """
    if n == 0:
        return 1
    elif n < 0:
        return 1 / power_recursive(x, -n)
    else:
        return x * power_recursive(x, n - 1)


def power_iterative(x, n):
    """
    2.  Iterative Approach

    Calculates x^n using an iterative approach (loop).  More efficient
    than the simple recursive approach for large exponents as it avoids
    deep recursion.

    Real-world application:
    -   Scientific computing:  Many numerical libraries (like NumPy) use
        iterative methods for efficient calculations on large arrays of data.
    -   Financial calculations:  Compound interest calculations, which involve
        repeated exponentiation, can be efficiently implemented iteratively.

    Args:
        x: The base number.
        n: The exponent.

    Returns:
        The result of x^n.

    Output:
    >>> power_iterative(2, 3)
    8
    >>> power_iterative(2, -2)
    0.25
    >>> power_iterative(5, 0)
    1
    """
    if n == 0:
        return 1
    elif n < 0:
        x = 1 / x
        n = -n
    result = 1
    for _ in range(n):
        result *= x
    return result



def power_binary(x, n):
    """
    3.  Binary Exponentiation (Recursive)

    Calculates x^n using the binary exponentiation algorithm, also
    known as exponentiation by squaring.  This is a very efficient
    method that significantly reduces the number of multiplications.
    This version is recursive.

    Real-world application:
    -   Cryptography:  Modular exponentiation, which is a core operation
        in many cryptographic algorithms (like RSA), is efficiently
        implemented using binary exponentiation.
    -   Large number arithmetic:  Libraries for handling very large
        numbers use binary exponentiation to speed up power calculations.

    Args:
        x: The base number.
        n: The exponent.

    Returns:
        The result of x^n.

    Output:
    >>> power_binary(2, 10)
    1024
    >>> power_binary(3, 5)
    243
    >>> power_binary(2, -3)
    0.125
    """
    if n == 0:
        return 1
    elif n < 0:
        return power_binary(1/x, -n)
    elif n % 2 == 0:
        return power_binary(x * x, n // 2)
    else:
        return x * power_binary(x * x, (n - 1) // 2)


def power_binary_iterative(x, n):
    """
    4. Binary Exponentiation (Iterative)

    Calculates x^n using the binary exponentiation algorithm, also
    known as exponentiation by squaring. This is a very efficient
    method that significantly reduces the number of multiplications.
    This version is iterative.

    Real-world application:
    -   High-performance computing:  For very large exponents, the
        iterative version is often preferred due to its lower memory
        footprint compared to the recursive version.
    -   Game development:  Efficient power calculations can be useful
        in game physics or animation, where performance is critical.

    Args:
        x: The base number.
        n: The exponent.

    Returns:
        The result of x^n.

    Output:
    >>> power_binary_iterative(2, 10)
    1024
    >>> power_binary_iterative(3, 5)
    243
    >>> power_binary_iterative(2, -3)
    0.125
    """
    if n == 0:
        return 1
    elif n < 0:
        x = 1 / x
        n = -n
    result = 1
    while n > 0:
        if n % 2 == 1:
            result *= x
        x *= x
        n //= 2
    return result

import math

def power_using_math_pow(x, n):
    """
    5.  Using the math.pow() function

    Calculates x^n using the built-in math.pow() function from Python's
    math module.  This is generally the most efficient and convenient
    way to calculate powers in Python.

    Real-world application:
     - General purpose scientific calculations: For most general-purpose
       scientific or engineering calculations, `math.pow` is the go-to
       function.
     - Data analysis: When performing data analysis with Python,
       libraries like Pandas and NumPy often rely on optimized
       implementations of power functions, which are often based on
       `math.pow`.

    Args:
        x: The base number.
        n: The exponent.

    Returns:
        The result of x^n.

    Output:
    >>> power_using_math_pow(2, 3)
    8.0
    >>> power_using_math_pow(2, -2)
    0.25
    >>> power_using_math_pow(5, 0)
    1.0
    """
    return math.pow(x, n)

def power_complex(x, n):
    """
    6. Handling complex numbers

    Calculates x^n where x can be a complex number and n can be any integer
    using Python's built-in support for complex numbers.

    Real-world application:
    - Signal processing:  Complex exponentials are used extensively in
      signal processing, for example, in Fourier analysis.
    - Quantum mechanics: Complex numbers are fundamental to the mathematical
      formulation of quantum mechanics.
    - Electrical engineering:  Complex numbers are used to represent
      alternating currents and voltages.

    Args:
        x: The base number (can be complex).
        n: The exponent (must be an integer).

    Returns:
        The result of x^n.

    Output:
    >>> power_complex(2 + 1j, 3)
    (2+11j)
    >>> power_complex(1j, 4)
    (1+0j)
    >>> power_complex(2 + 0j, -2)
    (0.25+0j)
    """
    return x ** n # Python's built-in power operator handles complex numbers

# Example usage (added to the end of the code)
print("Recursive Approach:")
print(power_recursive(2, 3))
print(power_recursive(2, -2))
print(power_recursive(5, 0))

print("\nIterative Approach:")
print(power_iterative(2, 3))
print(power_iterative(2, -2))
print(power_iterative(5, 0))

print("\nBinary Exponentiation (Recursive):")
print(power_binary(2, 10))
print(power_binary(3, 5))
print(power_binary(2, -3))

print("\nBinary Exponentiation (Iterative):")
print(power_binary_iterative(2, 10))
print(power_binary_iterative(3, 5))
print(power_binary_iterative(2, -3))

print("\nUsing math.pow():")
print(power_using_math_pow(2, 3))
print(power_using_math_pow(2, -2))
print(power_using_math_pow(5, 0))

print("\nHandling Complex Numbers:")
print(power_complex(2 + 1j, 3))
print(power_complex(1j, 4))
print(power_complex(2 + 0j, -2))
