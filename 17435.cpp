#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
#define point pair<int, int> 
vector<vector<int>> dp(20, vector<int>{0});
//이진법 자릿수(몇 번째인지)들을 리턴
vector<int> binary(int n) {
	if(n == 0) return vector<int>{};
	if(n == 1) return vector<int>{0};
	int c = log2(n);
	int l = pow(2, c);
	vector<int> b = binary(n-l); b.push_back(c);
	return b;
}

int main() {
	cin.tie(0); ios::sync_with_stdio();
	int m; cin >> m; 
	for(int i = 0; i < m; i++) {
		int tmp; cin >> tmp;
		dp[0].push_back(tmp);
	}

	//1 < n < 500000, log_2(500000) = 18.93
	for (int i = 1; i < 20; i++) {
	  dp[i] = vector<int>(m+1, 0);
	  for (int j = 1; j <= m; j++) {
	  	dp[i][j] = dp[i-1][dp[i-1][j]];
	  } 
	}

	int q; cin >> q; 
	for(int i = 0; i < q; i++) {
		int n,x; cin >> n >> x;
		vector<int> digits = binary(n); int res = x;
		for(auto &d : digits) {
			res = dp[d][res];
		} cout << res << '\n';
	}

}