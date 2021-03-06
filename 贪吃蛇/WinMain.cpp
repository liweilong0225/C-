#include <windows.h>
#include <stdlib.h>
#include "resource.h"
#include <time.h>
#include <stdio.h>

//===========================资源=========================================
HBITMAP g_hBack = 0;
HBITMAP g_hSnakeHeadLeft = 0;
HBITMAP g_hSnakeHeadRight = 0;
HBITMAP g_hSnakeHeadUp = 0;
HBITMAP g_hSnakeHeadDown = 0;
HBITMAP g_hSnakeBody = 0;
HBITMAP g_hApple = 0;
void LoadRes(HINSTANCE hInstance)
{
	g_hBack = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP7));
	g_hSnakeHeadLeft = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP5));
	g_hSnakeHeadRight = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP3));
	g_hSnakeHeadUp = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP4));
	g_hSnakeHeadDown = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP6));
	g_hSnakeBody = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP1));
	g_hApple = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP2));
}

//===========================资源=========================================

//==========================背景地图=======================================
int arrBackMap[20][20]={0};
BOOL LoadMap()
{
	//----------------------打开文件-----------------------------
	FILE* pf= NULL;
	fopen_s(&pf,".\\map.txt","rb");// .统计目录 ..上一级目录
	if(pf == 0)
		return FALSE;
	//--------------------读文件内容存到 arrBackMap --------------
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			char c = fgetc(pf);//读一个字符
			arrBackMap[i][j] = c-'0';//获取数字，存到数组里
		}
		//过滤掉'\r\n'
		fgetc(pf);
		fgetc(pf);
	}
	//----------------------关闭文件---------------------------------
	fclose(pf);
	pf = 0;
	return TRUE;
}
//==========================背景地图=======================================
void ShowBack(HDC hdc)
{
	//--------------------画一个大矩形盖住多余的蛇身------------------
	Rectangle(hdc,0,0,600,600);
	//--------------------画一个大矩形盖住多余的蛇身------------------

	HDC hMemDC = CreateCompatibleDC(hdc);
	//--------------------遍历arrBackMap数组------------------------
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (arrBackMap[i][j] == 1)
			{
				SelectObject(hMemDC,g_hBack);
				BitBlt(hdc,j*30,i*30,30,30,hMemDC,0,0,SRCCOPY);
			}
		}
	}
	//--------------------遍历arrBackMap数组------------------------
	DeleteDC(hMemDC);
}
LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
HINSTANCE hIns = 0;

int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR lpCmdLine,int nShowCmd)
{
	//-----------------------------------------------------
	HWND hwnd = 0;
	MSG msg;       //  装消息的结构体
	WNDCLASSEX wndclass;
	srand((unsigned)time(NULL));
	//-----------------------------------------------------

	hIns = hInstance;

	//----------------------创建窗口过程-----------------------------------
	//  1. 设计
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndclass.hCursor = LoadCursor(0,MAKEINTRESOURCE(IDC_ARROW));
	wndclass.hIcon = 0;
	wndclass.hIconSm = 0;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WindowProc;
	wndclass.lpszClassName = "Snake";
	wndclass.lpszMenuName = 0;
	wndclass.style = CS_HREDRAW|CS_VREDRAW;
	// 2.  注册
	if(RegisterClassEx(&wndclass) == FALSE)
	{
		MessageBox(0,"注册失败","提示",MB_OK);
		return 0;
	}
	//  3.  创建
	hwnd = CreateWindow("Snake","贪吃蛇",WS_OVERLAPPEDWINDOW,0,0,600+16,600+38,0,0,hInstance,0);
	if(hwnd == 0)
	{
		MessageBox(0,"创建失败","提示",MB_OK);
		return 0;	
	}
	//  4.  显示窗口
	ShowWindow(hwnd,SW_SHOW);
	//---------------------------创建窗口过程------------------------------------------------



	//----------------------------消息循环-------------------------------------------
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//----------------------------消息循环-------------------------------------------

	return 0;
}
//============================================苹果===============================================
struct Apple
{
	int x;
	int y;
};
Apple apple;

