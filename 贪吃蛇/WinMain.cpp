#include <windows.h>
#include <stdlib.h>
#include "resource.h"
#include <time.h>

//===========================��Դ=========================================
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

//===========================��Դ=========================================

//==========================������ͼ=======================================
int arrBackMap[20][20]={
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
//==========================������ͼ=======================================
void ShowBack(HDC hdc)
{
	//--------------------��һ������θ�ס���������------------------
	Rectangle(hdc,0,0,600,600);
	//--------------------��һ������θ�ס���������------------------

	HDC hMemDC = CreateCompatibleDC(hdc);
	//--------------------����arrBackMap����------------------------
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
	//--------------------����arrBackMap����------------------------
	DeleteDC(hMemDC);
}
LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
HINSTANCE hIns = 0;

int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR lpCmdLine,int nShowCmd)
{
	//-----------------------------------------------------
	HWND hwnd = 0;
	MSG msg;       //  װ��Ϣ�Ľṹ��
	WNDCLASSEX wndclass;
	srand((unsigned)time(NULL));
	//-----------------------------------------------------

	hIns = hInstance;

	//----------------------�������ڹ���-----------------------------------
	//  1. ���
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
	// 2.  ע��
	if(RegisterClassEx(&wndclass) == FALSE)
	{
		MessageBox(0,"ע��ʧ��","��ʾ",MB_OK);
		return 0;
	}
	//  3.  ����
	hwnd = CreateWindow("Snake","̰����",WS_OVERLAPPEDWINDOW,0,0,600+16,600+38,0,0,hInstance,0);
	if(hwnd == 0)
	{
		MessageBox(0,"����ʧ��","��ʾ",MB_OK);
		return 0;	
	}
	//  4.  ��ʾ����
	ShowWindow(hwnd,SW_SHOW);
	//---------------------------�������ڹ���------------------------------------------------



	//----------------------------��Ϣѭ��-------------------------------------------
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//----------------------------��Ϣѭ��-------------------------------------------

	return 0;
}
//============================================ƻ��===============================================
struct Apple
{
	int x;
	int y;
};
Apple apple;

//============================================��=================================================
struct Snake
{
	int x;
	int y;
	Snake *pNext;
};
Snake *g_pHead = NULL;
Snake *g_pEnd = NULL;
int FX = VK_RIGHT;
//������
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
//��ʾ��
void ShowSnake(HDC hdc)
{
	HDC hMemDC = CreateCompatibleDC(hdc);
	//-----------------------���������нڵ㶼����ͼ---------------------------------------------
	//��ʾ����
	Snake *pTemp = g_pHead;
	while (pTemp->pNext != NULL)
	{
		SelectObject(hMemDC,g_hSnakeBody);
		BitBlt(hdc,pTemp->x,pTemp->y,30,30,hMemDC,0,0,SRCCOPY);
		pTemp = pTemp->pNext;
	}
	//��ʾ��ͷ
	if (FX == VK_LEFT)
		SelectObject(hMemDC,g_hSnakeHeadLeft);
	if (FX == VK_RIGHT)
		SelectObject(hMemDC,g_hSnakeHeadRight);
	if (FX == VK_UP)
		SelectObject(hMemDC,g_hSnakeHeadUp);
	if (FX == VK_DOWN)
		SelectObject(hMemDC,g_hSnakeHeadDown);
	BitBlt(hdc,g_pEnd->x,g_pEnd->y,30,30,hMemDC,0,0,SRCCOPY);
	//-----------------------���������нڵ㶼����ͼ---------------------------------------------
	DeleteDC(hMemDC);
}
//���ƶ�
void SnakeMove()
{
	//��ͷȡһ���ڵ�
	Snake *pNode = g_pHead;
	g_pHead = g_pHead->pNext;
	pNode->pNext = NULL;
	//�жϷ��������ڵ� ��ֵ����
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
	//������ڵ���ӵ�β��
	g_pEnd->pNext = pNode;
	g_pEnd = pNode;
}
//============================================��=================================================

//============================================ƻ��===============================================
//�ж��Ƿ���Գ�ƻ��
BOOL IsEatApple()
{
	if(g_pEnd->x == apple.x && g_pEnd->y == apple.y)
		return TRUE;
	return FALSE;
}
//�߳���
void GrowUp()
{
	//����ͷ���һ���ڵ�
	Snake* pSnake = (Snake*)malloc(sizeof(Snake));
	pSnake->x = apple.x;
	pSnake->y = apple.y;
	pSnake->pNext = NULL;
	g_pEnd->pNext = pSnake;
	g_pEnd = pSnake;
}
//�������ƻ��
void CreateApple()
{
	while (1)
	{
		//���һ������
		apple.x = rand()%20*30;
		apple.y = rand()%20*30;
		//�ж��Ƿ���ǽ��
		int i = apple.y/30;
		int j = apple.x/30;
		if (arrBackMap[i][j] == 1)
			continue;
		//�ж��Ƿ���������
		Snake* pTemp = g_pHead;
		while (pTemp)
		{
			if (pTemp->x == apple.x && pTemp->y == apple.y)
				break;
			pTemp = pTemp->pNext;
		}
		//�ж��Ƿ�����ɹ�
		if(pTemp == NULL)
			return;
	}
}
//��ʾƻ��
void ShowApple(HDC hdc)
{
	HDC hMemDC = CreateCompatibleDC(hdc);
	SelectObject(hMemDC,g_hApple);
	BitBlt(hdc,apple.x,apple.y,30,30,hMemDC,0,0,SRCCOPY);
	DeleteDC(hMemDC);
}

//=================================������Ϣ========================================================
LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		{
			LoadRes(hIns);//������Դ
			CreateSnake();//������
			CreateApple();//����ƻ��
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps = {0};
			HDC hdc = BeginPaint(hwnd,&ps);
			//------��ʾ��Ϸ����-------
			ShowBack(hdc);	//��ʾ����
			ShowSnake(hdc);	//��ʾ��
			ShowApple(hdc);	//��ʾƻ��
			//------��ʾ��Ϸ����-------
			EndPaint(hwnd,&ps);
		}
		break;
	case WM_TIMER:
		{
			SnakeMove();
			RECT rect = {0,0,600,600};
			InvalidateRect(hwnd,&rect,TRUE);
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
			SetTimer(hwnd,1,200,0);
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