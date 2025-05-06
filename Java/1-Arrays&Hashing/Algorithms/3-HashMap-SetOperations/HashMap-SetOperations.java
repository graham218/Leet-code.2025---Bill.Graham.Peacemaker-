import java.util.*;
import java.lang.*;

class HashMapSetOperations {

    public static void main(String[] args) {
        // Test data
        String[] words1 = {"apple", "banana", "apple", "orange", "banana", "kiwi"};
        String[] words2 = {"grape", "apple", "kiwi", "mango", "banana"};

        System.out.println("Original Arrays:");
        System.out.println("Array 1: " + Arrays.toString(words1));
        System.out.println("Array 2: " + Arrays.toString(words2));
        System.out.println();

        // 1. Find unique elements in an array
        System.out.println("1. Unique elements in Array 1:");
        findUniqueElements(words1);
        System.out.println();

        // 2. Find common elements between two arrays
        System.out.println("2. Common elements between Array 1 and Array 2:");
        findCommonElements(words1, words2);
        System.out.println();

        // 3. Count word frequencies in an array
        System.out.println("3. Word frequencies in Array 1:");
        countWordFrequencies(words1);
        System.out.println();

        // 4. Check if one array is a subset of another
        System.out.println("4. Is Array 2 a subset of Array 1?");
        System.out.println(isSubset(words1, words2));
        System.out.println();

        // 5. Find the first non-repeating element in an array
        System.out.println("5. First non-repeating element in Array 1:");
        findFirstNonRepeating(words1);
    }

    // 1. Find unique elements in an array using HashSet
    //    -  Time Complexity: O(n), where n is the length of the array.
    //    -  Space Complexity: O(n), in the worst case, to store all unique elements.
    public static void findUniqueElements(String[] arr) {
        Set<String> uniqueSet = new HashSet<>();
        for (String word : arr) {
            uniqueSet.add(word); // Add each word to the set.  Duplicates are automatically ignored.
        }
        System.out.println(uniqueSet); // Print the set, which contains only unique elements.
    }

    // 2. Find common elements between two arrays using HashSet
    //    -  Time Complexity: O(m + n), where m and n are the lengths of the two arrays.
    //    -  Space Complexity: O(min(m, n)), to store the smaller array in the set.
    public static void findCommonElements(String[] arr1, String[] arr2) {
        Set<String> set1 = new HashSet<>(Arrays.asList(arr1)); // Store elements of arr1 in a HashSet.
        Set<String> commonSet = new HashSet<>(); // Store the common elements
        for (String word : arr2) {
            if (set1.contains(word)) { // Check if the element from arr2 is present in set1.
                commonSet.add(word); // If present, add it to the common set.
            }
        }
        System.out.println(commonSet); // Print the common elements.
    }

    // 3. Count word frequencies in an array using HashMap
    //    -  Time Complexity: O(n), where n is the length of the array.
    //    -  Space Complexity: O(k), where k is the number of unique words.
    public static void countWordFrequencies(String[] arr) {
        Map<String, Integer> wordCountMap = new HashMap<>();
        for (String word : arr) {
            // If the word is already in the map, increment its count; otherwise, add it with a count of 1.
            wordCountMap.put(word, wordCountMap.getOrDefault(word, 0) + 1);
        }
        // Iterate through the map and print each word with its frequency.
        for (Map.Entry<String, Integer> entry : wordCountMap.entrySet()) {
            System.out.println(entry.getKey() + ": " + entry.getValue());
        }
    }

    // 4. Check if one array is a subset of another using HashSet
    //    -  Time Complexity: O(m + n), where m and n are the lengths of the two arrays.
    //    -  Space Complexity: O(m), where m is the length of the first array.
    public static boolean isSubset(String[] arr1, String[] arr2) {
        Set<String> set1 = new HashSet<>(Arrays.asList(arr1)); // Store elements of arr1 in a HashSet.
        for (String word : arr2) {
            if (!set1.contains(word)) { // If any element from arr2 is not in set1, it's not a subset.
                return false;
            }
        }
        return true; // If the loop completes without finding any missing element, arr2 is a subset of arr1.
    }

    // 5. Find the first non-repeating element in an array using LinkedHashMap
    //    -  Time Complexity: O(n), where n is the length of the array.
    //    -  Space Complexity: O(k), where k is the number of unique elements in the array.  In the worst case, k == n.
    public static void findFirstNonRepeating(String[] arr) {
        Map<String, Integer> countMap = new LinkedHashMap<>(); // Use LinkedHashMap to maintain insertion order.

        // Count the frequency of each element in the array.
        for (String word : arr) {
            countMap.put(word, countMap.getOrDefault(word, 0) + 1);
        }

        // Iterate through the map to find the first element with a frequency of 1.
        for (Map.Entry<String, Integer> entry : countMap.entrySet()) {
            if (entry.getValue() == 1) {
                System.out.println(entry.getKey()); // Print the first non-repeating element.
                return; // Exit the method after finding the first non-repeating element.
            }
        }
        System.out.println("No non-repeating element found."); // If no non-repeating element is found.
    }
}

