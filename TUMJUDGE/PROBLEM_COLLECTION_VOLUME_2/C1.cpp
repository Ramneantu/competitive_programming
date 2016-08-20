// Author: Adrian Kuegel
// Date: September 8th, 2010
// Algorithm: greedy
// Complexity: O(n)

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <algorithm>
#include <assert.h>
using namespace std;

#define MAXN 1000
char a[MAXN+1];

int solve(int n) {
	int sum = 0, res = n-1;
	int empty = 0;
	for (int i=0; i<n; ++i)
		if (a[i] != 'A') {
			sum += min(a[i]-'A', 'Z'-a[i]+1);
			if (empty && empty != i)
				res = min(res, n-i+(i-empty-1)*2);
			empty = 0;
		}
		else
			++empty;
	if (!sum)
		return 0;
	if (empty)
		res = min(res, n-1-empty);
	return res + sum;
}

int main() {
	int tc;
	scanf("%d", &tc);
	assert(tc >= 1 && tc <= 100);
	while(tc--) {
		scanf("%s", a);
		int l = strlen(a);
		assert(l <= MAXN);
		for (int i=1; i<l; ++i)
			assert(isupper(a[i]));
		int res1 = solve(l);
		reverse(a+1, a+l);
		int res2 = solve(l);
		printf("%d\n", min(res1, res2));
	}
	return 0;
}
