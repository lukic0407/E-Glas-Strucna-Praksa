// E-glass sturcna praksa
//Gabrijel Lukic

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//Funkcija za provjeru dali se u bilokojem trenutku nalazi negativan broj putnika u tramvaju
//U slucaju da je ona istinita znaci da su podaci krivo zabiljezeni ili uneseni
bool ProvjeraKapaciteta(int* kapacitet, int d) {
    if (*kapacitet < 0) {
        cout << endl << "Molimo provjerite unesene podatke za " << d + 1 << ".stanicu, jer broj putnika u tramvaju nemoze biti negeativan !!!" << endl;
        return false;
    }else {
        return true;
    }
}

//Funkcija za provjeru dali ulaz i izlaz putnika odgovaraju danim ogranicenjima odnosno da moraju biti manji od 0 i veci od 1000
bool ProvjeraUlazaIzlaza(int ulaz, int izlaz, int d) {
    if (ulaz < 0 || ulaz > 1000) {
        cout << endl << "Molimo provjerite unesene podatke za " << d + 1 << ".stanicu, jer broj ulaza putnika nemoze biti manji od 0 ili veci od 1000" << endl;
        return true;
    }
    else if (izlaz < 0 || izlaz > 1000) {
        cout << endl << "Molimo provjerite unesene podatke za " << d + 1 << ".stanicu, jer broj izlaza putnika nemoze biti manji od 0 ili veci od 1000" << endl;
        return true;
    }
    else {
        return false;
    }
}

//Funkcija za provjeru prve stanice odnosno provjera da nijedan putnik ne izlazi na prvoj stanici
bool ProvjeraPrveStanice(int izlaz) {
    if (izlaz != 0) {
        cout << "Broj ljudi koji izlaze iz tramvaja na prvoj stanici nemoze biti razliciti od 0 !!!" << endl;
        return true;
    }
    else {
        return false;
    }
}

//Funkcija za provjeru zadnje stanice tramvaja. Provjerava da nitko od putnika ne ulazi na zadnjoj stanici te da su svi putnici izasli iz tramvaja
bool ProvjeraZadnjeStanice(int ulaz, int kapacitet) {
    if (ulaz != 0) {
        cout << "Broj ljudi koji ulaze u tramvaj na zadnjoj stanici nemoze biti razliciti od 0 !!!" << endl;
        return true;
    }
    else if (kapacitet != 0) {
        cout << "Na zadnjoj stanici svi ljudi moraju izaci iz tramvaja, molim provjerite unos !!!" << endl;
        cout << "Trenutni broj ljudi u tramvaju iznosi: " << kapacitet << endl;
        return true;
    }
    else {
        return false;
    }
}

//Funkcija koja Ucitava podatke iz datoteke "putnici.txt", liniju po liniju te vrsi odredene provjere nad njima
//Ako su sve provjere uspjesno izvrsene, ispisuje "Minimalni moguci kapacitet tramvaja", u slucaju da dode do greske
//Funkcija vraca obavijest o tome odnosno vraca na mjesto gdje je pozvana false.
bool UcitajIzDatoteke() {
    int d = -1, n = 0, kapacitet = 0, max = 0, ulaz = 0, izlaz = 0;
    ifstream file("Putnici.txt");
    string linija;
    char* next;

    if (!file) {
        cout << "Putnici.txt nije pronaden !!!" << endl;
        return false;
    }

    getline(file, linija);
    char* cLinija = new char[linija.length() + 1];
    strcpy_s(cLinija, linija.length() + 1, linija.c_str());

    char* token = strtok_s(cLinija, " ", &next);
    n = stoi(token);

    if (n < 2 || n>1000) {
        cout << "Broj stanica tramvaja nemoze biti manji od 2 ili veci od 1000 !!!";
        return false;
    }
    else {
        while (getline(file, linija) && d < n-1){ //(d < n-1) Ne ucitava veci broj stanica od definiranog u prvom retku
            d++;
            strcpy_s(cLinija, linija.length() + 1, linija.c_str());
            token = strtok_s(cLinija, " ", &next);
            izlaz = stoi(token);
            kapacitet -= izlaz;
            if (d == 0 && ProvjeraPrveStanice(izlaz)) {
                return false;
            }else if (ProvjeraKapaciteta(&kapacitet, d)) {
                token = strtok_s(NULL, " ", &next);
                ulaz = stoi(token);
                kapacitet += ulaz;
                if (d == n - 1 && ProvjeraZadnjeStanice(ulaz, kapacitet)) {
                    return false;
                }
                if (ProvjeraUlazaIzlaza(ulaz, izlaz, d)) {
                    return false;
                }
                else if (kapacitet > max) {
                    max = kapacitet;
                }
            }
            else {
                return false;
            }
        }
    }
    cout << "Minimalni moguci kapacitet tramvaja iznosi: " << max;
    return true;
    
}

int main() {
    if (!UcitajIzDatoteke()) {
        cout << "Doslo je do greske pri izvrsavanju programa !!!";
    }
    cout << endl;
    system("pause");
}