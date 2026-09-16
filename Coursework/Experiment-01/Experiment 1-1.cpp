/*
    实验一 T1：图书管理系统
    使用线性表存储图书信息，
    实现图书的插入、删除、查找和遍历等基本操作，
    掌握线性表的存储结构及其在实际管理问题中的应用。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    char bookId[20];
    char title[100];
    char author[50];
    int stock;
} Book;

typedef struct Node {
    Book bookData;
    struct Node* next;
} Node;

// 创建新的具有图书信息的结点
Node* CreateNode(Book& bookData) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->bookData = bookData;
    p->next = NULL;
    return p;
}

// 链表尾部 插入图书信息
void InsertBook(Node** head, Book data) {
    Node* s = CreateNode(data);
    if (*head == NULL) {
        *head = s;
        return;
    }

    Node* p = *head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = s;
}

// 根据书号删除图书信息
int DeleteBook(Node** head, char bookId[]) {
    if (*head == NULL) 
        return 0;
    Node* p = *head;
    Node* prev = NULL;

    while (p != NULL) {
        if (strcmp(p->bookData.bookId, bookId) == 0) {
            if (prev == NULL) 
                *head = p->next;   // 删除头结点
            else 
                prev->next = p->next;
            
            free(p);
            return 1;
        }
        prev = p;
        p = p->next;
    }
    return 0;
}

// 根据书号修改库存数量
int UpdateStock(Node* head, char bookId[], int newStock) {
    Node* p = head;
    while (p != NULL) {
        if (strcmp(p->bookData.bookId, bookId) == 0) {
            p->bookData.stock = newStock;
            return 1;
        }
        p = p->next;
    }

    return 0;
}

// 根据书号查找图书的信息
Node* FindBook(Node* head, char bookId[]) {
    Node* p = head;
    while (p != NULL) {
        if (strcmp(p->bookData.bookId, bookId) == 0) {
            return p;
        }
        
        p = p->next;
    }

    return NULL;
}

// 遍历图书信息
void TraverseList(Node* head) {
    Node* p = head;

    printf("图书列表:\n");
    while (p != NULL) {
        printf("书号: %s,书名: %s,作者: %s,库存: %d\n",
            p->bookData.bookId,
            p->bookData.title,
            p->bookData.author,
            p->bookData.stock);
        p = p->next;
    }
}
