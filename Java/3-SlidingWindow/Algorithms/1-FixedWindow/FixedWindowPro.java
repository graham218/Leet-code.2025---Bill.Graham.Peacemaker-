import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class SlidingWindowFixed {

    public static void main(String[] args) {
        int[] arr = {1, 3, -1, -3, 5, 3, 6, 7};
        int k = 3; // Fixed window size

        // 1. Maximum of all subarrays of size k (Real-world: Stock price analysis)
        List<Integer> maxSubarrays = maxOfSubarrays(arr, k);
        System.out.println("1. Max of subarrays (Stock Analysis): " + maxSubarrays);

        // 2. Minimum of all subarrays of size k (Real-world: Finding lowest latency)
        List<Integer> minSubarrays = minOfSubarrays(arr, k);
        System.out.println("2. Min of subarrays (Latency Analysis): " + minSubarrays);

        // 3.  Sum of all subarrays of size k (Real-world: Moving average)
        List<Integer> sumSubarrays = sumOfSubarrays(arr, k);
        System.out.println("3. Sum of subarrays (Moving Average): " + sumSubarrays);

        // 4. Check if a subarray with sum equal to a target exists (Real-world: Anomaly Detection)
        int targetSum = 8;
        boolean existsSubarraySum = checkSubarraySum(arr, k, targetSum);
        System.out.println("4. Subarray with sum " + targetSum + " exists (Anomaly Detection): " + existsSubarraySum);

        // 5. Count occurrences of a specific element in each subarray (Real-world: Keyword frequency)
        int targetElement = 3;
        List<Integer> elementCounts = countElementOccurrences(arr, k, targetElement);
        System.out.println("5. Element " + targetElement + " occurrences (Keyword Frequency): " + elementCounts);
    }

    /**
     * 1. Maximum of all subarrays of size k
     *
     * Real-world application: Stock price analysis.  We want to find the maximum stock price
     * over a rolling window of 'k' days.  This helps identify trends and potential peaks.
     *
     * @param arr The input array.
     * @param k The size of the sliding window.
     * @return A list containing the maximum of each subarray of size k.
     */
    public static List<Integer> maxOfSubarrays(int[] arr, int k) {
        List<Integer> result = new ArrayList<>();
        if (arr == null || arr.length < k || k <= 0) {
            return result; // Handle invalid input
        }

        // Use a deque (double-ended queue) to efficiently track the maximum element in the window.
        LinkedList<Integer> deque = new LinkedList<>();

        // Process the first k elements.
        for (int i = 0; i < k; i++) {
            // Remove elements from the back of the deque that are smaller than the current element.
            while (!deque.isEmpty() && arr[i] >= arr[deque.peekLast()]) {
                deque.removeLast();
            }
            deque.addLast(i); // Add the index of the current element to the deque.
        }

        // Process the remaining elements.
        for (int i = k; i < arr.length; i++) {
            // The front of the deque contains the index of the maximum element in the previous window.
            result.add(arr[deque.peekFirst()]);

            // Remove elements from the front of the deque that are outside the current window.
            while (!deque.isEmpty() && deque.peekFirst() <= i - k) {
                deque.removeFirst();
            }

            // Remove elements from the back of the deque that are smaller than the current element.
            while (!deque.isEmpty() && arr[i] >= arr[deque.peekLast()]) {
                deque.removeLast();
            }
            deque.addLast(i); // Add the index of the current element to the deque.
        }

        // Add the maximum of the last window.
        result.add(arr[deque.peekFirst()]);
        return result;
    }

    /**
     * 2. Minimum of all subarrays of size k
     *
     * Real-world application: Finding the lowest latency over a fixed time window (e.g., k seconds).
     * This helps in identifying performance bottlenecks and ensuring quality of service.
     *
     * @param arr The input array.
     * @param k The size of the sliding window.
     * @return A list containing the minimum of each subarray of size k.
     */
    public static List<Integer> minOfSubarrays(int[] arr, int k) {
        List<Integer> result = new ArrayList<>();
        if (arr == null || arr.length < k || k <= 0) {
            return result;
        }

        LinkedList<Integer> deque = new LinkedList<>();

        for (int i = 0; i < k; i++) {
            while (!deque.isEmpty() && arr[i] <= arr[deque.peekLast()]) { // Changed to <= for minimum
                deque.removeLast();
            }
            deque.addLast(i);
        }

        for (int i = k; i < arr.length; i++) {
            result.add(arr[deque.peekFirst()]);
            while (!deque.isEmpty() && deque.peekFirst() <= i - k) {
                deque.removeFirst();
            }
            while (!deque.isEmpty() && arr[i] <= arr[deque.peekLast()]) { // Changed to <= for minimum
                deque.removeLast();
            }
            deque.addLast(i);
        }

        result.add(arr[deque.peekFirst()]);
        return result;
    }

    /**
     * 3. Sum of all subarrays of size k
     *
     * Real-world application: Calculating the moving average of a series of values, such as stock prices,
     * website traffic, or sensor readings.  Smoothing out short-term fluctuations and highlighting
     * longer-term trends.
     *
     * @param arr The input array.
     * @param k The size of the sliding window.
     * @return A list containing the sum of each subarray of size k.
     */
    public static List<Integer> sumOfSubarrays(int[] arr, int k) {
        List<Integer> result = new ArrayList<>();
        if (arr == null || arr.length < k || k <= 0) {
            return result;
        }

        int windowSum = 0;
        // Calculate the sum of the first window.
        for (int i = 0; i < k; i++) {
            windowSum += arr[i];
        }
        result.add(windowSum);

        // Slide the window through the rest of the array.
        for (int i = k; i < arr.length; i++) {
            windowSum = windowSum - arr[i - k] + arr[i]; // Subtract the outgoing element, add the incoming.
            result.add(windowSum);
        }
        return result;
    }

    /**
     * 4. Check if a subarray with sum equal to a target exists
     *
     * Real-world application: Anomaly detection in time series data.  If the sum of values in a window
     * deviates significantly from the expected sum, it could indicate an anomaly or an error.
     *
     * @param arr The input array.
     * @param k The size of the sliding window.
     * @param targetSum The target sum to check for.
     * @return True if a subarray with the target sum exists, false otherwise.
     */
    public static boolean checkSubarraySum(int[] arr, int k, int targetSum) {
        if (arr == null || arr.length < k || k <= 0) {
            return false;
        }

        int windowSum = 0;
        for (int i = 0; i < k; i++) {
            windowSum += arr[i];
        }
        if (windowSum == targetSum) {
            return true;
        }

        for (int i = k; i < arr.length; i++) {
            windowSum = windowSum - arr[i - k] + arr[i];
            if (windowSum == targetSum) {
                return true;
            }
        }
        return false;
    }

    /**
     * 5. Count occurrences of a specific element in each subarray
     *
     * Real-world application: Keyword frequency analysis in a text stream.  We want to count how many times
     * a specific keyword appears in a sliding window of text.  This can be used for sentiment analysis,
     * topic detection, and other text processing tasks.
     *
     * @param arr The input array.
     * @param k The size of the sliding window.
     * @param targetElement The element to count occurrences of.
     * @return A list containing the number of occurrences of the target element in each subarray of size k.
     */
    public static List<Integer> countElementOccurrences(int[] arr, int k, int targetElement) {
        List<Integer> result = new ArrayList<>();
        if (arr == null || arr.length < k || k <= 0) {
            return result;
        }

        int count = 0;
        for (int i = 0; i < k; i++) {
            if (arr[i] == targetElement) {
                count++;
            }
        }
        result.add(count);

        for (int i = k; i < arr.length; i++) {
            if (arr[i - k] == targetElement) {
                count--; // Decrement count if the outgoing element was the target.
            }
            if (arr[i] == targetElement) {
                count++; // Increment count if the incoming element is the target.
            }
            result.add(count);
        }
        return result;
    }
}

