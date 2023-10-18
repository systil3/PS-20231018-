#include <iostream>
#include <queue>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
using namespace std;
#define INT_MAX 2147483600
vector<int> arr;

vector<int> get_primes(int n) {
	vector<bool> isprime(n+1, true);
    isprime[0] = false, isprime[1] = false;

	for(int i = 2; i <= sqrt(n); i++) {
		int tmp = i;
		if(isprime[i] == false) continue;

		while(tmp <= n) {
			if(tmp != i) isprime[tmp] = false;
			tmp += i;
		}
	}

	vector<int> ret;
	for(int i = 1; i <= n; i++) {
		if(isprime[i]) ret.push_back(i);
	}

	return ret;
}

int main() {
	int n; cin >> n;

	vector<int> arr = get_primes(n);
	
	for(int &p : arr) cout << p << " ";
	int m = arr.size(); 
    if(m == 0) {cout << 0; return 0;}
    
	int sum = 0, k = 0;
	while(k < m && sum < n) {
		sum += arr[k]; k++;}

	int i = 0, j = k-1, cnt = 0;

	while(j < m) {
		while(sum > n) {sum -= arr[i]; i++;} 

		if(sum < n) {j++; sum += arr[j];}
		else {sum -= arr[i]; cnt++; i++;} 
	}

	cout << cnt << endl;
}