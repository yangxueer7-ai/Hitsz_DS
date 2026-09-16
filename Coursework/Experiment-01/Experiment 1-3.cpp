/*
    实验一 第三题：火车排序
    利用栈和队列将两条从大到小排列的车厢序列合并为一条从小到大的有序序列，
    依次对栈顶元素进行比较，小的先入队
    队列的特性是先进先出
    所有元素入队完再依次出队，就构成了从小到大的有序序列
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAXSIZE 1000

typedef struct {
    int data[MAXSIZE];
    int top;
} Stack;

typedef struct {
    int data[MAXSIZE];
    int front;
    int rear;
} Queue;

// 这里用结构体指针成员访问符->
// 因为s不是变量本身，而是指向变量的指针
void InitStack(Stack* s) {
    s->top = -1;
}

int StackEmpty(Stack* s) {
    return s->top == -1;
    // 若 == -1 返回真 没读到返回false
    // OJ平台用的是C语言系统，没有bool
}

void Push(Stack* s, int x) {
    s->data[++s->top] = x;
}

int Pop(Stack* s) {
    return s->data[s->top--];
}

int GetTop(Stack* s) {
    return s->data[s->top];
}

void InitQueue(Queue* q) {
    q->front = q->rear = 0;
}

int QueueEmpty(Queue* q) {
    return q->front == q->rear;
}

// 数据入队
void EnQueue(Queue* q, int x) {
    q->data[q->rear++] = x;
}

// 数据出队
int DeQueue(Queue* q) {
    return q->data[q->front++];
}

int main() {
    Stack s1, s2;
    Queue q;
    InitStack(&s1);
    InitStack(&s2);
    InitQueue(&q);

    int x;
    char ch;

    // 读第一个栈
    while (scanf("%d", &x) == 1) { //成功读到数返回1 没读到返回0
        Push(&s1, x);
        ch = getchar();
        if (ch == '\n')
            break;
    }

    // 读第二个栈
    while (scanf("%d", &x) == 1) {
        Push(&s2, x);
        ch = getchar();
        if (ch == '\n')
            break;
    }

    // 进行两个栈元素的合并
    // 判空函数是返回1的 这个while进行循环的条件是 两者都不是空栈
    while (!StackEmpty(&s1) && !StackEmpty(&s2)) {
        if (GetTop(&s1) < GetTop(&s2))
            EnQueue(&q, Pop(&s1));
        else
            EnQueue(&q, Pop(&s2));
    }

    // 当两个栈对应元素比较完后还有剩余
    while (!StackEmpty(&s1))
        EnQueue(&q, Pop(&s1));

    while (!StackEmpty(&s2))
        EnQueue(&q, Pop(&s2));

    // 排好的从小到大的元素依次出队
    while (!QueueEmpty(&q))
        printf("%d ", DeQueue(&q));

    return 0;
}