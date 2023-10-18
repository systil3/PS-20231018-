#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <string>
using namespace std;
#define ll long long int
#define pos pair<int, int>
#define INT_MAX 2147483600
int d,e,f;
vector<int> arr;

int main() {
	int n, s; cin >> n >> s;
	
	for(int i = 0; i < n; i++) {
		int t; cin >> t;
		arr.push_back(t);
	}

	int sum = 0, k = 0;
	while(k < n && sum < s) {
		sum += arr[k]; k++;}

	if(sum < s) {cout << 0 << endl; return 0;}

	int res = k;

	int i = 0, j = k-1;
	while(i < j && j < n) {
		while(sum - arr[i] >= s) {
			sum -= arr[i];
			i++;
		}

		res = min(res, j-i+1);
		j++; sum += arr[j]; 
	}

	cout << res << endl;
}