#include "LocatarRepo.h"
#include <assert.h>
#include <iostream>
#include <sstream>
#include <random>
#include <chrono>
#include <algorithm>

using std::ostream;
using std::stringstream;

void LocatarRepo::bloc(const Locatar& p)
{
	if (exist(p)) {
		throw LocatarRepoException("Exista deja locatarul: " + p.getNume() + " la numarul: " + std::to_string(p.getAp()));
	}
	all.push_back(p);
}
void LocatarRepo::Lista(const Locatar& p)
{
	lista.push_back(p);
}

void LocatarRepo::golireNorificari() {
	lista.clear();
}

void LocatarRepo::randomNotificari(int nr) {
	vector<Locatar> alz = all;
	std::shuffle(alz.begin(), alz.end(), std::default_random_engine(std::random_device{}()));
	while (lista.size() < nr && !alz.empty()) {
		lista.push_back(alz.back());
		alz.pop_back();
	}
}

bool LocatarRepo::exist(const Locatar& p) const {
	try {
		find(p.getAp(), p.getNume());
		return true;
	}
	catch (LocatarRepoException&) {
		return false;
	}
}
/*
Cauta
arunca exceptie daca nu exista animal
*/
const Locatar& LocatarRepo::find(int ap, string nume) const {
	for (const auto& p : all) {
		if (p.getAp() == ap && p.getNume() == nume) {
			return p;
		}
	}
	//daca nu exista arunc o exceptie
	throw LocatarRepoException("Nu exista locatar sub numele de: " + nume + " la numarul: " + std::to_string(ap));
}


/*
returneaza toate animalele salvate
*/
const vector<Locatar>& LocatarRepo::getAll() const noexcept {
	return all;
}

const vector<Locatar>& LocatarRepo::getNotificari() const noexcept {
	return lista;
}

ostream& operator<<(ostream& out, const LocatarRepoException& ex) {
	out << ex.msg;
	return out;
}

void LocatarRepo::stergeLocatarRepo(int poz) {
	if (all.size() <= poz || poz < 0)
		throw LocatarRepoException("Indice Invalid\n");
	all.erase(all.begin() + poz);
}

void LocatarRepo::modificaLocatarRepo(const Locatar& p, int poz) {
	if (all.size() <= poz || poz < 0)
		throw LocatarRepoException("Indice Invalid\n");
	all[poz] = p;
}



void testeAdauga() {
	LocatarRepo rep;
	rep.bloc(Locatar{ 1,"a",1.0,"a" });
	assert(rep.getAll().size() == 1);
	assert(rep.find(1, "a").getNume() == "a");

	rep.bloc(Locatar{ 2,"b",2.0,"b" });
	assert(rep.getAll().size() == 2);

	//nu pot adauga 2 cu nume si ap la fel
	try {
		rep.bloc(Locatar{ 1,"a",1.0,"a" }); assert(false);
	}
	catch (const LocatarRepoException&) {
		assert(true);
	}

	//cauta inexistent
	try {
		rep.find(3, "c"); assert(false);
	}
	catch (const LocatarRepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}

	//modifica
	Locatar p3(4, "c", 4.0, "c");
	try {
		rep.modificaLocatarRepo(p3, -1); assert(false);
	}
	catch (const LocatarRepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("Indice invalid\n") >= 0);
	}

	rep.modificaLocatarRepo(p3, 0);
	assert(p3.getAp() == 4);

	//sterge
	try {
		rep.stergeLocatarRepo(-1); assert(false);
	}
	catch (const LocatarRepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("Indice invalid\n") >= 0);
	}

	rep.stergeLocatarRepo(0);

}

void testeCauta() {
	LocatarRepo rep;
	rep.bloc(Locatar{ 1,"a",1.0,"a" });
	rep.bloc(Locatar{ 2,"b",2.0,"b" });

	auto p = rep.find(1, "a");
	assert(p.getNume() == "a");
	assert(p.getAp() == 1);

	//arunca exceptie daca nu gaseste
	try {
		rep.find(1, "b"); assert(false);
	}
	catch (LocatarRepoException&) {
		assert(true);
	}
}

void testeRepo() {
	testeAdauga();
	testeCauta();
}