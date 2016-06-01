/*
 *	The euler method:
 *	Consider a given initial value problem y'=f(t,y(t)), y(0)=y0.
 *	The Euler Method is: y(n+1) = y(n) + h*f(t(n),y(n)), where h is the step size.
 *	The step size is the change in t.
 *	The solution is given by the values of y plotted against t.
 */

#include <iostream>
#include <math.h>

using namespace std;

const double o = 10.;
const double b = 8. / 3.;
const double r = 181.1;         // control parameter

void doDerive(double t, double y[], double derive[], int sizeOfODE);
void updateF(double f[], double y[]);
void euler(double t, double y[], double derive[], double f[], double h, int sizeOfODE);
double dist(double y1[], double y2[], int sizeOfODE);

int main()
{
	// declaring constants
	const double maxTime = 200;
	const double h = 0.001;			// step size

	//declaring variables
	double t = 0;					// starting time


	// declaring ODE

	int sizeOfODE = 3;				// number of arguments of y

	//double y[] = {-.1,-5,.1};		// starting value for {x,y,z}
	double y[] = { -(double)sqrt(b*(r-1.)) - 0.00001, -(double)sqrt(b*(r-1)) + 0.00001, r-1 - 0.00001 };
	double f[sizeOfODE];

	updateF(f, y);

	double derive[sizeOfODE];		// derivation of y[]

	// first output
	printf("# %10s,%10s,%10s,%10s,%10s\n", "Time","x","y","z","dist");

	while (t <= maxTime)
	{
		double attractor[] = { (double)sqrt(b*(r-1.)), (double)sqrt(b*(r-1)), r-1 }; // position of the attractor

		// output values
		//printf("%10.5f\t%10.5f\t%10.5f\t%10.5f \n", t, y[0], y[1], y[2]);
		printf("%10.5f\t%10.5f\t%10.5f\t%10.5f\t%10.5f \n", t, y[0], y[1], y[2], dist(attractor, y, sizeOfODE));


		// actual computing
		euler(t, y, derive, f, h, sizeOfODE);
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

void updateF(double f[], double y[]) {


	f[0] = (o * (y[1] - y[0]));
	f[1] = (y[0] * (r - y[2]) - y[1]);
	f[2] = (y[0] * y[1] - b * y[2]);
}

void euler(double t, double y[], double derive[], double f[], double h, int sizeOfODE)
{
	updateF(f, y);
	// derive[0] = h * y[1];
	// derive[1] = h * f;
	for (int i = 0; i <= sizeOfODE; ++i)
	{
		derive[i] = h * f[i];
	}
}



double dist(double y1[], double y2[], int sizeOfODE) {
	double result = 0;
	for (int i = 0; i < sizeOfODE; ++i) {
		result += (y1[i] - y2[i]) * (y1[i] - y2[i]);
	}
	return (double)sqrt(result);
}