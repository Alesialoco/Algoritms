#include <iostream>
#include <vector>
#include <queue>


struct ListNode {
    int val;
    ListNode* next;
    ListNode(int value) : val(value), next(nullptr) {}
};


ListNode* merge_lists(std::vector<ListNode*>& v) {
    auto cmp = [](ListNode* first, ListNode* second) { return first->val > second->val; };
    std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(cmp)> heap(cmp);
    for (ListNode* elem : v) {
        if (elem != nullptr) {
            heap.push(elem);
        }
    }
    
    ListNode additional(0);
    ListNode* now_node = &additional;
    while (!heap.empty()) {
        ListNode* min_node = heap.top();
        heap.pop();
        now_node->next = min_node;
        now_node = now_node->next;
        if (min_node->next != nullptr) {
            heap.push(min_node->next);
        }
    }
    return additional.next;
}



int main() {
    ListNode* list1 = new ListNode(0);
    list1->next = new ListNode(4);
    list1->next->next = new ListNode(10);

    ListNode* list2 = new ListNode(1);
    list2->next = new ListNode(3);
    list2->next->next = new ListNode(7);
    list2->next->next->next = new ListNode(9);
    list2->next->next->next->next = new ListNode(12);

    ListNode* list3 = new ListNode(2);
    list3->next = new ListNode(5);
    list3->next->next = new ListNode(6);
    list3->next->next->next = new ListNode(11);

    std::vector<ListNode*> lists = {list1, list2, list3};
    ListNode* unioun_list = merge_lists(lists);


    ListNode* additional = unioun_list;
    while (additional != nullptr) {
        std::cout << additional->val;
        if (additional->next != nullptr) {
            std::cout << " -> ";
        }
        additional = additional->next;
    }
    std::cout << std::endl;

    ListNode* head = unioun_list;
    while (head != nullptr) {
        ListNode* now_node = head;
        head = head->next;
        delete now_node;
    }
    return 0;
}