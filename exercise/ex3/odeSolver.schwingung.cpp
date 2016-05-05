/*
 *	The euler method:
 *	Consider a given initial value problem y'=f(t,y(t), y(0)=y0.
 *	The Euler Method is: y(n+1) = y(n) + h*f(t(n),y(n)), where h is the step size.
 *	The step size is the change in t.
 *	The solution is given by the values of y plotted against t.
 *
 *
 */

#include <iostream>
#include <stdio.h>

using namespace std;

// declare variables
void doDerive(double t, double y[], double derive[], int sizeOfODE);
double updateF(double y[]);
void euler(double t, double y[], double derive[], double f, double h);

int main()
{
	// declaring constants
	const double maxTime = 50;
	const double h = 0.001;		// step size

	//declaring variables
	double t = 0;			// starting time

	// declaring ODE
	
	/*
	 *	here we consider the ode y=y', y(0) = 0, y'(0) = 1
	 */

	int sizeOfODE = 2;		// number of arguments of y
	
	double y[] = {0,1};		// starting value for {y,y'}
	double f;
	f = updateF(y);

	double derive[sizeOfODE];	// derive = {y',f}
	
	// first output
	printf("%15s,%15s,%15s", "Time","y","y\'");

	while (t < maxTime)
	{
		// output values
		printf("%10.5f\t%10.5f\t%10.5f \n", t, y[0], y[1]);

		// actual computing
		euler(t, y, derive, f, h);
		doDerive(t,y,derive, sizeOfODE);
			
		// increase time by step size
		t += h;
	}	

	return 0;
}

void doDerive(double t, double y[], double derive[], int sizeOfODE)
{
	// change y according to derive
	for (int i = 0; i < sizeOfODE; i++)
	{
		y[i] += derive[i];
	}

}

double updateF(double y[])
{
	return -y[0];
}

void euler(double t, double y[], double derive[], double f, double h)
{
	f = updateF(y);
	derive[0] = h * y[1];
       	derive[1] = h * f;
}
