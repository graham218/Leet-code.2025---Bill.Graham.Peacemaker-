import java.util.InputMismatchException;
import java.util.Scanner;

public class EuclideanGCD {

    /**
     * Main method to demonstrate and test the different GCD implementations.
     *
     * @param args command line arguments (not used in this example)
     */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int num1, num2;

        // Get input from the user with input validation.
        try {
            System.out.print("Enter the first non-negative integer: ");
            num1 = scanner.nextInt();
            if (num1 < 0) {
                System.out.println("Error: Input must be a non-negative integer.");
                scanner.close();
                return; // Exit the program
            }

            System.out.print("Enter the second non-negative integer: ");
            num2 = scanner.nextInt();
            if (num2 < 0) {
                System.out.println("Error: Input must be a non-negative integer.");
                scanner.close();
                return; // Exit the program
            }
        } catch (InputMismatchException e) {
            System.out.println("Error: Invalid input. Please enter integers only.");
            scanner.close();
            return; // Exit the program
        } finally {
            // Close the scanner to prevent resource leaks
            // moved scanner.close() to finally block
            // scanner.close(); // Close the scanner
        }


        // Calculate and print GCD using different methods.
        System.out.println("GCD(" + num1 + ", " + num2 + ") using recursion: " + gcdRecursive(num1, num2));
        System.out.println("GCD(" + num1 + ", " + num2 + ") using iteration: " + gcdIterative(num1, num2));
        System.out.println("GCD(" + num1 + ", " + num2 + ") using binary recursion: " + gcdBinaryRecursive(num1, num2));
        System.out.println("GCD(" + num1 + ", " + num2 + ") using binary iteration: " + gcdBinaryIterative(num1, num2));
        System.out.println("GCD(" + num1 + ", " + num2 + ") using subtraction: " + gcdSubtraction(num1, num2));
        scanner.close(); // moved scanner close here
    }

    /**
     * Recursive implementation of the Euclidean Algorithm.
     * This method calculates the GCD of two numbers using recursion.
     *
     * @param a the first non-negative integer
     * @param b the second non-negative integer
     * @return the greatest common divisor of a and b
     */
    public static int gcdRecursive(int a, int b) {
        if (b == 0) {
            return a;
        }
        return gcdRecursive(b, a % b);
    }

    /**
     * Iterative implementation of the Euclidean Algorithm.
     * This method calculates the GCD of two numbers using a while loop.
     *
     * @param a the first non-negative integer
     * @param b the second non-negative integer
     * @return the greatest common divisor of a and b
     */
    public static int gcdIterative(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    /**
     * Recursive implementation of the Binary (Stein's) GCD Algorithm.
     * This method is more efficient than the traditional Euclidean algorithm, especially for large numbers.
     * It leverages bitwise operations and recursion.
     *
     * @param a the first non-negative integer
     * @param b the second non-negative integer
     * @return the greatest common divisor of a and b
     */
    public static int gcdBinaryRecursive(int a, int b) {
        if (a == 0) {
            return b;
        }
        if (b == 0) {
            return a;
        }
        if (a == b) {
            return a;
        }
        if ((a & 1) == 0) { // a is even
            if ((b & 1) == 0) { // b is even
                return gcdBinaryRecursive(a >> 1, b >> 1) << 1; // result * 2
            } else { // b is odd
                return gcdBinaryRecursive(a >> 1, b);
            }
        } else { // a is odd
            if ((b & 1) == 0) { // b is even
                return gcdBinaryRecursive(a, b >> 1);
            } else { // b is odd
                if (a > b) {
                    return gcdBinaryRecursive(a - b, b);
                } else {
                    return gcdBinaryRecursive(b - a, a);
                }
            }
        }
    }

    /**
     * Iterative implementation of the Binary (Stein's) GCD Algorithm.
     * This method calculates the GCD of two numbers without using division,
     * instead using bitwise operations.
     *
     * @param a the first non-negative integer
     * @param b the second non-negative integer
     * @return the greatest common divisor of a and b
     */
    public static int gcdBinaryIterative(int a, int b) {
        // GCD(0, b) is b, GCD(a, 0) is a.
        if (a == 0)
            return b;
        if (b == 0)
            return a;

        //Find common factor of 2
        int shift;
        for (shift = 0; ((a | b) & 1) == 0; ++shift) {
            a >>= 1;
            b >>= 1;
        }

        // Now, a and b are not both even.
        while ((a & 1) == 0)
            a >>= 1;

        // From here, a is always odd.
        do {
            while ((b & 1) == 0)  // Remove all factors of 2 in b
                b >>= 1;
            if (a > b) {
                int t = b;
                b = a;
                a = t;
            }
            b = b - a;
        } while (b != 0);
        return a << shift;
    }

    /**
     * Implementation of the Euclidean Algorithm using subtraction.
     * This method calculates the GCD of two numbers by repeatedly subtracting
     * the smaller number from the larger number until they are equal.
     *
     * @param a the first non-negative integer
     * @param b the second non-negative integer
     * @return the greatest common divisor of a and b
     */
    public static int gcdSubtraction(int a, int b) {
        if (a == 0) return b;
        if (b == 0) return a;

        while (a != b) {
            if (a > b) {
                a = a - b;
            } else {
                b = b - a;
            }
        }
        return a;
    }
}

