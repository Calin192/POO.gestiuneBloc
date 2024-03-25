#pragma once
#pragma once
#pragma once

#include "Locatar.h"
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "validator.h"
#include "undo.h"
#include "Observer.h"

using std::vector;
using std::function;
using std::unique_ptr;

class Bloc : public Observable{
	LocatarRepo& rep;
	LocatarValidator& val;

	std::vector<unique_ptr<ActiuneUndo>> undoActions;
	/*
	 Functie de sortare generala
	 maiMareF - functie care compara 2 Pet, verifica daca are loc relatia mai mare
			  - poate fi orice functe (in afara clasei) care respecta signatura (returneaza bool are 2 parametrii Pet)
			  - poate fi functie lambda (care nu capteaza nimic in capture list)
	 returneaza o lista sortata dupa criteriu dat ca paramatru
	*/
	vector<Locatar> generalSort(bool (*maiMicF)(const Locatar&, const Locatar&));
	/*
	Functie generala de filtrare
	fct - poate fi o functie
	fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
	returneaza doar animalele care trec de filtru (fct(pet)==true)
	*/
	vector<Locatar> filtreaza(function<bool(const Locatar&)>fct);
public:
	Bloc(LocatarRepo& rep, LocatarValidator& val) noexcept :rep{ rep }, val{ val } {}
	//nu permitem copierea de obiecte PetStore
	Bloc(const Bloc& ot) = delete;
	/*
	 returneaza toate animalele in ordinea in care au fost adaugate
	*/
	const vector<Locatar>& getAll() noexcept {
		return rep.getAll();
	}

	const vector<Locatar>& getNotificari() noexcept {
		return rep.getNotificari();
	}

	void golesteNotificari();

	void randomNotificari(int nr);
	/*
	Adauga un nou pet
	arunca exceptie daca: nu se poate salva, nu este valid
	*/
	void addLocatar(int ap, const string& nume, float sup, const string& tip);

	void addNotificare(int ap, string nume);
	/*
	Sorteaza dupa nume
	*/
	vector<Locatar> sortByNume();

	/*
	Sorteaza dupa sup
	*/
	vector<Locatar> sortBySup();

	/*
	Sorteaza dupa tip+supragata
	*/
	vector<Locatar> sortByTipSuprafata();

	/*
	filtrare tip. atat
	*/
	//vector<Locatar> filtrareTip();

	/*
	filtrare suprafata. atat
	*/
	vector<Locatar> filtrareSup(float sup);

	vector<Locatar> filtrareTip(const string& tip);

	void stergeLocatar(int poz);

	void ModificaLocatar(int ap, const string& nume, float sup, const string& tip, int poz);

	void testAdaugaCtr();

	void testeFiltrare();

	void testSortare();

	void testNotificari();

	void cata_suprafata(std::map<std::string, float>& dictionar);

	void undo();
};

void testCtr();