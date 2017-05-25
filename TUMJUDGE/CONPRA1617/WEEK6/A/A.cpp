#include<bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
#define debug 0
#define DBG(code) if(debug == 1) \
                    do{ \
                      code \
                    }while(0);

// globals
int n;
string line;
vector<vector<int> > times;
vector<vector<int> > next_digit;
vector<vector<int> > working_leds;
vector<vector<int> > sols;
map<int,int> led2dec;
map<int,int> dec2led;

// Helpers
void print_vector(vector<int> v, string msg){
  cout << msg << ": ";
  rep(i,0,v.size()-1)
    cout << v[i] << " ";
  cout << "\n";
}
void print_matrix(vector<vector<int> > M, string msg){
  cout << msg << ":\n";
  rep(i,0,M.size()-1){
    rep(j,0,M[i].size()-1)
      cout << M[i][j] << " ";
    cout << "\n";
  }
}
void print_map(map<int,int> M, string msg){
  cout << msg << ":\n";
  for(map<int,int>::iterator it=M.begin(); it!=M.end(); ++it)
    cout << it->first << ": " << it->second << "\n";
  cout << "\n";
}

inline void convert_LED_digit_to_leds(int digit, vector<int>& leds){
  if(digit==0){
      leds[0]=1;
      leds[1]=1;
      leds[3]=1;
      leds[4]=1;
      leds[2]=1;
      leds[5]=1;
  }
  if(digit==1){
      leds[4]=1;
      leds[5]=1;
  }
  if(digit==2){
      leds[0]=1;
      leds[2]=1;
      leds[3]=1;
      leds[5]=1;
      leds[6]=1;
  }
  if(digit==3){
      leds[0]=1;
      leds[4]=1;
      leds[3]=1;
      leds[5]=1;
      leds[6]=1;
  }
  if(digit==4){
      leds[1]=1;
      leds[5]=1;
      leds[6]=1;
      leds[4]=1;
  }
  if(digit==5){
      leds[0]=1;
      leds[4]=1;
      leds[3]=1;
      leds[1]=1;
      leds[6]=1;
  }
  if(digit==6){
      leds[0]=1;
      leds[1]=1;
      leds[2]=1;
      leds[3]=1;
      leds[4]=1;
      leds[6]=1;
  }
  if(digit==7){
      leds[4]=1;
      leds[5]=1;
      leds[0]=1;
  }
  if(digit==8){
      leds[0]=1;
      leds[1]=1;
      leds[2]=1;
      leds[3]=1;
      leds[4]=1;
      leds[6]=1;
      leds[5]=1;
  }
  if(digit==9){
      leds[0]=1;
      leds[1]=1;
      leds[3]=1;
      leds[4]=1;
      leds[6]=1;
      leds[5]=1;
  }
}
inline int convert_leds_to_dec(vector<int> leds){
  int nr = 0;
  rep(i,0,6)
    nr += (1<<i) * leds[i];
  return nr;
}
inline int convert_LED_digit_to_dec(int digit){
  vector<int> tmp(7,0);
  convert_LED_digit_to_leds(digit,tmp);
  return convert_leds_to_dec(tmp);
}
void init(){
  led2dec[0]=63;
  led2dec[1]=48;
  led2dec[2]=109;
  led2dec[3]=121;
  led2dec[4]=114;
  led2dec[5]=91;
  led2dec[6]=95;
  led2dec[7]=49;
  led2dec[8]=127;
  led2dec[9]=123;

  dec2led[63]=0;
  dec2led[48]=1;
  dec2led[109]=2;
  dec2led[121]=3;
  dec2led[114]=4;
  dec2led[91]=5;
  dec2led[95]=6;
  dec2led[49]=7;
  dec2led[127]=8;
  dec2led[123]=9;


  next_digit.clear();
  next_digit.resize(10,vector<int>());
  next_digit[0].push_back(0);
  next_digit[0].push_back(8);
  next_digit[1].push_back(0);
  next_digit[1].push_back(1);
  next_digit[1].push_back(3);
  next_digit[1].push_back(4);
  next_digit[1].push_back(7);
  next_digit[1].push_back(8);
  next_digit[1].push_back(9);
  next_digit[2].push_back(2);
  next_digit[2].push_back(8);
  next_digit[3].push_back(3);
  next_digit[3].push_back(8);
  next_digit[3].push_back(9);
  next_digit[4].push_back(4);
  next_digit[4].push_back(8);
  next_digit[4].push_back(9);
  next_digit[5].push_back(5);
  next_digit[5].push_back(6);
  next_digit[5].push_back(8);
  next_digit[5].push_back(9);
  next_digit[6].push_back(6);
  next_digit[6].push_back(8);
  next_digit[7].push_back(0);
  next_digit[7].push_back(3);
  next_digit[7].push_back(7);
  next_digit[7].push_back(8);
  next_digit[7].push_back(9);
  next_digit[8].push_back(8);
  next_digit[9].push_back(9);
  next_digit[9].push_back(8);
  DBG(
    //print_matrix(next_digit, "next_digit");
  )
}
inline vector<int> get_next_time(vector<int> cur_time){
  vector<int> next_time(4,0);
  int minutes = cur_time[2]*10 + cur_time[3];
  int hours = cur_time[0]*10 + cur_time[1];
  minutes++;
  if(minutes == 60){
    next_time[2] = next_time[3] = 0;
    hours++;
  }
  else{
    next_time[2] = minutes / 10;
    next_time[3] = minutes % 10;
  }
  if(hours == 24){
    next_time[0] = next_time[1] = 0;
  }
  else{
    next_time[0] = hours / 10;
    next_time[1] = hours % 10;
  }
  return next_time;
}

