import java.util.InputMismatchException;
import java.util.Scanner;

public class EuclideanAlgorithm {

    /**
     * Main method to run the program and demonstrate the different GCD implementations.
     *
     * @param args command line arguments (not used in this example)
     */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int num1 = 0, num2 = 0; // Initialize num1 and num2

        // Input validation loop
        while (true) {
            try {
                System.out.print("Enter the first non-negative integer: ");
                num1 = scanner.nextInt();
                if (num1 < 0) {
                    System.out.println("Please enter a non-negative integer.");
                    continue; // Go back to the beginning of the loop
                }
                System.out.print("Enter the second non-negative integer: ");
                num2 = scanner.nextInt();
                if (num2 < 0) {
                    System.out.println("Please enter a non-negative integer.");
                    continue; // Go back to the beginning of the loop
                }
                break; // Exit the loop if both inputs are valid
            } catch (InputMismatchException e) {
                System.out.println("Invalid input. Please enter integers only.");
                scanner.next(); // Consume the invalid input to prevent an infinite loop
            }
        }
        scanner.close();


        System.out.println("--------------------------------------------------------------------");
        System.out.println("Euclidean Algorithm Implementations for GCD(" + num1 + ", " + num2 + ")");
        System.out.println("--------------------------------------------------------------------");

        // 1. Basic Euclidean Algorithm (Iterative)
        long startTime = System.nanoTime();
        int gcd1 = iterativeGCD(num1, num2);
        long endTime = System.nanoTime();
        System.out.println("1. Iterative GCD: " + gcd1 + " (Time: " + (endTime - startTime) + " ns)");

        // 2. Recursive Euclidean Algorithm
        startTime = System.nanoTime();
        int gcd2 = recursiveGCD(num1, num2);
        endTime = System.nanoTime();
        System.out.println("2. Recursive GCD: " + gcd2 + " (Time: " + (endTime - startTime) + " ns)");

        // 3. Binary Euclidean Algorithm (Iterative)
        startTime = System.nanoTime();
        int gcd3 = binaryGCD(num1, num2);
        endTime = System.nanoTime();
        System.out.println("3. Binary GCD (Iterative): " + gcd3 + " (Time: " + (endTime - startTime) + " ns)");

        // 4. Extended Euclidean Algorithm (Iterative)
        startTime = System.nanoTime();
        int[] result4 = extendedEuclideanGCD(num1, num2);
        endTime = System.nanoTime();
        System.out.println("4. Extended Euclidean GCD (Iterative): GCD = " + result4[0] + ", x = " + result4[1] + ", y = " + result4[2] + " (Time: " + (endTime - startTime) + " ns)");

        // 5. GCD for Large Numbers (using BigInteger)
        startTime = System.nanoTime();
        int gcd5 = largeNumberGCD(num1, num2);
        endTime = System.nanoTime();
        System.out.println("5. GCD for Large Numbers: " + gcd5 + " (Time: " + (endTime - startTime) + " ns)");
        System.out.println("--------------------------------------------------------------------");
    }

    /**
     * 1. Iterative implementation of the Euclidean Algorithm to find the GCD of two integers.
     * This is the most common and basic approach.  It repeatedly applies the division
     * algorithm until the remainder is 0.
     *
     * @param a The first integer.
     * @param b The second integer.
     * @return The greatest common divisor of a and b.
     *
     * Example Use Case:
     * - Simplifying fractions in a calculator application.
     * - Finding the dimensions for the largest possible square tiles to cover a rectangular floor.
     */
    public static int iterativeGCD(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    /**
     * 2. Recursive implementation of the Euclidean Algorithm.
     * This approach provides a more concise and elegant solution compared to the iterative method,
     * but it may be less efficient for very large numbers due to function call overhead.
     *
     * @param a The first integer.
     * @param b The second integer.
     * @return The greatest common divisor of a and b.
     *
     * Example Use Case:
     * - Implementing a symbolic math library.
     * - Used in cryptography for key generation.
     */
    public static int recursiveGCD(int a, int b) {
        if (b == 0) {
            return a;
        }
        return recursiveGCD(b, a % b);
    }

    /**
     * 3. Iterative implementation of the Binary Euclidean Algorithm.
     * This algorithm is more efficient than the traditional Euclidean algorithm, especially
     * on hardware where division is slower than bitwise operations.  It leverages the
     * properties of binary representation to reduce the number of iterations.
     *
     * @param a The first integer.
     * @param b The second integer.
     * @return The greatest common divisor of a and b.
     *
     * Example Use Case:
     * - Optimizing GCD calculations in embedded systems.
     * - Used in high-performance computing applications.
     */
    public static int binaryGCD(int a, int b) {
        if (a == 0) return b;
        if (b == 0) return a;

        int shift = 0;
        while (((a | b) & 1) == 0) { // While both a and b are even
            a >>= 1;
            b >>= 1;
            shift++;
        }

        while ((a & 1) == 0) { // While a is even
            a >>= 1;
        }

        do {
            while ((b & 1) == 0) { // While b is even
                b >>= 1;
            }
            if (a > b) {
                int temp = a;
                a = b;
                b = temp;
            }
            b -= a;
        } while (b != 0);

        return a << shift;
    }

    /**
     * 4. Iterative implementation of the Extended Euclidean Algorithm.
     * This algorithm not only finds the GCD of two numbers a and b, but also finds
     * the coefficients x and y such that ax + by = gcd(a, b).  This is crucial for
     * solving linear Diophantine equations and finding modular inverses.
     *
     * @param a The first integer.
     * @param b The second integer.
     * @return An array containing the GCD, x, and y, in that order.
     * Returns int[]{gcd, x, y}
     *
     * Example Use Case:
     * - Finding modular inverses in cryptography (RSA algorithm).
     * - Solving linear Diophantine equations in number theory applications.
     */
    public static int[] extendedEuclideanGCD(int a, int b) {
        int x0 = 1, x1 = 0, y0 = 0, y1 = 1;
        int tempA = a, tempB = b; // Store original a and b for the equation

        while (b != 0) {
            int q = a / b;
            int temp = b;
            b = a % b;
            a = temp;

            int tempX = x0 - q * x1;
            int tempY = y0 - q * y1;
            x0 = x1;
            x1 = tempX;
            y0 = y1;
            y1 = tempY;
        }
        return new int[]{a, x0, y0}; // Returns {gcd, x, y}
    }

    /**
     * 5. Implementation of the Euclidean Algorithm for very large numbers using Java's BigInteger class.
     * This is necessary when the input numbers exceed the maximum value of the primitive int type.
     *
     * @param a The first integer.
     * @param b The second integer.
     * @return The greatest common divisor of a and b.
     *
     * Example Use Case:
     * - Cryptography with very large keys.
     * - Scientific computations involving very large integers.
     */
    public static int largeNumberGCD(int a, int b) {
        // Convert to BigInteger
        java.math.BigInteger bigA = java.math.BigInteger.valueOf(a);
        java.math.BigInteger bigB = java.math.BigInteger.valueOf(b);
        java.math.BigInteger result = bigA.gcd(bigB);
        return result.intValue();
    }
}

