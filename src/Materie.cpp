#include "Materie.h"

Materie::Materie(const std::string nume_, const int credit_, std::vector<std::shared_ptr<Notare>> notari_,
	const int an_, const bool optional_, const bool facultativ_)
{
	nume = nume_;
	credit = credit_;
	Notari = notari_;
	an = an_;
	optional = optional_;
	facultativ = facultativ_;
}

bool Materie::operator==(const Materie& other)
{
	return nume == other.nume;
}

std::string Materie::getNume() const
{
	return nume;
}

int Materie::getCredit() const
{
	return credit;
}

int Materie::getAn() const
{
	return an;
}

bool Materie::isOptional() const
{
	return optional;
}

bool Materie::isFacultativ() const
{
	return facultativ;
}

std::shared_ptr<Notare> Materie::getNotare(const int s) const
{
	int a = s - 3;
	return Notari.at(a);
}
