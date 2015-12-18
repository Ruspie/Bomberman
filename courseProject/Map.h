//#ifndef SFML_GRAPHICS
//#	define SFML_GRAPHICS
#	include <SFML/Graphics.hpp>
//#endif // !SFML_GRAPHICS

const int HEIGHT_MAP = 25;
const int WIDTH_MAP = 25;


sf::String TileMap[HEIGHT_MAP] = {
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

//sf::String TileMap[HEIGHT_MAP] = {
//	"MMMMMMMMMMMMMMMMMMMMMMMMM",
//	"M  SSSSSSSSSSSSSSSSSSS  M",
//	"M MSMSMSMSMSMSMSMSMSMSM M",
//	"MSSSSSSSSSSSSSSSSSSSSSSSM",
//	"MSMSMSMSMSMSMSMSMSMSMSMSM",
//	"MSSSSSSSSSSSSSSSSSSSSSSSM",
//	"MSMSMSMSMSMSMSMSMSMSMSMSM",
//	"MSSSSSSSSSSSSSSSSSSSSSSSM",
//	"MSMSMSMSMSMSMSMSMSMSMSMSM",
//	"MSSSSSSSSSSSSSSSSSSSSSSSM",
//	"MSMSMSMSMSMSMSMSMSMSMSMSM",
//	"MSSSSSSSSSSSSSSSSSSSSSSSM",
//	"MSMSMSMSMSMSMSMSMSMSMSMSM",
//	"MSSSSSSSSSSSSSSSSSSSSSSSM",
//	"MSMSMSMSMSMSMSMSMSMSMSMSM",
//	"MSSSSSSSSSSSSSSSSSSSSSSSM",
//	"MSMSMSMSMSMSMSMSMSMSMSMSM",
//	"MSSSSSSSSSSSSSSSSSSSSSSSM",
//	"MSMSMSMSMSMSMSMSMSMSMSMSM",
//	"MSSSSSSSSSSSSSSSSSSSSSSSM",
//	"MSMSMSMSMSMSMSMSMSMSMSMSM",
//	"MSSSSSSSSSSSSSSSSSSSSSSSM",
//	"M MSMSMSMSMSMSMSMSMSMSM M",
//	"M  SSSSSSSSSSSSSSSSSSS  M",
//	"MMMMMMMMMMMMMMMMMMMMMMMMM",
//};

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
		if ((TileBonusMap[x][y] != 'M') && (TileMap[x][y] != 'q') && (TileBonusMap[x][y] != 'B') && (TileBonusMap[x][y] != 'S') && (TileBonusMap[x][y] != 'F'))
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