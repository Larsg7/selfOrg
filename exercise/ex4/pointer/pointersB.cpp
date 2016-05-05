#include <iostream>
#include <stdio.h>

using namespace std;

int myFunc(int &x, int &y)
{
	return x*y;
}

int main(int argLength, char* argValues[])
{
	int a = 3;
	int b = 4;
	cout << myFunc(a,b) << endl;

	return 0;
}
