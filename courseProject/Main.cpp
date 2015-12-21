#ifndef SFML_GRAPHICS
#	define SFML_GRAPHICS
#include <SFML/Graphics.hpp>
#endif // !SFML_GRAPHICS
#include <SFML\Audio.hpp>
#include "Map.h"
#include "Help.h"
#include "Win.h"
#include <iostream>
#include "Constants.h"

class Game
{
	class Player
	{

		class Bomb
		{

		private:
			float x, y, width, heigth;
			float nativeTime, boomTime;

		public:
			int frame;
			int fire;
			sf::String File;
			sf::Image image;
			sf::Texture texture;
			sf::Sprite sprite;
			sf::Sound soundBoom;
			bool visible, inPlayer, isBoom, enabled;
			int fireState;

			Bomb()
			{
			}

			void Create(sf::String F, sf::Sound *SoundBoom, float X, float Y, float Width, float Heigth)
			{
				x = X; y = Y;
				File = F;
				width = Width; heigth = Heigth;
				frame = 0; nativeTime = 0; boomTime = 0; fireState = 2;
				visible = false; inPlayer = false; isBoom = false; enabled = false;
				image.loadFromFile("images/" + File);
				texture.loadFromImage(image);
				sprite.setTexture(texture);
				sprite.setTextureRect(sf::IntRect(0, 30, Width, Heigth));
				sprite.setOrigin(width / 2, heigth / 2);
				sprite.setPosition(X + 3 + width / 2, Y + 3 + heigth / 2);
				soundBoom = *SoundBoom;
			}

			void Reset()
			{
				frame = 0; nativeTime = 0; boomTime = 0; fireState = 2;
				visible = false; inPlayer = false; isBoom = false; enabled = false;
			}

			void SetPosition(float X, float Y)
			{
				x = X; y = Y;
			}

			void SetTileDestroyStone(int positionY, int positionX)
			{
				if ((TileMap[positionY][positionX] == 'S') || (TileMap[positionY][positionX] == '1')
					|| (TileMap[positionY][positionX] == '2') || (TileMap[positionY][positionX] == '3')
					|| (TileMap[positionY][positionX] == '4') || (TileMap[positionY][positionX] == '5'))
				{
					if (boomTime < 0.2)
						TileMap[positionY][positionX] = '1';
					else
						if (boomTime < 0.4)
							TileMap[positionY][positionX] = '2';
						else
							if (boomTime < 0.6)
								TileMap[positionY][positionX] = '3';
							else
								if (boomTime < 0.8)
									TileMap[positionY][positionX] = '4';
								else
									if (boomTime < 1)
										TileMap[positionY][positionX] = '5';
									else
										TileMap[positionY][positionX] = ' ';
				}
			}

			void CheckBombOnFire(float x, float y)
			{
				for (int i = (y - 100) / CELL_SIZE; i < (y - 100 + heigth) / CELL_SIZE; i++)
				{
					for (int j = x / CELL_SIZE; j < (x + width) / CELL_SIZE; j++)
					{
						char SymbolInMap = TileBoomMap[i][j];
						if ((SymbolInMap == 'H') || (SymbolInMap == 'R') || (SymbolInMap == 'L') || (SymbolInMap == 'V') || (SymbolInMap == 'D') || (SymbolInMap == 'U') || (SymbolInMap == 'S'))
						{
							nativeTime = 3;
							break;
						}
					}
					if (nativeTime == 3)
						break;

				}
			}

