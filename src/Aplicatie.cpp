#include "Aplicatie.h"

Aplicatie::Aplicatie(std::string title, unsigned int width, unsigned int height) : window{ sf::VideoMode({width, height}),
    title, sf::Style::Titlebar | sf::Style::Close }
{
    window.setFramerateLimit(60);
}

std::shared_ptr<Obiect> Aplicatie::clicked = nullptr;
std::shared_ptr<TextInput> Aplicatie::active_input = nullptr;

void Aplicatie::setClick(std::shared_ptr<Obiect> ob)
{
    clicked = ob;
}

std::shared_ptr<Obiect> Aplicatie::getClick()
{
    return clicked;
}

void Aplicatie::update() {
    updateEvents();
    updateMousePosition();

    for (std::shared_ptr<Obiect> object : obiecte)
    {
        object->update();
    }
}

void Aplicatie::render() {
    window.clear(sf::Color::White);
    for (std::shared_ptr<Obiect> object : obiecte)
    {
        object->render(window);
    }
    window.display();
}

void Aplicatie::updateEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
        else if (event->is<sf::Event::KeyPressed>())
        {
            if(event->getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scancode::Escape)
                window.close();
            else if (active_input != nullptr)
            {
                switch (event->getIf<sf::Event::KeyPressed>()->scancode)
                {
                    case sf::Keyboard::Scancode::Num0:
                        active_input->pushCharacter('0');
                        break;
                    case sf::Keyboard::Scancode::Num1:
                        active_input->pushCharacter('1');
                        break;
                    case sf::Keyboard::Scancode::Num2:
                        active_input->pushCharacter('2');
                        break;
                    case sf::Keyboard::Scancode::Num3:
                        active_input->pushCharacter('3');
                        break;
                    case sf::Keyboard::Scancode::Num4:
                        active_input->pushCharacter('4');
                        break;
                    case sf::Keyboard::Scancode::Num5:
                        active_input->pushCharacter('5');
                        break;
                    case sf::Keyboard::Scancode::Num6:
                        active_input->pushCharacter('6');
                        break;
                    case sf::Keyboard::Scancode::Num7:
                        active_input->pushCharacter('7');
                        break;
                    case sf::Keyboard::Scancode::Num8:
                        active_input->pushCharacter('8');
                        break;
                    case sf::Keyboard::Scancode::Num9:
                        active_input->pushCharacter('9');
                        break;
                    case sf::Keyboard::Scancode::Period:
                        active_input->pushCharacter('.');
                        break;
                    case sf::Keyboard::Scancode::Backspace:
                        if (active_input->getText() != "> " && active_input->getText() != "> |")
                            active_input->popCharacter();
                        break;
                }
            }
        }
        else if (event->is<sf::Event::MouseButtonPressed>())
        {
            if (event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
            {
                for (std::shared_ptr<Obiect> object : obiecte_clickable)
                {
                    auto bounds = object->getBounds();
                    auto leftUpper = bounds.first;
                    auto rightBottom = bounds.second;
                    if (mouse_position.x >= leftUpper.x && mouse_position.x <= rightBottom.x && mouse_position.y >= leftUpper.y && mouse_position.y <= rightBottom.y)
                    {
                        Aplicatie::setClick(object);
                        break;
                    }
                }
            }
        }
    }
}

void Aplicatie::updateMousePosition()
{
    mouse_position = sf::Mouse::getPosition(window);
}

const bool Aplicatie::isRunning() const
{
    return window.isOpen();
}

void Aplicatie::addObject(std::shared_ptr<Obiect> object)
{
    obiecte.push_back(object);
    if (object->isClickable())
    {
        obiecte_clickable.push_back(object);
    }
}

void Aplicatie::removeObject(std::shared_ptr<Obiect> ob)
{
    obiecte.erase(std::remove(obiecte.begin(), obiecte.end(), ob), obiecte.end());
    if (isInVector<std::shared_ptr<Obiect>>(obiecte_clickable, ob))
    {
        obiecte_clickable.erase(std::remove(obiecte_clickable.begin(), obiecte_clickable.end(), ob), obiecte_clickable.end());
    }
}

void Aplicatie::removeClickableObject(std::shared_ptr<Obiect> ob)
{
    if (isInVector<std::shared_ptr<Obiect>>(obiecte_clickable, ob))
    {
        obiecte_clickable.erase(std::remove(obiecte_clickable.begin(), obiecte_clickable.end(), ob), obiecte_clickable.end());
    }
}

std::shared_ptr<TextInput> Aplicatie::getActiveInput()
{
    return active_input;
}

void Aplicatie::setActiveInput(std::shared_ptr<TextInput> inp)
{
    active_input = inp;
}