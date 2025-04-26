// Problem: Remove Nth Node from End of List
// LeetCode Problem Link: https://leetcode.com/problems/remove-nth-node-from-end-of-list/

#include <iostream>
#include <stack>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// ----------- Approach 1: Two Passes (First count nodes, then remove target) -----------
class Solution_TwoPass {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int length = 0;
        ListNode* temp = head;
        while (temp) {
            length++;
            temp = temp->next;
        }
        if (length == n) {
            ListNode* newHead = head->next;
            delete head;
            return newHead;
        }
        temp = head;
        for (int i = 1; i < length - n; i++) {
            temp = temp->next;
        }
        ListNode* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        return head;
    }
};

// ----------- Approach 2: One Pass (Two pointers technique) -----------
class Solution_OnePass {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);
        ListNode* fast = dummy;
        ListNode* slow = dummy;
        for (int i = 0; i <= n; ++i) {
            fast = fast->next;
        }
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }
        ListNode* toDelete = slow->next;
        slow->next = slow->next->next;
        delete toDelete;
        ListNode* newHead = dummy->next;
        delete dummy;
        return newHead;
    }
};

// ----------- Approach 3: Recursive Method -----------
class Solution_Recursive {
private:
    int counter;
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        counter = n;
        ListNode* node = recursive(head);
        if (counter == 0) {
            ListNode* temp = head->next;
            delete head;
            return temp;
        }
        return head;
    }
    ListNode* recursive(ListNode* node) {
        if (!node) return nullptr;
        node->next = recursive(node->next);
        counter--;
        if (counter == 0) {
            ListNode* temp = node->next;
            delete node;
            return temp;
        }
        return node;
    }
};

// ----------- Approach 4: Stack Based Method -----------
class Solution_StackBased {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        stack<ListNode*> st;
        ListNode* dummy = new ListNode(0, head);
        ListNode* temp = dummy;
        while (temp) {
            st.push(temp);
            temp = temp->next;
        }
        for (int i = 0; i < n; ++i) {
            st.pop();
        }
        ListNode* prev = st.top();
        ListNode* toDelete = prev->next;
        prev->next = prev->next->next;
        delete toDelete;
        ListNode* newHead = dummy->next;
        delete dummy;
        return newHead;
    }
};

// ----------- Approach 5: Length Precomputed and Prechecked -----------
class Solution_LengthValidated {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (!head) return nullptr;
        int length = getLength(head);
        if (n > length) return head;
        ListNode* dummy = new ListNode(0, head);
        ListNode* temp = dummy;
        for (int i = 0; i < length - n; ++i) {
            temp = temp->next;
        }
        ListNode* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        ListNode* newHead = dummy->next;
        delete dummy;
        return newHead;
    }
private:
    int getLength(ListNode* head) {
        int length = 0;
        while (head) {
            length++;
            head = head->next;
        }
        return length;
    }
};

// ------------------ Helper Functions ------------------
void printList(ListNode* head) {
    while (head) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

ListNode* createSampleList() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    return head;
}

// ------------------ Main ------------------
int main() {
    int n = 2;

    // Two Pass
    ListNode* head1 = createSampleList();
    Solution_TwoPass sol1;
    cout << "Two Pass Solution: ";
    head1 = sol1.removeNthFromEnd(head1, n);
    printList(head1);

    // One Pass
    ListNode* head2 = createSampleList();
    Solution_OnePass sol2;
    cout << "One Pass Solution: ";
    head2 = sol2.removeNthFromEnd(head2, n);
    printList(head2);

    // Recursive
    ListNode* head3 = createSampleList();
    Solution_Recursive sol3;
    cout << "Recursive Solution: ";
    head3 = sol3.removeNthFromEnd(head3, n);
    printList(head3);

    // Stack Based
    ListNode* head4 = createSampleList();
    Solution_StackBased sol4;
    cout << "Stack Based Solution: ";
    head4 = sol4.removeNthFromEnd(head4, n);
    printList(head4);

    // Length Validated
    ListNode* head5 = createSampleList();
    Solution_LengthValidated sol5;
    cout << "Length Validated Solution: ";
    head5 = sol5.removeNthFromEnd(head5, n);
    printList(head5);

    return 0;
}