//============================================蛇=================================================
struct Snake
{
	int x;
	int y;
	Snake *pNext;
};
Snake *g_pHead = NULL;
Snake *g_pEnd = NULL;
int FX = VK_RIGHT;
//创建蛇
BOOL IsGameOver()
{
	//通过蛇头的坐标获取背景数组的下标
	int i = g_pEnd->y/30;
	int j = g_pEnd->x/30;
	if(arrBackMap[i][j] == 1)
		return TRUE;
	return FALSE;
}
void CreateSnake()
{
	for (int i = 0; i < 4; i++)
	{
		Snake *pSnake = (Snake*)malloc(sizeof(Snake));
		pSnake->x = 30+i*30;
		pSnake->y = 30;
		pSnake->pNext = NULL;
		if (g_pHead == NULL)
		{
			g_pHead = pSnake;
			g_pEnd = pSnake;
		}
		else
		{
			g_pEnd->pNext = pSnake;
			g_pEnd = pSnake;
		}
	}
}
//显示蛇
void ShowSnake(HDC hdc)
{
	HDC hMemDC = CreateCompatibleDC(hdc);
	//-----------------------链表中所有节点都贴上图---------------------------------------------
	//显示蛇身
	Snake *pTemp = g_pHead;
	while (pTemp->pNext != NULL)
	{
		SelectObject(hMemDC,g_hSnakeBody);
		BitBlt(hdc,pTemp->x,pTemp->y,30,30,hMemDC,0,0,SRCCOPY);
		pTemp = pTemp->pNext;
	}
	//显示蛇头
	if (FX == VK_LEFT)
		SelectObject(hMemDC,g_hSnakeHeadLeft);
	if (FX == VK_RIGHT)
		SelectObject(hMemDC,g_hSnakeHeadRight);
	if (FX == VK_UP)
		SelectObject(hMemDC,g_hSnakeHeadUp);
	if (FX == VK_DOWN)
		SelectObject(hMemDC,g_hSnakeHeadDown);
	BitBlt(hdc,g_pEnd->x,g_pEnd->y,30,30,hMemDC,0,0,SRCAND);
	//-----------------------链表中所有节点都贴上图---------------------------------------------
	DeleteDC(hMemDC);
}
//蛇移动
void SnakeMove()
{
	//在头取一个节点
	Snake *pNode = g_pHead;
	g_pHead = g_pHead->pNext;
	pNode->pNext = NULL;
	//判断方向给这个节点 赋值坐标
	if (FX == VK_LEFT)
	{
		if(g_pEnd->x == 0)
			pNode->x = 570;
		else
			pNode->x = g_pEnd->x-30;
		pNode->y = g_pEnd->y;
	}
	if (FX == VK_RIGHT)
	{
		if(g_pEnd->x == 570)
			pNode->x = 0;
		else
			pNode->x = g_pEnd->x+30;
		pNode->y = g_pEnd->y;
	}
	if (FX == VK_UP)
	{
		if(g_pEnd->y == 0)
			pNode->y = 570;
		else
			pNode->y = g_pEnd->y-30;
		pNode->x = g_pEnd->x;
	}
	if (FX == VK_DOWN)
	{
		if(g_pEnd->y == 570)
			pNode->y = 0;
		else
			pNode->y = g_pEnd->y+30;
		pNode->x = g_pEnd->x;
	}
	//把这个节点添加到尾部
	g_pEnd->pNext = pNode;
	g_pEnd = pNode;
}
//============================================蛇=================================================

//============================================苹果===============================================
//判断是否可以吃苹果
BOOL IsEatApple()
{
	if(g_pEnd->x == apple.x && g_pEnd->y == apple.y)
		return TRUE;
	return FALSE;
}
//蛇长大
void GrowUp()
{
	//给蛇头添加一个节点
	Snake* pSnake = (Snake*)malloc(sizeof(Snake));
	pSnake->x = apple.x;
	pSnake->y = apple.y;
	pSnake->pNext = NULL;
	g_pEnd->pNext = pSnake;
	g_pEnd = pSnake;
}
//随机创建苹果
void CreateApple()
{
	while (1)
	{
		//随机一个坐标
		apple.x = rand()%20*30;
		apple.y = rand()%20*30;
		//判断是否在墙上
		int i = apple.y/30;
		int j = apple.x/30;
		if (arrBackMap[i][j] == 1)
			continue;
		//判断是否在蛇身上
		Snake* pTemp = g_pHead;
		while (pTemp)
		{
			if (pTemp->x == apple.x && pTemp->y == apple.y)
				break;
			pTemp = pTemp->pNext;
		}
		//判断是否随机成功
		if(pTemp == NULL)
			return;
	}
}
//显示苹果
void ShowApple(HDC hdc)
{
	HDC hMemDC = CreateCompatibleDC(hdc);
	SelectObject(hMemDC,g_hApple);
	BitBlt(hdc,apple.x,apple.y,30,30,hMemDC,0,0,SRCCOPY);
	DeleteDC(hMemDC);
}

//=================================处理消息========================================================
LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		{
			LoadRes(hIns);	//加载资源
			LoadMap();		//加载地图
			CreateSnake();	//创建蛇
			CreateApple();	//创建苹果
		}
		break;
	case WM_PAINT:
		{
			//双缓冲 解决屏幕闪烁问题
			PAINTSTRUCT ps = {0};
			HDC hdc = BeginPaint(hwnd,&ps);
			HDC hMemDC = CreateCompatibleDC(hdc);
			HBITMAP hBitmap = CreateCompatibleBitmap(hdc,600,600);//创建一个位图和hdc,兼容的图片可以画颜色
			SelectObject(hMemDC,hBitmap);
			//------显示游戏内容-------
			ShowBack(hMemDC);	//显示背景
			ShowSnake(hMemDC);	//显示蛇
			ShowApple(hMemDC);	//显示苹果
			//------显示游戏内容-------
			BitBlt(hdc,0,0,600,600,hMemDC,0,0,SRCCOPY);
			DeleteObject(hBitmap);
			DeleteDC(hMemDC);
			EndPaint(hwnd,&ps);
		}
		break;
	case WM_TIMER:
		{
			SnakeMove();
			RECT rect = {0,0,600,600};
			InvalidateRect(hwnd,&rect,TRUE);
			if (IsGameOver() == TRUE)
			{
				KillTimer(hwnd,1);
				MessageBox(0,"GameOver","提示",MB_OK);
				break;
			}
			//是否吃到苹果
			if (IsEatApple() == TRUE)
			{
				GrowUp();
				CreateApple();
			}
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			SetTimer(hwnd,1,100,0);
			break;
		case VK_LEFT:
			if(FX != VK_RIGHT)
				FX = VK_LEFT;
			break;
		case VK_RIGHT:
			if(FX != VK_LEFT)
				FX = VK_RIGHT;
			break;
		case VK_UP:
			if(FX != VK_DOWN)
				FX = VK_UP;
			break;
		case VK_DOWN:
			if(FX != VK_UP)
				FX = VK_DOWN;
			break;
		default:
			break;
		}
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc( hwnd, uMsg, wParam, lParam);
}