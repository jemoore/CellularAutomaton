#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(512, 512), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	float switchTime = 700.0f;
	float deltaTime = 0.0f;
	float totalTime = 0.0f;

	sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asMicroseconds();
		totalTime += deltaTime;

		if (totalTime >= switchTime) {

			totalTime -= switchTime;

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
				shape.move(-0.01f, 0.0f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
				shape.move(0.01f, 0.0f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
				shape.move(0.0f, -0.01f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
				shape.move(0.0f, 0.01f);
			}
		
			window.clear();
			window.draw(shape);
			window.display();
		}
	}

	return 0;
}