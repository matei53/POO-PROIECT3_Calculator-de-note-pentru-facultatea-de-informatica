#include "Buton.h"

Buton::Buton(const sf::Vector2f& poz, const sf::Vector2f& mar, const unsigned int mar_font, const std::string& text_, const sf::Font& font,
	const sf::Color& culoare_, const sf::Color& culoare_apasat_) : Obiect{ poz, mar, mar_font, text_, font, culoare_},
	culoare_apasat{ culoare_apasat_ } { }

//std::shared_ptr<Obiect> Buton::clone() const
//{
//	return std::make_shared<Buton>(*this);
//}

void Buton::update()
{
	if (!clock) return;

	if (clock->getElapsedTime() < sf::seconds(5))
	{
		forma.setFillColor(culoare_apasat);
	}
	else
	{
		forma.setFillColor(culoare);
	}
}

std::string Buton::getText() const
{
	return text.getString().toAnsiString();
}

void Buton::animateClick()
{
	if (!clock) clock = std::make_unique<sf::Clock>();
	clock->restart();
}

void Buton::changeAnimationColor(const sf::Color clr)
{
	culoare_apasat = clr;
}