#include "Slist.h"
int main()
{
	SListNode *phead;
	SListInit(&phead);//��Ҫ��phead��ָ�����ı䣬���Դ�phead�ĵ�ַ
	/*SListEraseAfter(phead);*/
	SListPushFront(&phead, 6);
	SListPushFront(&phead, 5);
	SListPushFront(&phead, 4);
	SListPushFront(&phead, 3);
	SListPushFront(&phead, 2);
	SListPushFront(&phead, 1);
	/*SListReverse(&phead);*/
	SListReverse2(&phead);
	SListPrint(phead);
	SListDestory(&phead);
	return 0;
}