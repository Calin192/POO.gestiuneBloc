#pragma once
#pragma once
#include "Locatar.h"

#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;

class LocatarRepo {
protected:vector<Locatar> all;
		 /*
		 metoda privata verifica daca exista deja p in repository
		 */
		 bool exist(const Locatar& p) const;

		 vector<Locatar> lista;
public:
	LocatarRepo() = default;
	//nu permitem copierea de obiecte
	LocatarRepo(const LocatarRepo& ot) = delete;

	virtual ~LocatarRepo() = default;
	/*
	Salvare pet
	arunca exceptie daca mai exista un animal cu acelasi tip si specie
	*/
	virtual void bloc(const Locatar& p);

	void Lista(const Locatar& p);
	/*
	Cauta
	arunca exceptie daca nu exista animal
	*/
	virtual const Locatar& find(int ap, string nume) const;

	virtual void stergeLocatarRepo(int poz);

	virtual void modificaLocatarRepo(const Locatar& p, int poz);
	/*
	returneaza toate animalele salvate
	*/
	virtual const vector<Locatar>& getAll() const noexcept;

	const vector<Locatar>& getNotificari() const noexcept;

	void golireNorificari();

	void randomNotificari(int nr);
};

class LocatarRepoException {
	string msg;
public:
	LocatarRepoException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const LocatarRepoException& ex);
};

ostream& operator<<(ostream& out, const LocatarRepoException& ex);

void testeAdauga();
void testeCauta();
void testeRepo();
