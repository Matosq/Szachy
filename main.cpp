#include<iostream>
#include"szachy.h"
using namespace std;

/*
	Uproszczona gra w szachy
	Poszczegolne figury poruszaja sie i bija tak jak w klasycznych szachach.
	Gra polega na podaniu wspolrzednych figury ktora chcemy przesunac,
	nastepnie wprowadzamy wspolrzedne pola na ktore chcemy je przesunac
	jesli na tym polu znajduje sie figura przeciwnika zostanie ona zaatakowana.
	Gra uwzglednia tzw promocje, gdy pionek osiagnie osmy rzad to jest on promowany.
	Rozgrywka konczy sie gdy jeden z graczy osiagnie 15pkt (za kazda zbita figure przeciwnika
	dostaje sie 1pkt) lub gdy po prostu pokona sie krola.
	Opis figur:
	P - pionek
	W - wieza
	S - skoczek
	K - krol
	H - hetman
	G - goniec

	Nie ma roszady ani podwojnego ruchu pionka.
	Czas nie jest mierzony.
*/

int main()
{
	CSzachy nowa_gra;
	nowa_gra.start();

	system("pause");
	return 0;
}