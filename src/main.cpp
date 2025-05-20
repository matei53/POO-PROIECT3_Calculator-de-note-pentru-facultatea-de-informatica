#include "Aplicatie.h"
#include "Materie.h"
#include "Erori.h"
#include <fstream>

struct NoteMaterie
{
    std::shared_ptr<Obiect> titlu_materie;
    std::shared_ptr<Obiect> nota_finala;
    std::vector<std::shared_ptr<Obiect>> metode_evaluare;
    std::vector<std::shared_ptr<Obiect>> inputuri;
    std::vector<std::shared_ptr<Obiect>> salvari;
};

void checkFiles()
{
    std::ifstream fg("..\\..\\..\\..\\src\\Roboto-Black.ttf");
    if (!fg) throw InvalidFilePathError("Fontul textului nu a putut fi incarcat. Verificati existenta lui in fisierul src.");
    fg.close();
    std::ifstream f("..\\..\\..\\..\\src\\materii.txt");
    if (!f) throw InvalidFilePathError("Fisierul care contine informatiile text nu a putut fi gasit. Verificati existenta lui in fisierul src.");
    f.close();
}

void readSubjectData(std::vector<Materie>& materii)
{
    std::ifstream f("..\\..\\..\\..\\src\\materii.txt");

    std::string line;
    unsigned int line_number = 0;

    while (getline(f, line))
    {
        int credit, an; bool optional, facultativ;
        line_number++; std::string materie = line;

        line_number++; getline(f, line);
        if (line.find("credit: ") == std::string::npos || std::count(line.begin(), line.end(), ' ') != 1)
            throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number);
        try { credit = std::stoi(line.substr(line.find_last_of(" "))); }
        catch (std::invalid_argument& eroare) { throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number); }
        if (credit < 2 || credit > 6) throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number);

        line_number++; getline(f, line);
        if (line.find("an: ") == std::string::npos || std::count(line.begin(), line.end(), ' ') != 1)
            throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number);
        try { an = std::stoi(line.substr(line.find_last_of(" "))); }
        catch (std::invalid_argument& eroare) { throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number); }
        if (an < 1 || an > 3) throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number);

        line_number++; getline(f, line);
        if (line.find("optional: ") == std::string::npos || std::count(line.begin(), line.end(), ' ') != 1)
            throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number);
        try { optional = std::stoi(line.substr(line.find_last_of(" "))); }
        catch (std::invalid_argument& eroare) { throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number); }

        line_number++; getline(f, line);
        if (line.find("facultativ: ") == std::string::npos || std::count(line.begin(), line.end(), ' ') != 1)
            throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number);
        try { facultativ = std::stoi(line.substr(line.find_last_of(" "))); }
        catch (std::invalid_argument& eroare) { throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number); }

        std::vector<std::shared_ptr<Notare>> notari;

        line_number++; getline(f, line);
        for (int i = 1; i <= 3; i++)
        {
            float nota_finala;
            if (line.find("nota_finala_seria3: ") == std::string::npos && line.find("nota_finala_seria4: ") == std::string::npos && line.find("nota_finala_seria5: ") == std::string::npos || std::count(line.begin(), line.end(), ' ') != 1)
                throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number);
            try { nota_finala = std::stof(line.substr(line.find_last_of(" "))); }
            catch (std::invalid_argument& eroare) { throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number); }

            std::vector<std::shared_ptr<Evaluare>> evaluari;
            while (getline(f, line) && line.find("nota_finala") == std::string::npos && line != "-")
            {
                float parte_din_final, punctaj_maxim, nota, prag;
                line_number++;
                std::string tip = line;

                line_number++; getline(f, line);
                if (line.find("parte: ") == std::string::npos || std::count(line.begin(), line.end(), ' ') != 1)
                    throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number);
                try { parte_din_final = std::stof(line.substr(line.find_last_of(" "))); }
                catch (std::invalid_argument& eroare) { throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number); }
                if (parte_din_final < 0 || parte_din_final > 10) throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number);

                line_number++; getline(f, line);
                if (line.find("max: ") == std::string::npos || std::count(line.begin(), line.end(), ' ') != 1)
                    throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number);
                try { punctaj_maxim = std::stof(line.substr(line.find_last_of(" "))); }
                catch (std::invalid_argument& eroare) { throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number); }
                if (punctaj_maxim < 0) throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number);

                line_number++; getline(f, line);
                if (line.find("prag: ") == std::string::npos || std::count(line.begin(), line.end(), ' ') != 1)
                    throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number);
                try { prag = std::stof(line.substr(line.find_last_of(" "))); }
                catch (std::invalid_argument& eroare) { throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number); }
                if (prag < 0) throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number);

                line_number++; getline(f, line);
                if (line.find("nota: ") == std::string::npos || std::count(line.begin(), line.end(), ' ') != 1)
                    throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number);
                try { nota = std::stof(line.substr(line.find_last_of(" "))); }
                catch (std::invalid_argument& eroare) { throw InvalidFileContentError("Fisierul cu informatiile despre materii este incomplet. Daca ati facut modificari manuale in continut, anulati-le. Daca nu, creati un issue pe proiectul GitHub.", line_number); }

                evaluari.push_back(std::make_shared<Evaluare>(Evaluare(tip, parte_din_final, punctaj_maxim, prag, nota)));
            }
            notari.push_back(std::make_shared<Notare>(Notare(evaluari, nota_finala)));
        }
        materii.push_back(Materie(materie, credit, notari, an, optional, facultativ));
    }
    f.close();
}

