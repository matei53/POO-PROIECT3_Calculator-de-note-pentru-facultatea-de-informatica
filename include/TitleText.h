#ifndef TITLETEXT_H
#define TITLETEXT_H

#include "Obiect.h"

class TitleText : public Obiect
{
	sf::Color culoare1;
	sf::Color culoare2;
	sf::Color culoare3;
public:
	TitleText(const sf::Vector2f&, const sf::Vector2f&, const unsigned int, const std::string&, const sf::Font&, const sf::Color&, const sf::Color&,
		const sf::Color&, const sf::Color&);
	TitleText(const sf::Vector2f&, const sf::Vector2f&, const unsigned int, const std::string&, const sf::Font&, const sf::Color&);

	//std::shared_ptr<Obiect> clone() const override;

	void update() override;
	void align() override;
	void animateColors();
};

#endif