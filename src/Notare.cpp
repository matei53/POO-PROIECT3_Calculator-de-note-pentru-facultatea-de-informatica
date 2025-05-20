#include "Notare.h"

Notare::Notare(std::vector<std::shared_ptr<Evaluare>> evals, const float finala)
{
	for (std::shared_ptr<Evaluare> e : evals)
	{
		evaluari.push_back(e);
	}
	nota_finala = finala;
}

std::vector<std::shared_ptr<Evaluare>> Notare::getEvals() const
{
	return evaluari;
}

int Notare::getNotaFinala() const
{
	return nota_finala;
}

void Notare::calculNotaFinala()
{
	float nota_finala_ = 0;
	for (std::shared_ptr<Evaluare> e : evaluari)
	{
		nota_finala_ += e->getParteFinal() * (e->getNota() / e->getMaxim());
	}
	nota_finala = round(nota_finala_);
	if (nota_finala > 10) nota_finala = 10;
}
