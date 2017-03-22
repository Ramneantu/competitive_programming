//====================================
// Name: 12.9 CTCI Vol6
// Date: 21/03/17
// Author: Cristian Plop
// Copyright: Please refer to author's name in your contribution.
// Description: implement a smart pointer in C++.
//====================================

#include<bits/stdc++.h>
using namespace std;

template<class T>
class SmartPointer{
private:
  size_t *references_count;
  T *reference;

  void remove(){
    if(*references_count > 0)
      *references_count--;

    if(*references_count == 0){
      delete reference;
      free(references_count);
      references_count = NULL;
      reference = NULL;
    }
  }
public:
  SmartPointer(T *ref){
    reference = ref;
    references_count = (size_t *) malloc(sizeof(size_t));
    *references_count = 1;
  }

  SmartPointer<T>& operator=(SmartPointer<T> &ptr){
    if(this == &ptr){ // we need & because we need to check if the addresses are the same, i.e. if we try to assign the sam object to itself.
      return *this; // we need to return the dereference, because this points to the adress of the object.
    }

    // remove one reference to the old ptr.
    remove();

    // update with new reference.
    reference = ptr.reference;
    references_count = ptr.references_count;
    (*references_count)++;

    return *this;
  }

  ~SmartPointer(){
    remove();
  }

  T get(){
    return *reference;
  }
};


int main(){

  // TEST!
}
