#define MaxSize 100
#include <cstdlib>

// 顺序栈的定义
typedef struct {
	int data[MaxSize];
	int top;
}SqStack;

// ================== top指针指向当前栈顶元素时 ===================//

// 顺序栈的初始化（top指针指向当前栈顶元素）
void InitStack_x(SqStack& S) {
	S.top = -1;
}

// 顺序栈的判空
bool StackEmpty_x(const SqStack& S) {
	if (S.top == -1)
		return true;
	else
		return false;
}

// 元素入栈
bool Push_x(SqStack& S, int x) {
	if (S.top == MaxSize - 1)// 栈满时，报错
		return false;
	S.data[++S.top] = x;// 先自增
  //   等价于 S.top = S.top + 1;
  //         S.data[S.top] = x;     
	return true;
}

// 元素出栈
bool Pop_x(SqStack& S, int& x) {
	if (S.top == -1) 
		return false;
	x = S.data[S.top--];
	return true;
}

// 读取栈顶元素
bool GetTop_x(const SqStack& S, int& x) {
	if (S.top == -1)
		return false;
	x = S.data[S.top];
	return true;
}

// ================== top指针指向下一个入栈位置时 ===================//

// 顺序栈初始化
void InitStack_y(SqStack& S) {
	S.top = 0;
}

// 顺序栈判空
bool StackEmpty_y(const SqStack& S) {
	if (S.top == 0)
		return true;
	else
		return false;
}

// 元素入栈
bool Push_y(SqStack& S, int x) {
	if (S.top == MaxSize)
		return false;
	S.data[S.top++] = x;
	return true;
}

// 元素出栈
bool Pop_y(SqStack& S, int& x) {
	if (S.top == 0)
		return false;
	x = S.data[--S.top];
	return true;
}

// 读取栈顶元素
bool GetTop_y(const SqStack& S, int& x) {
	if (S.top == 0)
		return false;
	x = S.data[S.top - 1];
	return true;
}

// ================== 栈链的基本操作 ===================//

// 栈链的定义 默认无头结点
typedef struct LinkNode {
	int data;
	struct LinkNode* next;
}LiStack;

// 栈链的元素入栈
bool Push(LiStack*& top, int x) {
	LiStack* s = (LiStack*)malloc(sizeof(LiStack));
	if (s == NULL)
		return false;

	s->data = x;
	s->next = top;
	top = s;
	return true;
}

// 栈链的元素出栈
bool Pop(LiStack*& top, int& x) {
	if (top == nullptr)
		return false;
	
	LiStack* del = top;
	x = top->data;
	top = top->next;
	free(del);
	return true;
}

// 获取栈链顶元素
bool GetTop(LiStack* top, int& x) {
	if (top == nullptr)
		return false;
	x = top->data;
	return true;
}

// 摧毁栈链 释放内存
void DestroyStack(LiStack*& top) {
	while (top != nullptr) {
		LiStack* del = top;
		top = top->next;
		free(del);
	}
}

