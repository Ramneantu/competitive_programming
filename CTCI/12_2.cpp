//====================================
// Name: 12.2 CTCI Vol6
// Date: 21/03/17
// Author: Cristian Plop
// Copyright: Please refer to author's name in your contribution.
// Description: reverse a C-string.
//====================================

#include<bits/stdc++.h>
using namespace std;

int main(){

}
#include<bits/stdc++.h>

void reverse(char *str){
  int len = strlen(str);
  int lim = len/2;
  int i=0;
  while(i<lim){
    std::swap(str[i], str[len-i-1]);
    i++;
  }
}

int main(){

  char str[1000];
  std::cin >> str;
  reverse(str);
  std::cout << str << std::endl;
}
