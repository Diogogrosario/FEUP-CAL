/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>
#include <cstring>
#include <iostream>
using namespace std;

string calcSum(int* sequence, int size)
{

    int min = 9999999999;
    int index;
    string result = "";
    int *seq = new int[size*size];
    memset(seq,0,sizeof(int)*size*size);
    for(int i = 0;i< size;i++){
        seq[i]=sequence[i];
        if(seq[i] < min){
            min = seq[i];
            index = i;
        }
    }
    result += to_string(min) + "," + to_string(index) + ";";

    for(int i = 1;i<size;i++){ // i  = valor do "bloco" em que estou
        min = 99999999999;
        for(int j = 0;j<size-1;j++){
            seq[i*size+j] = seq[(i-1)*size+j] + seq[j+i];
            if(seq[i*size+j] < min){
                min = seq[i*size+j];
                index = j;
            }
        }
        result += to_string(min) + "," + to_string(index) + ";";
    }


	return result;
}