			void Update(float time)
			{
				if (visible == true)
				{
					nativeTime += time;
					CheckBombOnFire(x, y);
					if (nativeTime < 3)
						sprite.setPosition(x + 3 + width / 2, y + 3 + heigth / 2);
					else
					{
						soundBoom.play();
						visible = false;
						isBoom = true;
						nativeTime = 0;
					}
				}
				if (isBoom)
				{	
					int positionX = (int)(x / CELL_SIZE), positionY = (int)((y - 100) / CELL_SIZE);
					boomTime += time;
					if (boomTime < 1)
					{
						SetBoomOnMap(positionX, positionY, 'S');
						for (int i = 0; i < fireState; i++)
						{
							if (TileMap[positionY][positionX + i + 1] == ' ')
							{
								if (i != fireState - 1)
								{
									if (positionX + i + 1 < HEIGHT_MAP)
										SetBoomOnMap(positionX + i + 1, positionY, 'H');
								}
								else
									if (positionX + i + 1 < HEIGHT_MAP)
										SetBoomOnMap(positionX + i + 1, positionY, 'R');
							}
							else
							{
								SetTileDestroyStone(positionY, positionX + i + 1);
								break;
							}
						}
						for (int i = 0; i < fireState; i++)
						{
							if (TileMap[positionY][positionX - i - 1] == ' ')
							{
								if (i != fireState - 1)
								{
									if (positionX - i - 1 > 0)
										SetBoomOnMap(positionX - i - 1, positionY, 'H');
								}
								else
									if (positionX - i - 1 > 0)
									{
										SetBoomOnMap(positionX - i - 1, positionY, 'L');
									}
							}
							else
							{
								SetTileDestroyStone(positionY, positionX - i - 1);
								break;
							}
						}
						for (int i = 0; i < fireState; i++)
						{
							if (TileMap[positionY + i + 1][positionX] == ' ')
							{
								if (i != fireState - 1)
								{
									if (positionY + i + 1 < HEIGHT_MAP)
										SetBoomOnMap(positionX, positionY + i + 1, 'V');
								}
								else
									if (positionY + i + 1 < HEIGHT_MAP)
									{
										SetBoomOnMap(positionX, positionY + i + 1, 'D');
									}
							}
							else
							{
								SetTileDestroyStone(positionY + i + 1, positionX);
								break;
							}
						}
						for (int i = 0; i < fireState; i++)
						{
							if (TileMap[positionY - i - 1][positionX] == ' ')
							{
								if (i != fireState - 1)
								{
									if (positionY - i - 1 > 0)
										SetBoomOnMap(positionX, positionY - i - 1, 'V');
								}
								else
									if (positionY - i - 1 < HEIGHT_MAP)
									{
										SetBoomOnMap(positionX, positionY - i - 1, 'U');
									}
							}
							else
							{
								SetTileDestroyStone(positionY - i - 1, positionX);
								break;
							}
						}
					}
					if (boomTime > 1)
					{
						isBoom = false;
						enabled = false;
						SetBoomOnMap(positionX, positionY, ' ');
						for (int i = 0; i < fireState; i++)
						{
							if (positionX + i + 1 < HEIGHT_MAP)
								SetBoomOnMap(positionX + i + 1, positionY, ' ');
							if (positionX - i - 1 > 0)
								SetBoomOnMap(positionX - i - 1, positionY, ' ');
							if (positionY + i + 1 < HEIGHT_MAP)
								SetBoomOnMap(positionX, positionY + i + 1, ' ');
							if (positionY - i - 1 > 0)
								SetBoomOnMap(positionX, positionY - i - 1, ' ');
							if (positionX + i + 1 > 0 && positionX + i + 1 < HEIGHT_MAP)
								if (TileMap[positionY][positionX + i + 1] == '5')
									TileMap[positionY][positionX + i + 1] = ' ';
							if (positionX - i - 1 > 0 && positionX - i - 1 < HEIGHT_MAP)
								if (TileMap[positionY][positionX - i - 1] == '5')
									TileMap[positionY][positionX - i - 1] = ' ';
							if (positionY + i + 1 > 0 && positionY + i + 1 < HEIGHT_MAP)
								if (TileMap[positionY + i + 1][positionX] == '5')
									TileMap[positionY + i + 1][positionX] = ' ';
							if (positionY - i - 1 > 0 && positionY - i - 1 < HEIGHT_MAP)
								if (TileMap[positionY - i - 1][positionX] == '5')
								TileMap[positionY - i - 1][positionX] = ' ';
						}
						boomTime = 0;
					}
				}
			}

			float GetPositionX()
			{
				return x;
			}

			float GetPositionY()
			{
				return y;
			}

			float GetHeigth()
			{
				return heigth;
			}

