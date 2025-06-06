#include "TextInput.h"

TextInput::TextInput(const sf::Vector2f& poz, const sf::Vector2f& mar, const unsigned int mar_font, const std::string& text_, const sf::Font& font,
	const sf::Color& culoare_, const int limita) : Obiect{ poz, mar, mar_font, text_, font, culoare_ }, limita_caractere{ limita }
{
	activ = std::make_shared<InactiveState>();
}

//std::shared_ptr<Obiect> TextInput::clone() const
//{
//	return std::make_shared<TextInput>(*this);
//}

void TextInput::update()
{
	if (clock && clock->getElapsedTime() > sf::milliseconds(600))
	{
		clock->restart();
		if (text.getString().getSize() != limita_caractere)
		{
			std::string text_string = text.getString().toAnsiString();
			if (text_string.empty() || text_string.back() != '|')
			{
				text_string.push_back('|');
			}
			else
			{
				text_string.pop_back();
			}
			text.setString(text_string);
		}
	}
};

void TextInput::pushCharacter(const char character_)
{
	stopAnimation();
	std::string text_string = getText();
	text_string.push_back(character_);
	text.setString(text_string);
	if (!text_string.empty() && text.getString().getSize() > limita_caractere)
	{
		text_string.pop_back();
	}
	text.setString(text_string);
	align();
	animateInput();
}

void TextInput::popCharacter()
{
	stopAnimation();
	std::string text_string = getText();
	text_string.pop_back();
	text.setString(text_string);
	align();
	animateInput();
}

void TextInput::animateInput()
{
	if (!clock) clock = std::make_shared<sf::Clock>();
	clock->restart();
}

void TextInput::stopAnimation()
{
	clock = nullptr;
	std::string text_string = getText();
	if (text_string.back() == '|')
	{
		text_string.pop_back();
		text.setString(text_string);
	}
}

void TextInput::setState(std::shared_ptr<State> s)
{
	activ = s;
}
void TextInput::on()
{
	activ->active(this);
}
void TextInput::off()
{
	activ->inactive(this);
}

void State::active(TextInput* inp) { return; }
void State::inactive(TextInput* inp) { return; }
void ActiveState::inactive(TextInput* inp)
{
	inp->stopAnimation();
	inp->setState(std::make_shared<InactiveState>());
}
void InactiveState::active(TextInput* inp)
{
	inp->animateInput();
	inp->setState(std::make_shared<ActiveState>());
}