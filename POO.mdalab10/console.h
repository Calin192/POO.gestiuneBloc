#pragma once
#pragma once
#include "Bloc.h"
#include "Locatar.h"
#include <map>
class ConsoleUI {
	Bloc& ctr;

	void adaugaUI();
	void stergeUI(int poz);
	void modificaUI();
	void tipareste(const vector<Locatar>& pets);
	void adaugaNotifiareUI();
	void tiparesteNotificare(const vector<Locatar>& locatari);
	void golireNotificariUI();
	void randomNotificareUI();
	void tiparesteFisier(const vector<Locatar>& locatari);
	void cerinta();
	void undo();
	void tiparesteFile(const vector<Locatar>& locatari);
public:
	ConsoleUI(Bloc& ctr) noexcept :ctr{ ctr } {
	}
	ConsoleUI(const ConsoleUI& ot) = delete;
	void start();
	void testeUI();
};