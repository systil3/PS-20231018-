#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
#define ll long long int
int cnt = 1;

struct node {
	vector<int> adj;
	int in_deg = -1;
	int out_deg = -1;
	int index = -1;
	void connect(node b) {
		adj.push_back(b.index);}
};	

bool cmp(node a, node b) {
	return a.out_deg < b.out_deg;
}

vector<node> graph;
vector<bool> visited;
vector<int> dp, time;

void dfs(vector<node> graph, int pos) {
	visited[pos] = true;
	graph[pos].in_deg = cnt;
	for(int &adj_ind : graph[pos].adj) {
		if(visited[adj_ind]) continue;
		cnt++;
		dfs(graph, adj_ind);
	}

	graph[pos].out_deg = cnt;
}

int main() {
	int t; cin >> t;
	
	while(t--) {
		int n, k; cin >> n >> k;
		graph.clear();
		visited.clear();
		time.clear();
		dp.clear();
		cnt = 1;

		for(int i = 0; i < n; i++) {
			int tmp; cin >> tmp;
			graph.push_back(node{vector<int>{}, -1, -1, i});
			time.push_back(tmp);
			visited.push_back(false);
			dp.push_back(-1);
			graph[i].index = i;
		}

		for(int i = 0; i < k; i++) {
			int a,b; cin >> a >> b;
			graph[a].connect(graph[b]); //a의 인접리스트에 b 인덱스 투입
		}

		dfs(graph, 0);
		sort(graph.begin(), graph.end(), cmp);
	}
}