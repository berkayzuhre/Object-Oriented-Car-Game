// GuzelProjeG10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Manager.h"

using namespace std;


int main()
{
	Manager m;


	m.ConstructConsole(160, 100, 6, 6);

	m.Start();

	



    return 0;
}

