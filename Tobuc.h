#pragma once
#ifndef TURBOC_HEADER
#define TURBOC_TEADER

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR }CURSOR_TYPE;

enum XyPos
{
	start, end
};


void clrscr();
void gotoxy(int x, int y);
int wherex();
int wherey();
void setcursortype(CURSOR_TYPE c);
int ConsoleMousePosX(COORD* coord, HANDLE hIN);

#define delay(n) Sleep(n)
#define randomize() srand((unsigned)time(NULL))
#define random(n) (rand() %(n))

#ifndef TURBOC_PROTOTYPE_ONLY

void clrscr()
{
	system("cls");
}

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);
	return BufInfo.dwCursorPosition.X;
}

int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);
	return BufInfo.dwCursorPosition.Y;
}

void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c)
	{
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}


int ConsoleMousePosX(COORD* coord, HANDLE hIN)
{


	INPUT_RECORD input_record; // 입력한 핸들의 정보를 저장하는 함수
	DWORD input_count; // unsigned long 형  CPU가 한번에 처리할 수 있는 데이터의 크기 단위 WORD 
	BOOL MouseDragstart = TRUE;
	BOOL MouseDragend = FALSE;

	int GetXY = 0;
	SetConsoleMode(hIN, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT); //ENABLE_QUICK_EDIT_MODE 

	while (1)
	{
		ReadConsoleInput(hIN, &input_record, 1, &input_count);


		if (input_record.EventType == MOUSE_EVENT)
		{
			if (input_record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				if (MouseDragstart == TRUE)
				{
					coord[start].X = input_record.Event.MouseEvent.dwMousePosition.X;
					coord[start].Y = input_record.Event.MouseEvent.dwMousePosition.Y;
					//		printf("start -> %d %d\n", coord.X, coord.Y);
					MouseDragstart = FALSE;
					MouseDragend = TRUE;
				}

			}
			else if (!(input_record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED))
			{
				if (MouseDragend == TRUE)
				{
					coord[end].X = input_record.Event.MouseEvent.dwMousePosition.X;
					coord[end].Y = input_record.Event.MouseEvent.dwMousePosition.Y;
					//	printf("end -> %d %d\n", coord.X, coord.Y);
					MouseDragend = FALSE;
					MouseDragstart = TRUE;
					return 1;
				}
			}
		}

	}


	return 0;
}



#endif
#endif

