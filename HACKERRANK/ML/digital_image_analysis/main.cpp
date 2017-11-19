#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;


bool in_bounds(int n, int m, int i, int j) {
  return i >= 0 && i < n && j >= 0 && j < m;
}

void output(const vector<vector<char> >& mat, bool use_space=true) {

  for (auto& row : mat) {
     for (auto& e : row) {
       std::cout << e;
       if (use_space) {
         std::cout << " ";
       }
     }
     std::cout << std::endl;
  }
}

int count_ones(vector<vector<char> >& mat) {
  int ones = 0;
  for (auto& row : mat) {
    for (auto& e : row) {
      ones += (e == '1');
    }
  }
  return ones;
}


vector<vector<char> > dilation(
    const vector<vector<char> >& mat,
    const vector<vector<char> >& pattern,
    const int ci,
    const int cj) {

  int n = mat.size();
  int m = mat[0].size();
  int pn = pattern.size();
  int pm = pattern[0].size();
  vector<vector<char> > dmat = mat;
  for(int i=0; i<n; ++i) {
    for(int j=0; j<m; ++j) {
      char new_val = '0';
      for(int k=-ci; k<=pn-ci; ++k) {
        for(int l=-cj; l<=pm-cj; ++l) {
          int ii = i + k;
          int jj = j + l;
          int pi = k+ci;
          int pj = l+cj;
          //std::cout << ii << " " << jj << " " << pi << " " << pj << std::endl;
          if (in_bounds(n,m,ii,jj) &&
              mat[ii][jj] == '1' &&
              in_bounds(pn,pm,pi,pj) &&
              pattern[pi][pj] == '1'){
              new_val = '1';
          }
        }
      }
      dmat[i][j] = new_val;
    }
  }
  return dmat;
}


vector<vector<char> > erosion(
    const vector<vector<char> >& mat,
    const vector<vector<char> >& pattern) {

  int n = mat.size();
  int m = mat[0].size();
  int pn = pattern.size();
  int pm = pattern[0].size();
  vector<vector<char> > dmat = mat;
  for(int i=0; i<n; ++i) {
    for(int j=0; j<m; ++j) {
      char new_val = '1';
      for(int k=-pn/2; k<=pn/2; ++k) {
        for(int l=-pm/2; l<=pm/2; ++l) {
          int ii = i + k;
          int jj = j + l;
          if (!in_bounds(n,m,ii,jj) || (mat[ii][jj] != '1')){
              new_val = '0';
          }
        }
      }
      dmat[i][j] = new_val;
    }
  }

  return dmat;
}


/*
vector<vector<char> > closing(const vector<vector<char> >& mat) {

  auto dmat = erosion(dilation(mat));
  count_ones(dmat);
  return dmat;
}

vector<vector<char> > opening(const vector<vector<char> >& mat) {

  auto dmat = dilation(erosion(mat));
  count_ones(dmat);
  return dmat;
}
*/


void read_mat(vector<vector<char> >& mat) {
  int n,m;
  cin >> n >> m;
  mat.resize(n, vector<char>(m));
  for (int i=0; i<n; ++i) {
    string line;
    cin >> line;
    for(int j=0; j<m; ++j) {
      mat[i][j] = line[j];
    }
  }
}


int main() {


  vector<vector<char> > mat, pattern;

  read_mat(mat);
  read_mat(pattern);

  cout << "Original image:" << std::endl;
  output(mat);
  cout << std::endl;

  cout << "Pattern:" << std::endl;
  output(pattern);
  cout << std::endl;

  {
    auto dmat = dilation(mat, pattern, 0,1);
    cout << "dilation image:" << std::endl;
    output(dmat, false);
    std::cout << "#ones: " << count_ones(dmat) << std::endl;
  }


  {
    auto dmat = erosion(mat, pattern);
    cout << "Erosion image:" << std::endl;
    output(dmat, false);
    std::cout << "#ones: " << count_ones(dmat) << std::endl;
  }

  /*
  cout << "Closing image:" << std::endl;
  dmat = closing(mat);
  output(dmat);

  cout << "Opening image:" << std::endl;
  dmat = opening(mat);
  output(dmat);
  */


  return 0;
}
