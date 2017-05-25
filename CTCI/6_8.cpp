#include<bits/stdc++.h>
//====================================
// Name: 6.8 CTCI Vol 6
// Date: 24/03/17
// Author: Cristian Plop
// Copyright: Please refer to author's name in your contribution.
// Description: You have 1000 botles, one of them poisoned, and 10 strips to test them. Testing lasts 7 days. Find out which bottle is poisoned in as few days as possible.
//====================================

using namespace std;

class Bottle{
private:
  int _id;
  bool _isPoisoned;
public:
  Bottle(){}
  Bottle(int id, bool poison) : _id(id), _isPoisoned(poison){}
  int id(){ return _id; }
  void set_id(int id){ _id = id; }
  bool isPoisoned(){ return _isPoisoned; }
  void setPoisoned(bool v){ _isPoisoned = v; }
};

class TestStripe{
private:
  int _id;
  map<int, vector<Bottle> > _bottlesDropedAtDay;
public:
  static const int DAYS_FOR_RESULT = 7;
  TestStripe(int id) : _id(id){}
  int id(){ return _id; }
  void set_id(int id){ _id = id; }
  void dropBottlesAtDay(int day, vector<Bottle>& bottles){
    for(auto& b : bottles)
      _bottlesDropedAtDay[day].push_back(b);
  }
  void dropBottlesAtDay(int day, Bottle& bottle){
    _bottlesDropedAtDay[day].push_back(bottle);
  }
  vector<Bottle> getBottlesOnDay(int day){
    int testDay = day - DAYS_FOR_RESULT;
    if(_bottlesDropedAtDay.find(testDay) != _bottlesDropedAtDay.end())
      return _bottlesDropedAtDay[testDay];
    return vector<Bottle>();
  }
  bool isPositive(vector<Bottle>& bottles){
    for(auto& b : bottles)
      if(b.isPoisoned())
        return true;
    return false;
  }
};


pair<Bottle,int> poisonousBottle(vector<Bottle>& bottles, vector<TestStripe>& testStripes){
  int day = 0;
  bool found = false;
  int id;
  while (!found) {
    for(auto& ts : testStripes){
      for(auto& b : bottles){
        int id = b.id();
        if(id & (1 << ts.id()))
          ts.dropBottlesAtDay(day, b);
      }
    }
    // wait for results
    day += TestStripe::DAYS_FOR_RESULT;

    id = 0;
    for(auto& ts : testStripes){
      vector<Bottle> bts = ts.getBottlesOnDay(day);
      if(ts.isPositive(bts))
        id = id | (1 << ts.id());
    }
    found = true;
  }
  return make_pair(Bottle(id, true), day);
}

int main(){

  srand(time(NULL));
  int n = 1000;
  int t = 10;
  vector<Bottle> bottles;
  for(int i=1; i<=n; ++i)
    bottles.push_back(Bottle(i, false));
  int poisonedIndex = rand()%n + 1;
  bottles[poisonedIndex].setPoisoned(true);

  for(auto& b: bottles)
    if(b.isPoisoned())
      cout << "Bottle #" << b.id() << " was poisoned.\n";


  vector<TestStripe> testStripes;
  for(int i=0; i<t; ++i)
    testStripes.push_back(TestStripe(i));

  pair<Bottle, int> res = poisonousBottle(bottles, testStripes);
  cout << "Poisonous bottle #" << res.first.id() << " in " << res.second << " days.\n";

}
