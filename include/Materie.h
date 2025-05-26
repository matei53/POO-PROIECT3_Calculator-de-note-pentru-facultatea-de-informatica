#ifndef MATERIE_H
#define MATERIE_H

#include "Notare.h"

class Materie
{
    std::string nume;
    int credit;
    std::vector<std::shared_ptr<Notare>> Notari;
    int an;
    bool optional;
    bool facultativ;
    
public:
    Materie(const std::string, const int, std::vector<std::shared_ptr<Notare>>, const int, const bool, const bool);

    bool operator==(const Materie&);

    std::string getNume() const;
    int getCredit() const;
    int getAn() const;
    bool isOptional() const;
    bool isFacultativ() const;
    std::shared_ptr<Notare> getNotare(const int) const;
};

#endif