void createTitle(std::shared_ptr<Obiect>& titlu, sf::Font& font, Aplicatie& app)
{
    titlu = std::make_shared<TitleText>(TitleText({ 0, 0 }, { 1900, 135 }, 80, "Welcome", font, sf::Color::Yellow, sf::Color::Red, sf::Color::Green, sf::Color::Blue));
    std::dynamic_pointer_cast<TitleText>(titlu)->animateColors();
    titlu->align();
    app.addObject(titlu);
}

void createSeriesChoiceBox(std::shared_ptr<Obiect>& alegere_serie, sf::Font& font, Aplicatie& app)
{
    alegere_serie = std::make_shared<TitleText>(TitleText({ 0, 155 }, { 380, 85 }, 50, "Alegeti seria", font, sf::Color::Yellow));
    alegere_serie->align();
    app.addObject(alegere_serie);
}

void createSeriesButtons(std::vector<std::shared_ptr<Obiect>>& butoane_serii, sf::Font& font, Aplicatie& app)
{
    butoane_serii.push_back(std::make_shared<Buton>(Buton({ 400, 155 }, { 85, 85 }, 50, "13", font, sf::Color::Green, sf::Color::Yellow)));
    butoane_serii.push_back(std::make_shared<Buton>(Buton({ 500, 155 }, { 85, 85 }, 50, "14", font, sf::Color::Green, sf::Color::Yellow)));
    butoane_serii.push_back(std::make_shared<Buton>(Buton({ 600, 155 }, { 85, 85 }, 50, "15", font, sf::Color::Green, sf::Color::Yellow)));
    butoane_serii.push_back(std::make_shared<Buton>(Buton({ 700, 155 }, { 85, 85 }, 50, "23", font, sf::Color::Green, sf::Color::Yellow)));
    butoane_serii.push_back(std::make_shared<Buton>(Buton({ 800, 155 }, { 85, 85 }, 50, "24", font, sf::Color::Green, sf::Color::Yellow)));
    butoane_serii.push_back(std::make_shared<Buton>(Buton({ 900, 155 }, { 85, 85 }, 50, "25", font, sf::Color::Green, sf::Color::Yellow)));
    butoane_serii.push_back(std::make_shared<Buton>(Buton({ 1000, 155 }, { 85, 85 }, 50, "33", font, sf::Color::Green, sf::Color::Yellow)));
    butoane_serii.push_back(std::make_shared<Buton>(Buton({ 1100, 155 }, { 85, 85 }, 50, "34", font, sf::Color::Green, sf::Color::Yellow)));
    butoane_serii.push_back(std::make_shared<Buton>(Buton({ 1200, 155 }, { 85, 85 }, 50, "35", font, sf::Color::Green, sf::Color::Yellow)));

    for (std::shared_ptr<Obiect> b : butoane_serii)
    {
        b->align();
        b->setClickable(1);
        app.addObject(b);
    }
}

void createForwardButton(std::shared_ptr<Obiect>& buton_inainte, sf::Font& font, Aplicatie& app)
{
    buton_inainte = std::make_shared<Buton>(Buton({ 1300, 155 }, { 185, 85 }, 50, "Inainte", font, sf::Color::Magenta, sf::Color::Red));
    buton_inainte->setClickable(1);
    buton_inainte->align();
    app.addObject(buton_inainte);
}

void deactivateSeriesButtons(std::vector<std::shared_ptr<Obiect>>& butoane_serii, std::shared_ptr<Obiect>& clicked_button, Aplicatie& app)
{
    for (std::shared_ptr<Obiect> b : butoane_serii)
    {
        b->setClickable(0);
        app.removeClickableObject(b);
    }
    auto b = std::dynamic_pointer_cast<Buton>(clicked_button);
    b->animateClick();
}

void createYearOneOptions(std::shared_ptr<Obiect>& titlu_facultative, std::vector<Materie>& materii, std::vector<std::shared_ptr<Obiect>>& butoane_facultative,
    sf::Font& font, Aplicatie& app, const int an)
{
    titlu_facultative = std::make_shared<TitleText>(TitleText({ 0, 250 }, { 1000, 75 }, 40, "Alegeti facultativele la care doriti sa participati", font, sf::Color::Yellow));
    app.addObject(titlu_facultative);
    titlu_facultative->align();

    float y_fac = 330;
    for (Materie m : materii)
    {
        if (m.getAn() == an && m.isFacultativ())
        {
            butoane_facultative.push_back(std::make_shared<Buton>(Buton({ 0, y_fac }, { 500, 70 }, 30, m.getNume(), font, sf::Color::Green, sf::Color::Yellow)));
            y_fac += 75;
        }
    }
    for (std::shared_ptr<Obiect> b : butoane_facultative)
    {
        b->align();
        b->setClickable(1);
        app.addObject(b);
    }
}

