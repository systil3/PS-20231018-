#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <bitset>
using namespace std;
#define point pair<int, int> 
int dp[1048576][16]; //dp[used][마지막 수] 형식으로 사용
int n, k, tmp, total;
vector<int> student;
vector<point> range; //정렬 후, 사이의 간격이 k를 초과하기 위해 제외해야 할 범위

int main() {
    
    ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	for(int i = 0; i < n; i++) {
		cin >> tmp; student.push_back(tmp);
	} total = pow(2, n)-1;

	sort(student.begin(), student.end());
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < total+1; j++) 
            dp[j][i] = -1;
		
		int left = i, right = i;
		while(left >= 0 && student[i] - student[left] <= k) left--;
		while(right <= n-1 && student[right] - student[i] <= k) right++;
		range.push_back(point{left+1, right-1});
	}

	cout << shuffle(0, pow(2, n)-1, -1);
}