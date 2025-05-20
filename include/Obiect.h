#ifndef OBIECT_H
#define OBIECT_H

#include "SFML/Graphics.hpp"
#include <functional>

class Obiect
{
protected:
	sf::Vector2f pozitie;
	sf::Vector2f marime;
	bool clickable;
	std::shared_ptr<sf::Clock> clock;

	unsigned int marime_font;
	sf::RectangleShape forma;
	sf::Text text;
	sf::Color culoare;

public:
	Obiect(const sf::Vector2f&, const sf::Vector2f&, const unsigned int, const std::string&, const sf::Font&, const sf::Color&);
	virtual ~Obiect() = default;

	//virtual Obiect* clone() const = 0; //constructor "virtual" de copiere

	virtual void update() = 0;
	void render(sf::RenderWindow&) const;
	virtual void align();
	void changeColor(const sf::Color);
	sf::Color getColor() const;
	std::pair<sf::Vector2f, sf::Vector2f> getBounds() const;
	bool isClickable() const;
	void setClickable(const bool);

	std::string getText() const;
	void setText(const std::string);
	void setPosition(const sf::Vector2f&);
};

#endif
