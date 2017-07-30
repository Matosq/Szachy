#include<iostream>
#include"szachy.h"
#include"windows.h"
#include<conio.h>
using namespace std;

///////////////////////////////
// Klasa CPionek

bool CPionek::ruch(int wX, int kX, int wY, int kY, CFigura* temp_p[8][8])
{
	///////////////////////////////////////////////
	// Fukcja sprawdza zakres ruchow figury
	// jesli moze ona sie przeniesc na podane wspolrzedne to zwraca TRUE
	
	CFigura* temp = temp_p[wY-1][kY-1];
	// warunek czy pole na ktore przesuwamy figure jest zajete przez inna figure
	if (temp == NULL)
	{
		if (kX == kY)
		{
			if (getGracz() == 2)
			{
				if (wY == wX + 1)
				{
					return true;
				}
			}
			else
			{
				if (wY == wX - 1)
				{
					return true;
				}
			}
		}
	}
	else
	{
		if ((kX == kY + 1) || (kX == kY - 1))
		{
			if (getGracz() == 2)
			{
				if (wY == wX + 1)
				{
					return true;
				}
			}
			else
			{
				if (wY == wX - 1)
				{
					return true;
				}
			}
		}
	}
	return false;
}


////////////////////////////////
// Klasa CWieza

bool CWieza::ruch(int wX, int kX, int wY, int kY, CFigura* temp_p[8][8])
{
	///////////////////////////////////////////////
	// Fukcja sprawdza zakres ruchow figury
	// jesli moze ona sie przeniesc na podane wspolrzedne to zwraca TRUE

	// sprawdzam czy na drodze nie stoi inna figura
	// wieza przesuwa sie w pionie i poziomie
	if (wX == wY)
	{
		int i = (kY - kX > 0) ? 1 : -1;
		for (int j = (kX + i-1); j != (kY-1); j = j+i)
		{
			if (temp_p[wX-1][j] != NULL)return false;
		}
		return true;
	}
	else if (kX == kY)
	{
		int k = (wY - wX > 0) ? 1 : -1;
		for (int h = (kX + k - 1); h != (wY-1); h =h+ k)
		{
			if (temp_p[h][kX-1] != NULL)return true;
		}
		return true;
	}
	return false;
}

////////////////////////////////
// Klasa CSkoczek
// Przesuwa sie po literze 'L'

bool CSkoczek::ruch(int wX, int kX, int wY, int kY, CFigura* temp_p[8][8])
{
	if ((wX == wY + 2) || (wX == wY - 2))
	{
		if ((kX == kY + 1) || (kX == kY - 1))
		{
			return true;
		}
	}
	if ((wX == wY + 1) || (wX == wY - 1))
	{
		if ((kX == kY + 2) || (kX == kY - 2))
		{
			return true;
		}
	}
	return false;
}

////////////////////////////////
// Klasa CKrol
// krol porusza sie o jedno pole w dowolnym kierunku

bool CKrol::ruch(int wX, int kX, int wY, int kY, CFigura* temp_p[8][8])
{
	int i = wY - wX;
	int j = kY - kX;
	if (((i >= -1) && (i <= 1)) && ((j >= -1) && (j <= 1)))
	{
		return true;
	}
	return false;
}

////////////////////////////////
// Klasa CHetman
// hetman (krolowka) porusza sie po liniach prostych i przekatnych
// nie moze przeskakiwac przez inne figury

bool CHetman::ruch(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, CFigura* temp_p[8][8])
{
	if (iSrcRow == iDestRow) {
		
		int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
		for (int iCheckCol = iSrcCol + iColOffset; iCheckCol != iDestCol; iCheckCol = iCheckCol + iColOffset) {
			if (temp_p[iSrcRow][iCheckCol] != 0) {
				return false;
			}
		}
		return true;
	}
	else if (iDestCol == iSrcCol) {
		
		int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
		for (int iCheckRow = iSrcRow + iRowOffset; iCheckRow != iDestRow; iCheckRow = iCheckRow + iRowOffset) {
			if (temp_p[iCheckRow][iSrcCol] != 0) {
				return false;
			}
		}
		return true;
	}
	else if ((iDestCol - iSrcCol == iDestRow - iSrcRow) || (iDestCol - iSrcCol == iSrcRow - iDestRow)) {
		
		int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
		int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
		int iCheckRow;
		int iCheckCol;
		for (iCheckRow = iSrcRow + iRowOffset, iCheckCol = iSrcCol + iColOffset;
			iCheckRow != iDestRow;
			iCheckRow = iCheckRow + iRowOffset, iCheckCol = iCheckCol + iColOffset)
		{
			if (temp_p[iCheckRow][iCheckCol] != 0) {
				return false;
			}
		}
		return true;
	}
	return false;

}

