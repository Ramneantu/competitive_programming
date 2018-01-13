#include "leet_code.h"
using namespace std;

class Solution {
public:
    bool judgeCircle(string moves) {
        std::map<char, pair<int,int> > move_to_position_table = {{'U',{-1,0}}, {'R', {0,1}}, {'D', {1,0}}, {'L', {0,-1}}};
        
        pair<int,int> last_position = {0,0};
        for(auto move : moves) {
            auto d_position = move_to_position_table[move];
            last_position.first += d_position.first;
            last_position.second += d_position.second;
        }
        return (last_position.first == 0 && last_position.second == 0);
    }
};

int main() {

    return 0;
}
