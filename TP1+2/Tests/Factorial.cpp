/*
 * Factorial.cpp
 */

#include "Factorial.h"
#include "vector"
using namespace std;

int factorialRecurs(int n)
{
    if(n == 1)
        return 1;
	return n*factorialRecurs(n-1);
}

int factorialDinam(int n)
{
    int counter = 1;
    vector<int> result = {1};
    while(counter<=n){
        result.push_back(result.back()*counter);
        counter++;
    }
    return result.back();
}