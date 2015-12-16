//#ifndef SFML_GRAPHICS
//#	define SFML_GRAPHICS
#include <SFML/Graphics.hpp>
//#endif // !SFML_GRAPHICS
#include "Map.h"
#include <iostream>

#define CELL_HEIGTH_WIDTH 22.0
#define PICTURE_BOMBERMAN_HEIGTH 20.0
#define PICTURE_BOMBERMAN_WIDTH 17.0
#define dX 0.1
#define dY 0.1
#define START_SPEED 0.05
#define LEFT_KEY 0
#define RIGHT_KEY 1
#define UP_KEY 2
#define DOWN_KEY 3
#define COUNT_CELLS 25

class Player
{
	class Bomb
	{

	private:
		float x, y, width, heigth;
		float nativeTime;

	public:
		int frame;
		int fire;
		sf::String File;
		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;
		bool visible, inPlayer;

		Bomb()
		{
		}

		void Create(sf::String F, float X, float Y, float Width, float Heigth)
		{
			x = X; y = Y;
			File = F;
			width = Width; heigth = Heigth;
			frame = 0; nativeTime = 0;
			visible = false; inPlayer = false;
			image.loadFromFile("images/" + File);
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(0, 30, Width, Heigth));
			sprite.setOrigin(width / 2, heigth / 2);
			sprite.setPosition(X + width / 2, Y + heigth / 2);
		}

		void SetPosition(float X, float Y)
		{
			x = X; y = Y;
		}

		void Update(float time)
		{
			if (visible == true)
			{
				nativeTime += time;
				if (nativeTime < 6660)
					sprite.setPosition(x + width / 2, y + heigth / 2);
				else
				{
					visible = false;
					nativeTime = 0;
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
	};

private:
	float x, y, width, heigth, dx, dy, currentFrame;
	int bombState, speedState, fireState;
	bool life;

public:
	float speed = 0;
	Bomb bomb[5];
	bool isMove, isSelected, isSpace;
	enum { left, rigth, up, down, stay } state;
	sf::String File;
	sf::Texture texture;
	sf::Sprite sprite;

	Player(sf::Image &image, float X, float Y, float Width, float Heigth)
	{
		bombState = 5; speedState = 1; fireState = 1;
		life = true;
		width = Width; heigth = Heigth;
		x = X; y = Y; currentFrame = 0, speed = 0;
		isMove = false; isSelected = false, isSpace = false;
		state = stay;
		for (int i = 0; i < 5; i++)
		{
			bomb[i].Create("bomberman_bomb_sheet.png", 0, 0, 16, 16);
		}
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, width, heigth));
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
		y += dy * time;
		CheckCollisionPlayerWithMap(0, dy);
		CheckCollisionPlayerWithBomb(0, dy, time);
		speed = 0;
		for (int i = 0; i < 5; i++)
		{
			bomb[i].Update(realTime);
		}
		sprite.setPosition(x + width / 2, y + heigth / 2);
	}

	bool CheckIntersectionX(int number)
	{
		if ((x + width > bomb[number].GetPositionX()) && (x < bomb[number].GetPositionX() + bomb[number].GetWidth()))
			return true;
		else
			return false;
	}

