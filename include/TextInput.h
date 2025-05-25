#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include "Obiect.h"

class State;

class TextInput : public Obiect
{
	std::shared_ptr<State> activ;
	int limita_caractere;

public:
	TextInput(const sf::Vector2f&, const sf::Vector2f&, const unsigned int, const std::string&, const sf::Font&, const sf::Color&, const int);

	//std::shared_ptr<Obiect> clone() const override;

	void update() override;
	void pushCharacter(const char character);
	void popCharacter();

	void animateInput();
	void stopAnimation();

	void setState(std::shared_ptr<State>);
	void on();
	void off();
};

class State
{
public:
	virtual void active(TextInput*);
	virtual void inactive(TextInput*);
};

class ActiveState : public State
{
public:
	void inactive(TextInput*);
};

class InactiveState : public State
{
public:
	void active(TextInput*);
};

#endif