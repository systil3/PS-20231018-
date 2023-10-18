#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
#define point pair<int, int> 
vector<vector<int>> adj(1001, vector<int>{});
int cost[1001][1001] = {0, };
int n, m;

int solve(int pos, int parent, int curr_cost) {
	//리프 노드이면 반드시 끊어야 함
	for(int &n : adj[pos]) {
		if(n==parent) continue;
		//인접한 각 노드들에 대해서 끊는 경우랑 안 끊는 경우를 비교
		//만약 연결점의 차수가 1이면 무조건 끊어야 함
		if(adj[n].size() == 1) curr_cost += cost[pos][n];
		else curr_cost = min(curr_cost + cost[pos][n], solve(n, pos, curr_cost));
	}
	
	return curr_cost;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while(t--) {
		vector<vector<int>> newadj(1001, vector<int>{});
        adj.swap(newadj);
		int n, m; cin >> n >> m;
		for(int i = 0; i < m; i++) {
			int a, b, r; cin >> a >> b >> r;
			adj[a].push_back(b);
			adj[b].push_back(a);
			cost[a][b] = r; cost[b][a] = r; 
		}
	}

	cout << solve(1, -1, 0);
}