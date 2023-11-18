#include <chrono>

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
	bg.setPosition(200, 200);
	bg.setFillColor(sf::Color::White);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}

		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previousTime);
		previousTime += deltaTime;
		lag += deltaTime;

		while (lag >= frameTime)
		{
			lag -= frameTime;

			if (lag < frameTime)
			{
				window.clear();
				window.draw(bg);
				window.display();
			}
		}
	}
}