			float GetWidth()
			{
				return width;
			}

			float GetNativeTime()
			{
				return nativeTime;
			}
		};

	private:
		float x, y, width, heigth, dx, dy, currentFrame, dieTime;
		int bombState, speedState, fireState, colDIe, shift;
		bool life;
		sf::String name;

	public:
		float speed = 0;
		Bomb bomb[5];
		bool isMove, isSelected, isSpace;
		enum { left, rigth, up, down, stay } state;
		sf::String File;
		sf::Texture texture;
		sf::Sprite sprite;
		sf::SoundBuffer bufferBoom, bufferBonus, bufferDie;
		sf::Sound soundBoom, soundBonus, soundDie;
		Player()
		{

		}

		void Create(sf::Image &image, sf::String Name,float X, float Y, float Width, float Heigth, int Shift)
		{
			bufferBoom.loadFromFile("data/Boom.mid");
			soundBoom.setBuffer(bufferBoom);
			bufferBonus.loadFromFile("data/Bonus.mid");
			soundBonus.setBuffer(bufferBonus);
			bufferDie.loadFromFile("data/Die.mid");
			soundDie.setBuffer(bufferDie);
			bombState = 1; speedState = 0; fireState = 2; dieTime = 0;
			life = true;
			name = Name;
			width = Width; heigth = Heigth;
			x = X; y = Y; currentFrame = 0, speed = 0; shift = Shift;
			isMove = false; isSelected = false, isSpace = false;
			state = stay;
			for (int i = 0; i < 5; i++)
			{
				bomb[i].Create("bomberman_bomb_sheet.png", &soundBoom, 0, 0, 16, 16);
			}
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(0 + shift, 0, width, heigth));
			sprite.setOrigin(width / 2, heigth / 2);
			sprite.setPosition(X + width / 2, Y + heigth / 2);
		}

		void Reset(float X, float Y, int Shift)
		{
			bombState = 1; speedState = 0; fireState = 2; dieTime = 0;
			life = true;
			x = X; y = Y; currentFrame = 0, speed = 0; shift = Shift;
			isMove = false; isSelected = false, isSpace = false;
			state = stay;
			for (int i = 0; i < 5; i++)
			{
				bomb[i].Reset();
			}
			sprite.setTextureRect(sf::IntRect(0 + shift, 0, width, heigth));
			sprite.setOrigin(width / 2, heigth / 2);
			sprite.setPosition(X + width / 2, Y + heigth / 2);
		}

		void Update(float time, float realTime)
		{
			dx = 0; dy = 0;
			Control(time);
			switch (state)
			{
			case left:
				dx = -speed; dy = 0; break;
			case rigth:
				dx = speed; dy = 0; break;
			case up:
				dx = 0; dy = -speed; break;
			case down:
				dx = 0; dy = speed; break;
			case stay: break;
			}
			x += dx * time;
			CheckCollisionPlayerWithMap(dx, 0);
			CheckCollisionPlayerWithBomb(dx, 0, time);
			//CheckCollisionBombWithBomb(dx, 0, time);			// закомментировано, из-за осознания того, что бомбы не двигаются ((((
			y += dy * time;
			CheckCollisionPlayerWithMap(0, dy);
			CheckCollisionPlayerWithBomb(0, dy, time);
			//CheckCollisionBombWithBomb(0, dy, time);			// закомментировано, из-за осознания того, что бомбы не двигаются ((((
			speed = 0;
			for (int i = 0; i < 5; i++)
			{
				bomb[i].Update(realTime);
			}
			sprite.setPosition(x + width / 2, y + heigth / 2);
			CheckPlayerOnFire(x, y);
		}

		void AnimationDie(int Shift, float time)
		{
			currentFrame += 0.005*time;
			if (currentFrame > 3)
				currentFrame -= 3;
			sprite.setTextureRect(sf::IntRect(int(currentFrame) * 30, Shift, PICTURE_BOMBERMAN_WIDTH, PICTURE_BOMBERMAN_HEIGTH));
		}

