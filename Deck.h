#pragma once
#include<iostream>
#include"Card.h"
#include<vector>
using namespace std;



const static int RANK_SIZE = 13;
const static int SUIT_SIZE = 4;
const static char RANKS[] = { 'A','2','3','4','5','6','7','8','9','T','J','Q','K' };
const static char SUITS[] = { 'h','d','s','c' };
const static int TOTAL_CARDS = 52;

class Deck
{
private:
	vector<Card> deck;
	int currentIndex;


public:

	Deck();
	void create_all_cards();
	void Shuffle();
	void allocate_board(vector<deque<Card*>>& _Board, deque<Card*>& re);
	~Deck();
};