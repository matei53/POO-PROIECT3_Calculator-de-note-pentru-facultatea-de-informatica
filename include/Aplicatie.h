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
	std::shared_ptr<TextInput> active_input = nullptr;
	sf::RenderWindow window;
	sf::Vector2i mouse_position;
	std::shared_ptr<Obiect> clicked = nullptr;

	void updateEvents();
	void updateMousePosition();

	Aplicatie();

public:
	Aplicatie(const Aplicatie&) = delete;
	Aplicatie& operator=(const Aplicatie&) = delete;

	static Aplicatie& getAplicatie();

	void setClick(std::shared_ptr<Obiect>);
	std::shared_ptr<Obiect> getClick();

	void update();
	void render();

	const bool isRunning() const;

	void addObject(std::shared_ptr<Obiect>);

	void removeObject(std::shared_ptr<Obiect>);
	void removeClickableObject(std::shared_ptr<Obiect>);

	std::shared_ptr<TextInput> getActiveInput();
	void setActiveInput(std::shared_ptr<TextInput>);
};

#endif