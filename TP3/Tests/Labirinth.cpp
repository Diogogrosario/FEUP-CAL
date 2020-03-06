/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;


Labirinth::Labirinth(int values[10][10])
{
    initializeVisited();
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}




void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}


bool Labirinth::findGoal(int x, int y)
{
    this->visited[x][y] = true;
    if(this->labirinth[x-1][y] == 2 || this->labirinth[x+1][y] == 2 || this->labirinth[x][y-1] == 2 || this->labirinth[x][y+1] == 2){ //Alguma saida
        return true;
    }

    if(x>=1 && this->labirinth[x-1][y] == 1 && this->visited[x-1][y] != 1) { //esquerda
        if(findGoal(x-1,y)){
            return true;
        }

    }
    if(x<=9 && this->labirinth[x+1][y] == 1 && this->visited[x+1][y] != 1){ //direita
        if(findGoal(x+1,y)){
            return true;
        }
    }
    if(y>=1 && this->labirinth[x][y-1] == 1 && this->visited[x][y-1] != 1){ //baixo
        if(findGoal(x,y-1)){
           return true;
        }
    }
    if(y<=9 && this->labirinth[x][y+1] == 1 && this->visited[x][y+1] != 1){ //cima
        if(findGoal(x,y+1)){
            return true;
        }
    }
    else
        return false;
}