		void Die(float time)
		{
			dieTime += time / 3;
			if (dieTime > 3)
				dieTime -= 3;
			AnimationDie((int)(dieTime)* 30, time);
		}

		void CheckPlayerOnFire(float x, float y)
		{
			for (int i = (y - 100) / CELL_SIZE; i < (y - 100 + heigth) / CELL_SIZE; i++)
			{
				for (int j = x / CELL_SIZE; j < (x + width) / CELL_SIZE; j++)
				{
					char SymbolInMap = TileBoomMap[i][j];
					if ((SymbolInMap == 'H') || (SymbolInMap == 'R') || (SymbolInMap == 'L') || (SymbolInMap == 'V') || (SymbolInMap == 'D') || (SymbolInMap == 'U') || (SymbolInMap == 'S'))
					{
						soundDie.play();
						life = false;
						currentFrame = 0;
						break;
					}
				}
				if (!life)
					break;

			}
		}

		bool CheckIntersectionPlayerAndBombX(int number)
		{
			if ((x + width > bomb[number].GetPositionX()) && (x < bomb[number].GetPositionX() + bomb[number].GetWidth()))
				return true;
			else
				return false;
		}

		bool CheckIntersectionPlayerAndBombY(int number)
		{
			if ((y + heigth > bomb[number].GetPositionY()) && (y < bomb[number].GetPositionY() + bomb[number].GetHeigth()))
				return true;
			else
				return false;
		}

		bool CheckBombInPlayer(int number)
		{
			if (((bomb[number].GetPositionX() + bomb[number].GetWidth() > x) && (bomb[number].GetPositionX() < x + width)) && ((bomb[number].GetPositionY() + bomb[number].GetWidth() > y) && (bomb[number].GetPositionY() < y + heigth)))
				return true;
			else
				return false;
		}

		void CheckCollisionPlayerWithBomb(float Dx, float Dy, float time)
		{
			for (int i = 0; i < 5; i++)
			{
				if (bomb[i].inPlayer)
				{
					bomb[i].inPlayer = CheckBombInPlayer(i);
				}
				else
				{
					if (CheckIntersectionPlayerAndBombY(i) && CheckIntersectionPlayerAndBombX(i) && bomb[i].visible)
					{
						if (Dy > 0)
						{
							//bomb[i].SetPosition(bomb[i].GetPositionX(), bomb[i].GetPositionY() + Dy * time);
							//CheckCollisionBombWithMap(Dx, Dy, i);
							y = bomb[i].GetPositionY() - heigth;
							break;
						}
						if (Dy < 0)
						{
							//bomb[i].SetPosition(bomb[i].GetPositionX(), bomb[i].GetPositionY() + Dy * time);
							//CheckCollisionBombWithMap(Dx, Dy, i);
							y = bomb[i].GetPositionY() + bomb[i].GetHeigth();
							break;
						}																									// закомментировано, из-за осознания того, что бомбы не двигаются ((((
						if (Dx > 0)
						{
							//bomb[i].SetPosition(bomb[i].GetPositionX() + Dx * time, bomb[i].GetPositionY());
							//CheckCollisionBombWithMap(Dx, Dy, i);
							x = bomb[i].GetPositionX() - width;
							break;
						}
						if (Dx < 0)
						{
							//bomb[i].SetPosition(bomb[i].GetPositionX() + Dx * time, bomb[i].GetPositionY());
							//CheckCollisionBombWithMap(Dx, Dy, i);
							x = bomb[i].GetPositionX() + bomb[i].GetWidth();
							break;
						}
					}
				}
			}
		}



