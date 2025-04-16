/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 * this.val = (val === undefined ? 0 : val);
 * this.next = (next === undefined ? null : next);
 * }
 */
/**
 * @param {ListNode} head
 * @param {number} n
 * @return {ListNode}
 */

// Helper function to create a linked list from an array (for testing)
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

// Helper function to convert a linked list to an array (for testing)
function linkedListToArray(head) {
    const result = [];
    let current = head;
    while (current) {
        result.push(current.val);
        current = current.next;
    }
    return result;
}

// Helper function to print the linked list
function printLinkedList(head) {
    let current = head;
    let result = "";
    while (current) {
        result += current.val + " -> ";
        current = current.next;
    }
    result += "null";
    console.log(result);
}

// Approach 1: Two Pass - Calculate Length
var removeNthFromEnd_TwoPass = function (head, n) {
    if (!head) return null;

    let length = 0;
    let current = head;
    while (current) {
        length++;
        current = current.next;
    }

    if (n > length) return head; // Handle invalid input
    if (n === length) return head.next; // Remove head

    const target = length - n;
    current = head;
    for (let i = 0; i < target - 1; i++) {
        current = current.next;
    }
    current.next = current.next.next;

    return head;
};

// Approach 2: Two Pointers - Fast and Slow
var removeNthFromEnd_TwoPointers = function (head, n) {
    if (!head) return null;

    let fast = head;
    let slow = head;

    // Move fast pointer n steps ahead
    for (let i = 0; i < n; i++) {
        if (!fast) return head; // Handle invalid n
        fast = fast.next;
    }

    // If fast reaches the end, remove the head
    if (!fast) return head.next;

    // Move both pointers until fast reaches the end
    while (fast.next) {
        fast = fast.next;
        slow = slow.next;
    }

    slow.next = slow.next.next;
    return head;
};

// Approach 3: Recursive Approach
var removeNthFromEnd_Recursive = function (head, n) {
    if (!head) {
        return { node: null, count: 0 };
    }

    const result = removeNthFromEnd_Recursive(head.next, n);
    head.next = result.node;
    const count = result.count + 1;

    if (count === n) {
        return { node: head.next, count: count };
    } else {
        return { node: head, count: count };
    }
};


var removeNthFromEnd_RecursiveWrapper = function (head, n) {
    return removeNthFromEnd_Recursive(head, n).node;
}


// Approach 4: Using a Dummy Node
var removeNthFromEnd_DummyNode = function (head, n) {
    const dummy = new ListNode(0);
    dummy.next = head;
    let fast = dummy;
    let slow = dummy;

    for (let i = 0; i < n; i++) {
        fast = fast.next;
    }

    while (fast.next) {
        fast = fast.next;
        slow = slow.next;
    }

    slow.next = slow.next.next;
    return dummy.next;
};

// Approach 5: Stack Approach
var removeNthFromEnd_Stack = function (head, n) {
    if (!head) return null;

    const stack = [];
    let current = head;

    while (current) {
        stack.push(current);
        current = current.next;
    }

    if (n > stack.length) return head;

    if (n === stack.length) return head.next;

    let target = stack.length - n;
    let prev = stack[target - 1];
    prev.next = prev.next.next;

    return head;
};



