#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int id;
	struct Node *pNext ;
}List;

void AddNode(List **ppHead,List **ppEnd,int id);
void InsertNode(List **ppHead,List **ppEnd,List *pNode,int id);
void DeleteNode(List **ppHead,List **ppEnd,int id);

int main()
{
	List *pHead = NULL;
	List *pEnd = NULL;

	//List a = {7,NULL};

	AddNode(&pHead,&pEnd,1);
	AddNode(&pHead,&pEnd,2);
	AddNode(&pHead,&pEnd,3);
	AddNode(&pHead,&pEnd,4);

	//InsertNode(&pHead,&pEnd,&a,5);

	DeleteNode(&pHead,&pEnd,4);
	while (pHead != NULL)
	{
		printf("%d\n",pHead->id);
		pHead = pHead->pNext;
	}

	return 0;
}

void AddNode(List **ppHead,List **ppEnd,int id)
{
	List *pTemp = (List*)malloc(sizeof(List));
	pTemp->id = id;
	pTemp->pNext = NULL;

	if (NULL == *ppHead)
	{
		*ppHead = pTemp;
	}
	else
	{
		(*ppEnd)->pNext=pTemp;
	}
	*ppEnd = pTemp;
}

void InsertNode(List **ppHead,List **ppEnd,List *pNode,int id)
{
	List *pMark = *ppHead;
	if ((*ppHead)->id == id)
	{
		pNode->pNext = *ppHead;
		*ppHead = pNode;
		return;
	}

	while (pMark->pNext != NULL)
	{
		if (pMark->pNext->id == id)
		{
			pNode->pNext = pMark->pNext;
			pMark->pNext = pNode;
			return;
		}
		pMark = pMark->pNext;
	}

	(*ppEnd)->pNext = pNode;
	*ppEnd = pNode;
}

void DeleteNode(List **ppHead,List **ppEnd,int id)
{
	List *pDel = NULL;
	List *pMark = *ppHead;

	if ((*ppHead)->id == id)
	{
		pDel = *ppHead;
		*ppHead = (*ppHead)->pNext;
		free(pDel);
		pDel = NULL;
		return;
	}

	while (pMark->pNext != NULL)
	{
		if (pMark->pNext->id == id)
		{
			pDel = pMark->pNext;
			pMark->pNext = pMark->pNext->pNext;
			free(pDel);
			pDel = NULL;
			if (NULL == pMark->pNext)
			{
				*ppEnd = pMark;
			}
			return;
		}
		pMark = pMark->pNext;
	}
}