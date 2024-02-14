#include<stdio.h>
#include<stdbool.h>
struct ListNode {
    int val;
    struct ListNode *next;
};


bool isPalindrome(struct ListNode* head){
    int arr[100000],k=0;
    struct ListNode* temp=head;
    while(temp!=NULL){
        arr[k++]=temp->val;
        temp=temp->next;
    }
    int left=0,right=k-1;
    while(left<right){
        if(arr[left]!=arr[right])return false;
        left++,right--;
    }
    return true;
}