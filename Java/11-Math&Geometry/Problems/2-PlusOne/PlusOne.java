import java.util.Arrays;

public class PlusOne {

    /**
     * **Approach 1: Iterative with Carry (Most Efficient)**
     *
     * -   Iterates through the digits array from right to left.
     * -   Adds 1 to the last digit.
     * -   If the digit becomes 10, set it to 0 and carry over 1 to the next digit.
     * -   If there's a carry after processing all digits, create a new array with an extra digit at the beginning (for the carry).
     *
     * **Time Complexity:** O(n) - where n is the number of digits.
     * **Space Complexity:** O(1) in the best case (no carry), O(n) in the worst case (carry to a new digit).
     *
     * @param digits The array of digits representing the non-negative integer.
     * @return A new array representing the integer incremented by one.
     */
    public static int[] plusOne_iterative(int[] digits) {
        int n = digits.length;

        // Iterate from the last digit (least significant) to the first.
        for (int i = n - 1; i >= 0; i--) {
            digits[i]++; // Add one to the current digit.

            if (digits[i] < 10) {
                // If the digit is less than 10, no carry-over is needed, so return the modified array.
                return digits;
            } else {
                // If the digit is 10, set it to 0 and carry-over 1 to the next digit.
                digits[i] = 0;
            }
        }

        // If the loop finishes and we still have a carry (i.e., the most significant digit was 9),
        // we need to create a new array with an extra digit to accommodate the carry.
        int[] newDigits = new int[n + 1];
        newDigits[0] = 1; // The first digit of the new array is the carry-over (1).
        // The rest of the new array will be initialized to 0 by default in Java.
        return newDigits;
    }

    /**
     * **Approach 2: Using BigInteger (For very large numbers)**
     *
     * -   Converts the digit array to a BigInteger.
     * -   Adds one to the BigInteger.
     * -   Converts the result back to an array of digits.
     *
     * **Time Complexity:** O(n) - where n is the number of digits (dominated by the conversion to and from String).  BigInteger addition is effectively constant time for reasonable inputs.
     * **Space Complexity:** O(n) -  for the BigInteger and the new digits array.
     *
     * @param digits The array of digits representing the non-negative integer.
     * @return A new array representing the integer incremented by one.
     */
    public static int[] plusOne_bigInteger(int[] digits) {
        StringBuilder sb = new StringBuilder();
        for (int digit : digits) {
            sb.append(digit);
        }
        java.math.BigInteger bigInteger = new java.math.BigInteger(sb.toString());
        bigInteger = bigInteger.add(java.math.BigInteger.ONE);
        String resultString = bigInteger.toString();
        int[] result = new int[resultString.length()];
        for (int i = 0; i < resultString.length(); i++) {
            result[i] = resultString.charAt(i) - '0';
        }
        return result;
    }

    /**
     * **Approach 3: Recursive with Carry**
     *
     * -   Recursively adds 1 to the least significant digit.
     * -   Handles the carry-over in the recursive calls.
     * -   Base case: If the digit is less than 10, return.
     * -   If there's a carry after processing all digits, create a new array with an extra digit.
     *
     * **Time Complexity:** O(n) - where n is the number of digits.
     * **Space Complexity:** O(n) - for the recursion call stack (in the worst case).
     *
     * @param digits The array of digits representing the non-negative integer.
     * @return A new array representing the integer incremented by one.
     */
    public static int[] plusOne_recursive(int[] digits) {
        int n = digits.length;
        // Create a new array.  We might need a bigger array.
        int[] result = new int[n + 1];
        // Copy the original digits into the *end* of the new array.
        System.arraycopy(digits, 0, result, 1, n);

        // Call the recursive helper, starting at the last index of the *new* array.
        recursiveAdd(result, n);

        // Check if there's a carry at the most significant position (index 0).
        if (result[0] == 0) {
            // No carry, return the last n elements of result.
            return Arrays.copyOfRange(result, 1, n + 1);
        }
        else {
            //otherwise return the whole array
            return result;
        }
    }

    private static void recursiveAdd(int[] arr, int index) {
        if (index < 0) {
            return; // Base case: end of the array, or carry propagated beyond.
        }
        arr[index]++; // Add 1 to the current digit.
        if (arr[index] < 10) {
            return; // No carry, so we're done.
        }
        arr[index] = 0; // Set to 0, and carry over.
        recursiveAdd(arr, index - 1); // Recursive call for the next digit.
    }



    /**
     * **Approach 4: Using a List (Intermediate List)**
     *
     * -   Converts the digit array to a List.
     * -   Adds 1 to the last element of the List.
     * -   Handles carry-overs within the List.
     * -   Converts the List back to an array.
     *
     * **Time Complexity:** O(n)
     * **Space Complexity:** O(n) - for the List.
     *
     * @param digits The array of digits representing the non-negative integer.
     * @return A new array representing the integer incremented by one.
     */
    public static int[] plusOne_list(int[] digits) {
        java.util.List<Integer> list = new java.util.ArrayList<>();
        for (int digit : digits) {
            list.add(digit);
        }

        int n = list.size();
        list.set(n - 1, list.get(n - 1) + 1); // Add 1 to the last digit.
        int carry = 0;

        for (int i = n - 1; i >= 0; i--) {
            int current = list.get(i) + carry;
            list.set(i, current % 10); // Store the digit.
            carry = current / 10;     // Calculate the carry.
        }

        if (carry > 0) {
            list.add(0, carry); // Add the carry to the beginning of the list.
        }

        int[] result = new int[list.size()];
        for (int i = 0; i < list.size(); i++) {
            result[i] = list.get(i);
        }
        return result;
    }

    /**
     * **Approach 5:  Carry with While Loop**
     *
     * -  Similar to the iterative approach, but uses a `while` loop to handle the carry.
     * -  This approach explicitly manages the carry variable.
     *
     * **Time Complexity:** O(n)
     * **Space Complexity:** O(1) (O(n) in the worst case where a new array is created)
     *
     * @param digits The array of digits representing the non-negative integer.
     * @return A new array representing the integer incremented by one.
     */
    public static int[] plusOne_carry(int[] digits) {
        int n = digits.length;
        int carry = 1; // Initialize carry to 1, since we're adding one.
        int i = n - 1;

        while (i >= 0 && carry > 0) {
            int sum = digits[i] + carry;
            digits[i] = sum % 10;
            carry = sum / 10;
            i--;
        }

        if (carry > 0) {
            int[] newDigits = new int[n + 1];
            newDigits[0] = carry;
            return newDigits;
        }

        return digits;
    }

    public static void main(String[] args) {
        int[] digits1 = {1, 2, 3};
        int[] result1 = plusOne_iterative(digits1);
        System.out.println("Iterative: " + Arrays.toString(result1)); // Output: [1, 2, 4]

        int[] digits2 = {9, 9, 9};
        int[] result2 = plusOne_bigInteger(digits2);
        System.out.println("BigInteger: " + Arrays.toString(result2)); // Output: [1, 0, 0, 0]

        int[] digits3 = {1, 2, 9};
        int[] result3 = plusOne_recursive(digits3);
        System.out.println("Recursive: " + Arrays.toString(result3)); // Output: [1, 3, 0]

        int[] digits4 = {9};
        int[] result4 = plusOne_list(digits4);
        System.out.println("List: " + Arrays.toString(result4)); // Output: [1, 0]

        int[] digits5 = {9, 8, 9};
        int[] result5 = plusOne_carry(digits5);
        System.out.println("Carry: " + Arrays.toString(result5)); // Output: [9, 9, 0]
    }
}
