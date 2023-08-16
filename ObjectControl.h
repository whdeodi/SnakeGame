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


	
	// Move 는 꼬리 값
	for (int i = ((int)_msize(*Snake) / sizeof(SnakeXY)) - 2; i >= 0; --i)
	{
		(*Snake)[i].x = cpy[Move].x; // Move 뱀 머리
		(*Snake)[i].y = cpy[Move].y;
		--Move;
		 
		if (Move == -1)
			Move = (*length)-2;

	}
	Move = (*length)-1; // 새로 생성된 배열 가르킨다.

	x = (*Snake)[0].x - (*Snake)[1].x; // 후미의 두 값을 빼서 방향을 알아낸다..
	y = (*Snake)[0].y - (*Snake)[1].y;



	(*Snake)[Move].x = (*Snake)[0].x + x; // 가장 후미 값에 방향 값을 더해 새로운 후미 값을 만든다.
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
