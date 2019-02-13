#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include "Data.h"
#include "ArgManager.h"

const string path = "logs/";

int main(int argn, char** argv)
{
	// Verification des arguments
	ArgManager aM(argn,argv);
	Options chx = aM.getOptions();
	aM.getMessage(chx.etat);

	// Demande de traitement
	if ((aM.goodFile(chx.logName)) && (chx.etat==Status::Good))
	{
		Data* data = new Data(chx);
		data->Traiter();
		
		//cout << *data;

		delete data;
	}
}