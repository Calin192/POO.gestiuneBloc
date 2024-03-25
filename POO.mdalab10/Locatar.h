#pragma once
#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Locatar {
	int ap;
	std::string nume;
	float sup;
	std::string tip;
public:
	Locatar(int a, const string n, float s, const string t) :ap{ a }, nume{ n }, sup{ s }, tip{ t } {}

	Locatar(const Locatar& ot) :ap{ ot.ap }, nume{ ot.nume }, sup{ ot.sup }, tip{ ot.tip } {
		//cout << "!!!!!!!!!!!!!!!!!!!!\n";
	}
	Locatar() {
	}
	int getAp() const noexcept {
		return ap;
	}
	string getNume() const {
		return nume;
	}
	float getSup() const noexcept {
		return sup;
	}
	string getTip() const {
		return tip;
	}
	void setAp(int newAp) {
		ap = newAp;
	}
	void setNume(const std::string& newNume) {
		nume = newNume;
	}
	void setSup(float newSup) {
		sup = newSup;
	}
	void setTip(const std::string& newTip) {
		tip = newTip;
	}
};

bool cmpAp(const Locatar& p1, const Locatar& p2);
bool cmpNume(const Locatar& p1, const Locatar& p2);
bool cmpSup(const Locatar& p1, const Locatar& p2);

void testeDomain();