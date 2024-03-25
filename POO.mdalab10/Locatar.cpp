#include "Locatar.h"
#include <assert.h>

bool cmpAp(const Locatar& p1, const Locatar& p2) {
	return p1.getAp() < p2.getAp();
}

bool cmpNume(const Locatar& p1, const Locatar& p2) {
	return p1.getNume() < p2.getNume();
}

bool cmpSup(const Locatar& p1, const Locatar& p2) {
	return p1.getSup() < p2.getSup();
}

void testeDomain() {
	Locatar p1(1, "a", 1.0, "a");
	Locatar p2(2, "b", 2.0, "b");

	assert(cmpAp(p1, p2) == 1);
	assert(cmpAp(p2, p1) == 0);

	assert(cmpNume(p1, p2) == 1);
	assert(cmpNume(p2, p1) == 0);

	assert(cmpSup(p1, p2) == 1);
	assert(cmpSup(p2, p1) == 0);
}