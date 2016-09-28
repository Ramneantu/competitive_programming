#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Trie{
    int cnt;
    map<char, Trie*> next;
};

Trie *init(){
    Trie *trie = new Trie;
    trie->cnt = 0;
    return trie;
}

void add(Trie* trie, string name){
    Trie* root = trie;
    string cur = "";
    for(int i=0; i<name.size(); ++i){
        char c = name[i];
        if(root->next.find(c) == root->next.end()){
            Trie* node = new Trie;
            root->next[c] = node;
        }
        root = root->next[c];
        root->cnt++;
    }
}

int find(Trie *trie, string partial){
    Trie* root = trie;
    int cnt;
    int i;
    for(i=0; i<partial.size(); ++i){
        char c = partial[i];
        if(root->next.find(c) == root->next.end())
            break;
        else{
      //      cout << c << " " << root->cnt << endl;
            root = root->next[c];
            cnt = root->cnt;
        }
    }
    //cout << "i=" << i << endl;
    if(i <= partial.size()-1)
        cnt = 0;
    return cnt;
}


int main(){
    int n;
    cin >> n;
    Trie* root = init();
    bool find_op = false;
    for(int a0 = 0; a0 < n; a0++){
        string op;
        string contact;
        cin >> op >> contact;
        if(op == "add"){
            add(root, contact);
        }
        else if(op == "find"){
            if(find_op)
              cout << endl;
            find_op = true;
            cout << find(root, contact);
        }
    }
    return 0;
}
