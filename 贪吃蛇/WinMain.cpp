#include <windows.h>
#include "resource.h"

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


//=================================������Ϣ========================================================
LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		{
			LoadRes(hIns);//������Դ
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps = {0};
			HDC hdc = BeginPaint(hwnd,&ps);
			//------��ʾ��Ϸ����-------
			ShowBack(hdc);	//��ʾ����
			//------��ʾ��Ϸ����-------
			//ReleaseDC(hwnd,hdc);
			EndPaint(hwnd,&ps);
		}
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc( hwnd, uMsg, wParam, lParam);
}