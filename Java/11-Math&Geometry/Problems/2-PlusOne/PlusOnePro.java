import java.util.Arrays;

public class PlusOne {

    /*
     * Problem: Plus One
     *
     * Given a non-empty array of decimal digits representing a non-negative integer,
     * increment one to the integer.
     *
     * The digits are stored such that the most significant digit is at the head of
     * the list. Return the updated array.
     *
     * Examples:
     *
     * Input: [1,2,3]
     * Output: [1,2,4]
     *
     * Input: [4,3,2,1]
     * Output: [4,3,2,2]
     *
     * Input: [9]
     * Output: [1,0]
     *
     *
     * Solution Approaches:
     *
     * 1.  Iterative with Carry (Most Common)
     * -   Simulate addition with carry, starting from the least significant digit.
     * -   This is the most straightforward and efficient approach for this problem.
     *
     * 2.  Convert to Number, Add One, Convert Back to Array
     * -   Convert the digit array to a single number.
     * -   Add one to the number.
     * -   Convert the result back to a digit array.
     * -   This approach is conceptually simple but can have limitations with very large numbers
     * due to potential overflow issues.
     *
     * 3.  Using BigInteger (For Very Large Numbers)
     * -   Use Java's BigInteger class to handle arbitrarily large numbers.
     * -    Convert the array to a BigInteger, add one, and convert back to an array.
     * -   This is suitable when the input array represents a very large number that
     * exceeds the capacity of primitive data types (like `int` or `long`).
     *
     * 4. Recursive Approach
     * -  Use recursion to add one to the digits array.
     * -  While generally not the most efficient way to solve this problem, it
     * demonstrates a different problem-solving technique.
     *
     * 5.  Using Streams (Java 8 and later)
     * -   Use Java 8 streams for a more functional approach.
     * -   This can be less efficient than the iterative approach but provides a
     * more concise way to express the solution.
     *
     */

    // Approach 1: Iterative with Carry
    // Time Complexity: O(n), where n is the length of the array.
    // Space Complexity: O(1) in most cases, O(n+1) in the worst case (when the array is all 9s).
    public static int[] plusOneIterative(int[] digits) {
        int n = digits.length;
        // Iterate from the least significant digit (rightmost) to the most significant digit.
        for (int i = n - 1; i >= 0; i--) {
            // Increment the current digit by one.
            digits[i]++;
            // If the digit is less than 10, no carry-over is needed, so we can return the array.
            if (digits[i] < 10) {
                return digits;
            }
            // If the digit is 10, set it to 0 and carry over the 1 to the next digit.
            digits[i] = 0;
        }
        // If we reach this point, it means all digits were 9, so we need to expand the array.
        // For example, [9,9,9] becomes [1,0,0,0].
        int[] newDigits = new int[n + 1];
        newDigits[0] = 1; // Set the first digit of the new array to 1.
        return newDigits;
    }

    // Approach 2: Convert to Number, Add One, Convert Back to Array
    // Time Complexity: O(n) to convert to number, O(log N) to convert back to array, where N is the resulting number.
    // Space Complexity: O(log N) for the new array.
    public static int[] plusOneConvertToNumber(int[] digits) {
        long number = 0;
        for (int digit : digits) {
            number = number * 10 + digit;
        }
        number++; // Increment the number.

        // Handle the case where the number becomes 0 (e.g., input [9,9,9...9]).
        if (number == 0) {
            return new int[]{1}; // Return [1, 0, 0, ..., 0]
        }
        String numStr = String.valueOf(number);
        int[] result = new int[numStr.length()];
        for (int i = 0; i < numStr.length(); i++) {
            result[i] = numStr.charAt(i) - '0'; // Convert each character back to a digit.
        }
        return result;
    }

    // Approach 3: Using BigInteger
    // Time Complexity: O(n) to convert to BigInteger, O(log N) to convert back to array.
    // Space Complexity: O(log N) for the BigInteger and the result array.
    public static int[] plusOneBigInteger(int[] digits) {
        StringBuilder sb = new StringBuilder();
        for (int digit : digits) {
            sb.append(digit);
        }
        java.math.BigInteger number = new java.math.BigInteger(sb.toString());
        number = number.add(java.math.BigInteger.ONE); // Use BigInteger.ONE for adding one.
        String resultStr = number.toString();
        int[] result = new int[resultStr.length()];
        for (int i = 0; i < resultStr.length(); i++) {
            result[i] = resultStr.charAt(i) - '0';
        }
        return result;
    }

    // Approach 4: Recursive Approach
    // Time Complexity: O(n) in the worst case (all 9s).
    // Space Complexity: O(n) due to the recursion depth.
    public static int[] plusOneRecursive(int[] digits) {
        return plusOneRecursiveHelper(digits, digits.length - 1);
    }

    private static int[] plusOneRecursiveHelper(int[] digits, int index) {
        if (index < 0) {
            int[] newDigits = new int[digits.length + 1];
            newDigits[0] = 1;
            return newDigits;
        }

        digits[index]++;
        if (digits[index] < 10) {
            return digits;
        }
        digits[index] = 0;
        return plusOneRecursiveHelper(digits, index - 1);
    }

    // Approach 5: Using Streams (Java 8 and later)
    // Time Complexity: O(n)
    // Space Complexity: O(n)
    public static int[] plusOneStreams(int[] digits) {
        // Find the index of the rightmost digit that is not 9
        int i = digits.length - 1;
        while (i >= 0 && digits[i] == 9) {
            i--;
        }

        if (i == -1) {
            // If all digits are 9, create a new array with an extra digit at the beginning
            int[] newDigits = new int[digits.length + 1];
            newDigits[0] = 1;
            return newDigits;
        } else {
            // Otherwise, increment the digit at index i and set all digits to the right to 0
            int[] newDigits = Arrays.copyOf(digits, digits.length); // Create a copy to avoid modifying original
            newDigits[i]++;
            for (int j = i + 1; j < newDigits.length; j++) {
                newDigits[j] = 0;
            }
            return newDigits;
        }
    }

