import java.util.HashSet;
import java.util.Set;

public class LinkedListFastAndSlowPointers {

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
        // Create a sample linked list for testing
        ListNode head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(3);
        head.next.next.next = new ListNode(4);
        head.next.next.next.next = new ListNode(5);

        // Create a cycle for testing cycle detection
        head.next.next.next.next.next = head.next; // Creates a cycle: 1 -> 2 -> 3 -> 4 -> 5 -> 2

        // 1. Detect Cycle in a Linked List
        System.out.println("1. Detect Cycle in a Linked List:");
        System.out.println("   Cycle detected (Approach 1): " + hasCycle(head)); // true
        System.out.println("   Cycle detected (Approach 2): " + hasCycleUsingSet(head)); // true

        // 2. Find the Middle of a Linked List
        System.out.println("\n2. Find the Middle of a Linked List:");
        ListNode middle = findMiddle(head);
        if (middle != null) {
            System.out.println("   Middle node value: " + middle.val); // 3 (if no cycle), but with cycle, prints 2.
        }

        // 3. Find the Start of a Cycle
        System.out.println("\n3. Find the Start of a Cycle:");
        ListNode cycleStart = findCycleStart(head);
        if (cycleStart != null) {
            System.out.println("   Cycle start node value: " + cycleStart.val); // 2
        }

        // 4. Check if a Linked List is a Palindrome
        System.out.println("\n4. Check if a Linked List is a Palindrome:");
        ListNode palindromeHead = new ListNode(1);
        palindromeHead.next = new ListNode(2);
        palindromeHead.next.next = new ListNode(3);
        palindromeHead.next.next.next = new ListNode(2);
        palindromeHead.next.next.next.next = new ListNode(1);
        System.out.println("   Is palindrome: " + isPalindrome(palindromeHead)); // true

        ListNode notPalindromeHead = new ListNode(1);
        notPalindromeHead.next = new ListNode(2);
        notPalindromeHead.next.next = new ListNode(3);
        notPalindromeHead.next.next.next = new ListNode(4);
        System.out.println("   Is palindrome: " + isPalindrome(notPalindromeHead)); // false

        // 5. Remove Nth Node From End of List
        System.out.println("\n5. Remove Nth Node From End of List:");
        ListNode removeNthHead = new ListNode(1);
        removeNthHead.next = new ListNode(2);
        removeNthHead.next.next = new ListNode(3);
        removeNthHead.next.next.next = new ListNode(4);
        removeNthHead.next.next.next.next = new ListNode(5);
        int n = 2;
        ListNode result = removeNthFromEnd(removeNthHead, n);
        System.out.print("   List after removing " + n + "th node from end: ");
        printList(result); // Output: 1 -> 2 -> 3 -> 5

