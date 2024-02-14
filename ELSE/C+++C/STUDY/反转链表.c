#include<stdio.h>
struct ListNode {
    int val;
    struct ListNode *next;
};
struct ListNode* reverseList(struct ListNode* head){
    struct ListNode *cnt=head;
    struct ListNode *left=NULL;
    struct ListNode *right=NULL;
    while(cnt){
        left=cnt;
        cnt=cnt->next;
        left->next=right;
        right=left;
    }
    return right;
}
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* cnt = head;
    struct ListNode* left = NULL;
    struct ListNode* right = NULL;
    while(cnt){ 
        left = cnt;
        cnt = cnt -> next;
        left -> next = right;
        right = left;
    }
    return right;
}