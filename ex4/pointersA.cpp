#include <iostream>
#include <stdio.h>

using namespace std;


int main()
{
	int iArray[] = {5,3,5,2};
	double dArray[] = {4.56,2.7,3.8908};
	long double ldArray[] = {579.78,54467,45.3455251};

	int *ip;
	double *dp;
	long double *ldp;
	
	ip = iArray;
	dp = dArray;
	ldp = ldArray;

	for (int i = 0; i < 2; i++)
	{
		cout << "Address of int Array: " << ip << endl;
		cout << "Address of double Array: " << dp << endl;
		cout << "Address of long double Array: " << ldp << endl;
	
		cout << "Value of int Array: " << *ip << endl;
		cout << "Value of double array: " << *dp << endl;
		cout << "Value of long double Array: " << *ldp << endl;

		ip++;
		dp++;
		ldp++;
	}
}

