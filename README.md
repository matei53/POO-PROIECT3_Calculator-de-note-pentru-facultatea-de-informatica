# Calculator de note pentru studenții de informatică din cadrul FMI

## Descriere generală

Această aplicație ajută la calcularea mediei finale pentru domeniul informatică, anul universitar 2024-2025.

Mai întâi se alege seria, apoi se selectează materiile opționale și cele facultative. În cazul alegerii facultativelor, se pot alege orice număr de opțiuni. În cazul alegerii opționalelor, trebuie aleasă o materie pentru anul 2, sau 6 materii (3 din primele 23 afișate și 3 din celelalte 18) pentru anul 3.

La final se inserează toate notele primite pentru fiecare materie (e.g. nota de la examen, nota de la colocviu, nota pe activitatea la curs/seminar/laborator). Această notă trebuie să fie între 0 și numărul aflat între parantezele de după numele evaluării.

Numărul de dinaintea numelui evaluării reprezintă numărul de puncte aduse de evaluarea respectivă în nota finală.

Dacă nota introdusă sau nota finală a unei materii este sub pragul de promovare, căsuța cu numele materiei va deveni roșie, indicând picarea materiei.

Nota finală a unei materii este calculată după ce au fost introduse toate notele pentru materia respectivă, iar mediile generale sunt calculate după ce au fost introduse toate notele pentru toate materiile.

Pentru a ieși din aplicație apăsați ESC.

## Clase

### Obiect - cu derivatele TitleText (căsuță de text simplă), Buton, TextInput (căsuță pentru introducerea notelor)

Acestea reprezintă cele trei tipuri de obiecte ce vor putea fi văzute în interfață.

Un obiect se declară cu următoarele valori: poziția și mărimea pe interfață, mărimea fontului, textul, font și culoare. Pentru un buton, se mai adaugă o culoare pentru animația apăsării, pentru o căsuță de input, se mai adaugă o limită de caractere ce pot fi introduse, iar pentru o căsuță simplă se pot adăuga alte trei culori pentru o animație constantă.

Aceste clase conțin **funcția virtuală pură *update()***, care se ocupă de animații. Pentru un buton, animația presupune schimbarea culorii acesteia pentru cinci secunde și revenirea la culoarea normală, pentru o căsuță simplă, animația presupune schimbarea culorii acesteia odată la cinci secunde, iar pentru o căsuță de input, animația presupune apariția și dispariția caracterului '|' pentru a indica că acel input este activ.

În plus, mai este și **funcția virtuală *align()***, care aliniază textul la stânga pentru căsuța de text simplă, și în centru pentru restul obiectelor.

Aceste funcții virtuale sunt **apelate prin pointeri *(sunt folosiți numai smart pointers)* la clasa Obiect**. Dacă este nevoie de o apelare a unei funcții care face parte numai dintr-o clasă derivată, se folosește **std::dynamic_pointer_cast<derivată>()** pentru a o putea accesa.

Acești pointeri la obiecte se pot găsi în main, **dar și în funcțiile clasei Aplicatie**.

### Aplicatie

Această clasă este folosită pentru a gestiona interfața.

Aplicația se declară cu lungimea, înălțimea și titlul ferestrei deschise. Clasa mai conține și doi vectori de obiecte, unul care reține toate obiectele din interfață, și altul care reține care dintre ele pot fi apăsate.

De asemenea, aici se găsesc **atributele statice *active_input* și *clicked***, care rețin căsuța de input activă, respectiv obiectul apăsat la un anumit moment.

Atributul *clicked* este gestionat de **funcțiile statice *setClick(obiect)* și *getClick()***, iar atributul *active_input* este gestionat de **funcțiile stative *getActiveInput()* și *setActiveInput(căsuță)***.

Atâta timp cât fereastra este deschisă, se verifică dacă un obiect a fost apăsat cu *getClick*. Dacă da, atunci se fac modificări pe interfață în funcție de ce a fost apăsat, iar apoi obiectul apăsat se setează la *nullptr*.

### Materie, Notare, Evaluare

Clasele Materie, Notare și Evaluare sunt folosite pentru a reține toate materiile și metodele de notare pentru fiecare dintre acestea. Fiecare materie are trei metode de notare separate, una pentru fiecare serie. Fiecare metodă de notare cuprinde mai multe evaluări, care au un procentaj din nota finală, un prag de promovare și o notă maximă care poate fi obținută.

### InvalidFilePathError, InvalidFileContentError, InvalidInputError - derivate din std:exception

Clasa InvalidFilePathError este folosita atunci cand fișierul cu informațiile despre materii sau cel cu fontul textului nu pot fi incarcate. In acest caz, se va închide fereastra (dacă este deschisă), și se va afișa un mesaj (cu funcția suprascrisă *what*) în terminal legat de problemă.

Clasa InvalidFileContentError este folosită atunci când fișierul cu informațiile despre materii nu conține informatii potrivite pentru program. În acest caz, pe lângă mesaj, se va afișa și linia din fișierul text unde s-a găsit problema.

Clasa InvalidInputError este folosită atunci când este salvată o notă invalidă introdusă într-o căsuță de input. În acest caz, culoarea de animație a butonului de salvare se va schimba în roșu, iar nota nu se va salva.

## Resurse

[SFML](https://github.com/SFML/SFML/tree/3.0.1) (Zlib)
