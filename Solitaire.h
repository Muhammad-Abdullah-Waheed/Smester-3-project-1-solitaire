#pragma once
#include<iostream>
#include<deque>
#include <vector>
#include "Deck.h"
#include "Card.h"
#include "Board.h"
#include<stack>
using namespace std;

class Solitaire
{
private:
	Board _board;
	position Source;
	position destination;
	int level;

	bool source_slected;
	bool destination_slected;
	int _moves{};
	int _score{};
	string moves;
	string score;
	string s;
	string d;
	string m;
	string time;


	sf::Texture t{};
	sf::Sprite sp{};

	sf::Font font;
	sf::RenderWindow&window;

	sf::Music music;
	sf::Music click;
	sf::Music error;
	sf::SoundBuffer buffer;
	sf::Sound cardplace;
	sf::Time countdownTime;
	sf::Clock clock;


	vector<vector<position>> undo;
	vector<vector<position>> redo;
public:
	Solitaire(sf::RenderWindow& w, int _level);
	void show_cards();
	void push_into_stock();
	bool Is_valid_source();
	bool Is_vlid_des();
	bool In_rage();
	bool Is_diferent_color(Card* sou, Card* des);
	bool Is_same_color(Card* sou, Card* des);
	bool IS_valid_ranks_decr(Card* sou, Card* des);
	bool IS_valid_ranks_incre(Card* sou, Card* des);
	void move();
	bool ValidMove();
	bool Is_Game_over();
	bool dispaly_time();
	void display_text_by_color(sf::RenderWindow& window, string txt, int row, int col, int size, sf::Color  c);
	void getRowColbyLeftClick_sfml(int& rpos, int& cpos, sf::RenderWindow& window);
	void get_source_sfml();
	void get_des_sfml();
	void get_position(position& P, sf::RenderWindow& window);
	void draw();
	void Lets_Play();
	void main_flow();
	void Undo();
	void Redo();
	~Solitaire();


};
