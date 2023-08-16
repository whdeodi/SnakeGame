#pragma once



int MoveSnake(SnakeXY* Snake, COORD direction, int* Move);
int SnakePlus(SnakeXY** Snake, int* length,int Move);

int SnakePlus(SnakeXY** Snake, int* length,int Move)
{
	int x, y;
	SnakeXY* temp = NULL;
	SnakeXY* cpy;

	++(*length);

	temp = (SnakeXY*)realloc(*Snake, sizeof(SnakeXY) * (*length));

	if (temp != NULL)
		*Snake = temp;


	cpy = (SnakeXY*)malloc(sizeof(SnakeXY) * (*length));

	memcpy(cpy, *Snake, sizeof(SnakeXY) * (*length));


	
	// Move �� ���� ��
	for (int i = ((int)_msize(*Snake) / sizeof(SnakeXY)) - 2; i >= 0; --i)
	{
		(*Snake)[i].x = cpy[Move].x; // Move �� �Ӹ�
		(*Snake)[i].y = cpy[Move].y;
		--Move;
		 
		if (Move == -1)
			Move = (*length)-2;

	}
	Move = (*length)-1; // ���� ������ �迭 ����Ų��.

	x = (*Snake)[0].x - (*Snake)[1].x; // �Ĺ��� �� ���� ���� ������ �˾Ƴ���..
	y = (*Snake)[0].y - (*Snake)[1].y;



	(*Snake)[Move].x = (*Snake)[0].x + x; // ���� �Ĺ� ���� ���� ���� ���� ���ο� �Ĺ� ���� �����.
	(*Snake)[Move].y = (*Snake)[0].y + y;

	free(cpy);

	return Move;
}

int MoveSnake(SnakeXY* Snake, COORD direction, int* Move)
{

	int Lenght = (int)_msize(Snake) / sizeof(SnakeXY);
	int returnMove;


	gotoxy(Snake[(*Move)].x * 2, Snake[(*Move)].y); //
	printf("  ");

	int preMove = (*Move) - 1 < 0 ? Lenght - 1 : (*Move) - 1;
	Snake[(*Move)].x = Snake[preMove].x + direction.X;
	Snake[(*Move)].y = Snake[preMove].y + direction.Y;
	returnMove = (*Move);

	++(*Move);
	if ((*Move) == Lenght)
		(*Move) = 0;

	return returnMove;
}



void CreateItem(Item* item)
{

	//if (y == 0 || x == 0 || y == hight + 1 || x == width + 1)

	if (item->exist == TRUE)
		return;

	item->x = random(width) + 1;
	item->y = random(hight) + 1;
	item->exist = TRUE;
}
