#include <iostream>
#include <stdio.h>
#include "Data.h"

int main(int argn, char** argv)
{
	Data* data = new Data();
	//FileManager* fileM;

	data->Ajouter("b", "a");
	data->AddNode("b", "a");

	data->Ajouter("c", "a");
	data->AddNode("c", "a");
	data->Ajouter("c", "a");
	data->AddNode("c", "a");

	data->Ajouter("b", "c");
	data->AddNode("b", "c");
	data->Ajouter("b", "c");
	data->AddNode("b", "c");

	cout << *data;

	delete data;
}