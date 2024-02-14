#include<stdio.h>
#include<stdlib.h>
struct ListNode {
    int val;
    struct ListNode *next;
};


struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){
    struct ListNode* head=(struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* pleft=list1;
    struct ListNode* pright=list2;
    struct ListNode* p=head;
    p->next=NULL;
    while(pleft&&pright){
        if(pleft->val>pleft->val){
            p->next=pleft;
            pleft=pleft->next;
            p=p->next;
        }
        else{
            p->next=pright;
            pright=pright->next;
            p=p->next;
        }
    }
    if(pleft){
        p->next=pleft;
    }
    else{
        p->next=pright;
    }
    return head->next;
    
}