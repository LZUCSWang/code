#include<stdio.h>
#include<stdbool.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
bool judge(struct TreeNode* root,int min,int max){
    if(root==NULL)return true;
    if(root->val>=max||root->val<=min)return false;
    return judge(root->left,min,root->val)&&judge(root->right,root->val,max);
}
bool isValidBST(struct TreeNode* root){
    int min=-2147483649;
    int max=2147483648;
    return judge(root,min,max);
}