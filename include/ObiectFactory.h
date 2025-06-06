#ifndef OBIECTFACTORY_H
#define OBIECTFACTORY_H

#include "Buton.h"
#include "TitleText.h"
#include "TextInput.h"

class ObiectFactory
{
public:
	static std::shared_ptr<Buton<SeriesSelectionClick>> buton_serie(const sf::Vector2f& poz, const std::string& text_, const sf::Font& font)
	{
		return std::make_shared<Buton<SeriesSelectionClick>>(Buton<SeriesSelectionClick>(poz, { 85, 85 }, 50, text_, font, sf::Color(213, 255, 204), sf::Color(249, 255, 204), 5));
	}
	static std::shared_ptr<Buton<OptFacSelectionClick>> buton_optfac12(const sf::Vector2f& poz, const std::string& text_, const sf::Font& font)
	{
		return std::make_shared<Buton<OptFacSelectionClick>>(Buton<OptFacSelectionClick>(poz, { 500, 70 }, 30, text_, font, sf::Color(213, 255, 204), sf::Color(204, 255, 248), 0.75));
	}
	static std::shared_ptr<Buton<OptFacSelectionClick>> buton_opt3(const sf::Vector2f& poz, const std::string& text_, const sf::Font& font)
	{
		return std::make_shared<Buton<OptFacSelectionClick>>(Buton<OptFacSelectionClick>(poz, { 400, 40 }, 20, text_, font, sf::Color(213, 255, 204), sf::Color(204, 255, 248), 0.75));
	}
	static std::shared_ptr<Buton<GradeSaveClick>> buton_salvare(const sf::Vector2f& poz, const std::string& text_, const sf::Font& font)
	{
		return std::make_shared<Buton<GradeSaveClick>>(Buton<GradeSaveClick>(poz, { 35, 35 }, 15, text_, font, sf::Color(249, 255, 204), sf::Color(213, 255, 204), 0.1));
	}
	static std::shared_ptr<Buton<GradeSaveClick>> nota_finala(const sf::Vector2f& poz, const std::string& text_, const sf::Font& font)
	{
		return std::make_shared<Buton<GradeSaveClick>>(Buton<GradeSaveClick>(poz, { 40, 35 }, 15, text_, font, sf::Color(228, 204, 255), sf::Color(228, 204, 255), 0));
	}
	static std::shared_ptr<TitleText> titlu_materie(const sf::Vector2f& poz, const std::string& text_, const sf::Font& font)
	{
		return std::make_shared<TitleText>(TitleText(poz, { 235, 35 }, 12, text_, font, sf::Color(213, 255, 204)));
	}
	static std::shared_ptr<TitleText> titlu_evaluare(const sf::Vector2f& poz, const std::string& text_, const sf::Font& font)
	{
		return std::make_shared<TitleText>(TitleText(poz, { 155, 35 }, 10, text_, font, sf::Color(213, 255, 204)));
	}
	static std::shared_ptr<TitleText> titlu_medie(const sf::Vector2f& poz, const std::string& text_, const sf::Font& font)
	{
		return std::make_shared<TitleText>(TitleText(poz, { 195, 35 }, 20, text_, font, sf::Color(228, 204, 255)));
	}
	static std::shared_ptr<TitleText> afisare_medie(const sf::Vector2f& poz, const std::string& text_, const sf::Font& font)
	{
		return std::make_shared<TitleText>(TitleText(poz, { 195, 35 }, 20, text_, font, sf::Color(249, 255, 204)));
	}
	static std::shared_ptr<TextInput> input_note(const sf::Vector2f& poz, const std::string& text_, const sf::Font& font)
	{
		return std::make_shared<TextInput>(TextInput(poz, { 75, 35 }, 15, text_, font, sf::Color(213, 255, 204), 7));
	}
};

#endif