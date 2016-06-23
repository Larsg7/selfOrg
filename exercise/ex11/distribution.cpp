#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <limits.h>
#include <map>

double expDist(double t, double lambda) {
	/*
	 * p(x) = lambda*exp(-lambda*x)
	 * => F(x) = -exp(-lambda*x) + 1
	 * => x = -ln(1-t)/lambda
	 */

	return - log(1- t) / lambda;
}

double powerDist(double t, double lambda) {
	/*
	 * p(x) = (lambda -1)*x^(-lambda)
	 * => F(x) = -x^(1-lambda) + 1
	 * => x = (1-t)^(1/(1-lambda))
	 */

	return pow((1-t),(1/(1-lambda))); 
}

int main() {

	const double lambda = 2;
	const int points = 100000;

	std::ofstream fileExp;
	std::ofstream filePow;
	fileExp.open("data-exponential");
	filePow.open("data-power");

	srand(time(NULL));

	std::cout << "Calculating histogram" << std::endl;

	std::map<int,int> expHist;
	std::map<int,int> powHist;

	for (int i = 0; i < points; ++i)
	{
		double t = (double)rand() / INT_MAX;
		double exp = (int)expDist(t, lambda);
		double pow = (int)powerDist(t, lambda);

		expHist[exp] += 1;
		powHist[pow] += 1;

	}

	std::cout << "Writing into files" << std::endl;

	for (int i = 0; i < expHist.size(); ++i)
	{
		fileExp << i << "\t" << expHist[i] << std::endl;
	}

	for (int i = 0; i < powHist.size(); ++i)
	{
		filePow << i << "\t" << powHist[i] << std::endl;
	}

	filePow.close();
	fileExp.close();
}