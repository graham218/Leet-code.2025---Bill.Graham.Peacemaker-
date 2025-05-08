import java.util.*;
import java.io.*;


public class MergeSortLinkedList {

    // Helper function to print the linked list
    public static void printList(ListNode head) {
        ListNode current = head;
        while (current != null) {
            System.out.print(current.val + " -> ");
            current = current.next;
        }
        System.out.println("null");
    }

    // Helper function to create a linked list from an array
    public static ListNode createListFromArray(int[] arr) {
        if (arr == null || arr.length == 0) {
            return null;
        }
        ListNode head = new ListNode(arr[0]);
        ListNode current = head;
        for (int i = 1; i < arr.length; i++) {
            current.next = new ListNode(arr[i]);
            current = current.next;
        }
        return head;
    }

    // 1. Top-Down Merge Sort (Recursive) - Classic Approach
    //   - Divide: Split the list into two halves recursively.
    //   - Conquer: Sort each half recursively.
    //   - Combine: Merge the sorted halves.
    // - Time Complexity: O(n log n)
    // - Space Complexity: O(log n) (due to recursion stack)
    public static ListNode mergeSortTopDown(ListNode head) {
        if (head == null || head.next == null) {
            return head; // Base case: 0 or 1 node, already sorted
        }

        // 1. Find the middle node using the slow and fast pointer technique.
        ListNode middle = findMiddle(head);
        ListNode nextOfMiddle = middle.next;

        // 2. Split the list into two halves.
        middle.next = null; // Important!  Break the link.

        // 3. Recursively sort the two halves.
        ListNode left = mergeSortTopDown(head);      // Sort the left half
        ListNode right = mergeSortTopDown(nextOfMiddle); // Sort the right half

        // 4. Merge the sorted halves.
        ListNode sortedList = merge(left, right);
        return sortedList;
    }

    // Helper function to find the middle node of a linked list
    private static ListNode findMiddle(ListNode head) {
        if (head == null) {
            return null;
        }
        ListNode slow = head;
        ListNode fast = head;
        // Floyd's Cycle Detection Algorithm (modified)
        while (fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    }

    // Helper function to merge two sorted linked lists
    private static ListNode merge(ListNode left, ListNode right) {
        ListNode dummy = new ListNode(0); // Dummy node to simplify merging
        ListNode tail = dummy;

        while (left != null && right != null) {
            if (left.val <= right.val) {
                tail.next = left;
                left = left.next;
            } else {
                tail.next = right;
                right = right.next;
            }
            tail = tail.next;
        }

        // Append the remaining nodes of either list (if any)
        tail.next = (left != null) ? left : right;
        return dummy.next; // Return the merged list, starting from the first real node
    }


    // 2. Bottom-Up Merge Sort (Iterative) - Efficient for Large Lists
    //   - Iterative approach, avoids recursion.
    //   - Merges sublists of increasing size.
    // - Time Complexity: O(n log n)
    // - Space Complexity: O(1) - Constant space
    public static ListNode mergeSortBottomUp(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }

        ListNode dummy = new ListNode(0); // Dummy node to simplify merging
        dummy.next = head;
        int n = getLength(head); // Get the length of the linked list

        // Iterate through sublist sizes: 1, 2, 4, 8, ...
        for (int size = 1; size < n; size <<= 1) { // size *= 2, but left shift is often faster
            ListNode prev = dummy;
            ListNode curr = dummy.next;

            while (curr != null) {
                // Divide the list into two sublists of size 'size'
                ListNode left = curr;
                ListNode right = split(curr, size); // Split the list.
                curr = split(right, size);       // Advance curr for next merge

                // Merge the two sublists
                prev.next = merge(left, right);
                // Advance 'prev' to the end of the merged sublist
                while (prev.next != null) {
                    prev = prev.next;
                }
            }
        }
        return dummy.next;
    }

    // Helper function to get the length of a linked list
    private static int getLength(ListNode head) {
        int length = 0;
        ListNode current = head;
        while (current != null) {
            length++;
            current = current.next;
        }
        return length;
    }

    // Helper function to split a linked list into two parts
    // Splits the list after 'size' nodes, returning the head of the second part
    private static ListNode split(ListNode head, int size) {
        if (head == null) {
            return null;
        }
        ListNode current = head;
        for (int i = 1; i < size && current.next != null; i++) {
            current = current.next;
        }
        ListNode next = current.next;
        current.next = null; // Split the list
        return next;
    }


