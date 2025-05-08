import java.util.HashSet;
import java.util.Set;



public class LinkedListCycleDetection {

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
        node5.next = node2; // Create a cycle: 5 points back to 2.

        // Test the different cycle detection methods.
        System.out.println("Using Floyd's Tortoise and Hare (Method 1): Cycle detected: " + hasCycleFloyd(head));
        System.out.println("Using Floyd's Tortoise and Hare with Cycle Start (Method 2): Cycle detected: " + hasCycleFloydWithStart(head));

        System.out.println("Using HashSet (Method 3): Cycle detected: " + hasCycleHashSet(head));

        System.out.println("Using Visited Flag (Method 4): Cycle detected: " + hasCycleVisitedFlag(head));

        System.out.println("Using List Length Check (Method 5): Cycle detected: " + hasCycleLengthCheck(head));
    }

    // Method 1: Floyd's Tortoise and Hare Algorithm (Basic)
    //   - Uses two pointers, 'slow' and 'fast'.
    //   - 'slow' moves one node at a time, 'fast' moves two nodes at a time.
    //   - If there is a cycle, the two pointers will eventually meet.
    //   - Time Complexity: O(n), Space Complexity: O(1)
    public static boolean hasCycleFloyd(ListNode head) {
        if (head == null || head.next == null) {
            return false; // No cycle if the list is empty or has only one node.
        }

        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;      // Move slow pointer one step.
            fast = fast.next.next; // Move fast pointer two steps.
            if (slow == fast) {
                return true; // Cycle detected: slow and fast pointers meet.
            }
        }
        return false; // No cycle: fast pointer reached the end of the list.
    }

    // Method 2: Floyd's Tortoise and Hare Algorithm (Find Cycle Start)
    //   - Same as Method 1, but also finds the start node of the cycle.
    //   - After the pointers meet, move 'slow' back to the head.
    //   - Move both 'slow' and 'fast' one step at a time until they meet again.
    //   - The meeting point is the start of the cycle.
    public static boolean hasCycleFloydWithStart(ListNode head) {
        if (head == null || head.next == null) {
            return false;
        }

        ListNode slow = head;
        ListNode fast = head;
        ListNode meetingPoint = null; // Store the meeting point of slow and fast pointers

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) {
                meetingPoint = slow; // Store the meeting point
                break;
            }
        }

        if (meetingPoint == null) {
            return false; // No cycle
        }

        // Find the start of the cycle
        slow = head;
        while (slow != meetingPoint) {
            slow = slow.next;
            meetingPoint = meetingPoint.next;
        }
        return true;
    }



    // Method 3: Using a HashSet
    //   - Stores each visited node in a HashSet.
    //   - If a node is encountered that is already in the HashSet, a cycle exists.
    //   - Time Complexity: O(n), Space Complexity: O(n)
    public static boolean hasCycleHashSet(ListNode head) {
        if (head == null) {
            return false;
        }

        Set<ListNode> visitedNodes = new HashSet<>();
        ListNode current = head;

        while (current != null) {
            if (visitedNodes.contains(current)) {
                return true; // Cycle detected: current node was already visited.
            }
            visitedNodes.add(current); // Add the current node to the HashSet.
            current = current.next;
        }
        return false; // No cycle: reached the end of the list.
    }

    // Method 4: Using a Visited Flag in the Node
    //   - Modifies the ListNode class (in-place modification).  //<- Important
    //   - Adds a 'visited' boolean flag to each node.
    //   - Set the flag to true when a node is visited.
    //   - If a visited node is encountered again, a cycle exists.
    //   - Time Complexity: O(n), Space Complexity: O(1) (excluding the space for the added flag)
    //   - Note: This method modifies the original linked list.  In some cases, you may not be allowed to modify the list.
    public static boolean hasCycleVisitedFlag(ListNode head) {
        if (head == null) {
            return false;
        }

        ListNode current = head;
        while (current != null) {
            if (current.val == Integer.MAX_VALUE) { // Using Integer.MAX_VALUE as a visited flag.  A boolean would be better, but avoids modifying the class.
                return true;
            }
            current.val = Integer.MAX_VALUE;  // Mark the current node as visited.
            current = current.next;
        }
        return false;
    }

    // Method 5: Cycle Detection by Length Check
    //  - Calculate the length of the linked list by traversing it.
    //  - If a cycle exists, the traversal might not terminate, or it will take a very long time.
    //  - We can set a maximum allowed length (e.g., 2n, where n is an estimated length).
    //  - If the traversal exceeds this limit, we assume there's a cycle.
    //  - This method is not very reliable, as the maximum length is arbitrary and depends on list
    //  - Time Complexity: O(n) in best case, O(infinite) in worst case (if no limit), Space Complexity: O(1)
    public static boolean hasCycleLengthCheck(ListNode head) {
        if (head == null) {
            return false;
        }

        int maxLength = 1000; // Arbitrary maximum length.  Should be related to expected list length.
        int length = 0;
        ListNode current = head;

        while (current != null && length <= maxLength) {
            length++;
            current = current.next;
        }

        return length > maxLength; // If length exceeds maxLength, assume a cycle.
    }
}

// Definition of a singly linked list node.
class ListNode {
    int val;
    ListNode next;

    ListNode(int val) {
        this.val = val;
        this.next = null;
    }
}