void createYearTwoOptions(std::shared_ptr<Obiect>& titlu_facultative, std::shared_ptr<Obiect>& titlu_optionale, std::vector<Materie>& materii,
    std::vector<std::shared_ptr<Obiect>>& butoane_facultative, std::vector<std::shared_ptr<Obiect>>& butoane_optionale, sf::Font& font, Aplicatie& app, const int an)
{
    titlu_facultative = std::make_shared<TitleText>(TitleText({ 0, 250 }, { 1000, 75 }, 40, "Alegeti facultativele la care doriti sa participati", font, sf::Color::Yellow));
    app.addObject(titlu_facultative);
    titlu_facultative->align();

    float y = 330;
    for (Materie m : materii)
    {
        if (m.getAn() == an && m.isFacultativ())
        {
            butoane_facultative.push_back(std::make_shared<Buton>(Buton({ 0, y }, { 500, 70 }, 30, m.getNume(), font, sf::Color::Green, sf::Color::Yellow)));
            y += 75;
        }
    }
    for (std::shared_ptr<Obiect> b : butoane_facultative)
    {
        b->align();
        b->setClickable(1);
        app.addObject(b);
    }

    titlu_optionale = std::make_shared<TitleText>(TitleText({ 0, y }, { 1000, 75 }, 40, "Alegeti optionalul la care veti participa", font, sf::Color::Yellow));
    app.addObject(titlu_optionale);
    titlu_optionale->align();
    y += 80;

    for (Materie m : materii)
    {
        if (m.getAn() == an && m.isOptional())
        {
            butoane_optionale.push_back(std::make_shared<Buton>(Buton({ 0, y }, { 500, 70 }, 30, m.getNume(), font, sf::Color::Green, sf::Color::Yellow)));
            y += 75;
        }
    }
    for (std::shared_ptr<Obiect> b : butoane_optionale)
    {
        b->align();
        b->setClickable(1);
        app.addObject(b);
    }
}

void createYearThreeOptions(std::shared_ptr<Obiect>& titlu_optionale, std::vector<Materie>& materii, std::vector<std::shared_ptr<Obiect>>& butoane_optionale,
    sf::Font& font, Aplicatie& app, const int an)
{
    titlu_optionale = std::make_shared<TitleText>(TitleText({ 0, 250 }, { 1700, 75 }, 30, "Alegeti optionalele la care veti participa.\nTrebuie sa alegeti 3 pentru semestrul 1 (primele doua coloane) si 3 pentru semestrul 2 (ultimele doua coloane).", font, sf::Color::Yellow));
    app.addObject(titlu_optionale);
    titlu_optionale->align();

    float x_opt = 0, y_opt = 330;
    for (Materie m : materii)
    {
        if (m.getAn() == an && m.isOptional())
        {
            butoane_optionale.push_back(std::make_shared<Buton>(Buton({ x_opt, y_opt }, { 400, 40 }, 20, m.getNume(), font, sf::Color::Green, sf::Color::Yellow)));
            y_opt += 45;
            if (y_opt > 950 || butoane_optionale.size() == 23)
            {
                x_opt += 425;
                y_opt = 330;
            }
        }
    }
    for (std::shared_ptr<Obiect> b : butoane_optionale)
    {
        b->align();
        b->setClickable(1);
        app.addObject(b);
    }
}

void manageYearTwoOptionals(std::vector<Materie>& materii, std::vector<std::shared_ptr<Obiect>>& butoane_optionale, std::vector<Materie>& optionale_selectate, Aplicatie& app)
{
    for (std::shared_ptr<Obiect> b : butoane_optionale)
    {
        b->setClickable(0);
        app.removeClickableObject(b);
    }
    auto b = std::dynamic_pointer_cast<Buton>(Aplicatie::getClick());
    b->changeColor(sf::Color::Cyan);
    for (Materie m : materii)
    {
        if (m.getNume() == b->getText())
        {
            optionale_selectate.push_back(m);
            break;
        }
    }
}

void manageYearThreeOptionals(std::vector<Materie>& materii, std::vector<std::shared_ptr<Obiect>>& butoane_optionale, std::vector<Materie>& optionale_selectate, Aplicatie& app)
{
    auto b = std::dynamic_pointer_cast<Buton>(Aplicatie::getClick());
    b->changeColor(sf::Color::Cyan);
    b->setClickable(0);
    app.removeClickableObject(b);

    int n = 0;
    while (b != butoane_optionale.at(n)) n++;
    if (n < 23)
    {
        int nr = 0;
        for (int i = 0; i < 23; i++)
            if (!butoane_optionale.at(i)->isClickable())
                nr++;
        if (nr == 3)
        {
            for (int i = 0; i < 23; i++)
            {
                butoane_optionale.at(i)->setClickable(0);
                app.removeClickableObject(butoane_optionale.at(i));
            }
        }
    }
    else
    {
        int nr = 0;
        for (int i = 23; i < 41; i++)
            if (!butoane_optionale.at(i)->isClickable())
                nr++;
        if (nr == 3)
        {
            for (int i = 23; i < 41; i++)
            {
                butoane_optionale.at(i)->setClickable(0);
                app.removeClickableObject(butoane_optionale.at(i));
            }
        }
    }
    for (Materie m : materii)
    {
        if (m.getNume() == b->getText())
        {
            optionale_selectate.push_back(m);
            break;
        }
    }
}

