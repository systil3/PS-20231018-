#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <bitset>
using namespace std;
#define point pair<int, int> 
int dp[65536][16]; //dp[used][마지막 수] 형식으로 사용
int n, k, tmp, total;
vector<int> student;
vector<point> range; //정렬 후, 사이의 간격이 k를 초과하기 위해 제외해야 할 범위

int filter(int n, int i) {
	int left = range[i].first;
	int right = range[i].second;
	//left부터 right까지 인덱스들 걸러내기
	return total ^ ((int)(pow(2, right+1) - 1)^(int)(pow(2, left) - 1));
}

//used : 사용하고 남은 인덱스들
//avail : used에 속한 인덱스 중 다음에 올 수 있는 것들(16비트), i번째 자리
//last : 마지막에 선 사람의 인덱스
long long shuffle(int used, int avail, int last) {

	if(last != -1 && dp[used][last] != -1) return dp[used][last];
	if(used == total) return 1;
	long long cnt = 0;

	for(int pos = 0; pos < n; pos++) {
		if(avail & (int)pow(2, pos)) { //pos번째에 있는 사람을 오게 할 수 있음
			int new_used = used + pow(2, pos); //사용했으므로 used에 추가
			int new_avail = (total - new_used) & filter(n, pos);
			//cout << bitset<4>(filter(n, pos)) << endl;
			cnt += shuffle(new_used, new_avail, pos);
		}
	}

	return dp[used][last] = cnt;
}

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