#include <iostream>
#include <map>
#include <utility>
#include <cstring>
#include <vector>
#include <stack>
#include <cassert>

using namespace std;

#define REP(i,a,b) for(int i=int(a); i<=int(b); ++i)


string add_op(stack<char> &s, char op){
  map<char, string> precs;
  precs['+'] = "-/*";
  precs['-'] = "+/*";
  precs['*'] = "/";
  precs['/'] = "*";
  string res = "";

  while(!s.empty() && precs[op].find(s.top()) != string::npos){
    res += s.top(); s.pop();
  }
  s.push(op);
  return res;
}

bool is_letter(char c){ return (c >= 'a' && c <= 'z'); }

string RPN(string s){
  // operator precedence from low to high
  // + - / *
  int i=0;
  string rpn;
  stack<char> st;
  while(i<s.size()){
    if(is_letter(s[i]))
      rpn += s[i];
    else if(s[i] == '('){
      st.push(s[i]);
    }
    else if(s[i] == ')'){
      while(!st.empty() && st.top() != '('){
        rpn += st.top(); st.pop();
      }
      st.pop(); // pop the open bracket ( from the stack.
    }
    else if(strchr("+-*/", s[i]) != NULL){
      rpn += add_op(st, s[i]);
    }
    i++;
  }
  while(!st.empty()){ rpn += st.top(); st.pop();}
  return rpn;
}

// evaluate a RPN expression.
double evalRPN(string rpn, map<char, int> values){
  double res = 0;
  stack<double> s;
  int i = 0;
  while(i<rpn.size()){
    if(is_letter(rpn[i])){
      s.push(values[rpn[i]]);
    }
    else if(rpn[i] == '+'){
      double a = s.top(); s.pop();
      double b = s.top(); s.pop();
      s.push(a + b);
    }
    else if(rpn[i] == '-'){
      double b = s.top(); s.pop();
      double a = s.top(); s.pop();
      s.push(a - b);
    }
    else if(rpn[i] == '*'){
      double a = s.top(); s.pop();
      double b = s.top(); s.pop();
      s.push(a * b);
    }
    else if(rpn[i] == '/'){
      double b = s.top(); s.pop();
      double a = s.top(); s.pop();
      s.push(a*1.0 / b);
    }
    i++;
  }
  res = s.top(); s.pop();
  return res;
}


map<char, int> unknowns;
map<char, int> vals;
vector<int> values;
vector<int> sol;
vector<bool> taken;
int is_possible;
int n, m;
string rpn;
void bk(int k){
  if(k == n){
    for(map<char,int>::iterator it=unknowns.begin(); it != unknowns.end(); ++it){
      vals[it->first] = values[sol[it->second]];
    }
    double res = evalRPN(rpn, vals);
    if(res == m){
        is_possible = 1;
    }
    if(res != m && is_possible == -1){
        is_possible = 0;
    }
  }
  else{
    REP(i, 0, n-1){
      if(k > 0){
        if(!taken[i]){
          taken[i] = true;
          sol[k] = i;
          bk(k+1);
          taken[i] = false;
        }
      }
      else{
        taken[i] = true;
        sol[k] = i;
        bk(k+1);
        taken[i] = false;
      }
    }
  }
}


int main(){

/*
  vals['a'] = 3;
  vals['b'] = 2;
  vals['c'] = 4;
  string expr = "(a+b)";
  rpn = RPN(expr);
  assert(rpn == "ab+");
  assert(evalRPN(rpn, vals) == 5);
  expr = "((a+b)*c)";
  rpn = RPN(expr);
  assert(rpn == "ab+c*");
  assert(evalRPN(rpn, vals) == 20);
  expr = "a-((b*c)+d)";
  rpn = RPN(expr);
  assert(rpn == "abc*d+-");
  expr = "a*b-(c*d)";
  rpn = RPN(expr);
  assert(rpn == "ab*cd*-");
  vals['a'] = 2;
  vals['b'] = 3;
  expr = "a/b*c";
  rpn = RPN(expr);
  assert(rpn == "ab/c*");
  assert(int(evalRPN(rpn, vals)) == 2);
    */
  int T;
  cin >> T;
  REP(t,1,T){
    cin >> n;
    sol.resize(n,0);
    taken.resize(n,false);
    REP(i,1,n){
      int val;
      cin >> val;
      values.push_back(val);
    }
    cin >> m;
    string s;
    cin >> s;
    int k = 0;
    REP(i, 0, s.size()-1){
      if(is_letter(s[i])){
        unknowns[s[i]] = k++;
        vals[s[i]] = 0;
      }
    }
    // turn expression to reverse polish here
    rpn = RPN(s);
    // backtrack over all the values here
    is_possible = -1;
    bk(0);
    if(is_possible == 1)
      cout << "Case #" << t << ": YES\n";
    else
      cout << "Case #" << t << ": NO\n";

    values.clear();
    unknowns.clear();
    vals.clear();

  }

  return 0;
}
