#include <iostream>      // standard IO
#include <stdio.h>       // for printf
#include <cstdlib>       // for atof
#include <math.h>        // for the math
#include <time.h>        // ('clock()' measures time in nanoseconds)
     
using namespace std;
     
const long int oneGigaByte = 1073741824;   // one Giga Byte

/* **************************************** */
/* *****      time in seconds	    ******* */
/* **************************************** */

double timeInSeconds()
{
const double oneSecond = 1.0 / CLOCKS_PER_SEC;
static long int lastTime = clock();
long int actual_time = clock();
long int elapsed_time = actual_time - lastTime;
lastTime = actual_time;
return elapsed_time * oneSecond;     // time passed since last call
}    

/* **************************************** */
/* *****	    main	    ******* */
/* **************************************** */
     
int main(int argLength, char* argValues[])  // parsing command line arguments
{
 if (argLength==1)
   {
   cout << "please run with a double argument (memory in GB)\n";
   return 0;
   }
 long int dynamicArraySize = (long)(atof(argValues[1])*oneGigaByte*1.0/sizeof(int));  
 timeInSeconds();			    // initialized

 int onePerCent = (int)(dynamicArraySize/100);
//
 int *aa = new int[dynamicArraySize];
/*
 for (int i=0;i<dynamicArraySize;i++)
 for (long int i=0;i<dynamicArraySize;i++)
*/
 for (size_t i=0;i<dynamicArraySize;i++)
   {
   aa[i] = i;
   if ((i%onePerCent)==0)
     printf("(main) %5.2f GB indices allocated, %5.2f seconds used\n",
	    i*1.0/oneGigaByte, timeInSeconds());
   }
//
 printf("\n");
 printf("(main) starting infinite loop\n\n");
//
 while (true)			// infinite loop
  double a = log(34545.3454);
//
 return 1;
}
