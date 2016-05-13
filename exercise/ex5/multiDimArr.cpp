#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 

const int height = 5;
const int width = 5;

void fillArray(double arr[][width], int height, int width) 
{
	for (int i=0; i < height; i++) 
	{
		for (int j = 0; j < width; ++j)
		{			
			arr[i][j] = rand() % 10;
		}
	}
	printf("%s\n", "Filling done");
}

void printArray(double arr[][width], int height, int width)
{
	// Printing introduction
	std::cout << "Printing array:" << std::endl;

	// Printing coulums
	std::cout << "i/j ";
	for (int i = 0; i < width; ++i)
	{
		std::cout << i << "   ";
	}
	std::cout << std::endl;

	// Printing data
	for (int i=0; i < height; i++) 
	{
		std::cout << i << "   ";
		for (int j = 0; j < width; ++j)
		{
			std::cout << arr[i][j] << "   ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main()
{
	std::cout << "Initialising random array" << std::endl;

	// seeding the RNG
	srand(time(NULL));

	// declaring the array
	double arr[height][width];

	std::cout << "Filling array" << std::endl;

	// calling the functions
	fillArray(arr, height, width);
	printArray(arr, height, width);

	return 0;
}