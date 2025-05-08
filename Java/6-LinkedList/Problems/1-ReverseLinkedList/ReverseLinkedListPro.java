/**
 * This class demonstrates 5 different approaches to reverse a linked list in Java.
 * Each approach is commented with explanations and real-world applicability.
 */
public class ReverseLinkedList {

    // Definition for singly-linked list node
    static class ListNode {
        int val;
        ListNode next;
        ListNode(int x) { val = x; }
    }

    /**
     * Approach 1: Iterative Approach (Standard)
     *
     * This is the most common approach used in production code for its:
     * - O(n) time complexity
     * - O(1) space complexity
     * - Easy to understand and maintain
     *
     * Real-world use: Most production codebases use this approach when
     * a simple in-place reversal is needed.
     */
    public static ListNode reverseIterative(ListNode head) {
        ListNode prev = null;
        ListNode current = head;
        ListNode next = null;

        while (current != null) {
            // Store the next node before we overwrite current.next
            next = current.next;

            // Reverse the current node's pointer
            current.next = prev;

            // Move pointers one position ahead
            prev = current;
            current = next;
        }

        // Prev is now the new head
        return prev;
    }

    /**
     * Approach 2: Recursive Approach
     *
     * This approach is elegant but has O(n) space complexity due to call stack.
     * Useful in functional programming contexts or when stack depth isn't a concern.
     *
     * Real-world use: Often used in functional programming style codebases
     * or when writing clean recursive solutions is preferred.
     */
    public static ListNode reverseRecursive(ListNode head) {
        // Base case: empty list or single node
        if (head == null || head.next == null) {
            return head;
        }

        // Reverse the rest of the list recursively
        ListNode reversedList = reverseRecursive(head.next);

        // Put the current node at the end of the reversed list
        head.next.next = head;
        head.next = null;

        return reversedList;
    }

    /**
     * Approach 3: Using Stack
     *
     * This approach uses extra O(n) space for the stack but demonstrates
     * how auxiliary data structures can be used for reversal.
     *
     * Real-world use: Useful in scenarios where you need to process nodes
     * in reverse order anyway (like when you need to access them twice).
     */
    public static ListNode reverseUsingStack(ListNode head) {
        if (head == null) return null;

        java.util.Deque<ListNode> stack = new java.util.ArrayDeque<>();
        ListNode current = head;

        // Push all nodes onto stack
        while (current != null) {
            stack.push(current);
            current = current.next;
        }

        // The new head is the top of the stack
        ListNode newHead = stack.pop();
        current = newHead;

        // Pop nodes from stack and link them
        while (!stack.isEmpty()) {
            current.next = stack.pop();
            current = current.next;
        }

        // Important: set the last node's next to null
        current.next = null;

        return newHead;
    }

    /**
     * Approach 4: In-place Reversal with Tail Recursion
     *
     * A tail-recursive version that some compilers can optimize to avoid stack overflow.
     * More efficient than regular recursion in languages that support tail call optimization.
     *
     * Real-world use: Used in performance-sensitive recursive implementations,
     * especially in functional languages or when tail call optimization is available.
     */
    public static ListNode reverseTailRecursive(ListNode head) {
        return reverseTailRecursiveHelper(head, null);
    }

    private static ListNode reverseTailRecursiveHelper(ListNode current, ListNode prev) {
        // Base case: end of list
        if (current == null) {
            return prev;
        }

        // Save next node before we overwrite current.next
        ListNode next = current.next;

        // Reverse the current node
        current.next = prev;

        // Tail recursive call
        return reverseTailRecursiveHelper(next, current);
    }

    /**
     * Approach 5: Using List/Array Conversion (Not In-place)
     *
     * This approach converts the list to an array first, then rebuilds it in reverse.
     * While not space efficient (O(n) space), it demonstrates an alternative approach.
     *
     * Real-world use: Useful when you need both the original and reversed lists,
     * or when working with systems that prefer array operations.
     */
    public static ListNode reverseUsingArray(ListNode head) {
        if (head == null) return null;

        // Count the number of nodes
        int count = 0;
        ListNode current = head;
        while (current != null) {
            count++;
            current = current.next;
        }

        // Store node values in an array
        int[] values = new int[count];
        current = head;
        for (int i = 0; i < count; i++) {
            values[i] = current.val;
            current = current.next;
        }

        // Build the reversed list from the array
        ListNode newHead = new ListNode(values[count - 1]);
        current = newHead;
        for (int i = count - 2; i >= 0; i--) {
            current.next = new ListNode(values[i]);
            current = current.next;
        }

        return newHead;
    }

    // Utility method to print the linked list
    public static void printList(ListNode head) {
        ListNode current = head;
        while (current != null) {
            System.out.print(current.val + " ");
            current = current.next;
        }
        System.out.println();
    }

    // Main method to test all approaches
    public static void main(String[] args) {
        // Create a sample linked list: 1 -> 2 -> 3 -> 4 -> 5
        ListNode head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(3);
        head.next.next.next = new ListNode(4);
        head.next.next.next.next = new ListNode(5);

        System.out.println("Original list:");
        printList(head);

        // Test all approaches
        System.out.println("\nReversed using iterative approach:");
        printList(reverseIterative(head));

        // Rebuild the list for next test
        head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(3);
        head.next.next.next = new ListNode(4);
        head.next.next.next.next = new ListNode(5);

        System.out.println("\nReversed using recursive approach:");
        printList(reverseRecursive(head));

        // Rebuild the list for next test
        head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(3);
        head.next.next.next = new ListNode(4);
        head.next.next.next.next = new ListNode(5);

        System.out.println("\nReversed using stack approach:");
        printList(reverseUsingStack(head));

        // Rebuild the list for next test
        head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(3);
        head.next.next.next = new ListNode(4);
        head.next.next.next.next = new ListNode(5);

        System.out.println("\nReversed using tail recursive approach:");
        printList(reverseTailRecursive(head));

        // Rebuild the list for next test
        head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(3);
        head.next.next.next = new ListNode(4);
        head.next.next.next.next = new ListNode(5);

        System.out.println("\nReversed using array conversion approach:");
        printList(reverseUsingArray(head));
    }
}