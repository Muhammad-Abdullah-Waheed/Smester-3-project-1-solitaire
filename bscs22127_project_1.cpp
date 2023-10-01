#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include"Solitaire.h"




#include <vector>
#include <cstdlib>
#include <ctime>




using namespace std;

const static int window_x = 1920, window_y = 1000;
struct Position
{
	int r, c;
};


void display_text(sf::RenderWindow& window, string txt, int row, int col, int size)
{
	sf::Font font;
	font.loadFromFile("Montague.ttf");
	sf::Text text(txt, font, size);
	text.setFillColor(sf::Color::Black);
	text.setPosition(row, col);
	window.draw(text);
}
void load_game(int& level)
{

	sf::RenderWindow win(sf::VideoMode(1900, 1000), "Load Game !!");
	sf::Sprite s;
	sf::Texture t;

	if (!t.loadFromFile("Cards\\b.jpg"))
	{
		cout << "Unable to load ___!";
	}
	Position P{};

	s.setTexture(t);
	s.setScale(1.6, 1.5);
	s.setPosition(0, 0);



    string point{};
	while (win.isOpen())
	{
		sf::Event e;
		while (win.pollEvent(e))
		{
			if (e.type == e.Closed)
			{
				win.close();
			}
			if (e.type == e.MouseButtonPressed)
			{
				sf::Vector2i P = sf::Mouse::getPosition(win);
				P.x /= 60, P.y /= 60;
                point = ("    Source.x= " + std::to_string(P.x) + "  Source.y= " + std::to_string(P.y));
				if ((P.x == 14 || P.x == 15) && P.y == 4)
					level = 1, win.close();
				else if ((P.x == 14 || P.x == 15) && P.y == 6)
					level = 2, win.close();
				else if ((P.x == 14 || P.x == 15) && P.y == 8)
					level = 3, win.close();
				else if ((P.x == 14 || P.x == 15) && P.y == 10)
					exit(-1);
			}

			int box_dimm = 90;
			win.draw(s);
			display_text(win, "solitaire GAME BY MUHAMMAD ABDULLAH WAHEED ", 4 * box_dimm,20, 50);
			display_text(win, "difficuilty level", 8 * box_dimm, 1 * box_dimm, 50);
			display_text(win, "Easy", 9 * box_dimm+30, 3 * box_dimm, 50);
			display_text(win, "Medium", 9 * box_dimm, 4 * box_dimm, 50);
            display_text(win, "Hard", 9 * box_dimm+30, 5 * box_dimm, 50);
			display_text(win, " Exit. ", 9 * box_dimm+10, 7 * box_dimm, 50);
            display_text(win,point, 9 * box_dimm + 10, 10 * box_dimm, 50);
			win.display();

		}
	}

}

int main()
{

    sf::RenderWindow window(sf::VideoMode(window_x, window_y), "Solitaire game By Muhammad Abdullah Waheed");
    

    sf::Vector2f v;
    v.x = window_x;
    v.y = window_y;

    int level=1;
    load_game(level);
    Solitaire S(window,level);
    S.Lets_Play();
    return 0;    
}


int main_1()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Card Drag and Drop");

    sf::Texture cardTexture;
    if (!cardTexture.loadFromFile("Cards\\ace_of_hearts.png")) {
        std::cerr << "Failed to load card texture." << std::endl;
        return 1;
    }

    sf::Sprite card(cardTexture);
    card.setScale(0.5f, 0.5f); // Adjust the scale as needed

    bool isDragging = false;
    sf::Vector2f offset;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    sf::FloatRect cardBounds = card.getGlobalBounds();

                    if (cardBounds.contains(mousePosition))
                    {
                        isDragging = true;
                        offset = card.getPosition() - mousePosition;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    isDragging = false;
                }
            }
        }

        if (isDragging)
        {
            sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            card.setPosition(mousePosition + offset);
        }

        window.clear();
        window.draw(card);
        window.display();
    }

    return 0;
}









class Cards {
public:
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Vector2f target;
    bool isMoving;

    Cards(const sf::Texture& texture, const sf::Vector2f& pos)
        : sprite(texture), position(pos), isMoving(false) {
        sprite.setScale(0.25, 0.25);
    }

    void shuffleTo(const sf::Vector2f& dest) {
        target = dest;
        isMoving = true;
    }

    void update() {
        if (isMoving) {
            sf::Vector2f direction = target - position;
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if (distance <= 1.0f) {
                position = target;
                isMoving = false;
            }
            else {
                direction /= distance;
                position += direction * 2.0f;
            }
        }
    }
};

