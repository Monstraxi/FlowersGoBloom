#include <chrono>
#include <algorithm>
#include <vector>

#include <SFML/Graphics.hpp>

int main()
{
	std::chrono::microseconds frameTime(16667);
	std::chrono::microseconds lag(0);
	std::chrono::microseconds deltaTime(0);
	std::chrono::steady_clock::time_point previousTime;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "FlowersGoBloom");
	window.setFramerateLimit(60);
	sf::Event event;

	previousTime = std::chrono::steady_clock::now();

	sf::RectangleShape bg({ 800, 600 });
	bg.setPosition(120, 60);
	bg.setFillColor(sf::Color::White);

	sf::RectangleShape player({ 60, 60 });
	player.setOrigin(30, 30);
	player.setFillColor(sf::Color::Yellow);
	player.setOutlineThickness(-5);
	player.setOutlineColor(sf::Color::Black);
	sf::Vector2f playerPos(0, 0);

	std::vector<sf::RectangleShape> flowers;
	std::vector<sf::RectangleShape> enemies;
	std::vector<sf::Vector2f> enemyPos;
	for (int i = 0; i < bg.getSize().y / 100; i++)
	{
		sf::RectangleShape enemy({ 60, 60 });
		enemy.setOrigin(30, 30);
		enemy.setFillColor(sf::Color::Red);
		enemy.setOutlineThickness(-5);
		enemy.setOutlineColor(sf::Color::Black);
		enemies.push_back(enemy);
		enemyPos.push_back(sf::Vector2f( bg.getSize().x / 100, i ));
	}

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				for (int i = 0; i < bg.getSize().y / 100; i++)
				{
					enemyPos[i].x--;
				}
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					playerPos.y--;
					break;
				case sf::Keyboard::Left:
					playerPos.x--;
					break;
				case sf::Keyboard::Down:
					playerPos.y++;
					break;
				case sf::Keyboard::Right:
					playerPos.x++;
					break;
				case sf::Keyboard::Space:
					sf::RectangleShape flower({40, 40});
					flower.setOrigin(20, 20);
					flower.setFillColor(sf::Color::Green);
					flower.setOutlineThickness(-5);
					flower.setOutlineColor(sf::Color::Black);
					flower.setPosition(player.getPosition());
					flowers.push_back(flower);
					break;
				}
				break;
			default:
				break;
			}
		}

		playerPos.x = std::clamp(playerPos.x, 0.0f, bg.getSize().x / 100 - 1);
		playerPos.y = std::clamp(playerPos.y, 0.0f, bg.getSize().y / 100 - 1);

		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previousTime);
		previousTime += deltaTime;
		lag += deltaTime;

		player.setPosition(bg.getPosition().x + playerPos.x * 100 + 50, bg.getPosition().y + playerPos.y * 100 + 50);
		for (int i = 0; i < bg.getSize().y / 100; i++)
		{
			enemies[i].setPosition(bg.getPosition().x + enemyPos[i].x * 100 + 50, bg.getPosition().y + enemyPos[i].y * 100 + 50);
		}

		while (lag >= frameTime)
		{
			lag -= frameTime;

			if (lag < frameTime)
			{
				window.clear();
				window.draw(bg);
				for (const sf::RectangleShape flower : flowers)
				{
					window.draw(flower);
				}
				for (int i = 0; i < bg.getSize().y / 100; i++)
				{
					window.draw(enemies[i]);
				}
				window.draw(player);
				window.display();
			}
		}
	}
}
