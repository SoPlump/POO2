#include <stdio.h>
#include <iostream>
#include "interface.h"

using namespace std;

int main()
{
	//Interface* interface = new Interface();
	//interface->Menu();

	Interface* interface = Interface::GetInstance();
	interface->Menu();

	delete interface;

	/*Catalogue* catalogue = new Catalogue();
	catalogue->Interface();

	delete catalogue;*/

	return 0;
}

