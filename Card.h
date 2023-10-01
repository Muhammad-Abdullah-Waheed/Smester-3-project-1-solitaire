#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include"utility.h"
#include<deque>

using namespace std;
const static int dim_x = 10, dim_y = 6;
struct position
{
	int x, y;
};
class Card
{
private:
	char rank;
	char suit;
	bool displayed;
	bool is_moving;

	sf::Vector2f V{};
	sf::Vector2f destination{};
	sf::Texture t{};
	sf::Sprite sp{};


	sf::Texture t1{};
	sf::Sprite sp1{};




	string load_image(char _rank, char _suit);
public:
	Card(char _rank = '?', char _suit = '?', bool dispaly = false);
	sf::Sprite get_sprite() { return sp; }
	bool get_is_moving();
	void set_is_moving(bool a);
	void change_displayed();
	bool Get_displayed();
	int Get_Rank_number();
	char Get_Suit();
	char Get_Rank();
	void Set_vector(sf::Vector2f P);
	sf::Vector2f get_vector();
	void Set_destination(sf::Vector2f P);
	sf::Vector2f get_destination();
	Card(char _rank, char _suit, bool  dispaly, int row, int col);
	void draw_back(sf::RenderWindow& window, int row, int col);
	void draw_Card(sf::RenderWindow& window, int row, int col);
	void draw_Card(sf::RenderWindow& window);
	void update();
	void shuffleTo(const sf::Vector2f& dest);

	~Card(void);
};

