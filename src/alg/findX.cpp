#include <iostream>
#include <unordered_set>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    std::unordered_set<ListNode*> nodes_in_B;
    while (headB != nullptr) {
        nodes_in_B.insert(headB);
        headB = headB->next;
    }
    while (headA != nullptr) {
        if (nodes_in_B.find(headA) != nodes_in_B.end()) {
            return headA;
        }
        headA = headA->next;
    }
    return nullptr;
}

int main() {
    // Example usage
    ListNode *common = new ListNode(8);
    common->next = new ListNode(10);

    ListNode *headA = new ListNode(3);
    headA->next = new ListNode(7);
    headA->next->next = common;

    ListNode *headB = new ListNode(99);
    headB->next = new ListNode(1);
    headB->next->next = common;

    ListNode *intersection = getIntersectionNode(headA, headB);
    if (intersection) {
        std::cout << "Intersection at node with value: " << intersection->val << std::endl;
    } else {
        std::cout << "No intersection found." << std::endl;
    }

    // Clean up memory
    delete headA->next->next; // common
    delete headA->next;
    delete headA;
    delete headB->next;
    delete headB;

    return 0;
}