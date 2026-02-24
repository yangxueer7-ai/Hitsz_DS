#include "SeqList.h"
int main()
{
	SeqList L;
	InitList(L);
	ListInsert(L, 1, 10);
//	ListInsert(L, 2, 20);
//	ListInsert(L, 3, 30);
//	std::cout << "当前长度: " << L.length
//		<< " 当前容量: " << L.MaxSize << std::endl;
//	IncreaseSize(L, 5);
//	std::cout << "扩容后容量: " << L.MaxSize << std::endl;
//
//	ListInsert(L, 4, 40);
//	ListInsert(L, 5, 50);
//	PrintList(L);
//
//	int val;
//	if (GetElem(L, 1, val))
//		std::cout << val << std::endl;
//	int y = LocateElem(L, 40);
//	std::cout << y << std::endl;
//	DestroyList(L);
//	std::cin.get();
//}