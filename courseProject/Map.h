#ifndef SFML_GRAPHICS
#	define SFML_GRAPHICS
#	include <SFML/Graphics.hpp>
#endif // !SFML_GRAPHICS
#include "Constants.h"
#define HEIGHT_MAP 25
#define WIDTH_MAP 25

//sf::String TileMap[HEIGHT_MAP] = {
//	"MMMMMMMMMMMMMMMMMMMMMMMMM",
//	"M                       M",
//	"M M M M M M M M M M M M M",
//	"M                       M",
//	"M M M M M M M M M M M M M",
//	"M                       M",
//	"M M M M M M M M M M M M M",
//	"M                       M",
//	"M M M M M M M M M M M M M",
//	"M                       M",
//	"M M M M M M M M M M M M M",
//	"M                       M",
//	"M M M M M M M M M M M M M",
//	"M                       M",
//	"M M M M M M M M M M M M M",
//	"M                       M",
//	"M M M M M M M M M M M M M",
//	"M                       M",
//	"M M M M M M M M M M M M M",
//	"M                       M",
//	"M M M M M M M M M M M M M",
//	"M                       M",
//	"M M M M M M M M M M M M M",
//	"M                       M",
//	"MMMMMMMMMMMMMMMMMMMMMMMMM",
//};

sf::String TileBonusMap[HEIGHT_MAP] = {
	"MMMMMMMMMMMMMMMMMMMMMMMMM",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"MMMMMMMMMMMMMMMMMMMMMMMMM",
};

const sf::String TileBonusMapConst[HEIGHT_MAP] = {
	"MMMMMMMMMMMMMMMMMMMMMMMMM",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"MMMMMMMMMMMMMMMMMMMMMMMMM",
};

sf::String TileBoomMap[HEIGHT_MAP] = {
	"MMMMMMMMMMMMMMMMMMMMMMMMM",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"MMMMMMMMMMMMMMMMMMMMMMMMM",
};

const sf::String TileBoomMapConst[HEIGHT_MAP] = {
	"MMMMMMMMMMMMMMMMMMMMMMMMM",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"M M M M M M M M M M M M M",
	"M                       M",
	"MMMMMMMMMMMMMMMMMMMMMMMMM",
};

sf::String TileMap[HEIGHT_MAP] = {
	"MMMMMMMMMMMMMMMMMMMMMMMMM",
	"M  SSSSSSSSSSSSSSSSSSS  M",
	"M MSMSMSMSMSMSMSMSMSMSM M",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"MSMSMSMSMSMSMSMSMSMSMSMSM",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"MSMSMSMSMSMSMSMSMSMSMSMSM",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"MSMSMSMSMSMSMSMSMSMSMSMSM",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"MSMSMSMSMSMSMSMSMSMSMSMSM",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"MSMSMSMSMSMSMSMSMSMSMSMSM",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"MSMSMSMSMSMSMSMSMSMSMSMSM",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"MSMSMSMSMSMSMSMSMSMSMSMSM",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"MSMSMSMSMSMSMSMSMSMSMSMSM",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"MSMSMSMSMSMSMSMSMSMSMSMSM",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"M MSMSMSMSMSMSMSMSMSMSM M",
	"M  SSSSSSSSSSSSSSSSSSS  M",
	"MMMMMMMMMMMMMMMMMMMMMMMMM",
};

const sf::String TileMapConst[HEIGHT_MAP] = {
	"MMMMMMMMMMMMMMMMMMMMMMMMM",
	"M  SSSSSSSSSSSSSSSSSSS  M",
	"M MSMSMSMSMSMSMSMSMSMSM M",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"MSMSMSMSMSMSMSMSMSMSMSMSM",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"MSMSMSMSMSMSMSMSMSMSMSMSM",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"MSMSMSMSMSMSMSMSMSMSMSMSM",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"MSMSMSMSMSMSMSMSMSMSMSMSM",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"MSMSMSMSMSMSMSMSMSMSMSMSM",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"MSMSMSMSMSMSMSMSMSMSMSMSM",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"MSMSMSMSMSMSMSMSMSMSMSMSM",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"MSMSMSMSMSMSMSMSMSMSMSMSM",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"MSMSMSMSMSMSMSMSMSMSMSMSM",
	"MSSSSSSSSSSSSSSSSSSSSSSSM",
	"M MSMSMSMSMSMSMSMSMSMSM M",
	"M  SSSSSSSSSSSSSSSSSSS  M",
	"MMMMMMMMMMMMMMMMMMMMMMMMM",
};

int GetRandomCoordinate()
{
	return 1 + rand() % (WIDTH_MAP - 1);
}

void SetBonusOnMap(int countBonus, char symbolBonus)
{
	int x, y;
	while (countBonus > 0)
	{
		x = GetRandomCoordinate();
		y = GetRandomCoordinate();
		if ((TileBonusMap[x][y] != 'M') && (TileMap[x][y] != ' ') && (TileBonusMap[x][y] != 'B') && (TileBonusMap[x][y] != 'S') && (TileBonusMap[x][y] != 'F'))
		{
			TileBonusMap[x][y] = symbolBonus;
			countBonus--;
		}
	}
}

void GenerateBonusMap()
{
	int countFireBonus = 10, countBombBonus = 10, countSpeedBonus = 10;
	srand(time(0));
	SetBonusOnMap(countBombBonus, 'B');
	SetBonusOnMap(countFireBonus, 'F');
	SetBonusOnMap(countSpeedBonus, 'S');
}

void SetBoomOnMap(int j, int i, char Status)
{
	TileBoomMap[i][j] = Status;
}

void ResetMaps()
{
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			TileMap[i][j] = TileMapConst[i][j];
			TileBonusMap[i][j] = TileBonusMapConst[i][j];
			TileBoomMap[i][j] = TileBoomMapConst[i][j];
		}

}