#pragma once

#include <cstdlib>
#include <cstdio>

#define MaxSize 100

// 默认规则：
// 1) 单链表默认带头结点(除非标注了），L 指向头结点，空表 L->next == NULL
// 2) 数据位序从 1 开始（第1个数据结点），头结点视为位序0 但不对外暴露
// 3) Length 返回数据结点个数，不包含头结点

// ====================== 单链表 ======================

// 单链表结点定义
typedef struct LNode {
    int data;
    struct LNode* next;
} LNode, * LinkList;

// 初始化
bool InitListWithHead(LinkList& L);   // 带头结点：创建头结点
bool InitListNoHead(LinkList& L);     // 无头结点：L = NULL

// 插入
bool ListInsert(LinkList& L, int i, int e);          // 带头：第i个数据结点位置插入（i>=1）
bool ListInsertNULL(LinkList& L, int i, int e);      // 无头：第i个位置插入（i>=1）

// 前插（对某个结点 p 实现“前插”效果）
bool InsertPriorNode(LNode* p, int e);

// 删除
bool ListDelete(LinkList& L, int i, int& e);         // 带头：删除第i个数据结点（i>=1）
bool DeleteNode(LNode* p);                           // 删除指定结点p（后继覆盖法，不能删尾结点）

// 长度/查找
int Length(const LinkList& L);                     // 返回数据结点个数（不含头结点）
LNode* GetElem(const LinkList& L, int i);            // 按位查找（你当前实现：i=0返回头结点）
LNode* LocateElem(const LinkList& L, int e);         // 按值查找（从第一个数据结点开始）

// 建表（输入 9999 结束）
LinkList List_HeadInsert(LinkList& L);
LinkList List_TailInsert(LinkList& L);

// ====================== 双链表 ======================

typedef struct DNode {
    int data;
    struct DNode* prior;
    struct DNode* next;
} DNode, * DLinkList;

// 插入
bool InsertNextDNode(DNode* p, DNode* s);            // p 后插入 s
bool InsertPriorDNode(DNode* p, DNode* s);           // p 前插入 s（通过 p->prior 后插实现）

// 删除/销毁
bool DeleteNextDNode(DNode* p);                      // 删除 p 的后继结点
void DestroyDLinkList(DLinkList& L);                 // 依次删后继，最后释放头结点

// ====================== 循环链表 ======================

// 循环单链表初始化（带头结点，L->next = L）
bool InitCircularList(LinkList& L);

// 循环双链表删除（删除 p 的后继）
bool DeleteCircularDNode(DNode* p);


// ====================== 静态链表 ======================

// 静态链表：数组形式
typedef struct {
    int data;
    int next;     // 游标
} SLinkList[MaxSize];
#pragma once
