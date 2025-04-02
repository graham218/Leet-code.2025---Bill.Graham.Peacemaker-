def sieve_of_eratosthenes_basic(n):
    """
    Sieve of Eratosthenes - Basic Implementation

    This is the most straightforward implementation of the Sieve of Eratosthenes algorithm.

    Args:
        n: The upper limit for finding prime numbers (inclusive).

    Returns:
        A list of prime numbers less than or equal to n.

    Example:
        sieve_of_eratosthenes_basic(20) == [2, 3, 5, 7, 11, 13, 17, 19]
    """
    if n <= 1:
        return []

    # Create a boolean list "is_prime[i]" initially assumed true for all numbers.
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False  # 0 and 1 are not prime

    # Iterate from 2 to the square root of n.  We only need to check up to the square root.
    for p in range(2, int(n**0.5) + 1):
        # If p is prime, mark all multiples of p as not prime.
        if is_prime[p]:
            for i in range(p * p, n + 1, p):
                is_prime[i] = False

    # Collect the prime numbers from the boolean list.
    primes = [i for i in range(n + 1) if is_prime[i]]
    return primes


def sieve_of_eratosthenes_optimized1(n):
    """
    Sieve of Eratosthenes - Optimized Implementation 1

    This version optimizes the basic version by:
    1.  Starting the inner loop from p*p (multiples less than p*p have already been marked).
    2. Iterating only through odd numbers after 2.

    Args:
        n: The upper limit for finding prime numbers (inclusive).

    Returns:
        A list of prime numbers less than or equal to n.

    Example:
        sieve_of_eratosthenes_optimized1(20) == [2, 3, 5, 7, 11, 13, 17, 19]
    """
    if n <= 1:
        return []
    if n == 2:
        return [2]

    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False

    # Handle the special case of 2
    primes = [2]

    # Only check odd numbers starting from 3
    for p in range(3, int(n**0.5) + 1, 2):
        if is_prime[p]:
            for i in range(p * p, n + 1, 2 * p): # Mark only odd multiples of p
                is_prime[i] = False

    # Collect the primes.  Start from 3 and increment by 2.
    for i in range(3, n + 1, 2):
        if is_prime[i]:
            primes.append(i)
    return primes



def sieve_of_eratosthenes_bitarray(n):
    """
    Sieve of Eratosthenes - Bit Array Optimization

    This version uses a bit array to store prime flags, significantly reducing memory usage.
    Instead of a boolean list, it uses an integer array where each bit represents the
    primality of a number.  This is much more space-efficient.

    Args:
        n: The upper limit for finding prime numbers (inclusive).

    Returns:
        A list of prime numbers less than or equal to n.

    Example:
        sieve_of_eratosthenes_bitarray(20) == [2, 3, 5, 7, 11, 13, 17, 19]
    """
    if n <= 1:
        return []

    # Calculate the size of the bit array.  Each integer holds 32 bits.
    size = (n + 31) // 32
    bit_array = [0] * size  # Initialize the bit array to 0

    def get_bit(num):
        """Helper function to get the bit value at a given number."""
        index = num // 32
        offset = num % 32
        return (bit_array[index] >> offset) & 1

    def set_bit(num):
        """Helper function to set the bit value at a given number."""
        index = num // 32
        offset = num % 32
        bit_array[index] |= (1 << offset)

    # 0 and 1 are not prime
    set_bit(0)
    set_bit(1)

    for p in range(2, int(n**0.5) + 1):
        if get_bit(p) == 0:  # If p is prime (bit is 0)
            for i in range(p * p, n + 1, p):
                set_bit(i)  # Mark multiples of p as not prime

    primes = []
    for i in range(2, n + 1):
        if get_bit(i) == 0:  # If the bit is 0, the number is prime
            primes.append(i)
    return primes



def sieve_of_eratosthenes_segmented(n):
    """
    Sieve of Eratosthenes - Segmented Sieve

    This version is optimized for very large values of n.  It divides the range [2, n]
    into smaller segments and applies the Sieve of Eratosthenes to each segment.
    This reduces memory usage, as the entire boolean array does not need to be
    stored in memory at once.

    Args:
        n: The upper limit for finding prime numbers (inclusive).

    Returns:
        A list of prime numbers less than or equal to n.
    """
    if n <= 1:
        return []

    segment_size = int(n**0.5) + 1  # Size of each segment
    primes = []  # To store all primes found

    # 1. Find primes up to the square root of n using the basic sieve
    is_prime = [True] * segment_size
    is_prime[0] = is_prime[1] = False
    for p in range(2, int(segment_size**0.5) + 1):
        if is_prime[p]:
            for i in range(p * p, segment_size, p):
                is_prime[i] = False
    base_primes = [i for i in range(segment_size) if is_prime[i]] #Primes upto sqrt(n)

    # 2. Process segments
    for low in range(0, n + 1, segment_size):
        high = min(low + segment_size - 1, n)  # Last number in this segment

        # Create a temporary array for the current segment
        segment = [True] * (high - low + 1)

        # Use the primes found in step 1 to mark non-primes in the current segment
        for p in base_primes:
            first_multiple = (low // p) * p  # Find the first multiple of p >= low
            if first_multiple < low:
                first_multiple += p
            for i in range(first_multiple - low, high - low + 1, p):
                segment[i] = False

        # Collect the primes from the current segment
        for i in range(high - low + 1):
            if segment[i]:
                primes.append(low + i)
    return primes



def sieve_of_eratosthenes_generator(n):
    """
    Sieve of Eratosthenes - Generator

    This version uses a generator to yield prime numbers one at a time, instead of
    returning a list. This can be more memory-efficient when dealing with very
    large values of n, as it avoids storing all primes in memory at once.

    Args:
        n: The upper limit for finding prime numbers (inclusive).

    Yields:
        Prime numbers less than or equal to n.

    Example:
        list(sieve_of_eratosthenes_generator(20)) == [2, 3, 5, 7, 11, 13, 17, 19]
    """
    if n <= 1:
        return

    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False

    for p in range(2, int(n**0.5) + 1):
        if is_prime[p]:
            for i in range(p * p, n + 1, p):
                is_prime[i] = False

    for i in range(2, n + 1):
        if is_prime[i]:
            yield i  # Use yield to return one prime at a time


if __name__ == "__main__":
    n = 20
    print(f"Prime numbers up to {n}:")

    print("\n1. Basic Sieve of Eratosthenes:")
    primes1 = sieve_of_eratosthenes_basic(n)
    print(primes1)

    print("\n2. Optimized Sieve of Eratosthenes 1:")
    primes2 = sieve_of_eratosthenes_optimized1(n)
    print(primes2)

    print("\n3. Sieve of Eratosthenes with Bit Array:")
    primes3 = sieve_of_eratosthenes_bitarray(n)
    print(primes3)

    print("\n4. Segmented Sieve of Eratosthenes:")
    primes4 = sieve_of_eratosthenes_segmented(n)
    print(primes4)

    print("\n5. Sieve of Eratosthenes with Generator:")
    primes5 = list(sieve_of_eratosthenes_generator(n)) #convert the generator to a list
    print(primes5)
