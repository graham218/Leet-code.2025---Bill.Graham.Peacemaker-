import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.Collections; // Import Collections

public class ThreeSum {

    /**
     * Approach 1: Basic Two Pointers
     * -   The most straightforward approach.
     * -   Sort the array first.
     * -   Fix one element and use two pointers to find the other two elements.
     * -   Time Complexity: O(n^2), Space Complexity: O(1) (excluding result list)
     *
     * @param nums The input array of integers.
     * @return A list of unique triplets that sum to zero.
     */
    public List<List<Integer>> threeSum1(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        Arrays.sort(nums); // Sort the array to use the two-pointer technique

        for (int i = 0; i < nums.length - 2; i++) {
            // Skip duplicate elements for the first number
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            int left = i + 1;
            int right = nums.length - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {
                    result.add(Arrays.asList(nums[i], nums[left], nums[right]));
                    // Skip duplicate elements for the second and third numbers
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++;
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        return result;
    }

    /**
     * Approach 2: Using HashSet to Avoid Duplicates
     * -   Uses a HashSet to store the triplets to ensure uniqueness.
     * -   Similar to the basic two-pointer approach but handles duplicates differently.
     * -   Time Complexity: O(n^2), Space Complexity: O(n) in worst case.
     *
     * @param nums The input array of integers.
     * @return A list of unique triplets that sum to zero.
     */
    public List<List<Integer>> threeSum2(int[] nums) {
        Set<List<Integer>> resultSet = new HashSet<>(); // Use a set to store unique triplets
        Arrays.sort(nums);

        for (int i = 0; i < nums.length - 2; i++) {
            int left = i + 1;
            int right = nums.length - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {
                    resultSet.add(Arrays.asList(nums[i], nums[left], nums[right])); // Add to set
                    left++;
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        return new ArrayList<>(resultSet); // Convert the set to a list
    }

    /**
     * Approach 3: Optimized with Early Exit
     * -   Includes an optimization to exit early if the current number is positive.
     * -   Improves performance in some cases.
     * -   Time Complexity: O(n^2), Space Complexity: O(1)
     *
     * @param nums The input array of integers.
     * @return A list of unique triplets that sum to zero.
     */
    public List<List<Integer>> threeSum3(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        Arrays.sort(nums);

        for (int i = 0; i < nums.length - 2; i++) {
            if (nums[i] > 0) { // Optimization: If the current number is positive, no need to continue.
                break;
            }
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            int left = i + 1;
            int right = nums.length - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {
                    result.add(Arrays.asList(nums[i], nums[left], nums[right]));
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++;
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        return result;
    }

    /**
     * Approach 4: Using Java 8 Streams (for demonstration)
     * -   Demonstrates a solution using Java 8 streams.
     * -   Less efficient than the two-pointer approach, primarily for demonstration.
     * -   Time Complexity: O(n^3) in the worst case, Space Complexity: O(n)
     * -  Note: This approach can be less efficient and harder to read for this problem.
     *
     * @param nums The input array of integers.
     * @return A list of unique triplets that sum to zero.
     */
    public List<List<Integer>> threeSum4(int[] nums) {
        List<Integer> numsList = Arrays.stream(nums).boxed().collect(Collectors.toList()); //convert int[] to List<Integer> to use indexOf
        return numsList.stream()
                .flatMap(i -> numsList.stream()
                        .flatMap(j -> numsList.stream()
                                .filter(k -> numsList.indexOf(i) < numsList.indexOf(j) && numsList.indexOf(j) < numsList.indexOf(k) && i + j + k == 0) // added index check.
                                .map(k -> Arrays.asList(i, j, k))
                        )
                )
                .distinct()
                .collect(Collectors.toList());
    }

    /**
     * Approach 5: Using HashMap (Less Efficient for 3Sum)
     * -   Uses a HashMap to find the third number.
     * -   Generally less efficient for the 3Sum problem compared to the two-pointer approach.
     * -   Time Complexity: O(n^2), Space Complexity: O(n)
     *
     * @param nums The input array of integers.
     * @return A list of unique triplets that sum to zero.
     */
    public List<List<Integer>> threeSum5(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        Set<List<Integer>> resultSet = new HashSet<>();
        for (int i = 0; i < nums.length - 2; i++) {
            for (int j = i + 1; j < nums.length - 1; j++) {
                for(int k = j+1; k < nums.length; k++){
                    if(nums[i] + nums[j] + nums[k] == 0){
                        List<Integer> triplet = Arrays.asList(nums[i], nums[j], nums[k]);
                        Collections.sort(triplet);
                        resultSet.add(triplet);
                    }
                }
            }
        }
        return new ArrayList<>(resultSet);
    }

    public static void main(String[] args) {
        ThreeSum solution = new ThreeSum();
        int[] nums = {-1, 0, 1, 2, -1, -4};

        System.out.println("Approach 1: " + solution.threeSum1(nums));
        System.out.println("Approach 2: " + solution.threeSum2(nums));
        System.out.println("Approach 3: " + solution.threeSum3(nums));
        System.out.println("Approach 4: " + solution.threeSum4(nums));
        System.out.println("Approach 5: " + solution.threeSum5(nums));
    }
}

