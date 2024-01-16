#include <iostream>
#include <stdlib.h>

using namespace std;

class Klient
{
	int m_typ;
	double m_odlegoscDostawy;
public:
	Klient(int typ, double odl)
		: m_typ(typ), m_odlegoscDostawy(odl)
	{}
	double wysokoscRabatu()
	{
		switch (m_typ)
		{
		default: case 0: // Nowy Klient
			return 0.00;
		case 1: //Stały Klient
			return 0.05;
		case 2: //Zaprzyjaxiony Kliejnt
			return 0.10;
		case 3: // V.I.P.
			return 0.15;
		}
	}
	double odleglModyfKosztuDostawy()
	{
		if (m_odlegoscDostawy < 10.0) //10 km
			return 1.0;
		else if (m_odlegoscDostawy < 100.0) // 100 km
			return 2.0;
		else if (m_odlegoscDostawy < 500.0) // 500 km
			return 3.0;
		else return 3.5;
	}
};

double naliczNaleznosc(int ilosc, double cenaNetto, double masaDetaliczna,
	double marza, int typPodatku, int typKlienta, double odelgosc)
{
	/* Obliczenie ceny brutto: */
	double cenaBrutto = 0;
	switch (typPodatku)
	{
	default: case 0: //zwykły vat
		cenaBrutto = cenaNetto * marza * 0.22; break;
	case 1: // vat 7%
		cenaBrutto = cenaNetto * marza * 0.07; break;
	case 2: // vat 11&
		cenaBrutto = cenaNetto * marza * 0.11; break;
	case 3: // vat 15%
		cenaBrutto = cenaNetto * marza * 0.15; break;
	}
	/* Obliczenie sumy zamówienia: */
	cenaBrutto *= ilosc;

	Klient temp(typKlienta, odelgosc);
	/* Doliczenie kosztów transportu (5.0 to koszt stały)*/
	cenaBrutto += (5.0 + 3.0 * masaDetaliczna * temp.odleglModyfKosztuDostawy());

	/*Odliczenie rabatu: */
	cenaBrutto -= temp.wysokoscRabatu() * cenaBrutto;
	return cenaBrutto;
}

class Zamowienie 
{
private:
	int Liczba_Produktow,
		Podatek_Vat,
		Rabat_Klienta;
	double
		Cena_Netto_Produktu,
		Masa_Produktu,
		Marza,
		Droga_Przetransportowania_Produktu;

	double Koszt_Transportu()
	{
		Klient temp(Rabat_Klienta, Droga_Przetransportowania_Produktu);
		double cenaBrutto =(5.0 + 3.0 * Masa_Produktu * temp.odleglModyfKosztuDostawy());
		return cenaBrutto;
	}

	double Rabat() 
	{
		Klient temp(Rabat_Klienta, Droga_Przetransportowania_Produktu);
		double Wartosc_Rabatu = temp.wysokoscRabatu() * Koszt_Transportu();
		return Wartosc_Rabatu;
	}

	int getPodatek() 
	{
		return Podatek_Vat;
	}

public:
	double Koszt_Realizacji_Zmaowinia()
	{
	
	}
};

void Pierwszy_Test_Funkcji_Nalicz_Naleznosc()
{
	double Oczekiwany_Wynik = 1786.13;
	double Rzeczywisty_Wynik = naliczNaleznosc(5, 43.5, 232.5, 0.16, 2, 3, 174);
	double Niepewnosc_Wyniku_Funkcji = 0.01;
	if (Rzeczywisty_Wynik<Oczekiwany_Wynik+Niepewnosc_Wyniku_Funkcji)
	{
		cerr << "OK!" << endl;
	}
	else
	{
		cerr << "FAIL!" << endl;
	}
}

void Drugi_Test_Funkcji_Nalicz_Naleznosc()
{
	double Oczekiwany_Wynik = 294.578;
	double Rzeczywisty_Wynik = naliczNaleznosc(40, 156.99, 2.5, 0.3, 3, 1, 432);
	double Niepewnosc_Wyniku_Funkcji = 0.01;
	if (abs(Rzeczywisty_Wynik - Oczekiwany_Wynik) < Niepewnosc_Wyniku_Funkcji)
	{
		cerr << "OK!"<<endl;
	}
	else
	{
		cerr << "FAIL!" << endl;
	}
}

void main(void)
{
	int
		Liczba_Produktow =     40,
		Podatek_Vat =		   3,
		Rabat_Klienta =        1;

	double
		Cena_Netto_Produktu=				 156.99,
		Masa_Produktu =					     2.5,
		Marza =							     0.3,
		Droga_Przetransportowania_Produktu = 432;
		
	cerr << naliczNaleznosc(Liczba_Produktow,Cena_Netto_Produktu,Masa_Produktu,Marza,Podatek_Vat,Rabat_Klienta,Droga_Przetransportowania_Produktu) << endl;

	Pierwszy_Test_Funkcji_Nalicz_Naleznosc();
	Drugi_Test_Funkcji_Nalicz_Naleznosc();
}
