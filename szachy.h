#ifndef _SZACHY_HPP
#define _SZACHY_HPP

#include<iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;

//////////////////////////////
// Klasa CFigura
// abstrakcyjna klasa, po ktorej dziedziczymy kolejen rodzaje figur szachowych

class CFigura {
	int gracz;			// zmienna identyfikujaca dwoch graczy
						// (do ktorego nalezy dana figura)
public:
	CFigura(int g) :gracz(g){}
	virtual ~CFigura(){}
	int getGracz() { return gracz; }
	virtual bool ruch(int, int, int, int, CFigura* temp_p[8][8]) = 0;
	virtual char symbol() = 0;		//kazda figura szachowa bedzie miec swoj znak
};


//////////////////////////////////////////
// Klasa CPionek, pochodna po klasie CFigura

class CPionek : public CFigura {
public:
	CPionek(int g):CFigura(g){}
	virtual ~CPionek(){}
	virtual bool ruch(int, int, int, int, CFigura* temp_p[8][8]);
	virtual char symbol() { return 'P'; }
};

//////////////////////////////////////////
// Klasa CWieza, pochodna po klasie CFigura

class CWieza : public CFigura {
public:
	CWieza(int g) :CFigura(g){}
	virtual ~CWieza(){}
	virtual bool ruch(int, int, int, int, CFigura* temp_p[8][8]);
	virtual char symbol() { return 'W'; }
};

//////////////////////////////////////////
// Klasa CSkoczek, pochodna po klasie CFigura

class CSkoczek : public CFigura {
public:
	CSkoczek(int g) :CFigura(g){}
	virtual ~CSkoczek(){}
	virtual bool ruch(int, int, int, int, CFigura* temp_p[8][8]);
	virtual char symbol() { return 'S'; }
};

//////////////////////////////////////////
// Klasa CKrol, pochodna po klasie CFigura

class CKrol : public CFigura {
public:
	CKrol(int g) :CFigura(g) {}
	virtual ~CKrol() {}
	virtual bool ruch(int, int, int, int, CFigura* temp_p[8][8]);
	virtual char symbol() { return 'K'; }
};

//////////////////////////////////////////
// Klasa CHetman, pochodna po klasie CFigura

class CHetman : public CFigura {
public:
	CHetman(int g) :CFigura(g) {}
	virtual ~CHetman() {}
	virtual bool ruch(int, int, int, int, CFigura* temp_p[8][8]);
	virtual char symbol() { return 'H'; }
};

//////////////////////////////////////////
// Klasa CGoniec, pochodna po klasie CFigura

class CGoniec : public CFigura {
public:
	CGoniec(int g) :CFigura(g) {}
	virtual ~CGoniec() {}
	virtual bool ruch(int, int, int, int, CFigura* temp_p[8][8]);
	virtual char symbol() { return 'G'; }
};


////////////////////////////////
// Klasa CPlansza

class CPlansza {
private:
	// zmienna pomocnicza do wyswietlania planszy
	char wiersz[10] = { 'A','B','C','D','E','F','G','H','I','J' };
	int wynikGracz1;
	int wynikGracz2;
public:
	CFigura* pole[8][8];		//tablica
	int getWynikGracz1() { return wynikGracz1; }
	int getWynikGracz2() { return wynikGracz2; }
	void setWynikGracz1();
	void setWynikGracz2();
	CPlansza() :wynikGracz1(0), wynikGracz2(0)
	{
		for (int i = 0; i < 8; i++)		//wiersze
		{
			for (int j = 0; j < 8; j++)	//kolumny
			{
				pole[i][j] = NULL;
			}
		}
		
		//ustawienie pionkow gracza nr1
		for (int i = 0; i < 8; i++)
		{
			pole[6][i] = new CPionek(1);
		}
		pole[7][0] = new CWieza(1);
		pole[7][1] = new CSkoczek(1);
		pole[7][2] = new CGoniec(1);
		pole[7][3] = new CHetman(1);
		pole[7][4] = new CKrol(1);
		pole[7][5] = new CGoniec(1);
		pole[7][6] = new CSkoczek(1);
		pole[7][7] = new CWieza(1);
		
		//ustawienie pionkow gracza nr2
		for (int i = 0; i < 8; i++)
		{
			pole[1][i] = new CPionek(2);
		}
		pole[0][0] = new CWieza(2);
		pole[0][1] = new CSkoczek(2);
		pole[0][2] = new CGoniec(2);
		pole[0][3] = new CHetman(2);
		pole[0][4] = new CKrol(2);
		pole[0][5] = new CGoniec(2);
		pole[0][6] = new CSkoczek(2);
		pole[0][7] = new CWieza(2);
		
	}
	~CPlansza() {
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				delete pole[i][j];
				pole[i][j] = NULL;
			}
		}
	}

	void wyswietl();
	void promocja();
	bool koniec_gry();
};


/////////////////////////////////
// Klasa CSzachy

class CSzachy {
	CPlansza mojaPlansza;
	int ruchGracza;		// zmienna pomocnicza przy okresleniu ktory z graczy ma ruch
public:
	CSzachy():ruchGracza(1){}
	~CSzachy() {}
	void start();
	void ruch_gracza(CFigura* temp_pole[8][8]);
	
};

#endif // ! SZACHY_HPP
