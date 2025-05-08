import java.util.HashSet;
import java.util.Set;
import java.util.Stack;

public class LinkedListCycle {

    // Definition of a singly linked list node.
    static class ListNode {
        int val;
        ListNode next;

        ListNode(int x) {
            val = x;
            next = null;
        }
    }

    public static void main(String[] args) {
        // Create a sample linked list with a cycle for testing.
        ListNode head = new ListNode(1);
        ListNode node2 = new ListNode(2);
        ListNode node3 = new ListNode(3);
        ListNode node4 = new ListNode(4);
        ListNode node5 = new ListNode(5);

        head.next = node2;
        node2.next = node3;
        node3.next = node4;
        node4.next = node5;
        node5.next = node2; // Creating a cycle: node5 points back to node2.

        // Test the different cycle detection methods.
        System.out.println("Using HashSet: Cycle detected? " + hasCycleUsingHashSet(head)); // Expected: true
        System.out.println("Using Floyd's Tortoise and Hare: Cycle detected? " + hasCycleUsingFloyd(head)); // Expected: true
        System.out.println("Using Stack: Cycle detected? " + hasCycleUsingStack(head)); //Expected: true
        System.out.println("Using Visited Flag: Cycle detected? " + hasCycleUsingVisitedFlag(head)); //Expected: true
        System.out.println("Using Length Comparison: Cycle detected? " + hasCycleUsingLengthComparison(head)); //Expected: true

        // Create a sample linked list without a cycle
        ListNode head2 = new ListNode(1);
        ListNode node6 = new ListNode(2);
        ListNode node7 = new ListNode(3);
        head2.next = node6;
        node6.next = node7;

        System.out.println("Using HashSet: Cycle detected? " + hasCycleUsingHashSet(head2)); // Expected: false
        System.out.println("Using Floyd's Tortoise and Hare: Cycle detected? " + hasCycleUsingFloyd(head2)); // Expected: false
        System.out.println("Using Stack: Cycle detected? " + hasCycleUsingStack(head2)); //Expected: false
        System.out.println("Using Visited Flag: Cycle detected? " + hasCycleUsingVisitedFlag(head2)); //Expected: false
        System.out.println("Using Length Comparison: Cycle detected? " + hasCycleUsingLengthComparison(head2)); //Expected: false
    }

    // 1. Using HashSet
    // Time Complexity: O(n), Space Complexity: O(n)
    // Description: This method uses a HashSet to keep track of visited nodes.  If a node is visited again,
    //              it means there is a cycle.
    public static boolean hasCycleUsingHashSet(ListNode head) {
        if (head == null) {
            return false;
        }
        Set<ListNode> visitedNodes = new HashSet<>();
        ListNode current = head;
        while (current != null) {
            if (visitedNodes.contains(current)) {
                return true; // Cycle detected: current node has been visited before.
            }
            visitedNodes.add(current); // Add the current node to the visited set.
            current = current.next;     // Move to the next node.
        }
        return false; // No cycle found: the list ends without repeating a node.
    }

    // 2. Floyd's Tortoise and Hare (Fast and Slow Pointer)
    // Time Complexity: O(n), Space Complexity: O(1)
    // Description: This is the most efficient method. It uses two pointers, one moving slowly (tortoise) and the other
    //              moving faster (hare). If there is a cycle, the two pointers will eventually meet.
    public static boolean hasCycleUsingFloyd(ListNode head) {
        if (head == null) {
            return false;
        }
        ListNode slow = head;
        ListNode fast = head;
        while (fast != null && fast.next != null) {
            slow = slow.next;       // Tortoise moves one step at a time.
            fast = fast.next.next; // Hare moves two steps at a time.
            if (slow == fast) {
                return true; // Cycle detected: the pointers meet.
            }
        }
        return false; // No cycle found: the fast pointer reached the end of the list.
    }

    // 3. Using Stack
    // Time Complexity: O(n), Space Complexity: O(n)
    // Description: This method uses a stack to store the visited nodes.  If a node is encountered that is already in the stack,
    //              then a cycle exists.
    public static boolean hasCycleUsingStack(ListNode head) {
        if (head == null) {
            return false;
        }
        Stack<ListNode> stack = new Stack<>();
        ListNode current = head;
        while (current != null) {
            if (stack.contains(current)) {
                return true; // Cycle detected
            }
            stack.push(current);
            current = current.next;
        }
        return false; // No cycle
    }

    // 4. Using Visited Flag (Modifying the Linked List)
    // Time Complexity: O(n), Space Complexity: O(1)
    // Description: This method modifies the linked list by adding a "visited" flag to each node.
    //              If a node is visited again, it indicates a cycle.  This method modifies the original list.
    public static boolean hasCycleUsingVisitedFlag(ListNode head) {
        if (head == null) {
            return false;
        }
        ListNode current = head;
        while (current != null) {
            if (current.val == Integer.MIN_VALUE) {
                return true; // Cycle detected: node already marked as visited.
            }
            current.val = Integer.MIN_VALUE; // Mark the current node as visited.
            current = current.next;
        }
        return false; // No cycle found.
    }

    // 5. Using Length Comparison
    // Time Complexity: O(n^2), Space Complexity: O(1)
    // Description: This method calculates the length of the linked list by traversing it. In each iteration, it checks
    //              if the length of the remaining list is decreasing. If not, it implies a cycle.
    public static boolean hasCycleUsingLengthComparison(ListNode head) {
        if (head == null) {
            return false;
        }
        ListNode current = head;
        int originalLength = 0;
        while(current != null){
            originalLength++;
            current = current.next;
        }

        current = head;
        int currentLength = originalLength;
        while (current != null) {
            int tempLength = 0;
            ListNode temp = current;
            while(temp != null){
                tempLength++;
                temp = temp.next;
            }
            if (tempLength > currentLength) {
                return true;
            }
            currentLength = tempLength;
            current = current.next;
        }
        return false;
    }
}

