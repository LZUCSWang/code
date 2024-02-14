#include<stdio.h>
#include<stdbool.h>
struct TreeNode {
    int val;
   struct TreeNode *left;
    struct TreeNode *right;
};
bool judge(struct TreeNode* left,struct TreeNode* right){
    if(left==NULL&&right==NULL)return true;
    if(left==NULL||right==NULL||right->val!=left->val)return false;
    return judge(left->left,right->right)&&judge(left->right,right->left);
}
bool isSymmetric(struct TreeNode* root){
    if(root==NULL)return true;
    return judge(root->left,root->right);
}