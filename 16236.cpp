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
#define set_input(a) {int a; cin >> a;}
#define for_range(a, i) {for(int (;i) = 0; (i) < a; (i)++)}
#define INT_MAX 65535

int field[21][21] = {0,};
int dir[3] = {-1, 0, 1};
int clock = 0;
int s_size = 2;
int levelup = 0;
int x, y;

int bfs(int n) {
	int dist[21][21] = {0, }; bool visited[21][21] = {0, };
	queue<pos> q;
	q.push(pos{x, y});
	int min_dist = INT_MAX;
	vector<pos> capture;

	while(!q.empty()) {
		pos curr = q.front(); q.pop();
		int cx = curr.first, cy = curr.second;
		
		for(int &d : dir) {
			for(int &e : dir) {
				if((d != 0 && e != 0) || (d == 0 && e == 0) || (cx+d >= n) || (cx+d < 0) 
				|| (cy+e >= n) || (cy+e < 0)) continue;

				int nx = cx+d, ny = cy+e;
				if(visited[nx][ny] == 0 && field[nx][ny] <= s_size) {

					visited[nx][ny] = 1;
					dist[nx][ny] = dist[cx][cy] + 1;
					if(dist[nx][ny] > min_dist) continue; //더 이상 탐색할 필요 X(최단거리 아님)
					
					//물고기 존재
					if(field[nx][ny] != 0 && field[nx][ny] < s_size) {
						capture.push_back(pos{nx, ny});
						min_dist = dist[nx][ny];
					}

					q.push(pos{nx, ny});
				}
			}
		}
	}

	if(capture.size() == 0) return -1;

	sort(capture.begin(), capture.end());
	int sx = capture[0].first, sy = capture[0].second;
	field[sx][sy] = 0;
	cout << "pos : " << sx << " " << sy << ", dist: " << min_dist << endl;

	if(++levelup == s_size) {s_size++; levelup = 0; cout << "size : " << s_size << endl;}

	clock += (min_dist);
	x = sx, y = sy;
	return 0;
}


int main() {
	sync_false();
	int n; cin >> n;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cin >> field[i][j];
			if(field[i][j] == 9) {x = i; y = j; field[i][j] = 0;}
		}}

	while(true) 
		if(bfs(n) == -1) break;

	cout << clock; 
}