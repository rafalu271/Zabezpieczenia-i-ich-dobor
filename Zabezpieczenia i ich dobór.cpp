// Zabezpieczenia i ich dobór.cpp : Definicja bibliotek wykorzystanych w programie
//
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// ----------------------------- Definicja zmiennych -----------------------------

// Przechowywanie parametrów silników
string nazwa_s[50];
int nr_s[50];
float prad_znam_s[50], moc_s[50], sprawnosc_s[50], il_in[50];

//	Przechowywanie parametrów bezpieczników
string nazwa_z[50];
int nr_z[50], numer_dobrany_bezp;
float prad_znam_z[50];

//	Przechowywanie parametrów przewodów
string nazwa_k[50], przekroj_k[50];
int nr_k[50], un_k[50], numer_dobrany_kabel;
float obc_prad_k[50];

int podany_silnik, podany_wkladka, podany_rozruch, podany_kabel;  // <--- Wartoœci pobierane od urzytkownika

// ----------------------------- Klasy -----------------------------

class cPliki
{
private:
	string linia;
	int czy_zapis;
	string nazwa_plik_zapis;

public:

	int ilosc_linii;
	int nr_linii, nr_elementu;

// ----------------------------- Metody -----------------------------

	void pobierz_plik_silniki(string nazwa_pliku)
	{
		ilosc_linii = 1;

		fstream silnik;
		silnik.open(nazwa_pliku, ios::in);

		if(silnik.good() == false)
		{
			cout << "Plik " << nazwa_pliku << " nie istnieje! Niepoprawny odczyt!" << endl;
		}

// Zmienne definiowane w celu zapisu tekstu z wczytanego pliku

		nr_linii = 1;
		nr_elementu = 1;

// Zapis danych z pliku do tablic odpowiadaj¹cyh poszczególnym parametrom

		while (getline(silnik,linia))
		{
			switch (nr_linii)
			{
				case 1: nr_s[nr_elementu] = atoi(linia.c_str());										break;
				case 2: nazwa_s[nr_elementu] = linia;													break;
				case 3: moc_s[nr_elementu] = atof(linia.c_str());										break;
				case 4: sprawnosc_s[nr_elementu] = atof(linia.c_str());									break;
				case 5: prad_znam_s[nr_elementu] = atof(linia.c_str());									break;
				case 6: il_in[nr_elementu] = atof(linia.c_str());				ilosc_linii++;			break;
			}

			if (nr_linii==6) {nr_linii=0; nr_elementu++;}
			nr_linii++;
		}
		ilosc_linii = ilosc_linii - 1;
		silnik.close();
	}

	void pobierz_plik_zabezpieczenia(string nazwa_pliku)
	{
		ilosc_linii = 1;

		fstream bezpiecznik;
		bezpiecznik.open(nazwa_pliku, ios::in);
		if(bezpiecznik.good() == false)
		{
			cout << "Plik " << nazwa_pliku << " nie istnieje! Niepoprawny odczyt!" << endl;
		}

// Zmienne definiowane w celu zapisu tekstu z wczytanego pliku

		nr_linii = 1;
		nr_elementu = 1;

// Zapis danych z pliku do tablic odpowiadaj¹cyh poszczególnym parametrom


		while (getline(bezpiecznik,linia))
		{
			switch (nr_linii)
			{
				case 1: nr_z[nr_elementu] = atoi(linia.c_str());									break;
				case 2: nazwa_z[nr_elementu] = linia;												break;
				case 3: prad_znam_z[nr_elementu] = atof(linia.c_str());			ilosc_linii++;		break;
			}

			if (nr_linii==3) {nr_linii=0; nr_elementu++;}
			nr_linii++;
		}
	ilosc_linii = ilosc_linii - 1;
	bezpiecznik.close();
	}

	void pobierz_plik_przewody(string nazwa_pliku)
	{
		ilosc_linii = 1;

		fstream przewod;
		przewod.open(nazwa_pliku, ios::in);

		if(przewod.good() == false)
		{
			cout << "Plik " << nazwa_pliku << " nie istnieje! Niepoprawny odczyt!" << endl;
		}

// Zmienne definiowane w celu zapisu tekstu z wczytanego pliku

		int nr_linii = 1;
		int nr_elementu = 1;

// Zapis danych z pliku do tablic odpowiadaj¹cyh poszczególnym parametrom

		while (getline(przewod,linia))
		{
			switch (nr_linii)
			{
				case 1: nr_k[nr_elementu] = atoi(linia.c_str());										break;
				case 2: un_k[nr_elementu] = atof(linia.c_str());										break;
				case 3: przekroj_k[nr_elementu] = linia;												break;
				case 4: obc_prad_k[nr_elementu] = atof(linia.c_str());									break;
				case 5: nazwa_k[nr_elementu] = linia;						ilosc_linii++;				break;
			}

			if (nr_linii==5) {nr_linii=0; nr_elementu++;}
			nr_linii++;
		}
		ilosc_linii = ilosc_linii - 1;
		przewod.close();
	}