void manageFacultatives(std::vector<Materie>& materii, std::vector<std::shared_ptr<Obiect>>& butoane_facultative, std::vector<Materie>& facultative_selectate, Aplicatie& app)
{
    auto b = std::dynamic_pointer_cast<Buton>(Aplicatie::getClick());
    b->changeColor(sf::Color::Cyan);
    b->setClickable(0);
    app.removeClickableObject(b);

    for (Materie m : materii)
    {
        if (m.getNume() == b->getText())
        {
            facultative_selectate.push_back(m);
            break;
        }
    }
}

bool checkOptionalSelection(std::vector<std::shared_ptr<Obiect>>& butoane_optionale)
{
    bool ok = 1;
    for (std::shared_ptr<Obiect> b : butoane_optionale)
        if (b->isClickable())
            return 0;
    return 1;
}

void removeFirstPageObjects(Aplicatie& app, std::shared_ptr<Obiect>& titlu, std::shared_ptr<Obiect>& alegere_serie, std::shared_ptr<Obiect>& buton_inainte,
    std::shared_ptr<Obiect>& titlu_facultative, std::shared_ptr<Obiect>& titlu_optionale, std::vector<std::shared_ptr<Obiect>>& butoane_serii,
    std::vector<std::shared_ptr<Obiect>>& butoane_optionale, std::vector<std::shared_ptr<Obiect>>& butoane_facultative)
{
    app.removeObject(titlu); titlu.reset();
    app.removeObject(alegere_serie); alegere_serie.reset();
    app.removeObject(buton_inainte); buton_inainte.reset();
    app.removeObject(titlu_facultative); titlu_facultative.reset();
    app.removeObject(titlu_optionale); titlu_optionale.reset();
    for (std::shared_ptr<Obiect> b : butoane_serii) { app.removeObject(b); b.reset(); }
    for (std::shared_ptr<Obiect> b : butoane_optionale) { app.removeObject(b); b.reset(); }
    for (std::shared_ptr<Obiect> b : butoane_facultative) { app.removeObject(b); b.reset(); }
}

void addPageTwoSideObjects(std::shared_ptr<Obiect>& titlu_medie_finala_bursa, std::shared_ptr<Obiect>& medie_finala_bursa, std::shared_ptr<Obiect>& titlu_medie_finala_buget,
    std::shared_ptr<Obiect>& medie_finala_buget, std::shared_ptr<Obiect>& titlu_credite, std::shared_ptr<Obiect>& total_credite_display,
    std::shared_ptr<Obiect>& instructiune1, std::shared_ptr<Obiect>& instructiune2, std::shared_ptr<Obiect>& instructiune3, std::shared_ptr<Obiect>& instructiune4,
    sf::Font& font, Aplicatie& app)
{
    titlu_medie_finala_bursa = std::make_shared<TitleText>(TitleText({ 1700, 5 }, { 195, 35 }, 20, "MEDIE BURSA", font, sf::Color::Magenta));
    medie_finala_bursa = std::make_shared<TitleText>(TitleText({ 1700, 40 }, { 195, 35 }, 20, "", font, sf::Color::Yellow));
    titlu_medie_finala_buget = std::make_shared<TitleText>(TitleText({ 1700, 80 }, { 195, 35 }, 20, "PUNCTE CREDIT", font, sf::Color::Magenta));
    medie_finala_buget = std::make_shared<TitleText>(TitleText({ 1700, 115 }, { 195, 35 }, 20, "", font, sf::Color::Yellow));
    titlu_credite = std::make_shared<TitleText>(TitleText({ 1700, 155 }, { 195, 35 }, 20, "CREDITE", font, sf::Color::Magenta));
    total_credite_display = std::make_shared<TitleText>(TitleText({ 1700, 190 }, { 195, 35 }, 20, "", font, sf::Color::Yellow));
    titlu_medie_finala_bursa->align();
    titlu_medie_finala_buget->align();
    titlu_credite->align();
    app.addObject(titlu_medie_finala_bursa);
    app.addObject(titlu_medie_finala_buget);
    app.addObject(titlu_credite);
    app.addObject(medie_finala_bursa);
    app.addObject(medie_finala_buget);
    app.addObject(total_credite_display);

    instructiune1 = std::make_shared<TitleText>(TitleText({ 1700, 230 }, { 195, 100 }, 14, "In calculul creditelor si\na punctelor de credit nu\nse iau in calcul facultativele.\nPunctele credit se folosesc\nin reclasificarea buget/taxa.", font, sf::Color::Yellow));
    instructiune2 = std::make_shared<TitleText>(TitleText({ 1700, 335 }, { 195, 150 }, 14, "Numarul din stanga\nevaluarii reprezinta\nnumarul de puncte din\nnota finala.\nNumarul din dreapta\nreprezinta punctajul\nmaxim ce se poate obtine\nla evaluarea respectiva.", font, sf::Color::Yellow));
    instructiune3 = std::make_shared<TitleText>(TitleText({ 1700, 490 }, { 195, 360 }, 14, "Daca pragul de trecere la\no evaluare a unei materii nu\na fost trecut sau daca\nnota finala a unei\nmaterii este sub 5,\natunci acea materie\neste picata.\nIn acest caz, casuta\ncu numele materiei si\ncea cu media pentru\nbursa vor deveni rosii.\nNotele pot fi inlocuite\ndupa restante/mariri.\nDaca cel putin o materie\neste inca picata dupa\nrestante, atunci bursa nu\nse poate obtine pentru\nanul urmator. Creditele la\nmateriile picate nu se iau\nin calcul la stabilirea\ncreditelor finale si a\npunctelor de credit.", font, sf::Color::Yellow));
    instructiune4 = std::make_shared<TitleText>(TitleText({ 1700, 855 }, { 195, 120 }, 14, "Criteriile de promovare a\nanului universitar se\ngasesc in capitolul 8 din\nregulamentul privind\nactivitatea profesionala\na studentilor.", font, sf::Color::Yellow));
    instructiune1->align();
    instructiune2->align();
    instructiune3->align();
    instructiune4->align();
    app.addObject(instructiune1);
    app.addObject(instructiune2);
    app.addObject(instructiune3);
    app.addObject(instructiune4);

}

