#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct Node
{
	int id;
	char *name;
	char *tel;
	struct Node *pNext;
}List;

typedef struct AA
{
	int TotalItem;		//总条数
	int TotalPage;		//总页数
	int OnePageItem;	//每页显示条数
	int CurrentPage;	//当前页
}Page;

List *GetNode();
void AddNode(List **ppHead,List **ppEnd,List *pNode);
int GetId();
char *GetName();
char *GetTel();
void InitInfo(List **ppHead,List **ppEnd,int n);
Page *GetPage(List *pHead,int n);
void ShowInfo(Page *pPage,List *pHead);
void TurnPage(Page *pPage,List *pHead);
char Getkey();
void ShowMenu(Page *pPage);

int main()
{
	List *pHead = NULL;
	List *pEnd = NULL;
	Page *pPage = NULL;

	InitInfo(&pHead,&pEnd,101);

	pPage = GetPage(pHead,10);

	TurnPage(pPage,pHead);

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
	static int n = 1;
	return n++;
}

char *GetName()
{
	char *pTemp = (char*)malloc(6);
	int i;
	for ( i = 0; i < 5; i++)
	{
		pTemp[i] = rand() % 26 + 'a';
	}
	pTemp[i] = '\0';

	return pTemp;
}

char *GetTel()
{
	char *pTemp = (char*)malloc(12);
	int i;

	switch (rand() % 4)
	{
	case 0:
		pTemp[0] = '1';
		pTemp[1] = '3';
		pTemp[2] = '3';
		break;
	case 1:
		strcpy_s(pTemp,12,"155");
		break;
	case 2:
		strcpy_s(pTemp,12,"177");
		break;
	case 3:
		strcpy_s(pTemp,12,"188");
		break;
	}
	for ( i = 3; i < 11; i++)
	{
		pTemp[i] = rand() % 10 + '0';
	}
	pTemp[i]='\0';
	return pTemp;
}

void InitInfo(List **ppHead,List **ppEnd,int n)
{
	int i;

	srand((unsigned int)time(NULL));
	for ( i = 1; i <= n; i++)
	{
		AddNode(ppHead,ppEnd,GetNode());
	}
}

Page *GetPage(List *pHead,int n)
{
	Page *pPage = (Page*)malloc(sizeof(Page));
	pPage->CurrentPage = 0;
	pPage->OnePageItem = n;
	pPage->TotalItem = 0;

	while (pHead != NULL)
	{
		pPage->TotalItem++;
		pHead = pHead->pNext;
	}

	pPage->TotalPage = pPage->TotalItem % pPage->OnePageItem == 0 ? pPage->TotalItem/pPage->OnePageItem : 
		pPage->TotalItem/pPage->OnePageItem + 1;

	return pPage;
}

void ShowInfo(Page *pPage,List *pHead)
{
	int begin = (pPage->CurrentPage - 1)*pPage->OnePageItem + 1;
	int end = pPage->CurrentPage * pPage->OnePageItem;
	int count = 0;

	while (pHead != NULL)
	{
		count++;
		if (count >= begin && count <= end)
		{
			printf("%d %s %s\n",pHead->id,pHead->name,pHead->tel);
		}
		pHead = pHead->pNext;
	}
}

void TurnPage(Page *pPage,List *pHead)
{
	char c = 's';
	while (1)
	{
		switch (c)
		{
		case 'w':
			if (pPage->CurrentPage == 1)
			{
				printf("已经是第一页了\n");
			}
			else
			{
				pPage->CurrentPage--;
				ShowInfo(pPage,pHead);
				ShowMenu(pPage);
			}
			break;
		case 's':
			if (pPage->CurrentPage == pPage->TotalPage)
			{
				printf("已经是最后一页了\n");
			}
			else
			{
				pPage->CurrentPage++;
				ShowInfo(pPage,pHead);
				ShowMenu(pPage);
			}
			break;
		case 'b':
			return;
			break;
		default:
			printf("按错了！\n");
			break;
		}
		c = Getkey();
	}
}

char Getkey()
{
	char c;
	char z;
	int flag = 1;
	while ((c = getchar())!='\n' || 1 == flag)
	{
		z = c;
		flag = 0;
	}
	return z;
}

void ShowMenu(Page *pPage)
{
	printf("当前第%d页 共%d页 共%d条 w上一页 s下一页 b返回\n",pPage->CurrentPage,pPage->TotalPage,pPage->TotalItem);
}