#include "Slist.h"
//如果要改变头指针的指向就要使用二级指针来做形参，实参用头指针的地址
SListNode* BuySListNode(SLTDataType x)
{
	SListNode*res = (SListNode*)malloc(sizeof(SListNode));
	res->data = x;
	res->next = NULL;
	return res;
}

void SListInit(SListNode** pphead)//初始化即该单链表最初的状态，由于是无头不循环单链表，所以它的初始状态是一个指向空的结构体指针
{
	*pphead = NULL;
}
void SListDestory(SListNode** pphead)//单链表的摧毁
{
	if (*pphead == NULL)
	{
		return;
	}
	while ((*pphead)->next)
	{
		SListEraseAfter(*pphead);
	}
	free(*pphead);
	*pphead = NULL;

}
void SListEraseAfter(SListNode* pos)
{
	SListNode* cur = pos->next;
	if (cur == NULL)//需要考虑最后一个节点是否还有其他节点，是空的话就是没有
	{
		return;
	}
	pos->next = cur->next;
	free(cur);
}
SListNode* SListFind(SListNode* phead, SLTDataType x)
{
	if (phead == NULL)
	{
		return NULL;
	}
	for (SListNode*tmp = phead; tmp; tmp = tmp->next)  //链表从头遍历的公式
	{
		if (tmp->data==x)
		{
			return tmp;
		}
	}
	return NULL;
}
void SListPushFront(SListNode** pphead, SLTDataType x)
{
	SListNode* tmp=BuySListNode(x);
	tmp->next = *pphead;
	*pphead = tmp;
}
void SListPopFront(SListNode** pphead)
{
	if (*pphead == NULL)
	{
		return;
	}
	SListNode* tmp = (*pphead)->next;
	free(*pphead);
	*pphead = tmp;
	tmp = NULL;
}
void SListInsertAfter(SListNode* pos, SLTDataType x)
{
	SListNode* tmp = BuySListNode(x);
	tmp->next = pos->next;
	pos->next = tmp;
}

void SListRemove(SListNode** pphead, SLTDataType x)
{
	SListNode* tmp;
	if (*pphead == NULL)  //判空
	{
		return;
	}
	if ((*pphead)->data == x) //如果第一个就是，则采用头删操作
	{
		SListPopFront(pphead);
		return;
	}
	for (tmp = *pphead; tmp->next; tmp = tmp->next)//由于采用的是后删的方式，所以在遍历到tmp->next==NULL时就不用遍历了
	{
		if (tmp->next->data == x)
		{
			SListEraseAfter(tmp);
			return;
		}
	
	}
}

void SListRemoveAll(SListNode** pphead, SLTDataType x)//重点再敲一遍！！！！！
{
	SListNode* tmp;
	if (*pphead == NULL)
	{
		return;
	}
	if ((*pphead)->data == x) //如果第一个就是，则采用头删操作
	{
		SListPopFront(pphead);
	}
	for (tmp = *pphead; tmp&&tmp->next; )//由于采用的是后删的方式，所以在遍历到tmp->next==NULL时就不用遍历了
	{
		if (tmp->next->data == x)    //如果tmp指向的下一个节点是x则对tmp采用后删操作  tmp的位置不发生变化
		{
			SListEraseAfter(tmp);
		}
		else                         //如果不是，tmp移位，去继续寻找
		{
			tmp = tmp->next;
		}
	}
	
}
//逆置两种方法以后需要再次回顾
void SListReverse(SListNode **pphead)//转向法
{
	SListNode *pre = *pphead;
	SListNode *cur = pre->next;
	SListNode *next = cur;
	pre->next = NULL;
	while (next)
	{
		next = next->next;  //先移动next到一个节点，防止下个节点的位置丢失
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	*pphead = pre;
}
void SListReverse2(SListNode **pphead)  //核心：后删头插操作
{
	SListNode *oldh = *pphead;
	SListNode *head = *pphead;
	SListNode *tmp = head->next;
	while (tmp)
	{
		oldh->next = tmp->next;
		tmp->next = head;
		head = tmp;
		tmp = oldh->next;
	}
	*pphead = head;
}
void SListPrint(SListNode* phead)
{
	for (SListNode *tmp = phead; tmp; tmp = tmp->next)
	{
		printf("%d->", tmp->data);
	}
	printf("NULL\n");
}
SListNode *getIntersectionNode(SListNode *headA, SListNode *headB)
{
	int lenA = 0;
	int lenB = 0;
	int gap;
	int i;
	SListNode * cur;
	SListNode * longerlist = headA;
	SListNode * shorterlist = headB;
	for (cur = headA; cur; cur = cur->next)//求链表A的长度
	{
		lenA++;
	}
	for (cur = headB; cur; cur = cur->next)//求链表B的长度
	{
		lenB++;
	}
	gap = abs(lenA - lenB);//两条链表的长度差
	if (lenA < lenB)//默认链表A比链表B长，如果B比A长，则将长指针给B，短指针给A
	{
		longerlist = headB;
		shorterlist = headA;
	}
	for (i = 0; i < gap; i++)
	{
		longerlist = longerlist->next;
	}
	for (; longerlist && shorterlist; longerlist = longerlist->next, shorterlist = shorterlist->next)
	{
		if (longerlist == shorterlist)
		{
			return longerlist;
		}
	}
	return NULL;
}
SListNode *detectCycle(SListNode *head)//想象成一个进入跑道的一条路和一条环形跑道，需要找到从这条路进入该环形跑道的入口的位置
{
	SListNode *fast = head;
	SListNode *slow = head;
	while(fast && slow && fast->next)  //找到这两个指针第一次相遇的位置
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow)
		{
			break;
		}
	}
	for (; fast&&fast->next; fast = fast->next, head = head->next) //意思是从第一次相遇的位置到环的入口点和从头部开始到环的入口距离是相等的
	{
		if (head == fast)											//从这个相遇的位置往后继续遍历，头节点也开始遍历
		{
			return fast;
		}
	}
	return NULL;
}