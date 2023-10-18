#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <vector>
#define fst first
#define snd second
#define ll long long int
#define len(x) (x).snd - (x)
using namespace std;
struct line {
	ll fst;
	ll snd;
	bool covered = false;
	void printl() {cout << fst << " - " << snd << endl;}
};

vector<line> L;
vector<int> f, s;

bool cmp(line a, line b) {
	return a.fst < b.fst;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	
	for(int i = 0; i < n; i++) {
		int a,b; cin >> a >> b;
		if(a > b) swap(a, b);
		f.push_back(a); s.push_back(b); }
	int d; cin >> d;
	int ret = -1;

	for(int i = 0; i < n; i++) {
		if(d >= s[i] - f[i]) L.push_back(line{f[i],s[i]});}

	if(!L.size()) {cout << 0; exit(0);}
	
	sort(L.begin(), L.end(), cmp);
	int cnt = 0, pos = 0, cover = 0;
	ll ls = L[0].fst, rs = L[0].snd;

	queue<line> q;
	n = L.size();

	int group = 0;
	while(pos < n) {
		while(L[cover].fst < L[pos].fst + d) {
			if(L[cover].snd <= L[pos].fst + d) {
				L[cover].covered = true; cnt++;}
			q.push(L[cover]); 
			//cover : 현재 위치에서 오른쪽으로 완전히 벗어나지 않는 선분의 최대 인덱스
            if(++cover >= n) break;
		}

		ret = max(ret, cnt);

		int dist = 0;
		while(L[pos + dist].fst == L[pos].fst) {
			dist++; 
			if(pos + dist >= n) break;
			cnt--; q.pop();
		} //위치를 다음 라인의 왼쪽 점으로 이동
		pos += dist;

		group = 0;
		while(L[pos + group].fst == L[pos].fst) {
			group++;
            if(pos + group >= n) break;
			if(L[pos + group].covered == false) {
				L[pos + ++group].covered == true;}
		}
	}
	cout << ret;
}