//#ifndef SFML_GRAPHICS
//#	define SFML_GRAPHICS
#	include <SFML/Graphics.hpp>
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
		bool visible;
		Bomb()
		{
		}

		/*Bomb(sf::String F, float X, float Y, float Width, float Heigth)
		{
			x = X; y = Y;
			File = F;
			width = Width; heigth = Heigth;
			frame = 0; visible = false; nativeTime = 0;
			image.loadFromFile("images/" + File);
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(0, 30, Width, Heigth));
			sprite.setOrigin(width / 2, heigth / 2);
			sprite.setPosition(Y + width / 2, Y + heigth / 2);
		}*/

		void Create(sf::String F, float X, float Y, float Width, float Heigth)
		{
			x = X; y = Y;
			File = F;
			width = Width; heigth = Heigth;
			frame = 0; visible = false; nativeTime = 0;
			image.loadFromFile("images/" + File);
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(0, 30, Width, Heigth));
			sprite.setOrigin(width / 2, heigth / 2);
			sprite.setPosition(X + width / 2, Y + heigth / 2);
		}

		void SetPositionBomb(float X, float Y)
		{
			x = X; y = Y;
		}

		void Update(float time)
		{
			nativeTime += time;
			if (visible == true)
				if (nativeTime < 3)
					sprite.setPosition(x + width / 2, y + heigth / 2);
				else
				{
					visible = false;
					nativeTime = 0;
				}
		}
	};

private:
	float x, y, width, heigth, dx, dy, currentFrame;
	int bombState, speedState, fireState;
	bool life;
public:
	float speed = 0;
	Bomb bomb[5];
	int counterBomb = 0;
	bool isMove, isSelected;
	enum {left, rigth, up, down, stay} state;
	sf::String File;
	sf::Texture texture;
	sf::Sprite sprite;


	Player(sf::Image &image, float X, float Y, float Width, float Heigth)
	{
		bombState = 0; speedState = 0; fireState = 0;
		life = true;
		width = Width; heigth = Heigth;
		x = X; y = Y; currentFrame = 0;
		isMove = false; isSelected = false;
		state = stay;
		for (int i = 0; i < 5; i++)
		{
			bomb[i].Create("bomberman_bomb_sheet.png", X, Y, 16, 16);
		}
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, width, heigth));
		sprite.setOrigin(width / 2, heigth / 2);
		sprite.setPosition(X + width / 2, Y + heigth / 2);
	}

	void Update(float time)
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
		case stay:
			break;
		}
		x += dx * time;
		CheckCollisionWithMap(dx, 0);
		y += dy * time;
		CheckCollisionWithMap(0, dy);
		speed = 0;
		sprite.setPosition(x + width / 2, y + heigth / 2);
		CheckBomb();
	}

	void CheckCollisionWithMap(float Dx, float Dy)
	{
		y -= 100;
		for (int i = y / CELL_HEIGTH_WIDTH; i < (y + heigth) / CELL_HEIGTH_WIDTH; i++)
			for (int j = x / CELL_HEIGTH_WIDTH; j < (x + width) / CELL_HEIGTH_WIDTH; j++)
				if ((TileMap[i][j] == 'M') || (TileMap[i][j] == 'S'))
				{
					if (dy > 0)
						if (y < i * CELL_HEIGTH_WIDTH)
							y = i * CELL_HEIGTH_WIDTH - heigth;
					if (dy < 0)
						if (y < i * CELL_HEIGTH_WIDTH + CELL_HEIGTH_WIDTH - 7)
							y = i * CELL_HEIGTH_WIDTH + CELL_HEIGTH_WIDTH - 7;
					if (dx > 0)
						if (y - i *CELL_HEIGTH_WIDTH < CELL_HEIGTH_WIDTH - 7)
							x = j * CELL_HEIGTH_WIDTH - width;
					if (dx < 0)
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

	void CheckBomb()
	{
		for (int i = 0; i < 5; i++)
		{
			if (!(bomb[i].visible))
			{
				for (int j = i + 1; j < 4; j++)
					bomb[j - 1] = bomb[j];
			}
		
		}
	}

	/*float GetPlayerCoordinateX()
	{
		return x;
	}

	float GetPlayerCoordinateY()
	{
		return y;
	}*/

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
		std::cout << fullTime << std::endl;
		clock.restart();
		time = time / 800;
		sf::Event event;

		while (windowGame.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Escape))
				windowGame.close();
			if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Space && !isSpace)
			{
				if (firstBomberman.counterBomb < 5)
				{
					std::cout << "lol" << firstBomberman.counterBomb << std::endl;
					firstBomberman.bomb[firstBomberman.counterBomb].visible = true;
					firstBomberman.bomb[firstBomberman.counterBomb].SetPositionBomb(firstBomberman.sprite.getPosition().x - 15/2., firstBomberman.sprite.getPosition().y - 15/2);
					isSpace = true;
					firstBomberman.counterBomb++;
				}
			}
			if (event.type == event.KeyReleased && event.key.code == sf::Keyboard::Space)
				isSpace = false;
		}
		firstBomberman.Update(time);
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
			firstBomberman.bomb[i].Update(realTime);
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