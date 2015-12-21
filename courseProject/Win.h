#ifndef SFML_GRAPHICS
#	include <SFML\Graphics.hpp>
#endif

void ShowWinner(sf::String name)
{
	sf::RenderWindow windowHelp(sf::VideoMode(550, 180), "You Win!");
	sf::RectangleShape rectangle(sf::Vector2f(550, 180));
	rectangle.setFillColor(sf::Color(185, 185, 185));
	rectangle.setPosition(0, 0);
	sf::Font font;
	//font.loadFromFile("data/Inky.ttf");
	font.loadFromFile("data/Brassie.ttf");
	//font.loadFromFile("data/danger.ttf");

	sf::Text text("", font, 25);
	text.setColor(sf::Color::White);

	while (windowHelp.isOpen())
	{
		sf::Event event;
		while (windowHelp.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || (event.type == event.KeyPressed && ((event.key.code == sf::Keyboard::Return) || (event.key.code == sf::Keyboard::Escape))))
				windowHelp.close();
		}
		windowHelp.clear();
		windowHelp.draw(rectangle);

		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		text.setString("Congratulations!");
		text.setPosition(190, 20);
		windowHelp.draw(text);

		sf::Text winnerText("", font, 30);
		if (name != "first")
			winnerText.setString("The winner was the first player!");
		else
			winnerText.setString("The winner was the second player!");
		winnerText.setStyle(sf::Text::Bold);
		winnerText.setPosition(70, 70);
		windowHelp.draw(winnerText);

		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		text.setString("To continue, press Escape or Enter");
		text.setPosition(100, 130);
		windowHelp.draw(text);

		windowHelp.display();
	}
}