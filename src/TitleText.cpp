#include "TitleText.h"

TitleText::TitleText(const sf::Vector2f& poz, const sf::Vector2f& mar, const unsigned int mar_font, const std::string& text_, const sf::Font& font,
	const sf::Color& culoare_, const sf::Color& culoare1_, const sf::Color& culoare2_, const sf::Color& culoare3_) :
	Obiect{ poz, mar, mar_font, text_, font, culoare_ }, culoare1{ culoare1_ }, culoare2{ culoare2_ }, culoare3{ culoare3_ } { }

TitleText::TitleText(const sf::Vector2f& poz, const sf::Vector2f& mar, const unsigned int mar_font, const std::string& text_, const sf::Font& font,
	const sf::Color& culoare_) : Obiect{ poz, mar, mar_font, text_, font, culoare_ } { }

//std::shared_ptr<Obiect> TitleText::clone() const
//{
//	return std::make_shared<TitleText>(*this);
//}

void TitleText::update()
{
	if (clock)
	{
		if (clock->getElapsedTime() < sf::seconds(5))
		{
			forma.setFillColor(culoare1);
		}
		else if (clock->getElapsedTime() < sf::seconds(10))
		{
			forma.setFillColor(culoare2);
		}
		else if (clock->getElapsedTime() < sf::seconds(15))
		{
			forma.setFillColor(culoare3);
		}
		else if (clock->getElapsedTime() < sf::seconds(20))
		{
			forma.setFillColor(culoare);
		}
		else
		{
			clock->restart();
			forma.setFillColor(culoare);
		}
	}
}

void TitleText::align()
{
	text.setOrigin(sf::Vector2f (0, text.getLocalBounds().size.y / 2.0f) + text.getLocalBounds().position);
	text.setPosition(sf::Vector2f(pozitie.x + marime.x / 20.0f, pozitie.y + marime.y / 2.0f));
}

void TitleText::animateColors()
{
	if (!clock) clock = std::make_unique<sf::Clock>();
	clock->restart();
}