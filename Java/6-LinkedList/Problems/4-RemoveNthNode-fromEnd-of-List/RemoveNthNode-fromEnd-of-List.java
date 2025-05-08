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
class Solution {

    /**
     * Approach 1: Two Pass
     * - Calculate the length of the linked list in the first pass.
     * - Calculate the node to remove (nThFromStart) from the beginning in the second pass.
     * - Remove the node.
     *
     * Time Complexity: O(L) where L is the length of the list.
     * Space Complexity: O(1)
     */
    public ListNode removeNthFromEnd(ListNode head, int n) {
        if (head == null) return null;

        int length = 0;
        ListNode current = head;

        // First pass: Calculate the length of the list
        while (current != null) {
            length++;
            current = current.next;
        }

        // Handle the case where we need to remove the head node
        if (n > length) { // n can't be greater than length
            return null; // Or throw an exception: throw new IllegalArgumentException("n is greater than the list length");
        }
        if (n == length) {
            return head.next;
        }

        int nThFromStart = length - n; // Index of the node to remove from the start
        current = head;
        for (int i = 1; i < nThFromStart; i++) {
            current = current.next;
        }
        current.next = current.next.next; // Remove the node
        return head;
    }

    /**
     * Approach 2: Two Pointers (Fast and Slow) - Optimized
     * - Move the fast pointer n nodes ahead of the slow pointer.
     * - Move both pointers until the fast pointer reaches the end.
     * - The slow pointer will be pointing to the node before the one to be deleted.
     * - Delete the node.
     *
     * Time Complexity: O(L) where L is the length of the list.
     * Space Complexity: O(1)
     */
    public ListNode removeNthFromEnd2(ListNode head, int n) {
        if (head == null) return null;

        ListNode dummy = new ListNode(0); // Dummy node to handle the case of removing the head
        dummy.next = head;
        ListNode fast = dummy;
        ListNode slow = dummy;

        // Move fast pointer n steps ahead
        for (int i = 0; i < n; i++) {
            if (fast == null) { // Handle cases where n is larger than the list
                return null; // Or throw an exception
            }
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

    /**
     * Approach 3: Recursive Approach
     * - Recursively go to the end of the list.
     * - Keep a counter. When the counter equals n, remove the node.
     * - This approach uses a helper function.
     *
     * Time Complexity: O(L) where L is the length of the list.
     * Space Complexity: O(L) due to the recursive call stack.
     */
    private int recursiveRemove(ListNode node, int n, ListNode[] nextNode) {
        if (node == null) {
            return 0;
        }
        int count = recursiveRemove(node.next, n, nextNode) + 1;
        if (count == n) {
            nextNode[0] = node.next; // Store the next node to be used by the previous call.
        }
        else if (nextNode[0] != null){
            node.next = nextNode[0];
        }
        return count;
    }

    public ListNode removeNthFromEnd3(ListNode head, int n) {
        ListNode[] nextNode = new ListNode[1]; // Array to simulate pass-by-reference for the next node.
        int count = recursiveRemove(head, n, nextNode);
        if (count == n) {
            return head.next;
        }
        return head;
    }


    /**
     * Approach 4: Using a Stack
     * - Push all nodes into a Stack.
     * - Pop n nodes from the stack.
     * - The top of the stack is the node before the one to be deleted.
     * - Delete the node.
     *
     * Time Complexity: O(L) where L is the length of the list.
     * Space Complexity: O(L) for the stack.
     */
    public ListNode removeNthFromEnd4(ListNode head, int n) {
        if (head == null) return null;

        java.util.Stack<ListNode> stack = new java.util.Stack<>();
        ListNode current = head;

        while (current != null) {
            stack.push(current);
            current = current.next;
        }

        // Handle cases where n is invalid
        if (n <= 0 || n > stack.size()) {
            return head; // Or throw an exception
        }
        for (int i = 0; i < n; i++) {
            stack.pop();
        }

        if (stack.isEmpty()) {
            return head.next; // Removing the head
        } else {
            ListNode prevNode = stack.peek();
            prevNode.next = prevNode.next.next;
            return head;
        }
    }

    /**
     * Approach 5:  Dummy Node and Two Pointers (Similar to Approach 2, but with more explicit comments)
     * - Create a dummy node to handle edge cases, like removing the head.
     * - Use two pointers, `fast` and `slow`.
     * - Move `fast` n steps ahead.
     * - Move both pointers until `fast` reaches the end.
     * - `slow` will be pointing to the node *before* the nth node from the end.
     * - Relink the pointers to remove the nth node.
     *
     * Time Complexity: O(L), where L is the length of the linked list.
     * Space Complexity: O(1)
     */
    public ListNode removeNthFromEnd5(ListNode head, int n) {
        // Handle edge case: empty list
        if (head == null) {
            return null;
        }

        // Create a dummy node to simplify handling the head of the list
        ListNode dummy = new ListNode(0);
        dummy.next = head;

        // Initialize two pointers, `fast` and `slow`, both starting at the dummy node
        ListNode fast = dummy;
        ListNode slow = dummy;

        // Move the `fast` pointer n steps ahead
        for (int i = 0; i < n; i++) {
            // Handle the case where n is greater than the length of the list
            if (fast == null) {
                return null; // Or throw an exception:  throw new IllegalArgumentException("n is out of bounds");
            }
            fast = fast.next;
        }

        // Move both pointers until the `fast` pointer reaches the end of the list
        while (fast.next != null) {
            fast = fast.next;
            slow = slow.next;
        }

        // `slow` is now pointing to the node *before* the nth node from the end
        // Remove the nth node from the end by updating the `next` pointer of `slow`
        slow.next = slow.next.next;

        // Return the head of the modified list (which is dummy.next)
        return dummy.next;
    }



    // ListNode Class (Inner Class)
    public static class ListNode {
        int val;
        ListNode next;
        ListNode() {}
        ListNode(int val) { this.val = val; }
        ListNode(int val, ListNode next) { this.val = val; this.next = next; }
    }

    public static void main(String[] args) {
        // Create a sample linked list: 1 -> 2 -> 3 -> 4 -> 5
        ListNode head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(3);
        head.next.next.next = new ListNode(4);
        head.next.next.next.next = new ListNode(5);

        int n = 2; // Remove the 2nd node from the end (which is 4)

        Solution solution = new Solution();

        // Test with different approaches:
        // Approach 1
        ListNode result1 = solution.removeNthFromEnd(head, n);
        System.out.print("Result 1: ");
        printLinkedList(result1); // Expected output: 1 -> 2 -> 3 -> 5

        // Reset the linked list
        head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(3);
        head.next.next.next = new ListNode(4);
        head.next.next.next.next = new ListNode(5);
        // Approach 2
        ListNode result2 = solution.removeNthFromEnd2(head, n);
        System.out.print("Result 2: ");
        printLinkedList(result2);

        // Reset the linked list
        head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(3);
        head.next.next.next = new ListNode(4);
        head.next.next.next.next = new ListNode(5);
        // Approach 3
        ListNode result3 = solution.removeNthFromEnd3(head, n);
        System.out.print("Result 3: ");
        printLinkedList(result3);

        // Reset the linked list
        head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(3);
        head.next.next.next = new ListNode(4);
        head.next.next.next.next = new ListNode(5);
        // Approach 4
        ListNode result4 = solution.removeNthFromEnd4(head, n);
        System.out.print("Result 4: ");
        printLinkedList(result4);

        // Reset the linked list
        head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(3);
        head.next.next.next = new ListNode(4);
        head.next.next.next.next = new ListNode(5);
        // Approach 5
        ListNode result5 = solution.removeNthFromEnd5(head, n);
        System.out.print("Result 5: ");
        printLinkedList(result5);
    }

    // Helper method to print the linked list
    public static void printLinkedList(ListNode head) {
        ListNode current = head;
        while (current != null) {
            System.out.print(current.val + " -> ");
            current = current.next;
        }
        System.out.println("null");
    }
}