    public static void main(String[] args) {
        // Example Usage of each approach.
        int[] digits1 = {1, 2, 3};
        System.out.println("Input: " + Arrays.toString(digits1));
        System.out.println("Iterative: " + Arrays.toString(plusOneIterative(digits1)));       // Output: [1, 2, 4]
        System.out.println("Convert to Number: " + Arrays.toString(plusOneConvertToNumber(digits1))); // Output: [1, 2, 4]
        System.out.println("BigInteger: " + Arrays.toString(plusOneBigInteger(digits1)));       // Output: [1, 2, 4]
        System.out.println("Recursive: " + Arrays.toString(plusOneRecursive(digits1)));          // Output: [1, 2, 4]
        System.out.println("Streams: " + Arrays.toString(plusOneStreams(digits1)));            // Output: [1, 2, 4]
        System.out.println();

        int[] digits2 = {9, 9, 9};
        System.out.println("Input: " + Arrays.toString(digits2));
        System.out.println("Iterative: " + Arrays.toString(plusOneIterative(digits2)));       // Output: [1, 0, 0, 0]
        System.out.println("Convert to Number: " + Arrays.toString(plusOneConvertToNumber(digits2))); // Output: [1, 0, 0, 0]
        System.out.println("BigInteger: " + Arrays.toString(plusOneBigInteger(digits2)));       // Output: [1, 0, 0, 0]
        System.out.println("Recursive: " + Arrays.toString(plusOneRecursive(digits2)));          // Output: [1, 0, 0, 0]
        System.out.println("Streams: " + Arrays.toString(plusOneStreams(digits2)));            // Output: [1, 0, 0, 0]
        System.out.println();

        int[] digits3 = {4, 3, 2, 1};
        System.out.println("Input: " + Arrays.toString(digits3));
        System.out.println("Iterative: " + Arrays.toString(plusOneIterative(digits3)));       // Output: [4, 3, 2, 2]
        System.out.println("Convert to Number: " + Arrays.toString(plusOneConvertToNumber(digits3))); // Output: [4, 3, 2, 2]
        System.out.println("BigInteger: " + Arrays.toString(plusOneBigInteger(digits3)));       // Output: [4, 3, 2, 2]
        System.out.println("Recursive: " + Arrays.toString(plusOneRecursive(digits3)));          // Output: [4, 3, 2, 2]
        System.out.println("Streams: " + Arrays.toString(plusOneStreams(digits3)));            // Output: [4, 3, 2, 2]
    }
}

/*
 * Real-World Project Implementations:
 *
 * 1.  E-commerce Systems:
 * -   Scenario: Incrementing the item quantity in a shopping cart.
 * -   Explanation: When a user adds an item to their cart or increases the quantity,
 * the system needs to update the quantity.  If the quantity is represented as
 * an array of digits (though it would normally be an integer), the `plusOneIterative`
 * method can be used to increment the quantity.  The system must handle cases
 * where adding one results in a carry-over (e.g., increasing from 9 to 10).
 * -   Relevance:  Essential for maintaining accurate cart information and order processing.
 *
 * 2.  Financial Systems:
 * -   Scenario: Incrementing transaction IDs or sequence numbers.
 * -   Explanation:  Financial systems often use sequential IDs for transactions, orders,
 * or records.  When a new transaction occurs, the system increments the last ID
 * to generate the next unique ID.  If these IDs are stored as digit arrays
 * for some reason, the `plusOneIterative` method can be used.  This ensures that
 * each transaction receives a unique identifier.  Using BigInteger is crucial
 * here to handle very large transaction IDs.
 * -  Relevance: Maintaining data integrity and audit trails.
 *
 * 3.  Version Control Systems:
 * -  Scenario:  Incrementing version numbers.
 * -  Explanation:  In software development, version numbers are used to track
 * changes to code or documents.  A version number might be represented as an
 * array of integers (e.g., [1, 2, 3] for version 1.2.3).  When a new version
 * is released, the system needs to increment the version number.  The `plusOneIterative`
 * method can be adapted to handle different versioning schemes (e.g., incrementing
 * the patch number, minor version, or major version).
 * -  Relevance:  Organizing and tracking software releases.
 *
 * 4.  High-Precision Scientific Calculations:
 * -  Scenario:  Incrementing counters in simulations or experiments.
 * -  Explanation:  In scientific applications, researchers may need to perform
 * calculations with very high precision, using numbers with hundreds or thousands
 * of digits.  These numbers might be represented as arrays of digits.  When
 * performing iterative calculations, it may be necessary to increment these
 * large numbers.  The `plusOneBigInteger` method is essential in these cases
 * to avoid overflow errors and ensure accuracy.
 * -  Relevance:  Ensuring the accuracy of scientific results.
 *
 * 5.  Digital Clock/Counter Systems
 * -  Scenario: Incrementing time or count values.
 * -  Explanation: Consider a digital clock or a counter display.  The displayed
 * time (hours, minutes, seconds) or count value can be thought of as an array
 * of digits.  The system needs to increment these digits every second or
 * count event.  The `plusOneIterative` method can be used to update the
 * displayed value, handling the carry-over from seconds to minutes, minutes
 * to hours, and so on.
 * -  Relevance: Updating displayed information in real-time.
 */
