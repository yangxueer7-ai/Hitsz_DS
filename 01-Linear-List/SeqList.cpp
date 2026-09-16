#include <cstdlib>
#include "SeqList.h"

//顺序表的初始化
void InitList(SeqList& L)
{
	L.data = (int*)malloc(InitSize * sizeof(int));
	L.MaxSize = InitSize;
	L.length = 0;
}

// 顺序表的摧毁
void DestroyList(SeqList& L)
{
	free(L.data);
	L.data = NULL;
	L.MaxSize = 0;
	L.length = 0;
}


//增加长度
void IncreaseSize(SeqList& L, int len)
{
	if (len <= 0)
		return;
	int* p = L.data;
	int* newdata = (int*)malloc((L.MaxSize + len) * sizeof(int));
	if (newdata == NULL) //判断是否申请成功或失败 防止申请失败导致对NULL解引用
		return;
	for (int i = 0; i < L.length; i++)
		newdata[i] = p[i];
	L.data = newdata; 
	L.MaxSize += len;
	free(p);
}


//顺序表插入元素
bool ListInsert(SeqList& L, int i, int e) // i为位序
{
	if (i < 1 || i > L.length + 1)
		return false;
	if (L.length >= L.MaxSize)// 存储空间已满
		return false;
	for (int j = L.length; j >= i; j--)
		L.data[j] = L.data[j - 1];// 原先的元素从后往前后移
	L.data[i - 1] = e;// 数组下标等于 位序-1
	L.length++;
	return true;
}


//顺序表删除元素
bool ListDelete(SeqList& L, int i, int& e)
{
	if (i<1 || i>L.length)
		return false;
	e = L.data[i - 1];
	for (int j = i; j < L.length; j++)
		L.data[j - 1] = L.data[j];// 原先元素从前往后前移一位
	L.length--;
	return true;
}

// 顺序表删除特定元素时间复杂度为o(n)的新算法
bool DeleteAllX(SeqList& L, int x)
{
	if (L.length == 0)
		return false;

	int i = 0, j = 0;

	while (i < L.length)
	{
		if (L.data[i] != x)
		{
			L.data[j] = L.data[i];
			j++;
		}
		
		i++;
	}

	L.length = j;
	return true;
}

// 顺序表删除特定元素后,尾段用0补齐
bool DeleteAllXToZero(SeqList& L, int x)
{
	if (L.length == 0)
		return false;
	int oldLength = L.length;
	int i = 0, j = 0;
	while (i < L.length)
	{
		if (L.data[i] != x)
		{
			L.data[j] = L.data[i];
			j++;
		}
		i++;
	}

	for (int k = j; k < oldLength; k++)
		L.data[k] = 0;
	L.length = j;
	return true;
}


// 按位查找
bool GetElem(const SeqList& L, int i, int& e)
{
	if (i < 1 || i > L.length)
		return false;
	e = L.data[i - 1];
	return true;
}

// 按值查找
int LocateElem(const SeqList& L, int e)
{
	for (int i = 1; i <= L.length; i++)
		if (L.data[i - 1] == e)
			return i - 1;
	return 0;
}


// 输出顺序表元素
void PrintList(const SeqList& L)
{
	if (L.data == NULL)
	{
		std::cout << "顺序表未初始化或已销毁。" << std::endl;
		return;
	}

	if (L.length == 0)
	{
		std::cout << "顺序表为空。" << std::endl;
		return;
	}

	for (int i = 1; i <= L.length; i++)
		std::cout << L.data[i - 1] << std::endl;
}

// 输出顺序表长度
int Length(const SeqList& L)
{
	return L.length;
}