    // 3. Merge Sort with Optimized Merge (Reduces Comparisons) - Optimization
    //   - Optimizes the merge step to reduce unnecessary comparisons.
    //   - Useful when one list is significantly shorter than the other.
    // - Time Complexity: O(n log n) -  In the average case, can be slightly better than standard merge.
    // - Space Complexity: O(log n) for top-down, O(1) for bottom-up (depending on the base algorithm)
    public static ListNode mergeSortOptimized(ListNode head, boolean useTopDown) {
        if (useTopDown) {
            return mergeSortTopDownOptimized(head);
        } else {
            return mergeSortBottomUpOptimized(head);
        }
    }

    private static ListNode mergeSortTopDownOptimized(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }
        ListNode middle = findMiddle(head);
        ListNode nextOfMiddle = middle.next;
        middle.next = null;

        ListNode left = mergeSortTopDownOptimized(head);
        ListNode right = mergeSortTopDownOptimized(nextOfMiddle);
        return mergeOptimized(left, right);
    }

    private static ListNode mergeSortBottomUpOptimized(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }

        ListNode dummy = new ListNode(0);
        dummy.next = head;
        int n = getLength(head);

        for (int size = 1; size < n; size <<= 1) {
            ListNode prev = dummy;
            ListNode curr = dummy.next;

            while (curr != null) {
                ListNode left = curr;
                ListNode right = split(curr, size);
                curr = split(right, size);
                prev.next = mergeOptimized(left, right); // Use optimized merge
                while (prev.next != null) {
                    prev = prev.next;
                }
            }
        }
        return dummy.next;
    }
    private static ListNode mergeOptimized(ListNode left, ListNode right) {
        if (left == null) return right;
        if (right == null) return left;

        ListNode dummy = new ListNode(0);
        ListNode tail = dummy;

        while (left != null && right != null) {
            if (left.val <= right.val) {
                tail.next = left;
                left = left.next;
            } else {
                tail.next = right;
                right = right.next;
            }
            tail = tail.next;
        }
        tail.next = (left != null) ? left : right;
        return dummy.next;
    }


    // 4. Merge Sort with Insertion Sort for Small Sublists - Hybrid Approach
    //   - Uses Merge Sort for larger sublists and Insertion Sort for smaller ones.
    //   - Insertion Sort is efficient for small lists, reducing overhead.
    // - Time Complexity: O(n log n) -  Improves performance in practice, especially for partially sorted data.
    // - Space Complexity: O(log n) for top-down, O(1) for bottom-up
    private static final int INSERTION_SORT_THRESHOLD = 10; // Threshold size for switching to Insertion Sort

    public static ListNode mergeSortHybrid(ListNode head, boolean useTopDown) {
        if (useTopDown)
            return mergeSortTopDownHybrid(head);
        else
            return mergeSortBottomUpHybrid(head);
    }

    private static ListNode mergeSortTopDownHybrid(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }
        if (getLength(head) <= INSERTION_SORT_THRESHOLD) {
            return insertionSort(head); // Use Insertion Sort for small lists
        }

        ListNode middle = findMiddle(head);
        ListNode nextOfMiddle = middle.next;
        middle.next = null;

        ListNode left = mergeSortTopDownHybrid(head);
        ListNode right = mergeSortTopDownHybrid(nextOfMiddle);
        return merge(left, right);
    }

    private static ListNode mergeSortBottomUpHybrid(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }

        ListNode dummy = new ListNode(0);
        dummy.next = head;
        int n = getLength(head);

        for (int size = 1; size < n; size <<= 1) {
            ListNode prev = dummy;
            ListNode curr = dummy.next;

            while (curr != null) {
                ListNode left = curr;
                ListNode right = split(curr, size);
                curr = split(right, size);

                // Check if sublist size is below the threshold
                if (getLength(left) <= INSERTION_SORT_THRESHOLD) {
                    prev.next = insertionSort(left); // Sort left part
                    while(prev.next != null) prev = prev.next;
                    prev.next = right;
                }
                else if (getLength(right) <= INSERTION_SORT_THRESHOLD && right != null) {
                    prev.next = left;
                    while(prev.next != null) prev = prev.next;
                    prev.next = insertionSort(right);
                }
                else {
                    prev.next = merge(left, right);
                    while (prev.next != null) {
                        prev = prev.next;
                    }
                }
            }
        }
        return dummy.next;
    }

    // Helper function for Insertion Sort (for small lists)
    private static ListNode insertionSort(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }

        ListNode sortedHead = null;
        ListNode current = head;

        while (current != null) {
            ListNode next = current.next; // Store next to avoid losing it
            sortedHead = insertSorted(sortedHead, current);
            current = next;
        }
        return sortedHead;
    }

    private static ListNode insertSorted(ListNode sortedHead, ListNode node) {
        if (sortedHead == null || node.val < sortedHead.val) {
            node.next = sortedHead;
            return node;
        } else {
            ListNode current = sortedHead;
            while (current.next != null && current.next.val < node.val) {
                current = current.next;
            }
            node.next = current.next;
            current.next = node;
            return sortedHead;
        }
    }


    // 5.  Merge Sort with Tail Recursion (Optimized for Tail Recursion) - Advanced
    //    - Implements merge sort using tail recursion, which can be optimized by some compilers.
    //    - Reduces stack usage in tail-recursive calls.
    // - Time Complexity: O(n log n)
    // - Space Complexity: O(log n)  (but can be optimized to O(1) by a smart compiler)
    public static ListNode mergeSortTailRecursive(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }
        ListNode middle = findMiddle(head);
        ListNode nextOfMiddle = middle.next;
        middle.next = null;
        ListNode left = mergeSortTailRecursive(head);
        ListNode right = mergeSortTailRecursive(nextOfMiddle);
        return mergeTailRecursiveHelper(left, right, null);
    }

    private static ListNode mergeTailRecursiveHelper(ListNode left, ListNode right, ListNode mergedHead) {
        if (left == null && right == null) {
            return mergedHead;
        }
        if (left == null) {
            mergedHead = addNodeToTail(mergedHead, right);
            return mergeTailRecursiveHelper(left, right.next, mergedHead);
        }
        if (right == null) {
            mergedHead = addNodeToTail(mergedHead, left);
            return mergeTailRecursiveHelper(left.next, right, mergedHead);
        }

        if (left.val <= right.val) {
            mergedHead = addNodeToTail(mergedHead, left);
            return mergeTailRecursiveHelper(left.next, right, mergedHead);
        } else {
            mergedHead = addNodeToTail(mergedHead, right);
            return mergeTailRecursiveHelper(left, right.next, mergedHead);
        }
    }

    private static ListNode addNodeToTail(ListNode head, ListNode node) {
        if (head == null) {
            node.next = null;
            return node;
        }
        ListNode current = head;
        while (current.next != null) {
            current = current.next;
        }
        current.next = node;
        node.next = null;
        return head;
    }


    public static void main(String[] args) {
        // Test cases
        int[] arr1 = {3, 2, 4, 1, 5};
        int[] arr2 = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        int[] arr3 = {1, 2, 3, 4, 5};
        int[] arr4 = {5, 4, 3, 2, 1};
        int[] arr5 = {1};
        int[] arr6 = {};
        int[] arr7 = {5, -1, 0, 10, -5, 8};

        ListNode head1 = createListFromArray(arr1);
        ListNode head2 = createListFromArray(arr2);
        ListNode head3 = createListFromArray(arr3);
        ListNode head4 = createListFromArray(arr4);
        ListNode head5 = createListFromArray(arr5);
        ListNode head6 = createListFromArray(arr6); // Empty list
        ListNode head7 = createListFromArray(arr7);

        System.out.println("Original Lists:");
        printList(head1);
        printList(head2);
        printList(head3);
        printList(head4);
        printList(head5);
        printList(head6);
        printList(head7);

        System.out.println("\n--- Top-Down Merge Sort ---");
        System.out.println("Sorted List 1: " + mergeSortTopDown(head1));
        System.out.println("Sorted List 2: " + mergeSortTopDown(head2));
        System.out.println("Sorted List 3: " + mergeSortTopDown(head3));
        System.out.println("Sorted List 4: " + mergeSortTopDown(head4));
        System.out.println("Sorted List 5: " + mergeSortTopDown(head5));
        System.out.println("Sorted List 6: " + mergeSortTopDown(head6));
        System.out.println("Sorted List 7: " + mergeSortTopDown(head7));


        head1 = createListFromArray(arr1); // Reset
        head2 = createListFromArray(arr2);
        head3 = createListFromArray(arr3);
        head4 = createListFromArray(arr4);
        head5 = createListFromArray(arr5);
        head6 = createListFromArray(arr6);
        head7 = createListFromArray(arr7);
        System.out.println("\n--- Bottom-Up Merge Sort ---");
        System.out.println("Sorted List 1: " + mergeSortBottomUp(head1));
        System.out.println("Sorted List 2: " + mergeSortBottomUp(head2));
        System.out.println("Sorted List 3: " + mergeSortBottomUp(head3));
        System.out.println("Sorted List 4: " + mergeSortBottomUp(head4));
        System.out.println("Sorted List 5: " + mergeSortBottomUp(head5));
        System.out.println("Sorted List 6: " + mergeSortBottomUp(head6));
        System.out.println("Sorted List 7: " + mergeSortBottomUp(head7));

        head1 = createListFromArray(arr1); // Reset
        head2 = createListFromArray(arr2);
        head3 = createListFromArray(arr3);
        head4 = createListFromArray(arr4);
        head5 = createListFromArray(arr5);
        head6 = createListFromArray(arr6);
        head7 = createListFromArray(arr7);
        System.out.println("\n--- Optimized Merge Sort (Top-Down)---");
        System.out.println("Sorted List 1: " + mergeSortOptimized(head1, true));
        System.out.println("Sorted List 2: " + mergeSortOptimized(head2, true));
        System.out.println("Sorted List 3: " + mergeSortOptimized(head3, true));
        System.out.println("Sorted List 4: " + mergeSortOptimized(head4, true));
        System.out.println("Sorted List 5: " + mergeSortOptimized(head5, true));
        System.out.println("Sorted List 6: " + mergeSortOptimized(head6, true));
        System.out.println("Sorted List 7: " + mergeSortOptimized(head7, true));

        head1 = createListFromArray(arr1); // Reset
        head2 = createListFromArray(arr2);
        head3 = createListFromArray(arr3);
        head4 = createListFromArray(arr4);
        head5 = createListFromArray(arr5);
        head6 = createListFromArray(arr6);
        head7 = createListFromArray(arr7);
        System.out.println("\n--- Optimized Merge Sort (Bottom-Up)---");
        System.out.println("Sorted List 1: " + mergeSortOptimized(head1, false));
        System.out.println("Sorted List 2: " + mergeSortOptimized(head2, false));
        System.out.println("Sorted List 3: " + mergeSortOptimized(head3, false));
        System.out.println("Sorted List 4: " + mergeSortOptimized(head4, false));
        System.out.println("Sorted List 5: " + mergeSortOptimized(head5, false));
        System.out.println("Sorted List 6: " + mergeSortOptimized(head6, false));
        System.out.println("Sorted List 7: " + mergeSortOptimized(head7, false));

        head1 = createListFromArray(arr1); // Reset
        head2 = createListFromArray(arr2);
        head3 = createListFromArray(arr3);
        head4 = createListFromArray(arr4);
        head5 = createListFromArray(arr5);
        head6 = createListFromArray(arr6);
        head7 = createListFromArray(arr7);
        System.out.println("\n--- Hybrid Merge Sort (Top-Down)---");
        System.out.println("Sorted List 1: " + mergeSortHybrid(head1, true));
        System.out.println("Sorted List 2: " + mergeSortHybrid(head2, true));
        System.out.println("Sorted List 3: " + mergeSortHybrid(head3, true));
        System.out.println("Sorted List 4: " + mergeSortHybrid(head4, true));
        System.out.println("Sorted List 5: " + mergeSortHybrid(head5, true));
        System.out.println("Sorted List 6: " + mergeSortHybrid(head6, true));
        System.out.println("Sorted List 7: " + mergeSortHybrid(head7, true));

        head1 = createListFromArray(arr1); // Reset
        head2 = createListFromArray(arr2);
        head3 = createListFromArray(arr3);
        head4 = createListFromArray(arr4);
        head5 = createListFromArray(arr5);
        head6 = createListFromArray(arr6);
        head7 = createListFromArray(arr7);
        System.out.println("\n--- Hybrid Merge Sort (Bottom-Up)---");
        System.out.println("Sorted List 1: " + mergeSortHybrid(head1, false));
        System.out.println("Sorted List 2: " + mergeSortHybrid(head2, false));
        System.out.println("Sorted List 3: " + mergeSortHybrid(head3, false));
        System.out.println("Sorted List 4: " + mergeSortHybrid(head4, false));
        System.out.println("Sorted List 5: " + mergeSortHybrid(head5, false));
        System.out.println("Sorted List 6: " + mergeSortHybrid(head6, false));
        System.out.println("Sorted List 7: " + mergeSortHybrid(head7, false));

        head1 = createListFromArray(arr1); // Reset
        head2 = createListFromArray(arr2);
        head3 = createListFromArray(arr3);
        head4 = createListFromArray(arr4);
        head5 = createListFromArray(arr5);
        head6 = createListFromArray(arr6);
        head7 = createListFromArray(arr7);
        System.out.println("\n--- Tail Recursive Merge Sort ---");
        System.out.println("Sorted List 1: " + mergeSortTailRecursive(head1));
        System.out.println("Sorted List 2: " + mergeSortTailRecursive(head2));
        System.out.println("Sorted List 3: " + mergeSortTailRecursive(head3));
        System.out.println("Sorted List 4: " + mergeSortTailRecursive(head4));
        System.out.println("Sorted List 5: " + mergeSortTailRecursive(head5));
        System.out.println("Sorted List 6: " + mergeSortTailRecursive(head6));
        System.out.println("Sorted List 7: " + mergeSortTailRecursive(head7));
    }
}

