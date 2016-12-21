#pragma once
#include "Vaisseau.h"
#include <string>
using namespace std;

class nouveauVaisseau : Vaisseau {
private:
	string vaisseau;
public:
	nouveauVaisseau();
	void putNouveauVaisseau() const;
	void removeVaisseau() const;
};