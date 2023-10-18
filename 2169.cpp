#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
#define INT_MIN -21474836

vector<vector<int>> field;
int dp[1000][1000][2] = {-1, };

int find(int n, int m, int i, int j, int dir) {
	if(j > m-1) return INT_MIN;
	if(j < 0) return INT_MIN;
	if(i < 0) return INT_MIN;
	if(dp[i][j][dir] != INT_MIN) return dp[i][j][dir];

	int tmp1 = -1, tmp2 = -1, tmp3 = -1;

	if(dir == 0) { // 오른쪽 
		tmp1 = find(n, m, i-1, j, 0);
		tmp2 = find(n, m, i-1, j, 1);
		tmp3 = find(n, m, i, j-1, 0);
	}

	else { // 왼쪽 
		tmp1 = find(n, m, i-1, j, 0);
		tmp2 = find(n, m, i-1, j, 1);
		tmp3 = find(n, m, i, j+1, 1);
	}

	dp[i][j][dir] = max(tmp1, max(tmp2, tmp3)) + field[i][j];
	return dp[i][j][dir];
}

int main() {
	
	int n,m; cin >> n >> m;
	for(int i = 0; i < n; i++) {
		field.push_back(vector<int>{});

		for(int j = 0; j < m; j++) {
			int tmp; cin >> tmp;
			field[i].push_back(tmp);
			dp[i][j][0] = INT_MIN; dp[i][j][1] = INT_MIN;
		}
	}

	dp[0][0][0] = field[0][0];

	cout << find(n, m, n-1, m-1, 0);
} 