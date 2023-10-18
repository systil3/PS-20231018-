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

int dp[100002];

int find_sum(vector<node> tree, int pos) { //sp 1이라 치고 총합 구함
    //cout << pos << endl;
    if(dp[pos] != -1) return dp[pos];

	int sum = 0;
	if(tree[pos].next.size() == 0) return 1;

	for(int &ni : tree[pos].next) 
		sum += find_sum(tree, ni);
	
    dp[pos] = sum;
	return sum;
}

vector<int> solution(int total_sp, vector<vector<int>> skills) {
	int n = skills.size() + 1;
	vector<bool> is_head;
	vector<node> tree;

	for(int i = 0; i < n; i++) {
		tree.push_back(node{i});
        dp[i] = -1;
	}

	for(vector<int>& skill : skills) {
		int a = skill[0]-1, b = skill[1]-1; // b->a
        cout << a << " " << b << " " << endl;
        tree[a].next.push_back(b);
	}

	int total_node_sum = 0;
	for(int i = 0; i < n; i++) 
		total_node_sum += find_sum(tree, i);

    //cout << "total : " << total_node_sum << endl;
	
	int node_sp = (int)(total_sp / total_node_sum);

    vector<int> answer;
    for(int i = 0; i < n; i++) {
    	answer.push_back(node_sp * find_sum(tree, i));
    }

    return answer;
}