#ifndef SFML_GRAPHICS
#	include <SFML\Graphics.hpp>
#endif

void ShowHelp()
{
	sf::RenderWindow windowHelp(sf::VideoMode(550, 340), "Help", sf::Style::Close | sf::Style::Titlebar);
	sf::RectangleShape rectangle(sf::Vector2f(550, 340));
	rectangle.setFillColor(sf::Color(185, 185, 185));
	rectangle.setPosition(0, 0);
	sf::Font font;
	//font.loadFromFile("data/Inky.ttf");
	font.loadFromFile("data/Brassie.ttf");
	//font.loadFromFile("data/danger.ttf");

	sf::Text text("", font, 20);
	text.setColor(sf::Color::White);
	
	while (windowHelp.isOpen())
	{
		sf::Event event;
		while (windowHelp.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Escape))
				windowHelp.close();
		}
		windowHelp.clear();
		windowHelp.draw(rectangle);
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		text.setString("Key config");
		text.setPosition(220, 10);
		windowHelp.draw(text);

		text.setString("First player :");
		text.setPosition(60, 50);
		windowHelp.draw(text);
		text.setString("Second player :");
		text.setPosition(350, 50);
		windowHelp.draw(text);

		text.setStyle(sf::Text::Bold);
		text.setString("Walk Up - W");
		text.setPosition(70, 90);
		windowHelp.draw(text);
		text.setString("Walk Down - S");
		text.setPosition(60, 120);
		windowHelp.draw(text);
		text.setString("Walk Left - A");
		text.setPosition(65, 150);
		windowHelp.draw(text);
		text.setString("Walk Right - D");
		text.setPosition(60, 180);
		windowHelp.draw(text);
		text.setString("Bomb - Space");
		text.setPosition(65, 210);
		windowHelp.draw(text);

		text.setString("Walk Up - Up");
		text.setPosition(360, 90);
		windowHelp.draw(text);
		text.setString("Walk Down - Down");
		text.setPosition(340, 120);
		windowHelp.draw(text);
		text.setString("Walk Left - Left");
		text.setPosition(345, 150);
		windowHelp.draw(text);
		text.setString("Walk Right - Rigth");
		text.setPosition(340, 180);
		windowHelp.draw(text);
		text.setString("Bomb - NUM 0");
		text.setPosition(355, 210);
		windowHelp.draw(text);

		text.setString("Help - F1");
		text.setPosition(230, 240);
		windowHelp.draw(text);

		text.setString("Show FPS - F9");
		text.setPosition(205, 270);
		windowHelp.draw(text);

		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		text.setString("Close Window - ESC");
		text.setPosition(185, 300);
		windowHelp.draw(text);

		windowHelp.display();
	}
}