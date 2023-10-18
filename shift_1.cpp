#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;
#define ll long long int
#define pos pair<int, int>
#define sync_false() {ios::sync_with_stdio(0); cin.tie(0);}
#define INT_MAX 65535
int d,e,f;

bool solution(int a, int b, int c, int d, int e, int f) {
	if(a >= d && b >= e && c >= f) return true;
	if(a+b+c <= d+e+f) return false;

	if()

	return solution(a-2, b, c+1, d, e, f) || solution(a-2, b+1, c, d, e, f)
	|| solution(a+1, b-2, c, d, e, f) || solution(a, b-2, c+1, d, e, f)
	|| solution(a+1, b, c-2, d, e, f) || solution(a, b+1, c-2, d, e, f);
}

int main() {
	int a,b,c; cin >> a >> b >> c >> d >> e >> f;

	cout << (solution(a, b, c, d, e, f) ? "true" : "false");
    return 0;
}