#include<cstdlib>
#define MaxSize 50

//==================== 顺序队列 =======================//
// 静态数组类队列的定义
typedef struct {
	int data[MaxSize];
	int front, rear;
}SqQueue;

//==================== 循环队列 =======================//
// 默认front指针指向队列首元素，rear指针指向队尾元素下一个插入的位置
// 进行初始化
void InitQueue(SqQueue& Q) {
	Q.rear = Q.front = 0;
}

// 判空
bool QueueEmpty(const SqQueue& Q) {
	if (Q.rear == Q.front)
		return true;
	else
		return false;
}

// 元素入队
bool EnQueue(SqQueue& Q, int x) {
	if ((Q.rear + 1) % MaxSize == Q.front)//判满，若满则报错
		return false;
	Q.data[Q.rear] = x;
	Q.rear = (Q.rear + 1) % MaxSize;
	return true;
}

// 元素出队
bool DeQueue(SqQueue& Q, int& x) {
	if (Q.rear == Q.front == 0)//判空,若空则报错
		return false;
	x = Q.data[Q.front];
	Q.front = (Q.front + 1) % MaxSize;
	return true;
}

// ============== 增设size成员 入队+1 出队-1 用以区分队空或队满 ===============
typedef struct {
	int data[MaxSize];
	int front, rear;
	int size;
}SqQueue_1;

// 初始化
void InitQueue_1(SqQueue_1& Q) {
	Q.rear = Q.front = 0;
	Q.size = 0;
}

// 判空
bool QueueEmpty_1(const SqQueue_1& Q) {
	if (Q.size == 0)
		return true;
	else
		return false;
}

// 元素入队
bool EnQueue_1(SqQueue_1& Q, int x) {
	if (Q.size == MaxSize)
		return false;
	Q.data[Q.rear] = x;
	Q.rear = (Q.rear + 1) % MaxSize;
	Q.size++;
	return true;
}

// 元素出队
bool DeQueue_1(SqQueue_1& Q, int& x) {
	if (Q.size == 0)
		return false;
	x = Q.data[Q.front];
	Q.front = (Q.front + 1) % MaxSize;
	Q.size--;
	return true;
}

// ============== 增设tag标志 入队操作标记1 出队操作标记0 用以区分队空或队满 ===============
typedef struct {
	int data[MaxSize];
	int front, rear;
	int tag;
}SqQueue_2;

// 初始化
void InitQueue_2(SqQueue_2& Q) {
	Q.rear = Q.front = 0;
	Q.tag = 0;
}

// 判空
bool QueueEmpty_2(const SqQueue_2& Q) {
	if (Q.rear == Q.front && Q.tag == 0)
		return true;
	else
		return false;
}

// 元素入队
bool EnQueue_2(SqQueue_2& Q, int x) {
	if (Q.rear == Q.front && Q.tag == 1) //判满 满则报错
		return false;
	Q.data[Q.rear] = x;
	Q.rear = (Q.rear + 1) % MaxSize;
	Q.tag = 1;
	return true;
}

// 元素出队
bool DeQueue_2(SqQueue_2& Q, int& x) {
	if (Q.rear == Q.front && Q.tag == 0)
		return false;
	x = Q.data[Q.front];
	Q.front = (Q.front + 1) % MaxSize;
	Q.tag = 0;
	return true;
}

//==================== 队列的链式存储 =======================//

// 链式队列的定义
// 1.结点
typedef struct LinkNode {
	int data;
	struct LinkNode* next;
} LinkNode;

// 2.队首，队尾指针
typedef struct {
	LinkNode* front, * rear;
}LinkQueue;

//==================== 带头结点 =======================//
// 初始化带头结点的链式队列
void InitQueueH(LinkQueue& Q) {
	Q.front = Q.rear = (LinkNode*)malloc(sizeof(LinkNode));
	Q.front->next = nullptr; // 初始置空
}

// 判空
bool IsEmptyH(const LinkQueue& Q) {
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}

// 入队（单链表的后插）
void EnLinkQueueH(LinkQueue& Q, int x) {
	LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));//申请结点s的空间
	
	s->data = x;
	s->next = nullptr;
	Q.rear->next = s;//入队
	Q.rear = s;//更新队尾指针
}

// 出队
bool DeLinkQueueH(LinkQueue& Q, int& x) {
	if (IsEmptyH(Q))//判空 空则报错
		return false;
	
	LinkNode* del = Q.front->next;
	x = del->data;
	Q.front->next = del->next;
	if (Q.rear == del)//特殊情况 队列只有一个结点时
		Q.rear = Q.front;//此时删除后为空链
	free(del);
	return true;
}

//==================== 不带头结点 =======================//
// 初始化不带头节点的链式队列
void InitQueueNH(LinkQueue& Q) {
	Q.front = Q.rear = (LinkNode*)malloc(sizeof(LinkNode));
	Q.front = nullptr; // 初始置空
}

// 判空
bool IsEmptyNH(const LinkQueue& Q) {
	if (Q.front == nullptr && Q.rear == nullptr)
		return true;
	else
		return false;
}

// 入队（单链表的后插）
bool EnLinkQueueNH(LinkQueue& Q, int x) {
	LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));//申请结点s的空间
	if (s == nullptr) //判断s是否申请失败
		return false;
	
	s->data = x;
	s->next = nullptr;

	if (Q.rear == nullptr){//为空队，此时插入的元素为唯一的一个元素
		Q.front = Q.rear = s;
		return true;
	}
	//插入的队列不为空队列，正常入队
	Q.rear->next = s;
	Q.rear = s;
	return true;
}

// 出队
bool DeLinkQueue2(LinkQueue& Q, int& x) {
	if (Q.front == NULL) return false;// 判空

	LinkNode* del = Q.front;
	x = del->data;
	Q.front = Q.front->next;//更新队首指针
	if (Q.front == nullptr)//如果删后为空队列
		Q.rear = nullptr;
	free(del);
	return true;
}

// 销毁链表
bool LinkQueueDestroyNH(LinkQueue& Q) {
	LinkNode* cur = Q.front;//进行依次遍历，队首指针往右移一次更新一次，删除一个元素
	while (cur != nullptr) {
		LinkNode* next = cur->next;//保存此时指针的下一个结点
		free(cur);
		cur = next;//更新~
	}
	Q.front = Q.rear = nullptr;//直到此时为空
	return true;
}