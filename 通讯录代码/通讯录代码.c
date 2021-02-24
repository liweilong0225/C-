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
typedef struct PAGE
{
	int TotalInfo;	//������
	int TotalPage;	//��ҳ��
	int OnePageInfo;//ÿҳ��ʾ����
	int Currentage;	//��ǰҳ
}Page;

List *GetNode();
void AddNode(List **ppHead,List **ppEnd,List *pNode);
int GetId();
char *GetName();
char *GetTel();
void InitInfo(List **ppHead,List **ppEnd,int n);
Page *GetPage(List *pHead,int n);
void ShowInfo(List *pHead,Page *pPage);
void TurnPage(List *pHead,Page *pPage);
char GetKey();
void ShowMenu(Page *pPage);

int main()
{
	List *pHead = NULL;
	List *pEnd = NULL;
	Page *pPage = NULL;

	InitInfo(&pHead,&pEnd,100);

	pPage = GetPage(pHead,10);
	TurnPage(pHead,pPage);

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
Page *GetPage(List *pHead,int n)
{
	Page *p = (Page*)malloc(sizeof(Page));
	p->Currentage = 0;
	p->OnePageInfo = n;
	p->TotalInfo = 0;

	while (pHead != NULL)
	{
		p->TotalInfo++;
		pHead = pHead->pNext;
	}
	p->TotalPage = p->TotalInfo % p->OnePageInfo == 0 ? p->TotalInfo / p->OnePageInfo : 
		p->TotalInfo / p->OnePageInfo + 1;
	return p;
}
void ShowInfo(List *pHead,Page *pPage)
{
	int begin = (pPage->Currentage-1) * pPage->OnePageInfo+1;
	int end = pPage->Currentage * pPage->OnePageInfo;
	int count = 0;

	while (pHead != NULL)
	{
		count++;
		if (begin <= count && count <= end)
		{
			printf("%d	%s	%s\n",pHead->id,pHead->name,pHead->tel);
		}
		pHead = pHead->pNext;
	}
}
void TurnPage(List *pHead,Page *pPage)
{
	char c = 's';

	while (1)
	{
		switch(c)
		{
		case 'w':
			if (pPage->Currentage > 1)
			{
				pPage->Currentage--;
				ShowInfo(pHead,pPage);
				ShowMenu(pPage);
			}
			else
			{
				printf("�Ѿ��ǵ�һҳ��\n");
			}
			break;
		case 's':
			if (pPage->Currentage < pPage->TotalPage)
			{
				pPage->Currentage++;
				ShowInfo(pHead,pPage);
				ShowMenu(pPage);
			}
			else
			{
				printf("�Ѿ������һҳ��\n");
			}
			break;
		case 'b':
			return;
			break;
		default:
			printf("������\n");
			break;
		}
		c = GetKey();
	}
}
char GetKey()
{
	char c;
	char z;
	int flag = 1;
	while ((c = getchar()) != '\n' || 1==flag)
	{
		z=c;
		flag = 0;
	}
	return z;
}
void ShowMenu(Page *pPage)
{
	printf("��ǰ��%dҳ	��%dҳ	��%d��	w��һҳ	s��һҳ	b����\n",pPage->Currentage,pPage->TotalPage,pPage->TotalInfo);
}