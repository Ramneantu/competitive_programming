//====================================
// Name: 12.10 CTCI Vol 6
// Date: 23/03/17
// Author: Cristian Plop
// Copyright: Please refer to author's name in your contribution.
// Description: write an alligned malloc.
//====================================

#include<bits/stdc++.h>
using namespace std;

void *alligned_malloc(size_t bytes, size_t allign){
  // original block as returned by malloc and will be freed by a free call.
  void *original;

  // alligned memory block.
  void *alligned;

  // wee need to allocate additional allign-1 to ensure we have an address that divides by allign.
  // and and additional void* pointer to store the address of the original memory as returend by malloc.
  int offset = allign-1 + sizeof(void*);

  // we try to create a block of offset and the bytes we want. If unsuccessfull, we return NULL.
  if((original = (void*)malloc(bytes + offset)) == NULL)
    return NULL;

  // starting from original as base and counting maximum offset, we want to find the address whih divides by allign.
  // so we and it with allign-1, e.g. when allign = 16, we and it with 16, and thus making the last 4 bits 0, ensuring that the memory is divisible by 16. It's like using mod operation too.
  alligned = (void*)((size_t(original) + offset) & (allign-1));
  // if you interpret alligned as a vector of void* pointers, i.e. a void**, then you can go back one position from where alligned points to, and assign this to original, so when we de-allocate know that one position before alligned, it's the original address which was returned by malloc.
  ((void**)alligned)[-1] = original;

  return alligned;
}

void alligned_free(void *p){
  void *original = ((void**)p)[-1];
  free(original);
}


int main(){

}
