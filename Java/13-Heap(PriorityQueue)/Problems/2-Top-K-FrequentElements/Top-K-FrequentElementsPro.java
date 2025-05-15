import java.util.*;

public class TopKFrequentElements {

    // Approach 1: Using a Min Heap (PriorityQueue)
    // Time Complexity: O(N log K), where N is the number of elements in the array.
    // Space Complexity: O(K), for the size of the heap.
    //
    // This approach efficiently finds the top K frequent elements. It's
    // commonly used in scenarios where you need to identify the most frequent items
    // in a dataset, such as:
    // - Analyzing website traffic to find the most visited pages.
    // - Finding the most popular products in an e-commerce store.
    // - Identifying the most common words in a document (text analysis).
    public static int[] topKFrequent_MinHeap(int[] nums, int k) {
        // 1. Count the frequency of each element using a HashMap.
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        for (int num : nums) {
            frequencyMap.put(num, frequencyMap.getOrDefault(num, 0) + 1);
        }

        // 2. Create a min heap (PriorityQueue) to store the top K frequent elements.
        //    The heap is ordered by frequency (lower frequency at the top).
        PriorityQueue<Integer> minHeap = new PriorityQueue<>(Comparator.comparingInt(frequencyMap::get));

        // 3. Iterate through the frequency map and add elements to the heap.
        for (int num : frequencyMap.keySet()) {
            minHeap.offer(num);
            if (minHeap.size() > k) {
                minHeap.poll(); // Remove the element with the lowest frequency if the heap size exceeds k.
            }
        }

        // 4. Extract the top K elements from the heap.
        //    We create an array of size k because we know that the heap will
        //    contain at most k elements.
        int[] result = new int[k];
        for (int i = k - 1; i >= 0; i--) {
            result[i] = minHeap.poll();
        }
        return result;
    }

    // Approach 2: Using a Max Heap (PriorityQueue)
    // Time Complexity: O(N + K log N), where N is the number of elements.
    // Space Complexity: O(N), for the size of the heap.
    //
    // This approach uses a max heap. While it has a slightly higher time complexity
    // in some cases compared to the min heap approach, it can be useful when you
    // need to perform other operations on the frequency-sorted elements, such as:
    // - Retrieving elements in descending order of frequency.
    // - Implementing a leaderboard where you need to display the top K scores.
    public static int[] topKFrequent_MaxHeap(int[] nums, int k) {
        // 1. Count the frequency of each element using a HashMap.
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        for (int num : nums) {
            frequencyMap.put(num, frequencyMap.getOrDefault(num, 0) + 1);
        }

        // 2. Create a max heap (PriorityQueue) to store elements based on their frequencies.
        //    The heap is ordered by frequency (higher frequency at the top).
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>((a, b) -> frequencyMap.get(b) - frequencyMap.get(a));

        // 3. Add all elements from the frequency map to the max heap.
        maxHeap.addAll(frequencyMap.keySet());

        // 4. Extract the top K elements from the max heap.
        int[] result = new int[k];
        for (int i = 0; i < k; i++) {
            result[i] = maxHeap.poll();
        }
        return result;
    }

    // Approach 3: Using Buckets (Bucket Sort)
    // Time Complexity: O(N), where N is the number of elements in the array.
    // Space Complexity: O(N), for the size of the buckets.
    //
    // This approach is very efficient, achieving linear time complexity. It's
    // particularly well-suited for scenarios where the range of frequencies is
    // relatively small compared to the number of elements, such as:
    // - Analyzing survey data where responses are on a limited scale (e.g., 1-5).
    // - Processing sensor data where readings fall within a known range.
    public static int[] topKFrequent_BucketSort(int[] nums, int k) {
        // 1. Count the frequency of each element using a HashMap.
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        for (int num : nums) {
            frequencyMap.put(num, frequencyMap.getOrDefault(num, 0) + 1);
        }

        // 2. Create an array of buckets to store elements based on their frequencies.
        //    The index of the bucket represents the frequency, and the value is a list of elements with that frequency.
        //    The size of the bucket array is max frequency + 1.
        List<Integer>[] buckets = new List[nums.length + 1];
        for (int num : frequencyMap.keySet()) {
            int frequency = frequencyMap.get(num);
            if (buckets[frequency] == null) {
                buckets[frequency] = new ArrayList<>();
            }
            buckets[frequency].add(num);
        }

        // 3. Iterate through the buckets in reverse order of frequency to get the top K elements.
        int[] result = new int[k];
        int index = 0;
        for (int i = buckets.length - 1; i >= 0 && index < k; i--) {
            if (buckets[i] != null) {
                for (int num : buckets[i]) {
                    result[index++] = num;
                    if (index == k) {
                        break;
                    }
                }
            }
        }
        return result;
    }

