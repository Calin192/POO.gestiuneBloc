#pragma once
#pragma once
#include "locatar.h"
#include "locatarRepo.h"
class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	//destructorul e virtual pentru a ne asigura ca daca dau delete se apeleaza destructorul din clasa care trebuie
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Locatar locatarAdaugat;
	LocatarRepo& rep;
public:
	UndoAdauga(LocatarRepo& rep, const  Locatar& p) :rep{ rep }, locatarAdaugat{ p } {}
	void doUndo() override {
		int x = 0, poz;
		for (auto i : rep.getAll()) {
			if (i.getNume() == locatarAdaugat.getNume() && i.getAp() == locatarAdaugat.getAp())
				poz = x;
			x++;
		}
		rep.stergeLocatarRepo(poz);
	}
};

class UndoSterge : public ActiuneUndo {
	Locatar locatarSters;
	LocatarRepo& rep;
public:
	UndoSterge(LocatarRepo& rep, const  Locatar& p) :rep{ rep }, locatarSters{ p } {}
	void doUndo() override {
		rep.bloc(locatarSters);
	}
};

class UndoModifica : public ActiuneUndo {
	Locatar locatarModificat;
	LocatarRepo& rep;
	int poz;
public:
	UndoModifica(LocatarRepo& rep, const Locatar& p, int poz) : rep{ rep }, locatarModificat{ p }, poz{ poz } {}
	void doUndo() override {
		rep.modificaLocatarRepo(locatarModificat, poz);
	}
};