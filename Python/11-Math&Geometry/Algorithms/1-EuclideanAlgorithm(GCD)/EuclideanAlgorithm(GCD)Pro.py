def gcd_extended(a, b):
    """
    Extended Euclidean Algorithm.

    Calculates the greatest common divisor (gcd) of a and b, and also finds integers x and y
    such that ax + by = gcd(a, b).

    Args:
        a: The first integer.
        b: The second integer.

    Returns:
        A tuple (gcd, x, y) where:
            gcd: The greatest common divisor of a and b.
            x:  Coefficient of 'a' in the linear combination.
            y:  Coefficient of 'b' in the linear combination.

    Real-world application:
    -   Fundamental in cryptography for calculating modular inverses, a key step in RSA encryption and decryption.
    -   Used in solving linear Diophantine equations, which arise in various engineering and computer science problems.
    """
    if b == 0:
        return a, 1, 0
    else:
        gcd, x1, y1 = gcd_extended(b, a % b)
        x = y1
        y = x1 - (a // b) * y1
        return gcd, x, y

def modular_inverse(a, m):
    """
    Calculates the modular inverse of 'a' modulo 'm'.

    The modular inverse of a (mod m) is an integer 'x' such that (a * x) % m == 1.
    It exists if and only if gcd(a, m) == 1.

    Args:
        a: The integer for which the inverse is sought.
        m: The modulus.

    Returns:
        The modular inverse of 'a' modulo 'm'. Returns -1 if the inverse does not exist.

    Raises:
        ValueError: If a or m is negative.

    Real-world application:
    -   RSA Cryptography:  The core of RSA involves finding the modular inverse of the public exponent modulo the totient of the modulus.
    -   Elliptic Curve Cryptography (ECC):  Used in point addition and scalar multiplication operations.
    -   Computer Science:  Hash table implementation (rehashing), error correction codes (Reed-Solomon).
    """
    if a < 0 or m < 0:
        raise ValueError("a and m must be non-negative")

    gcd, x, y = gcd_extended(a, m)  # Use the extended Euclidean algorithm

    if gcd != 1:
        return -1  # Modular inverse does not exist
    else:
        # x is the inverse, but it might be negative.  Normalize it to the range 0 to m-1.
        return x % m

def rsa_example():
    """
    Demonstrates a simplified RSA key generation and encryption/decryption process,
    highlighting the use of modular inverse.

    Real-world application:
    -   Secure communication over the internet (HTTPS).
    -   Digital signatures for verifying the authenticity of documents.
    -   Cryptocurrency wallets.
    """
    # 1. Choose two distinct prime numbers, p and q.
    p = 61
    q = 53
    print(f"p = {p}, q = {q}")

    # 2. Calculate n = p * q.
    n = p * q
    print(f"n = p * q = {n}")

    # 3. Calculate the totient of n, φ(n) = (p-1)(q-1).
    phi_n = (p - 1) * (q - 1)
    print(f"φ(n) = (p-1)(q-1) = {phi_n}")

    # 4. Choose an integer e such that 1 < e < φ(n) and gcd(e, φ(n)) = 1 (e is the public exponent).
    e = 17
    print(f"e (public exponent) = {e}")
    gcd_check = gcd_extended(e, phi_n)[0]  # Only need the GCD
    print(f"gcd(e, φ(n)) = {gcd_check}")
    if gcd_check != 1:
        print("Error: e is not relatively prime to φ(n). Choose a different e.")
        return  # Exit if e is not valid

    # 5. Calculate the modular inverse of e modulo φ(n), which is the private exponent d.
    d = modular_inverse(e, phi_n)
    print(f"d (private exponent) = {d}")

    # 6. Public key is (n, e), private key is (n, d).

    # --- Encryption ---
    message = 12345
    print(f"Original message = {message}")
    ciphertext = pow(message, e, n)  # c = m^e mod n
    print(f"Ciphertext = {ciphertext}")

    # --- Decryption ---
    decrypted_message = pow(ciphertext, d, n)  # m = c^d mod n
    print(f"Decrypted message = {decrypted_message}")

    if decrypted_message == message:
        print("Decryption successful!")
    else:
        print("Decryption failed!")

def main():
    """
    Main function to demonstrate the modular inverse calculation and RSA example.
    """
    # Example 1:  Finding the modular inverse of 17 modulo 31
    a1 = 17
    m1 = 31
    inv1 = modular_inverse(a1, m1)
    if inv1 != -1:
        print(f"The modular inverse of {a1} modulo {m1} is {inv1}")
        print(f"Verification: ({a1} * {inv1}) % {m1} = {(a1 * inv1) % m1}")
    else:
        print(f"The modular inverse of {a1} modulo {m1} does not exist.")

    # Example 2:  A case where the modular inverse does not exist
    a2 = 12
    m2 = 18
    inv2 = modular_inverse(a2, m2)
    if inv2 != -1:
        print(f"The modular inverse of {a2} modulo {m2} is {inv2}")
        print(f"Verification: ({a2} * {inv2}) % {m2} = {(a2 * inv2) % m2}")
    else:
        print(f"The modular inverse of {a2} modulo {m2} does not exist.")

    # Example 3: Using a different pair of numbers
    a3 = 5
    m3 = 11
    inv3 = modular_inverse(a3, m3)
    if inv3 != -1:
        print(f"The modular inverse of {a3} modulo {m3} is {inv3}")
        print(f"Verification: ({a3} * {inv3}) % {m3} = {(a3 * inv3) % m3}")
    else:
        print(f"The modular inverse of {a3} modulo {m3} does not exist.")

    print("\n--- RSA Example ---")
    rsa_example()


if __name__ == "__main__":
    main()
