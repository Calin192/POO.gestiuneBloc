#include "Bloc.h"
#include <functional>
#include <algorithm>
#include <assert.h>


vector<Locatar> Bloc::generalSort(bool(*maiMicF)(const Locatar&, const Locatar&)) {
	vector<Locatar> v{ rep.getAll() };
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (!maiMicF(v[i], v[j])) { Locatar aux = v[i]; v[i] = v[j]; v[j] = aux; }
		}
	}
	return v;
}
/*
Adauga un nou locatar
arunca exceptie daca: nu se poate salva, nu este valid
*/
void Bloc::addLocatar(int ap, const string& nume, float sup, const string& tip) {
	Locatar p{ ap,nume,sup,tip };
	val.validate(p);
	rep.bloc(p);
	undoActions.push_back(std::make_unique<UndoAdauga>(rep, p));
}


void Bloc::stergeLocatar(int poz) {
	int x = 0;
	Locatar p;
	for (auto i : getAll()) {
		if (x == poz) {
			p.setAp(i.getAp());
			p.setNume(i.getNume());
			p.setSup(i.getSup());
			p.setTip(i.getTip());
		}
		x++;
	}
	rep.stergeLocatarRepo(poz);
	undoActions.push_back(std::make_unique<UndoSterge>(rep, p));
}


void Bloc::ModificaLocatar(int ap, const string& nume, float sup, const string& tip, int poz) {
	int x = 0;
	Locatar b;
	for (auto i : getAll()) {
		if (x == poz) {
			b.setAp(i.getAp());
			b.setNume(i.getNume());
			b.setSup(i.getSup());
			b.setTip(i.getTip());
		}
		x++;
	}
	undoActions.push_back(std::make_unique<UndoModifica>(rep, b, poz));
	Locatar p{ ap,nume,sup,tip };
	rep.modificaLocatarRepo(p, poz);
}

void Bloc::undo() {
	if (undoActions.empty()) {
		throw LocatarRepoException{ "Nu mai exista operatii" };
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

void Bloc::addNotificare(int ap, string nume) {
	try {
		Locatar p = this->rep.find(ap, nume);
		this->rep.Lista(p);
	}
	catch (LocatarRepoException&) {
		return;
	}
	notify();
}

void Bloc::golesteNotificari() {
	this->rep.golireNorificari();
	notify();
}


void Bloc::randomNotificari(int nr) {
	this->rep.randomNotificari(nr);
	notify();
}
/*
Sorteaza dupa nume
*/
vector<Locatar> Bloc::sortByNume() {
	auto copyAll = rep.getAll();
	std::sort(copyAll.begin(), copyAll.end(), cmpNume);
	return copyAll;
}

/*
Sorteaza dupa suprafata
*/
vector<Locatar> Bloc::sortBySup() {
	return generalSort(cmpSup);
}

/*
Sorteaza dupa tip+supragata
*/
vector<Locatar> Bloc::sortByTipSuprafata() {
	return generalSort([](const Locatar& p1, const Locatar& p2) {
		if (p1.getTip() == p2.getTip()) {
			return p1.getSup() < p2.getSup();
		}
		return p1.getTip() < p2.getTip();
		});
}

vector<Locatar> Bloc::filtreaza(function<bool(const Locatar&)> fct) {
	vector<Locatar> rez;
	for (const auto& locatar : rep.getAll()) {
		if (fct(locatar)) {
			rez.push_back(locatar);
		}
	}
	return rez;
}

vector<Locatar> Bloc::filtrareSup(float sup) {
	return filtreaza([=](const Locatar& p) {
		return p.getSup() == sup;
		});
}

vector<Locatar> Bloc::filtrareTip(const string& tip) {
	return filtreaza([=](const Locatar& p) {
		return p.getTip() == tip;
		});
}



void Bloc::cata_suprafata(std::map<std::string, float>& dictionar) {
	LocatarRepo repo;
	for (auto i : getNotificari()) {
		dictionar[i.getNume()] = 0;
		//cout << dictionar[i.getNume()] << ' ';
	}
	for (auto i : getNotificari()) {
		dictionar[i.getNume()] += i.getSup();
		//cout << dictionar[i.getNume()] << '\n';
	}
}

void testAdaugaCtr() {
	LocatarRepo rep;
	LocatarValidator val;
	Bloc ctr{ rep,val };
	ctr.addLocatar(1, "a", 1.0, "a");
	assert(ctr.getAll().size() == 1);

	//adaug ceva invalid
	try {
		ctr.addLocatar(0, "", 0, ""); assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}
	//incerc sa adaug ceva ce exista deja
	try {
		ctr.addLocatar(1, "a", 1.0, "a"); assert(false);
	}
	catch (LocatarRepoException&) {
		assert(true);
	}

	ctr.ModificaLocatar(2, "b", 2.0, "a", 0);
}

void testeFiltrare() {
	LocatarRepo rep;
	LocatarValidator val;
	Bloc ctr{ rep,val };
	ctr.addLocatar(1, "a", 1.0, "a");
	ctr.addLocatar(2, "b", 2.0, "b");
	ctr.addLocatar(3, "a", 3.0, "b");
	assert(ctr.filtrareSup(2).size() == 1);
	assert(ctr.filtrareSup(3).size() == 1);
	assert(ctr.filtrareTip("a").size() == 1);
	assert(ctr.filtrareTip("b").size() == 2);
	assert(ctr.filtrareTip("d").size() == 0);
}

void testSortare() {
	LocatarRepo rep;
	LocatarValidator val;
	Bloc ctr{ rep,val };
	ctr.addLocatar(1, "a", 1.0, "a");
	ctr.addLocatar(2, "b", 2.0, "b");
	ctr.addLocatar(3, "a", 3.0, "b");


	auto firstP = ctr.sortByNume()[0];
	assert(firstP.getNume() == "a");

	firstP = ctr.sortBySup()[0];
	assert(firstP.getSup() == 1.0);

	firstP = ctr.sortByTipSuprafata()[0];
	assert(firstP.getNume() == "a");

	ctr.stergeLocatar(0);
}

void testNotificari() {
	LocatarRepo rep;
	LocatarValidator val;
	Bloc ctr{ rep,val };
	ctr.addLocatar(1, "a", 1.0, "a");

	ctr.addNotificare(1, "a");

	assert(ctr.getNotificari().size() == 1);


	ctr.addNotificare(2, "b");

	assert(ctr.getNotificari().size() == 1);

	ctr.golesteNotificari();

	assert(ctr.getNotificari().size() == 0);

	ctr.addNotificare(1, "a");

	ctr.randomNotificari(1);

	assert(ctr.getNotificari().size() == 1);
}

void testCtr() {
	testAdaugaCtr();
	testeFiltrare();
	testSortare();
	testNotificari();
}