	void eksport_obliczen(int nr_silnika, int zmienna_pom_bez, int zmienna_pom_kabel)
	{
		cout << "Czy chcesz zapisac dobrane elementy do silnika?" << endl << "1. - Tak, poprosze" << endl << "2. - Nie, dziekuje" << endl;
		cin >> czy_zapis;

		if (czy_zapis == 1)
		{
			cout << endl << "Jak chcesz nazwac plik?" << endl;
			cin >> nazwa_plik_zapis;

			fstream plik;
			plik.open(nazwa_plik_zapis,ios::out);

			plik << "Podany silnik: " << nazwa_s[nr_silnika] << ", Moc: " << moc_s[nr_silnika] << "kW, Sprawnosc: " << sprawnosc_s[nr_silnika]
				 << "%, Prad znamionowy: " << prad_znam_s[nr_silnika] << "A, Il/In = " << il_in[nr_silnika] << endl;
			plik << "Dobrany przewod: " << nazwa_k[zmienna_pom_kabel] << " " << przekroj_k[zmienna_pom_kabel] << endl;
			plik << "Dobrana wkladka: " << nazwa_z[zmienna_pom_bez] << " " << prad_znam_z[zmienna_pom_bez] << "A" << endl;

			plik.close();

		}

	}
};

class cWyswietl
{
public:
	int pobrany_element;

	void wybor(int linia, string element, string nazwa[], int nr_elementu[])
	{
		bledny_numer:

		for (int i = 1; i <= linia; i++)
		{
			cout << nr_elementu[i] << " " << nazwa[i] << /*" " << moc_s[i] << " " << prad_s[i] <<*/ endl;
		}
		cout << endl << "Podaj numer wybranego " << element << ": ";
		cin >> pobrany_element;

		if (pobrany_element > linia)
		{
			system ("cls");
			cout << "Podany nr. " << element <<" nie istnieje." << endl << "Prosze podac numer jeszcze raz z podanych na ekranie: " << endl << endl;
			goto bledny_numer;
		}

		system ("cls");
	}
};

class cObliczenia
{
private:
	int kg, zmienna_pom;
	float kt, k2, Ib, In, I_pom, I_ze, I2, I_pom2, I_rmax, I_pom3, a;
	float obc_prad_kc;

public:

	void dobor_przewodu(int podany_silnik)
	{
		zmienna_pom = 1;
		obc_prad_kc = obc_prad_k[zmienna_pom];			//cout << "obc_prad_kc = " << obc_prad_kc << endl;
		kg = 1;
		kt = 1.06;
		k2 = 1.15;

		Ib = 1.2 * prad_znam_s[podany_silnik];			//cout << "Ib = " << Ib << endl;
		In = Ib + 0.05;									//cout << "In = " << In << endl;

		I_pom = In/(kg*kt); /* <= Iz */					//cout << "I_pom = " << I_pom << endl;	

// + sprawdzenie pradu Iz
		if (I_pom > obc_prad_kc)
		{
			do
			{
				zmienna_pom ++;
				obc_prad_kc = obc_prad_k[zmienna_pom];
			} while (I_pom > obc_prad_kc);
		}
														//cout << "obc_prad_kc = " << obc_prad_kc << endl;
														//cout << "Zmienna pomocnicza: " << zmienna_pom << endl;

		// Koniec warunków

		I_ze = kg * kt * obc_prad_kc;					//cout << "I_ze = " << I_ze << endl;

		// Drugi warunek

		I2 = k2 * In;									//cout << "I2 = " << I2 << endl;
		I_pom2 = 1.45 * I_ze;							//cout << "I_pom2 = " << I_pom2 << endl;

		// Funkcja porownawcza dwoch powyzszych warunkow
		//
		//
		numer_dobrany_kabel = zmienna_pom;
		cout << "Dobrany przewod: " << nazwa_k[zmienna_pom] << " " << przekroj_k[zmienna_pom] << endl;
	}

