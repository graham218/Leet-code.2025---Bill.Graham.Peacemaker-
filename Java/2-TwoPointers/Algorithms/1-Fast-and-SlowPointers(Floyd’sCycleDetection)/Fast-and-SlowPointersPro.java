import java.util.*;

public class TwoPointers {

    // 1. Linked List Cycle Detection
    //   - Real-world application: Detecting loops in linked list-based data structures,
    //     such as detecting if a routing path in a network has a loop, which can cause network congestion.
    //   - Problem: Given the head of a singly linked list, determine if the list has a cycle.
    //   - Time Complexity: O(n)
    //   - Space Complexity: O(1)
    public static boolean hasCycle(ListNode head) {
        if (head == null || head.next == null) {
            return false;
        }
        ListNode slow = head;
        ListNode fast = head.next; // Start fast one step ahead

        while (fast != null && fast.next != null) {
            if (slow == fast) {
                return true; // Cycle detected
            }
            slow = slow.next;
            fast = fast.next.next;
        }
        return false; // No cycle
    }

    // ListNode class (inner class for linked list problems)
    static class ListNode {
        int val;
        ListNode next;
        ListNode(int x) {
            val = x;
            next = null;
        }
    }



    // 2. Find the Start of a Linked List Cycle
    //   - Real-world application: Detecting the beginning of a loop in a circular buffer
    //     used in real-time data processing, allowing for resetting the buffer.
    //   - Problem: Given the head of a linked list with a cycle, find the node where the cycle begins.
    //   - Time Complexity: O(n)
    //   - Space Complexity: O(1)
    public static ListNode findCycleStart(ListNode head) {
        if (head == null || head.next == null) {
            return null;
        }
        ListNode slow = head;
        ListNode fast = head;

        // Detect the cycle
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) {
                break; // Cycle detected, break the loop
            }
        }

        // If no cycle, return null
        if (fast == null || fast.next == null) {
            return null;
        }
        // Find the start of the cycle
        slow = head;
        while (slow != fast) {
            slow = slow.next;
            fast = fast.next;
        }
        return slow; // Returns the start of the cycle
    }


    // 3. Happy Number
    //   - Real-world application: Used in software testing to detect infinite loops
    //     in state transition systems. For example, testing if a configuration setting
    //     repeatedly leads back to itself without reaching a terminal state.
    //   - Problem: A happy number is a number which eventually reaches 1 when replaced by the sum of the square of each digit.
    //     For example, 13 is a happy number because 1^2 + 3^2 = 10, 1^2 + 0^2 = 1.
    //     Determine if a number is a happy number.
    //   - Time Complexity: O(log n)
    //   - Space Complexity: O(1)
    public static boolean isHappy(int n) {
        int slow = n;
        int fast = n;

        do {
            slow = findSquareSum(slow);
            fast = findSquareSum(findSquareSum(fast));
        } while (slow != fast);

        return slow == 1;
    }

    private static int findSquareSum(int num) {
        int sum = 0;
        while (num > 0) {
            int digit = num % 10;
            sum += digit * digit;
            num /= 10;
        }
        return sum;
    }


    // 4. Middle of the Linked List
    //  - Real-world application: Finding the middle point in a linked list of tasks
    //    in a task management system, which can be useful for dividing tasks or
    //    implementing a "jump to middle" feature.
    //  - Problem: Given the head of a singly linked list, return the middle node of the linked list.
    //    If there are two middle nodes, return the second middle node.
    //  - Time Complexity: O(n)
    //  - Space Complexity: O(1)

    public static ListNode middleNode(ListNode head) {
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


    // 5. Circular Array Loop
    // - Real-world application: Detecting cyclic dependencies in a configuration file,
    //   where each element represents a jump instruction to another element. This can
    //   help prevent infinite loops during configuration loading or processing.
    // - Problem: You are given a circular array nums of n integers, where each number nums[i] is the number of steps
    //   you take forward or backward starting from index i.
    //   Return true if there is a cycle in nums, otherwise return false.
    // - Time Complexity: O(n)
    // - Space Complexity: O(1)
    public static boolean hasCircularArrayLoop(int[] nums) {
        if (nums == null || nums.length < 2) {
            return false;
        }

        int n = nums.length;
        for (int i = 0; i < n; i++) {
            int slow = i, fast = i;
            boolean isForward = nums[i] > 0; // Store the direction

            while (true) {
                // Move slow pointer
                slow = nextStep(nums, slow, isForward);
                // Move fast pointer twice
                fast = nextStep(nums, fast, isForward);
                if (fast != -1) { // Check for -1 before nextStep
                    fast = nextStep(nums, fast, isForward);
                }

                if (slow == -1 || fast == -1) {
                    break; // No cycle found for this starting point
                }

                if (slow == fast) {
                    // Check for non-trivial cycle (length > 1)
                    if (slow == nextStep(nums, slow, isForward)) {
                        break; // Cycle of length 1, invalid
                    }
                    return true; // Cycle found
                }
            }
        }
        return false;
    }

    private static int nextStep(int[] nums, int index, boolean prevIsForward) {
        int n = nums.length;
        if (index < 0 || index >= n) return -1;

        boolean currentIsForward = nums[index] > 0;
        if (currentIsForward != prevIsForward) {
            return -1; // Different direction, not a valid step
        }

        int nextIndex = (index + nums[index]) % n;
        if (nextIndex < 0) {
            nextIndex += n; // Handle negative indices in circular array
        }
        return nextIndex;
    }



    public static void main(String[] args) {
        // 1. Linked List Cycle Detection
        ListNode head1 = new ListNode(1);
        head1.next = new ListNode(2);
        head1.next.next = new ListNode(3);
        head1.next.next.next = new ListNode(4);
        head1.next.next.next.next = head1.next; // Create a cycle
        System.out.println("Linked List Cycle Detection: " + hasCycle(head1)); // Output: true

        ListNode head2 = new ListNode(1);
        head2.next = new ListNode(2);
        head2.next.next = new ListNode(3);
        System.out.println("Linked List Cycle Detection: " + hasCycle(head2)); // Output: false

        // 2. Find the Start of a Linked List Cycle
        ListNode cycleStart = findCycleStart(head1);
        if (cycleStart != null) {
            System.out.println("Cycle Start Node Value: " + cycleStart.val); // Output: 2
        } else {
            System.out.println("No cycle found.");
        }

        ListNode head3 = new ListNode(1);
        head3.next = new ListNode(2);
        head3.next.next = new ListNode(3);
        System.out.println("Cycle Start of list without cycle: " + findCycleStart(head3)); //null

        // 3. Happy Number
        System.out.println("Is 13 a happy number? " + isHappy(13)); // Output: true
        System.out.println("Is 4 a happy number? " + isHappy(4));   // Output: false

        // 4. Middle of the Linked List
        ListNode head4 = new ListNode(1);
        head4.next = new ListNode(2);
        head4.next.next = new ListNode(3);
        head4.next.next.next = new ListNode(4);
        head4.next.next.next.next = new ListNode(5);
        System.out.println("Middle Node: " + middleNode(head4).val); // Output: 3

        ListNode head5 = new ListNode(1);
        head5.next = new ListNode(2);
        head5.next.next = new ListNode(3);
        head5.next.next.next = new ListNode(4);
        head5.next.next.next.next = new ListNode(5);
        head5.next.next.next.next.next = new ListNode(6);
        System.out.println("Middle Node of even length list: " + middleNode(head5).val); //4

        // 5. Circular Array Loop
        int[] nums1 = {2, -1, 1, 2, 2};
        System.out.println("Circular Array Loop: " + hasCircularArrayLoop(nums1)); // Output: true

        int[] nums2 = {-2, 1, -1, -2, -2};
        System.out.println("Circular Array Loop: " + hasCircularArrayLoop(nums2)); // Output: false

        int[] nums3 = {1, 2};
        System.out.println("Circular Array Loop: " + hasCircularArrayLoop(nums3)); // false

        int[] nums4 = {2, -1, 1, -2, -2};
        System.out.println("Circular Array Loop 4: " + hasCircularArrayLoop(nums4)); // false

        int[] nums5 = {1, 2, -1, 2, 2};
        System.out.println("Circular Array Loop 5: " + hasCircularArrayLoop(nums5)); // true
    }
}

