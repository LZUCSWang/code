/*
 * @Author: WangXianYi
 * @School: LZU
 * @Date: 2023-10-12 19:22:00
 * @Description: 
 */
#include <stdio.h>
#include <stdlib.h>

// ����������ṹ
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// �������ڴ����µĶ������ڵ�
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// �������ڹ��������������չǰ���������
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

// ��������ǰ�������������������
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// �����������������������������
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

// �������ں��������������������
void postorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
}

int main() {
    // ʾ����չǰ���������
    // int preorder[] = {1, 2, 4, -1, -1, 5, -1, -1, 3, 6, -1, -1, 7, -1, -1};
    int preorder[15];
    // ����preorder
    printf("��������չǰ���������: ");
    int i;
    for (i = 0; i < 15; i++) {
        scanf("%d", &preorder[i]);
    }
    int index = 0;

    // ����������
    struct TreeNode* root = buildTree(preorder, &index);

    printf("ǰ��������: ");
    preorderTraversal(root);
    printf("\n");

    printf("����������: ");
    inorderTraversal(root);
    printf("\n");

    printf("����������: ");
    postorderTraversal(root);
    printf("\n");
    // getchar();
    // getchar();
    return 0;
}
