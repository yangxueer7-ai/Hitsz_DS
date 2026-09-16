#ifndef QUEUE_H
#define QUEUE_H

#include <cstdlib>

#define MaxSize 50

// ==================== 循环队列：空一格法 =======================
typedef struct {
    int data[MaxSize];
    int front, rear; // front 指向队头元素，rear 指向下一个插入位置
} SqQueue;

void InitQueue(SqQueue& Q);
bool QueueEmpty(const SqQueue& Q);
bool EnQueue(SqQueue& Q, int x);
bool DeQueue(SqQueue& Q, int& x);

// ==================== 循环队列：size 法 =======================
typedef struct {
    int data[MaxSize];
    int front, rear;
    int size;
} SqQueue_1;

void InitQueue_1(SqQueue_1& Q);
bool QueueEmpty_1(const SqQueue_1& Q);
bool EnQueue_1(SqQueue_1& Q, int x);
bool DeQueue_1(SqQueue_1& Q, int& x);

// ==================== 循环队列：tag 法 =======================
typedef struct {
    int data[MaxSize];
    int front, rear;
    int tag; // 0: 最近一次是出队；1: 最近一次是入队
} SqQueue_2;

void InitQueue_2(SqQueue_2& Q);
bool QueueEmpty_2(const SqQueue_2& Q);
bool EnQueue_2(SqQueue_2& Q, int x);
bool DeQueue_2(SqQueue_2& Q, int& x);

// ==================== 链式队列结点 =======================
typedef struct LinkNode {
    int data;
    struct LinkNode* next;
} LinkNode;

// ==================== 带头结点链队列 =======================
typedef struct {
    LinkNode* front; // 指向头结点
    LinkNode* rear;  // 指向尾结点
} LinkQueueH;

bool InitLinkQueueH(LinkQueueH& Q);
bool IsEmptyH(const LinkQueueH& Q);
bool EnLinkQueueH(LinkQueueH& Q, int x);
bool DeLinkQueueH(LinkQueueH& Q, int& x);
void DestroyLinkQueueH(LinkQueueH& Q);

// ==================== 不带头结点链队列 =======================
typedef struct {
    LinkNode* front; // 指向首元素
    LinkNode* rear;  // 指向尾元素
} LinkQueueNH;

void InitLinkQueueNH(LinkQueueNH& Q);
bool IsEmptyNH(const LinkQueueNH& Q);
bool EnLinkQueueNH(LinkQueueNH& Q, int x);
bool DeLinkQueueNH(LinkQueueNH& Q, int& x);
void DestroyLinkQueueNH(LinkQueueNH& Q);

#endif#pragma once
