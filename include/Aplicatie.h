#ifndef APLICATIE_H
#define APLICATIE_H

#include "Buton.h"
#include "TitleText.h"
#include "TextInput.h"
#include "FunctiiTemplate.h"

#include <vector>
#include <functional>

class Aplicatie
{
	std::vector<std::shared_ptr<Obiect>> obiecte;
	std::vector<std::shared_ptr<Obiect>> obiecte_clickable;
	static std::shared_ptr<TextInput> active_input;
	sf::RenderWindow window;
	sf::Vector2i mouse_position;
	static std::shared_ptr<Obiect> clicked;

	void updateEvents();
	void updateMousePosition();

public:
	Aplicatie(std::string, unsigned int, unsigned int);
	static void setClick(std::shared_ptr<Obiect>);
	static std::shared_ptr<Obiect> getClick();

	void update();
	void render();

	const bool isRunning() const;

	void addObject(std::shared_ptr<Obiect>);

	void removeObject(std::shared_ptr<Obiect>);
	void removeClickableObject(std::shared_ptr<Obiect>);

	static std::shared_ptr<TextInput> getActiveInput();
	static void setActiveInput(std::shared_ptr<TextInput>);
};

#endif