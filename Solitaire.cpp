#include"Solitaire.h"


Solitaire::Solitaire(sf::RenderWindow& w, int _level) :_board(), Source(), destination(), window(w), level(_level), source_slected(false), destination_slected(false)
{
	font.loadFromFile("Montague.ttf");
	if (!t.loadFromFile("Cards\\background.jpg"))
	{
		throw("Unable to load img");
	}
	if (!buffer.loadFromFile("Bonus\\cardPlace1.ogg")) {
		std::cerr << "Failed to load audio file." << std::endl;
		return;
	}
	cardplace.setBuffer(buffer);
	

	if (!click.openFromFile("Bonus\\Click.wav")) {
		std::cerr << "Failed to load audio file." << std::endl;
		return;
	}
	if (!error.openFromFile("Bonus\\Error.wav")) {
		std::cerr << "Failed to load audio file." << std::endl;
		return;
	}
	if (!music.openFromFile("Bonus\\Music.wav")) {
		return ;
	}
	music.setLoop(true);
	



	sp.setTexture(t);
	sp.setScale(1.3, 1.3);
	sp.setPosition(0, 0);

}
void Solitaire::show_cards()
{
	for (int i = 0; i < level && i < _board.get_remainnig().size(); ++i)
	{
		auto C = this->_board.get_remainnig().back();
		this->_board.get_remainnig().pop_back();
		C->change_displayed();
		this->_board.get_B()[0].push_back(C);
	}
}
void Solitaire::push_into_stock()
{
	int si = this->_board.get_B()[0].size();
	for (int i = 0; i < si; ++i)
	{
		this->_board.get_remainnig().push_front(this->_board.get_B()[0].back());
		this->_board.get_B()[0].pop_back();
	}
}
bool Solitaire::Is_valid_source()
{
	if ((Source.y < 0 || Source.y>this->_board.get_B().size()) || (Source.x > this->_board.get_B()[Source.y].size() - 1 || Source.x < 0))
	{
		return false;
	}
	click.play();
	return true;
}
bool Solitaire::Is_vlid_des()
{
	if ((destination.y < 1 || destination.y >= this->_board.get_B().size()) || (destination.x < 0 || destination.x> this->_board.get_B()[destination.y].size()))
	{
		return false;
	}
	return true;
}
bool Solitaire::In_rage()
{
	if (!(Is_valid_source() && Is_vlid_des()))
		return false;
	return true;
}
bool Solitaire::Is_diferent_color(Card* sou, Card* des)
{
	int Des_Color = 0;
	if (des->Get_Suit() == 'h' || des->Get_Suit() == 'd')
		Des_Color = 0;
	else
		Des_Color = 1;

	int Sou_Color = 0;
	if (sou->Get_Suit() == 'h' || sou->Get_Suit() == 'd')
		Sou_Color = 0;
	else
		Sou_Color = 1;

	if (Des_Color == Sou_Color)
		return false;
	return true;
}
bool Solitaire::Is_same_color(Card* sou, Card* des)
{
	return des->Get_Suit() == des->Get_Suit();
}

bool Solitaire::IS_valid_ranks_decr(Card* sou, Card* des)
{
	return (sou->Get_Rank_number() == (des->Get_Rank_number() - 1));
}
bool Solitaire::IS_valid_ranks_incre(Card* sou, Card* des)
{
	return (sou->Get_Rank_number() == (des->Get_Rank_number() + 1));
}
void Solitaire::move()
{
	//Hello i am here
	stack<Card*> temp;
	int siz = this->_board.get_B()[Source.y].size() - 1;
	if (Source.x <= siz)
		for (int i = Source.x; i <= siz; ++i)
		{
			temp.push(this->_board.get_B()[Source.y].back());
			this->_board.get_B()[Source.y].pop_back();
		}
	if (!this->_board.get_B()[Source.y].empty())
		this->_board.get_B()[Source.y].back()->change_displayed();
	int si = temp.size();
	for (int i = 0; i < si; ++i)
		this->_board.get_B()[destination.y].push_back(temp.top()), temp.pop();
	cardplace.play();
	/*_board.get_B()[Source.y][Source.x]->set_is_moving(true);*/

}
bool Solitaire::ValidMove()
{
	if (!In_rage())
		return false;
	Card* Sou{}, * des{};
	if (Source.y == destination.y)
		return false;
	if (Source.x < _board.get_B()[Source.y].size())
	{
		if (!_board.get_B()[Source.y][Source.x]->Get_displayed())
		{
			return false;
		}
	}
	else
		return false;

	if (!_board.get_B()[Source.y].empty() && Source.y > 0)
		Sou = this->_board.get_B()[Source.y][Source.x];
	else if (!_board.get_B()[Source.y].empty() && Source.y == 0)
		Sou = this->_board.get_B()[Source.y].back();
	else
		return false;


	if (!_board.get_B()[destination.y].empty())
		des = this->_board.get_B()[destination.y].back();

	if (this->_board.get_B()[destination.y].empty())
	{
		if ((Sou->Get_Rank() == 'K' && destination.y < 8) || (Sou->Get_Rank() == 'A' && destination.y >= 8))
			return true;
		return false;
	}
	else if ((IS_valid_ranks_decr(Sou, des) && Is_diferent_color(Sou, des) && destination.y < 8) ||
		(IS_valid_ranks_incre(Sou, des) && Is_same_color(Sou, des) && destination.y >= 8))
	{
		return true;
	}
	return false;
}
bool Solitaire::Is_Game_over()
{
	for (int i = 8; i < 12; ++i)
	{
		if (_board.get_B()[i].size() != 13)
			return false;
	}
	return true;
}

