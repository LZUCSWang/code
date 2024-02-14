/*
 * @Author: WangXianYi
 * @School: LZU
 * @Date: 2023-10-12 19:22:00
 * @Description: 
 */
#include <stdio.h>
#include <stdlib.h>

// 定义二叉树结构
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 函数用于创建新的二叉树节点
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 函数用于构造二叉树根据扩展前序遍历序列
struct TreeNode* buildTree(int* preorder, int* index) {
    if (preorder[*index] == -1) {
        (*index)++;
        return NULL;
    }

    struct TreeNode* root = createNode(preorder[(*index)++]);
    root->left = buildTree(preorder, index);
    root->right = buildTree(preorder, index);

    return root;
}

// 函数用于前序遍历二叉树并输出结果
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// 函数用于中序遍历二叉树并输出结果
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

// 函数用于后序遍历二叉树并输出结果
void postorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
}

int main() {
    // 示例扩展前序遍历序列
    // int preorder[] = {1, 2, 4, -1, -1, 5, -1, -1, 3, 6, -1, -1, 7, -1, -1};
    int preorder[15];
    // 输入preorder
    printf("请输入扩展前序遍历序列: ");
    int i;
    for (i = 0; i < 15; i++) {
        scanf("%d", &preorder[i]);
    }
    int index = 0;

    // 构建二叉树
    struct TreeNode* root = buildTree(preorder, &index);

    printf("前序遍历结果: ");
    preorderTraversal(root);
    printf("\n");

    printf("中序遍历结果: ");
    inorderTraversal(root);
    printf("\n");

    printf("后序遍历结果: ");
    postorderTraversal(root);
    printf("\n");
    // getchar();
    // getchar();
    return 0;
}
