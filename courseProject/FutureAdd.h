bool CheckIntersectionBombAndBombX(int firstNumber, int secondNumber)
{
if ((bomb[firstNumber].GetPositionX() + bomb[firstNumber].GetWidth() > bomb[secondNumber].GetPositionX()) && (bomb[firstNumber].GetPositionX() < bomb[secondNumber].GetPositionX() + bomb[secondNumber].GetWidth()))
return true;																																											// закомментировано, из-за осознания того, что бомбы не двигаются ((((
else
return false;
}

bool CheckIntersectionBombAndBombY(int firstNumber, int secondNumber)
{
if ((bomb[firstNumber].GetPositionY() + bomb[firstNumber].GetHeigth() > bomb[secondNumber].GetPositionY()) && ((bomb[firstNumber].GetPositionY() < bomb[secondNumber].GetPositionY() + bomb[secondNumber].GetHeigth())))
return true;
else																																														// закомментировано, из-за осознания того, что бомбы не двигаются ((((
return false;
}

void CheckCollisionBombWithBomb(float Dx, float Dy, float time)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if ((i != j) && (bomb[i].visible) && (bomb[j].visible))
			{
				if ((CheckIntersectionBombAndBombX(i, j)) && (CheckIntersectionBombAndBombY(i, j)))
				{
					if (Dy > 0)
					{
						if (bomb[i].GetPositionY() < bomb[j].GetPositionY())
						{
							bomb[i].SetPosition(bomb[i].GetPositionX(), bomb[j].GetPositionY() - bomb[i].GetHeigth());
							y = bomb[i].GetPositionY() - heigth;
							//break;
						}
						else
						{
							bomb[j].SetPosition(bomb[j].GetPositionX(), bomb[i].GetPositionY() - bomb[i].GetHeigth());
							y = bomb[j].GetPositionY() - heigth;
							//break;
						}
					}
					if (Dy < 0)
					{
						if (bomb[i].GetPositionY() > bomb[j].GetPositionY())
						{
							bomb[i].SetPosition(bomb[i].GetPositionX(), bomb[j].GetPositionY() + bomb[j].GetHeigth());
							y = bomb[i].GetPositionY() - bomb[i].GetHeigth() - heigth;
							//break;
						}
						else
						{																																				// закомментировано, из-за осознания того, что бомбы не двигаются ((((
							bomb[j].SetPosition(bomb[j].GetPositionX(), bomb[i].GetPositionY() + bomb[i].GetHeigth());
							y = bomb[j].GetPositionY() - bomb[j].GetHeigth() - heigth;
							//break;
						}
					}
					if (Dx > 0)
					{
						if(bomb[i].GetPositionX() < bomb[j].GetPositionX())
						{
							bomb[i].SetPosition(bomb[j].GetPositionX() - bomb[i].GetWidth(), bomb[i].GetPositionY());
							x = bomb[i].GetPositionX() - width;
							//break;
						}
						else
						{
							bomb[j].SetPosition(bomb[i].GetPositionX() - bomb[j].GetWidth(), bomb[j].GetPositionY());
							x = bomb[j].GetPositionX() - width;
							//break;
						}
					}
					if (Dx < 0)
					{
						if (bomb[i].GetPositionX() > bomb[j].GetPositionX())
						{
							bomb[i].SetPosition(bomb[j].GetPositionX() + bomb[j].GetWidth(), bomb[i].GetPositionY());
							x = bomb[i].GetPositionX() + bomb[i].GetWidth();
							//break;
						}
						else
						{
							bomb[j].SetPosition(bomb[i].GetPositionX() + bomb[i].GetWidth(), bomb[j].GetPositionY());
							x = bomb[j].GetPositionX() + bomb[j].GetWidth();
							//break;
						}
					}
				}
			}
		}
	}
}

/*void CheckCollisionBombWithMap(float Dx, float Dy, int number)
{
float x = bomb[number].GetPositionX(), y = bomb[number].GetPositionY();
y -= 100;
for (int i = y / CELL_SIZE; i < (y + bomb[number].GetHeigth()) / CELL_SIZE; i++)
for (int j = x / CELL_SIZE; j < (x + bomb[number].GetWidth()) / CELL_SIZE; j++)
if ((TileMap[i][j] == 'M') || (TileMap[i][j] == 'S'))
{																												// закомментировано, из-за осознания того, что бомбы не двигаются ((((
if (Dy > 0)
if (y < i * CELL_SIZE)
y = i * CELL_SIZE - bomb[number].GetHeigth();
if (Dy < 0)
if (y < i * CELL_SIZE + CELL_SIZE - 7)
y = i * CELL_SIZE + CELL_SIZE - 7;
if (Dx > 0)
if (y - i *CELL_SIZE < CELL_SIZE - 7)
x = j * CELL_SIZE - bomb[number].GetWidth();
if (Dx < 0)
if (y - i * CELL_SIZE < CELL_SIZE - 7)
x = j * CELL_SIZE + CELL_SIZE;
}
y += 100;
bomb[number].SetPosition(x, y);
}*/