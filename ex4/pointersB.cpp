#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <cstdlib>

using namespace std;

int myFunc(int &x, int &y)
{
	return x*y;
}

int main(int argLength, char* argValues[])
{
	assert (argLength =2);
	cout << myFunc((int)atof(argValues[1]),(int)atof(argValues[2])) << endl;

	return 0;
}
