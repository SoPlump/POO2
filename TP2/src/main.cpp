#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
//#include "Data.h"
#include "FileManager.h"

int main(int argn, char** argv)
{
	bool e = false, t = false;
	int heure = 0;
	string path = "logs/";
	string line;

	//Data* data = new Data();
	
	FileManager fileM(path +"test");
	getline(fileM,line);
	stringstream s(line);
	vector <string> v = fileM.Decouper(s);
	for(int i = 0; i<v.size();i++)
	{
		cout << v[i] << endl;
	}


	if ( e )
	{
		if ( t )
		{
			//Data( e, heure );
		}
		else
		{
			//Data( e );
		}
	}
	else if ( t )
	{
		//Data( heure );
	}
	else
	{
	}
}