void addPageTwoSubjectInputs(std::vector<Materie>& materii, const int an, const int serie, std::vector<Materie>& optionale_selectate, std::vector<Materie>& facultative_selectate,
    std::vector<NoteMaterie>& notare_materii, sf::Font& font, Aplicatie& app, std::shared_ptr<Obiect>& titlu_medie_finala_bursa)
{
    float x = 5, y = 5;
    for (Materie m : materii)
    {
        if (m.getAn() == an)
        {
            if ((m.isOptional() && (std::find(optionale_selectate.begin(), optionale_selectate.end(), m) != optionale_selectate.end()) ||
                (m.isFacultativ() && std::find(facultative_selectate.begin(), facultative_selectate.end(), m) != facultative_selectate.end()) ||
                (!m.isOptional() && !m.isFacultativ())))
            {
                if (notare_materii.size() == 6)
                {
                    x = 5; y = 325;
                }
                else if (notare_materii.size() == 12)
                {
                    x = 5; y = 645;
                }
                float y1 = y;
                NoteMaterie M;
                M.titlu_materie = std::make_shared<TitleText>(TitleText({ x, y1 }, { 235, 35 }, 12, m.getNume(), font, sf::Color::Green));
                if (m.getNotare(serie)->getNotaFinala() != -1 && m.getNotare(serie)->getNotaFinala() < 5)
                {
                    M.titlu_materie->changeColor(sf::Color::Red);
                    titlu_medie_finala_bursa->changeColor(sf::Color::Red);
                }
                M.titlu_materie->align();
                app.addObject(M.titlu_materie);
                if (m.getNotare(serie)->getNotaFinala() == -1)
                    M.nota_finala = std::make_shared<Buton>(Buton({ x + 235, y1 }, { 40, 35 }, 15, "", font, sf::Color::Magenta, sf::Color::Magenta));
                else
                    M.nota_finala = std::make_shared<Buton>(Buton({ x + 235, y1 }, { 40, 35 }, 15, std::to_string(m.getNotare(serie)->getNotaFinala()), font, sf::Color::Magenta, sf::Color::Magenta));
                app.addObject(M.nota_finala);
                M.nota_finala->align();
                for (std::shared_ptr<Evaluare> e : m.getNotare(serie)->getEvals())
                {
                    y1 += 35;
                    auto ev = std::make_shared<TitleText>(TitleText({ x, y1 }, { 155, 35 }, 10, std::to_string(e->getParteFinal()).substr(0, 4) + " - " + e->getTip() + " (" + std::to_string(e->getMaxim()).substr(0, 4) + ")", font, sf::Color::Green));
                    std::shared_ptr<Obiect> inp;
                    if (e->getNota() == -1)
                        inp = std::make_shared<TextInput>(TextInput({ x + 160, y1 }, { 75, 35 }, 15, "> ", font, sf::Color::Green, 7));
                    else
                        inp = std::make_shared<TextInput>(TextInput({ x + 160, y1 }, { 75, 35 }, 15, "> " + std::to_string(e->getNota()).substr(0, 5), font, sf::Color::Green, 7));
                    if (e->getNota() < e->getPrag() && e->getNota() != -1)
                    {
                        M.titlu_materie->changeColor(sf::Color::Red);
                        titlu_medie_finala_bursa->changeColor(sf::Color::Red);
                    }
                    auto save = std::make_shared<Buton>(Buton({ x + 240, y1 }, { 35, 35 }, 15, "OK", font, sf::Color::Yellow, sf::Color::Green));
                    ev->align(); inp->align(); save->align();
                    inp->setClickable(1);
                    save->setClickable(1);
                    M.metode_evaluare.push_back(ev);
                    M.inputuri.push_back(inp);
                    M.salvari.push_back(save);
                    app.addObject(M.metode_evaluare.back());
                    app.addObject(M.inputuri.back());
                    app.addObject(M.salvari.back());
                }
                notare_materii.push_back(M);
                x += 280;
            }
        }
    }
}