bool Solitaire::dispaly_time()
{
	sf::Time elapsed;
	elapsed = countdownTime - clock.getElapsedTime();
	int minutes = elapsed.asSeconds() / 60;
	int seconds = elapsed.asSeconds();
	seconds %= 60;
	int milliseconds = elapsed.asMilliseconds() % 6 + 1;
	if (elapsed <= sf::Time::Zero) {
		minutes = 0;
		seconds = 0;
		milliseconds = 0;
	}
	int dim = 140;
	time = ((minutes < 10) ? "0" : "") + std::to_string(minutes) + ":" + ((seconds < 10) ? "0" : "") + std::to_string(seconds);
	return true;
}
void Solitaire::display_text_by_color(sf::RenderWindow& window, string txt, int row, int col, int size, sf::Color  c)
{
	sf::Text text(txt, font, size);
	text.setFillColor(c);
	text.setPosition(row, col);
	window.draw(text);
}
void Solitaire::getRowColbyLeftClick_sfml(int& rpos, int& cpos, sf::RenderWindow& window)
{
	sf::Vector2i p = sf::Mouse::getPosition(window);
	cpos = p.x;
	rpos = p.y;
}
void Solitaire::get_source_sfml()
{
	get_position(Source, window);
	if (Source.y == 0 && (Source.x >= 2 && Source.x <= 4))
	{
		push_into_stock();
		show_cards();
		cardplace.play();
		//++_moves;
	}
	else if (Source.y == 0 && Source.x >= 4 && Source.x <= 10)
	{
		Source.y = 1;
		Source.x = (_board.get_B())[0].size() + 1;
	}
	Source.x -= 2, Source.y -= 1;
	s = "    Source.x= " + std::to_string(Source.x) + "  Source.y= " + std::to_string(Source.y);

}
void Solitaire::get_des_sfml()
{
	get_position(destination, window);
	destination.x -= 2, destination.y -= 1;
	d = "    dest.x= " + std::to_string(destination.x) + "  dest.y= " + std::to_string(destination.y);
}
void Solitaire::get_position(position& P, sf::RenderWindow& window)
{
	getRowColbyLeftClick_sfml(P.x, P.y, window);
	P.x /= 50;
	P.y /= 140;
}
void Solitaire::draw()
{
	dispaly_time();





	window.draw(sp);
	_board.draw_card(window);
	display_text_by_color(window, s, 1200, 400, 50, sf::Color::Black);
	display_text_by_color(window, d, 1200, 600, 50, sf::Color::Black);
	display_text_by_color(window, time, 400, 10, 50, sf::Color::Black);
	display_text_by_color(window, ("Score : " + std::to_string(_score)), 800, 10, 50, sf::Color::Black);
	display_text_by_color(window, ("Move : " + std::to_string(_moves)), 1200, 10, 50, sf::Color::Black);
	display_text_by_color(window, ("Press 'R' for [ Redo ]:"), 300, 800, 50, sf::Color::Black);
	display_text_by_color(window, ("Press 'U' for [ Redo ]:"), 300, 900, 50, sf::Color::Black);
}
void Solitaire::Lets_Play()
{

	this->countdownTime = sf::seconds(1800.10f);

	_board.Shuffling(window);
	_board.starting_animation(window);


	music.play();
	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == event.Closed)
				window.close();
			if (event.type == event.MouseButtonPressed)
			{
				main_flow();
			}
			int i = 0;

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				if (event.key.code == sf::Keyboard::R)
				{
					Redo();
				}
				if (event.key.code == sf::Keyboard::U)
				{
					Undo();
				}
			}
		}
		
		window.clear();
		draw();
		window.display();


	}
}
void Solitaire::main_flow()
{
	if (!source_slected)
		get_source_sfml();
	if (source_slected && !destination_slected)
		get_des_sfml();

	if (Is_valid_source() && !source_slected)
	{
		source_slected = true;
	}
	else if (Is_vlid_des() && !destination_slected)
	{
		destination_slected = true;
	}
	else
	{
		source_slected = false;
		destination_slected = false;
		error.play();
	}

	bool V_M = ValidMove();
	if (source_slected && destination_slected && V_M)
	{
		source_slected = false;
		destination_slected = false;
		move();


		vector<position> temp1;
		temp1.push_back(Source);
		temp1.push_back(destination);
		undo.push_back(temp1);


		if (Source.x > 0)
			_score += 5 * 1;
		++_moves;
	}
}

void Solitaire::Undo()
{
	if (!undo.empty())
	{
		vector<position> temp1(undo.back());
		undo.pop_back();

		Source = temp1.back();
		if(Source.y<8)
			++Source.x;
		temp1.pop_back();
		destination = temp1.back();
		temp1.pop_back();
		move();
		vector<position> temp;
		if (Source.y < 8)
		--Source.x;
		temp.push_back(Source);
		temp.push_back(destination);
		redo.push_back(temp);
		--_moves;
	}
}
void Solitaire::Redo()
{
	if (!redo.empty())
	{
		vector<position> temp1(redo.back());
		redo.pop_back();

		Source = temp1.back();
		/*if (Source.y == 0)
			Source.x = _board.get_B()[0].size()-1, _board.get_B()[0].pop_back();*/
		temp1.pop_back();
		destination = temp1.back();
		temp1.pop_back();
		move();
		vector<position> temp;
		temp.push_back(Source);
		temp.push_back(destination);
		undo.push_back(temp);
		++_moves;
	}
}


Solitaire::~Solitaire() {}