	bool CheckIntersectionY(int number)
	{
		if (y + heigth > bomb[number].GetPositionY() && (y < bomb[number].GetPositionY() + bomb[number].GetHeigth()))
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
				if (Dy > 0)
					if (CheckIntersectionY(i) && CheckIntersectionX(i))
					{
						bomb[i].SetPosition(bomb[i].GetPositionX(), bomb[i].GetPositionY() + Dy * time);
						CheckCollisionBombWithMap(Dx, Dy, i);
						y = bomb[i].GetPositionY() - heigth;
						break;
					}
				if (Dy < 0)
					if (CheckIntersectionY(i) && CheckIntersectionX(i))
					{
						bomb[i].SetPosition(bomb[i].GetPositionX(), bomb[i].GetPositionY() + Dy * time);
						CheckCollisionBombWithMap(Dx, Dy, i);
						y = bomb[i].GetPositionY() + bomb[i].GetHeigth();
						break;
					}
				if (Dx > 0)
					if (CheckIntersectionY(i) && CheckIntersectionX(i))
					{
						bomb[i].SetPosition(bomb[i].GetPositionX() + Dx * time, bomb[i].GetPositionY());
						CheckCollisionBombWithMap(Dx, Dy, i);
						x = bomb[i].GetPositionX() - width;
						break;
					}
				if (Dx < 0)
					if (CheckIntersectionY(i) && CheckIntersectionX(i))
					{
						bomb[i].SetPosition(bomb[i].GetPositionX() + Dx * time, bomb[i].GetPositionY());
						CheckCollisionBombWithMap(Dx, Dy, i);
						x = bomb[i].GetPositionX() + bomb[i].GetWidth();
						break;
					}
			}
		}
	}

	void CheckCollisionBombWithMap(float Dx, float Dy, int number)
	{
		float x = bomb[number].GetPositionX(), y = bomb[number].GetPositionY();
		y -= 100;
		for (int i = y / CELL_HEIGTH_WIDTH; i < (y + heigth) / CELL_HEIGTH_WIDTH; i++)
			for (int j = x / CELL_HEIGTH_WIDTH; j < (x + width) / CELL_HEIGTH_WIDTH; j++)
				if ((TileMap[i][j] == 'M') || (TileMap[i][j] == 'S'))
				{
					if (Dy > 0)
						if (y < i * CELL_HEIGTH_WIDTH)
							y = i * CELL_HEIGTH_WIDTH - bomb[number].GetHeigth();
					if (Dy < 0)
						if (y < i * CELL_HEIGTH_WIDTH + CELL_HEIGTH_WIDTH - 7)
							y = i * CELL_HEIGTH_WIDTH + CELL_HEIGTH_WIDTH - 7;
					if (Dx > 0)
						if (y - i *CELL_HEIGTH_WIDTH < CELL_HEIGTH_WIDTH - 7)
							x = j * CELL_HEIGTH_WIDTH - bomb[number].GetWidth();
					if (Dx < 0)
						if (y - i * CELL_HEIGTH_WIDTH < CELL_HEIGTH_WIDTH - 7)
							x = j * CELL_HEIGTH_WIDTH + CELL_HEIGTH_WIDTH;
				}
		y += 100;
		bomb[number].SetPosition(x, y);
	}

	void CheckCollisionPlayerWithMap(float Dx, float Dy)
	{
		y -= 100;
		for (int i = y / CELL_HEIGTH_WIDTH; i < (y + heigth) / CELL_HEIGTH_WIDTH; i++)
			for (int j = x / CELL_HEIGTH_WIDTH; j < (x + width) / CELL_HEIGTH_WIDTH; j++)
				if ((TileMap[i][j] == 'M') || (TileMap[i][j] == 'S'))
				{
					if (Dy > 0)
						if (y < i * CELL_HEIGTH_WIDTH)
							y = i * CELL_HEIGTH_WIDTH - heigth;
					if (Dy < 0)
						if (y < i * CELL_HEIGTH_WIDTH + CELL_HEIGTH_WIDTH - 7)
							y = i * CELL_HEIGTH_WIDTH + CELL_HEIGTH_WIDTH - 7;
					if (Dx > 0)
						if (y - i *CELL_HEIGTH_WIDTH < CELL_HEIGTH_WIDTH - 7)
							x = j * CELL_HEIGTH_WIDTH - width;
					if (Dx < 0)
						if (y - i * CELL_HEIGTH_WIDTH < CELL_HEIGTH_WIDTH - 7)
							x = j * CELL_HEIGTH_WIDTH + CELL_HEIGTH_WIDTH;
				}
		y += 100;
	}

	void Animation(int Shift, float time)
	{
		currentFrame += 0.005*time;
		if (currentFrame > 3)
			currentFrame -= 3;
		sprite.setTextureRect(sf::IntRect(Shift, int(currentFrame) * 30, PICTURE_BOMBERMAN_WIDTH, PICTURE_BOMBERMAN_HEIGTH));
	}

	void Control(float time)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			state = left;
			speed = START_SPEED;
			Animation(30, time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
		{
			state = rigth;
			speed = START_SPEED;
			Animation(90, time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
		{
			state = up;
			speed = START_SPEED;
			Animation(60, time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
		{
			state = down;
			speed = START_SPEED;
			Animation(0, time);
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

};

int main()
{
	sf::RenderWindow windowGame(sf::VideoMode(550, 650), "Bomberman 0.1");

	sf::Clock clock;
	sf::Time Time;
	float currentFrame = 0;
	bool isSpace = false;
	
	//sf::Font font;
	//font.loadFromFile("data/Inky.ttf");
	//font.loadFromFile("data/Brassie.ttf");
	//font.loadFromFile("data/danger.ttf");
	//sf::Text text("", font, 12);
	//text.setColor(sf::Color::White);
	//text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	sf::Image mapImage, panelImage;
	mapImage.loadFromFile("images/bomberman_tiles_sheet_add.png");
	panelImage.loadFromFile("images/panel_state_bomberman.png");
	sf::Texture map, panel;
	map.loadFromImage(mapImage);
	panel.loadFromImage(panelImage);
	sf::Sprite mapSprite, panelSprite;
	mapSprite.setTexture(map);
	panelSprite.setTexture(panel);
	panelSprite.setPosition(0, 0);
	mapSprite.setScale(CELL_HEIGTH_WIDTH / 16, CELL_HEIGTH_WIDTH / 16); // size picture is 20x20

	sf::Image heroImage;
	heroImage.loadFromFile("images/bomberman2_various_sheet.png");
	Player firstBomberman(heroImage, 25, 606, PICTURE_BOMBERMAN_WIDTH, PICTURE_BOMBERMAN_HEIGTH);
	float fullTime = 0;
	while (windowGame.isOpen())
	{
		Time = clock.getElapsedTime();
		float time = Time.asMicroseconds();
		float realTime = Time.asSeconds();
		fullTime += realTime;
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
				for (int i = 0; i < firstBomberman.GetBombState(); i++)
				{
					if (!(firstBomberman.bomb[i].visible) && !(isSpace))
					{
						std::cout << "lol" << i << std::endl;
						firstBomberman.bomb[i].visible = true;
						firstBomberman.bomb[i].inPlayer = true;
						firstBomberman.bomb[i].SetPosition(firstBomberman.sprite.getPosition().x - 15 / 2., firstBomberman.sprite.getPosition().y - 15 / 2);
						isSpace = true;
						break;
					}
				}
			}
			if (event.type == event.KeyReleased && event.key.code == sf::Keyboard::Space)
				isSpace = false;
		}
		firstBomberman.Update(time, realTime);
		windowGame.clear();
		windowGame.draw(panelSprite);
		for (int i = 0; i < HEIGHT_MAP; i++)
		{
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == 'M')
					mapSprite.setTextureRect(sf::IntRect(28, 0, 16, 16));
				if (TileMap[i][j] == 'S')
					mapSprite.setTextureRect(sf::IntRect(58, 0, 16, 16));
				if (TileMap[i][j] == ' ')
					mapSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
				mapSprite.setPosition(j * CELL_HEIGTH_WIDTH, i * CELL_HEIGTH_WIDTH + 100);
				windowGame.draw(mapSprite);
			}
		}
		for (int i = 0; i < 5; i++)
		{
			if (firstBomberman.bomb[i].visible)
				windowGame.draw(firstBomberman.bomb[i].sprite);
		}
		//text.setString("Bomberman");
		//text.setPosition(firstBomberman.GetPlayerCoordinateX() - PICTURE_WIDTH, firstBomberman.GetPlayerCoordinateY() - PICTURE_HEIGTH / 2 - 5);
		//windowGame.draw(text);
		windowGame.draw(firstBomberman.sprite);
		windowGame.display();
	}
	return 0;
}