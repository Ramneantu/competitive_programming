#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int steps(string line){
  int left, right, cur, moves;
  moves = 0;
  cur = 0;
  int i;
  for(i=0; i<line.length() && line[i] == 'A'; ++i);
  left = i;
  //cout << "left: " << left << "\n";

  for(i=line.length()-1; i>= 0 && line[i] == 'A'; --i);
  right = i;
  //cout << "right: " << right << "\n";

  while(left <= right){
    //cout << "line: " << line << "\n";
    int dist_left, dist_right;
    if(left < cur)
      dist_left = line.length() - (cur - left);
    else
      dist_left = left - cur;
    if(right < cur)
      dist_right = cur - right;
    else
      dist_right = line.length() - (right - cur);

    //cout << "dist_to_left: " << dist_left << " dist_to_right: " << dist_right << "\n";

    if(dist_left < dist_right){
      cur = left;
      moves += dist_left;
      int letter_dist = line[left]-'A';
      line[left] = 'A';
      moves += min(letter_dist, 26-letter_dist);
      for(i=cur; i<line.length() && line[i] == 'A'; ++i);
      left = i;
    }
    else{
      cur = right;
      moves += dist_right;
      int letter_dist = line[right]-'A';
      line[right] = 'A';
      moves += min(letter_dist, 26-letter_dist);
      for(i=cur; i>=0 && line[i] == 'A'; --i);
      right = i;
    }
  }
  return moves;
}


int main(){

  int T;
  cin >> T;
  string dummy;
  for(int t=1; t<=T; ++t){
    string line;
    cin >> line;

    int s1 = steps(line);
    reverse(line.begin(), line.end());
    int s2 = steps(line);

    cout << s1 << " " << s2 << "\n";

    cout << "Case #" << t << ": " << min(s1, s2+1) << "\n";
  }

  return 0;
}
