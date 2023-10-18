#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
#define ll long long int

using namespace std;

long long solution(string block, int pos) {
    long long clock = 0;
    int n = block.size();
    pos = pos - 1;

    while(pos < n && pos >= 0) {
        //cout << pos << endl;
        if(block[pos] == '<') {
            pos--;
            block.replace(pos, 1, ">");
        }
        else {
            pos++;
            block.replace(pos, 1, "<");
        }
        clock++;
    }

    return clock;
}

int main() {
    string block; cin >> block;
    int pos; cin >> pos;
    cout << solution(block, pos);
}