	void dobor_zabezpieczenie()
	{
		zmienna_pom = 1;

		if (podany_rozruch == 1)
		{
			a = 2;
		}

		else if (podany_rozruch == 2)
		{
			a = 3;
		}

																	cout << "a = " << a << endl;
																	cout << "Ib = " << Ib << endl;

		I_rmax = (Ib * il_in[podany_silnik])/3;						cout << "I_rmax = " << I_rmax << endl;
		I_pom3 = I_rmax/a;											cout << "I_pom3 = " << I_pom3 << endl;

		if (I_pom3 >= Ib) 
		{
			do
			{
				zmienna_pom ++;
			} while (I_pom3 >= prad_znam_z[zmienna_pom]);
			
																	cout << "zmien pom = " << zmienna_pom << endl;
			numer_dobrany_bezp = zmienna_pom;
			cout << "Dobrana wkladka: " << nazwa_z[zmienna_pom] << " " << prad_znam_z[zmienna_pom] << "A" << endl;
		}

		else
		{
			do
			{
				zmienna_pom ++;
			} while (Ib >= prad_znam_z[zmienna_pom]);

																	cout << "zmien pom = " << zmienna_pom << endl;
			numer_dobrany_bezp = zmienna_pom;
			cout << "Dobrana wkladka: " << nazwa_z[zmienna_pom] << " " << prad_znam_z[zmienna_pom] << "A" << endl;
		}
	}
		
};


// ----------------------------- Funkcja main -----------------------------

int main()
{

	cout << endl << "Program sluzy do doboru zabezpieczenia oraz" << endl << "przewodu dla wybranego z katalogu silnika." << endl << endl;
	cout << "Katalogi txt musza znajdowac sie w wolderze razem z programem: " << endl;
	cout << " - silniki.txt" << endl;
	cout << " - zabezpieczenia.txt" << endl;
	cout << " - kable.txt" << endl << endl;

	cout << "Wcisnij Enter by kontynuowac...";
	getchar ();
	system ("cls");

// ----------------------------- Pobranie danych z pliku silniki.txt -----------------------------

	kolejny_przypadek:

	cPliki silniki;
	silniki.pobierz_plik_silniki("silniki.txt");

// Wyœwietlanie oraz wybór modelu silnika wczytanego z pliku

	int ilosc_linii_sil = silniki.ilosc_linii;

	cWyswietl druk;
	druk.wybor(ilosc_linii_sil, "silnika", nazwa_s, nr_s);
	podany_silnik = druk.pobrany_element;

	cout << "Podany silnik: " << nazwa_s[podany_silnik] << ", Moc: " << moc_s[podany_silnik] << "kW, " << endl << "Sprawnosc: " << sprawnosc_s[podany_silnik]
	<< "%, Prad znamionowy: " << prad_znam_s[podany_silnik] << "A, Il/In = " << il_in[podany_silnik] << endl << endl;

// ----------------------------- Pobranie danych z pliku zabezpieczenia.txt -----------------------------

	cPliki zabezpieczenia;
	zabezpieczenia.pobierz_plik_zabezpieczenia("zabezpieczenia.txt");

// ----------------------------- Pobranie danych z pliku kable.txt -----------------------------

	cPliki kable;
	kable.pobierz_plik_przewody("kable.txt");

// ----------------------------- Wybór rodzaju rozruchu -----------------------------

	rozruch:										//Etykieta dla zle dobranego rozruchu

	cout << "Mozliwe rodzaje rozruchu:" << endl;
	cout << 1 << ". rozruch sredni - dzialanie opoznione" << endl;
	cout << 2 << ". rozruch nr 2" << endl;

	cout << "Podaj numer dobranego rodzaju rozruchu: ";
	cin >> podany_rozruch;

	if (podany_rozruch > 2)
	{
		system ("cls");
		cout << "Podany rozruch nie istnieje. Prosze wybrac ponownie z podanych ponizej." << endl << endl;
		goto rozruch;
	}

	system ("cls");

// ----------------------------- Obliczenia doboru wk³adki oraz porzewodu -----------------------------

	cObliczenia oblicz;
	oblicz.dobor_przewodu(podany_silnik);
	oblicz.dobor_zabezpieczenie();

// ----------------------------- Czy chcesz wyeksportowac obliczenia? -----------------------------

	cPliki zapis;
	zapis.eksport_obliczen(podany_silnik, numer_dobrany_bezp, numer_dobrany_kabel);

// ----------------------------- Czy chcesz dobrac przewody ponownie? -----------------------------

	int ponownie;
	cout << endl << "Czy chcesz dobrac elementy ponownie?: " << endl << "1 - Tak" << endl << "2 - Nie" << endl;
	cin >> ponownie;

	system ("cls");

	if (ponownie==1)
	{
		goto kolejny_przypadek;
	}

	else
	{
		cout << "Dziekujemy za skozystanie z naszych uslug." << endl << "Zyczymy milego dnia!" << endl << endl << "R Urlich Corp." << endl << endl;
		cout << "Prosze wcisnac dowolny klawisz oraz Enter by zakonczyc...";
		int koniec;
		cin >> koniec;
	}

	return 0;
}