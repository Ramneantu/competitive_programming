//====================================
// Name: 12.11 CTCI Vol 6
// Date: 24/03/17
// Author: Cristian Plop
// Copyright: Please refer to author's name in your contribution.
// Description: write a 2d malloc
//====================================

#include<bits/stdc++.h>
using namespace std;

int **malloc_2d(int rows, int cols){
  int **a;
  if((a = (int**)malloc(rows * sizeof(int*))) == NULL)
    return NULL;
  for(int i=0; i<rows; ++i)
    a[i] = (int*)malloc(cols * sizeof(int));
  return a;
}

int main(){

}
