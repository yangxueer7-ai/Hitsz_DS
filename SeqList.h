#pragma once
#include <iostream>

#define InitSize 100

typedef struct {
    int* data;
    int MaxSize;
    int length;
} SeqList;

// º¯ÊýÉùÃ÷

void InitList(SeqList& L);
void DestroyList(SeqList& L);
void IncreaseSize(SeqList& L, int len);

bool ListInsert(SeqList& L, int i, int e);
bool ListDelete(SeqList& L, int i, int& e);

bool GetElem(const SeqList& L, int i, int& e);
int LocateElem(SeqList& L, int e);

void PrintList(const SeqList& L);
int Length(const SeqList& L);
