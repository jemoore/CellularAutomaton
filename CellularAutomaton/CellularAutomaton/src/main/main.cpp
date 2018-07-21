#include <ModelInterface.h>
#include <ConwayModel.h>

#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
	const float cellSize = 5.0f; // square
	const unsigned int windowH = 1000;
	const unsigned int windowW = 1000;

	const unsigned int rowCnt = windowH / (int)cellSize;
	const unsigned int colCnt = windowW / (int)cellSize;

	jem_models::ConwayModel m(rowCnt, colCnt);
	m.initialize();

	typedef std::vector<sf::RectangleShape> CellRow;
	std::vector<CellRow> board;
	const float xOffset = cellSize / 2.0f;
	const float yOffset = cellSize / 2.0f;

	for (unsigned int i = 0; i < rowCnt; i++) {
		CellRow row;
		for (unsigned int j = 0; j < colCnt; j++) {
			sf::RectangleShape shape(sf::Vector2f(cellSize, cellSize));
			sf::Color c = sf::Color::Green;
			if (m.getColor(i, j) == jem_models::white) {
				c = sf::Color::White;
			}
			else if (m.getColor(i, j) == jem_models::black) {
				c = sf::Color::Black;
			}
			shape.setFillColor(c);
			shape.setPosition(xOffset + (i * cellSize), yOffset + (j * cellSize));

			row.push_back(shape);
		}
		board.push_back(row);
	}
	sf::RenderWindow window(sf::VideoMode(windowW, windowH), "SFML works!");


	const float switchTime = 500.0f;//700.0f;
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

			//const int x = rand() % numWCells;
			//const int y = rand() % numHCells;
			//board[y][x].setFillColor(sf::Color::Blue);
			for (unsigned int i = 0; i < rowCnt; i++) {
				for (unsigned int j = 0; j < colCnt; j++) {
					sf::Color c = sf::Color::Green;

					if (m.getColor(i, j) == jem_models::white) {
						c = sf::Color::White;
					}
					else if (m.getColor(i, j) == jem_models::black) {
						c = sf::Color::Black;
					}
					board[i][j].setFillColor(c);

					window.draw(board[i][j]);
				}
			}

			window.display();

			m.runModel();

		}
	}

	return 0;
}