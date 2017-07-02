#include <bits/stdc++.h>
using namespace std;


int main(){
    int n1;
    int n2;
    int n3;
    cin >> n1 >> n2 >> n3;
    int H1=0,H2=0,H3=0;
    vector<int> h1(n1);
    for(int h1_i = 0;h1_i < n1;h1_i++){
       cin >> h1[h1_i];
       H1 += h1[h1_i];
    }
    vector<int> h2(n2);
    for(int h2_i = 0;h2_i < n2;h2_i++){
       cin >> h2[h2_i];
       H2 += h2[h2_i];
    }
    vector<int> h3(n3);
    for(int h3_i = 0;h3_i < n3;h3_i++){
       cin >> h3[h3_i];
       H3 += h3[h3_i];
    }
    int i1=0,i2=0,i3=0;
    while(i1 < h1.size() && i2 < h2.size() && i3 < h3.size()){
        if(H1 == H2 && H2 == H3)
            break;
        if(H1 >= H2 && H1 >= H3)
            H1 -= h1[i1++];
        else if(H2 >= H1 && H2 >= H3)
            H2 -= h2[i2++];
        else if(H3 >= H1 && H3 >= H2)
            H3 -= h3[i3++];
    }
    if(i1 == h1.size()||i2 == h2.size()||i3 == h3.size())
        H1 = 0;

    cout << H1 << endl;
    return 0;
}
