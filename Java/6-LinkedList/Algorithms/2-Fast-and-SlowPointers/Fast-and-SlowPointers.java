import java.util.*;

public class LinkedListFastSlowPointers {

    // 1. Detect a Cycle in a Linked List
    //    - Using Fast and Slow Pointers
    //    - Time Complexity: O(n)
    //    - Space Complexity: O(1)
    public boolean hasCycle(ListNode head) {
        if (head == null || head.next == null) {
            return false;
        }
        ListNode slow = head;
        ListNode fast = head.next; // Start fast one step ahead

        while (fast != null && fast.next != null) {
            if (slow == fast) {
                return true;
            }
            slow = slow.next;
            fast = fast.next.next;
        }
        return false;
    }

    // 2. Find the Middle of a Linked List
    //    - Using Fast and Slow Pointers
    //    - Time Complexity: O(n)
    //    - Space Complexity: O(1)
    public ListNode findMiddle(ListNode head) {
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

    // 3. Find the Start of a Cycle in a Linked List
    //    - Using Fast and Slow Pointers
    //    - Time Complexity: O(n)
    //    - Space Complexity: O(1)
    public ListNode detectCycle(ListNode head) {
        if (head == null || head.next == null) {
            return null;
        }

        ListNode slow = head;
        ListNode fast = head;
        ListNode meet = null; // Store the meeting point

        // Phase 1: Detect the cycle
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) {
                meet = slow; // Found the meeting point
                break;
            }
        }

        if (meet == null) {
            return null; // No cycle
        }

        // Phase 2: Find the start of the cycle
        ListNode start = head;
        while (start != meet) {
            start = start.next;
            meet = meet.next;
        }
        return start;
    }

    // 4. Check if a Linked List is a Palindrome
    //    - Using Fast and Slow Pointers to find the middle, reverse the second half, and compare.
    //    - Time Complexity: O(n)
    //    - Space Complexity: O(1)
    public boolean isPalindrome(ListNode head) {
        if (head == null || head.next == null) {
            return true; // Empty or single-node list is a palindrome
        }

        // Find the middle of the linked list
        ListNode slow = head;
        ListNode fast = head;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }

        // Reverse the second half of the linked list
        ListNode prev = null;
        ListNode curr = slow;
        ListNode next;
        while (curr != null) {
            next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }

        // Compare the first half with the reversed second half
        ListNode firstHalf = head;
        ListNode secondHalf = prev; // prev is now the head of the reversed second half
        while (secondHalf != null) {
            if (firstHalf.val != secondHalf.val) {
                return false;
            }
            firstHalf = firstHalf.next;
            secondHalf = secondHalf.next;
        }
        return true;
    }

    // 5. Reorder a Linked List
    //    - Using Fast and Slow Pointers to find the middle, reverse the second half, and merge.
    //    - Time Complexity: O(n)
    //    - Space Complexity: O(1)
    public void reorderList(ListNode head) {
        if (head == null || head.next == null || head.next.next == null) {
            return; // Nothing to reorder for lists with 0, 1, or 2 nodes
        }

        // 1. Find the middle of the linked list
        ListNode slow = head;
        ListNode fast = head;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }

        // 2. Reverse the second half of the linked list
        ListNode prev = null;
        ListNode curr = slow.next; // Start from the node after the middle
        slow.next = null; // Disconnect the first half from the second half
        ListNode next;
        while (curr != null) {
            next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }

        // 3. Merge the two halves
        ListNode firstHalf = head;
        ListNode secondHalf = prev; // prev is the head of the reversed second half
        while (secondHalf != null) {
            ListNode temp1 = firstHalf.next;
            ListNode temp2 = secondHalf.next;

            firstHalf.next = secondHalf;
            secondHalf.next = temp1;

            firstHalf = temp1;
            secondHalf = temp2;
        }
    }

    // Helper method to create a linked list from an array
    public ListNode createLinkedList(int[] arr) {
        if (arr == null || arr.length == 0) {
            return null;
        }
        ListNode head = new ListNode(arr[0]);
        ListNode curr = head;
        for (int i = 1; i < arr.length; i++) {
            curr.next = new ListNode(arr[i]);
            curr = curr.next;
        }
        return head;
    }

    // Helper method to print a linked list
    public void printLinkedList(ListNode head) {
        ListNode curr = head;
        while (curr != null) {
            System.out.print(curr.val + " -> ");
            curr = curr.next;
        }
        System.out.println("null");
    }

    public static void main(String[] args) {
        LinkedListFastSlowPointers solution = new LinkedListFastSlowPointers();

        // Example usage for hasCycle
        ListNode head1 = solution.createLinkedList(new int[]{1, 2, 3, 4, 5});
        head1.next.next.next.next.next = head1.next; // Create a cycle
        System.out.println("Has Cycle: " + solution.hasCycle(head1)); // Output: true
        head1.next.next.next.next.next = null; //remove cycle

        // Example usage for findMiddle
        ListNode head2 = solution.createLinkedList(new int[]{1, 2, 3, 4, 5});
        System.out.print("Linked List: ");
        solution.printLinkedList(head2);
        ListNode middle = solution.findMiddle(head2);
        System.out.println("Middle Node: " + middle.val); // Output: 3

        // Example usage for detectCycle
        ListNode head3 = solution.createLinkedList(new int[]{1, 2, 3, 4, 5});
        head3.next.next.next.next.next = head3.next.next; // Create a cycle
        ListNode cycleStart = solution.detectCycle(head3);
        System.out.println("Cycle Start Node: " + (cycleStart != null ? cycleStart.val : "No Cycle")); // Output: 3
        head3.next.next.next.next.next = null;

        // Example usage for isPalindrome
        ListNode head4 = solution.createLinkedList(new int[]{1, 2, 3, 2, 1});
        System.out.print("Linked List: ");
        solution.printLinkedList(head4);
        System.out.println("Is Palindrome: " + solution.isPalindrome(head4)); // Output: true

        ListNode head5 = solution.createLinkedList(new int[]{1, 2, 3, 4, 5});
        System.out.print("Linked List: ");
        solution.printLinkedList(head5);
        System.out.print("Reordered List: ");
        solution.reorderList(head5);
        solution.printLinkedList(head5); // Output: 1 -> 5 -> 2 -> 4 -> 3 -> null
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
}