		void CheckCollisionPlayerWithMap(float Dx, float Dy)
		{
			y -= 100;
			for (int i = y / CELL_SIZE; i < (y + heigth) / CELL_SIZE; i++)
				for (int j = x / CELL_SIZE; j < (x + width) / CELL_SIZE; j++)
				{
					if ((TileMap[i][j] == 'M') || (TileMap[i][j] == 'S') || (TileMap[i][j] == '1') || (TileMap[i][j] == '2') || (TileMap[i][j] == '3') || (TileMap[i][j] == '4') || (TileMap[i][j] == '5'))
					{
						if (Dy > 0)
							if ((y < i * CELL_SIZE) && ((x < (j)* CELL_SIZE + CELL_SIZE - 3) && (x + width > j * CELL_SIZE + 3)))
								y = i * CELL_SIZE - heigth;
						if (Dy < 0)
							if ((y < i * CELL_SIZE + CELL_SIZE - 7) && ((x < (j)* CELL_SIZE + CELL_SIZE - 3) && (x + width > j * CELL_SIZE + 3)))
								y = i * CELL_SIZE + CELL_SIZE - 7;
						if (Dx > 0)
							if ((y < i *CELL_SIZE + CELL_SIZE - 7) && (x < j * CELL_SIZE + CELL_SIZE - 3) && (x > j * CELL_SIZE - width + 3))
								x = j * CELL_SIZE - width + 3;
						if (Dx < 0)
							if ((y < i * CELL_SIZE + CELL_SIZE - 7) && (x < j * CELL_SIZE + CELL_SIZE - 3) && (x > j * CELL_SIZE - width + 3))
								x = j * CELL_SIZE + CELL_SIZE - 3;
					}
					if ((TileBonusMap[i][j] == 'S') && (TileMap[i][j] != 'S'))
					{
						soundBonus.play();
						if (speedState < 5)
							speedState++;
						TileBonusMap[i][j] = ' ';
					}
					if ((TileBonusMap[i][j] == 'F') && (TileMap[i][j] != 'S'))
					{
						soundBonus.play();
						if (fireState < 5)
							fireState++;
						TileBonusMap[i][j] = ' ';
					}
					if ((TileBonusMap[i][j] == 'B') && (TileMap[i][j] != 'S'))
					{
						soundBonus.play();
						if (bombState < 5)
							bombState++;
						TileBonusMap[i][j] = ' ';
					}
				}

			y += 100;
		}

		void AnimationWalk(int Shift, float time)
		{
			currentFrame += 0.005*time;
			if (currentFrame > 3)
				currentFrame -= 3;
			sprite.setTextureRect(sf::IntRect(Shift + shift, int(currentFrame) * 30, PICTURE_BOMBERMAN_WIDTH, PICTURE_BOMBERMAN_HEIGTH));
		}

		void Control(float time)
		{
			if (name == "first")
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					state = left;
					speed = START_SPEED + BONUS_SPEED * speedState;
					AnimationWalk(30, time);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					state = rigth;
					speed = START_SPEED + BONUS_SPEED * speedState;
					AnimationWalk(90, time);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					state = up;
					speed = START_SPEED + BONUS_SPEED * speedState;
					AnimationWalk(60, time);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					state = down;
					speed = START_SPEED + BONUS_SPEED * speedState;
					AnimationWalk(0, time);
				}
			}
			if (name == "second")
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					state = left;
					speed = START_SPEED + BONUS_SPEED * speedState;
					AnimationWalk(30, time);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					state = rigth;
					speed = START_SPEED + BONUS_SPEED * speedState;
					AnimationWalk(90, time);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					state = up;
					speed = START_SPEED + BONUS_SPEED * speedState;
					AnimationWalk(60, time);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					state = down;
					speed = START_SPEED + BONUS_SPEED * speedState;
					AnimationWalk(0, time);
				}
			}
		}

		int GetBombState()
		{
			return bombState;
		}

		int GetSpeedState()
		{
			return speedState;
		}

		int GetFireState()
		{
			return fireState;
		}

		bool GetLife()
		{
			return life;
		}

		sf::String GetName()
		{
			return name;
		}
	};

	public:
		Player bomberman[2];
		sf::Image heroImage;
	Game(sf::String Name)
	{
		heroImage.loadFromFile(Name);
		bomberman[0].Create(heroImage, "first",25, 606, PICTURE_BOMBERMAN_WIDTH, PICTURE_BOMBERMAN_HEIGTH, 0);
		bomberman[1].Create(heroImage, "second", 509, 122, PICTURE_BOMBERMAN_WIDTH, PICTURE_BOMBERMAN_HEIGTH, 210);
	}

	void Reset()
	{
		bomberman[0].Reset(25, 606, 0);
		bomberman[1].Reset(509, 122, 210);
	}
};

