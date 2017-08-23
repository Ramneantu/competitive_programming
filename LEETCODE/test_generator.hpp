#ifndef TEST_GENERATOR_HPP
#define TEST_GENERATOR_HPP

#include <bits/stdc++.h>
using namespace std;


namespace leetcode_test {

	/**
		Initializes the random generator.
		@param[in] seed the starting value of the generator, by default 0.
	**/
	void randInit(int seed = 0) {
		srand(seed);
	}


	/**
		Generates a random number between N and M.
		@param[in] M upper limit of the random generated value.
		@param[in] N lower limit of the random generated value.
		@param[out] the generated random number.
	**/
	template<typename T>
	T randMToN(T M, T N) {
	    return M + T(rand() / ( RAND_MAX / (N-M) ) ) ;
	}


	/**
		Generates and optionaly optionally outputs a number n of at most nmax pair<T,T> values, one on each line.
		@param[in] nmax maximum number of pairs to generate.
		@param[in] xmin minimum value of the first value of any pair generated.
		@param[in] xmax maximum value of the first value of any pair generated.
		@param[in] ymin minimum value of the second value of any pair generated.
		@param[in] ymax maximum value of the second value of any pair generated.
		@param[in] printToOutputStream if true, the value n and pairs will be printed to stdout
		@param[out] vector containing the generated pairs.
	**/
	template<typename T>
	vector<pair<T,T> > generatePairs(int nmax, T xmin, T xmax, T ymin, T ymax, bool printToOutputStream = false) {
		int n = rand() % nmax;
		vector<pair<T,T> > res;
		for(int i=0; i<n; ++i) {
			T x = randMToN(xmin, xmax);
			T y = randMToN(ymin, ymax);
			res.push_back({x,y});
		}

		if(printToOutputStream) {
			cout << n << endl;
			for(auto& e : res) {
				cout << e.first << " " << e.second << endl;
			}
		}
		return res;
	}
}

#endif // TEST_GENERATOR_HPP
