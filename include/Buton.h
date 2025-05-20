#ifndef BUTON_H
#define BUTON_H

#include "Obiect.h"

class Buton : public Obiect
{
	sf::Color culoare_apasat;

public:
	Buton(const sf::Vector2f&, const sf::Vector2f&, const unsigned int, const std::string&, const sf::Font&, const sf::Color&, const sf::Color&);

	//std::shared_ptr<Obiect> clone() const override;

	void update() override;
	std::string getText() const;
	void animateClick();
	void changeAnimationColor(const sf::Color);
};

#endif