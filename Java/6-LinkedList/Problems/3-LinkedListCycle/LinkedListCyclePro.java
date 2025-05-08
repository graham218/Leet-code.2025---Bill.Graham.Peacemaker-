import java.util.HashSet;
import java.util.Set;

/**
 * This class provides multiple solutions to detect a cycle in a linked list.
 * Each approach is commented with its real-world application scenario and time/space complexity.
 */
public class LinkedListCycleDetector {

    // Definition for singly-linked list node
    static class ListNode {
        int val;
        ListNode next;
        ListNode(int x) {
            val = x;
            next = null;
        }
    }

    /**
     * Solution 1: Hash Table Approach
     * Real-world use: Ideal for scenarios where you need to track visited nodes for other purposes
     * (like debugging or analytics) while detecting cycles.
     *
     * Time Complexity: O(n) - We visit each node exactly once
     * Space Complexity: O(n) - We store each node in the hash set
     */
    public static boolean hasCycleHashTable(ListNode head) {
        // Create a set to store visited nodes
        Set<ListNode> visitedNodes = new HashSet<>();

        // Traverse the list
        ListNode current = head;
        while (current != null) {
            // If we've seen this node before, there's a cycle
            if (visitedNodes.contains(current)) {
                return true;
            }
            // Add current node to the set
            visitedNodes.add(current);
            // Move to next node
            current = current.next;
        }

        // If we reach null, no cycle found
        return false;
    }

    /**
     * Solution 2: Floyd's Tortoise and Hare (Two Pointers)
     * Real-world use: Most efficient for memory-constrained environments as it uses O(1) space.
     * Commonly used in production systems for cycle detection.
     *
     * Time Complexity: O(n) - Linear time
     * Space Complexity: O(1) - Constant space
     */
    public static boolean hasCycleTwoPointers(ListNode head) {
        if (head == null || head.next == null) {
            return false;
        }

        // Initialize slow and fast pointers
        ListNode slow = head;
        ListNode fast = head.next;

        while (slow != fast) {
            // If fast reaches the end, no cycle
            if (fast == null || fast.next == null) {
                return false;
            }
            // Move slow by 1 and fast by 2
            slow = slow.next;
            fast = fast.next.next;
        }

        // If slow and fast meet, cycle exists
        return true;
    }

    /**
     * Solution 3: Marking Visited Nodes (Destructive)
     * Real-world use: Useful in temporary debugging scenarios where you can modify the list structure
     * and don't need to preserve the original list.
     *
     * Time Complexity: O(n) - Linear time
     * Space Complexity: O(1) - Constant space, but modifies the original list
     */
    public static boolean hasCycleMarking(ListNode head) {
        // Traverse the list
        ListNode current = head;
        while (current != null) {
            // If we find a marked node, cycle exists
            if (current.val == Integer.MIN_VALUE) {
                return true;
            }
            // Mark the current node by changing its value
            current.val = Integer.MIN_VALUE;
            // Move to next node
            current = current.next;
        }

        // No marked nodes found, no cycle
        return false;
    }

    /**
     * Solution 4: Reverse List Approach
     * Real-world use: Useful when you need to both detect cycles and potentially reverse the list
     * if no cycle exists. More of a academic approach than production code.
     *
     * Time Complexity: O(n) - Linear time
     * Space Complexity: O(1) - Constant space
     */
    public static boolean hasCycleReverseList(ListNode head) {
        if (head == null || head.next == null) {
            return false;
        }

        ListNode reversed = null;
        ListNode current = head;
        ListNode next;

        try {
            while (current != null) {
                // Store next node
                next = current.next;
                // Reverse the link
                current.next = reversed;
                // Move pointers
                reversed = current;
                current = next;

                // If we reach head again, cycle exists
                if (current == head) {
                    return true;
                }
            }
        } finally {
            // In a real implementation, you might want to restore the list
            // This is omitted here for simplicity
        }

        // If we successfully reversed the whole list, no cycle
        return false;
    }

    /**
     * Solution 5: Using a Temp Node
     * Real-world use: Useful when you can't modify node values (like in readonly systems)
     * but can temporarily modify pointers. Less destructive than Solution 3.
     *
     * Time Complexity: O(n) - Linear time
     * Space Complexity: O(1) - Constant space
     */
    public static boolean hasCycleTempNode(ListNode head) {
        // Create a temporary node
        ListNode temp = new ListNode(0);

        ListNode current = head;
        while (current != null) {
            // If we find a node pointing to temp, cycle exists
            if (current.next == temp) {
                return true;
            }

            // Store next node
            ListNode next = current.next;
            // Point current node to temp
            current.next = temp;
            // Move to next node
            current = next;
        }

        // No cycles found
        return false;
    }

    // Helper method to create a linked list with cycle for testing
    public static ListNode createLinkedListWithCycle(int[] values, int pos) {
        if (values == null || values.length == 0) {
            return null;
        }

        ListNode[] nodes = new ListNode[values.length];
        ListNode head = new ListNode(values[0]);
        nodes[0] = head;

        for (int i = 1; i < values.length; i++) {
            nodes[i] = new ListNode(values[i]);
            nodes[i-1].next = nodes[i];
        }

        if (pos >= 0 && pos < values.length) {
            nodes[values.length-1].next = nodes[pos];
        }

        return head;
    }

    // Test cases
    public static void main(String[] args) {
        // Test case 1: No cycle
        ListNode list1 = createLinkedListWithCycle(new int[]{1, 2, 3, 4}, -1);
        System.out.println("Test Case 1 (No cycle):");
        System.out.println("Hash Table: " + hasCycleHashTable(list1));
        System.out.println("Two Pointers: " + hasCycleTwoPointers(list1));
        System.out.println("Marking: " + hasCycleMarking(createLinkedListWithCycle(new int[]{1, 2, 3, 4}, -1)));
        System.out.println("Reverse List: " + hasCycleReverseList(createLinkedListWithCycle(new int[]{1, 2, 3, 4}, -1)));
        System.out.println("Temp Node: " + hasCycleTempNode(createLinkedListWithCycle(new int[]{1, 2, 3, 4}, -1)));

        // Test case 2: Has cycle
        ListNode list2 = createLinkedListWithCycle(new int[]{1, 2, 3, 4}, 1);
        System.out.println("\nTest Case 2 (Has cycle):");
        System.out.println("Hash Table: " + hasCycleHashTable(list2));
        System.out.println("Two Pointers: " + hasCycleTwoPointers(list2));
        System.out.println("Marking: " + hasCycleMarking(createLinkedListWithCycle(new int[]{1, 2, 3, 4}, 1)));
        System.out.println("Reverse List: " + hasCycleReverseList(createLinkedListWithCycle(new int[]{1, 2, 3, 4}, 1)));
        System.out.println("Temp Node: " + hasCycleTempNode(createLinkedListWithCycle(new int[]{1, 2, 3, 4}, 1)));
    }
}