#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include "Obiect.h"

class TextInput : public Obiect
{
	int limita_caractere;

public:
	TextInput(const sf::Vector2f&, const sf::Vector2f&, const unsigned int, const std::string&, const sf::Font&, const sf::Color&, const int);

	//std::shared_ptr<Obiect> clone() const override;

	void update() override;
	void pushCharacter(const char character);
	void popCharacter();

	void animateInput();
	void stopAnimation();
};

#endif