// ========= 根据前序与中序遍历序列构造二叉树==========
/*
本题要求根据二叉树的前序遍历序列和中序遍历序列构造二叉树，
并使用层次遍历输出二叉树，空结点用 null 表示。
1. 前序遍历的顺序是：根结点 -> 左子树 -> 右子树，
   因此前序序列的第一个元素一定是当前子树的根结点。

2. 中序遍历的顺序是：左子树 -> 根结点 -> 右子树，
   所以在中序序列中找到根结点后， 根结点左边的元素属于左子树， 根结点右边的元素属于右子树。

3. 根据中序序列中根结点的位置，可以得到左子树结点个数 leftSize
   和右子树结点个数 rightSize。
   然后分别确定左右子树在前序和中序序列中的范围，
   递归调用 buildTree 构造左右子树。

4. 二叉树构造完成后，使用队列进行层次遍历。
   每次从队列中取出一个结点：
   如果该结点为空，则输出 null；
   如果该结点不为空，则输出结点值，并将它的左右孩子入队。

5. 由于题目要求输出空结点，因此真实结点的左右孩子即使为空，
   也需要加入队列，等出队时输出 null。
*/
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 创建一个新的树结点
struct TreeNode* createNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    if (preorderSize == 0 || inorderSize == 0) {
        return NULL;
    }

    // 找到根结点---前序遍历的第一个元素是根结点
    int rootVal = preorder[0];
    struct TreeNode* root = createNode(rootVal);

    // 中序遍历--找到根结点的位置
    int rootIndex = 0;
    for (int i = 0; i < inorderSize; i++) {
        if (inorder[i] == rootVal) {
            rootIndex = i;// 根节点的位置！
            break;
        }
    }

    // rootIndex 左边是左子树，右边是右子树
    int leftSize = rootIndex;
    int rightSize = inorderSize - rootIndex - 1;

    // 构造左子树
    root->left = buildTree(
        preorder + 1,
        leftSize,
        inorder,
        leftSize
    );

    // 构造右子树
    root->right = buildTree(
        preorder + 1 + leftSize,
        rightSize,
        inorder + rootIndex + 1,
        rightSize
    );

    return root;
}

void printTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // 存放结点指针的数组队列
    struct TreeNode** queue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * 10005);
    int front = 0;
    int rear = 0;

    // 根结点入队
    queue[rear++] = root;

    while (front < rear) {
        // 队首元素出队 记为cur
        struct TreeNode* cur = queue[front++];
        if (cur == NULL) {
            printf("null");
        }
        else {
            printf("%d", cur->val);
            //左右孩子入队
            queue[rear++] = cur->left;
            queue[rear++] = cur->right;
        }
    }

    free(queue);
}