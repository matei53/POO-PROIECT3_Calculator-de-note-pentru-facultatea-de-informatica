# Calculator de note pentru studenții de informatică din cadrul FMI (PROIECTUL 3)

## Acest proiect este o continuare a proiectului 2, ce poate fi văzut [aici](https://github.com/matei53/Calculator-de-note-pentru-facultatea-de-informatica).

## Descriere generală

Această aplicație ajută la calcularea mediei finale pentru domeniul informatică, anul universitar 2024-2025.

Mai întâi se alege seria, apoi se selectează materiile opționale și cele facultative. În cazul alegerii facultativelor, se pot alege orice număr de opțiuni. În cazul alegerii opționalelor, trebuie aleasă o materie pentru anul 2, sau 6 materii (3 din primele 23 afișate și 3 din celelalte 18) pentru anul 3.

La final se inserează toate notele primite pentru fiecare materie (e.g. nota de la examen, nota de la colocviu, nota pe activitatea la curs/seminar/laborator). Această notă trebuie să fie între 0 și numărul aflat între parantezele de după numele evaluării.

Numărul de dinaintea numelui evaluării reprezintă numărul de puncte aduse de evaluarea respectivă în nota finală.

Dacă nota introdusă sau nota finală a unei materii este sub pragul de promovare, căsuța cu numele materiei va deveni roșie, indicând picarea materiei.

Nota finală a unei materii este calculată după ce au fost introduse toate notele pentru materia respectivă, iar mediile generale sunt calculate după ce au fost introduse toate notele pentru toate materiile.

Pentru a ieși din aplicație apăsați ESC.

## Design patterns

### Singleton

Acest design pattern este implementat în clasa Aplicație, și ne asigură că poate exista o singură instanță a aplicației la un moment dat.

Implementarea presupune:
1. ștergerea *constructorului de copiere* și a *operatorului de atribuire (operator=)* din clasă;
2. crearea funcției statice **getAplicatie()**, care construiește o instanță a aplicației și o returnează.

### Factory (ObiectFactory.h)

Acest design pattern este implementat în clasa **ObiectFactory**, care conține numai funcții statice publice ce returnează diverse obiecte ce urmează anumite formate. Aceste funcții au ca atribute poziția obiectului în fereastră, textul și fontul obiectului.

Aceste funcții simplifică crearea:
1. butoanelor de alegere a seriei;
2. butoanelor de alegere a materiilor opționale/facultative;
3. căsuțelor cu titlul materiei, nota finală, metodele de evaluare, inputurile, salvările (pentru fiecare materie);
4. căsuțelor cu media finală, punctajul de credit și numărul de credite.

### State

Acest design pattern este implementat în clasa **TextInput**, prin clasa **State** (cu derivatele **ActiveState** și **InactiveState**).

Clasa *State* conține funcțiile virtuale **active(TextInput\*)** și **inactive(TextInput\*)**, clasa *ActiveState* conține funcția **inactive(TextInput\*)** (care schimbă starea atributului la tipul InactiveState), iar clasa *InactiveState* conține funcția **active(TextInput\*)** (care schimbă starea atributului la tipul ActiveState).

Funcțiile din clasa de bază pot fi apelate numai în cazul în care încercăm să dezactivăm un input deja inactiv sau să activăm un input deja activ, caz în care nu se întâmplă nimic. Schimbarea stării atributului se face cu funcția *setState*, descrisă mai jos.

La clasa *TextInput* s-au adăugat membrul *activ* de tip std::shared_ptr\<State> (inițializat cu pointer la InactiveState), și funcțiile **on()**, **off()** și **setState(std::shared_ptr\<State>)**.

Funția *on* face membrul *activ* să apeleze funcția *active(this)* (efectiv, activează inputul), iar funția *off* face membrul *activ* să apeleze funcția *inactive(this)* (efectiv, dezactivează inputul). Funcția *setState(s)* schimbă starea lui *activ* la *s*.

## Funcții șablon (FuncțiiTemplate.h)

### void eraseFromVector(std::vector\<T>& vect, T obj)

Șterge obiectul *obj* din vectorul de obiecte *vect*.

Această funcție este folosită:

1. pentru a șterge materiile cu anul diferit de cel selectat (la alegerea seriei) din vectorul principal de materii;
2. în funcțiile aplicației *removeObject(obj)* și *removeClickableObject(obj)*, pentru a șterge obiectul apelat din vectorul de obiecte (și, după caz, din vectorul de obiecte clickable) din aplicație.

### bool isInVector(std::vector\<T> vect, T obj)

Returnează *true* dacă obiectul *obj* este în vectorul de obiecte *vect*.

Această funcție este folosită:

1. pentru a verifica dacă un obiect apăsat (obținut cu funcția aplicației *getClick()*) se află într-un vector de obiecte (e.g. butoanele de alegere a seriei, butoanele de alegere a materiilor opționale/facultative, căsuțele de introducere a notelor, butoanele de salvare a notelor), pentru a ști ce cod trebuie executat în urma unei apăsări;
2. în afișarea materiilor opționale/facultative în pagina de introducere a notelor, prin alfarea materiilor care se află și în vectorul principal de materii, și în vectorul de opționale/facultative selectate;
3. în funcțiile aplicației *removeObject(obj)* și *removeClickableObject(obj)*, pentru a afla dacă obiectul apelat trebuie șters din vectorul de obiecte clickable din aplicație.

## Clasă șablon - Buton\<TipAnimație>

Clasa **Buton** a fost transformată în clasă șablon, având un membru șablon ce reprezintă tipul de animație a click-ului.

Tipurile de animație au fost implementate cu clasele:
1. **SeriesSelectionClick** (butonul își schimbă culoarea pentru o durată de timp, iar apoi revine la cea inițială);
2. **OptFacSelectionClick** (butonul alternează între două culori la infinit);
3. **GradeSaveClick** (butonul își schimbă culoarea în ordinea culoare secundară - culoare inițială - culoare secundară - culoare inițială).

Cele trei clase au funcția membru **animate**, care execută animațiile descrise mai sus. Funcția este apelată prin membrul șablon al clasei Buton menționat mai sus.

## Resurse

[SFML](https://github.com/SFML/SFML/tree/3.0.1) (Zlib)
