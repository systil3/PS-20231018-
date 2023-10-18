#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define fst first
#define snd second
#define ll long long int
#define len(x) (x).snd - (x)
using namespace std;

vector<string> field;
int dp[1001][1001]; // (i, j)를 오른쪽 끝점으로 갖는 정사각형 중 최대 변

int find(int a, int b) {
	if(dp[a][b] != -1) return dp[a][b];
	if(a == 0 || b == 0) return field[a][b] == '1';
	
	if(field[a][b] == '0') return 0;
	else {
		int dist = min(find(a, b-1), find(a-1, b));

		if(field[a-dist][b-dist] == '1') dp[a][b] = dist + 1;
		else dp[a][b] = dist;

		return dp[a][b];
	}
}


int main() {
	int n,m; cin >> n >> m;

	for(int i = 0; i < n; i++) {
		string str; cin >> str;
		field.push_back(str);
		for(int j = 0; j < m; j++) {
			dp[i][j] = -1; }
	}
	
	int res = -1;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			res = max(res, find(i, j)); }}

	cout << res*res;
}