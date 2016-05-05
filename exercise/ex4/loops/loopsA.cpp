#include <iostream>
#include <stdio.h>

using namespace std;

double factorial(double n)
{
        double result = 1;
        for(int i = 1; i <= n; i++)
        {
                result *= i;
        }
        return result;
}

int main()
{       
        long double upperLimit = 2000000000000000000000;
        double largestFactorial = 0;
        int number = 0;

	cout << "The upper Limit is: " << upperLimit << endl << endl;

        while(largestFactorial < upperLimit)
        {
		number++;
                largestFactorial = factorial(number);
                cout << "Current largest factorial: " << largestFactorial;
                cout << " with number: " << number << endl;
        }
        return 0;
}       
