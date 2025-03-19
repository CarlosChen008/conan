#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

bool hasCycle(ListNode *head) {
    if (head == NULL || head->next == NULL) {
        return false;
    }

    ListNode *slow = head;
    ListNode *fast = head->next;

    while (slow != fast) {
        if (fast == NULL || fast->next == NULL) {
            return false;
        }
        slow = slow->next;
        fast = fast->next->next;
    }

    return true;
}

int main() {
    // Example usage:
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = head; // Creates a cycle

    if (hasCycle(head)) {
        std::cout << "Cycle detected." << std::endl;
    } else {
        std::cout << "No cycle detected." << std::endl;
    }

    // Clean up memory (in a real scenario, ensure to handle cycles properly)
    delete head->next->next;
    delete head->next;
    delete head;

    return 0;
}