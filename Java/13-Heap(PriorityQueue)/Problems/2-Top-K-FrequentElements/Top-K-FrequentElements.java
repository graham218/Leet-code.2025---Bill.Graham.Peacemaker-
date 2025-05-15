import java.util.*;

public class TopKFrequentElements {

    /**
     * Given an integer array nums and an integer k, return the k most frequent elements.
     * You may return the answer in any order.
     *
     * Example 1:
     * Input: nums = [1,1,1,2,2,3], k = 2
     * Output: 2:
     * Input: nums = [1], k = 1
     * Output: [1]
     *
     * Constraints:
     * 1 <= nums.length <= 10^5
     * -10^4 <= nums[i] <= 10^4
     * k is in the range [1, the number of unique elements in the array].
     * It is guaranteed that the answer is unique.
     */

    // Approach 1: Using HashMap and PriorityQueue (Min Heap)
    // Time Complexity: O(N log K), N is the number of elements in nums
    // Space Complexity: O(N + K), N for HashMap, K for PriorityQueue
    public static int[] topKFrequent1(int[] nums, int k) {
        // 1. Count the frequency of each element using a HashMap
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        for (int num : nums) {
            frequencyMap.put(num, frequencyMap.getOrDefault(num, 0) + 1);
        }

        // 2. Create a min-heap (PriorityQueue) to store the top k frequent elements.
        //    The heap is ordered by frequency (ascending order).
        PriorityQueue<Integer> minHeap = new PriorityQueue<>(Comparator.comparingInt(frequencyMap::get));

        // 3. Iterate through the HashMap and add elements to the min-heap.
        //    If the heap size exceeds k, remove the element with the lowest frequency.
        for (int num : frequencyMap.keySet()) {
            minHeap.add(num);
            if (minHeap.size() > k) {
                minHeap.poll(); // Remove the least frequent element
            }
        }

        // 4. Create an array to store the result and extract elements from the min-heap.
        int[] result = new int[k];
        for (int i = k - 1; i >= 0; i--) {
            result[i] = minHeap.poll(); // Get the most frequent element
        }
        return result;
    }

    // Approach 2: Using HashMap and Sorting (Full Sort)
    // Time Complexity: O(N log N), N is the number of elements in nums (due to sorting)
    // Space Complexity: O(N), N for HashMap
    public static int[] topKFrequent2(int[] nums, int k) {
        // 1. Count element frequencies using a HashMap
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        for (int num : nums) {
            frequencyMap.put(num, frequencyMap.getOrDefault(num, 0) + 1);
        }

        // 2. Create a list of unique elements
        List<Integer> uniqueElements = new ArrayList<>(frequencyMap.keySet());

        // 3. Sort the list of unique elements based on their frequencies in descending order.
        uniqueElements.sort((a, b) -> frequencyMap.get(b) - frequencyMap.get(a));

        // 4. Create the result array and add the top k elements.
        int[] result = new int[k];
        for (int i = 0; i < k; i++) {
            result[i] = uniqueElements.get(i);
        }
        return result;
    }

    // Approach 3: Using HashMap and Bucket Sort
    // Time Complexity: O(N), N is the number of elements in nums
    // Space Complexity: O(N), N for HashMap and the bucket array
    public static int[] topKFrequent3(int[] nums, int k) {
        // 1. Count element frequencies using a HashMap
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        for (int num : nums) {
            frequencyMap.put(num, frequencyMap.getOrDefault(num, 0) + 1);
        }

        // 2. Create a bucket array where the index represents frequency and the value is a list of elements with that frequency.
        //    The maximum possible frequency is nums.length.
        List<Integer>[] buckets = new List[nums.length + 1];
        for (int num : frequencyMap.keySet()) {
            int frequency = frequencyMap.get(num);
            if (buckets[frequency] == null) {
                buckets[frequency] = new ArrayList<>();
            }
            buckets[frequency].add(num);
        }

        // 3. Create the result array and fill it with the top k frequent elements by iterating through the buckets in reverse order.
        int[] result = new int[k];
        int index = 0;
        for (int i = buckets.length - 1; i >= 1 && index < k; i--) { // Iterate from highest frequency to lowest
            if (buckets[i] != null) {
                for (int num : buckets[i]) {
                    result[index++] = num;
                    if (index == k) {
                        break; // Stop when we have found k elements
                    }
                }
            }
        }
        return result;
    }

    // Approach 4: Using Java 8 Streams
    // Time Complexity: O(N log K), N is the number of elements in nums
    // Space Complexity: O(N)
    public static int[] topKFrequent4(int[] nums, int k) {
        return Arrays.stream(nums)
                .boxed() // Convert int[] to Stream<Integer>
                .collect(Collectors.toMap( // Collect elements into a map
                        num -> num, // Key: the number itself
                        num -> 1,    // Value: initial count is 1
                        Integer::sum, // Merge function: sum the counts for duplicate keys
                        HashMap::new // Use a HashMap
                ))
                .entrySet() // Get the entry set (number, frequency)
                .stream()  // Convert the entry set to a stream
                .sorted(Map.Entry.<Integer, Integer>comparingByValue().reversed()) // Sort by frequency (descending)
                .limit(k) // Take the top k elements
                .mapToInt(Map.Entry::getKey) // Extract the number (key)
                .toArray(); // Convert the stream to an int[]
    }

    // Approach 5: Using HashMap and Collections.sort (Partial Sort)
    // Time Complexity: O(N + K log K),  N for counting, K log K for sorting the top k.
    // Space Complexity: O(N)
    public static int[] topKFrequent5(int[] nums, int k) {
        // 1. Count the frequency of each element using a HashMap
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        for (int num : nums) {
            frequencyMap.put(num, frequencyMap.getOrDefault(num, 0) + 1);
        }

        // 2. Create a list of entries from the frequency map.
        List<Map.Entry<Integer, Integer>> entryList = new ArrayList<>(frequencyMap.entrySet());

        // 3. Sort the first k elements of the entry list. This effectively sorts the top k frequent elements.
        entryList.sort(0, k, Map.Entry.comparingByValue(Comparator.reverseOrder()));

        // 4. Create result array and copy the top k elements
        int[] result = new int[k];
        for (int i = 0; i < k; i++) {
            result[i] = entryList.get(i).getKey();
        }

        return result;
    }

    public static void main(String[] args) {
        int[] nums = {1, 1, 1, 2, 2, 3};
        int k = 2;

        System.out.println("Input: nums = " + Arrays.toString(nums) + ", k = " + k);
        System.out.println("Top " + k + " frequent elements (Approach 1): " + Arrays.toString(topKFrequent1(nums, k))); // Using PriorityQueue
        System.out.println("Top " + k + " frequent elements (Approach 2): " + Arrays.toString(topKFrequent2(nums, k))); // Using Full Sort
        System.out.println("Top " + k + " frequent elements (Approach 3): " + Arrays.toString(topKFrequent3(nums, k))); // Using Bucket Sort
        System.out.println("Top " + k + " frequent elements (Approach 4): " + Arrays.toString(topKFrequent4(nums, k))); // Using Java 8 Streams
        System.out.println("Top " + k + " frequent elements (Approach 5): " + Arrays.toString(topKFrequent5(nums, k))); // Using partial sort
    }
}
