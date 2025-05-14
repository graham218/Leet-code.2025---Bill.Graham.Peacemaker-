import java.util.HashSet;
import java.util.Set;

public class HappyNumber {

    /**
     * Approach 1: Using a HashSet to detect cycles.
     * A number is considered happy if, after repeatedly replacing it by the sum of the square of its digits,
     * it eventually reaches 1. If the process loops endlessly in a cycle which does not include 1, then the number is not happy.
     *
     * @param n The number to check.
     * @return true if n is a happy number, false otherwise.
     */
    public static boolean isHappyUsingSet(int n) {
        Set<Integer> seen = new HashSet<>();
        while (n != 1 && !seen.contains(n)) {
            seen.add(n);
            n = getSumOfSquares(n);
        }
        return n == 1;
    }

    /**
     * Helper function to calculate the sum of the squares of the digits of a number.
     *
     * @param n The number.
     * @return The sum of the squares of its digits.
     */
    private static int getSumOfSquares(int n) {
        int sum = 0;
        while (n > 0) {
            int digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        return sum;
    }

    /**
     * Approach 2: Using the Floyd Cycle Detection Algorithm (Tortoise and Hare).
     * This approach is more efficient as it doesn't require extra space to store seen numbers.
     * It uses two pointers, one moving one step at a time (slow), and the other moving two steps at a time (fast).
     * If there is a cycle, the two pointers will eventually meet.
     *
     * @param n The number to check.
     * @return true if n is a happy number, false otherwise.
     */
    public static boolean isHappyUsingFloyd(int n) {
        int slow = n;
        int fast = n;
        do {
            slow = getSumOfSquares(slow);
            fast = getSumOfSquares(getSumOfSquares(fast));
        } while (slow != fast);
        return slow == 1;
    }

    /**
     * Approach 3: Using a lookup table of known unhappy numbers.
     * Any number that eventually leads to 4 is unhappy.  We can expand this to include other numbers in the cycle.
     * This approach pre-computes the cycle and checks if the number reaches any of those.
     *
     * @param n The number to check.
     * @return true if n is a happy number, false otherwise.
     */
    public static boolean isHappyUsingLookup(int n) {
        // The cycle for unhappy numbers is: 4 -> 16 -> 37 -> 58 -> 89 -> 145 -> 42 -> 20 -> 4
        while (n != 1 && n != 4 && n != 16 && n != 37 && n != 58 && n != 89 && n != 145 && n != 42 && n != 20) {
            n = getSumOfSquares(n);
        }
        return n == 1;
    }

    /**
     * Approach 4: Iterative approach with a hardcoded limit.
     * Since the maximum value for n is 2^31 - 1, the maximum sum of squared digits will be less than 243.
     * So, we can iterate at most a fixed number of times (e.g., 100) to check if the number becomes 1.
     *
     * @param n The number to check.
     * @return true if n is a happy number, false otherwise.
     */
    public static boolean isHappyWithLimit(int n) {
        int count = 0;
        while (n != 1 && count <= 100) { // Limiting iterations to avoid infinite loop.
            n = getSumOfSquares(n);
            count++;
        }
        return n == 1;
    }

    /**
     * Approach 5: Recursive approach with a HashSet to detect cycles
     * This method uses recursion, combined with a Set to track previously seen numbers,
     * effectively preventing infinite loops by detecting cycles.
     *
     * @param n The number to check for happiness.
     * @param seen A set to keep track of numbers encountered during the recursion.
     * @return true if the number is happy, false otherwise.
     */
    public static boolean isHappyRecursive(int n, Set<Integer> seen) {
        if (n == 1) {
            return true; // Base case: 1 is a happy number
        }

        if (seen.contains(n)) {
            return false; // Base case: Cycle detected, not a happy number
        }

        seen.add(n); // Add the current number to the set
        int sumOfSquares = getSumOfSquares(n); // Calculate the sum of squared digits

        return isHappyRecursive(sumOfSquares, seen); // Recursive call with the new sum
    }

    public static boolean isHappyRecursive(int n) {
        return isHappyRecursive(n, new HashSet<>());
    }



    public static void main(String[] args) {
        int number = 19; // Example number to check

        System.out.println(number + " is a happy number using Set?: " + isHappyUsingSet(number));
        System.out.println(number + " is a happy number using Floyd's?: " + isHappyUsingFloyd(number));
        System.out.println(number + " is a happy number using Lookup?: " + isHappyUsingLookup(number));
        System.out.println(number + " is a happy number using Limit?: " + isHappyWithLimit(number));
        System.out.println(number + " is a happy number using Recursion?: " + isHappyRecursive(number));

        number = 2;
        System.out.println("\n" + number + " is a happy number using Set?: " + isHappyUsingSet(number));
        System.out.println(number + " is a happy number using Floyd's?: " + isHappyUsingFloyd(number));
        System.out.println(number + " is a happy number using Lookup?: " + isHappyUsingLookup(number));
        System.out.println(number + " is a happy number using Limit?: " + isHappyWithLimit(number));
        System.out.println(number + " is a happy number using Recursion?: " + isHappyRecursive(number));
    }
}