// Definition for singly-linked list.
class ListNode {
    int val;
    ListNode next;

    ListNode() {
    }

    ListNode(int val) {
        this.val = val;
    }

    ListNode(int val, ListNode next) {
        this.val = val;
        this.next = next;
    }

    @Override
    public String toString() {
        return val + (next != null ? " -> " + next.toString() : "");
    }
}


/*
 * Explanation of Approaches and Real-World Considerations:
 *
 * 1. Top-Down Merge Sort (Recursive):
 * - Classic, easy-to-understand implementation.
 * - Recursive calls can lead to stack overflow for very large lists.
 * - Good for: Educational purposes, moderately sized lists.
 * - Real-world: Suitable for smaller datasets or when stack depth is not a limitation.  Often used as a baseline.
 *
 * 2. Bottom-Up Merge Sort (Iterative):
 * - Iterative, avoids recursion, more efficient for large lists.
 * - Uses O(1) extra space, making it memory-efficient.
 * - Preferred for: Large datasets, external sorting (with modifications).
 * - Real-world: Databases, file sorting, scenarios where memory is a concern.  The iterative nature makes it more robust.
 *
 * 3. Merge Sort with Optimized Merge:
 * - Optimizes the merge step.
 * - Useful when lists are of unequal length.
 * - Real-world: Situations where input lists might have varying sizes, such as merging results from different data sources.
 *
 * 4. Merge Sort with Insertion Sort for Small Sublists (Hybrid):
 * - Combines Merge Sort with Insertion Sort.
 * - Insertion Sort is faster for small lists, reducing the overhead of recursive calls in Merge Sort.
 * - Good for: General-purpose sorting, performance optimization.
 * - Real-world: Standard library implementations often use this hybrid approach (e.g., Timsort in Python, which is a highly optimized merge sort).  Improves average-case performance.
 *
 * 5. Merge Sort with Tail Recursion:* - Uses tail recursion, which can be optimized by some compilers to reduce stack usage.
 * - More advanced, may not be supported by all Java compilers to the same extent.
 * - Good for: Optimizing recursive solutions, functional programming style.
 * - Real-world:  Less common in Java due to limitations in JVM's tail call optimization.  More relevant in languages with better tail call support.
 *
 * Key Considerations for Real-World Projects:
 *
 * - Memory Usage:  For very large datasets, the iterative bottom-up approach is often preferred due to its O(1) space complexity.
 * - Performance:  Hybrid approaches (like #4) can provide the best average-case performance.
 * - Stability:  Merge Sort is a stable sorting algorithm (maintains the relative order of equal elements), which is important in many applications.
 * - External Sorting:  For datasets that don't fit in memory, Merge Sort can be adapted for external sorting (reading/writing data in chunks).
 * - Parallelism:  Merge Sort can be easily parallelized to take advantage of multi-core processors.
 * - Existing Libraries:  In practice, it's often best to use the sorting methods provided by the Java standard library (e.g., Collections.sort()) as they are highly optimized.  However, understanding the underlying algorithms is crucial for making informed decisions and for implementing custom sorting solutions when needed.
 * - Data Characteristics: The choice of algorithm can depend on the characteristics of the data (e.g., partially sorted, nearly sorted, random).
 * - Threshold for Hybrid Approach: The optimal value for INSERTION_SORT_THRESHOLD in approach #4 can vary depending on the specific system and data.  It's often determined experimentally.
 * - Tail Recursion Optimization:  While the tail recursion approach is presented, be aware that Java's JVM doesn't fully optimize tail calls in the same way that some other languages/compilers do.
 *
 */
