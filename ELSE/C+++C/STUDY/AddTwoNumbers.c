#include<stdio.h>
struct ListNode {
    int val;
    struct ListNode *next;
};
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct ListNode *head = NULL , *tail=NULL;
    int sum,up=0;
    while(l1||l2){
        int n1=(l1)?l1->val:0;
        int n2=(l2)?l2->val:0;
        int sum=n1+n2+up;
        if(!head){
            head=tail=malloc(sizeof(struct ListNode));
            tail->val=sum%10;
            tail->next=NULL;
        }
        else {
            tail->next=malloc(sizeof(struct ListNode));
            tail->next->val=sum%10;
            tail=tail->next;
            tail->next=NULL;
        }
        up=sum/10;
        if(l1)l1=l1->next;
        if(l2)l2=l2->next;
    }
    if(up>0){
        tail->next=malloc(sizeof(struct ListNode));
        tail->next->val=up;
        tail->next->next=NULL;
    }
    return head;
}