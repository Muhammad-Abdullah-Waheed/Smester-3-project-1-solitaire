#include"Deck.h"


Deck::Deck() :deck(TOTAL_CARDS)
{
	create_all_cards();
	Shuffle();
}
void Deck::create_all_cards()
{
	int k{ 0 };
	for (int i{ 0 }; i < SUIT_SIZE; ++i)
	{
		for (int j{ 0 }; j < RANK_SIZE; ++j)
		{
			deck[k] = Card(RANKS[j], SUITS[i]);
			++k;
		}
	}
}
void Deck::Shuffle()
{
	int max = SUIT_SIZE * RANK_SIZE;
	int ran = rand() % 500;
	for (int k = 0; k < ran; ++k)
		for (int i = 0; i < max - 1; i++)
		{
			int rand_i = rand() % 52;
			std::swap(deck[i], deck[rand_i]);
		}
}
void Deck::allocate_board(vector<deque<Card*>>& _Board, deque<Card*>& re)
{
	int count{ 0 };
	for (int i = 1; i < 8; ++i)
	{
		for (int k = 0; k < i; ++k)
		{
			bool display = false;
			if (k == i - 1)
				display = true;
			_Board[i].push_back(new Card(deck[count].Get_Rank(), deck[count].Get_Suit(), display, i, k));
			count++;
		}
	}
	for (int i = 0, j = count; j < deck.size(); i++, ++j)
	{
		deck[count].change_displayed();
		re.push_back(new Card(deck[count].Get_Rank(), deck[count].Get_Suit(), true, i, 0));
		count++;
	}

}
Deck::~Deck() {}