#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include "Data.h"
#include "FileManager.h"
#include "ArgManager.h"

const string path = "logs/";

int main(int argn, char** argv)
{
	Data* data = new Data();
	//FileManager* fileM;

	data->Ajouter("b", "a");

	data->Ajouter("c", "a");
	data->Ajouter("c", "a");

	data->Ajouter("b", "c");
	data->Ajouter("b", "c");

	cout << *data;

	bool e = false, t = false;
	int heure = 0;
	string line;

	ArgManager aM(argn,argv);
	Options chx = aM.getOptions();
	aM.getMessage(chx.etat);
	cout << chx.eOption << endl;
	cout << chx.gOption << endl;
	cout << chx.tOption << endl;
	cout << chx.hour << endl;
	cout << chx.logName << endl;
	cout << chx.graphName << endl;


	FileManager fileM(path +"test.log");
	getline(fileM,line);
	stringstream s(line);
	vector <string> v = fileM.Decouper(s);
	for(int i = 0; i<v.size();i++)
	{
		cout << v[i] << endl;
	}

	getline(fileM,line);
	s=stringstream(line);
	v=fileM.Decouper(s);
	for(int i = 0; i<v.size();i++)
	{
		cout << v[i] << endl;
	}

	delete data;
}