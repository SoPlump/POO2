#include <stdio.h>
#include <iostream>
#include "catalogue.h"
#include "trajet.h"
#include "trajetsimple.h"
#include "trajetcompose.h"

using namespace std;

int main()
{
	Catalogue* catalogue = new Catalogue();
	catalogue->Interface();

	delete catalogue;

	return 0;
}