////////////////////////////////
// Klasa CGoniec
// goniec porusza sie po przekatnych o dowolna ilosc pol

bool CGoniec::ruch(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, CFigura* temp_p[8][8])
{
	if ((iDestCol - iSrcCol == iDestRow - iSrcRow) || (iDestCol - iSrcCol == iSrcRow - iDestRow)) {
		
		int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
		int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
		int iCheckRow;
		int iCheckCol;
		for (iCheckRow = iSrcRow + iRowOffset, iCheckCol = iSrcCol + iColOffset;
			iCheckRow != iDestRow;
			iCheckRow = iCheckRow + iRowOffset, iCheckCol = iCheckCol + iColOffset)
		{
			if (temp_p[iCheckRow][iCheckCol] != 0) {
				return false;
			}
		}
		return true;
	}
	return false;
}


///////////////////////////////////
// Klasa CPlansza

void CPlansza::setWynikGracz1()
{
	wynikGracz1++;
}

void CPlansza::setWynikGracz2()
{
	wynikGracz2++;
}

void CPlansza::wyswietl()
{
	///////////////////////////////
	// Fukcja wystwietlajaca aktualna plansze

	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	cout << "    1   2   3   4   5   6   7   8		wynik:" << endl;;
	cout << "    v   v   v   v   v   v   v   v ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "		gracz1 " <<wynikGracz1<< endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << "    --------------------------------";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "		gracz2 " << wynikGracz2 << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	for (int i = 0; i < 8; i++)
	{
		cout << " " << wiersz[i] << "-| ";
		for (int j = 0; j < 8; j++)
		{
			if (pole[i][j] == NULL)
			{
				cout << " ";
			}
			else
			{
				if (pole[i][j]->getGracz() == 1)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				}
				else if (pole[i][j]->getGracz() == 2)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				}
				cout << pole[i][j]->symbol();
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			cout << " | ";
			if (i == 3 && j==7)
			{
				cout << "		W - wieza";
			}
			else if (i == 4 && j==7)
			{
				cout << "		K - krol";
			}
			else if (i == 5 && j == 7)
			{
				cout << "		G - goniec";
			}
		}
		cout << endl << "    --------------------------------";

		if (i==2)
		{
			cout << "		P - pionek";
		}
		else if (i == 3)
		{
			cout << "		S - skoczek";
		}
		else if (i == 4)
		{
			cout << "		H - hetman";
		}
		cout << endl;
	}

}

