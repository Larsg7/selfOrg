#include <iostream>
#include <time.h>

using namespace std;

float floatGeoRow (float k)
{
    float result = 0;

    for (int i = 1; i < k; ++i) {
        result += 1 / i;
    }

    return result;
}

double doubleGeoRow (float k)
{
    double result = 0;

    for (int i = 1; i < k; ++i) {
        result += 1 / i;
    }

    return result;
}

long double longDoubleGeoRow (double k)
{
    long double result = 0;

    for (int i = 1; i < k; ++i) {
        result += 1 / i;
    }

    return result;
}

int main()
{
    double k = 900000000;


    double end;
    float result;
    double start;
/*    start = time(NULL);
    result = floatGeoRow(k);
    end = time(NULL);
    cout << "It took " << "floatGeoRow(" << k << ") " << end-start << " seconds to finish, with result " << result << endl;

    start = time(NULL);
    double dresult = doubleGeoRow(k);
    end = time(NULL);
    cout << "It took " << "doubleGeoRow(" << k << ") " << end-start << " seconds to finish, with result " << dresult << endl;
*/
    start = time(NULL);
    long double ldresult = longDoubleGeoRow(k);
    end = time(NULL);
    cout << "It took " << "longDoubleGeoRow(" << k << ") " << end-start << " seconds to finish, with result " << ldresult << endl;

    return 0;
}