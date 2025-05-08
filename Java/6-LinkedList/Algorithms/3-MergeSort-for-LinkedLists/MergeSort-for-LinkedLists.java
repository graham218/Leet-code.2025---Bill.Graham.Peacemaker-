import java.util.*;


public class MergeSortLinkedList {

    /**
     * Approach 1: Top-Down Merge Sort (Recursive) - Classic Implementation
     * -   Find the middle of the linked list using the slow and fast pointer approach.
     * -   Recursively sort the left and right halves.
     * -   Merge the sorted halves.
     *
     * Time Complexity: O(n log n)
     * Space Complexity: O(log n) - due to the recursive call stack
     */
    public ListNode mergeSortRecursive(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }

        // 1. Find the middle
        ListNode middle = findMiddle(head);
        ListNode nextOfMiddle = middle.next;
        middle.next = null; // Split the list

        // 2. Recursively sort the two halves
        ListNode left = mergeSortRecursive(head);
        ListNode right = mergeSortRecursive(nextOfMiddle);

        // 3. Merge the sorted halves
        ListNode sortedList = merge(left, right);
        return sortedList;
    }

    // Helper function to find the middle of the linked list
    private ListNode findMiddle(ListNode head) {
        if (head == null) {
            return null;
        }
        ListNode slow = head;
        ListNode fast = head;
        //when fast reaches null, slow is at the middle
        while (fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    }

    // Helper function to merge two sorted linked lists
    private ListNode merge(ListNode left, ListNode right) {
        ListNode dummy = new ListNode(-1); // Dummy node to simplify the merging
        ListNode tail = dummy;

        while (left != null && right != null) {
            if (left.val <= right.val) {
                tail.next = left;
                left = left.next;
            } else {
                tail.next = right;
                right = right.next;
            }
            tail = tail.next;
        }

        // Add the remaining nodes from either list (if any)
        tail.next = (left != null) ? left : right;
        return dummy.next; // Return the merged list starting from the first actual node
    }



    /**
     * Approach 2: Bottom-Up Merge Sort (Iterative)
     * -   Iteratively merge sublists of increasing size.
     * -   Start with sublists of size 1, then 2, 4, 8, and so on.
     * -   This avoids recursion and uses a loop-based approach.
     *
     * Time Complexity: O(n log n)
     * Space Complexity: O(1) - Iterative approach uses constant extra space
     */
    public ListNode mergeSortIterative(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }

        int n = getLength(head); //get the length of the linked list.
        ListNode dummy = new ListNode(-1); // Dummy node to simplify merging
        dummy.next = head;

        for (int size = 1; size < n; size <<= 1) { // size doubles in each iteration (1, 2, 4, 8...)
            ListNode prev = dummy;
            ListNode curr = dummy.next;

            while (curr != null) {
                ListNode left = curr;
                ListNode right = split(curr, size); //splits the list into left and right of size = size
                curr = split(right, size);     // next sublist to merge

                prev.next = mergeIterative(left, right); // Merges and updates the 'next' pointer of the previous sublist.
                while (prev.next != null) {
                    prev = prev.next;
                }
            }
        }
        return dummy.next;
    }

    // Helper function to get the length of the linked list
    private int getLength(ListNode head) {
        int length = 0;
        ListNode current = head;
        while (current != null) {
            length++;
            current = current.next;
        }
        return length;
    }

    // Helper function to split the linked list into two parts
    // Splits the list into two parts.  The first part has 'size' nodes.
    private ListNode split(ListNode head, int size) {
        if (head == null) {
            return null;
        }
        ListNode current = head;
        for (int i = 1; i < size && current.next != null; i++) {
            current = current.next;
        }
        ListNode next = current.next;
        current.next = null; // Important:  Break the link
        return next;
    }

    // Helper function to merge two sorted linked lists (iterative version)
    private ListNode mergeIterative(ListNode left, ListNode right) {
        ListNode dummy = new ListNode(-1);
        ListNode tail = dummy;

        while (left != null && right != null) {
            if (left.val <= right.val) {
                tail.next = left;
                left = left.next;
            } else {
                tail.next = right;
                right = right.next;
            }
            tail = tail.next;
        }
        tail.next = (left != null) ? left : right;
        return dummy.next;
    }



    /**
     * Approach 3: Merge Sort with Auxiliary Array
     * -   Copy the linked list to an array.
     * -   Apply merge sort on the array.
     * -   Update the linked list values from the sorted array.
     *
     * Time Complexity: O(n log n)
     * Space Complexity: O(n) - for the auxiliary array
     */
    public ListNode mergeSortArray(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }

        // 1. Copy linked list to array
        ArrayList<Integer> list = new ArrayList<>();
        ListNode current = head;
        while (current != null) {
            list.add(current.val);
            current = current.next;
        }

        // 2. Sort the array
        Collections.sort(list); // Using Java's built-in sort (which is usually a variant of merge sort)

        // 3. Update linked list values from the sorted array
        current = head;
        int index = 0;
        while (current != null) {
            current.val = list.get(index++);
            current = current.next;
        }
        return head;
    }

    /**
     * Approach 4: In-Place Merge Sort (Optimized Iterative)
     * -   This approach is a refined iterative merge sort that minimizes extra variable usage.
     * -   It's similar to the iterative approach but with more careful pointer manipulation.
     *
     * Time Complexity: O(n log n)
     * Space Complexity: O(1) - Constant extra space
     */
    public ListNode mergeSortInPlace(ListNode head) {
        if (head == null || head.next == null) return head;

        int n = getLength(head);
        ListNode dummy = new ListNode(-1);
        dummy.next = head;

        for (int size = 1; size < n; size <<= 1) {
            ListNode prev = dummy, curr = dummy.next;
            while (curr != null) {
                ListNode left = curr, right = splitInPlace(curr, size);
                curr = splitInPlace(right, size);
                ListNode merged = mergeInPlace(left, right);
                prev.next = merged;
                while (prev.next != null) prev = prev.next;
            }
        }
        return dummy.next;
    }

    private ListNode splitInPlace(ListNode head, int size) {
        if (head == null) return null;
        ListNode curr = head;
        for (int i = 1; i < size && curr.next != null; i++) curr = curr.next;
        ListNode next = curr.next;
        curr.next = null;
        return next;
    }

    private ListNode mergeInPlace(ListNode left, ListNode right) {
        ListNode dummy = new ListNode(-1), tail = dummy;
        while (left != null && right != null) {
            if (left.val <= right.val) {
                tail.next = left;
                left = left.next;
            } else {
                tail.next = right;
                right = right.next;
            }
            tail = tail.next;
        }
        tail.next = (left != null) ? left : right;
        return dummy.next;
    }



    /**
     * Approach 5: Using Collections.sort with a Custom Comparator (Not truly in-place)
     * -  Copy the linked list nodes to a List.
     * -  Sort the List using Collections.sort and a custom comparator.
     * -  Reconstruct the linked list from the sorted List.
     * -  This approach leverages Java's sorting capabilities but isn't a true in-place linked list sort.
     *
     * Time Complexity: O(n log n) - Due to Collections.sort
     * Space Complexity: O(n) - To store the nodes in a List
     */
    public ListNode mergeSortWithCollections(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }

        // 1. Copy nodes to a List
        List<ListNode> nodes = new ArrayList<>();
        ListNode curr = head;
        while (curr != null) {
            nodes.add(curr);
            curr = curr.next;
        }

        // 2. Sort the List using Collections.sort and a custom comparator
        Collections.sort(nodes, Comparator.comparingInt(node -> node.val));

        // 3. Reconstruct the linked list
        for (int i = 0; i < nodes.size() - 1; i++) {
            nodes.get(i).next = nodes.get(i + 1);
        }
        nodes.get(nodes.size() - 1).next = null; // Ensure the last node's next is null

        return nodes.get(0); // The first node in the sorted list
    }


    // Utility function to print the linked list
    public void printLinkedList(ListNode head) {
        ListNode current = head;
        while (current != null) {
            System.out.print(current.val + " -> ");
            current = current.next;
        }
        System.out.println("null");
    }

    // Utility function to create a linked list from an array
    public ListNode createLinkedList(int[] arr) {
        if (arr == null || arr.length == 0) {
            return null;
        }
        ListNode head = new ListNode(arr[0]);
        ListNode current = head;
        for (int i = 1; i < arr.length; i++) {
            current.next = new ListNode(arr[i]);
            current = current.next;
        }
        return head;
    }

    public static void main(String[] args) {
        MergeSortLinkedList sorter = new MergeSortLinkedList();

        // Test case 1
        int[] arr1 = {5, 2, 8, 1, 9, 4, 7, 3, 6};
        ListNode head1 = sorter.createLinkedList(arr1);
        System.out.println("Original List 1:");
        sorter.printLinkedList(head1);

        // Test case 2: Already sorted
        int[] arr2 = {1, 2, 3, 4, 5};
        ListNode head2 = sorter.createLinkedList(arr2);
        System.out.println("\nOriginal List 2 (Sorted):");
        sorter.printLinkedList(head2);

        // Test case 3: Reverse sorted
        int[] arr3 = {5, 4, 3, 2, 1};
        ListNode head3 = sorter.createLinkedList(arr3);
        System.out.println("\nOriginal List 3 (Reverse Sorted):");
        sorter.printLinkedList(head3);

        // Test case 4: Duplicate values
        int[] arr4 = {5, 2, 8, 2, 9, 4, 8, 3, 6};
        ListNode head4 = sorter.createLinkedList(arr4);
        System.out.println("\nOriginal List 4 (Duplicates):");
        sorter.printLinkedList(head4);

        // Test case 5: Single element
        int[] arr5 = {5};
        ListNode head5 = sorter.createLinkedList(arr5);
        System.out.println("\nOriginal List 5 (Single Element):");
        sorter.printLinkedList(head5);

        // Test case 6: Empty list
        int[] arr6 = {};
        ListNode head6 = sorter.createLinkedList(arr6);
        System.out.println("\nOriginal List 6 (Empty List):");
        sorter.printLinkedList(head6);


        // Test each approach
        System.out.println("\n--- Test: Recursive Merge Sort ---");
        ListNode sortedList1 = sorter.mergeSortRecursive(head1);
        sorter.printLinkedList(sortedList1); // Should print sorted list

        System.out.println("\n--- Test: Iterative Merge Sort ---");
        ListNode sortedList2 = sorter.mergeSortIterative(head2);
        sorter.printLinkedList(sortedList2);

        System.out.println("\n--- Test: Merge Sort with Array ---");
        ListNode sortedList3 = sorter.mergeSortArray(head3);
        sorter.printLinkedList(sortedList3);

        System.out.println("\n--- Test: In-Place Merge Sort ---");
        ListNode sortedList4 = sorter.mergeSortInPlace(head4);
        sorter.printLinkedList(sortedList4);

        System.out.println("\n--- Test: Merge Sort with Collections ---");
        ListNode sortedList5 = sorter.mergeSortWithCollections(head5);
        sorter.printLinkedList(sortedList5);

        System.out.println("\n--- Test: Empty List ---");
        ListNode sortedList6 = sorter.mergeSortWithCollections(head6);
        sorter.printLinkedList(sortedList6);
    }
}

// Definition for singly-linked list.
class ListNode {
    int val;
    ListNode next;
    ListNode() {}
    ListNode(int val) { this.val = val; }
    ListNode(int val, ListNode next) { this.val = val; this.next = next; }
}

