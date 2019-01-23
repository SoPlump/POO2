#include <iostream>
#include <stdio.h>
#include "Data.h"

int main(int argn, char** argv)
{
	bool e = false, t = false;
	int heure = 0;

	Data* data = new Data();
	FileManager* fileM = new FileManager();

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