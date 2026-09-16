/*
    实验一 T2：纸牌游戏
    对按编号排列的纸牌按倍数规律进行翻面操作，
    制定状态值：正面朝上为1 反之为0
    注意到在不计入1的情况下，
    只有完全平方数的因数为偶数（因数有他本身）
    才能正面朝上
    最终输出正面朝上的纸牌编号及数量，
    通过本题掌握顺序表的使用和状态模拟的方法。
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct {
    ElemType* elem;    // 空间基地址，空间存放纸牌正反面状态值,正/反分别用1/0表示
    int length;        // 存放纸牌数
    int listsize;      // 存放空间的容量
} SqList;

int main() {
    int n;
    scanf("%d", &n);

    SqList L;
    L.length = n;
    L.listsize = n + 1;   // 0号位置闲置，使用1~n
    L.elem = (ElemType*)malloc((n + 1) * sizeof(ElemType));

    if (L.elem == NULL) {
        return 0;
    }

    // 初始化：1~n号牌都正面朝上，记为1
    for (int i = 1; i <= n; i++) {
        L.elem[i] = 1;
    }

    // 模拟翻牌过程
    // 从第2张牌开始，以2为基数；再以3为基数……直到n
    for (int i = 2; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            if (L.elem[j] == 1) {
                L.elem[j] = 0;
            }
            else {
                L.elem[j] = 1;
            }
        }
    }

    // 输出正面朝上的牌编号
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (L.elem[i] == 1) {
            printf("%d ", i);
            count++;
        }
    }

    // 输出正面朝上的纸牌张数
    printf("\n%d", count);

    free(L.elem);
    return 0;
}