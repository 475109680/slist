#ifndef _SLIST_H_
#define _SLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable:4996)

typedef int SLTDataType;
typedef struct SListNode 
{
	SLTDataType data;
	struct SListNode *next;  //一定要加上"struct",由于只是定义的外面的SListNode是一个结构体类型，括号里面没有定义

}SListNode;

void SListInit(SListNode** pphead);
void SListDestory(SListNode** pphead);
SListNode* BuySListNode(SLTDataType x);
void SListPushFront(SListNode** pphead, SLTDataType x);
void SListPopFront(SListNode** pphead);
void SListInsertAfter(SListNode* pos, SLTDataType x);
void SListEraseAfter(SListNode* pos);
SListNode* SListFind(SListNode* phead, SLTDataType x);
void SListRemove(SListNode** pphead, SLTDataType x);
void SListRemoveAll(SListNode** pphead, SLTDataType x);
void SListPrint(SListNode* phead);
void SListReverse(SListNode **pphead);
void SListReverse2(SListNode **pphead);
SListNode *getIntersectionNode(SListNode *headA, SListNode *headB);
SListNode *detectCycle(SListNode *head);

#endif
