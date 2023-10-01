#include"Board.h"



Board::Board() :B(12), remaining(0)
{
	Deck Dec;
	Dec.allocate_board(B, remaining);

	c = new Card * [5];
	for (int i = 0; i < 5; ++i)
	{
		c[i] = new Card('8', 'd', false, i + 8, 0);
	}
}
vector<deque<Card*>>& Board::get_B()
{
	return B;
}
deque<Card*>& Board::get_remainnig()
{
	return remaining;
}
void Board::draw_card(sf::RenderWindow& w)
{
	c[0]->draw_back(w, -1, 0);
	for (int i = 0; i < B[0].size(); ++i)
	{
		B[0][i]->draw_Card(w, -1, i + 5);
	}
	for (int i = 1; i < B.size(); ++i)
	{
		if (i < 8)
		{
			for (int k = 0; k < B[i].size(); ++k)
			{
				(*B[i][k]).draw_Card(w, i, k);
			}
		}
		else
		{
			if (!B[i].empty())
				B[i][B[i].size() - 1]->draw_Card(w, i, 0);
			else
				c[i - 8]->draw_Card(w, i, 0);
		}
	}
}
void Board::starting_animation(sf::RenderWindow& window)
{
    sf::Texture t;
    sf::Sprite ap;

    sf::SoundBuffer buffer;
    sf::Sound cardplace;
    if (!buffer.loadFromFile("Bonus\\Click.wav")) {
        std::cerr << "Failed to load audio file." << std::endl;
        return;
    }
    cardplace.setBuffer(buffer);

    if (!t.loadFromFile("Cards\\background.jpg"))
    {
        throw("Unable to load img");
    }

    sp.setTexture(t);
    sp.setScale(1.3, 1.3);
    sp.setPosition(0, 0);

    std::vector<Card*> cards;
    float animationSpeed = .05f;

    for (size_t i = 1; i < 8; ++i)
    {
        for (size_t j = 0; j < i; ++j)
        {
            cards.push_back(B[i][j]);
            
        }
    }
    cardplace.setLoop(true);
    cardplace.play();

    bool allFinished = false;
    while (!allFinished)
    {
        allFinished = true;

        for (size_t i = 0; i < cards.size();++i) {
            if (cards[i]->get_is_moving()) {
                sf::Vector2f source = cards[i]->get_vector();
                sf::Vector2f destination = cards[i]->get_destination();
                destination.x += 1;
                destination.y += 1;
                sf::Vector2f direction = destination - source;
                float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

                if (distance <= animationSpeed) {
                    cards[i]->Set_vector(cards[i]->get_destination());
                    cards[i]->set_is_moving(false) ;
                }
                else {
                    direction /= distance;
                    cards[i]->Set_vector(cards[i]->get_vector()+direction*animationSpeed);
                    allFinished = false;
                }
            }
        }
        if (allFinished) {
            allFinished = true;
        }
        window.clear();
        window.draw(sp);
        for (size_t i = 0; i < cards.size(); ++i) {
            cards[i]->draw_Card(window);
        }
        window.display();
    }

    return;
}
void Board::Shuffling(sf::RenderWindow& window)
{
    sf::Texture t;
    sf::Sprite ap;

    sf::SoundBuffer buffer;
    sf::Sound cardplace;
    if (!buffer.loadFromFile("Bonus\\Click.wav")) {
        std::cerr << "Failed to load audio file." << std::endl;
        return;
    }
    cardplace.setBuffer(buffer);

    if (!t.loadFromFile("Cards\\background.jpg"))
    {
        throw("Unable to load img");
    }

    sp.setTexture(t);
    sp.setScale(1.3, 1.3);
    sp.setPosition(0, 0);

    std::vector<Card*> cards;
    Board B;

    for (int i = 0; i < B.remaining.size(); ++i)
    {
        cards.push_back(B.remaining[i]);
    }

    for (size_t i = 1; i < 8; ++i)
    {
        for (size_t j = 0; j < i; ++j)
        {
            cards.push_back(B.B[i][j]);

        }
    }
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    cardplace.setLoop(true);
    cardplace.play();


    sf::Clock clock;
    sf::Time loopDuration = sf::seconds(10.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == event.MouseButtonPressed)
            {
                for (int i = 0; i < cards.size(); ++i)
                {
                    cards[i]->Set_destination({ -1,-1 });
                    cards[i]->set_is_moving(false);
                }
            }
        }
        bool allFinished = true;

        for (Card*& card : cards) {
            card->update();
            if (card->get_is_moving()) {
                allFinished = false;
            }
        }

        if (allFinished) {
            // Shuffle the cards to random positions
            for (Card*& card : cards) {
                int randomX = std::rand() % 10 ;
                int randomY = std::rand() % 10 ;
                card->shuffleTo(sf::Vector2f(static_cast<float>(randomX), static_cast<float>(randomY)));
            }
        }

        window.clear();
        window.draw(sp);
        for (Card*& card : cards) {
            card->Set_vector(card->get_vector());
            card->draw_Card(window);
        }

        window.display();


        sf::Time elapsedTime = clock.getElapsedTime();

        if (elapsedTime >= loopDuration) {
            
            break;
        }
    }

    return ;
}