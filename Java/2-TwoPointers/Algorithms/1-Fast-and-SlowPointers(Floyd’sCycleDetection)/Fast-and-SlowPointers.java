import java.util.*;

public class FastAndSlowPointers {

    // Definition of ListNode (used for linked list problems)
    static class ListNode {
        int val;
        ListNode next;

        ListNode(int val) {
            this.val = val;
            this.next = null;
        }
    }

    // Definition of Node (used for graph problems)
    static class Node {
        int val;
        List<Node> neighbors;

        Node(int val) {
            this.val = val;
            this.neighbors = new ArrayList<>();
        }
    }

    public static void main(String[] args) {
        // Example Usage for Linked List Cycle Detection
        ListNode head = new ListNode(1);
        ListNode node2 = new ListNode(2);
        ListNode node3 = new ListNode(3);
        ListNode node4 = new ListNode(4);
        ListNode node5 = new ListNode(5);

        head.next = node2;
        node2.next = node3;
        node3.next = node4;
        node4.next = node5;
        node5.next = node2; // Creating a cycle: 5 points back to 2

        System.out.println("Linked List Cycle Detection:");
        System.out.println("Approach 1 (Floyd's Cycle Detection): Cycle detected? " + hasCycleFloyd(head)); // true
        System.out.println("Approach 2 (Using a Set): Cycle detected? " + hasCycleSet(head)); // true
        System.out.println("Approach 3 (Modified Floyd's): Cycle detected? " + hasCycleModifiedFloyd(head)); //true

        //Find the start of the cycle
        System.out.println("Start of cycle (Floyd's): " + findCycleStart(head).val);

        // Example Usage for Happy Number
        int num1 = 19;
        int num2 = 2;

        System.out.println("\nHappy Number:");
        System.out.println(num1 + " is a happy number? " + isHappy(num1)); // true
        System.out.println(num2 + " is a happy number? " + isHappy(num2)); // false

        // Example usage Palindrome Linked List
        ListNode headPalindrome1 = new ListNode(1);
        headPalindrome1.next = new ListNode(2);
        headPalindrome1.next.next = new ListNode(2);
        headPalindrome1.next.next.next = new ListNode(1);
        System.out.println("\nPalindrome Linked List:");
        System.out.println("Is the linked list a palindrome? " + isPalindrome(headPalindrome1));

        ListNode headPalindrome2 = new ListNode(1);
        headPalindrome2.next = new ListNode(2);
        System.out.println("Is the linked list a palindrome? " + isPalindrome(headPalindrome2));

    }

    // Approach 1: Floyd's Cycle Detection Algorithm (Fast and Slow Pointers)
    // - Time Complexity: O(n)
    // - Space Complexity: O(1)
    // - Explanation: Uses two pointers, 'slow' and 'fast'.  'Slow' moves one step at a time,
    //   'fast' moves two steps at a time. If there's a cycle, the two pointers will eventually meet.
    public static boolean hasCycleFloyd(ListNode head) {
        if (head == null || head.next == null) {
            return false; // No cycle if the list is empty or has only one node
        }

        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;      // Move slow pointer one step
            fast = fast.next.next;  // Move fast pointer two steps

            if (slow == fast) {
                return true; // Cycle detected: slow and fast pointers meet
            }
        }
        return false; // No cycle: fast pointer reached the end of the list
    }

    // Approach 2: Using a Set to detect cycles
    // - Time Complexity: O(n)
    // - Space Complexity: O(n)
    // - Explanation:  Iterate through the linked list, adding each node to a Set.
    //   If a node is encountered that's already in the Set, then there's a cycle.
    public static boolean hasCycleSet(ListNode head) {
        if (head == null) {
            return false;
        }
        Set<ListNode> visitedNodes = new HashSet<>();
        ListNode current = head;
        while (current != null) {
            if (visitedNodes.contains(current)) {
                return true; // Cycle detected: node already in the set
            }
            visitedNodes.add(current); // Add the current node to the set
            current = current.next;
        }
        return false; // No cycle: reached the end of the list
    }

    // Approach 3: Modified Floyd's Algorithm (Finding the cycle start)
    // - Time Complexity: O(n)
    // - Space Complexity: O(1)
    // - Explanation: This approach not only detects the cycle but also finds the start
    //   node of the cycle. After the slow and fast pointers meet, move the slow
    //   pointer back to the head and move both slow and fast pointers one step at a
    //   time. The point where they meet again is the start of the cycle.
    public static boolean hasCycleModifiedFloyd(ListNode head) {
        if (head == null || head.next == null) {
            return false;
        }

        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) {
                return true; // Cycle detected
            }
        }
        return false;
    }

    public static ListNode findCycleStart(ListNode head) {
        if (head == null || head.next == null) {
            return null; // No cycle, no start
        }

        ListNode slow = head;
        ListNode fast = head;

        // Phase 1: Detect the cycle
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) {
                break; // Cycle detected, exit the loop
            }
        }

        if (fast == null || fast.next == null) {
            return null; // No cycle found
        }

        // Phase 2: Find the start of the cycle
        slow = head; // Move slow pointer back to the head
        while (slow != fast) {
            slow = slow.next; // Move both pointers one step at a time
            fast = fast.next;
        }
        return slow; // The meeting point is the start of the cycle
    }

    // Approach 4: Happy Number Problem
    // - Time Complexity: O(log n) - The number of iterations is bounded by the number of digits in 'n'.
    // - Space Complexity: O(1)      - Constant extra space is used.
    // - Explanation: A happy number is a number that eventually reaches 1 when repeatedly replaced by the sum of the square of its digits.
    //   This solution uses the fast and slow pointer approach to detect if a number is happy or not.
    //   If a number is not happy, its sequence will end up in a cycle.  We use the fast and slow pointer
    //   technique to detect this cycle.
    public static boolean isHappy(int n) {
        int slow = n;
        int fast = n;

        do {
            slow = findSquareSum(slow);       // Move slow pointer one step
            fast = findSquareSum(findSquareSum(fast)); // Move fast pointer two steps
        } while (slow != fast);

        return slow == 1; // If the meeting point is 1, the number is happy
    }

    // Helper function to calculate the sum of the squares of the digits of a number
    private static int findSquareSum(int num) {
        int sum = 0;
        while (num > 0) {
            int digit = num % 10;
            sum += digit * digit;
            num /= 10;
        }
        return sum;
    }

    // Approach 5: Palindrome Linked List
    // - Time Complexity: O(n)
    // - Space Complexity: O(1)
    public static boolean isPalindrome(ListNode head) {
        if (head == null || head.next == null) {
            return true; // Empty list or single node is a palindrome
        }

        ListNode slow = head;
        ListNode fast = head;

        // Find the middle of the linked list
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }

        // Reverse the second half of the linked list
        ListNode secondHalf = reverseList(slow);

        // Compare the first half and the reversed second half
        ListNode firstHalf = head;
        while (secondHalf != null) {
            if (firstHalf.val != secondHalf.val) {
                return false; // Not a palindrome
            }
            firstHalf = firstHalf.next;
            secondHalf = secondHalf.next;
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
}

