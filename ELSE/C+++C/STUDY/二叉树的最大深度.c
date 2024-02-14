#include<stdio.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
int maxDepth(struct TreeNode* root){
    if(root==NULL)return 0;
    int datas=maxDepth(root->left);
    int b=maxDepth(root->right);
    return (datas>b)?datas+1:b+1;
}