#include<bits/stdc++.h>

using namespace std;

int main(){

  int T;
  cin >> T;
  string dummy;
  getline(cin, dummy);
  for(int t=1; t<=T; ++t){
    string line;
    getline(cin, line);
    vector<int> freq(26, 0);
    for(int i=0; i<line.length(); ++i){
      if(line[i] != ' '){
        int c2i = line[i] - 'A';
        freq[c2i]++;
      }
    }

    // find out the shift d by the frequency of E
    int max_freq = -1;
    int pos = -1;
    for(int i=0; i<freq.size(); ++i)
      if(freq[i] > max_freq){
        max_freq = freq[i];
        pos = i;
      }

    int count_max = 0;
    for(int i=0; i<freq.size(); ++i){
      if (freq[i] == max_freq)
        count_max++;
    }
    if(count_max > 1){
      cout << "Case #" << t << ": impossible\n";
    }
    else{
      int d = pos - ('E'-'A');
      if(d < 0)
        d = freq.size() + d;
      for(int i=0; i<line.length(); ++i){
        if(line[i] != ' '){
          int new_order = (line[i]-'A'-d);
          if(new_order < 0)
            new_order = freq.size() + new_order;
          char new_value = (char)((int)'A' + new_order);
          line[i] = new_value;
        }
      }

      cout << "Case #" << t << ": " << d << " ";
      cout << line << "\n";
    }

  }
  return 0;
}
