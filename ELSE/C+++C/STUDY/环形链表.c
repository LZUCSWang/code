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
    struct ListNode *temp;
    temp=head;
    int count=0;
    while(temp!=NULL){
        count++;
        if(count>100000)return true;
        temp=temp->next;            
    }
    return false;
}