void saveGrade(std::vector<Materie>& materii, const int serie, const float grade, const int i, const int j)
{
    //verificare daca a fost modificat fisierul manual in timpul rularii
    std::vector<Materie> mtr;
    readSubjectData(mtr);
    
    std::ifstream f("..\\..\\..\\..\\src\\materii.txt");
    if (!f) throw InvalidFilePathError("Fisierul care contine informatiile text nu a putut fi gasit. Verificati existenta lui in fisierul src.");
    std::string line, lines = "";
    while (getline(f, line))
    {
        lines += line + "\n";
        if (line == materii[j].getNume())
        {
            while (getline(f, line))
            {
                lines += line + "\n";
                if (line == materii[j].getNotare(serie)->getEvals()[i]->getTip())
                {
                    getline(f, line); lines += line + "\n";
                    getline(f, line); lines += line + "\n";
                    getline(f, line); lines += line + "\n";
                    getline(f, line); line = "nota: " + std::to_string(grade).substr(0, 4); lines += line + "\n";
                    break;
                }
            }
        }
    }
    f.close();
    std::ofstream g("..\\..\\..\\..\\src\\materii.txt");
    g << lines;
    g.close();
}

void saveFinalGrade(std::vector<Materie>& materii, const int serie, const int j)
{
    std::ifstream f("..\\..\\..\\..\\src\\materii.txt");
    if (!f) throw InvalidFilePathError("Fisierul care contine informatiile text nu a putut fi gasit. Verificati existenta lui in fisierul src.");
    std::string line, lines = "";
    while (getline(f, line))
    {
        lines += line + "\n";
        if (line == materii[j].getNume())
        {
            while (getline(f, line))
            {
                if (line.find("nota_finala_seria") != std::string::npos)
                {
                    line = "nota_finala_seria" + std::to_string(serie) + ": " + std::to_string(materii[j].getNotare(serie)->getNotaFinala()); lines += line + "\n";
                    break;
                }
                lines += line + "\n";
            }
        }
    }
    f.close();
    std::ofstream g("..\\..\\..\\..\\src\\materii.txt");
    g << lines;
    g.close();
}

void setFinals(std::vector<NoteMaterie>& notare_materii, std::vector<Materie>& materii, std::shared_ptr<Obiect>& medie_finala_bursa, std::shared_ptr<Obiect>& medie_finala_buget,
    std::shared_ptr<Obiect>& total_credite_display)
{
    float nota_bursa = 0;
    int puncte_buget = 0;
    int total_credite = 0, credite_obtinute = 0;
    for (NoteMaterie final : notare_materii)
    {
        if (final.nota_finala->getText() != "")
        {
            int credite = 0; bool trecere = 1, facl = 0;
            for (Materie mt : materii)
            {
                if (final.titlu_materie->getText() == mt.getNume())
                {
                    if (mt.isFacultativ()) facl = 1;
                    credite = mt.getCredit();
                    if (final.titlu_materie->getColor() == sf::Color::Red) trecere = 0;
                    break;
                }
            }
            nota_bursa += std::stof(final.nota_finala->getText());
            if (!facl)
            {
                if (trecere)
                {
                    puncte_buget += std::stof(final.nota_finala->getText()) * credite;
                    credite_obtinute += credite;
                }
                total_credite += credite;
            }
        }
        else
        {
            int credite = 0; bool  facl = 0;
            for (Materie mt : materii)
            {
                if (final.titlu_materie->getText() == mt.getNume())
                {
                    if (mt.isFacultativ()) facl = 1;
                    credite = mt.getCredit();
                    break;
                }
            }
            if (!facl)
                total_credite += credite;
        }

    }
    nota_bursa = nota_bursa / notare_materii.size();
    if (nota_bursa == 10)
        medie_finala_bursa->setText("10.00");
    else
        medie_finala_bursa->setText(std::to_string(nota_bursa).substr(0, 4));

    medie_finala_buget->setText(std::to_string(puncte_buget) + "/" + std::to_string(total_credite * 10));
    total_credite_display->setText(std::to_string(credite_obtinute) + "/" + std::to_string(total_credite));

    medie_finala_bursa->align();
    medie_finala_buget->align();
    total_credite_display->align();
}

