/*
 * Change.cpp
 */
#include "iostream"
#include "Change.h"
#include "stdlib.h"
#include "string.h"
using namespace std;

int minCoins(int i,int k, int *coinValues) {
    if(k==0)
        return 0;
    else if(k<0)
        return -1;
    else if(i == 0 ||
            (coinValues[i] <= k && 1+minCoins(i,k-coinValues[i],coinValues) < minCoins(i-1,k,coinValues)))    //se 1 moeda nova pode substituir 2 das antigas, Ex: 1 de 2 centimos substitui 2 de 1 centimo
        return (1+minCoins(i,k-coinValues[i],coinValues));
    else
        return minCoins(i-1,k,coinValues); //  senao o minimo continua o mesmo de antes
}

int lastCoin(int i, int k, int *coinValues) {
    if (k == 0 || i == -1)
        return 0;
    else if(coinValues[i]<= k && (i == 0 || 1+minCoins(i,k-coinValues[i],coinValues) < minCoins(i-1,k,coinValues))) //  se 1 moeda nova pode substituir 2 das antigas a ultima moeda passa a ser a nova
        return coinValues[i];
    else
        return lastCoin(i-1,k,coinValues); // senao continua a ser a moeda antiga
}


string calcChange(int m, int numCoins, int *coinValues)
{
    int troco = m;
    string result = "";
    if (m == 0 || numCoins == 0){
        return "";
    }
    else if(minCoins(numCoins-1,m,coinValues) == 0){
        return "-";
    }
/*
    cout << "    ";
    for(int i = 0;i<troco;i++) {
        cout << i << " | ";
    }
    cout << endl;
    cout << "0 | ";
    for(int i = 0;i<troco;i++) {
        if(i<10)
            cout << "0" << " | ";
        else
            cout  << " 0" << " | ";
    }
    cout << endl;
    for(int i = 1;i<numCoins;i++){
        cout << i << " | ";
        for(int j = 0;j<troco;j++){
            if(j<10 || minCoins(i-1,j,coinValues)>=10)
            cout << minCoins(i-1,j,coinValues) << " | ";
            else
                cout << " " <<  minCoins(i-1,j,coinValues) << " | ";
        }
        cout << endl;
    }
*/
    int coin;

    do{
        coin = lastCoin(numCoins-1,m,coinValues); // vai buscar a ultima moeda e retira ao troco
        m -= coin;
        result += to_string(coin);
        result += ";";
    }while(m>0);
    //cout << endl << endl;
    return result;
}


