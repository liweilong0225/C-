#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
//通讯录
typedef struct Node
{
	int id;
	char *name;
	char *tel;
	struct Node *pNext;
}List;
typedef struct PAGE
{
	int TotalInfo;	//总条数
	int TotalPage;	//总页数
	int OnePageInfo;//每页显示条数
	int Currentage;	//当前页
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
void Browse(List *pHead,int n);
List *GetNodeIn();
char *GetString();
void Query(List *pHead);
void DeleteNode(List **ppHead,List **ppEnd,int id);
void DeleteInfo(List **ppHead,List **ppEnd);
void UpDateInfo(List *pHead);

int g_MenuType;
char g_Key;

int main()
{
	List *pHead = NULL;
	List *pEnd = NULL;
	char c;
	InitInfo(&pHead,&pEnd,100);
	while (1)
	{
		printf("1.查看通讯录\n");
		printf("2.添加信息\n");
		printf("3.查询信息\n");
		printf("4.删除信息\n");
		printf("5.修改信息\n");
		printf("q.退出\n");

		c = GetKey();

		switch (c)
		{
		case '1':
			g_MenuType = 1;
			Browse(pHead,10);
			break;
		case '2':
			AddNode(&pHead,&pEnd,GetNodeIn());
			break;
		case '3':
			g_MenuType = 3;
			Query(pHead);
			break;
		case '4':
			g_MenuType = 4;
			DeleteInfo(&pHead,&pEnd);
			break;
		case '5':
			g_MenuType = 5;
			UpDateInfo(pHead);
			break;
		case 'q':
			return;
			break;
		default:
			printf("按错了\n");
			break;
		}

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
				printf("已经是第一页了\n");
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
				printf("已经是最后一页了\n");
			}
			break;
		case 'b':
			return;
			break;
		case 'c':
			return;
			break;
		case 'd':
			return;
			break;
		case 'u':
			return;
			break;
		default:
			printf("按错了\n");
			break;
		}
		c = GetKey();
		g_Key = c;
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
	switch (g_MenuType)
	{
	case 1:
		printf("当前第%d页	共%d页	共%d条	w上一页	s下一页	b返回\n",pPage->Currentage,pPage->TotalPage,pPage->TotalInfo);
		break;
	case 3:
		printf("当前第%d页	共%d页	共%d条	w上一页	s下一页	c重新查询 b返回\n",pPage->Currentage,pPage->TotalPage,pPage->TotalInfo);
		break;
	case 4:
		printf("当前第%d页	共%d页	共%d条	w上一页	s下一页	d删除信息 b返回\n",pPage->Currentage,pPage->TotalPage,pPage->TotalInfo);
		break;
	case 5:
		printf("当前第%d页	共%d页	共%d条	w上一页	s下一页	u修改信息 b返回\n",pPage->Currentage,pPage->TotalPage,pPage->TotalInfo);
		break;
	default:
		break;
	}
}
void Browse(List *pHead,int n)
{
	Page *pPage = GetPage(pHead,n);
	TurnPage(pHead,pPage);
	free(pPage);
	pPage = NULL;
}
List *GetNodeIn()
{
	List *pTemp = (List*)malloc(sizeof(List));
	pTemp->id = GetId();
	printf("请输入姓名：\n");
	pTemp->name = GetString();
	printf("请输入电话：\n");
	pTemp->tel = GetString();
	pTemp->pNext = NULL;

	return pTemp;
}
char *GetString()
{
	int size = 5;
	char *str = (char*)malloc(size);
	char c;
	int count = 0;
	char *newstr = NULL;
	char *pMark = str;

	while ((c = getchar())!='\n')
	{
		*str = c;
		str++;
		count++;
		if (count +1 == size)
		{
			*str = '\0';
			size += 5;
			newstr = (char*)malloc(size);
			strcpy_s(newstr,size,pMark);
			free(pMark);
			pMark = newstr;
			str = newstr+count;
		}
	}
	*str = '\0';
	return pMark;
}
void Query(List *pHead)
{
	char *str = NULL;
	List *pNewHead = NULL;
	List *pNewEnd = NULL;
	List *pTemp = NULL;
	List *pDel = NULL;
	List *pMark = pHead;

	while (1)
	{
		while (1)
		{
			printf("请输入关键字：\n");
			str = GetString();
			printf("a确认 其他键重新输入\n");
			if (GetKey() == 'a')
			{
				break;
			}
			else
			{
				free(str);
				str = NULL;
			}
		}
		pHead = pMark;
		while (pHead != NULL)
		{
			if (0 == strncmp(pHead->name,str,strlen(str)) || 0 == strncmp(pHead->tel,str,strlen(str)))
			{
				pTemp = (List*)malloc(sizeof(List));
				pTemp->id = pHead->id;
				pTemp->name = pHead->name;
				pTemp->tel = pHead->tel;
				pTemp->pNext = NULL;
				AddNode(&pNewHead,&pNewEnd,pTemp);
			}
			pHead = pHead->pNext;
		}
		Browse(pNewHead,10);

		while (pNewHead != NULL)
		{
			pDel = pNewHead;
			pNewHead = pNewHead->pNext;
			free(pDel);
			pDel = NULL;
		}
		pNewEnd = NULL;

		if ('b' == g_Key || 'd' == g_Key || 'u' == g_Key)
		{
			break;
		}
	}
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
			pMark->pNext =  pMark->pNext->pNext;
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
void DeleteInfo(List **ppHead,List **ppEnd)
{
	char *str = NULL;
	int id;
	while (1)
	{
		Query(*ppHead);
		if ( 'b ' == g_Key)
		{
			break;
		}
		printf("请输入要删除的编号：\n");
		str = GetString();
		id = atoi(str);
		free(str);
		str = NULL;
		DeleteNode(ppHead,ppEnd,id);
		printf("y继续删除 其他键返回\n");
		if (GetKey() != 'y')
		{
			break;
		}
	}	
}
void UpDateInfo(List *pHead)
{
	char *str = NULL;
	int id;
	Query(pHead);
	if ('b' == g_Key)
	{
		return;
	}
	printf("请输入要修改的编号：\n");
	str = GetString();
	id = atoi(str);
	free(str);
	str = NULL;

	while (pHead != NULL)
	{
		if (pHead->id == id)
		{
			printf("请输入姓名：\n");
			str = GetString();
			if (strlen(str)>0)
			{
				free(pHead->name);
				pHead->name = str;
			}
			printf("请输入电话：\n");
			str = GetString();
			if (strlen(str)>0)
			{
				free(pHead->tel);
				pHead->tel = str;
			}
		}
		pHead = pHead->pNext;
	}
}