void manageInputedGrade(std::vector<NoteMaterie>& notare_materii, Aplicatie& app, std::vector<Materie>& materii, const int serie, std::shared_ptr<Obiect>& titlu_medie_finala_bursa,
    std::shared_ptr<Obiect>& medie_finala_bursa, std::shared_ptr<Obiect>& medie_finala_buget, std::shared_ptr<Obiect>& total_credite_display, NoteMaterie& m, const float grade,
    const int i, const int j)
{
    bool prag_fail = 0, fail = 0, complet = 1;

    if (grade > materii[j].getNotare(serie)->getEvals()[i]->getMaxim())
        throw InvalidInputError(sf::Color::Red);

    materii[j].getNotare(serie)->getEvals()[i]->setNota(grade);
    saveGrade(materii, serie, grade, i, j);

    for (int k = 0; k < m.salvari.size() && fail == 0; k++)
        if (materii[j].getNotare(serie)->getEvals()[k]->getNota() < materii[j].getNotare(serie)->getEvals()[k]->getPrag() && materii[j].getNotare(serie)->getEvals()[k]->getNota() != -1)
            fail = 1;

    if (fail == 0)
    {
        prag_fail = 0;

        if (m.titlu_materie->getColor() == sf::Color::Red)
        {
            m.titlu_materie->changeColor(sf::Color::Green);

            bool brs = 1;
            for (NoteMaterie mbr : notare_materii)
                if (mbr.titlu_materie->getColor() == sf::Color::Red)
                {
                    brs = 0;
                    break;
                }
            if (brs == 1)
                titlu_medie_finala_bursa->changeColor(sf::Color::Magenta);
        }
    }
    else if (fail == 1)
    {
        prag_fail = 1;

        if (m.titlu_materie->getColor() == sf::Color::Green)
        {
            m.titlu_materie->changeColor(sf::Color::Red);
            titlu_medie_finala_bursa->changeColor(sf::Color::Red);
        }
    }

    for (std::shared_ptr<Evaluare> ev : materii[j].getNotare(serie)->getEvals())
        if (ev->getNota() == -1)
            complet = 0;

    if (complet)
    {
        materii[j].getNotare(serie)->calculNotaFinala();
        saveFinalGrade(materii, serie, j);

        if (materii[j].getNotare(serie)->getNotaFinala() < 5 && m.titlu_materie->getColor() == sf::Color::Green)
        {
            m.titlu_materie->changeColor(sf::Color::Red);
            titlu_medie_finala_bursa->changeColor(sf::Color::Red);
        }
        else if (materii[j].getNotare(serie)->getNotaFinala() >= 5 && m.titlu_materie->getColor() == sf::Color::Red && prag_fail == 0)
        {
            m.titlu_materie->changeColor(sf::Color::Green);

            bool brs = 1;
            for (NoteMaterie mbr : notare_materii)
                if (mbr.titlu_materie->getColor() == sf::Color::Red)
                {
                    brs = 0;
                    break;
                }
            if (brs == 1)
                titlu_medie_finala_bursa->changeColor(sf::Color::Magenta);
        }
        m.nota_finala->setText(std::to_string(materii[j].getNotare(serie)->getNotaFinala()));
        m.nota_finala->align();

        setFinals(notare_materii, materii, medie_finala_bursa, medie_finala_buget, total_credite_display);
    }
}

void manageInputClick(Aplicatie& app)
{
    if (Aplicatie::getActiveInput())
        Aplicatie::getActiveInput()->stopAnimation();
    auto inp = std::dynamic_pointer_cast<TextInput>(Aplicatie::getClick());
    inp->animateInput();
    Aplicatie::setActiveInput(inp);
}

void manageSaveClick(std::vector<NoteMaterie>& notare_materii, Aplicatie& app, std::vector<Materie>& materii, const int serie, std::shared_ptr<Obiect>& titlu_medie_finala_bursa,
    std::shared_ptr<Obiect>& medie_finala_bursa, std::shared_ptr<Obiect>& medie_finala_buget, std::shared_ptr<Obiect>& total_credite_display, NoteMaterie& m, const int i)
{
    std::shared_ptr<Buton> sav = std::dynamic_pointer_cast<Buton>(Aplicatie::getClick());
    sav->changeAnimationColor(sf::Color::Green);
    try
    {
        std::string grade_string = m.inputuri.at(i)->getText().substr(2);
        if (grade_string != "" && grade_string.back() == '|') grade_string.pop_back();
        if (std::count(grade_string.begin(), grade_string.end(), '.') > 1 || grade_string == "." || grade_string == "")
            throw InvalidInputError(sf::Color::Red);
        sav->animateClick();

        float grade = std::stof(grade_string);

        for (int j = 0; j < materii.size(); j++)
        {
            if (m.titlu_materie->getText() == materii[j].getNume())
            {
                manageInputedGrade(notare_materii, app, materii, serie, titlu_medie_finala_bursa, medie_finala_bursa, medie_finala_buget, total_credite_display, m, grade, i, j);
                break;
            }
        }
    }
    catch (InvalidInputError& eroare)
    {
        sav->changeAnimationColor(eroare.getColor());
        sav->animateClick();
    }
}

void manageGradeInputs(std::vector<NoteMaterie>& notare_materii, Aplicatie& app, std::vector<Materie>& materii, const int serie, std::shared_ptr<Obiect>& titlu_medie_finala_bursa,
    std::shared_ptr<Obiect>& medie_finala_bursa, std::shared_ptr<Obiect>& medie_finala_buget, std::shared_ptr<Obiect>& total_credite_display)
{
    for (NoteMaterie m : notare_materii)
    {
        if (std::find(m.inputuri.begin(), m.inputuri.end(), Aplicatie::getClick()) != m.inputuri.end())
        {
            manageInputClick(app);
            Aplicatie::setClick(nullptr);
            break;
        }
        else
            for (int i = 0; i < m.salvari.size(); i++)
                if (m.salvari.at(i) == Aplicatie::getClick())
                {
                    manageSaveClick(notare_materii, app, materii, serie, titlu_medie_finala_bursa, medie_finala_bursa, medie_finala_buget, total_credite_display, m, i);
                    Aplicatie::setClick(nullptr);
                    break;
                }
    }
}

