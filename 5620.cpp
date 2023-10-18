#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
#define point pair<int, int> 
#define x first
#define y second
#define INT_MAX 2147483647

vector<int> dp;
vector<point> points;

int dist(point p, point q) {
	return pow((p.x-q.x), 2) + pow((p.y-q.y), 2);
	
}

bool cmpX(point p, point q) {
	return p.x == q.x ? p.y < q.y : p.x < q.x;
}

int solve(int l, int r) {
	if(r == l) return INT_MAX;
	if(r == l+1) return dist(points[l], points[r]);

	int mid = (l+r)/2;
	while(points[mid].x == points[mid+1].x) mid++;
	int dist1 = solve(l, mid), dist2 = solve(mid+1, r);
	int curr_min = min(dist1, dist2);

	int width = 0, border = -1, section;
	//왼쪽 집합 1개와 오른쪽 집합 1개 간 거리 중 최대가 뭐지?

	for(int lpos = mid; lpos >= l; lpos--) {
		int rpos = mid+1;
		if(points[mid+1].x - points[lpos].x >= curr_min) break;
		int ly = points[lpos].y;
		while(rpos <= r) {
			if(points[rpos].x - points[lpos].x >= curr_min) break;

			//y좌표 같은 점끼리 묶기
			border = rpos;
			while(points[border].x == points[border+1].x) {
				if(points[border].y <= ly && points[border+1].y >= ly) section = border;
				border++;
			}

			//y좌표 떨어진 거리가 최소인 점 찾기
			if(points[rpos].y >= ly) curr_min = min(curr_min, dist(points[rpos], points[lpos]));
			else if(points[border].y <= ly) curr_min = min(curr_min, dist(points[border], points[lpos]));
			else curr_min = min(curr_min, 
					min(dist(points[section], points[lpos]), dist(points[section+1], points[lpos])));

			rpos = border + 1;
		}
	}
	return curr_min;
}

int main() {
	int n; cin >> n;
	cin.tie(0); ios::sync_with_stdio();
	for(int i = 0; i < n; i++) {
		int a,b; cin >> a >> b;
		points.push_back(point{a,b});
	}

	sort(points.begin(), points.end(), cmpX);
	cout << solve(0, n-1);
}