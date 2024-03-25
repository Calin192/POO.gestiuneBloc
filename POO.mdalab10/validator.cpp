#include "validator.h"
#include <assert.h>
#include <sstream>

void LocatarValidator::validate(const Locatar& p) {
	vector<string> msgs;
	if (p.getAp() <= 0) msgs.push_back("Apartament negativ!!!");
	if (p.getNume().size() == 0) msgs.push_back("Nume invalid!!!");
	if (p.getSup() <= 0) msgs.push_back("Suprafata invalida!!!");
	if (p.getTip().size() == 0) msgs.push_back("Tip invalid!!!");
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}

void testeValidator() {
	LocatarValidator v;
	Locatar p{ 0,"",0,"" };
	try {
		v.validate(p);
	}
	catch (const ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		auto mesaj = sout.str();
		assert(mesaj.find("negativ") >= 0);
		assert(mesaj.find("vid") >= 0);
	}
}