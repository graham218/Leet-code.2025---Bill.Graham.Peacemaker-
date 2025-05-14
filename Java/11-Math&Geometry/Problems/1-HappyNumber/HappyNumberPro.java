import java.util.HashSet;
import java.util.Set;

public class HappyNumber {

    /**
     * Approach 1: Using a HashSet to detect cycles (Basic Implementation)
     *
     * A happy number is defined by the following process:
     * - Starting with any positive integer, replace the number by the sum of the squares of its digits.
     * - Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
     * - Those numbers for which this process ends in 1 are happy numbers.
     *
     * This method implements the basic approach to determine if a number is a happy number.
     * It uses a HashSet to keep track of previously seen numbers. If the same number appears again,
     * it indicates that the process is in a cycle, and the number is not a happy number.
     *
     * Example:
     * isHappy(19) == true  (19 -> 82 -> 68 -> 100 -> 1)
     * isHappy(2) == false   (2 -> 4 -> 16 -> 37 -> 58 -> 89 -> 145 -> 42 -> 20 -> 4 -> ...)
     *
     * @param n The integer to check for being a happy number.
     * @return true if n is a happy number, false otherwise.
     */
    public static boolean isHappy(int n) {
        Set<Integer> seenNumbers = new HashSet<>();
        while (n != 1 && !seenNumbers.contains(n)) {
            seenNumbers.add(n);
            n = getSumOfSquaredDigits(n);
        }
        return n == 1;
    }

    /**
     * Helper function to calculate the sum of the squares of the digits of a number.
     *
     * @param n The number to process.
     * @return The sum of the squares of the digits.
     */
    private static int getSumOfSquaredDigits(int n) {
        int sum = 0;
        while (n > 0) {
            int digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        return sum;
    }

    /**
     * Approach 2: Using the Floyd's Cycle Detection Algorithm (Optimized)
     *
     * This approach optimizes the happy number determination by using Floyd's cycle detection
     * algorithm (also known as the "tortoise and hare" algorithm).  Instead of storing every
     * seen number in a set, it uses two pointers, 'slow' and 'fast'.  The 'slow' pointer
     * moves one step at a time, while the 'fast' pointer moves two steps at a time.
     * If 'n' is a happy number, both pointers will eventually meet at 1. If 'n' is not a happy
     * number, the two pointers will meet at some other number within the cycle.  This approach
     * avoids the overhead of storing a large number of previously seen numbers, making it more
     * efficient in terms of space complexity.
     *
     * Example:
     * isHappyFloyd(19) == true
     * isHappyFloyd(2) == false
     *
     * @param n The integer to check.
     * @return true if n is a happy number, false otherwise.
     */
    public static boolean isHappyFloyd(int n) {
        int slow = n;
        int fast = n;
        do {
            slow = getSumOfSquaredDigits(slow);
            fast = getSumOfSquaredDigits(getSumOfSquaredDigits(fast));
        } while (slow != fast);
        return slow == 1;
    }

    /**
     * Approach 3: Using a Precomputed Set of Unhappy Numbers (Lookup Table)
     *
     * This approach precomputes the set of unhappy numbers that eventually fall into the 4, 16, 37, 58, 89, 145, 42, 20 cycle.
     * Instead of calculating the sum of squared digits repeatedly, we check if the number eventually reaches any number in this cycle.
     * This is based on the observation that all unhappy numbers will eventually fall into this specific cycle.
     * This approach provides a time-efficient way to check for happy numbers, as it avoids repeated calculations
     * for known unhappy number sequences.
     *
     * Example:
     * isHappyPrecomputed(19) == true
     * isHappyPrecomputed(2) == false
     *
     * @param n The integer to check.
     * @return true if n is a happy number, false otherwise.
     */
    public static boolean isHappyPrecomputed(int n) {
        Set<Integer> unhappyNumbers = Set.of(4, 16, 37, 58, 89, 145, 42, 20); // Unhappy number cycle
        while (n != 1 && !unhappyNumbers.contains(n)) {
            n = getSumOfSquaredDigits(n);
        }
        return n == 1;
    }

    /**
     * Approach 4: Recursive Approach with Memoization
     *
     * This approach uses recursion with memoization to determine if a number is happy.
     * Memoization is a technique where the results of expensive function calls are cached
     * and reused when the same inputs occur again.  This can significantly improve performance
     * by avoiding redundant calculations.  In this case, we use a HashSet to store the
     * numbers we've already encountered during the recursion.  If we encounter a number
     * again, we know we're in a cycle and the number is not happy.
     *
     * @param n The integer to check.
     * @return true if n is a happy number, false otherwise.
     */
    public static boolean isHappyRecursive(int n) {
        Set<Integer> memo = new HashSet<>();
        return isHappyRecursiveHelper(n, memo);
    }

    private static boolean isHappyRecursiveHelper(int n, Set<Integer> memo) {
        if (n == 1) {
            return true;
        }
        if (memo.contains(n)) {
            return false; // Cycle detected
        }
        memo.add(n);
        int nextNumber = getSumOfSquaredDigits(n);
        return isHappyRecursiveHelper(nextNumber, memo);
    }


    /**
     * Approach 5: Iterative Approach with Early Termination for Known Unhappy Numbers
     *
     * This approach is an iterative method that incorporates an optimization for early termination.
     * It leverages the fact that all unhappy numbers eventually fall into the same cycle:
     * 4 -> 16 -> 37 -> 58 -> 89 -> 145 -> 42 -> 20 -> 4.  The algorithm calculates the sum of squared
     * digits iteratively. If at any point the sum becomes one of the numbers in this cycle,
     * it immediately terminates and returns false, indicating that the original number is not a happy number.
     * If the sum reaches 1, the algorithm terminates and returns true. This approach is efficient
     * because it avoids unnecessary calculations once it's determined that a number is unhappy.
     *
     * @param n The number to be checked.
     * @return true if the number is a happy number, false otherwise.
     */
    public static boolean isHappyIterativeEarlyExit(int n) {
        while (n != 1) {
            n = getSumOfSquaredDigits(n);
            if (n == 4 || n == 16 || n == 37 || n == 58 || n == 89 || n == 145 || n == 42 || n == 20) {
                return false; // Early exit for unhappy numbers
            }
        }
        return true;
    }

    public static void main(String[] args) {
        // Test cases
        System.out.println("Is 19 a happy number? (Approach 1): " + isHappy(19)); // true
        System.out.println("Is 2 a happy number? (Approach 1): " + isHappy(2));   // false

        System.out.println("Is 19 a happy number? (Approach 2 - Floyd's): " + isHappyFloyd(19)); // true
        System.out.println("Is 2 a happy number? (Approach 2 - Floyd's): " + isHappyFloyd(2));   // false

        System.out.println("Is 19 a happy number? (Approach 3 - Precomputed): " + isHappyPrecomputed(19)); // true
        System.out.println("Is 2 a happy number? (Approach 3 - Precomputed): " + isHappyPrecomputed(2));   // false

        System.out.println("Is 19 a happy number? (Approach 4 - Recursive): " + isHappyRecursive(19)); // true
        System.out.println("Is 2 a happy number? (Approach 4 - Recursive): " + isHappyRecursive(2));   // false

        System.out.println("Is 19 a happy number? (Approach 5 - Iterative Early Exit): " + isHappyIterativeEarlyExit(19)); // true
        System.out.println("Is 2 a happy number? (Approach 5 - Iterative Early Exit): " + isHappyIterativeEarlyExit(2));   // false
    }
}

