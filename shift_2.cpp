#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;
#define ll long long int
#define pos pair<int, int>
#define INT_MAX 65535
int d,e,f;

using namespace std;

//기린은 n까지, 열매는 m부터

int solution(int k, vector<int> giraffe, vector<int> fruits) {
    int answer = -1;
    int toeat[101] = {0, };

    sort(fruits.begin(), fruits.end());
    sort(giraffe.begin(), giraffe.end());
    vector<int> caneat;
    int n = giraffe.size();
    int m = fruits.size();

    for(int &g : giraffe) {
        int cnt = 0; //먹을 수 있는 개수
        for(int i = 0; i < m; i++) {
            if(fruits[i] > g) break;
            cnt++; 
        }

        caneat.push_back(cnt);
    }

    int g_cnt = n-1;
    int offset = 0;

    while(g_cnt >= 0) {
        if(caneat[0] < k) {
            answer += k - caneat[0];
            for(int i = 1; i < g_cnt-1; i++) {
                caneat[i] -= caneat[0];
            }
        }
        else {
            for(int i = 1; i < g_cnt-1; i++) {
                caneat[i] -= k;
        }}
    }

    return answer;
}

