#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
using namespace std;
#define inf 1e9 + 7
int dp[100][10001];
struct edge
{
    int m;
    int c;
    int d;
}; 

vector<vector<edge>> graph;

void connect(int n, int m, int c, int d) {
    graph[n].push_back(edge{m, c, d});
    graph[m].push_back(edge{n, c, d});
}

struct cmp{
    bool operator()(edge e1, edge e2) {
        return e1.m < e2.m;
    }
};

void dijkstra(int start, int n, int m, int k) {
    priority_queue<edge, vector<edge>, cmp> pq;
    pq.push(edge{start, 0, 0});
    for(int i = 0; i < m; i++) dp[0][i] = 0;
    int c_ind, c_cost, c_time, n_ind, n_cost, n_time;

    while(!pq.empty()) {
        edge pos = pq.top();
        pq.pop();
        c_ind = pos.m; c_cost = pos.c; c_time = pos.d;
        //cout << c_ind << " " << c_cost << " " << c_time << endl;
        if(c_time > dp[c_ind][c_cost]) continue;

        for(auto &node_info : graph[c_ind]) {
            n_ind = node_info.m;
            n_cost = node_info.c + c_cost;
            n_time = node_info.d + c_time;

            if(n_cost > m || n_time >= dp[n_ind][n_cost]) continue; 

            for(int j = n_cost+1; j <= m; j++) {
                if(dp[n_ind][j] < n_time) break;
                dp[n_ind][j] = n_time;
            }

            dp[n_ind][n_cost] = n_time;
            pq.push(edge{n_ind, n_cost, n_time});
        }
    }
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    int t; cin >> t;
    while(t--) {
        int min_time = inf;
        int n, m, k; cin >> n >> m >> k;    
        graph = vector<vector<edge>>(n, vector<edge>{});
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m+1; j++) {
                dp[i][j] = inf;
            }
        }

        for(int i = 0; i < k; i++) {
            int u,v,c,d; cin >> u >> v >> c >> d;
            connect(u-1, v-1, c, d);
        }

        dijkstra(0, n, m, k);
        for(int i = 0; i < m+1; i++)
            min_time = min(min_time, dp[n-1][i]);

        if(min_time == inf) cout << "Poor KCM" << "\n";
        else cout << min_time << "\n";
    }
}