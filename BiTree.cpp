#include <cstdlib>
#include <stdio.h>
#include <iostream>
#define MAXSIZE 100

// 二叉树的结点（链式存储）
typedef struct BiTNode {
	int data;
	struct BiTNode* lchild, * rchild; //左右孩子指针
}BiTNode, * BiTree;

// 二叉树的构建
void CreateBiTree(BiTree& T) {
	int x;
	if (scanf_s("%d", &x) != 1)
		return;
	if (x == 9999)
		T = NULL;
	else {
		T = (BiTNode*)malloc(sizeof(BiTNode));
		if (T == NULL)
			return;
		T->data = x;
		T->lchild = NULL;
		T->rchild = NULL;

		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}

// 二叉树结点的访问
void visit(BiTree T) {
	std::cout << T->data << " ";
}

// 二叉树求深度 类后序遍历的递归算法~
int BiTreeDepth(BiTree T) {
	if (T == NULL)
		return 0;
	else {
		int ldepth = BiTreeDepth(T->lchild);
		int rdepth = BiTreeDepth(T->rchild);

		return ldepth > rdepth ? ldepth + 1 : rdepth + 1;
	}
}

// 二叉树的先序遍历
bool PreOrder(BiTree T) {
	if (T == NULL)
		return false;
	else {
		visit(T);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
		return true;
	}
}

// 二叉树的中序遍历
bool Inorder(BiTree T) {
	if (T == NULL)
		return false;
	else {
		Inorder(T->lchild);
		visit(T);
		Inorder(T->rchild);
		return true;
	}
}

// 二叉树的后序遍历
bool PostOrder(BiTree T) {
	if (T == NULL)
		return false;
	else {
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		visit(T);
		return true;
	}
}

// ================== 存 BiTree 的链式队列 ==================
typedef struct LinkNode {
	BiTree data;
	struct LinkNode* next;
} LinkNode;

typedef struct {
	LinkNode* front;
	LinkNode* rear;
} LinkQueue;

// 初始化队列：带头结点
void InitQueue(LinkQueue& Q) {
	Q.front = Q.rear = (LinkNode*)malloc(sizeof(LinkNode));
	Q.front->next = nullptr;
}

// 判断队空
bool QueueEmpty(const LinkQueue& Q) {
	return Q.front == Q.rear;
}

// 入队
bool EnQueue(LinkQueue& Q, BiTree x) {
	LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
	if (s == nullptr)
		return false;

	s->data = x;
	s->next = nullptr;
	Q.rear->next = s;
	Q.rear = s;
	return true;
}


// 出队
bool DeQueue(LinkQueue& Q, BiTree& x) {
	if (QueueEmpty(Q))
		return false;
	LinkNode* p = Q.front->next;
	x = p->data;
	Q.front->next = p->next;

	// 如果删除的是最后一个结点，需要更新 rear
	if (Q.rear == p)
		Q.rear = Q.front;
	free(p);
	return true;
}

// 二叉树的层序遍历
bool LevelOrder(BiTree T) {
	if (T == nullptr)
		return false;

	LinkQueue Q;
	InitQueue(Q);
	BiTree p;

	EnQueue(Q, T);   // 根结点入队

	while (!QueueEmpty(Q)) {
		DeQueue(Q, p);   // 队头结点出队
		visit(p);        // 访问该结点
		if (p->lchild != nullptr)
			EnQueue(Q, p->lchild);
		if (p->rchild != nullptr)
			EnQueue(Q, p->rchild);
	}

	return true;
}

// ================== 线索二叉树 ===================

// 线索二叉树的构建
typedef struct ThreadNode {
	int data;
	struct ThreadNode* lchild, * rchild;
	int ltag, rtag; // 0表示指向真正的孩子，1表示没有对应的孩子，指向前驱或后继
}ThreadNode, * ThreadBiTree;

ThreadNode* pre = NULL;

// 线索二叉树 进行中序线索化时访问结点 q
void visitInThreadNode(ThreadNode* q) {
	// q没有左孩子，建立前驱线索pre
	if (q->lchild == NULL) {
		q->lchild = pre;
		q->ltag = 1;
	}
	else {
		q->ltag = 0;
	}

	// pre没有右孩子，建立后继线索指向q
	if (pre != NULL && pre->rchild == NULL) {
		pre->rchild = q;
		pre->rtag = 1;
	}

	pre = q;
}

// 中序线索化
void InThread(ThreadBiTree T) {
	if (T != NULL) {
		InThread(T->lchild);
		visitInThreadNode(T);
		InThread(T->rchild);
	}
}

// 创建中序线索二叉树
void CreateInThread(ThreadBiTree T) {
	pre = NULL;
	if (T != NULL) {
		InThread(T);
		// 处理最后一个结点 
		// 如果最后一个结点没有右孩子，后继线索指向NULL，rtag置1
		if (pre != NULL && pre->rchild == NULL) {
			pre->rtag = 1;
		}
	}
}

// 线索二叉树 进行先序线索化时访问结点q
void visitPreThreadNode(ThreadNode* q) {
	if (q->lchild == NULL) {
		q->lchild = pre;
		q->ltag = 1;
	}
	else {
		q->ltag = 0;
	}

	if (pre != NULL && pre->rchild == NULL) {
		pre->rchild = q;
		pre->rtag = 1;
	}
	
	pre = q;
}

// 先序线索化
void PreThread(ThreadBiTree T) {
	if (T != NULL) {
		visitPreThreadNode(T);

		// 只有左子树是真正的孩子时，才递归线索化左子树
		if (T->ltag == 0)
			PreThread(T->lchild);

		if (T->rtag == 0)
			PreThread(T->rchild);
	}
}

// 创建先序线索二叉树
void CreatePreThread(ThreadBiTree T){
	pre = NULL;
	if (T != NULL) {
		PreThread(T);
		if (pre != NULL &&pre->rchild == NULL) {
			pre->rtag = 1;
			}
		}
}

// 在后序线索化过程中访问结点 q，建立 q 的前驱线索，并为 pre 建立后继线索
void visitPostThreadNode(ThreadBiTree q) {
	if (q->lchild == NULL) {
		q->lchild = pre;
		q->ltag = 1;
	}
	else {
		q->ltag = 0;
	}

	if (pre != NULL) {
		if (pre->rchild == NULL) {
			pre->rchild = q;
			pre->rtag = 1;
		}
		else {
			pre->rtag = 0;
		}
	}

	pre = q;
}

// 按后序遍历顺序对二叉树T进行线索化
void PostThread(ThreadBiTree T) {
	if (T != NULL) {
		PostThread(T->lchild);
		PostThread(T->rchild);
		visitPostThreadNode(T);
	}
}

// 创建以T为根的后序线索二叉树
void CreatePostThread(ThreadBiTree T) {
	pre = NULL;
	if (T != NULL) {
		PostThread(T);
		if (pre != NULL&& pre->rchild == NULL) {
			pre->rtag = 1;
		}
	}
}


//============以下传入的 p 为根节点 ======================
// FirstNode 最左下特殊点 LastNode 最右下特殊点
//=======================================================
// 正向遍历 寻找中序线索二叉树的后继
ThreadNode* FirstNode(ThreadNode* p) {
	while (p->ltag == 0)
		p = p->lchild;
	return p; // 找到最左下结点 即第一个被中序遍历的结点
}

ThreadNode* NextNode(ThreadNode* p) {
	if (p->rtag == 0) {
		// 有右子树时，返回右子树第一个结点
		return FirstNode(p->rchild);
	}

	else
		return p->rchild;
}

void visit(ThreadNode* T) {
	std::cout << T->data << " ";
}

// 中序线索二叉树的中序遍历
void InOrderByThread(ThreadNode* T) {
	for (ThreadNode* p = FirstNode(T); p != NULL; p = NextNode(p)) 
		
		visit(p);
}

// 逆向遍历 找到以p为根的子树中，最后一个被中序遍历的结点
ThreadNode* LastNode(ThreadNode* p) {
	while (p->rtag == 0)
		p = p->rchild;
	return p;
}

// 找到节点p的前驱结点
ThreadNode* PreNode(ThreadNode* p) {
	if (p->ltag == 0) {
		return LastNode(p->lchild);
	}// 有左子树时，返回左子树最后一个结点（左子树最右下），即为p的前驱
	else {
		return p->lchild; //否则，建立前驱线索并连接
	}
}

// 对中序线索二叉树进行逆向遍历
void ReverseInorder(ThreadNode* T) {
	for (ThreadNode* p = LastNode(T); p != NULL; p = PreNode(p)) {
		visit(p);
	}
}

// 先序线索二叉树找后继
ThreadNode* PreOrderNext(ThreadNode* p) {
	// p有左孩子
	if (p->ltag == 0)
		return p->lchild;
	// p无左孩子 无论有无右孩子，都返回右孩子（可能是线索，也可能是真正的右孩子）
	else {
		return p->rchild;
	}
}

// 定义一个存有父节点的三叉链表的线索二叉树
typedef struct ThreadNode_T {
	int data;
	struct ThreadNode_T* lchild;
	struct ThreadNode_T* rchild;
	struct ThreadNode_T* parent; //父结点指针
	int ltag, rtag;
} TreeNode_T, * BiTree_T;

ThreadNode_T* LastNode(ThreadNode_T* p) {
	while (p->rtag == 0)
		p = p->rchild;
	return p;
}


// 先序线索二叉树找前驱
ThreadNode_T* PreOrderPre(ThreadNode_T* p) {
	ThreadNode_T* parent = p->parent;
	if (parent == NULL)
		return NULL;
	// p无左孩子 直接返回线索
	if (p->ltag == 1)
		return p->lchild;
	// p有左孩子
	else {
		// p是父节点左孩子
		if (p == parent->lchild)
			return parent;
		// p是父节点右孩子，且父节点没有左孩子
		else if (p == parent->rchild && parent->ltag == 1)
			return parent;
		//p是父节点右孩子，父节点也有左孩子
		else if (p == parent->rchild && parent->ltag == 0) {
			return LastNode(parent->lchild);
		}
	}

	return NULL;
}

// 后序线索二叉树找前驱
ThreadNode* PostOrderPre(ThreadNode* p) {
	// p有右孩子，直接返回右孩子
	if (p->rtag == 0)
		return p->rchild;
	// p无右孩子，有左孩子，返回左孩子
	if (p->rtag == 1 && p->ltag == 0)
		return p->lchild;
	// p无右孩子无左孩子，返回线索
	else
		return p->lchild;
}

ThreadNode_T* FirstNode(ThreadNode_T* p) {
	while (p->ltag == 0)
		p = p->lchild;
	return p; // 找到最左下结点 即第一个被中序遍历的结点
}
// 后序线索二叉树找后继
ThreadNode_T* PostOrderNext(ThreadNode_T* p) {
	ThreadNode_T* parent = p->parent;
	// p为根节点，没有父母结点，直接返回空
	if (parent == NULL)
		return NULL;
	// p是父节点右孩子 或 p是父节点左孩子，且父节点没有右孩子
	// 都是直接返回父节点
	if (p == parent->rchild ||(p == parent->lchild && parent->rtag == 1))
		return parent;
	// p是父节点左孩子，父节点有右孩子，返回父节点右孩子的最左下第一个结点
	if (p == parent->lchild && parent->rtag == 0) {
		return FirstNode(parent->rchild);
	}

	return NULL;
}