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
        cout << pos << endl;
        if(block[pos] == '<') {
            int cnt = 1;
            while(block[pos-cnt] == '<') 
                {cnt++; 
                if(pos-cnt < 0) {clock += cnt; break;}}
            block.replace(pos-(cnt+1), 1, "<");
            pos = +1;

            clock += 2*cnt + 1;
        }

        else {
            int cnt = 1;
            while(block[pos+cnt] == '>') 
                {cnt++; 
                if(pos+cnt >= n) {clock += cnt; break;}}
            block.replace(pos+(cnt+1), 1, ">");
            pos = -1;

            clock += 2*cnt + 1;
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