#include <bits/stdc++.h>
#include "test_generator.hpp"
using namespace std;

int main() {

	leetcode_test::randInit(time(NULL));
	leetcode_test::generatePairs(10, 0,5,0,5, true);

	return 0;
}