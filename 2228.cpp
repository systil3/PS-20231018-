#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
#define ll long long int
#define INT_MIN -2147483640
int dp[55][105];
vector<int> arr;

int find(int n, int k, int s) { //s : 최초 포함 위치
	int sum = 0;
	int Max = INT_MIN;
	if(dp[k][s] != INT_MIN) return dp[k][s];

	cout << n << " " << k << " " << s << endl; 
	if(n-s + 1 < 2*k) return INT_MIN;
	if(k == 0) return 0;

	for(int i = s; i < n; i++) {	
		sum += arr[i];
		if(k != 1) {
			for(int j = i+2; j < n; j++) 
				Max = max(Max, sum + find(n, k-1, j)); }
		else Max = max(Max, sum);
	}

	dp[k][s] = Max;
	cout << Max <<endl;
	return Max;
}

int main() {
	int n, m; cin >> n >> m;
	for(int i = 0; i < 55; i++) {
		for(int j = 0; j < 105; j++) {
			dp[i][j] = INT_MIN;
		}}

	int res = INT_MIN;
	for(int i = 0; i < n; i++) {
		int tmp; cin >> tmp;
		arr.push_back(tmp);
	}


	for(int i = 0; i < n; i++) 
		res = max(res, find(n, m, i));
	
	cout << res;
}