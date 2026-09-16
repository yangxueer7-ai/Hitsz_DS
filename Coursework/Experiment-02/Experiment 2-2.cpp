// ===========题目2 二叉树的镜像核计数=================
/*
题目思路：
本题输入的是一棵二叉树的前序序列，其中 # 表示空结点。
普通前序序列无法唯一确定一棵二叉树，因为无法判断某个结点的孩子在左边还是右边。
本题的前序序列中 包含 # 表示空结点，因此每个结点的左右孩子位置都被明确标出。
所以可以仅根据这条带空结点标记的前序序列，递归构造出唯一的二叉树。

构造二叉树时，每次读取一个字符串：如果读到 #，说明当前结点为空，返回 NULL；
否则将该字符串转为整数，创建新结点，然后递归构造它的左子树和右子树。

建树完成后，定义 isMirror 函数判断两棵树是否互为镜像：
若两棵树都为空，则是镜像；
若只有一棵为空，或两个根结点值不同，则不是镜像；
否则递归判断第一棵树的左子树是否与第二棵树的右子树镜像，以及第一棵树的右子树是否与第二棵树的左子树镜像。

最后遍历整棵二叉树，对每个结点判断：
如果该结点的左子树和右子树互为镜像，
则该结点为“镜像核”，计数加一。
递归统计所有结点后，输出镜像核结点总数。
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode, * BiTree;

// 根据前序序列构造二叉树，# 表示空结点
TreeNode* buildTree() {
    char str[50];

    if (scanf("%s", str) == EOF) {
        return NULL;
    }

    if (strcmp(str, "#") == 0) {
        return NULL;
    }

    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = atoi(str);

    root->left = buildTree();
    root->right = buildTree();
    return root;
}

// 判断两棵二叉树是否互为镜像
int isMirror(TreeNode* T1, TreeNode* T2) {
    // 两棵树都为空，互为镜像
    if (T1 == NULL && T2 == NULL) {
        return 1;
    }

    // 一个为空，一个不为空，不是镜像
    if (T1 == NULL || T2 == NULL) {
        return 0;
    }

    // 根结点值不同，不是镜像
    if (T1->val != T2->val) {
        return 0;
    }

    // 递归判断：
    // T1 的左子树和 T2 的右子树互为镜像
    // T1 的右子树和 T2 的左子树互为镜像
    return isMirror(T1->left, T2->right) &&
        isMirror(T1->right, T2->left);
}

// 统计镜像核结点数量
int countMirrorCore(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    int count = 0;

    // 当前结点的左右子树互为镜像，则当前结点是镜像核
    if (isMirror(root->left, root->right)) {
        count++;
    }

    count += countMirrorCore(root->left);
    count += countMirrorCore(root->right);

    return count;
}

// 释放二叉树
void freeTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
