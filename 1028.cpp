#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<vector<int>> field;
int srl [750][750][5]; //대각선 4방향으로 연속한 1의 개수
int n,m;

int diag(vector<vector<int>> field, int i, int j, int dir, int d_lim[][2], int d_unit[][2]) {
    if(srl[i][j][dir] != -1) return srl[i][j][dir];
    if(field[i][j] == 0) return srl[i][j][dir] = 0;

    if(i == d_lim[dir][0] || j == d_lim[dir][1]) srl[i][j][dir] = field[i][j]; 
    else srl[i][j][dir] = diag(field, i+d_unit[dir][0], j+d_unit[dir][1], dir, d_lim, d_unit)+1;

    return srl[i][j][dir];
}

void set_dp(vector<vector<int>> field, int d_lim[][2], int d_unit[][2]) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) { //(i, j)
            for(int d = 1; d < 5; d++) 
                srl[i][j][d] = diag(field, i, j, d, d_lim, d_unit); }}
    return;
}

int find(vector<vector<int>> field, int d_lim[][2], int d_unit[][2]) {
    int Max = 0;
    for(int s = 1; s <= (int)((min(n, m) + 1)/2); s++) { //s는 크기
        for(int i = 0; i <= n-1 - 2*(s-1); i++) { 
            for(int j = s-1; j <= m-1 - (s-1); j++) {
                int k = i + 2*(s-1);
                if(field[i][j] == 0) continue;
                if(srl[k][j][1] < s || srl[k][j][2] < s) continue;
                if(srl[i][j][3] < s || srl[i][j][4] < s) continue;

                Max = max(Max, s); }}}
            
    return Max;
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    cin >> n >> m;
    cin.ignore();
    int d_lim[5][2] = {{0, 0}, {0, 0}, {0, m-1}, {n-1, m-1}, {n-1, 0}};
    int d_unit[5][2] = {{0, 0}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
    
    for(int i = 0; i < n; i++) {
        field.push_back(vector<int>{});
        string str; getline(cin, str);
        const char* input = str.c_str();

        for(int j = 0; j < m; j++) {
            field[i].push_back((int)*(input+j) - 48);
            for(int k = 0; k < 5; k++) srl[i][j][k] = -1;   
        }
    }
    
    set_dp(field, d_lim, d_unit);
    cout << find(field, d_lim, d_unit);
}
