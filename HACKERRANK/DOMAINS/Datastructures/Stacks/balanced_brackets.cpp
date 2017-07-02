#include <bits/stdc++.h>
using namespace std;

bool solve(string s){
    stack<char> S;
    for(int i=0; i<s.size(); ++i){
        char c = s[i];
        if(c == '(' || c == '[' || c == '{')
            S.push(c);
        else if(c == ')'){
            if(S.empty() || S.top() != '(')
                return false;
            else
                S.pop();
        }
        else if(c == ']'){
            if(S.empty() || S.top() != '[')
                return false;
            else
                S.pop();
        }
        else if(c == '}'){
            if(S.empty() || S.top() != '{')
                return false;
            else
                S.pop();
        }
    }
    if(!S.empty())
        return false;
    return true;
}

int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        string s;
        cin >> s;
        if(solve(s))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}


