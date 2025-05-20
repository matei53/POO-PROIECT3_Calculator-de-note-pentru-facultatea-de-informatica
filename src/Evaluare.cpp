#include "Evaluare.h"

Evaluare::Evaluare(const std::string tip_, const float parte, const float maxim, const float prag_, const float nota_)
{
	tip = tip_;
	parte_din_final = parte;
	punctaj_maxim = maxim;
	prag = prag_;
	nota = nota_;
}

std::string Evaluare::getTip() const
{
	return tip;
}

float Evaluare::getParteFinal() const
{
	return parte_din_final;
}

float Evaluare::getMaxim() const
{
	return punctaj_maxim;
}

float Evaluare::getNota() const
{
	return nota;
}

float Evaluare::getPrag() const
{
	return prag;
}

void Evaluare::setNota(const float input)
{
	nota = input;
}
