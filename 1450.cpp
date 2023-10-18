#include <iostream>
#include <queue>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
using namespace std;
#define INT_MAX 2147483600
#define ll long long
vector<int> arr;
vector<int> la;
vector<int> ra;
long long cnt = 0;

void dfs(int pos, int r, vector<int> &totals, int curr_sum, int c) {
	if(pos > r) {totals.push_back(curr_sum); return;}
	dfs(pos+1, r, totals, curr_sum, c);
	dfs(pos+1, r, totals, curr_sum + arr[pos], c);
}

ll b_search(int l, int r, int key, int c) {
	if(l == r) return key+ra[l] <= c ? l+1 : l;

	int m = (l+r)/2;
	if(key+ra[m] > c) return b_search(l, m-1, key, c);
	else if(key+ra[m] < c) return b_search(m+1, r, key, c);
	else {
		int cnt = m; 
		while(ra[cnt] == ra[m]) {cnt++; if(cnt > r) break;}
		return cnt;
	}
}

void find(int n, int c) {
	cnt = 0;
	vector<int> res;

	dfs(0, n/2, la, 0, c);
	dfs(n/2+1, n-1, ra, 0, c);
	sort(ra.begin(), ra.end());
	int a = ra.size();

	for(int &ln : la) 
		{cnt += b_search(0, a-1, ln, c);}

	return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
	int n; int c; cin >> n >> c;
	
	for(int i = 0; i < n; i++) {
		int t; cin >> t;
		arr.push_back(t);
	}

	find(n, c);
	cout << cnt << endl;
}