    // Approach 4: Using TreeMap
    // Time Complexity: O(N log N) in the worst case, where N is the number of elements.
    // Space Complexity: O(N), for the size of the TreeMap.
    //
    // This approach uses a TreeMap, which maintains elements in sorted order. It's
    // useful when you need the top K elements to be sorted by their frequency,
    // and you might also need to perform other operations on the sorted frequencies,
    // such as:
    // - Retrieving the frequency of a specific element.
    // - Finding the range of frequencies.
    public static int[] topKFrequent_TreeMap(int[] nums, int k) {
        // 1. Count the frequency of each element using a HashMap.
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        for (int num : nums) {
            frequencyMap.put(num, frequencyMap.getOrDefault(num, 0) + 1);
        }

        // 2. Create a TreeMap to store frequencies as keys and lists of elements with that frequency as values.
        //    TreeMap automatically sorts the frequencies in descending order.
        TreeMap<Integer, List<Integer>> frequencyToElements = new TreeMap<>(Collections.reverseOrder());
        for (int num : frequencyMap.keySet()) {
            int frequency = frequencyMap.get(num);
            if (!frequencyToElements.containsKey(frequency)) {
                frequencyToElements.put(frequency, new ArrayList<>());
            }
            frequencyToElements.get(frequency).add(num);
        }

        // 3. Extract the top K elements from the TreeMap.
        int[] result = new int[k];
        int index = 0;
        for (List<Integer> elements : frequencyToElements.values()) {
            for (int element : elements) {
                result[index++] = element;
                if (index == k) {
                    return result;
                }
            }
        }
        return result;
    }

    // Approach 5: Using QuickSelect (Modified)
    // Time Complexity: O(N) on average, O(N^2) in the worst case.
    // Space Complexity: O(N) in the worst case (due to recursion).
    //
    // This approach uses a modified QuickSelect algorithm. It's generally the
    // most efficient in terms of average-case time complexity, but it has a
    // worst-case time complexity of O(N^2). It's suitable for large datasets
    // where average-case performance is critical, such as:
    // - Real-time data analysis where speed is paramount.
    // - Processing massive datasets in batch jobs.
    public static int[] topKFrequent_QuickSelect(int[] nums, int k) {
        // 1. Count the frequency of each element using a HashMap.
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        for (int num : nums) {
            frequencyMap.put(num, frequencyMap.getOrDefault(num, 0) + 1);
        }

        // 2. Create an array of unique elements with their frequencies.
        int n = frequencyMap.size();
        int[] uniqueElements = new int[n];
        int[] frequencies = new int[n];
        int index = 0;
        for (Map.Entry<Integer, Integer> entry : frequencyMap.entrySet()) {
            uniqueElements[index] = entry.getKey();
            frequencies[index] = entry.getValue();
            index++;
        }

        // 3. Use QuickSelect to find the kth largest frequency.
        quickSelect(frequencies, uniqueElements, 0, n - 1, n - k); // Find the element at the (n-k)th position for top k

        // 4. Collect the top K frequent elements. These will be the last k elements
        //    in the uniqueElements array after the quickSelect (partitioning around the (n-k)th largest frequency).
        int[] result = new int[k];
        for (int i = 0; i < k; i++) {
            result[i] = uniqueElements[n - 1 - i];
        }
        return result;
    }

    // Helper function for QuickSelect
    private static void quickSelect(int[] frequencies, int[] elements, int low, int high, int k) {
        if (low == high) {
            return;
        }
        int pivotIndex = partition(frequencies, elements, low, high);
        if (pivotIndex == k) {
            return;
        } else if (pivotIndex < k) {
            quickSelect(frequencies, elements, pivotIndex + 1, high, k);
        } else {
            quickSelect(frequencies, elements, low, pivotIndex - 1, k);
        }
    }

    // Helper function for partitioning (used in QuickSelect)
    private static int partition(int[] frequencies, int[] elements, int low, int high) {
        int pivot = frequencies[high];
        int i = low;
        for (int j = low; j < high; j++) {
            if (frequencies[j] < pivot) { // Changed comparison to find kth largest
                // Swap frequencies and corresponding elements
                int tempFrequency = frequencies[i];
                frequencies[i] = frequencies[j];
                frequencies[j] = tempFrequency;

                int tempElement = elements[i];
                elements[i] = elements[j];
                elements[j] = tempElement;

                i++;
            }
        }
        // Swap pivot with the element at i
        int tempFrequency = frequencies[i];
        frequencies[i] = frequencies[high];
        frequencies[high] = tempFrequency;

        int tempElement = elements[i];
        elements[i] = elements[high];
        elements[high] = tempElement;
        return i;
    }

    public static void main(String[] args) {
        int[] nums = {1, 1, 1, 2, 2, 3};
        int k = 2;

        System.out.println("Input: nums = " + Arrays.toString(nums) + ", k = " + k);

        // Approach 1: Min Heap
        int[] result1 = topKFrequent_MinHeap(nums, k);
        System.out.println("Top " + k + " frequent elements (Min Heap): " + Arrays.toString(result1));

        // Approach 2: Max Heap
        int[] result2 = topKFrequent_MaxHeap(nums, k);
        System.out.println("Top " + k + " frequent elements (Max Heap): " + Arrays.toString(result2));

        // Approach 3: Bucket Sort
        int[] result3 = topKFrequent_BucketSort(nums, k);
        System.out.println("Top " + k + " frequent elements (Bucket Sort): " + Arrays.toString(result3));

        // Approach 4: TreeMap
        int[] result4 = topKFrequent_TreeMap(nums, k);
        System.out.println("Top " + k + " frequent elements (TreeMap): " + Arrays.toString(result4));

        // Approach 5: QuickSelect
        int[] result5 = topKFrequent_QuickSelect(nums, k);
        System.out.println("Top " + k + " frequent elements (QuickSelect): " + Arrays.toString(result5));
    }
}