int main()
{
    try
    {
        std::vector<Materie> materii;
        checkFiles();
        readSubjectData(materii);

        sf::Font font("..\\..\\..\\..\\src\\Roboto-Black.ttf");

        Aplicatie app("Calculator note", 1900, 980);
        int an = 0, serie = 0;

        std::shared_ptr<Obiect> titlu;
        createTitle(titlu, font, app);

        std::shared_ptr<Obiect> alegere_serie;
        createSeriesChoiceBox(alegere_serie, font, app);

        std::vector<std::shared_ptr<Obiect>> butoane_serii;
        createSeriesButtons(butoane_serii, font, app);

        std::shared_ptr<Obiect> buton_inainte;

        std::shared_ptr<Obiect> titlu_facultative;
        std::vector<std::shared_ptr<Obiect>> butoane_facultative;
        std::vector<Materie> facultative_selectate;

        std::shared_ptr<Obiect> titlu_optionale;
        std::vector<std::shared_ptr<Obiect>> butoane_optionale;
        std::vector<Materie> optionale_selectate;

        std::vector<NoteMaterie> notare_materii;

        std::shared_ptr<Obiect> titlu_medie_finala_bursa;
        std::shared_ptr<Obiect> medie_finala_bursa;

        std::shared_ptr<Obiect> titlu_medie_finala_buget;
        std::shared_ptr<Obiect> medie_finala_buget;

        std::shared_ptr<Obiect> titlu_credite;
        std::shared_ptr<Obiect> total_credite_display;
            
        std::shared_ptr<Obiect> instructiune1;
        std::shared_ptr<Obiect> instructiune2;
        std::shared_ptr<Obiect> instructiune3;
        std::shared_ptr<Obiect> instructiune4;

        while (app.isRunning())
        {
            app.update();
            app.render();

            if (Aplicatie::getClick())
            {
                if (std::find(butoane_serii.begin(), butoane_serii.end(), Aplicatie::getClick()) != butoane_serii.end())
                {
                    deactivateSeriesButtons(butoane_serii, Aplicatie::getClick(), app);
                    createForwardButton(buton_inainte, font, app);

                    an = Aplicatie::getClick()->getText().front() - '0';
                    serie = Aplicatie::getClick()->getText().back() - '0';
                    Aplicatie::setClick(nullptr);

                    if (an == 1)
                        createYearOneOptions(titlu_facultative, materii, butoane_facultative, font, app, an);
                    else if (an == 2)
                        createYearTwoOptions(titlu_facultative, titlu_optionale, materii, butoane_facultative, butoane_optionale, font, app, an);
                    else if (an == 3)
                        createYearThreeOptions(titlu_optionale, materii, butoane_optionale, font, app, an);
                }

                else if (std::find(butoane_optionale.begin(), butoane_optionale.end(), Aplicatie::getClick()) != butoane_optionale.end())
                {
                    if (an == 2)
                        manageYearTwoOptionals(materii, butoane_optionale, optionale_selectate, app);
                    else if (an == 3)
                        manageYearThreeOptionals(materii, butoane_optionale, optionale_selectate, app);
                    Aplicatie::setClick(nullptr);
                }

                else if (std::find(butoane_facultative.begin(), butoane_facultative.end(), Aplicatie::getClick()) != butoane_facultative.end())
                {
                    manageFacultatives(materii, butoane_facultative, facultative_selectate, app);
                    Aplicatie::setClick(nullptr);
                }

                else if (Aplicatie::getClick() == buton_inainte)
                {
                    Aplicatie::setClick(nullptr);
                    if (checkOptionalSelection(butoane_optionale))
                    {
                        removeFirstPageObjects(app, titlu, alegere_serie, buton_inainte, titlu_facultative, titlu_optionale, butoane_serii, butoane_optionale, butoane_facultative);
                        addPageTwoSideObjects(titlu_medie_finala_bursa, medie_finala_bursa, titlu_medie_finala_buget, medie_finala_buget, titlu_credite, total_credite_display, instructiune1, instructiune2, instructiune3, instructiune4, font, app);
                        addPageTwoSubjectInputs(materii, an, serie, optionale_selectate, facultative_selectate, notare_materii, font, app, titlu_medie_finala_bursa);
                    }
                    setFinals(notare_materii, materii, medie_finala_bursa, medie_finala_buget, total_credite_display);
                }

                else manageGradeInputs(notare_materii, app, materii, serie, titlu_medie_finala_bursa, medie_finala_bursa, medie_finala_buget, total_credite_display);
            }
        }
    }
    catch (InvalidFilePathError& eroare)
    {
        std::cout << eroare.what();
    }
    catch (InvalidFileContentError& eroare)
    {
        std::cout << "Linia " << eroare.getLine() << "\n" << eroare.what();
    }

    return 0;
}