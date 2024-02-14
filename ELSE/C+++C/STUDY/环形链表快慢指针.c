#include<stdio.h>
#include<stdbool.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
bool hasCycle(struct ListNode *head) {
    if(head==NULL)return false;
    if(head->next==NULL)return false;
    struct ListNode *low=head;
    struct ListNode *quick=head;
    while(quick!=NULL&&quick->next!=NULL){
        low=low->next;//for one steps
        quick=quick->next->next;//for two steps
        if(low==quick)return true;
    }
    return false;
}