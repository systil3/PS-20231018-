#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;
#define ll long long int
#define pos pair<int, int>
#define INT_MAX 65535
int d,e,f;

int main() {
	int n; cin >> n;
	vector<int> arr;
	for(int i = 0; i < n; i++) {
		int t; cin >> t;
		arr.push_back(t);
	}

	sort(arr.begin(), arr.end());

	int x; cin >> x;

	int i = 0, j = n-1;
	int cnt = 0;

	while(i < j) {
		if(arr[i]+arr[j] < x) i++;
		else if(arr[i]+arr[j] > x) j--;
		else {cnt++; i++;}
	}

	cout << cnt << endl;
}