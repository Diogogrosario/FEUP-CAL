/*
 * Partioning.cpp
 */

#include "Partitioning.h"
#include <vector>

using namespace std;

int s_recursive(int n,int k)
{
   if( k == n || k == 1){
       return 1;
   }
   return (s_recursive(n-1,k-1)+k*s_recursive(n-1,k));
}

int s_dynamic(int n,int k)
{
    vector <int> values;
    for(int i = 0;i<n-k;i++){
        for(int j = 1;j<k;j++){
            values.at(j) = (j+1)*values.at(j)+values.at(j-1);
        }
    }
    return values.at(k-1);

}


int b_recursive(int n)
{
    int result = 0;
    for(int i = 1;i<=n;i++)
        result += s_recursive(n,i);
	return result;
}

int b_dynamic(int n)
{
    int result = 0;
    for(int i = 1;i<=n;i++)
        result += s_dynamic(n,i);
    return result;
}






