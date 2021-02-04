#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct AA
{
	int id;
	char *name;
	char *birth;
	struct AA *pNext; 
}Node;

Node *GetNode(int id,char *name,char *birth);
void AddNode(Node **ppHead,Node **ppEnd,Node *pTemp);
int main()
{
	Node *pHead = NULL;
	Node *pEnd = NULL;

	AddNode(&pHead,&pEnd,GetNode(1,"AA","1991"));
	AddNode(&pHead,&pEnd,GetNode(2,"BB","1992"));
	AddNode(&pHead,&pEnd,GetNode(3,"CC","1993"));

	while (pHead != NULL)
	{
		printf("%d %s %s\n",pHead->id,pHead->name,pHead->birth);
		pHead = pHead->pNext;
	}

	return 0;
}

Node *GetNode(int id,char *name,char *birth)
{
	Node *pTemp = (Node*)malloc(sizeof(Node));
	pTemp->id = id;
	pTemp->name = name;
	pTemp->birth = birth;
	pTemp->pNext = NULL;

	return pTemp;
}
void AddNode(Node **ppHead,Node **ppEnd,Node *pTemp)
{
	if (NULL == *ppHead)
	{
		*ppHead = pTemp;
	}
	else
	{
		(*ppEnd)->pNext = pTemp;
	}
	*ppEnd = pTemp;
}