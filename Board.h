#pragma once
#include<iostream>
#include<deque>
#include <vector>
#include "Deck.h"
#include "Card.h"
using namespace std;

class Board
{
private:
	vector<deque<Card*>> B;
	deque<Card*> remaining;

	Card** c;
	sf::Texture t{};
	sf::Sprite sp{};

public:

	Board();
	vector<deque<Card*>>& get_B();
	deque<Card*>& get_remainnig();
	void draw_card(sf::RenderWindow& w);
	
	void starting_animation(sf::RenderWindow& w);
	void Shuffling(sf::RenderWindow& window);
};