#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct Node
{
	int id;
	char *name;
	char *tel;
	struct Node *pNext;
}List;
List *GetNode();
void AddNode(List **ppHead,List **ppEnd,List *pNode);
int GetId();
char *GetName();
char *GetTel();
void InitInfo(List **ppHead,List **ppEnd,int n);
int main()
{
	List *pHead = NULL;
	List *pEnd = NULL;

	InitInfo(&pHead,&pEnd,100);
	while (pHead!= NULL)
	{
		printf("%d	%s	%s\n",pHead->id,pHead->name,pHead->tel);
		pHead = pHead->pNext;
	}
	return 0;
}
List *GetNode()
{
	List *pTemp = (List*)malloc(sizeof(List));
	pTemp->id = GetId();
	pTemp->name = GetName();
	pTemp->tel = GetTel();
	pTemp->pNext = NULL;

	return pTemp;
}
void AddNode(List **ppHead,List **ppEnd,List *pNode)
{
	if (NULL == *ppHead)
	{
		*ppHead = pNode;
	}
	else
	{
		(*ppEnd)->pNext = pNode;
	}
	*ppEnd = pNode;
}
int GetId()
{
	static int id = 1;
	return id++;
}
char *GetName()
{
	char *pTemp = (char*)malloc(6);
	int i;
	for ( i = 0; i < 5; i++)
	{
		pTemp[i] = rand() % 26 +'a';
	}
	pTemp[i] = '\0';
	return pTemp;
}
char *GetTel()
{
	char *pTemp = (char*)malloc(12);
	int i;
	switch(rand()%4)
	{
	case 0:
		strcpy_s(pTemp,12,"133");
		break;
	case 1:
		strcpy_s(pTemp,12,"155");
		break;
	case 2:
		strcpy_s(pTemp,12,"187");
		break;
	case 3:
		strcpy_s(pTemp,12,"188");
		break;
	}
	for ( i = 3; i < 11; i++)
	{
		pTemp[i] = rand()%10+'0';
	}
	pTemp[i] = '\0';
	return pTemp;
}
void InitInfo(List **ppHead,List **ppEnd,int n)
{
	int i;
	srand((unsigned int)time(NULL));

	for ( i = 0; i < n; i++)
	{
		AddNode(ppHead,ppEnd,GetNode());
	}
}