#include <iostream>
#include <fstream>
#include <utility>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <sstream>

#include <boost/filesystem.hpp>

using namespace boost::filesystem;
using namespace std;

typedef vector<vector<vector<double> > > IRGB;
typedef vector<vector<double> > IGRAY;


static const int BIN_THRESHOLD = 35;

std::ifstream fin, ofin;

std::ofstream fout("model.out");


IRGB read_rgb() {

    // input file contains BGR values, make sure to read them as RGB
    int r, c;
    fin >> r >> c;
    cout << "r: " << r << " c: " << c << endl;

    IRGB img;
    img.resize(r, vector<vector<double> > (c, vector<double>()));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            string tok;
            fin >> tok;
            istringstream iss(tok);
            double v;
            while (iss >> v) {
                img[i][j].push_back(v);
                if (iss.peek() == ',') {
                    iss.ignore();
                }
            }
            swap(img[i][j][0], img[i][j][2]);
        }
    }

    return img;
}



IGRAY rgb2gray(const IRGB& img) {

    int r = img.size();
    int c = img[0].size();

    IGRAY gray(r, vector<double>(c));

    for (int i=0; i<r; ++i) {
        for (int j=0; j<c; ++j) {
            gray[i][j] = 0.21 * img[i][j][0] + 0.72 * img[i][j][1] + 0.07 * img[i][j][2];
        }
    }

    return gray;
}


void plot(const IGRAY& gray, double threshold, bool invert=false, bool bounding_box=false) {

    if(bounding_box) {
        for(int i=0; i<gray[0].size()+1; ++i)
        cout << "--";
        cout << endl;
    }
    for (auto& r : gray) {
        if (bounding_box)
        cout << "|";
        for (auto &c : r) {
            if (c <= threshold) {
                if (invert) {
                    cout << "  ";
                }
                else {
                    cout << "X ";
                }
            }
            else {
                if (invert) {
                    cout << "X ";
                }
                else {
                    cout << "  ";
                }
            }
        }
        if (bounding_box)
        cout << "|";
        cout << endl;
    }
    if (bounding_box) {
        for(int i=0; i<gray[0].size()+1; ++i)
        cout << "--";
        cout << endl;
    }
}


void print_img(const IRGB& img) {

    for (auto& r : img) {
        for (auto &c : r) {
            cout << c[0] << "," << c[1] << "," << c[2] << " ";
        }
        cout << endl;
    }
}


void print_img(const IGRAY& img) {

    for (auto& r : img) {
        for (auto &c : r) {
            cout << c << " ";
        }
        cout << endl;
    }
}


map<double, int> histogram(const IGRAY& gray) {

    map<double,int> hist;
    for (auto& r : gray) {
        for (auto& c : r) {
            hist[c]++;
        }
    }
    return hist;
}


void bin_threshold(IGRAY& gray, double threshold) {
    for (auto& r : gray) {
        for (auto& c : r) {
            if (c <= threshold) {
                c = 1;
            }
            else {
                c = 0;
            }
        }
    }
}


vector<bool> project_on_horizontal(const IGRAY& gray) {

    vector<bool> res(gray[0].size(), 0);

    for (int i=0; i<gray.size(); ++i) {
        for (int j=0; j<gray[0].size(); ++j) {
            if (gray[i][j] == 1) {
                res[j] = 1;
            }
        }
    }
    return res;
}

vector<bool> project_on_vertical(const IGRAY& gray) {

    vector<bool> res(gray.size(), 0);

    for (int i=0; i<gray.size(); ++i) {
        for (int j=0; j<gray[0].size(); ++j) {
            if (gray[i][j] == 1) {
                res[i] = 1;
            }
        }
    }
    return res;
}

vector<pair<int,int> > get_segments(const vector<bool>& arr) {

    vector<pair<int, int> > res;
    for (int i=0; i<arr.size(); ++i) {
        if (arr[i]) {
            if (i == 0 || arr[i-1]) {
                res.back().second++;
            }
            else {
                res.push_back(make_pair(i,1));
            }
        }
    }
    return res;
}


