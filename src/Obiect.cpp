#include "Obiect.h"

Obiect::Obiect(const sf::Vector2f& poz, const sf::Vector2f& mar, const unsigned int mar_font, const std::string& text_, const sf::Font& font,
	const sf::Color& culoare_) : pozitie{ poz }, marime{ mar }, clock{ nullptr }, marime_font{ mar_font }, culoare{ culoare_ },
	text{ font, text_, mar_font }
{
	forma.setPosition(pozitie);
	forma.setSize(marime);
	forma.setFillColor(culoare);
	text.setFillColor(sf::Color::Black);
	clickable = 0;
}

void Obiect::render(sf::RenderWindow& window_) const
{
	window_.draw(forma);
	window_.draw(text);
}

void Obiect::align()
{
	text.setOrigin(text.getLocalBounds().size / 2.0f + text.getLocalBounds().position);
	text.setPosition(sf::Vector2f(pozitie.x + marime.x / 2.0f, pozitie.y + marime.y / 2.0f));
}

void Obiect::changeColor(const sf::Color c)
{
	forma.setFillColor(c);
	culoare = c;
}

sf::Color Obiect::getColor() const
{
	return culoare;
}

std::pair<sf::Vector2f, sf::Vector2f> Obiect::getBounds() const
{
	return std::pair<sf::Vector2f, sf::Vector2f>(pozitie, sf::Vector2f(pozitie.x + marime.x, pozitie.y + marime.y));
}

bool Obiect::isClickable() const
{
	return clickable;
}

void Obiect::setClickable(const bool c)
{
	clickable = c;
}

std::string Obiect::getText() const
{
	return text.getString().toAnsiString();
}

void Obiect::setText(const std::string t)
{
	text.setString(t);
}

void Obiect::setPosition(const sf::Vector2f& poz)
{
	pozitie = poz;
	forma.setPosition(pozitie);
}