#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
vector<int> dp;
vector<int> arr;

int lis(vector<int>arr, int n, int s) {
	if(dp[s] != -1) return dp[s];
	if(s == n-1) return 1;
	if(s > n-1) return 0;

	int tmp = 1;
	for(int i = s; i < n; i++) {
		if(arr[s] < arr[i]) {
			tmp = max(tmp, lis(arr, n, i)+1);
		}
	}

	dp[s] = tmp;
	return tmp;
}

int main() {
	int n; cin >> n;
	for(int i = 0; i < n; i++) {
		dp.push_back(-1);
		int tmp; cin >> tmp;
		arr.push_back(tmp);
	}
	int res = 0;
	for(int i = 0; i < n; i++) 
		res = max(res, lis(arr, n, i));
	cout << res;
}