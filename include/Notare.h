#ifndef NOTARE_H
#define NOTARE_H

#include "Evaluare.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Notare
{
    std::vector<std::shared_ptr<Evaluare>> evaluari;
    int nota_finala;

public:
    Notare(std::vector<std::shared_ptr<Evaluare>>, const float);

    std::vector<std::shared_ptr<Evaluare>> getEvals() const;
    int getNotaFinala() const;
    void calculNotaFinala();
};

#endif