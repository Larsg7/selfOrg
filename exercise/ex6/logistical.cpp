#include <iostream>

using namespace std;

double getXplus (double r, double x)
{
	return r*x*(1.-x);
}

int main()
{
	double xn = 0.5;
	double r = 5;
	int nmax = 200;

	for (int i=1; i < nmax; i++)
	{
		xn = getXplus(r,xn);		
		cout << i << "     " << xn << endl;
	}

	return 0;
}
