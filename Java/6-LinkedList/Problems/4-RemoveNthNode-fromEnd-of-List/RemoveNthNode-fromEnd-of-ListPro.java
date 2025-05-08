/**
 * Definition for singly-linked list.
 * public class ListNode {
 * int val;
 * ListNode next;
 * ListNode() {}
 * ListNode(int val) { this.val = val; }
 * ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
import java.util.Stack;

class Solution {

    /**
     * Approach 1: Two Pass Solution
     *
     * This is the most straightforward approach.  It involves two passes through the linked list.
     *
     * 1.  First Pass: Calculate the length of the linked list.
     * 2.  Second Pass:  Traverse to the (length - n)th node and remove the nth node from the end.
     *
     * Time Complexity: O(L), where L is the length of the list.
     * Space Complexity: O(1), constant space.
     *
     * Real-world application:  Useful in scenarios where you need to know the size of a list
     * before performing operations, such as in database query processing
     * where you might need to know the number of results before displaying
     * them in a paginated format.
     */
    public ListNode removeNthFromEnd(ListNode head, int n) {
        if (head == null) return null;

        int length = 0;
        ListNode current = head;

        // First pass: Calculate the length of the linked list
        while (current != null) {
            length++;
            current = current.next;
        }

        // Handle the case where we need to remove the head node
        if (n > length) { // n can't be greater than length
            return null; // Or throw an exception:  throw new IllegalArgumentException("n is greater than the list length");
        }
        if (n == length) {
            return head.next;
        }

        // Second pass: Traverse to the (length - n)th node
        current = head;
        for (int i = 1; i < length - n; i++) {
            current = current.next;
        }

        // Remove the nth node from the end
        current.next = current.next.next;

        return head;
    }



    /**
     * Approach 2: Two Pointers (Fast and Slow)
     *
     * This approach uses two pointers, often called 'fast' and 'slow'.
     *
     * 1.  Move the 'fast' pointer n nodes ahead of the 'slow' pointer.
     * 2.  Move both pointers simultaneously until the 'fast' pointer reaches the end.
     * 3.  When the 'fast' pointer reaches the end, the 'slow' pointer will be at the node just before
     * the node to be deleted.
     *
     * Time Complexity: O(L), where L is the length of the list.
     * Space Complexity: O(1), constant space.
     *
     * Real-world application:  Efficiently finding elements at a specific offset from the end
     * is useful in network protocols, where you might need to process
     * packets or data streams with a certain offset.
     */
    public ListNode removeNthFromEndTwoPointers(ListNode head, int n) {
        if (head == null) return null;

        ListNode dummy = new ListNode(0); // Use a dummy node to handle the case where the head needs to be removed.
        dummy.next = head;
        ListNode fast = dummy;
        ListNode slow = dummy;

        // Move the 'fast' pointer n nodes ahead
        for (int i = 0; i < n; i++) {
            if (fast == null) { // Handle cases where n is larger than the list.
                return null; // Or throw an exception
            }
            fast = fast.next;
        }

        // Move both pointers until the 'fast' pointer reaches the end
        while (fast.next != null) {
            fast = fast.next;
            slow = slow.next;
        }

        // Remove the nth node from the end
        slow.next = slow.next.next;

        return dummy.next;
    }

    /**
     * Approach 3: Using Stack
     *
     * This approach uses a stack to store the nodes of the linked list.
     *
     * 1.  Traverse the linked list and push each node onto the stack.
     * 2.  Pop n nodes from the stack.
     * 3.  The node at the top of the stack is the node before the one to be deleted.
     *
     * Time Complexity: O(L), where L is the length of the list.
     * Space Complexity: O(L), space used by the stack.
     *
     * Real-world application:  Stacks are commonly used in undo/redo functionality in text editors
     * or other applications.  This approach could be adapted to manage
     * a history of changes in a linked list-based data structure.
     */
    public ListNode removeNthFromEndStack(ListNode head, int n) {
        if (head == null) return null;

        Stack<ListNode> stack = new Stack<>();
        ListNode current = head;

        // Push all nodes onto the stack
        while (current != null) {
            stack.push(current);
            current = current.next;
        }

        // Pop n nodes
        for (int i = 0; i < n; i++) {
            if (stack.isEmpty()) return null; // Handle cases where n is larger than list
            stack.pop();
        }

        // Handle the case where the head node needs to be removed
        if (stack.isEmpty()) {
            return head.next;
        }

        // Remove the nth node from the end
        ListNode prev = stack.peek();
        prev.next = prev.next.next;

        return head;
    }

    /**
     * Approach 4:  Recursion
     *
     * This approach uses recursion.
     *
     * 1.  The recursive function calculates the length of the list as it goes down the list.
     * 2.  When the recursion reaches the end of the list, it starts returning values back up the call stack.
     * 3.  When the return value equals n, we remove the node.
     *
     * Time Complexity: O(L), where L is the length of the list.
     * Space Complexity: O(L),  due to the recursion stack.
     *
     * Real-world application: Recursion is used in many algorithms, such as tree traversals
     * and graph searching.  While not always the most efficient for linked lists,
     * this demonstrates a different problem-solving approach.
     */
    private int removeNthFromEndRecursiveHelper(ListNode node, int n) {
        if (node == null) {
            return 0;
        }

        int length = removeNthFromEndRecursiveHelper(node.next, n) + 1;

        if (length == n + 1) { // Corrected condition.  We want to modify the node *before* the nth from the end.
            node.next = node.next.next; // Remove the nth node.
        }

        return length;
    }

    public ListNode removeNthFromEndRecursive(ListNode head, int n) {
        if (head == null) return null;
        // Create a dummy node to handle the case where the head needs to be removed.
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        removeNthFromEndRecursiveHelper(dummy, n);
        return dummy.next;
    }


    /**
     * Approach 5: Optimized Two Pointers (Single Pass)
     *
     * This approach is a refined version of the two-pointer approach.  It aims to be more concise.
     *
     * 1.  Initialize two pointers, `fast` and `slow`, both pointing to a dummy node before the head.
     * 2.  Move `fast` pointer `n` steps forward.
     * 3.  Move both `fast` and `slow` pointers forward until `fast` reaches the end of the list.
     * 4.  At this point, `slow` will be pointing to the node *before* the node to be removed.
     * 5.  Update `slow.next` to skip the node to be removed.
     * 6.  Return the `next` of the dummy node (which is the head of the modified list).
     *
     * Time Complexity: O(L), where L is the length of the linked list.
     * Space Complexity: O(1), constant space.
     *
     * Real-world application: This optimized approach is suitable for performance-critical
     * applications where minimizing the number of iterations is crucial,
     * such as processing large lists in real-time systems.
     */
    public ListNode removeNthFromEndOptimized(ListNode head, int n) {
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        ListNode fast = dummy;
        ListNode slow = dummy;

        // Move fast pointer n steps ahead
        for (int i = 0; i < n; i++) {
            fast = fast.next;
        }

        // Move both pointers until fast reaches the end
        while (fast.next != null) {
            fast = fast.next;
            slow = slow.next;
        }

        // Remove the nth node from the end
        slow.next = slow.next.next;

        return dummy.next;
    }


    // ListNode class (Definition for singly-linked list)
    public static class ListNode {
        int val;
        ListNode next;
        ListNode() {}
        ListNode(int val) { this.val = val; }
        ListNode(int val, ListNode next) { this.val = val; this.next = next; }
    }

    // Main method for testing
    public static void main(String[] args) {
        // Create a sample linked list: 1 -> 2 -> 3 -> 4 -> 5
        ListNode head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(3);
        head.next.next.next = new ListNode(4);
        head.next.next.next.next = new ListNode(5);

        int n = 2; // Remove the 2nd node from the end (which is 4)

        Solution solution = new Solution();

        // Test Approach 1: Two Pass
        ListNode result1 = solution.removeNthFromEnd(copyList(head), n); // Pass a copy to avoid modifying the original
        System.out.print("Two Pass: ");
        printList(result1); // Expected output: 1 -> 2 -> 3 -> 5

        // Test Approach 2: Two Pointers
        ListNode result2 = solution.removeNthFromEndTwoPointers(copyList(head), n);
        System.out.print("Two Pointers: ");
        printList(result2); // Expected output: 1 -> 2 -> 3 -> 5

        // Test Approach 3: Stack
        ListNode result3 = solution.removeNthFromEndStack(copyList(head), n);
        System.out.print("Stack: ");
        printList(result3); // Expected output: 1 -> 2 -> 3 -> 5

        // Test Approach 4: Recursion
        ListNode result4 = solution.removeNthFromEndRecursive(copyList(head), n);
        System.out.print("Recursion: ");
        printList(result4); // Expected output: 1 -> 2 -> 3 -> 5

        // Test Approach 5: Optimized Two Pointers
        ListNode result5 = solution.removeNthFromEndOptimized(copyList(head), n);
        System.out.print("Optimized Two Pointers: ");
        printList(result5); // Expected output: 1 -> 2 -> 3 -> 5
    }

    // Helper method to print the linked list
    public static void printList(ListNode head) {
        ListNode current = head;
        while (current != null) {
            System.out.print(current.val + " -> ");
            current = current.next;
        }
        System.out.println("null");
    }

    // Helper method to create a copy of the linked list.  Important for testing!
    public static ListNode copyList(ListNode head) {
        if (head == null) return null;
        ListNode newHead = new ListNode(head.val);
        ListNode current = head.next;
        ListNode copyCurrent = newHead;

        while (current != null) {
            ListNode newNode = new ListNode(current.val);
            copyCurrent.next = newNode;
            copyCurrent = newNode;
            current = current.next;
        }
        return newHead;
    }
}

