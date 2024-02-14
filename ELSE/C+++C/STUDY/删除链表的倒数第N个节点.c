#include<stdio.h>
struct ListNode {
    int val;
    struct ListNode *next;
};
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

int nodelen(struct ListNode* head){
    int len=0;
    while(head!=NULL){
        len++;
        head=head->next;
    }
    return len;
}
struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    if(head->next=NULL)return NULL;
    struct ListNode*p1;
    p1=head;
    int last=len(head)-n;
    for(int i=0;i<last;i++){
        p1=p1->next;
    }
    p1->next=p1->next->next;
    return head;
}