        ListNode removeHead = new ListNode(1);
        n = 1;
        ListNode result2 = removeNthFromEnd(removeHead, n);
        System.out.print("   List after removing " + n + "th node from end: ");
        printList(result2); // Output: (empty list)
    }

    // 1. Detect Cycle in a Linked List
    //    - Problem: Determine if a linked list contains a cycle.
    //    - Real-world application: Detecting infinite loops in data processing pipelines,
    //      identifying circular dependencies in configuration files.
    //    - Approach: Floyd's Cycle Detection Algorithm (Fast and Slow Pointers)
    public static boolean hasCycle(ListNode head) {
        if (head == null || head.next == null) {
            return false; // No cycle if the list is empty or has only one node
        }
        ListNode slow = head;
        ListNode fast = head.next; // Start fast pointer one step ahead

        while (fast != null && fast.next != null) {
            if (slow == fast) {
                return true; // Cycle detected
            }
            slow = slow.next;
            fast = fast.next.next;
        }
        return false; // No cycle
    }

    // 1. (Alternative) Detect Cycle in a Linked List using HashSet
    //   - Problem: Same as above.
    //   - Real-world application: Same as above.
    //   - Approach: Using a HashSet to keep track of visited nodes.
    public static boolean hasCycleUsingSet(ListNode head) {
        Set<ListNode> visited = new HashSet<>();
        ListNode current = head;
        while (current != null) {
            if (visited.contains(current)) {
                return true; // Cycle detected
            }
            visited.add(current);
            current = current.next;
        }
        return false; // No cycle
    }


    // 2. Find the Middle of a Linked List
    //    - Problem: Locate the middle node in a linked list.
    //    - Real-world application: Finding the pivot element in a linked list for sorting algorithms,
    //      determining the center point for rendering a long list in a user interface.
    //    - Approach: Fast and Slow Pointers
    public static ListNode findMiddle(ListNode head) {
        if (head == null) {
            return null;
        }
        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    }

    // 3. Find the Start of a Cycle
    //    - Problem: Given a linked list with a cycle, find the node where the cycle begins.
    //    - Real-world application: Debugging memory leaks caused by circular data structures,
    //      analyzing network routing paths for loops.
    //    - Approach: Floyd's Cycle Detection Algorithm with additional steps
    public static ListNode findCycleStart(ListNode head) {
        if (head == null || head.next == null) {
            return null; // No cycle
        }
        ListNode slow = head;
        ListNode fast = head;
        boolean hasCycle = false;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) {
                hasCycle = true;
                break; // Cycle detected, break the loop
            }
        }

        if (!hasCycle) {
            return null; // No cycle
        }

        // Move slow pointer to the head and keep fast at the meeting point.
        slow = head;
        while (slow != fast) {
            slow = slow.next;
            fast = fast.next;
        }
        return slow; // The meeting point is the start of the cycle.
    }

    // 4. Check if a Linked List is a Palindrome
    //    - Problem: Determine if a linked list reads the same forwards and backward.
    //    - Real-world application: Verifying the integrity of data transmitted over a network,
    //      validating user input for palindromic patterns (e.g., in a DNA sequence analysis tool).
    //    - Approach: Reverse the second half of the linked list and compare it with the first half.
    public static boolean isPalindrome(ListNode head) {
        if (head == null || head.next == null) {
            return true; // Empty or single-node list is a palindrome
        }

        // Find the middle of the linked list
        ListNode middle = findMiddle(head);

        // Reverse the second half of the linked list
        ListNode secondHalfHead = reverseList(middle);

        // Compare the first half and the reversed second half
        ListNode firstHalfPtr = head;
        ListNode secondHalfPtr = secondHalfHead;
        while (secondHalfPtr != null) {
            if (firstHalfPtr.val != secondHalfPtr.val) {
                return false; // Not a palindrome
            }
            firstHalfPtr = firstHalfPtr.next;
            secondHalfPtr = secondHalfPtr.next;
        }

        return true; // Is a palindrome
    }

    // Helper function to reverse a linked list
    private static ListNode reverseList(ListNode head) {
        ListNode prev = null;
        ListNode current = head;
        ListNode next = null;
        while (current != null) {
            next = current.next;
            current.next = prev;
            prev = current;
            current = next;
        }
        return prev;
    }

    // 5. Remove Nth Node From End of List
    //    - Problem: Delete the nth node from the end of a linked list.
    //    - Real-world application: Implementing undo functionality in a text editor,
    //      managing a history of changes in a version control system.
    //    - Approach: Two pointers with a gap of n nodes.
    public static ListNode removeNthFromEnd(ListNode head, int n) {
        if (head == null) {
            return null;
        }
        ListNode dummy = new ListNode(0); // Dummy node to handle the case where the head is removed
        dummy.next = head;
        ListNode slow = dummy;
        ListNode fast = dummy;

        // Move the fast pointer n nodes ahead
        for (int i = 0; i < n; i++) {
            if (fast == null) {
                return null; // Handle invalid n (n is greater than the list length)
            }
            fast = fast.next;
        }

        // Move both pointers until the fast pointer reaches the end
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next;
        }

        // Remove the nth node from the end
        slow.next = slow.next.next;

        return dummy.next; // Return the new head (in case the head was removed)
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
}