// Test Cases
function runTestCases() {
    let head1 = createLinkedList([1, 2, 3, 4, 5]);
    let n1 = 2;
    console.log("Test Case 1:");
    console.log("Input List:", linkedListToArray(head1), "n =", n1);

    let head2 = createLinkedList([1]);
    let n2 = 1;
    console.log("\nTest Case 2:");
    console.log("Input List:", linkedListToArray(head2), "n =", n2);

    let head3 = createLinkedList([1, 2]);
    let n3 = 1;
    console.log("\nTest Case 3:");
    console.log("Input List:", linkedListToArray(head3), "n =", n3);

    let head4 = createLinkedList([1, 2, 3, 4, 5]);
    let n4 = 5;
    console.log("\nTest Case 4:");
    console.log("Input List:", linkedListToArray(head4), "n =", n4);

    let head5 = createLinkedList([1, 2, 3, 4, 5]);
    let n5 = 1;
    console.log("\nTest Case 5:");
    console.log("Input List:", linkedListToArray(head5), "n =", n5);

    console.log("\n--- Approach 1: Two Pass ---");
    let result1_1 = removeNthFromEnd_TwoPass(createLinkedList([1, 2, 3, 4, 5]), 2);
    console.log("Output:", linkedListToArray(result1_1));
    let result1_2 = removeNthFromEnd_TwoPass(createLinkedList([1]), 1);
    console.log("Output:", linkedListToArray(result1_2));
    let result1_3 = removeNthFromEnd_TwoPass(createLinkedList([1, 2]), 1);
    console.log("Output:", linkedListToArray(result1_3));
    let result1_4 = removeNthFromEnd_TwoPass(createLinkedList([1, 2, 3, 4, 5]), 5);
    console.log("Output:", linkedListToArray(result1_4));
    let result1_5 = removeNthFromEnd_TwoPass(createLinkedList([1, 2, 3, 4, 5]), 1);
    console.log("Output:", linkedListToArray(result1_5));

    console.log("\n--- Approach 2: Two Pointers ---");
    let result2_1 = removeNthFromEnd_TwoPointers(createLinkedList([1, 2, 3, 4, 5]), 2);
    console.log("Output:", linkedListToArray(result2_1));
    let result2_2 = removeNthFromEnd_TwoPointers(createLinkedList([1]), 1);
    console.log("Output:", linkedListToArray(result2_2));
    let result2_3 = removeNthFromEnd_TwoPointers(createLinkedList([1, 2]), 1);
    console.log("Output:", linkedListToArray(result2_3));
    let result2_4 = removeNthFromEnd_TwoPointers(createLinkedList([1, 2, 3, 4, 5]), 5);
    console.log("Output:", linkedListToArray(result2_4));
    let result2_5 = removeNthFromEnd_TwoPointers(createLinkedList([1, 2, 3, 4, 5]), 1);
    console.log("Output:", linkedListToArray(result2_5));

    console.log("\n--- Approach 3: Recursive ---");
    let result3_1 = removeNthFromEnd_RecursiveWrapper(createLinkedList([1, 2, 3, 4, 5]), 2);
    console.log("Output:", linkedListToArray(result3_1));
    let result3_2 = removeNthFromEnd_RecursiveWrapper(createLinkedList([1]), 1);
    console.log("Output:", linkedListToArray(result3_2));
    let result3_3 = removeNthFromEnd_RecursiveWrapper(createLinkedList([1, 2]), 1);
    console.log("Output:", linkedListToArray(result3_3));
    let result3_4 = removeNthFromEnd_RecursiveWrapper(createLinkedList([1, 2, 3, 4, 5]), 5);
    console.log("Output:", linkedListToArray(result3_4));
    let result3_5 = removeNthFromEnd_RecursiveWrapper(createLinkedList([1, 2, 3, 4, 5]), 1);
    console.log("Output:", linkedListToArray(result3_5));

    console.log("\n--- Approach 4: Dummy Node ---");
    let result4_1 = removeNthFromEnd_DummyNode(createLinkedList([1, 2, 3, 4, 5]), 2);
    console.log("Output:", linkedListToArray(result4_1));
    let result4_2 = removeNthFromEnd_DummyNode(createLinkedList([1]), 1);
    console.log("Output:", linkedListToArray(result4_2));
    let result4_3 = removeNthFromEnd_DummyNode(createLinkedList([1, 2]), 1);
    console.log("Output:", linkedListToArray(result4_3));
    let result4_4 = removeNthFromEnd_DummyNode(createLinkedList([1, 2, 3, 4, 5]), 5);
    console.log("Output:", linkedListToArray(result4_4));
    let result4_5 = removeNthFromEnd_DummyNode(createLinkedList([1, 2, 3, 4, 5]), 1);
    console.log("Output:", linkedListToArray(result4_5));

    console.log("\n--- Approach 5: Stack ---");
    let result5_1 = removeNthFromEnd_Stack(createLinkedList([1, 2, 3, 4, 5]), 2);
    console.log("Output:", linkedListToArray(result5_1));
    let result5_2 = removeNthFromEnd_Stack(createLinkedList([1]), 1);
    console.log("Output:", linkedListToArray(result5_2));
    let result5_3 = removeNthFromEnd_Stack(createLinkedList([1, 2]), 1);
    console.log("Output:", linkedListToArray(result5_3));
    let result5_4 = removeNthFromEnd_Stack(createLinkedList([1, 2, 3, 4, 5]), 5);
    console.log("Output:", linkedListToArray(result5_4));
    let result5_5 = removeNthFromEnd_Stack(createLinkedList([1, 2, 3, 4, 5]), 1);
    console.log("Output:", linkedListToArray(result5_5));
}

// ListNode definition (Fix for the error)
function ListNode(val, next) {
    this.val = (val === undefined ? 0 : val);
    this.next = (next === undefined ? null : next);
}

runTestCases();
