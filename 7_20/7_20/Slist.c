#include "Slist.h"
//���Ҫ�ı�ͷָ���ָ���Ҫʹ�ö���ָ�������βΣ�ʵ����ͷָ��ĵ�ַ
SListNode* BuySListNode(SLTDataType x)
{
	SListNode*res = (SListNode*)malloc(sizeof(SListNode));
	res->data = x;
	res->next = NULL;
	return res;
}

void SListInit(SListNode** pphead)//��ʼ�����õ����������״̬����������ͷ��ѭ���������������ĳ�ʼ״̬��һ��ָ��յĽṹ��ָ��
{
	*pphead = NULL;
}
void SListDestory(SListNode** pphead)//������Ĵݻ�
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
	if (cur == NULL)//��Ҫ�������һ���ڵ��Ƿ��������ڵ㣬�ǿյĻ�����û��
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
	for (SListNode*tmp = phead; tmp; tmp = tmp->next)  //�����ͷ�����Ĺ�ʽ
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
	if (*pphead == NULL)  //�п�
	{
		return;
	}
	if ((*pphead)->data == x) //�����һ�����ǣ������ͷɾ����
	{
		SListPopFront(pphead);
		return;
	}
	for (tmp = *pphead; tmp->next; tmp = tmp->next)//���ڲ��õ��Ǻ�ɾ�ķ�ʽ�������ڱ�����tmp->next==NULLʱ�Ͳ��ñ�����
	{
		if (tmp->next->data == x)
		{
			SListEraseAfter(tmp);
			return;
		}
	
	}
}

void SListRemoveAll(SListNode** pphead, SLTDataType x)//�ص�����һ�飡��������
{
	SListNode* tmp;
	if (*pphead == NULL)
	{
		return;
	}
	if ((*pphead)->data == x) //�����һ�����ǣ������ͷɾ����
	{
		SListPopFront(pphead);
	}
	for (tmp = *pphead; tmp&&tmp->next; )//���ڲ��õ��Ǻ�ɾ�ķ�ʽ�������ڱ�����tmp->next==NULLʱ�Ͳ��ñ�����
	{
		if (tmp->next->data == x)    //���tmpָ�����һ���ڵ���x���tmp���ú�ɾ����  tmp��λ�ò������仯
		{
			SListEraseAfter(tmp);
		}
		else                         //������ǣ�tmp��λ��ȥ����Ѱ��
		{
			tmp = tmp->next;
		}
	}
	
}
//�������ַ����Ժ���Ҫ�ٴλع�
void SListReverse(SListNode **pphead)//ת��
{
	SListNode *pre = *pphead;
	SListNode *cur = pre->next;
	SListNode *next = cur;
	pre->next = NULL;
	while (next)
	{
		next = next->next;  //���ƶ�next��һ���ڵ㣬��ֹ�¸��ڵ��λ�ö�ʧ
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	*pphead = pre;
}
void SListReverse2(SListNode **pphead)  //���ģ���ɾͷ�����
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
	for (cur = headA; cur; cur = cur->next)//������A�ĳ���
	{
		lenA++;
	}
	for (cur = headB; cur; cur = cur->next)//������B�ĳ���
	{
		lenB++;
	}
	gap = abs(lenA - lenB);//��������ĳ��Ȳ�
	if (lenA < lenB)//Ĭ������A������B�������B��A�����򽫳�ָ���B����ָ���A
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
SListNode *detectCycle(SListNode *head)//�����һ�������ܵ���һ��·��һ�������ܵ�����Ҫ�ҵ�������·����û����ܵ�����ڵ�λ��
{
	SListNode *fast = head;
	SListNode *slow = head;
	while(fast && slow && fast->next)  //�ҵ�������ָ���һ��������λ��
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow)
		{
			break;
		}
	}
	for (; fast&&fast->next; fast = fast->next, head = head->next) //��˼�Ǵӵ�һ��������λ�õ�������ڵ�ʹ�ͷ����ʼ��������ھ�������ȵ�
	{
		if (head == fast)											//�����������λ���������������ͷ�ڵ�Ҳ��ʼ����
		{
			return fast;
		}
	}
	return NULL;
}