// an element is: xmin, xmax, ymin, ymax
vector<vector<int> > get_bounding_boxes(const IGRAY& gray) {

    auto hs = project_on_horizontal(gray);
    auto vs = project_on_vertical(gray);

    auto hs_segs = get_segments(hs);
    auto vs_segs = get_segments(vs);

    vector<vector<int> > res;

    for (auto& h : hs_segs) {
        res.push_back(vector<int>(4));
        res.back()[0] = h.first;
        res.back()[1] = h.first + h.second - 1;

        res.back()[2] = vs_segs[0].first;
        res.back()[3] = vs_segs[0].first + vs_segs[0].second - 1;
    }
    return res;
}


IGRAY trim(IGRAY& bin, int xmin, int ymin, int xmax, int ymax) {

    int n = ymax - ymin + 1;
    int m = xmax - xmin + 1;

    IGRAY res(n, vector<double>(m));

    for (int i=ymin; i<=ymax; ++i) {
        for (int j=xmin; j<=xmax; ++j) {
            res[i-ymin][j-xmin] = bin[i][j];
        }
    }
    return res;
}


int main () {

    map<char, IGRAY> p2l;


    path inp ("./sampleCaptchas");
    cout << inp.string() << endl;

    directory_iterator end_itr;

    // cycle through the directory
    for (directory_iterator itr(inp); itr != end_itr; ++itr)
    {
        // If it's not a directory, list it. If you want to list directories too, just remove this check.
        if (is_regular_file(itr->path()) &&
        itr->path().extension().string() == ".txt" &&
        itr->path().string().find("input") != std::string::npos) {
            // assign current file name to current_file and echo it out to the console.
            string current_file = itr->path().string();

            // open input file
            fin.open(current_file);
            cout << "Opened file: " << current_file << endl;
            if (!fin.is_open()) {
                cout << "Could not open input file ..." << endl;
                continue;
            }

            size_t pos = current_file.find("input");
            string output_file = current_file.substr(0,pos) + string("output") + current_file.substr(pos+5);

            cout << "Open output file: " << output_file << endl;
            ofin.open(output_file);
            if (!ofin.is_open()) {
                cout << "Could not open output file ..." << endl;
                continue;
            }
            string label;
            ofin >> label;
            cout << "Label: " << label << endl;

            //ofin.close();
            //fin.close();

            auto img = read_rgb();

            cout << "Converting to gray ..." << endl;
            auto gray = rgb2gray(img);

            cout << "plot ..." << endl;
            plot(gray, BIN_THRESHOLD);

            cout << "Threshold ..." << endl;
            bin_threshold(gray, BIN_THRESHOLD);

            cout << "Get bounding boxes ..." << endl;

            auto bbs = get_bounding_boxes(gray);
            int _i = 0;
            for (auto& bb : bbs) {
                cout << bb[0] << "," << bb[2] << " " << bb[1] << "," << bb[3] << endl;

                auto res = trim(gray, bb[0], bb[2], bb[1], bb[3]);

                if (p2l.find(label[_i]) == p2l.end()) {
                    p2l[label[_i]] = res;
                }

                plot(res, 0, true);
                _i++;
            }

            fin.close();
            ofin.close();
        }
    }

    fout << "map<char, vector<vector<double> > > l2p = {\n";

    for (auto& k : p2l) {
        plot(k.second, 0, true);
        cout << "LABEL: " << k.first << endl;

        // write to file as a map<char, IGRAY> definition

        fout << "{\n";

        fout << "'" << k.first << "', {\n";

        auto mat = k.second;
        int n = mat.size();
        int m = mat[0].size();
        for (int i=0; i<n; ++i) {
            fout << "{";
            for (int j=0; j<m; ++j) {
                fout << mat[i][j];
                if (j != m-1) {
                    fout << ", ";
                }
            }
            fout << "}";
            if (i != n-1) {
                fout << ",";
            }
            fout << "\n";
        }
        fout << "}\n";

        fout << "},\n";
        break;
    }
    fout << "};";
    fout.close();





    /*
    auto hist = histogram(gray);
    for (auto& e : hist) {
    if (e.second > 50) {
    cout << e.first << ": " << e.second << endl;
}
}
*/

//plot(gray);

/*
auto horiz = project_on_horizontal(gray);
auto verti = project_on_vertical(gray);

auto horiz_len = get_segments(horiz);
for (auto& e : horiz_len) {
cout << e.first << ": " << e.second << endl;
}


auto verti_len = get_segments(verti);

for (auto& e : verti_len) {
cout << e.first << ": " << e.second << endl;
}
*/

return 0;
}