int main()
{
	sf::RenderWindow windowGame(sf::VideoMode(550, 650), "Bomberman 0.1");
	
	sf::Music fonMusic;
	fonMusic.openFromFile("data/Bomber.ogg");
	fonMusic.setLoop(true);
	fonMusic.play();

	sf::Clock clock;
	sf::Time Time;
	float currentFrame = 0;
	bool isSpace = false, isNum = false, inPlayer = false, boomDraw = false, showFPS = false;
	sf::Font font;

	//font.loadFromFile("data/Inky.ttf");
	font.loadFromFile("data/Brassie.ttf");
	//font.loadFromFile("data/danger.ttf");
	sf::Text text("", font, 20);
	text.setColor(sf::Color::White);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	GenerateBonusMap();

	Game game("images/bomberman2_various_sheet.png");

	sf::Image mapImage, panelImage, boomImage;
	mapImage.loadFromFile("images/bomberman_tiles_sheet_add.png");
	panelImage.loadFromFile("images/panel_state_bomberman.png");
	boomImage.loadFromFile("images/bomberman_bomb_sheet.png");

	sf::Texture map, panel, boom;
	map.loadFromImage(mapImage);
	panel.loadFromImage(panelImage);
	boom.loadFromImage(boomImage);

	sf::Sprite mapSprite, panelSprite, boomSprite;
	mapSprite.setTexture(map);
	panelSprite.setTexture(panel);
	boomSprite.setTexture(boom);
	panelSprite.setPosition(0, 0);
	mapSprite.setScale(CELL_SIZE / 16, CELL_SIZE / 16); // size picture is 20x20
	boomSprite.setScale(CELL_SIZE / 16, CELL_SIZE / 16); // size picture is 20x20

	float fullTime = 0;
	while (windowGame.isOpen())
	{
		Time = clock.getElapsedTime();
		float time = Time.asMicroseconds();
		float realTime = Time.asSeconds();
		fullTime += realTime;
		float Framerate = 1.f / clock.getElapsedTime().asSeconds();
		//	std::cout << fullTime << std::endl;
		clock.restart();
		time = time / 800;
		sf::Event event;
		while (windowGame.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Escape))
				windowGame.close();

			if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Space && !isSpace)
			{
				for (int i = 0; i < game.bomberman[0].GetBombState(); i++)
				{
					for (int j = 0; j < 5; j++)
						if ((game.bomberman[0].bomb[j].inPlayer) && (i != j))
						{
							inPlayer = true;
							break;
						}
					if (!(inPlayer))
						if (!(game.bomberman[0].bomb[i].enabled) && !(isSpace))
						{
							game.bomberman[0].bomb[i].visible = true;
							game.bomberman[0].bomb[i].enabled = true;
							game.bomberman[0].bomb[i].inPlayer = true;
							game.bomberman[0].bomb[i].fireState = game.bomberman[0].GetFireState();
							float xFloat = ((game.bomberman[0].sprite.getPosition().x - PICTURE_BOMBERMAN_WIDTH / 2) / CELL_SIZE);
							float yFloat = ((game.bomberman[0].sprite.getPosition().y - 100 - PICTURE_BOMBERMAN_HEIGTH / 2) / CELL_SIZE);
							game.bomberman[0].bomb[i].SetPosition((xFloat - (int)xFloat < 0.5) ? (int)xFloat * CELL_SIZE : ((int)xFloat + 1) * CELL_SIZE, (yFloat - (int)yFloat < 0.5) ? (int)yFloat * CELL_SIZE + 100 : ((int)yFloat + 1) * CELL_SIZE + 100);
							isSpace = true;
							break;
						}
				}
				inPlayer = false;
			}
			if (event.type == event.KeyReleased && event.key.code == sf::Keyboard::Space)
				isSpace = false;

			if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Numpad0 && !isNum)
			{
				for (int i = 0; i < game.bomberman[1].GetBombState(); i++)
				{
					for (int j = 0; j < 5; j++)
						if ((game.bomberman[1].bomb[j].inPlayer) && (i != j))
						{
							inPlayer = true;
							break;
						}
					if (!(inPlayer))
						if (!(game.bomberman[1].bomb[i].enabled) && !(isNum))
						{
							game.bomberman[1].bomb[i].visible = true;
							game.bomberman[1].bomb[i].enabled = true;
							game.bomberman[1].bomb[i].inPlayer = true;
							game.bomberman[1].bomb[i].fireState = game.bomberman[1].GetFireState();
							float xFloat = ((game.bomberman[1].sprite.getPosition().x - PICTURE_BOMBERMAN_WIDTH / 2) / CELL_SIZE);
							float yFloat = ((game.bomberman[1].sprite.getPosition().y - 100 - PICTURE_BOMBERMAN_HEIGTH / 2) / CELL_SIZE);
							game.bomberman[1].bomb[i].SetPosition((xFloat - (int)xFloat < 0.5) ? (int)xFloat * CELL_SIZE : ((int)xFloat + 1) * CELL_SIZE, (yFloat - (int)yFloat < 0.5) ? (int)yFloat * CELL_SIZE + 100 : ((int)yFloat + 1) * CELL_SIZE + 100);
							isNum = true;
							break;
						}
				}
				inPlayer = false;
			}
			if (event.type == event.KeyReleased && event.key.code == sf::Keyboard::Numpad0)
				isNum = false;
			if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::F9)
				if (showFPS)
					showFPS = false;
				else
					showFPS = true;
			if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::F1)
			{
				windowGame.setVisible(false);
				ShowHelp();
				windowGame.setVisible(true);
				clock.restart();
			}
				
		}
		if ((game.bomberman[0].GetLife()) && (game.bomberman[1].GetLife()))
		{
			game.bomberman[0].Update(time, realTime);
			game.bomberman[1].Update(time, realTime);
		}
		else
		{	
			if (!(game.bomberman[0].GetLife()))
				game.bomberman[0].Die(time);
			else
				game.bomberman[1].Die(time);
			fonMusic.stop();
			windowGame.setVisible(false);
			ShowWinner((game.bomberman[0].GetLife() ? game.bomberman[1].GetName() : game.bomberman[0].GetName()));
			game.Reset();
			ResetMaps();
			GenerateBonusMap();
			clock.restart();
			fonMusic.play();
			windowGame.setVisible(true);
		}
		windowGame.clear();
		windowGame.draw(panelSprite);
		for (int i = 0; i < HEIGHT_MAP; i++)
		{
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				boomDraw = false;
				if (TileMap[i][j] == 'M')
					mapSprite.setTextureRect(sf::IntRect(28, 0, 16, 16));
				if (TileMap[i][j] == 'S')
					mapSprite.setTextureRect(sf::IntRect(58, 0, 16, 16));
				if (TileMap[i][j] == '1')
					mapSprite.setTextureRect(sf::IntRect(88, 0, 16, 16));
				if (TileMap[i][j] == '2')
					mapSprite.setTextureRect(sf::IntRect(118, 0, 16, 16));
				if (TileMap[i][j] == '3')
					mapSprite.setTextureRect(sf::IntRect(148, 0, 16, 16));
				if (TileMap[i][j] == '4')
					mapSprite.setTextureRect(sf::IntRect(178, 0, 16, 16));
				if (TileMap[i][j] == '5')
					mapSprite.setTextureRect(sf::IntRect(208, 0, 16, 16));
				if (TileMap[i][j] == ' ')
					mapSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
				if ((TileMap[i][j] == ' ') && (TileBonusMap[i][j] == 'B'))
					mapSprite.setTextureRect(sf::IntRect(328, 0, 16, 16));
				if ((TileMap[i][j] == ' ') && (TileBonusMap[i][j] == 'S'))
					mapSprite.setTextureRect(sf::IntRect(268, 0, 16, 16));
				if ((TileMap[i][j] == ' ') && (TileBonusMap[i][j] == 'F'))
					mapSprite.setTextureRect(sf::IntRect(298, 0, 16, 16));
				if ((TileBoomMap[i][j] == 'S') && (TileMap[i][j] == ' '))
				{
					boomSprite.setTextureRect(sf::IntRect(330, 30, 16, 16));
					boomDraw = true;
				}
				if ((TileBoomMap[i][j] == 'H') && (TileMap[i][j] == ' '))
				{
					boomSprite.setTextureRect(sf::IntRect(360, 60, 16, 16));
					boomDraw = true;
				}
				if ((TileBoomMap[i][j] == 'R') && (TileMap[i][j] == ' '))
				{
					boomSprite.setTextureRect(sf::IntRect(360, 30, 16, 16));
					boomDraw = true;
				}
				if ((TileBoomMap[i][j] == 'V') && (TileMap[i][j] == ' '))
				{
					boomSprite.setTextureRect(sf::IntRect(360, 0, 16, 16));
					boomDraw = true;
				}
				if ((TileBoomMap[i][j] == 'L') && (TileMap[i][j] == ' '))
				{
					boomSprite.setTextureRect(sf::IntRect(300, 30, 16, 16));
					boomDraw = true;
				}
				if ((TileBoomMap[i][j] == 'U') && (TileMap[i][j] == ' '))
				{
					boomSprite.setTextureRect(sf::IntRect(330, 0, 16, 16));
					boomDraw = true;
				}
				if ((TileBoomMap[i][j] == 'D') && (TileMap[i][j] == ' '))
				{
					boomSprite.setTextureRect(sf::IntRect(330, 60, 16, 16));
					boomDraw = true;
				}
				mapSprite.setPosition(j * CELL_SIZE, i * CELL_SIZE + 100);
				windowGame.draw(mapSprite);
				if (boomDraw)
				{
					boomSprite.setPosition(j * CELL_SIZE, i * CELL_SIZE + 100);
					windowGame.draw(boomSprite);
				}
			}
		}
		for (int i = 0; i < 5; i++)
		{
			if (game.bomberman[0].bomb[i].visible)
				windowGame.draw(game.bomberman[0].bomb[i].sprite);
			if (game.bomberman[1].bomb[i].visible)
				windowGame.draw(game.bomberman[1].bomb[i].sprite);
		}
		windowGame.draw(game.bomberman[0].sprite);
		windowGame.draw(game.bomberman[1].sprite);
		if (showFPS) 
		{
			std::string tempString;
			tempString = std::to_string((int)Framerate);
			text.setString(tempString);
			text.setPosition(1, 1);
			windowGame.draw(text);
		}
		text.setString("Press F1 to help");
		text.setPosition(205, 5);
		windowGame.draw(text);


		sf::Text textState("", font, 16);
		std::string tempString;

		textState.setString("State firsts bomberman :");
		textState.setPosition(30, 30);
		windowGame.draw(textState);

		tempString = std::to_string(game.bomberman[0].GetBombState());
		textState.setString("Bomb state : " + tempString);
		textState.setPosition(30, 45);
		windowGame.draw(textState);

		tempString = std::to_string(game.bomberman[0].GetFireState() - 1);
		textState.setString("Fire state : " + tempString);
		textState.setPosition(30, 60);
		windowGame.draw(textState);

		tempString = std::to_string(game.bomberman[0].GetSpeedState() + 1);
		textState.setString("Speed state : " + tempString);
		textState.setPosition(30, 75);
		windowGame.draw(textState);

		textState.setString("State second bomberman :");
		textState.setPosition(350, 30);
		windowGame.draw(textState);

		tempString = std::to_string(game.bomberman[1].GetBombState());
		textState.setString("Bomb state : " + tempString);
		textState.setPosition(350, 45);
		windowGame.draw(textState);

		tempString = std::to_string(game.bomberman[1].GetFireState() - 1);
		textState.setString("Fire state : " + tempString);
		textState.setPosition(350, 60);
		windowGame.draw(textState);

		tempString = std::to_string(game.bomberman[1].GetSpeedState() + 1);
		textState.setString("Speed state : " + tempString);
		textState.setPosition(350, 75);
		windowGame.draw(textState);

		windowGame.display();
	}
	return 0;
}