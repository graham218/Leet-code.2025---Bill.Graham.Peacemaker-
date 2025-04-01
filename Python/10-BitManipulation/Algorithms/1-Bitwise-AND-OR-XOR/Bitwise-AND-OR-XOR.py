def bitwise_operations_demo():
    """
    Demonstrates bitwise AND, OR, and XOR operations in Python with multiple approaches.
    """
    # Initialize two integer variables
    a = 10  # Binary: 1010
    b = 7   # Binary: 0111

    print("Bitwise Operations Demo:")
    print(f"a = {a}, Binary: {bin(a)}")
    print(f"b = {b}, Binary: {bin(b)}")
    print("-" * 30)

    # Approach 1: Direct application of operators
    print("Approach 1: Direct Application of Operators")
    and_result = a & b  # Bitwise AND
    or_result = a | b   # Bitwise OR
    xor_result = a ^ b  # Bitwise XOR
    print(f"a & b = {and_result}, Binary: {bin(and_result)}")  # Output: 2, Binary: 0b10
    print(f"a | b = {or_result}, Binary: {bin(or_result)}")   # Output: 15, Binary: 0b1111
    print(f"a ^ b = {xor_result}, Binary: {bin(xor_result)}")  # Output: 13, Binary: 0b1101
    print("-" * 30)

    # Approach 2: Using bin() for formatted output
    print("Approach 2: Using bin() for Formatted Output")
    print(f"AND: {a} & {b} = {bin(a & b)}")
    print(f"OR:  {a} | {b} = {bin(a | b)}")
    print(f"XOR: {a} ^ {b} = {bin(a ^ b)}")
    print("-" * 30)

    # Approach 3:  Showing individual bit comparisons (commented for brevity, but useful for understanding)
    print("Approach 3: Individual Bit Comparisons (Conceptual)")
    # This approach would involve iterating through the bits of the numbers,
    # which is more complex in Python without built-in bit access.  It's more
    # illustrative to show it conceptually.
    # For example, for AND:
    #   1010
    # & 0111
    # ------
    #   0010  (2 in decimal)
    #
    # For OR:
    #   1010
    # | 0111
    # ------
    #   1111  (15 in decimal)
    #
    # For XOR:
    #   1010
    # ^ 0111
    # ------
    #   1101  (13 in decimal)
    print("See code comments for bit comparison")
    print("-" * 30)

    # Approach 4: Using a function for reusability
    def bitwise_ops(x, y):
        """
        Performs bitwise AND, OR, and XOR operations on two integers.

        Args:
            x: The first integer.
            y: The second integer.

        Returns:
            A tuple containing the results of AND, OR, and XOR operations.
        """
        return x & y, x | y, x ^ y

    print("Approach 4: Using a Function")
    and_result, or_result, xor_result = bitwise_ops(a, b)
    print(f"AND: {a} & {b} = {and_result}, Binary: {bin(and_result)}")
    print(f"OR:  {a} | {b} = {or_result}, Binary: {bin(or_result)}")
    print(f"XOR: {a} ^ {b} = {xor_result}, Binary: {bin(xor_result)}")
    print("-" * 30)

    # Approach 5:  Illustrating with different input values
    print("Approach 5: Different Input Values")
    c = 5  # 0101
    d = 12 # 1100
    and_result = c & d
    or_result = c | d
    xor_result = c ^ d
    print(f"c = {c}, Binary: {bin(c)}")
    print(f"d = {d}, Binary: {bin(d)}")
    print(f"c & d = {and_result}, Binary: {bin(and_result)}")  # 0
    print(f"c | d = {or_result}, Binary: {bin(or_result)}")   # 15
    print(f"c ^ d = {xor_result}, Binary: {bin(xor_result)}")  # 9
    print("-" * 30)
    # Example of using the values directly
    e = 0b1011 # 11
    f = 0b0101 # 5
    print(f"Binary {e:b} & {f:b} = {e & f}, Binary: {bin(e&f)}")
    print(f"Binary {e:b} | {f:b} = {e | f}, Binary: {bin(e|f)}")
    print(f"Binary {e:b} ^ {f:b} = {e ^ f}, Binary: {bin(e^f)}")
    print("-" * 30)

if __name__ == "__main__":
    bitwise_operations_demo()
