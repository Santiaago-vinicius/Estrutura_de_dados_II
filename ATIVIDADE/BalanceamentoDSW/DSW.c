#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* createVine(TreeNode* root) {
    TreeNode* vine = NULL;
    TreeNode* tail = root;

    while (tail != NULL) {
        if (tail->left != NULL) {
            TreeNode* node = tail->left;
            tail->left = node->right;
            node->right = tail;
            tail = node;
        } else {
            vine = tail;
            tail = tail->right;
        }
    }

    return vine;
}

int countNodes(TreeNode* root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

void compress(TreeNode* vine, int count) {
    TreeNode* current = vine;
    for (int i = 0; i < count; i++) {
        TreeNode* child = current->right;
        current->right = child->right;
        current = current->right;
        child->right = current->left;
        current->left = child;
    }
}

TreeNode* balanceDSW(TreeNode* root) {
    TreeNode* vine = createVine(root);
    int n = countNodes(vine);
    int m = pow(2, (int)log2(n + 1)) - 1;
    compress(vine, n - m);

    while (m > 1) {
        m = m / 2;
        compress(vine, m);
    }

    return vine;
}

void printInorder(TreeNode* node) {
    if (node == NULL)
        return;

    printInorder(node->left);
    printf("%d ", node->val);
    printInorder(node->right);
}

void freeTree(TreeNode* node) {
    if (node == NULL)
        return;

    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main() {
    TreeNode* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->left = createNode(12);
    root->right->right = createNode(17);

    printf("Árvore binária original:\n");
    // Imprime a árvore original
    //        10
    //       /  \
    //      5    15
    //     / \  /  \
    //    3  7 12  17

    TreeNode* balancedRoot = balanceDSW(root);

    printf("Árvore binária balanceada:\n");
    // Imprime a árvore balanceada
    //        10
    //       /  \
    //      5    15
    //     /    /  \
    //    3   12   17
    //     \
    //      7

    printInorder(balancedRoot);
    printf("\n");

    freeTree(balancedRoot);

    return 0;
}
