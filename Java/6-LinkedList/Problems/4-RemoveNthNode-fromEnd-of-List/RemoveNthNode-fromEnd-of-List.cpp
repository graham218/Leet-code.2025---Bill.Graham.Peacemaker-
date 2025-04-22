// Definition for singly-linked list.
function ListNode(val, next) {
    this.val = (val===undefined ? 0 : val)
    this.next = (next===undefined ? null : next)
}

/**
 * Given the head of a linked list, remove the nth node from the end of the list and return its head.
 *
 * Example 1:
 * Input: head = [1,2,3,4,5], n = 2
 * Output: [1,2,3,5]
 *
 * Example 2:
 * Input: head = [1], n = 1
 * Output: []
 *
 * Example 3:
 * Input: head = [1,2], n = 1
 * Output: [1]
 */
/**
 * @param {ListNode} head
 * @param {number} n
 * @return {ListNode}
 */

// Approach 1: Two Pass
var removeNthFromEnd_twoPass = function(head, n) {
    if (!head) return null;

    let length = 0;
    let current = head;

    // First pass: Calculate the length of the linked list
    while (current) {
        length++;
        current = current.next;
    }

    // Handle the case where we need to remove the head
    if (n === length) {
        return head.next;
    }

    let prev = null;
    current = head;
    let count = 0;

    // Second pass: Find the node before the one to remove
    while (count < length - n) {
        prev = current;
        current = current.next;
        count++;
    }

    // Remove the nth node from the end
    prev.next = current.next;

    return head;
};

// Approach 2: Two Pointers (Fast and Slow)
var removeNthFromEnd_twoPointers = function(head, n) {
    if (!head) return null;

    let slow = head;
    let fast = head;

    // Move the fast pointer n steps ahead
    for (let i = 0; i < n; i++) {
        if (!fast) return head.next; // Handle the case where n is greater than the list length
        fast = fast.next;
    }

    // If fast reaches the end, we're removing the head
    if (!fast) {
        return head.next;
    }

    // Move both pointers until fast reaches the end
    while (fast.next) {
        slow = slow.next;
        fast = fast.next;
    }

    // Remove the nth node from the end
    slow.next = slow.next.next;

    return head;
};

// Approach 3: Recursive Approach
var removeNthFromEnd_recursive = function(head, n) {
    if (!head) {
        return { node: null, count: 0 };
    }

    const result = removeNthFromEnd_recursive(head.next, n);
    head.next = result.node;
    const count = result.count + 1;

    if (count === n) {
        return { node: head.next, count };
    }

    return { node: head, count };
};

var removeNthFromEnd_recursive_wrapper = function(head, n) {
    return removeNthFromEnd_recursive(head, n).node;
}


// Approach 4: Using a Dummy Node
var removeNthFromEnd_dummyNode = function(head, n) {
    const dummy = new ListNode(0);
    dummy.next = head;
    let slow = dummy;
    let fast = dummy;

    // Move fast pointer n steps ahead
    for (let i = 0; i < n; i++) {
        fast = fast.next;
    }

    // Move both pointers until fast reaches the end
    while (fast.next) {
        slow = slow.next;
        fast = fast.next;
    }

    // Remove the nth node from the end
    slow.next = slow.next.next;

    return dummy.next;
};

// Approach 5: Using Array
var removeNthFromEnd_array = function(head, n) {
    if (!head) return null;

    const nodes = [];
    let current = head;

    // Store all nodes in an array
    while (current) {
        nodes.push(current);
        current = current.next;
    }

    const length = nodes.length;
    if (n > length) return head;

    if (n === length) {
        return length === 1 ? null : head.next;
    }

    const prevIndex = length - n - 1;
    const currentIndex = length - n;

    nodes[prevIndex].next = nodes[currentIndex].next;

    return head;
};



// Helper function to create a linked list from an array
function createLinkedList(arr) {
    if (!arr || arr.length === 0) return null;
    let head = new ListNode(arr[0]);
    let current = head;
    for (let i = 1; i < arr.length; i++) {
        current.next = new ListNode(arr[i]);
        current = current.next;
    }
    return head;
}

// Helper function to convert a linked list to an array for easy printing
function linkedListToArray(head) {
    const result = [];
    let current = head;
    while (current) {
        result.push(current.val);
        current = current.next;
    }
    return result;
}

// Test cases
const testCases = [
    { arr: [1, 2, 3, 4, 5], n: 2 },
    { arr: [1], n: 1 },
    { arr: [1, 2], n: 1 },
    { arr: [1, 2, 3, 4, 5], n: 1 },
    { arr: [1, 2, 3, 4, 5], n: 5 },
    { arr: [1,2], n: 2},
    { arr: [1,2,3], n: 3}
];

console.log("Test Cases and Outputs:\n");
testCases.forEach((test, index) => {
    const { arr, n } = test;
    const head = createLinkedList(arr);

    // Create a copy of the linked list for each approach to avoid modification issues
    const head1 = createLinkedList(arr);
    const head2 = createLinkedList(arr);
    const head3 = createLinkedList(arr);
    const head4 = createLinkedList(arr);
    const head5 = createLinkedList(arr);


    console.log(`\nTest Case ${index + 1}: Input: list = [${arr}], n = ${n}`);

    // Approach 1: Two Pass
    const result1 = removeNthFromEnd_twoPass(head1, n);
    console.log("Approach 1: Two Pass:", linkedListToArray(result1));

    // Approach 2: Two Pointers
    const result2 = removeNthFromEnd_twoPointers(head2, n);
    console.log("Approach 2: Two Pointers:", linkedListToArray(result2));

    // Approach 3: Recursive
    const result3 = removeNthFromEnd_recursive_wrapper(head3, n);
    console.log("Approach 3: Recursive:", linkedListToArray(result3));

    // Approach 4: Dummy Node
    const result4 = removeNthFromEnd_dummyNode(head4, n);
    console.log("Approach 4: Dummy Node:", linkedListToArray(result4));

    // Approach 5: Array
    const result5 = removeNthFromEnd_array(head5, n);
    console.log("Approach 5: Array:", linkedListToArray(result5));
});
