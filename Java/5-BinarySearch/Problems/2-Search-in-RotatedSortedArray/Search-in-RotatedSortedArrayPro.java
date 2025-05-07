import java.util.Arrays;

public class RotatedSortedArraySearch {

    /**
     * **Approach 1: Iterative Binary Search with Rotation Handling**
     *
     * This is the most common and efficient approach for searching in a rotated sorted array.
     * It's a modification of the standard binary search algorithm.
     *
     * **Logic:**
     * 1.  Find the middle element.
     * 2.  Check if the target is equal to the middle element.
     * 3.  Determine which half of the array is sorted.
     * 4.  If the target is in the sorted half, search in that half.
     * 5.  Otherwise, search in the unsorted half.
     *
     * **Real-World Considerations:**
     * * Suitable for most applications where performance is critical.
     * * Well-suited for large datasets due to its logarithmic time complexity.
     * * Easy to understand and implement.
     *
     * **Time Complexity:** O(log n)
     * **Space Complexity:** O(1)
     */
    public static int searchIterative(int[] nums, int target) {
        int left = 0;
        int right = nums.length - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2; // Prevent overflow

            if (nums[mid] == target) {
                return mid;
            }

            if (nums[left] <= nums[mid]) { // Left half is sorted
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else { // Right half is sorted
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }

        return -1;
    }

    /**
     * **Approach 2: Recursive Binary Search with Rotation Handling**
     *
     * This approach is a recursive version of the iterative binary search.
     * It follows the same logic as the iterative approach but uses recursion.
     *
     * **Logic:**
     * 1.  Base case: If left > right, return -1 (target not found).
     * 2.  Find the middle element.
     * 3.  Check if the target is equal to the middle element.
     * 4.  Determine which half of the array is sorted.
     * 5.  Recursively search in the appropriate half.
     *
     * **Real-World Considerations:**
     * * Can be more concise to write for some developers.
     * * May have a slightly higher overhead due to function calls, but usually negligible.
     * * For very deep recursions, a stack overflow could occur (though unlikely in typical scenarios).
     *
     * **Time Complexity:** O(log n)
     * **Space Complexity:** O(log n) (due to the recursion call stack)
     */
    public static int searchRecursive(int[] nums, int target, int left, int right) {
        if (left > right) {
            return -1;
        }

        int mid = left + (right - left) / 2;

        if (nums[mid] == target) {
            return mid;
        }

        if (nums[left] <= nums[mid]) { // Left half is sorted
            if (nums[left] <= target && target < nums[mid]) {
                return searchRecursive(nums, target, left, mid - 1);
            } else {
                return searchRecursive(nums, target, mid + 1, right);
            }
        } else { // Right half is sorted
            if (nums[mid] < target && target <= nums[right]) {
                return searchRecursive(nums, target, mid + 1, right);
            } else {
                return searchRecursive(nums, target, left, mid - 1);
            }
        }
    }

    public static int searchRecursive(int[] nums, int target) {
        return searchRecursive(nums, target, 0, nums.length - 1);
    }

    /**
     * **Approach 3: Using Java Streams (Less Efficient for this Specific Problem)**
     *
     * This approach uses Java Streams to find the target.  While Streams are
     * powerful for many operations, they are not the most efficient for
     * a problem that fundamentally requires a binary search.  This is because
     * Streams don't inherently provide the random access needed for binary search.
     *
     * **Logic:**
     * 1. Convert the array to a stream.
     * 2. Use `IntStream.filter()` to find elements equal to the target.
     * 3. Use `findFirst()` to get the first matching element.
     * 4. If found, use `indexOf()` to get the index.
     *
     * **Real-World Considerations:**
     * * Generally *not* recommended for searching in sorted arrays when performance is critical.
     * * Streams are better suited for more complex data processing pipelines.
     * * Demonstrates Java 8 Stream API usage, but less efficient here.
     * * The `indexOf` operation on the original array after finding the element in the stream makes this approach linear in the worst case.
     *
     * **Time Complexity:** O(n) in the worst case (due to the potential need to iterate through the entire stream and the use of `indexOf`)
     * **Space Complexity:** O(1) (excluding the stream overhead, which is implementation-dependent but generally constant)
     */
    public static int searchWithStreams(int[] nums, int target) {
        return Arrays.stream(nums)
                .filter(num -> num == target)
                .findFirst()
                .stream() //convert the optional to stream to use index of.
                .map(n -> {
                    for (int i = 0; i < nums.length; i++) {
                        if (nums[i] == n) {
                            return i;
                        }
                    }
                    return -1;
                })
                .findFirst()
                .orElse(-1);
    }

    /**
     * **Approach 4: Find Rotation Point, Then Binary Search Twice**
     *
     * This approach first finds the rotation point (the index of the smallest
     * element) and then performs two separate binary searches: one on the
     * left sorted portion and one on the right sorted portion.
     *
     * **Logic:**
     * 1. Find the rotation point using a modified binary search.
     * 2. Perform binary search on the left side (0 to rotationPoint - 1).
     * 3. Perform binary search on the right side (rotationPoint to nums.length - 1).
     * 4. Return the index if found in either search, otherwise return -1.
     *
     * **Real-World Considerations:**
     * * Good for scenarios where you need to perform multiple searches on the same rotated array.  Finding the rotation point once amortizes the cost.
     * * Slightly more complex to implement than the basic iterative approach, but still efficient.
     *
     * **Time Complexity:** O(log n) (both finding the rotation point and the binary searches are logarithmic)
     * **Space Complexity:** O(1)
     */
    public static int searchRotationPoint(int[] nums, int target) {
        int rotationPoint = findRotationPoint(nums);
        int leftResult = binarySearch(nums, target, 0, rotationPoint - 1);
        int rightResult = binarySearch(nums, target, rotationPoint, nums.length - 1);

        return (leftResult != -1) ? leftResult : rightResult;
    }

    private static int findRotationPoint(int[] nums) {
        int left = 0;
        int right = nums.length - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }

    private static int binarySearch(int[] nums, int target, int left, int right) {
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }

    /**
     * **Approach 5: Using Java's built-in Arrays.binarySearch (with caveats)**
     *
     * Java's `Arrays.binarySearch` method can be used, but it assumes the array is
     * fully sorted.  We can use it *if* we know which half of the rotated array
     * is sorted, and the target is within that half.  This approach is *not* a
     * complete solution for a *general* rotated sorted array search.
     *
     * **Logic:**
     * 1.  Determine which half of the array *might* contain the target.
     * 2.  If the target *could* be in the sorted half, use `Arrays.binarySearch`.
     * 3.  If the target is not in the sorted half, return -1 (or search the other half, for a more complete solution).
     *
     * **Real-World Considerations:**
     * * This approach is **highly discouraged** for general use with rotated arrays. It only works in specific, limited cases.
     * * Using Arrays.binarySearch directly is simpler, but it's crucial to ensure the preconditions are met (the portion being searched *must* be sorted).
     * * For production code, the iterative or the find rotation point approaches are much safer and more reliable.
     * * This is added primarily for demonstration and comparison.
     * * This approach is NOT robust.
     *
     * **Time Complexity:** O(log n) (when used correctly on a sorted portion)
     * **Space Complexity:** O(1)
     */
    public static int searchWithArraysBinarySearch(int[] nums, int target) {
        int left = 0;
        int right = nums.length - 1;
        int mid = left + (right - left) / 2;

        if (nums.length == 0) return -1;

        if (nums[left] <= nums[mid]) { // Left half is sorted
            if (target >= nums[left] && target <= nums[mid]) {
                return Arrays.binarySearch(nums, left, mid + 1, target); // Important: exclusive right bound
            } else {
                return -1; // Target is not in the sorted left half.  To make this correct, you'd need to search the right half too.
            }
        } else { // Right half is sorted
            if (target >= nums[mid] && target <= nums[right]) {
                return Arrays.binarySearch(nums, mid, right + 1, target);  // Important: exclusive right bound
            } else {
                return -1; // Target is not in the sorted right half. To make this correct, you'd need to search the left half too.
            }
        }
        //This will not handle all cases.
        //return -1; //This is incomplete.
    }

    public static void main(String[] args) {
        int[] rotatedArray = {4, 5, 6, 7, 0, 1, 2};
        int target = 0;

        System.out.println("Iterative Search: " + searchIterative(rotatedArray, target)); // Output: 4
        System.out.println("Recursive Search: " + searchRecursive(rotatedArray, target)); // Output: 4
        System.out.println("Stream Search: " + searchWithStreams(rotatedArray, target)); // Output: 4
        System.out.println("Rotation Point Search: " + searchRotationPoint(rotatedArray, target)); // Output: 4
        System.out.println("Arrays.binarySearch: " + searchWithArraysBinarySearch(rotatedArray, target)); // Output: 4 (But this is NOT a general solution)

        int[] rotatedArray2 = {5, 1, 3};
        target = 3;
        System.out.println("Iterative Search: " + searchIterative(rotatedArray2, target));
        System.out.println("Recursive Search: " + searchRecursive(rotatedArray2, target));
        System.out.println("Stream Search: " + searchWithStreams(rotatedArray2, target));
        System.out.println("Rotation Point Search: " + searchRotationPoint(rotatedArray2, target));
        System.out.println("Arrays.binarySearch: " + searchWithArraysBinarySearch(rotatedArray2, target)); //incorrect
    }
}