void CPlansza::promocja()
{
	/////////////////////////////
	// Funkcja sprawdza czy ktorys pionek doszedl na koniec planszy
	// jesli tak, mozna dokonac zamiany na hetmana, wieze, gonca ub skoczka

	for (int i = 0; i < 8; i++)
	{
		if (pole[0][i] != NULL)
		{
			if (pole[0][i]->getGracz() == 1)
			{
				if (pole[0][i]->symbol() == 'P')
				{
					bool poprawne_dane = false;
					do
					{
						
						cout << "Mozna dokonac promocji. Wybierz na jaka figure chcesz zamienic:" << endl;
						cout << "1. Hetman" << endl;
						cout << "2. Wieza" << endl;
						cout << "3. Goniec" << endl;
						cout << "4. Skoczek" << endl;

						char wybor = _getch();
						switch (wybor)
						{
						case '1': delete pole[0][i]; poprawne_dane = true;
							pole[0][i] = new CHetman(1); break;
						case '2': delete pole[0][i]; poprawne_dane = true;
							pole[0][i] = new CWieza(1); break;
						case '3': delete pole[0][i]; poprawne_dane = true;
							pole[0][i] = new CGoniec(1); break;
						case '4': delete pole[0][i]; poprawne_dane = true;
							pole[0][i] = new CSkoczek(1); break;
						}
					} while (!poprawne_dane);
				}
			}
		}
	}

	for (int i = 0; i < 8; i++)
	{
		if (pole[7][i] != NULL)
		{
			if (pole[7][i]->getGracz() == 2)
			{
				if (pole[7][i]->symbol() == 'P')
				{
					bool poprawne_dane = false;
					do
					{
		
						cout << "Mozna dokonac promocji. Wybierz na jaka figure chcesz zamienic:" << endl;
						cout << "1. Hetman" << endl;
						cout << "2. Wieza" << endl;
						cout << "3. Goniec" << endl;
						cout << "4. Skoczek" << endl;

						char wybor1 = _getch();
						switch (wybor1)
						{
						case '1':
							delete pole[7][i];
							poprawne_dane = true;
							pole[7][i] = new CHetman(2); break;
						case '2':
							delete pole[7][i];
							poprawne_dane = true;
							pole[7][i] = new CWieza(2); break;
						case '3':
							delete pole[7][i];
							poprawne_dane = true;
							pole[7][i] = new CGoniec(2); break;
						case '4':
							delete pole[7][i];
							poprawne_dane = true;
							pole[7][i] = new CSkoczek(2); break;
						default:
							cout << "Zle podales wartosc. Sprobuj jeszcze raz wybrac." << endl;
						}
					} while (!poprawne_dane);
				}
			}
		}
	}
}

