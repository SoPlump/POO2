#include <stdio.h>
#include <iostream>
#include "Interface.h"

using namespace std;

int main()
{
	//Interface* interface = new Interface();
	//interface->Menu();

	Interface* interface = Interface::GetInstance();
	interface->Menu();

	delete interface;

	return 0;
}

