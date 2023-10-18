#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
bool finished[10001] = {false, };
int parent[10001] = {0, };
int id = 1e9+7;

vector<vector<int>> graph;
vector<vector<int>> scc;
stack<int> s;

void connect(int n, int m) {
    graph[n].push_back(m);
}

int find_parent(int pos) {
    s.push(pos);
    int min_parent = parent[pos] = ++id;
    for(int i = 0; i < graph[pos].size(); i++) {
        int npos = graph[pos][i];

        if(parent[npos] == 0)  //방문하지 않음
            min_parent = min(find_parent(npos), min_parent);
        else if(!finished[npos])  //방문은 했는데 아직 scc에 안들어감 -> 사이클 발생
            min_parent = min(min_parent, parent[npos]);
    }

    vector<int> to_input;
    if(min_parent == parent[pos]) {
        int tmp;
        while(1) {
            tmp = s.top();
            s.pop();
            finished[tmp] = true;
            to_input.push_back(tmp);
            if(tmp == pos) break;     
        }
        scc.push_back(to_input);
    }

    return min_parent;
}

int comp(vector<int> c1, vector<int> c2) {
    return c1[0] < c2[0];
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    int v, e; cin >> v >> e;
    for(int i = 0; i < v+1; i++) {
        graph.push_back(vector<int>{});
    }

    for(int i = 0; i < e; i++) {
        int a,b; cin >> a >> b;
        connect(a, b);}

    for(int i = 1; i < v+1; i++) {
        if(parent[i] == 0) find_parent(i);}

    for(int i = 0; i < scc.size(); i++) 
        sort(scc[i].begin(), scc[i].end());
    sort(scc.begin(), scc.end(), comp);

    cout << scc.size() << "\n";
    for(int i = 0; i < scc.size(); i++) {
        for(int j = 0; j < scc[i].size(); j++) 
            cout << scc[i][j] << " ";
        cout << "-1" << "\n";
    }
}