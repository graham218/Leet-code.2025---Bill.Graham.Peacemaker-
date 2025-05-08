import java.util.HashSet;
import java.util.Set;
import java.util.HashMap;
import java.util.Map;

public class LinkedListCycleDetection {

    // Definition of a singly linked list node.
    static class ListNode {
        int val;
        ListNode next;

        ListNode(int val) {
            this.val = val;
            this.next = null;
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
        System.out.println("Floyd's Cycle Detection (Tortoise and Hare): " + hasCycleFloyd(head)); // Expected: true
        System.out.println("Using HashSet: " + hasCycleUsingHashSet(head)); // Expected: true
        System.out.println("Using HashMap: " + hasCycleUsingHashMap(head)); // Expected: true
        System.out.println("Modifying List Nodes: " + hasCycleModifyingList(head)); // Expected: true, but modifies the list!
        //Recreate the list
        head = new ListNode(1);
        node2 = new ListNode(2);
        node3 = new ListNode(3);
        node4 = new ListNode(4);
        node5 = new ListNode(5);

        head.next = node2;
        node2.next = node3;
        node3.next = node4;
        node4.next = node5;
        node5.next = node2;
        System.out.println("Using Length Comparison: " + hasCycleLengthComparison(head));
    }

    // 1. Floyd's Cycle Detection Algorithm (Tortoise and Hare)
    //   - Uses two pointers, 'slow' and 'fast'.
    //   - 'slow' moves one step at a time, 'fast' moves two steps at a time.
    //   - If there is a cycle, the two pointers will eventually meet.
    //   - This is the most efficient and commonly used algorithm.
    //
    //   - Real-world application: Detecting loops in program execution paths,
    //     finding circular dependencies in data structures, and optimizing
    //     memory management by identifying unreachable objects.
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

    // 2. Using a HashSet
    //   - Stores each visited node in a HashSet.
    //   - If a node is encountered again, it means there is a cycle.
    //   - Uses extra space for the HashSet.
    //
    //   - Real-world application: Detecting duplicate entries in data streams,
    //     identifying previously visited states in state machines, and
    //     preventing infinite loops in web crawling algorithms.
    public static boolean hasCycleUsingHashSet(ListNode head) {
        if (head == null) {
            return false;
        }

        Set<ListNode> visitedNodes = new HashSet<>();
        ListNode current = head;

        while (current != null) {
            if (visitedNodes.contains(current)) {
                return true; // Cycle detected: current node is already in the set.
            }
            visitedNodes.add(current); // Add the current node to the set.
            current = current.next;     // Move to the next node.
        }
        return false; // No cycle: reached the end of the list.
    }

    // 3. Using a HashMap
    //   - Stores each visited node and its count in a HashMap.
    //   - If a node is encountered again, the count will be greater than 1,
    //     indicating a cycle.
    //   - Similar to HashSet but stores counts, which can be useful in other scenarios.
    //
    //  - Real-world application: Counting the frequency of visited URLs in
    //    web crawling, tracking the number of times a specific process
    //    is executed, and analyzing network traffic patterns to detect
    //    repeatedly visited nodes.
    public static boolean hasCycleUsingHashMap(ListNode head) {
        if (head == null) {
            return false;
        }

        Map<ListNode, Integer> nodeCounts = new HashMap<>();
        ListNode current = head;

        while (current != null) {
            if (nodeCounts.containsKey(current)) {
                return true; // Cycle detected: node count is greater than 1.
            }
            nodeCounts.put(current, 1); // Add the node to the map or increment its count.
            current = current.next;       // Move to the next node.
        }
        return false; // No cycle: reached the end of the list.
    }

    // 4. Modifying List Node Values (Not Recommended for Production)
    //   - Changes the 'val' field of each visited node to a specific value.
    //   - If a node with the specific value is encountered again, it indicates a cycle.
    //   - **Caution:** This method modifies the original linked list, which is
    //     generally not recommended.  It's destructive and can lead to problems
    //     if the list is used elsewhere.
    //   - It also only works for specific data types and value ranges.
    //
    //   - Real-world application: This approach is generally *not* recommended
    //     for real-world applications due to its destructive nature.  It might
    //     be used in very specific, isolated scenarios where modifying the
    //     list is acceptable and memory efficiency is extremely critical, but
    //     alternatives are almost always preferred.  It's included here for
    //     completeness and to illustrate a less desirable approach.
    public static boolean hasCycleModifyingList(ListNode head) {
        if (head == null) {
            return false;
        }

        ListNode current = head;
        int markerValue = Integer.MIN_VALUE; // Use a value that's unlikely to appear in the list.

        while (current != null) {
            if (current.val == markerValue) {
                return true; // Cycle detected: node value has been seen before.
            }
            current.val = markerValue; // Mark the node as visited.
            current = current.next;     // Move to the next node.
        }
        return false; // No cycle: reached the end of the list.
    }

    // 5. Length Comparison (Only Works for Specific Cycle Types)
    //   - Calculate the length of the list by traversing it.
    //   - If a cycle exists, the traversal might not terminate, or a very long traversal.
    //   - This method is unreliable for general cycle detection, especially for complex cycles.
    //   - It's more of a conceptual approach and not robust.
    //   - In practical scenarios, you might set a maximum allowed length to prevent infinite loops.
    //
    //   - Real-world application: This method is generally *not* suitable for
    //     real-world applications due to its limitations and potential for
    //     infinite loops.  It might be used in very specific scenarios where
    //     the cycle is known to be a simple loop at the end of the list, and
    //     a rough estimate of length is needed.  However, Floyd's algorithm
    //     or HashSet are far more reliable and efficient.
    public static boolean hasCycleLengthComparison(ListNode head) {
        if (head == null) {
            return false;
        }

        int originalLength = 0;
        ListNode current = head;
        while (current != null && originalLength < 200) { //Added a max length check
            originalLength++;
            current = current.next;
        }
        if(current == null){
            return false;
        }

        int traversedLength = 0;
        current = head;
        while (current != null && traversedLength <= originalLength) {
            traversedLength++;
            current = current.next;
        }

        return traversedLength > originalLength;
    }
}

