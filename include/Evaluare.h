#ifndef EVALUARE_H
#define EVALUARE_H

#include <iostream>
#include <string>
#include <vector>

class Evaluare
{
    std::string tip;
    float parte_din_final;
    float punctaj_maxim;
    float prag;
    float nota;

public:
    Evaluare(const std::string, const float, const float, const float, const float);

    std::string getTip() const;
    float getParteFinal() const;
    float getMaxim() const;
    float getNota() const;
    float getPrag() const;

    void setNota(const float);
};

#endif