bool CPlansza::koniec_gry()
{
	////////////////////////////////////////
	// Funkcja sprawdza czy krol jest na szachownicy
	int zmienna = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (pole[i][j] != NULL)
			{
				if (pole[i][j]->symbol() == 'K')
				{
					zmienna++;
					if(zmienna==2)			// jesli na planszy nie ma dwoch kroli, konczymy gre
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}



////////////////////////////////
// Klasa CSzachy

void CSzachy::ruch_gracza(CFigura* temp_pole[8][8])
{
	bool poprawne_dane = false;
	int kolumnaX = 0, wierszX = 0;	// wspolrzedne figury ktora chcemy przesunac
	int kolumnaY = 0, wierszY = 0;	// wspolrzedne gdzie chcemy przemiescic figure

									///////////////////////////////////////
									// wybor koloru dla odroznienia figur graczy
	if (ruchGracza == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	}

	///////////////////////////////////////////////////////
	// Petla do wprowadzania wspolrzednych
	// i sprawdzania ich poprawnosci
	do
	{
		cout << "Gracz numer " << ruchGracza << endl;
		cout << "Wprowadz wsporzedne figury ktora chcesz przesunac. " << endl;
		cout << "Podaj wiersz: ";
		char wybor = _getch(); cout << wybor;
		cout << endl << "Podaj kolumne: ";
		cin >> kolumnaX;
		wierszX = int(wybor) - 96;

		// Sprawdzamy czy wybralismy figure
		if (temp_pole[wierszX - 1][kolumnaX - 1] == NULL)
		{
			cout << "Wybrane pole nie jest figura. " << endl;
			poprawne_dane = false; continue;
		}
		else
		{
			// warunek czy gracz wybral swoja figure
			if (temp_pole[wierszX - 1][kolumnaX - 1]->getGracz() != ruchGracza)
			{
				cout << "Wybrana figura nie nalezy do tego gracza. " << endl;
				poprawne_dane = false; continue;
			}
		}

		cout << "Gdzie chcesz przesunac figure. " << endl;
		cout << "Podaj wiersz: ";
		wybor = _getch(); cout << wybor;
		cout << endl << "Podaj kolumne: ";
		cin >> kolumnaY;
		wierszY = int(wybor) - 96;

		// warunek czy wspolrzedne sa w zakresie 1-8
		if (wierszX > 0 && wierszX < 9 && wierszY > 0 && wierszY < 9 && kolumnaY > 0 && kolumnaY < 9 && kolumnaX > 0 && kolumnaX < 9)
		{
			// sprawdzamy poprawnosc funkcji ruch()
			// czy dana figura moze sie na wskazane pole przemiescic (nie przekraczajac zakresu tej figury)
			if (temp_pole[wierszX - 1][kolumnaX - 1]->ruch(wierszX, kolumnaX, wierszY, kolumnaY, temp_pole))
			{
				// warunek czy na tym polu nie stoi inna figura
				if (temp_pole[wierszY - 1][kolumnaY - 1] == NULL)
				{
					poprawne_dane = true;
				}
				else
				{
					// warunek czy na tym polu jest figura tego samego gracza
					if (temp_pole[wierszX - 1][kolumnaX - 1]->getGracz() == temp_pole[wierszY - 1][kolumnaY - 1]->getGracz())
					{
						cout << "Nie mozesz sie na to pole przemiescic. Stoi tu juz figura." << endl;
						poprawne_dane = false; continue;
					}
					// warunek czy na tym polu jest figura przeciwnika
					// jezeli tak, wskaznik na figure przeciwnika przyjmuje NULL
					else if (temp_pole[wierszX - 1][kolumnaX - 1]->getGracz() != temp_pole[wierszY - 1][kolumnaY - 1]->getGracz())
					{
						temp_pole[wierszY - 1][kolumnaY - 1] = NULL;
						poprawne_dane = true;
						// po zbiciu figury odpowiedni gracz dostaje punkt
						if (ruchGracza == 1)
						{
							mojaPlansza.setWynikGracz1();
						}
						else if (ruchGracza == 2)
						{
							mojaPlansza.setWynikGracz2();
						}
					}
				}
			}
			else
			{
				cout << "Ta figura nie mozesz sie na to pole przemiescic." << endl;
				poprawne_dane = false; continue;
			}
		}
		else
		{
			cout << "Wprowadziles zle wspolrzedne. Sprobuj podac jeszcze raz w zakresie a-h oraz 1-8 " << endl;
		}


	} while (!poprawne_dane);

	CFigura* temp = temp_pole[wierszY - 1][kolumnaY - 1];
	temp_pole[wierszY - 1][kolumnaY - 1] = temp_pole[wierszX - 1][kolumnaX - 1];
	temp_pole[wierszX - 1][kolumnaX - 1] = NULL;

}


void CSzachy::start()
{
	mojaPlansza.wyswietl();
	cout << "Uproszczona gra w szachy" << endl;
	cout << "Poszczegolne figury poruszaja sie i bija tak jak w klasycznych szachach." << endl;
	cout << "Gra polega na podaniu wspolrzednych figury ktora chcemy przesunac," << endl;
	cout << "nastepnie wprowadzamy wspolrzedne pola na ktore chcemy je przesunac" << endl;
	cout << "jesli na tym polu znajduje sie figura przeciwnika zostanie ona zaatakowana." << endl;
	cout << "Gra uwzglednia tzw promocje, gdy pionek osiagnie osmy rzad to jest on promowany." << endl;
	cout << "Rozgrywka konczy sie gdy jeden z graczy osiagnie 15pkt (za kazda zbita figure przeciwnika" << endl;
	cout << "dostaje sie 1pkt) lub gdy po prostu pokona sie krola." << endl;
	cout << "Opis figur:" << endl;
	cout << "P - pionek" << endl;
	cout << "W - wieza" << endl;
	cout << "S - skoczek" << endl;
	cout << "K - krol" << endl;
	cout << "H - hetman" << endl;
	cout << "G - goniec" << endl;
	cout << endl;
	cout << "Nie ma roszady ani podwojnego ruchu pionka." << endl;
	cout << "Czas nie jest mierzony." << endl;
	cout << endl;
	cout <<"Wprowadz znak z klawiatury aby zaczac gre"<< endl;
	_getch();

	int i = 0;
	while (!mojaPlansza.koniec_gry())
	{
		ruchGracza = i % 2 + 1;
		mojaPlansza.wyswietl();
		mojaPlansza.promocja();
		mojaPlansza.wyswietl();
		ruch_gracza(mojaPlansza.pole);
		i++;
		mojaPlansza.wyswietl();
		cout << "KONIEC GRY!!!" << endl;
	}
}