inline bool is_valid_time(vector<int> cur_time){
  if(cur_time[0] > 2 || cur_time[2] > 5)
    return false;
  if(cur_time[0] == 2 && cur_time[1] > 3)
    return false;
  return true;
}


bool is_valid_move(vector<int> cur_time, vector<int> next_time){

  //printf("cur_time: %d%d:%d%d\nnext_time: %d%d:%d%d\n",
  //cur_time[0],cur_time[1],cur_time[2], cur_time[3],
  //next_time[0],next_time[1],next_time[2],next_time[3]);
  rep(col,0,3){
    int cur_led = led2dec[cur_time[col]];
    int next_led = led2dec[next_time[col]];

    //printf("cur_led: %d\nnext_led: %d\n", cur_led, next_led);
    //cout << "cur_led: " << bitset<8>(cur_led) << endl;
    //cout << "next_led: " << bitset<8>(next_led) << endl;

    rep(i,0,6){
      // if led in input is ON and led in next_time is OFF => invalid
      if(((cur_led & (1<<i)) > 0) && ((next_led & (1<<i)) == 0)){
        //cout << "FALSE\n";
        return false;
      }
      // if led in input is OFF and led in next_time is ON and led is working => invalid
      if(((next_led & (1<<i)) > 0) && ((cur_led & (1<<i)) == 0) && working_leds[col][i] == 1){
        //cout << "FALSE\n";
        return false;
      }
    }
    DBG(
      //printf("n:%d\no:%d\n", next_led, cur_led);
    )
  }

  return true;
}

inline bool is_same_time(vector<int> s1, vector<int> s2){
  if(s1[0] == s2[0] && s1[1] == s2[1] && s1[2] == s2[2] && s1[3] == s2[3])
    return true;
  return false;
}

void print_result(int t){
  bool printed = false;
  cout << "Case #" << t << ":\n";
  if(sols.size() > 0){
    rep(i,0,sols.size()-1){
      if(is_valid_time(sols[i])){
        DBG(
          //cout << "sols: " << sols[i][0] << sols[i][1] << ":" << sols[i][2] << sols[i][3];
          //cout << "\n";
        )
        if(printed && !is_same_time(sols[i-1], sols[i])){
          cout << sols[i][0] << sols[i][1] << ":" << sols[i][2] << sols[i][3];
          cout << "\n";
        }
        else if(!printed){
          cout << sols[i][0] << sols[i][1] << ":" << sols[i][2] << sols[i][3];
          cout << "\n";
          printed = true;
        }
      }
    }
  }
  if(!printed)
    cout << "none\n";
}

vector<vector<int> > get_candidates(){
  vector<vector<int> > candidates(4, vector<int>());
  for(int col=3; col>=0; --col){
    int dig = times[0][col];
    int dig_dec = led2dec[dig];
    rep(i,0,next_digit[dig].size()-1){
      int next_dig = next_digit[dig][i];
      int next_dig_dec = led2dec[next_dig];
      int working_led2dec = ~convert_leds_to_dec(working_leds[col]);
      //printf("column: %d\nnd: %d\nnz: %d\n", working_led2dec, next_dig_dec, dig_dec);
      if(((next_dig_dec ^ dig_dec) | working_led2dec) == working_led2dec){
        if(col == 0 && next_dig <= 2){ // hour digit
          candidates[col].push_back(next_dig);
        }
        else if(col == 2 && next_dig <= 5){ // first minute digit
          candidates[col].push_back(next_dig);
        }
        else if(col != 0 && col != 2){
          candidates[col].push_back(next_dig);
        }
      }
    }
  }
  DBG(
    print_matrix(candidates, "candidates");
  )
  return candidates;
}

void read(){
  cin >> n;
  times.resize(n,vector<int>(4));
  rep(i,0,n-1){
    cin >> line;
    times[i][0] = line[0]-'0';
    times[i][1] = line[1]-'0';
    times[i][2] = line[3]-'0';
    times[i][3] = line[4]-'0';
  }
  DBG(
    print_matrix(times,"times");
  )
}

void get_working_leds(){
  working_leds.resize(4,vector<int>());
  rep(col,0,3){
    vector<int> leds(7,0);
    rep(i,0,n-1){
      convert_LED_digit_to_leds(times[i][col],leds);
    }
    working_leds[col] = leds;
  }
  DBG(
    print_matrix(working_leds,"working_leds");
  )
}

int main(){

  init();
  int T;
  cin >> T;
  rep(t,1,T){
    read();
    get_working_leds();

    // determine for every digit the candidates according to the working leds.
    vector<vector<int> > candidates = get_candidates();

    // generate all possible combinations of candidates.
    // sort them to get increasing order output.
    rep(i,0,3)
      sort(candidates[i].begin(),candidates[i].end());

    DBG(
      print_matrix(candidates, "candidates");
    )

    rep(i,0,candidates[0].size()-1)
      rep(j,0,candidates[1].size()-1)
        rep(k,0,candidates[2].size()-1)
          rep(l,0,candidates[3].size()-1){
            vector<int> cur_time;
            cur_time.push_back(candidates[0][i]);
            cur_time.push_back(candidates[1][j]);
            cur_time.push_back(candidates[2][k]);
            cur_time.push_back(candidates[3][l]);
            bool valid = false;
            if(is_valid_time(cur_time)){
              valid = true;
              vector<int> next_time = cur_time;
              for(int _i=0; _i<n; _i++){
                if(!is_valid_move(times[_i], next_time)){
                  valid = false;
                  break;
                }
                next_time = get_next_time(next_time);
              }
            }
            if(valid)
              sols.push_back(cur_time);
          }

    print_result(t);

    // clear globals
    times.clear();
    sols.clear();
    working_leds.clear();
  }

  return 0;
}
