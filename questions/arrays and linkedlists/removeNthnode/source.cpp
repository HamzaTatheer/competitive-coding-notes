/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {    
        ListNode* n1 = head;
        ListNode* n2 = head;
        while(n != 0){
            n2 = n2->next;
            n = n -1;
        }
        
        if(n2 == nullptr)
            return head->next;
        
        while(n2->next != nullptr){
            n1 = n1->next;
            n2 = n2->next;
        }
        n1->next = n1->next->next;        
        return head;
    }
};