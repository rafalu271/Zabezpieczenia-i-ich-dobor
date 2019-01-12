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

// Zmienne urzyte podczas pracy programu
//
//

int nr_linii_s = -1, nr_linii_b = -1, nr_linii_p = -1;	// <--- Zmienne do katalogów

// Przechowywanie parametrów silników
string nazwa_s[100];
int moc_s[100], prad_s[100];

//	Przechowywanie parametrów bezpieczników
string nazwa_b[100];
int moc_b[100], prad_b[100];

//	Przechowywanie parametrów przewodów
string nazwa_p[100];
int moc_p[100], prad_p[100];


int podany_silnik, podany_wkladka, podany_rozruch;  // <--- Wartoœci pobierane od urzytkownika


int main()
{
	// Pobranie danych z pliku silniki.txt								--- Katlog silników
	//
	//

	fstream silnik;
	silnik.open("silniki.txt", ios::in);

	if(silnik.good() == false)
	{
		cout << "Plik silniki.txt nie istnieje! Niepoprawny odczyt!" << endl;
	}

	// Zmienne definiowane w celu zapisu tekstu z wczytanego pliku
	//
	//

	string linia_sil;
	int nr_linii_sil = 1;
	int nr_silnika = 0;

	// Zapis danych z pliku do tablic odpowiadaj¹cyh poszczególnym parametrom
	//
	//

	while (getline(silnik,linia_sil))
	{
		switch (nr_linii_sil)
		{
			case 1: nazwa_s[nr_silnika] = linia_sil;										break;
			case 2: moc_s[nr_silnika] = atoi(linia_sil.c_str());							break;
			case 3: prad_s[nr_silnika] = atoi(linia_sil.c_str());		nr_linii_s++;		break;
		}

		if (nr_linii_sil==3) {nr_linii_sil=0; nr_silnika++;}
		nr_linii_sil++;
	}
	silnik.close();

	// Wyœwietlanie oraz wybór modelu silnika wczytanego z pliku
	//
	//

	for (int i = 0; i <= nr_linii_s; i++)
	{
		cout << i << " " << nazwa_s[i] << /*" " << moc_s[i] << " " << prad_s[i] <<*/ endl;
	}
	cout << "Podaj numer wybranego modelu silnika: ";
	cin >> podany_silnik;

	if (podany_silnik > nr_linii_s)
	{
		cout << "Podany nr. silnika nie istnieje. Prosze podac numer jeszcze raz z podanych na ekranie: ";
		cin >> podany_silnik;
	}


	// Pobranie danych z pliku bezpieczniki.txt							--- Katalog bezpieczników
	//
	//

	fstream bezpiecznik;
	bezpiecznik.open("bezpieczniki.txt", ios::in);
	if(bezpiecznik.good() == false)
	{
		cout << "Plik bezpieczniki.txt nie istnieje! Niepoprawny odczyt!" << endl;
	}

	// Zmienne definiowane w celu zapisu tekstu z wczytanego pliku
	//
	//

	string linia_bez;
	int nr_linii_bez = 1;
	int nr_bezpiecznika = 0;

	// Zapis danych z pliku do tablic odpowiadaj¹cyh poszczególnym parametrom
	//
	//

	while (getline(bezpiecznik,linia_bez))
	{
		switch (nr_linii_bez)
		{
			case 1: nazwa_b[nr_bezpiecznika] = linia_bez;										break;
			case 2: moc_b[nr_bezpiecznika] = atoi(linia_bez.c_str());							break;
			case 3: prad_b[nr_bezpiecznika] = atoi(linia_bez.c_str());		nr_linii_b++;		break;
		}

		if (nr_linii_bez==3) {nr_linii_bez=0; nr_bezpiecznika++;}
		nr_linii_bez++;
	}
	bezpiecznik.close();

	// Wyœwietlanie oraz wybór modelu silnika wczytanego z pliku
	//
	//

	for (int i = 0; i <= nr_linii_b; i++)
	{
		cout << i << " " << nazwa_b[i] << /*" " << moc_s[i] << " " << prad_s[i] <<*/ endl;
	}
	cout << "Podaj numer wybranego typu wk³adki: ";
	cin >> podany_wkladka;

	// Pobranie danych z pliku przewody.txt								--- Katalog przewodów
	//
	//

	fstream przewod;
	przewod.open("przewody.txt", ios::in);

	if(przewod.good() == false)
	{
		cout << "Plik przewody.txt nie istnieje! Niepoprawny odczyt!" << endl;
	}

	// Zmienne definiowane w celu zapisu tekstu z wczytanego pliku
	//
	//

	string linia_prze;
	int nr_linii_prze = 1;
	int nr_przewodu = 0;

	// Zapis danych z pliku do tablic odpowiadaj¹cyh poszczególnym parametrom
	//
	//

	while (getline(przewod,linia_prze))
	{
		switch (nr_linii_prze)
		{
			case 1: nazwa_p[nr_przewodu] = linia_prze;										break;
			case 2: moc_p[nr_przewodu] = atoi(linia_prze.c_str());							break;
			case 3: prad_p[nr_przewodu] = atoi(linia_prze.c_str());		nr_linii_p++;		break;
		}

		if (nr_linii_prze==3) {nr_linii_prze=0; nr_przewodu++;}
		nr_linii_prze++;
	}
	przewod.close();


	// Wyœwietlanie oraz wybór rodzaju rozruchu
	//
	//

	cout << 1 << ". rozruch nr 1" << endl;
	cout << 2 << ". rozruch nr 2" << endl;
	cout << 3 << ". rozruch nr 3" << endl;

	cout << "Podaj numer wybranego rodzaju rozruchu: ";
	cin >> podany_rozruch;

	if (podany_rozruch > 3)
	{
		cout << "Podany rozruch nie istnieje. Prosze wybrac ponownie z podanych na ekranie.";
		cin >> podany_rozruch;
	}

	//	Uproszczona logika w celu sprawdzenia dzia³ania tablic pobieranych elementów
	//
	//

	float sum_moc, sum_prad;
	double napiece;

	sum_moc  =	moc_s[podany_silnik]	+ moc_b[podany_wkladka]		+ moc_p[podany_rozruch];
	sum_prad =	prad_s[podany_silnik]	+ prad_b [podany_wkladka]	+ prad_p[podany_rozruch];

	napiece  =	sum_moc / sum_prad;

	cout << endl;
	cout << "Suma mocy: "			<< sum_moc		<< endl;
	cout << "Suma pradu: "			<< sum_prad		<< endl;
	cout << "Calkowite napiecie: "  << napiece		<< endl;

	string wyjscie;
	cin >> wyjscie;

	getchar ();
	return 0;
}