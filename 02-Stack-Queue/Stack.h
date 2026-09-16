#ifndef STACK_DS_H
#define STACK_DS_H

#include <cstdlib>

#define MaxSize 100

// 顺序栈
typedef struct {
    int data[MaxSize];
    int top;
} SqStack;

// top 指向当前栈顶元素
void InitStack_x(SqStack& S);
bool StackEmpty_x(const SqStack& S);
bool Push_x(SqStack& S, int x);
bool Pop_x(SqStack& S, int& x);
bool GetTop_x(const SqStack& S, int& x);

// top 指向下一个入栈位置
void InitStack_y(SqStack& S);
bool StackEmpty_y(const SqStack& S);
bool Push_y(SqStack& S, int x);
bool Pop_y(SqStack& S, int& x);
bool GetTop_y(const SqStack& S, int& x);

// 链栈（无头结点）
typedef struct LinkNode {
    int data;
    struct LinkNode* next;
} LiStack;

bool Push(LiStack*& top, int x);
bool Pop(LiStack*& top, int& x);

bool GetTop(LiStack* top, int& x);
void DestroyStack(LiStack*& top);

#endif // STACK_DS_H#pragma once
