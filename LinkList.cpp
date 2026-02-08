#include<cstdlib>

typedef struct LNode {
	int data;
	struct LNode* next;
}LNode, * LinkList;

// 单链表的初始化（带头结点）
bool InitList(LinkList& L)
{
	L = (LNode*)malloc(sizeof(LNode));
	L->next = NULL;
	return true;
}

// 单链表的初始化（不带头节点）
bool InitList(LinkList& L)
{
	L = (LNode*)malloc(sizeof(LNode));
	L = NULL;
	return true;
}

// 单链表的后插
bool ListInsert(LinkList& L, int i, int e)
{
	LNode* p = L;
	int j = 0;
	while (p != NULL && j < i - 1) // 循环找到第i-1个结点
	{
		p = p->next;
		j++;
	}
	
	if (p == NULL)
		return false;

	LNode* s = (LNode*)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}

// 单链表的前插
bool InsertPriorNode(LNode* p, int e)
{
	if (p == NULL)
		return false;

	LNode* s = (LNode*)malloc(sizeof(LNode));
	s->next = p->next;
	p->next = s;
	s->data = p->data;
	p->data = e; //前插入的结点变成p，原先被前插的结点变成s
	return true;
}

// 单链表删除结点
bool ListDelete(LinkList& L, int i, int& e)
{
	if (i < 0)
		return false;
	LNode* p = L;
	int j = 0;// j为一个计数器 记录结点指针p走的轨迹
	while (p != NULL && j < i - 1)//找到第i-1个结点
	{
		p = p->next;
		j++;
	}
	
	if (p == NULL)
		return false;
	if (p->next == NULL)
		return false;
	
	LNode* q = p->next;
	e = q->data;
	p->next = q->next;
	
	free(q);
	return true;
}

// 单链表删除指定的结点
bool DeleteNode(LNode* p)
{
	if (p == NULL)
		return false;
	LNode* q = p->next;
	p->data = p->next->data;
	p->next = q->next;
	free(q);
	return true;
}

// 求单链表表长
int Length(LinkList& L)
{
	int len = 0;
	LNode* p = L;
	while (p->next != NULL)
	{
		p = p->next;
		len++;
	}

	return len;
}

// 单链表按位查找
LNode* GetElem(const LinkList& L, int i)
{
	if (i < 0)
		return NULL;
	LNode* p = L;
	int j = 0;
	while (p != NULL && j < i)// 找到第i个结点，其中头结点是第0个结点
	{
		p = p->next;
		j++;
	}
	return p;
}

// 单链表按值查找
LNode* LocateElem(const LinkList& L, int& e)
{
	LNode* p = L->next;
	while (p != NULL && p->data != e)
		p = p->next;
	return p; //返回该节点指针
} 

