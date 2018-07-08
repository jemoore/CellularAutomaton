#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>

int main()
{
	srand(time(NULL));

	const float cellSize = 10.0f; // square
	const unsigned int windowH = 600;
	const unsigned int windowW = 600;

	const unsigned int numHCells = windowH / (int)cellSize;
	const unsigned int numWCells = windowW / (int)cellSize;

	typedef std::vector<sf::RectangleShape> CellRow;
	std::vector<CellRow> board;
	const float xOffset = cellSize / 2.0f;
	const float yOffset = cellSize / 2.0f;

	for (unsigned int i = 0; i < numWCells; i++) {
		CellRow row;
		for (unsigned int j = 0; j < numHCells; j++) {
			sf::RectangleShape shape(sf::Vector2f(cellSize, cellSize));
			shape.setFillColor(sf::Color::Green);
			shape.setPosition(xOffset + (j * cellSize), yOffset + (i * cellSize));

			row.push_back(shape);
		}
		board.push_back(row);
	}
	sf::RenderWindow window(sf::VideoMode(windowW, windowH), "SFML works!");


	const float switchTime = 700.0f;
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

			window.clear();
			const int x = rand() % numWCells;
			const int y = rand() % numHCells;
			board[y][x].setFillColor(sf::Color::Blue);

			for (unsigned int i = 0; i < numWCells; i++) {
				for (unsigned int j = 0; j < numHCells; j++) {
					window.draw(board[i][j]);
				}
			}

			window.display();
		}
	}

	return 0;
}