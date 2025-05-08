public class ReverseLinkedList {

    // Definition for singly-linked list.
    static class ListNode {
        int val;
        ListNode next;

        ListNode(int val) {
            this.val = val;
        }
    }

    // Approach 1: Iterative using 3 pointers
    public static ListNode reverseIterative(ListNode head) {
        ListNode prev = null;
        ListNode curr = head;

        while (curr != null) {
            ListNode nextTemp = curr.next; // Store next node
            curr.next = prev;              // Reverse the link
            prev = curr;                   // Move prev forward
            curr = nextTemp;               // Move curr forward
        }
        return prev; // New head of reversed list
    }

    // Approach 2: Recursive
    public static ListNode reverseRecursive(ListNode head) {
        // Base case: if head is null or one node, it's reversed already
        if (head == null || head.next == null) {
            return head;
        }
        // Recursively reverse the rest
        ListNode newHead = reverseRecursive(head.next);
        head.next.next = head; // Put current head after its next
        head.next = null;      // Set current node's next to null
        return newHead;
    }

    // Approach 3: Using a stack
    public static ListNode reverseWithStack(ListNode head) {
        java.util.Stack<ListNode> stack = new java.util.Stack<>();
        ListNode current = head;
        while (current != null) {
            stack.push(current);
            current = current.next;
        }
        if (stack.isEmpty()) return null;

        ListNode newHead = stack.pop();
        ListNode temp = newHead;
        while (!stack.isEmpty()) {
            temp.next = stack.pop();
            temp = temp.next;
        }
        temp.next = null; // Last node should point to null
        return newHead;
    }

    // Approach 4: Reverse by inserting nodes at the beginning of a new list
    public static ListNode reverseInsertFront(ListNode head) {
        ListNode newHead = null;
        while (head != null) {
            ListNode next = head.next;
            head.next = newHead; // Insert current node at new head
            newHead = head;
            head = next;
        }
        return newHead;
    }

    // Approach 5: Tail-recursive style (requires helper method)
    public static ListNode reverseTailRecursive(ListNode head) {
        return reverseTailHelper(head, null);
    }

    private static ListNode reverseTailHelper(ListNode current, ListNode prev) {
        if (current == null) return prev;
        ListNode next = current.next;
        current.next = prev;
        return reverseTailHelper(next, current);
    }

    // Helper to print linked list
    public static void printList(ListNode head) {
        while (head != null) {
            System.out.print(head.val + " -> ");
            head = head.next;
        }
        System.out.println("null");
    }

    // Main method for testing
    public static void main(String[] args) {
        // Creating sample list: 1 -> 2 -> 3 -> 4 -> 5 -> null
        ListNode head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(3);
        head.next.next.next = new ListNode(4);
        head.next.next.next.next = new ListNode(5);

        System.out.println("Original list:");
        printList(head);

        System.out.println("Reversed list (Iterative):");
        printList(reverseIterative(head));

        // You can rebuild the list and test other methods similarly
    }
}
