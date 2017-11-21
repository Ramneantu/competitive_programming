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
    cin >> r >> c;

    IRGB img;
    img.resize(r, vector<vector<double> > (c, vector<double>()));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            string tok;
            cin >> tok;
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

bool equal(
    const IGRAY& i1,
    const IGRAY& i2) {

        if (i1.size() != i2.size())
        return false;
        if (i1[0].size() != i2[0].size())
        return false;

        double diff = 0;
        for (int i=0; i<i1.size(); ++i) {
            for (int j = 0; j<i1[i].size(); ++j) {
                if (i1[i][j] != i2[i][j]) {
                    diff++;
                    //return false;
                }
            }
        }
        diff /= (i1.size() * i1[0].size());
        //cout << "Error: " << diff << endl;

        if (diff <= 0.07)
        return true;
        return false;
    }


    void train () {
        map<char, IGRAY> p2l;

        path inp ("/Users/whoiscris/competitive_programming/HACKERRANK/ML/digital_image_analysis/sampleCaptchas");

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


        /**
        * Write the model to model.txt
        **/
        fout << "map<char, vector<vector<double> > > l2p = {\n";
        for (auto& k : p2l) {
            plot(k.second, 0, true);
            cout << "LABEL: " << k.first << endl;

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
        }
        fout << "};";
        fout.close();
    }



    int main () {

        //train();

        /**
        * The model obtained from model.txt generated by train();
        **/
        map<char, vector<vector<double> > > l2p = {
            {
                '0', {
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 1, 1, 1, 1, 0, 0},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {0, 0, 1, 1, 1, 1, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0}
                }
            },
            {
                '1', {
                    {0, 0, 1, 1, 0, 0},
                    {0, 1, 1, 1, 0, 0},
                    {1, 1, 1, 1, 0, 0},
                    {0, 0, 1, 1, 0, 0},
                    {0, 0, 1, 1, 0, 0},
                    {0, 0, 1, 1, 0, 0},
                    {0, 0, 1, 1, 0, 0},
                    {0, 0, 1, 1, 0, 0},
                    {0, 0, 1, 1, 0, 0},
                    {1, 1, 1, 1, 1, 1}
                }
            },
            {
                '2', {
                    {0, 0, 1, 1, 1, 1, 0, 0},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 1, 1, 0},
                    {0, 0, 0, 0, 1, 1, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 1, 1, 0, 0, 0, 0},
                    {0, 1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 1, 1, 1, 1, 1, 1}
                }
            },
            {
                '3', {
                    {0, 1, 1, 1, 1, 1, 0, 0},
                    {1, 1, 0, 0, 0, 1, 1, 0},
                    {0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 1, 1, 0},
                    {0, 0, 0, 1, 1, 1, 0, 0},
                    {0, 0, 0, 0, 0, 1, 1, 0},
                    {0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 1, 1, 0},
                    {0, 1, 1, 1, 1, 1, 0, 0}
                }
            },
            {
                '4', {
                    {0, 0, 0, 0, 0, 1, 1, 0},
                    {0, 0, 0, 0, 1, 1, 1, 0},
                    {0, 0, 0, 1, 1, 1, 1, 0},
                    {0, 0, 1, 1, 0, 1, 1, 0},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {1, 1, 0, 0, 0, 1, 1, 0},
                    {1, 1, 1, 1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 0, 1, 1, 0},
                    {0, 0, 0, 0, 0, 1, 1, 0},
                    {0, 0, 0, 0, 0, 1, 1, 0}
                }
            },
            {
                '5', {
                    {1, 1, 1, 1, 1, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 1, 1, 1, 0, 0},
                    {1, 1, 1, 0, 0, 1, 1, 0},
                    {0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {0, 0, 1, 1, 1, 1, 0, 0}
                }
            },
            {
                '6', {
                    {0, 0, 1, 1, 1, 1, 0, 0},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 1, 1, 1, 0, 0},
                    {1, 1, 1, 0, 0, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {0, 0, 1, 1, 1, 1, 0, 0}
                }
            },
            {
                '7', {
                    {1, 1, 1, 1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 1, 1, 0},
                    {0, 0, 0, 0, 1, 1, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 1, 1, 0, 0, 0, 0},
                    {0, 1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0}
                }
            },
            {
                '8', {
                    {0, 0, 1, 1, 1, 1, 0, 0},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {0, 0, 1, 1, 1, 1, 0, 0},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {0, 0, 1, 1, 1, 1, 0, 0}
                }
            },
            {
                '9', {
                    {0, 0, 1, 1, 1, 1, 0, 0},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {0, 1, 1, 0, 0, 1, 1, 1},
                    {0, 0, 1, 1, 1, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 1, 0, 0, 0, 0, 1, 1},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {0, 0, 1, 1, 1, 1, 0, 0}
                }
            },
            {
                'A', {
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 1, 1, 1, 1, 0, 0},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1}
                }
            },
            {
                'B', {
                    {1, 1, 1, 1, 1, 1, 0, 0},
                    {1, 1, 0, 0, 0, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 1, 1, 0},
                    {1, 1, 1, 1, 1, 1, 0, 0},
                    {1, 1, 0, 0, 0, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 1, 1, 0},
                    {1, 1, 1, 1, 1, 1, 0, 0}
                }
            },
            {
                'C', {
                    {0, 0, 1, 1, 1, 1, 1, 0},
                    {0, 1, 1, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 0, 1},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 1},
                    {0, 1, 1, 0, 0, 0, 1, 1},
                    {0, 0, 1, 1, 1, 1, 1, 0}
                }
            },
            {
                'D', {
                    {1, 1, 1, 1, 1, 1, 0, 0},
                    {1, 1, 0, 0, 0, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 1, 1, 0},
                    {1, 1, 1, 1, 1, 1, 0, 0}
                }
            },
            {
                'E', {
                    {1, 1, 1, 1, 1, 1, 1},
                    {1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 1, 1, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 1, 1, 1, 1, 1}
                }
            },
            {
                'F', {
                    {1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 1, 1, 1, 1, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0}
                }
            },
            {
                'G', {
                    {0, 0, 1, 1, 1, 1, 1, 0},
                    {0, 1, 1, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 1, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {0, 1, 1, 0, 0, 0, 1, 1},
                    {0, 0, 1, 1, 1, 1, 1, 0}
                }
            },
            {
                'H', {
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1}
                }
            },
            {
                'I', {
                    {1, 1, 1, 1, 1, 1},
                    {0, 0, 1, 1, 0, 0},
                    {0, 0, 1, 1, 0, 0},
                    {0, 0, 1, 1, 0, 0},
                    {0, 0, 1, 1, 0, 0},
                    {0, 0, 1, 1, 0, 0},
                    {0, 0, 1, 1, 0, 0},
                    {0, 0, 1, 1, 0, 0},
                    {0, 0, 1, 1, 0, 0},
                    {1, 1, 1, 1, 1, 1}
                }
            },
            {
                'J', {
                    {0, 0, 1, 1, 1, 1},
                    {0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 1, 1},
                    {1, 0, 0, 0, 1, 1},
                    {1, 1, 0, 1, 1, 0},
                    {0, 1, 1, 1, 0, 0}
                }
            },
            {
                'K', {
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 1, 0, 0},
                    {1, 1, 0, 0, 1, 1, 0, 0},
                    {1, 1, 0, 1, 1, 0, 0, 0},
                    {1, 1, 1, 1, 0, 0, 0, 0},
                    {1, 1, 1, 1, 0, 0, 0, 0},
                    {1, 1, 0, 1, 1, 0, 0, 0},
                    {1, 1, 0, 0, 1, 1, 0, 0},
                    {1, 1, 0, 0, 0, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 1}
                }
            },
            {
                'L', {
                    {1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 1, 1, 1, 1, 1}
                }
            },
            {
                'M', {
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 1, 0, 0, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 1, 0, 1, 1, 0, 1, 1},
                    {1, 1, 0, 1, 1, 0, 1, 1},
                    {1, 1, 0, 1, 1, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1}
                }
            },
            {
                'N', {
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 1, 0, 0, 0, 1, 1},
                    {1, 1, 1, 1, 0, 0, 1, 1},
                    {1, 1, 1, 1, 0, 0, 1, 1},
                    {1, 1, 0, 1, 1, 0, 1, 1},
                    {1, 1, 0, 1, 1, 0, 1, 1},
                    {1, 1, 0, 0, 1, 1, 1, 1},
                    {1, 1, 0, 0, 0, 1, 1, 1},
                    {1, 1, 0, 0, 0, 1, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1}
                }
            },
            {
                'O', {
                    {0, 0, 1, 1, 1, 1, 0, 0},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {0, 0, 1, 1, 1, 1, 0, 0}
                }
            },
            {
                'P', {
                    {1, 1, 1, 1, 1, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 1, 1, 1, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0}
                }
            },
            {
                'Q', {
                    {0, 0, 1, 1, 1, 1, 0, 0},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 1, 1, 0, 1, 1},
                    {1, 1, 0, 0, 1, 1, 1, 1},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {0, 0, 1, 1, 1, 1, 0, 1}
                }
            },
            {
                'R', {
                    {1, 1, 1, 1, 1, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 1, 1, 1, 1, 1, 0},
                    {1, 1, 1, 1, 1, 0, 0, 0},
                    {1, 1, 0, 0, 1, 1, 0, 0},
                    {1, 1, 0, 0, 0, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1}
                }
            },
            {
                'S', {
                    {0, 1, 1, 1, 1, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0, 0},
                    {0, 1, 1, 1, 1, 1, 1, 0},
                    {0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {0, 1, 1, 1, 1, 1, 1, 0}
                }
            },
            {
                'T', {
                    {1, 1, 1, 1, 1, 1, 1, 1},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0}
                }
            },
            {
                'U', {
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {0, 0, 1, 1, 1, 1, 0, 0}
                }
            },
            {
                'V', {
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {0, 0, 1, 1, 1, 1, 0, 0},
                    {0, 0, 1, 1, 1, 1, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0}
                }
            },
            {
                'W', {
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 1, 1, 0, 1, 1},
                    {1, 1, 0, 1, 1, 0, 1, 1},
                    {1, 1, 0, 1, 1, 0, 1, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 0, 0, 1, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1}
                }
            },
            {
                'X', {
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {0, 0, 1, 1, 1, 1, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 1, 1, 1, 1, 0, 0},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1}
                }
            },
            {
                'Y', {
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {1, 1, 0, 0, 0, 0, 1, 1},
                    {0, 1, 1, 0, 0, 1, 1, 0},
                    {0, 0, 1, 1, 1, 1, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0}
                }
            },
            {
                'Z', {
                    {1, 1, 1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 1, 1, 0},
                    {0, 0, 0, 1, 1, 0, 0},
                    {0, 0, 1, 1, 0, 0, 0},
                    {0, 1, 1, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 0},
                    {1, 1, 1, 1, 1, 1, 1}
                }
            },
        };


        /**
        * Read an image and classify the letters.
        **/
        IRGB img = read_rgb();

        IGRAY gray = rgb2gray(img);

        bin_threshold(gray, BIN_THRESHOLD);

        string ans = "";
        auto bbs = get_bounding_boxes(gray);
        int _i = 0;
        for (auto& bb : bbs) {
            auto res = trim(gray, bb[0], bb[2], bb[1], bb[3]);

            // search for the right pattern
            for (auto& k : l2p) {
                if (equal(res, k.second)) {
                    ans += k.first;
                    break;
                }
            }
        }
        cout << ans << endl;

        return 0;
    }
