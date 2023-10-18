#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
#define ll long long int
struct node {
	int index = -1;
	vector<int> next;
};	

int dp[502][502];
int dp_norm[502];
int dp_leak[502];

int find_normal(vector<node> tree, int pos, vector<int> leaked) { //정상 노드의 개수 구함
	if(dp_norm[pos] != -1) return dp_norm[pos];

	int sum = (leaked.find(leaked.begin(), leaked.end(), pos) == leaked.end()) ? 0 : 1;
	if(tree[pos].next.size() == 0) return 0;

	for(int &ni : tree[pos].next) 
		sum += find_normal(tree, ni);
	
    dp[pos] = sum;
	return sum;
}

int find_leaked(vector<node> tree, int pos, vector<int> leaked) { //비정상 노드의 개수 구함
	if(dp_leak[pos] != -1) return dp_leak[pos];

	int sum = (leaked.find(leaked.begin(), leaked.end(), pos) == leaked.end()) ? 1 : 0;
	if(tree[pos].next.size() == 0) return 0;

	for(int &ni : tree[pos].next) 
		sum += find_leaked(tree, ni);
	
    dp[pos] = sum;
	return sum;
}

int find_min(vector<node> tree, int m, int pos, vector<int> leaked) { //m개 중단
    //cout << pos << endl;
    if(dp[pos][m] != -1) return dp[pos][m];
    if(m == 0) return 0;
    int sum = 0;
    
	if(leaked.find(leaked.begin(), leaked.end(), pos) == leaked.end()) { //문제 있는 노드
		if(m == 1) return find_normal(tree, pos, leaked);
		else return 65535;
	}

	else {
		int tmp1 = find_normal(tree, m-1, ni, leaked); //종료시킬 때 
		int tmp2;
		for(int &ni : tree[pos].next) { //문제 없는 노드 
			
			if(find_leaked(tree, pos, leaked) == 0) {

			}
		}
	}


    dp[pos] = sum;
	return sum;
}

vector<int> solution(vector<vector<int>> edges, vector<int> leaked) {
	int n = edges.size() + 1;
	vector<bool> is_head;
	vector<node> tree;

	for(int i = 0; i <= n; i++) {
		tree.push_back(node{i});
        dp[i] = -1;
        dp_norm[i] = -1;
	}

	for(vector<int>& edge : edges) {
		int a = edge[0], b = edge[1]; // b->a
        cout << a << " " << b << " " << endl;
        tree[a].next.push_back(b);
	}

    vector<int> answer;
    for(int i = 0; i < m; i++) {
    	answer.push_back(node_sp * find_min(tree, 0, m));
    }

    return answer;
}