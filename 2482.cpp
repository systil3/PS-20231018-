#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
int dpc[1001][1001] = {-1, };
int dpl[1001][1001] = {-1, };
#define ll long long  
ll mod = 1000000003;
vector<int> arr;

ll find_l(int n, int k) {
	if(dpl[n][k] != -1) return dpl[n][k];
	if(n < 0) return 0;
	if(n == 0) return 1;
	if(n == 1) return (k == 0 ? 1 : (k == 1 ? 1 : 0));
	if(n == 2) return (k == 0 ? 1 : (k == 1 ? 2 : 0));

	ll tmp1 = find_l(n-1, k);
	ll tmp2 = find_l(n-2, k-1);
	dpl[n][k] = (tmp1 + tmp2) % mod; return dpl[n][k];
}

ll find_c(int n, int k) {
	if(dpc[n][k] != -1) return dpc[n][k];
	if(n < 0) return 0;
	if(n == 0) return 1;
	if(n == 1) return (k == 0 ? 1 : (k == 1 ? 1 : 0));
	if(n == 2) return (k == 0 ? 1 : (k == 1 ? 2 : 0));

	//1번째 색 선택
	ll tmp1 = find_l(n-3, k-1);
	//1번째 선택 x 
	ll tmp2 = find_l(n-1, k);
	dpc[n][k] = (tmp1 + tmp2) % mod; return dpc[n][k];
}

int main() {
	for(int i = 0; i < 1001; i++) {
		for(int j = 0; j < 1001; j++) {
			dpc[i][j] = -1; dpl[i][j] = -1;
		}
	}
	int n, k; 
	cin >> n; cin >> k;
	
	cout << find_c(n, k);
}