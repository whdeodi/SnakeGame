#include "Tobuc.h"
#include "Draw.h"
#include "ObjectControl.h"

#define LEFT 75
#define RIGHT 77 
#define UP 72
#define DOWN 80
#define ESC 27
#define InitLength 4

// ■ 뱀 몸통 ● 뱀 대가리  ◎ 뱀 먹이

int GameEnd(SnakeXY* Snake,int Move)
{
	int length = (int)_msize(Snake) / sizeof(SnakeXY);

	if (Snake[Move].y == 0 || Snake[Move].x == 0 || Snake[Move].y == hight + 1 || Snake[Move].x == width + 1)
		return 1;


	for (int i = 0; i < length; i++)
	{
		if (i == Move)
			continue;

		if (Snake[Move].x == Snake[i].x && Snake[Move].y == Snake[i].y)
			return 1;
	}


	return 0;
 }

int main()
{
	COORD direction;
	Item item;
	SnakeXY* Snake;
	Snake = (SnakeXY*)malloc(sizeof(SnakeXY)* InitLength);


	if (Snake != NULL)
	{
		for (int i = 0; i < InitLength; i++)
		{
			Snake[i].x = 20 + i;
			Snake[i].y = 10;
		}
	}

	int length = InitLength;
	int Input;
	int End = 0;
	int Pause = 0;
	int Move = 0;
	int returnMove = 0;
	direction.X = 1;
	direction.Y = 0;
	randomize();
	setcursortype(NOCURSOR);
	DrawFrame();
	

	while (1)
	{
		if (Pause)
		{
			Pause = 0;
			for (int i = 3; i > 0; i--)
			{
				gotoxy(40, 12);
				printf("%d초 후 실행됩니다.", i);
				Sleep(1000);
				clrscr(); // systme clr하면 static 변수 값이 초기화 된다.
			}
			DrawFrame();
		}

		while (1)
		{
			if (_kbhit())
				break;
			
			if (item.exist == FALSE)
				CreateItem(&item);

			returnMove = MoveSnake(Snake, direction, &Move);

			if (GameEnd(Snake, returnMove))
			{
				End = 1;
				break;
			}

			DrawItem(&item);
			DrawSnake(Snake, returnMove);

			

			if (CheckEatItem(&item, Snake, returnMove))
			{
				Move = SnakePlus(&Snake, &length, returnMove);
			}

			gotoxy(0, hight + 3);
			printf("뱀 길이 ->%d", length);


			Sleep(100);
		}

		if (End)
			break;

		Input = _getch();

		if (Input == 0xE0 || Input == 0x00)
		{
			Input = _getch();

			switch (Input)
			{
			case LEFT:
				direction.X = -1;
				direction.Y = 0;
				break;
			case RIGHT:
				direction.X = 1;
				direction.Y = 0;
				break;
			case UP:
				direction.X = 0;
				direction.Y = -1;
				break;
			case DOWN:
				direction.X = 0;
				direction.Y = 1;
				break;
			default:
				break;
			}
		}
		else
		{
			switch (Input)
			{
			case ' ':
				clrscr();
				gotoxy(40, 12);
				printf("게임을 일시정시 합니다.");
				gotoxy(40, 13);
				Pause = 1;
				system("PAUSE");
				break;
			case ESC:
				End = 1;
				break;
			default:
				break;
			}
		}

		if (End)
			break;

	}


	clrscr();
	gotoxy(40, 12);
	printf("게임 종료");


	free(Snake);
	return 0;
}

// Snake Game

// 뱀이 움직이 듯이 움직이는 게임
// 뱀 물체의 머리부분이 게임이 진행 시간에 따라 움직인다.
// 뱀이 이동하는 방향은 사용자 입력을 통해 제어가능한다.
// 뱀 머리가 움직인 방향을 따라 뱀의 꼬리 부분도 움직인다.
// 뱀 머리가 아이템을 먹으면 뱀의 길이가 커진다.
// 뱀 머리가 뱀의 몸 혹은 벽에 부딪친다면 게임이 종료된다.
// 뱀 길이를 보여준다.`