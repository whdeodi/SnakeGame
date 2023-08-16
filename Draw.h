#pragma once
#define hight 20 
#define width 40

int Map[width][hight];


struct SnakeXY
{
	int x;
	int y;

};
struct Item
{
	BOOL exist = FALSE;
	int x;
	int y;
};


int DrawSnake(SnakeXY* Snake, int Move);
void DrawFrame();
int CheckEatItem(Item* item, SnakeXY* Snake, int Move);
void DrawItem(Item* item);




void DrawFrame()
{
	for (int y = 0; y < hight + 2; y++)
	{
		for (int x = 0; x < width + 2; x++)
		{
			if (y == 0 || x == 0 || y == hight + 1 || x == width + 1)
			{
				Map[x][y] = 0;
				gotoxy(x * 2, y);
				printf("��");
			}
		}
	}
}


int DrawSnake(SnakeXY* Snake, int Move)
{


	//gotoxy(Snake[Move].x * 2, Snake[Move].y);
	//printf("��"); // ���� ���� �׸���

	int body = Move - 1 < 0 ? (int)_msize(Snake) / sizeof(SnakeXY) - 1 : Move - 1;

	gotoxy(Snake[Move].x * 2, Snake[Move].y); // �Ӹ�
	printf("��"); 

	gotoxy(Snake[body].x * 2, Snake[body].y); // ��
	printf("��");

	return Move;
}


int CheckEatItem(Item* item, SnakeXY* Snake, int Move)
{

	if (item->exist == FALSE)
		return 0;


	if (item->x == Snake[Move].x && item->y == Snake[Move].y)
	{		
		item->exist = FALSE;
		gotoxy(item->x * 2, item->y);
		printf("��");
		//gotoxy(item->x * 2, item->y);
		//printf("��");// ���� ���� �׸���
		return 1;
	}


	return 0;
}

void DrawItem(Item* item)
{
	gotoxy(item->x * 2, item->y); // ������ �˾Ƽ� ���������.
	printf("��");
}