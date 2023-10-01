#include"Card.h"



string Card::load_image(char _rank, char _suit)
{
	string image_name = "Cards\\";
	switch (_suit)
	{
	case'h':
	{
		switch (_rank)
		{
		case'A':
			image_name += "ace_of_hearts";
			break;
		case'2':
			image_name += "2_of_hearts";
			break;
		case'3':
			image_name += "3_of_hearts";
			break;
		case'4':
			image_name += "4_of_hearts";
			break;
		case'5':
			image_name += "5_of_hearts";
			break;
		case'6':
			image_name += "6_of_hearts";
			break;
		case'7':
			image_name += "7_of_hearts";
			break;
		case'8':
			image_name += "8_of_hearts";
			break;
		case'9':
			image_name += "9_of_hearts";
			break;
		case'T':
			image_name += "10_of_hearts";
			break;
		case'J':
			image_name += "jack_of_hearts2";
			break;
		case'Q':
			image_name += "queen_of_hearts2";
			break;
		case'K':
			image_name += "king_of_hearts2";
			break;
		}
	}
	break;
	case'd':
	{
		switch (_rank)
		{
		case'A':
			image_name += "ace_of_diamonds";
			break;
		case'2':
			image_name += "2_of_diamonds";
			break;
		case'3':
			image_name += "3_of_diamonds";
			break;
		case'4':
			image_name += "4_of_diamonds";
			break;
		case'5':
			image_name += "5_of_diamonds";
			break;
		case'6':
			image_name += "6_of_diamonds";
			break;
		case'7':
			image_name += "7_of_diamonds";
			break;
		case'8':
			image_name += "8_of_diamonds";
			break;
		case'9':
			image_name += "9_of_diamonds";
			break;
		case'T':
			image_name += "10_of_diamonds";
			break;
		case'J':
			image_name += "jack_of_diamonds2";
			break;
		case'Q':
			image_name += "queen_of_diamonds2";
			break;
		case'K':
			image_name += "king_of_diamonds2";
			break;
		}
	}
	break;
	case's':
	{
		switch (_rank)
		{
		case'A':
			image_name += "ace_of_spades";
			break;
		case'2':
			image_name += "2_of_spades";
			break;
		case'3':
			image_name += "3_of_spades";
			break;
		case'4':
			image_name += "4_of_spades";
			break;
		case'5':
			image_name += "5_of_spades";
			break;
		case'6':
			image_name += "6_of_spades";
			break;
		case'7':
			image_name += "7_of_spades";
			break;
		case'8':
			image_name += "8_of_spades";
			break;
		case'9':
			image_name += "9_of_spades";
			break;
		case'T':
			image_name += "10_of_spades";
			break;
		case'J':
			image_name += "jack_of_spades2";
			break;
		case'Q':
			image_name += "queen_of_spades2";
			break;
		case'K':
			image_name += "king_of_spades2";
			break;
		}
	}
	break;
	case'c':
	{
		switch (_rank)
		{
		case'A':
			image_name += "ace_of_clubs";
			break;
		case'2':
			image_name += "2_of_clubs";
			break;
		case'3':
			image_name += "3_of_clubs";
			break;
		case'4':
			image_name += "4_of_clubs";
			break;
		case'5':
			image_name += "5_of_clubs";
			break;
		case'6':
			image_name += "6_of_clubs";
			break;
		case'7':
			image_name += "7_of_clubs";
			break;
		case'8':
			image_name += "8_of_clubs";
			break;
		case'9':
			image_name += "9_of_clubs";
			break;
		case'T':
			image_name += "10_of_clubs";
			break;
		case'J':
			image_name += "jack_of_clubs2";
			break;
		case'Q':
			image_name += "queen_of_clubs2";
			break;
		case'K':
			image_name += "king_of_clubs2";
			break;
		}

	}
	break;
	case'A':
	{

	}
	default:
		break;
	}
	return image_name + ".png";
}
Card::Card(char _rank , char _suit , bool dispaly ) :rank(_rank), suit(_suit), displayed(dispaly) {}
bool Card::get_is_moving() { return is_moving; }
void Card::set_is_moving(bool a) { is_moving = a; }
void Card::change_displayed()
{
	displayed = true;
}
sf::Vector2f Card::get_vector() 
{ 
	return V;
}
void Card::Set_destination(sf::Vector2f P)
{
	destination = P;
}
sf::Vector2f Card::get_destination()
{
	return destination;
}
bool Card::Get_displayed()
{
	return displayed;
}
int Card::Get_Rank_number()
{
	switch (rank)
	{
	case 'A':
		return 1;
	case 'T':
		return 10;
	case 'J':
		return 11;
	case 'Q':
		return 12;
	case 'K':
		return 13;
	default:
		return int(rank - '0');
	}
}
char Card::Get_Suit()
{
	return suit;
}
char Card::Get_Rank()
{
	return rank;
}
Card::~Card(void) {}
void Card::Set_vector(sf::Vector2f P)
{
	V.x = P.x;
	V.y = P.y;
}
Card::Card(char _rank, char _suit, bool  dispaly, int row, int col) :rank(_rank), suit(_suit), displayed(dispaly)
{
	is_moving = true;
	string image_name = load_image(_rank, _suit);
	if (!t.loadFromFile(image_name))
	{
		throw("Unable to load img");
	}
	if (!t1.loadFromFile("Cards\\reverse.png"))
	{
		throw("Unable to load img");
	}
	sp1.setTexture(t1);
	sp1.setScale(0.50, 0.54);


	sp.setTexture(t);
	sp.setScale(0.25, 0.29);


	sf::Vector2f temp;
	temp.x = row;
	temp.y = col;
	Set_vector({ 0,1 });
	Set_destination(temp);
}
void Card::draw_back(sf::RenderWindow& window, int row, int col)
{
	sp1.setPosition((row + 1) * 140, (col + 2) * 50);
	window.draw(sp1);
}
void Card::draw_Card(sf::RenderWindow& window, int row, int col)
{
	destination.x = row, destination.y = col;
	Set_vector({ (destination.x + 1) * 140, (destination.y + 2) * 50 });

	sp.setPosition((destination.x + 1) * 140, (destination.y + 2) * 50);
	sp1.setPosition((destination.x + 1) * 140, (destination.y + 2) * 50);
	if (!displayed)
		window.draw(sp1);
	else
		window.draw(sp);
}
void Card::draw_Card(sf::RenderWindow& window)
{
	sp.setPosition((V.x + 1) * 140, (V.y+2)*50);
	sp1.setPosition((V.x + 1) * 140, (V.y + 2) * 50);
	if (!displayed)
		window.draw(sp1);
	else
		window.draw(sp);
}


void Card::update() {
	if (is_moving) {
		sf::Vector2f direction = destination - V;
		float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		if (distance <= 1.0f) {
			V = destination;
			is_moving = false;
			
		}
		else {
			direction /= distance;
			V += direction * .09f;
		}
	}
}

void Card::shuffleTo(const sf::Vector2f& dest) {
	destination = dest;
	is_moving = true;
}