#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
#define ll long long int
ll dp1[101][101] = {-1, }; //1로 시작하는 수열
ll dp0[101][101] = {-1, }; //0으로 시작하는 수열
vector<int> arr;

ll find(int n, int k, int sbit) {
	if(sbit == 1) {
		if(dp1[n][k] != -1) return dp1[n][k];
		if(n == 1) return (k == 0 ? 1 : 0);
		if(n-1 < k || k < 0) return 0;

		dp1[n][k] = find(n-1, k-1, 1) + find(n-1, k, 0);
		return dp1[n][k];
	}

	if(sbit == 0) {
		if(dp0[n][k] != -1) return dp0[n][k];
		if(n == 1) return (k == 0 ? 1 : 0);
		if(n-2 < k || k < 0) return 0;

		dp0[n][k] = find(n-1, k, 1) + find(n-1, k, 0);
		return dp0[n][k];
	}
}

int main() {
	int t; cin >> t;
	for(int i = 0; i < 101; i++) {
		for(int j = 0; j < 101; j++) {
			dp1[i][j] = -1; dp0[i][j] = -1;
		}
	}

	while(t--) {
		int a,b; cin >> a >> b;
		cout << find(a, b, 0) + find(a, b, 1) << endl;
	}
}