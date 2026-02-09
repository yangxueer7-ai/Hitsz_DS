#include "LinkList.h"

// 默认规则：
// 1) 单链表默认带头结点(除非标注了），L 指向头结点，空表 L->next == NULL
// 2) 数据位序从 1 开始（第1个数据结点），头结点视为位序0 但不对外暴露
// 3) Length 返回数据结点个数，不包含头结点


// ====================== 单链表 ======================

// 单链表的初始化（带头结点）
bool InitListWithHead(LinkList& L)
{
	L = (LNode*)malloc(sizeof(LNode));
	L->next = NULL;
	return true;
}

// 单链表的初始化（不带头节点）
bool InitListNoHead(LinkList& L)
{
	L = NULL;
	return true;
}


// 单链表的后插(带头结点）
bool ListInsert(LinkList& L, int i, int e)
{
	if (i < 1)
		return false;
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

// 单链表的后插（不带头节点）
bool ListInsertNULL(LinkList& L, int i, int e)
{
	if (i < 1)
		return false;
	LNode* p = L;
	int j = 0;
	LNode* s = (LNode*)malloc(sizeof(LNode));
	s->data = e;
	if (i == 1)
	{
		s->next = L;
		L = s;
		return true;//如果插入第一个结点 新插入的结点直接取代原先的L 改变入口指针
	}
	while (p != NULL && j < i - 1) // 循环找到第i-1个结点
	{
		p = p->next;
		j++;
	}

	if (p == NULL)
		return false;

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
	if (i < 1)
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
	if (p == NULL||p->next == NULL)
		return false;
	LNode* q = p->next;
	p->data = q->data;
	p->next = q->next;
	free(q);
	return true;
}


// 求单链表表长
int Length(const LinkList& L)
{
	int len = 0;
	for (LNode* p = L->next; p != NULL; p = p->next)
		len++;
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
LNode* LocateElem(const LinkList& L, int e)
{
	LNode* p = L->next;// 结点指针p从第一个结点开始 因为后面有p->data
	while (p != NULL && p->data != e)
		p = p->next;
	return p; //返回该结点指针
} 

// 单链表的建立--头插法
LinkList List_HeadInsert(LinkList& L)
{
	LNode* s;
	int x;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	scanf("%d", &x);
	while (x != 9999)
	{
		s = (LNode*)malloc(sizeof(LNode));
		s->data = x;
		s->next = L->next;
		L->next = s;
		scanf("%d", &x);
	}
	return L;
}

// 单链表的建立--尾插法
LinkList List_TailInsert(LinkList& L)
{
	int x;
	L = (LinkList)malloc(sizeof(LNode));
	LNode* s, * r = L;// r为表尾指针,始终指向最后一个结点，每插入一个向后移动一位
	scanf("%d", &x);
	while (x != 9999)
	{
		s = (LNode*)malloc(sizeof(LNode));
		s->data = x;
		r->next = s;
		r = s;
		scanf("%d", &x);
	}
	r->next = NULL;
	return L;
}

// ====================== 双链表 ======================

// 双链表的后插
bool InsertNextDNode(DNode* p, DNode* s)
{
	if (p == NULL || s == NULL)
		return false;
	
	s->next = p->next;
	if (p->next != NULL)
		p->next->prior = s;
	s->prior = p;
	p->next = s;
	return true;
}

// 双链表的前插
bool InsertPriorDNode(DNode* p, DNode* s)
{
	if (p == NULL || s == NULL)
		return false;
	DNode* q = p->prior;//对q实现后插，即对p实现前插
	if (q == NULL)
		return false;
	s->next = q->next;
	q->next->prior = s;
	s->prior = q;
	q->next = s;
	return true;
}

// 双链表的删除操作
bool DeleteNextDNode(DNode* p)//删除的是传入的p的下一个结点
{
	if (p == NULL || p->next == NULL)
		return false;
	DNode* q = p->next;
	if (q->next == NULL)
		return false;
	p->next = q->next;
	q->next->prior = p;
	
	free(q);
	return true;
}

// 双链表的摧毁操作
void DestroyDLinkList(DLinkList& L)
{
	while (L->next != NULL)
		DeleteNextDNode(L);
	free(L);
	L = NULL;
}

// ====================== 循环链表 ======================

// 循环单链表的初始化
bool InitCircularList(LinkList& L)
{
	L = (LNode*)malloc(sizeof(LNode));
	if (L == NULL)
		return false;
	
	L->next = L;
	return true;
}

// 循环双链表的删除
bool DeleteCircularDNode(DNode* p)
{
	if (p == NULL )
		return false;
	DNode* q = p->next;
	if (q == p)
		return false;
	p->next = q->next;
	q->next->prior = p;
	free(q);
	return true;
}
