#ifndef BUTON_H
#define BUTON_H

#include "Obiect.h"

class SeriesSelectionClick
{
	float durata;
	
public:
	SeriesSelectionClick(const float dur) : durata{ dur } { }
	void animate(std::shared_ptr<sf::Clock>& clock, sf::RectangleShape& forma, sf::Color& culoare, sf::Color& culoare_apasat) const
	{
		if (clock->getElapsedTime() < sf::seconds(durata))
		{
			forma.setFillColor(culoare_apasat);
		}
		else
		{
			forma.setFillColor(culoare);
		}
	}
};
class OptFacSelectionClick
{
	float durata;

public:
	OptFacSelectionClick(const float dur) : durata{ dur } {}
	void animate(std::shared_ptr<sf::Clock>& clock, sf::RectangleShape& forma, sf::Color& culoare, sf::Color& culoare_apasat) const
	{
		if (clock->getElapsedTime() < sf::seconds(durata))
		{
			forma.setFillColor(culoare_apasat);
		}
		else if (clock->getElapsedTime() < sf::seconds(2*durata))
		{
			forma.setFillColor(culoare);
		}
		else
		{
			clock->restart();
		}
	}
};
class GradeSaveClick
{
	float durata;

public:
	GradeSaveClick(const float dur) : durata{ dur } {}
	void animate(std::shared_ptr<sf::Clock>& clock, sf::RectangleShape& forma, sf::Color& culoare, sf::Color& culoare_apasat) const
	{
		if (clock->getElapsedTime() < sf::seconds(durata))
		{
			forma.setFillColor(culoare_apasat);
		}
		else if(clock->getElapsedTime() < sf::seconds(2*durata))
		{
			forma.setFillColor(culoare);
		}
		else if (clock->getElapsedTime() < sf::seconds(3*durata))
		{
			forma.setFillColor(culoare_apasat);
		}
		else
		{
			forma.setFillColor(culoare);
		}
	}
};

template <class animType>
class Buton : public Obiect
{
	sf::Color culoare_apasat;
	animType animation;

public:
	Buton(const sf::Vector2f& poz, const sf::Vector2f& mar, const unsigned int mar_font, const std::string& text_, const sf::Font& font,
		const sf::Color& culoare_, const sf::Color& culoare_apasat_, const float dur) : Obiect{ poz, mar, mar_font, text_, font, culoare_ },
		culoare_apasat{ culoare_apasat_ }, animation{ dur } { }

	//std::shared_ptr<Obiect> Buton::clone() const
	//{
	//	return std::make_shared<Buton>(*this);
	//}

	void update()
	{
		if (!clock) return;
		else
			animation.animate(clock, forma, culoare, culoare_apasat);
	}

	std::string getText() const
	{
		return text.getString().toAnsiString();
	}

	void animateClick()
	{
		if (!clock) clock = std::make_unique<sf::Clock>();
		clock->restart();
	}

	void changeAnimationColor(const sf::Color clr)
	{
		culoare_apasat = clr;
	}
};

#endif